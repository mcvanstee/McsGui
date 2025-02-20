#include "display_hal.h"

#include "display_driver.h"
#include <stdbool.h>

#include "main.h"


typedef enum {
    DISPLAY_DMA_TRANSFER_IDLE,
    DISPLAY_DMA_TRANSFER_COLOR,
    DISPLAY_DMA_TRANSFER_PIXEL_DATA
} DisplayDmaTransferState_e;

/* Constants */
#define DISPLAY_SPI_TIMEOUT 1000

/* Private function declarations */
static void display_hal_commandMode(void);

static inline void display_hal_waitForSpiReady(void);
static inline void display_hal_addColorToBuffer(const uint16_t color);

/* Module global variables */
static volatile DisplayDmaTransferState_e m_dmaTransferState;
static uint8_t m_colorBuffer[DISPLAY_COLOR_BUFFER_SIZE_BYTES];
static uint8_t *p_pixelBuffer;
static volatile int32_t m_pixelsToWrite;
static volatile int32_t m_writeIndex;


void display_hal_init(void)
{
    m_pixelsToWrite = 0;
    m_writeIndex = 0;
    m_dmaTransferState = DISPLAY_DMA_TRANSFER_IDLE;
    p_pixelBuffer = NULL;

    display_hal_chipSelectHigh();
    display_hal_dataMode();
}

void display_hal_sendCommand(uint8_t command)
{
    display_hal_waitForSpiReady();
    display_hal_commandMode();
    display_hal_chipSelectLow();
    HAL_SPI_Transmit(g_p_displaySPI, &command, 1, DISPLAY_SPI_TIMEOUT);
    display_hal_chipSelectHigh();
}

void display_hal_sendU8Data(const uint8_t data)
{
	display_hal_waitForSpiReady();
	display_hal_dataMode();
	display_hal_chipSelectLow();
	HAL_SPI_Transmit(g_p_displaySPI, &data, 1, DISPLAY_SPI_TIMEOUT);
	display_hal_chipSelectHigh();
}

void display_hal_sendCommandData(uint8_t command, const uint8_t *p_data, const uint8_t dataLength)
{
    display_hal_waitForSpiReady();
    display_hal_commandMode();
    display_hal_chipSelectLow();
    HAL_SPI_Transmit(g_p_displaySPI, &command, 1, DISPLAY_SPI_TIMEOUT);
    display_hal_dataMode();
    HAL_SPI_Transmit(g_p_displaySPI, (uint8_t*)p_data, dataLength, DISPLAY_SPI_TIMEOUT);
    display_hal_chipSelectHigh();
}

void display_hal_writeColor(const uint16_t color, const int32_t pixels)
{
	display_hal_addColorToBuffer(color);
	display_hal_waitForSpiReady();
    display_hal_dataMode();
    display_hal_chipSelectLow();

    m_dmaTransferState = DISPLAY_DMA_TRANSFER_COLOR;
    m_pixelsToWrite = pixels;

    const uint16_t bytesToSend = (pixels > DISPLAY_COLOR_BUFFER_SIZE_PIXELS) ? DISPLAY_COLOR_BUFFER_SIZE_BYTES : pixels * 2;

    HAL_SPI_Transmit_DMA(g_p_displaySPI, m_colorBuffer, bytesToSend);

    display_hal_waitForSpiReady();
}

void display_hal_writePixelData(const uint16_t *p_data, const int32_t pixels)
{
    display_hal_waitForSpiReady();
    display_hal_dataMode();
    display_hal_chipSelectLow();

    m_dmaTransferState = DISPLAY_DMA_TRANSFER_PIXEL_DATA;
    m_pixelsToWrite = pixels;
    m_writeIndex = 0;
    p_pixelBuffer = (uint8_t *)p_data;

    const uint16_t bytesToSend = (pixels > DISPLAY_COLOR_BUFFER_SIZE_PIXELS) ? DISPLAY_COLOR_BUFFER_SIZE_BYTES : pixels * 2;

    HAL_SPI_Transmit_DMA(g_p_displaySPI, (uint8_t*) p_data, bytesToSend);
}

void display_hal_transmissionFinished(void)
{
    display_hal_waitForSpiReady();
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (g_p_displaySPI != hspi)
    {
        return;
    }

    m_pixelsToWrite -= DISPLAY_COLOR_BUFFER_SIZE_PIXELS;

    if (m_dmaTransferState == DISPLAY_DMA_TRANSFER_COLOR)
    {
        if (m_pixelsToWrite > DISPLAY_COLOR_BUFFER_SIZE_PIXELS)
        {
            HAL_SPI_Transmit_DMA(g_p_displaySPI, m_colorBuffer, DISPLAY_COLOR_BUFFER_SIZE_BYTES);
        }
        else if (m_pixelsToWrite > 0)
        {
            HAL_SPI_Transmit_DMA(g_p_displaySPI, m_colorBuffer, m_pixelsToWrite * 2);
        }
        else
        {
            m_dmaTransferState = DISPLAY_DMA_TRANSFER_IDLE;
            display_hal_chipSelectHigh();
        }
    }
    else if (m_dmaTransferState == DISPLAY_DMA_TRANSFER_PIXEL_DATA)
    {
        m_writeIndex += DISPLAY_COLOR_BUFFER_SIZE_BYTES;

        if (m_pixelsToWrite > DISPLAY_COLOR_BUFFER_SIZE_PIXELS)
        {
            HAL_SPI_Transmit_DMA(g_p_displaySPI, &p_pixelBuffer[m_writeIndex], DISPLAY_COLOR_BUFFER_SIZE_BYTES);
        }
        else if (m_pixelsToWrite > 0)
        {
            HAL_SPI_Transmit_DMA(g_p_displaySPI, &p_pixelBuffer[m_writeIndex], m_pixelsToWrite * 2);
        }
        else
        {
            m_dmaTransferState = DISPLAY_DMA_TRANSFER_IDLE;
            display_hal_chipSelectHigh();
        }
    }
    else
    {
        // Reset the state
        //
        m_dmaTransferState = DISPLAY_DMA_TRANSFER_IDLE;
        display_hal_chipSelectHigh();
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    if (g_p_displaySPI != hspi)
    {
        return;
    }

    m_dmaTransferState = DISPLAY_DMA_TRANSFER_IDLE;
    display_hal_chipSelectHigh();
}

void display_hal_readCmd(uint8_t cmd, uint8_t *p_data, const uint32_t dataLength)
{
    display_hal_sendCommand(cmd);
    display_hal_readData(p_data, dataLength);
}

void display_hal_readData(uint8_t *p_data, const uint32_t dataLength)
{
    display_hal_waitForSpiReady();
    display_hal_dataMode();
    display_hal_chipSelectLow();
    HAL_SPI_Receive(g_p_displaySPI, p_data, dataLength, DISPLAY_SPI_TIMEOUT);
    display_hal_chipSelectHigh();
}

void display_hal_backlightOn(void)
{
	display_hal_setBacklight(100);
}

void display_hal_backlightOff(void)
{
	display_hal_setBacklight(0);
}

void display_hal_setBacklight(const uint8_t percentage)
{
    const uint32_t clk = g_p_displayBacklightPWMTimer->Init.Period;
    uint32_t pulse = (clk * percentage) / 100;

    if (percentage > 100)
    {
        pulse = clk;
    }

    HAL_TIM_PWM_Stop(g_p_displayBacklightPWMTimer, TIM_CHANNEL_4);

    TIM_OC_InitTypeDef sConfigOC;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(g_p_displayBacklightPWMTimer, &sConfigOC, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(g_p_displayBacklightPWMTimer, TIM_CHANNEL_4);
}

void display_hal_delay(const uint32_t delay)
{
	HAL_Delay(delay);
}

void display_hal_chipSelectHigh(void)
{
	HAL_GPIO_WritePin(Display_CS_GPIO_Port, Display_CS_Pin, GPIO_PIN_SET);
}

void display_hal_chipSelectLow(void)
{
	HAL_GPIO_WritePin(Display_CS_GPIO_Port, Display_CS_Pin, GPIO_PIN_RESET);
}

void display_hal_dataMode(void)
{
	HAL_GPIO_WritePin(Display_DC_GPIO_Port, Display_DC_Pin, GPIO_PIN_SET);
}

static void display_hal_commandMode(void)
{
	HAL_GPIO_WritePin(Display_DC_GPIO_Port, Display_DC_Pin, GPIO_PIN_RESET);
}

void display_hal_resetHigh(void)
{
    HAL_GPIO_WritePin(Display_Reset_GPIO_Port, Display_Reset_Pin, GPIO_PIN_SET);
}

void display_hal_resetLow(void)
{
	HAL_GPIO_WritePin(Display_Reset_GPIO_Port, Display_Reset_Pin, GPIO_PIN_RESET);
}

void display_hal_powerOn(void)
{
}

void display_hal_powerOff(void)
{
}

static inline void display_hal_waitForSpiReady(void)
{
    while ((HAL_SPI_STATE_READY != g_p_displaySPI->State) && (m_dmaTransferState != DISPLAY_DMA_TRANSFER_IDLE));
}

static void display_hal_addColorToBuffer(const uint16_t color)
{
    uint16_t *p_colorBuffer = (uint16_t *)m_colorBuffer;

    if (p_colorBuffer[0] == color)
    {
        return;
    }

    for (uint32_t i = 0; i < DISPLAY_COLOR_BUFFER_SIZE_PIXELS; i++)
    {
        p_colorBuffer[i] = color;
    }
}



/*** end of file ***/
