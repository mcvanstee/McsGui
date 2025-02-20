#include "touch_driver.h"

#include <stdbool.h>

#include "stm32l4xx_hal.h"

#include "main.h"
#include "display_api.h"
#include "sys_timer.h"
#include "touch_api.h"

#define TOUCH_STATE_NOT_PRESSED 0x01
#define TOUCH_STATE_PRESSED 0x02

#define TOUCH_Z_PRESSED_VALUE 250
#define TOUCH_Z_MAX_VALUE 0xFFFF

#define XPT2046_START_BIT   0x01 << 7
#define XPT2046_A2_ENABLE   0x01 << 6
#define XPT2046_A1_ENABLE   0x01 << 5
#define XPT2046_A0_ENABLE   0x01 << 4
#define XPT2046_MODE_8BIT   0x01 << 3
#define XPT2046_MODE_SER    0x01 << 2
#define XPT2046_PD1_ENABLE  0x01 << 1
#define XPT2046_PD0_ENABLE  0x01 << 0

// XPT2046_PowerModes
#define XPT2046_POWER_DOWN 0x00
#define XPT2046_REFERENCE_OFF_ADC_ON XPT2046_PD0_ENABLE
#define XPT2046_REFERENCE_ON_ADC_OFF XPT2046_PD1_ENABLE
#define XPT2046_DEVICE_ALWAYS_ON XPT2046_PD1_ENABLE | XPT2046_PD0_ENABLE

// XPT2046_ReferenceModes
#define XPT2046_DFR_MODE 0
#define XPT2046_SER_MODE XPT2046_MODE_SER

// XPT2046 Channel Modes
#define XPT2046_SER_TEMP0 0
#define XPT2046_SER_Y XPT2046_A0_ENABLE
#define XPT2046_SER_VBAT XPT2046_A1_ENABLE
#define XPT2046_SER_Z1 XPT2046_A1_ENABLE | XPT2046_A0_ENABLE
#define XPT2046_SER_Z2 XPT2046_A2_ENABLE
#define XPT2046_SER_X XPT2046_A2_ENABLE | XPT2046_A0_ENABLE
#define XPT2046_SER_AUXIN XPT2046_A2_ENABLE | XPT2046_A1_ENABLE
#define XPT2046_SER_TEMP1 XPT2046_A2_ENABLE | XPT2046_A1_ENABLE | XPT2046_A0_ENABLE
#define XPT2046_DFR_Y XPT2046_A0_ENABLE
#define XPT2046_DFR_Z1 XPT2046_A1_ENABLE | XPT2046_A0_ENABLE
#define XPT2046_DFR_Z2 XPT2046_A2_ENABLE
#define XPT2046_DFR_X XPT2046_A2_ENABLE | XPT2046_A0_ENABLE

#define XPT2046_12BIT_MODE 0
#define XPT2046_8BIT_MODE XPT2046_MODE_8BIT

#define XPT2046_NONE 0
#define XPT2046_START XPT2046_START_BIT

#define CMD_X (XPT2046_12BIT_MODE | XPT2046_REFERENCE_OFF_ADC_ON |XPT2046_DFR_MODE | XPT2046_DFR_X | XPT2046_START)
#define CMD_Y (XPT2046_12BIT_MODE | XPT2046_REFERENCE_OFF_ADC_ON |XPT2046_DFR_MODE | XPT2046_DFR_Y | XPT2046_START)
#define CMD_Z1 (XPT2046_12BIT_MODE | XPT2046_REFERENCE_OFF_ADC_ON |XPT2046_DFR_MODE | XPT2046_DFR_Z1 | XPT2046_START)
#define CMD_Z2 (XPT2046_12BIT_MODE | XPT2046_REFERENCE_OFF_ADC_ON |XPT2046_DFR_MODE | XPT2046_DFR_Z2 | XPT2046_START)

#define TOUCHPAD_SPI_TIMEOUT_MS 1000
#define ERR_RANGE 50    //tolerance scope
#define NUMBER_OF_ADC_READINGS 5
#define LOST_NUM    1   //Discard value


static void touch_dr_calculatePointPressed(const uint32_t xADValue, const uint32_t yADValue);
static void touch_dr_rotatePoint(int32_t *p_x, int32_t *p_y, const int32_t x_raw, const int32_t y_raw);
static void touch_dr_validatePoint(int32_t *p_x, int32_t *p_y);
static bool touch_dr_readTwiceADC(uint32_t *p_out_xADC, uint32_t *p_out_yADC, uint32_t *p_out_zValue);
static uint32_t touch_dr_readADC(uint8_t cmd);
static void touch_dr_initSPI(const uint32_t baudRatePrescaler);
static void touch_dr_readADC_XYZ(uint32_t *p_out_xADC, uint32_t *p_out_yADC, uint32_t *p_out_zPressValue);
static uint32_t touch_dr_readADCAverage(const uint8_t channelCmd);
static void touch_dr_cs_select(void);
static void touch_dr_cs_deSelect(void);

extern SPI_HandleTypeDef hspi1;

static uint8_t m_touchState;
static TouchPoint_s m_pointPressed;
static TouchADCValues_s m_adcValues;
static TouchCalibrationValues_s m_calibrationValues;

void touch_dr_init(void)
{
    timer_init();
    touch_dr_cs_deSelect();
    m_touchState = TOUCH_STATE_NOT_PRESSED;
    touch_dr_resetCalibration();
}

void touch_dr_scan(void)
{
    uint32_t xADValue = 0;
    uint32_t yADValue = 0;
    uint32_t zValue = 0;

    const bool readADC_OK = touch_dr_readTwiceADC(&xADValue, &yADValue, &zValue);
    const bool pressed = (zValue <= TOUCH_Z_PRESSED_VALUE);

    if (!readADC_OK || !pressed || ((xADValue == 0) && (yADValue == 0)))
    {
        if (m_touchState == TOUCH_STATE_PRESSED)
        {
            m_touchState = TOUCH_STATE_NOT_PRESSED;
            touch_setState(TouchState_Released, m_pointPressed);
        }
    }
    else
    {
    	m_adcValues.x = xADValue;
    	m_adcValues.y = yADValue;
    	m_adcValues.z = zValue;

        touch_dr_calculatePointPressed(xADValue, yADValue);

        if (m_touchState == TOUCH_STATE_NOT_PRESSED)
        {
            m_touchState = TOUCH_STATE_PRESSED;
        }

        m_pointPressed.z = zValue;
        touch_setState(TouchState_Pressed, m_pointPressed);
    }
}

void touch_dr_resetCalibration(void)
{
	m_calibrationValues.gainX = 1.0f;
	m_calibrationValues.gainY = 1.0f;
	m_calibrationValues.offsetX = 0.0f;
	m_calibrationValues.offsetY = 0.0f;
}

void touch_dr_setCalibrationValues(const TouchCalibrationValues_s *p_values)
{
	m_calibrationValues = *p_values;
}

TouchCalibrationValues_s touch_dr_getCalibrationValues(void)
{
	return m_calibrationValues;
}

TouchADCValues_s touch_dr_getAdcValues(void)
{
	return m_adcValues;
}

static void touch_dr_calculatePointPressed(const uint32_t xADValue, const uint32_t yADValue)
{
    int32_t x = -1;
    int32_t y = -1;

    // Touch is default in portrait mode
    //
    const DisplaySize_s display = display_getDefaultSizePixels();
    const int32_t x_raw = (display.width - 1) * xADValue / 4095;
    const int32_t y_raw = (display.height - 1) * yADValue / 4095;

    touch_dr_rotatePoint(&x, &y, x_raw, y_raw);

    x = (int32_t)((float_t)x * m_calibrationValues.gainX + m_calibrationValues.offsetX);
    y = (int32_t)((float_t)y * m_calibrationValues.gainY + m_calibrationValues.offsetY);

    touch_dr_validatePoint(&x, &y);

    m_pointPressed.x = (uint32_t)x;
    m_pointPressed.y = (uint32_t)y;
}

static void touch_dr_rotatePoint(int32_t *p_x, int32_t *p_y, const int32_t x_raw, const int32_t y_raw)
{
	const DisplaySize_s display = display_getDefaultSizePixels();
	const DisplayOrientation_e orientation = display_getOrientation();

	if (Landscape == orientation)
	{
		*p_x = display.width - 1 - y_raw;
		*p_y = display.height - 1 - x_raw;
	}
	else if (LandscapeFlip)
	{
        *p_y = x_raw;
        *p_x = display.height - 1 - y_raw;
	}
	else if (PortraitFlip)
	{
		*p_x = display.width - 1 - x_raw;
		*p_y = display.height - 1 - y_raw;
	}
	else
	{
	}
}

static void touch_dr_validatePoint(int32_t *p_x, int32_t *p_y)
{
	const DisplaySize_s display = display_getSizePixels();

	if (*p_x < 0)
	{
		*p_x = 0;
	}

	if (*p_y < 0)
	{
		*p_y = 0;
	}

	if (*p_x >= display.width)
	{
		*p_x = display.width - 1;
	}

	if (*p_y >= display.height)
	{
		*p_y = display.height - 1;
	}
}

/*******************************************************************************
function:
        2 times to read the touch screen IC, and the two can not exceed the deviation,
        ERR_RANGE, meet the conditions, then that the correct reading, otherwise the reading error.
parameter:
    Channel_Cmd :   pYCh_Adc = 0x90 :Read channel Y +
                    pXCh_Adc = 0xd0 :Read channel x +
*******************************************************************************/
static bool touch_dr_readTwiceADC(uint32_t *p_out_xADC, uint32_t *p_out_yADC, uint32_t *p_out_zValue)
{
    uint32_t XCh_Adc1;
    uint32_t YCh_Adc1;
    uint32_t XCh_Adc2;
    uint32_t YCh_Adc2;
    uint32_t zADC1;
    uint32_t zADC2;

    touch_dr_readADC_XYZ(&XCh_Adc1, &YCh_Adc1, &zADC1);
    touch_dr_readADC_XYZ(&XCh_Adc2, &YCh_Adc2, &zADC2);

    *p_out_zValue = (zADC1 + zADC2) / 2;

    //The ADC error used twice is greater than ERR_RANGE to take the average
    //
    if (((XCh_Adc2 <= XCh_Adc1 && XCh_Adc1 < (XCh_Adc2 + ERR_RANGE)) ||
         (XCh_Adc1 <= XCh_Adc2 && XCh_Adc2 < (XCh_Adc1 + ERR_RANGE)))
        && ((YCh_Adc2 <= YCh_Adc1 && YCh_Adc1 < (YCh_Adc2 + ERR_RANGE)) ||
            (YCh_Adc1 <= YCh_Adc2 && YCh_Adc2 < (YCh_Adc1 + ERR_RANGE))))
    {
        *p_out_xADC = (XCh_Adc1 + XCh_Adc2) / 2;
        *p_out_yADC = (YCh_Adc1 + YCh_Adc2) / 2;

        return true;
    }

    return false;
}

static uint32_t touch_dr_readADC(uint8_t cmd)
{
    uint32_t data = 0;

    touch_dr_initSPI(SPI_BAUDRATEPRESCALER_16);
    touch_dr_cs_select();

    HAL_SPI_Transmit(&hspi1, &cmd, 1, TOUCHPAD_SPI_TIMEOUT_MS);
    delay_us(200);

    uint8_t data1 = 0;
    HAL_SPI_Receive(&hspi1, &data1, 1, TOUCHPAD_SPI_TIMEOUT_MS);

    uint8_t data2 = 0;
    HAL_SPI_Receive(&hspi1, &data2, 1, TOUCHPAD_SPI_TIMEOUT_MS);

    data = data1;
    data <<= 8;
    data |= data2;
    data >>= 3;

    touch_dr_cs_deSelect();
    touch_dr_initSPI(SPI_BAUDRATEPRESCALER_4);

    return data;
}

static void touch_dr_initSPI(const uint32_t baudRatePrescaler)
{
      hspi1.Instance = SPI1;
      hspi1.Init.Mode = SPI_MODE_MASTER;
      hspi1.Init.Direction = SPI_DIRECTION_2LINES;
      hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
      hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
      hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
      hspi1.Init.NSS = SPI_NSS_SOFT;
      hspi1.Init.BaudRatePrescaler = baudRatePrescaler;
      hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
      hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
      hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
      hspi1.Init.CRCPolynomial = 7;
      hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
      hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;

      if (HAL_SPI_Init(&hspi1) != HAL_OK)
      {
          Error_Handler();
      }
}

/*******************************************************************************
  function:
        Read X channel and Y channel AD value
  parameter:
    Channel_Cmd :   0x90 :Read channel Y +
                    0xd0 :Read channel x +
*******************************************************************************/
static void touch_dr_readADC_XYZ(uint32_t *p_out_xADC, uint32_t *p_out_yADC, uint32_t *p_out_zPressValue)
{
    *p_out_xADC = touch_dr_readADCAverage(CMD_X);

    const uint32_t yADCAverage = touch_dr_readADCAverage(CMD_Y);
    if (yADCAverage == 4095)
    {
        *p_out_yADC = 0;
    }
    else
    {
        *p_out_yADC = yADCAverage;
    }

    const uint32_t z1 = touch_dr_readADCAverage(CMD_Z1);
    const uint32_t z2 = touch_dr_readADCAverage(CMD_Z2);

    if (z1 != 0)
    {
        *p_out_zPressValue = (uint32_t)(*p_out_xADC / 40.960) * (((z2 * 1.0) / (z1 * 1.0)) - 1);
    }
    else
    {
        *p_out_zPressValue = TOUCH_Z_MAX_VALUE;
    }
}

/*******************************************************************************
  function:
        Read the 5th channel value and exclude the maximum and minimum returns the average
  parameter:
    Channel_Cmd :   0x90 :Read channel Y +
                    0xd0 :Read channel x +
*******************************************************************************/
static uint32_t touch_dr_readADCAverage(const uint8_t channelCmd)
{
    uint32_t readBuffer[NUMBER_OF_ADC_READINGS];
    uint32_t readSum = 0;
    uint32_t readTemp = 0;

    //Read and save multiple samples
    for (int32_t i = 0; i < NUMBER_OF_ADC_READINGS; i++)
    {
        readBuffer[i] = touch_dr_readADC(channelCmd);
        delay_us(200);
    }

    //Sort from small to large
    for (int32_t i = 0; i < NUMBER_OF_ADC_READINGS  -  1; i ++)
    {
        for (int32_t j = i + 1; j < NUMBER_OF_ADC_READINGS; j ++)
        {
            if (readBuffer[i] > readBuffer[j])
            {
                readTemp = readBuffer[i];
                readBuffer[i] = readBuffer[j];
                readBuffer[j] = readTemp;
            }
        }
    }

    //Exclude the largest and the smallest
    for (uint32_t i = LOST_NUM; i < NUMBER_OF_ADC_READINGS - LOST_NUM; i ++)
    {
        readSum += readBuffer[i];
    }

    //Averaging
    readTemp = readSum / (NUMBER_OF_ADC_READINGS - 2 * LOST_NUM);

    return readTemp;
}

static void touch_dr_cs_select(void)
{
    HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_RESET);
}

static void touch_dr_cs_deSelect(void)
{
    HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_SET);
}
