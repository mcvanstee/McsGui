#include "display_driver.h"

#include "display_hal.h"

/* Extern declarations */

/* Constants */
#define DISPLAY_CMD_NOP 0x00u
#define DISPLAY_CMD_SOFTWARE_RESET 0x01u
#define DISPLAY_CMD_READ_ID 0x04u
#define DISPLAY_CMD_READ_STATUS 0x09u

#define DISPLAY_CMD_READ_POWER_MODE 0x0Au
#define DISPLAY_CMD_READ_MEMORY_ACCESS 0x0Bu
#define DISPLAY_CMD_READ_PIXEL_FORMAT 0x0Cu
#define DISPLAY_CMD_READ_IMAGE_FORMAT 0x0Du
#define DISPLAY_CMD_READ_SIGNAL_MODE 0x0Eu
#define DISPLAY_CMD_READ_DIAGNOSTICS 0x0Fu

#define DISPLAY_CMD_SLEEP_IN 0x10u
#define DISPLAY_CMD_SLEEP_OUT 0x11u
#define DISPLAY_CMD_PARTIAL_MODE_ON 0x12u
#define DISPLAY_CMD_PARTIAL_MODE_OFF 0x13u

#define DISPLAY_CMD_INVERSION_MODE_OFF 0x20u
#define DISPLAY_CMD_INVERSION_MODE_ON 0x21u
#define DISPLAY_CMD_GAMMA_CURVE_SELECT 0x26u
#define DISPLAY_CMD_DISPLAY_OFF 0x28u
#define DISPLAY_CMD_DISPLAY_ON 0x29u

#define DISPLAY_CMD_SET_COLUMN_ADDRESS 0x2Au
#define DISPLAY_CMD_SET_ROW_ADDRESS 0x2Bu
#define DISPLAY_CMD_MEMORY_WRITE_START 0x2Cu
#define DISPLAY_CMD_MEMORY_READ_START 0x2Eu

#define DISPLAY_CMD_PARTIAL_ADDRESS_SET 0x30u
#define DISPLAY_CMD_VERTICAL_SCROLLING_SET 0x33u
#define DISPLAY_CMD_TEARING_LINE_OFF 0x34u
#define DISPLAY_CMD_TEARING_LINE_ON 0x35u
#define DISPLAY_CMD_MEMORY_ACCESS_CONTROL 0x36u
#define DISPLAY_CMD_VERTICAL_SCROLL_ADDRESS_SET 0x37u
#define DISPLAY_CMD_IDLE_MODE_ON 0x39u
#define DISPLAY_IDLE_MODE_OFF 0x38u

#define DISPLAY_CMD_PIXEL_FORMAT_SET 0x3Au
#define DISPLAY_CMD_FRMCTR1 0xB1u    /* Frame Rate Control (In Normal Mode/Full Colors) */
#define DISPLAY_CMD_FRMCTR2 0xB2u    /* Frame Rate Control (In Idle Mode/8 colors) */
#define DISPLAY_CMD_FRMCTR3 0xB3u    /* Frame Rate control (In Partial Mode/Full Colors) */
#define DISPLAY_CMD_INVCTR 0xB4u     /* Display Inversion Control */
#define DISPLAY_CMD_DFUNCTR 0xB6u    /* Display Function Control */

#define DISPLAY_CMD_PWCTR1 0xC0u     /* Power Control 1 */
#define DISPLAY_CMD_PWCTR2 0xC1u     /* Power Control 2 */
#define DISPLAY_CMD_PWCTR3 0xC2u     /* Power Control 3 */
#define DISPLAY_CMD_PWCTR4 0xC3u     /* Power Control 4 */
#define DISPLAY_CMD_PWCTR5 0xC4u     /* Power Control 5 */
#define DISPLAY_CMD_VMCTR1 0xC5u     /* VCOM Control 1 */
#define DISPLAY_CMD_VMCTR2 0xC7u     /* VCOM Control 2 */

#define DISPLAY_CMD_RDID1 0xDAu      /* Read ID 1 */
#define DISPLAY_CMD_RDID2 0xDBu      /* Read ID 2 */
#define DISPLAY_CMD_RDID3 0xDCu      /* Read ID 3 */
#define DISPLAY_CMD_RDID4 0xDDu      /* Read ID 4 */

#define DISPLAY_CMD_GMCTRP1 0xE0u    /* Positive Gamma Correction */
#define DISPLAY_CMD_GMCTRN1 0xE1u    /* Negative Gamma Correction */
#define DISPLAY_CMD_PWCTR6 0xFCu
#define DISPLAY_CMD_DELAY 0xFFu

#define MADCTL_MY 0x80u         /* Bottom to top */
#define MADCTL_MX 0x40u         /* Right to left */
#define MADCTL_MV 0x20u         /* Reverse Mode */
#define MADCTL_ML 0x10u         /* LCD refresh Bottom to top */
#define MADCTL_RGB 0x00u        /* Red-Green-Blue pixel order */
#define MADCTL_BGR 0x08u        /* Blue-Green-Red pixel order */
#define MADCTL_MH 0x04u         /* LCD refresh right to left */


/* Private function declarations */
static bool display_dr_setAddressWindow(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);
static void display_dr_setOrientation(const DisplayOrientation_e orientation);
static void display_dr_invertDisplay(const bool invert);
static void display_dr_setSize(DisplayDriver_s *p_driver);

static void display_dr_hardwareReset(void);
static void display_dr_sendCommandData(const uint8_t command, const uint8_t *p_data, const uint8_t dataLength);
static void display_dr_sendCommand(const uint8_t command);
static inline bool display_dr_checkAddressWindow(const uint16_t x, const uint16_t x1, const uint16_t y, const uint16_t y1);


/* Global variables */
static DisplayDriver_s *m_p_display_driver;

static const uint8_t displayInitCMDSequence[] =
{
	0xb0, 1, 0x0,
	DISPLAY_CMD_SLEEP_OUT, 0,
	DISPLAY_CMD_DISPLAY_ON, 0,
	0x3A, 1, 0x55,
	0x36, 1, 0x28,
	0xC2, 1, 0x44,
	0xC5, 4, 0x00, 0x00, 0x00, 0x00,
	0xE0, 15, 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98, 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00,
	0xE1, 15, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
	0xE2, 15, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
	0x36, 1, 0x28,
	DISPLAY_CMD_SLEEP_OUT, 0,
	DISPLAY_CMD_DISPLAY_ON, 0,
	DISPLAY_CMD_DELAY, 1, 250,
    0x00                                    /* End of list */
};


bool ILI9486_init(DisplayDriver_s *p_driver)
{
	m_p_display_driver = p_driver;
	p_driver->setAddressWindow = display_dr_setAddressWindow;
	p_driver->setOrientation = display_dr_setOrientation;
	p_driver->invertDisplay = display_dr_invertDisplay;

	p_driver->orientation = Portrait;
	p_driver->displaySize.width = p_driver->defaultWidth;
	p_driver->displaySize.height = p_driver->defaultHeight;

	display_dr_hardwareReset();
	display_hal_sendCommand(0);

    uint8_t command;
    uint32_t index = 0;

    // Send the power-on command sequence.
    //
    while ((command = displayInitCMDSequence[index++]) > 0)
    {
        const uint32_t numberOfArguments = displayInitCMDSequence[index];
        index++;

        if (command == DISPLAY_CMD_DELAY)
        {
            const uint32_t delay_msec = displayInitCMDSequence[index];
            display_hal_delay(delay_msec);
        }
        else if (numberOfArguments == 0u)
        {
        	display_dr_sendCommand(command);
        }
        else
        {
            display_dr_sendCommandData(
                    command, &displayInitCMDSequence[index], (uint8_t)numberOfArguments);
        }

        index += numberOfArguments;
    }

    return true;
}

static bool display_dr_setAddressWindow(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height)
{
    const uint16_t x1 = (x + width) - 1u;
    const uint16_t y1 = (y + height) - 1u;

    bool isInAddressWindow = display_dr_checkAddressWindow(x, x1, y, y1);
    if (!isInAddressWindow)
    {
        return false;
    }

    display_hal_sendCommand(DISPLAY_CMD_SET_COLUMN_ADDRESS);
    display_hal_sendU8Data(x >> 8);
    display_hal_sendU8Data(x & 0xFF);
    display_hal_sendU8Data(x1 >> 8);
    display_hal_sendU8Data(x1 & 0xFF);

    display_hal_sendCommand(DISPLAY_CMD_SET_ROW_ADDRESS);
    display_hal_sendU8Data(y >> 8);
    display_hal_sendU8Data(y & 0xFF);
    display_hal_sendU8Data(y1 >> 8);
    display_hal_sendU8Data(y1 & 0xFF);

    display_hal_sendCommand(DISPLAY_CMD_MEMORY_WRITE_START);

    return isInAddressWindow;
}

static void display_dr_setOrientation(const DisplayOrientation_e orientation)
{
    uint8_t memoryAccessRegData = 0;
    uint8_t displayFuntionRegData = 0;

    switch (orientation)
    {
        case Landscape:
			memoryAccessRegData = 0x28;
			displayFuntionRegData = 0x62;
            break;
        case Portrait:
			memoryAccessRegData = 0x08;
			displayFuntionRegData = 0x22;
            break;
        case LandscapeFlip:
			memoryAccessRegData = 0x28;
			displayFuntionRegData = 0x02;
            break;
        case PortraitFlip:
			memoryAccessRegData = 0x08;
			displayFuntionRegData = 0x42;
            break;
        default:
            break;
    }

    m_p_display_driver->orientation = orientation;
    display_dr_setSize(m_p_display_driver);

    uint8_t functionDataBuff[2] = {0};
    functionDataBuff[0] = 0x00;
    functionDataBuff[1] = displayFuntionRegData;

	display_dr_sendCommandData(DISPLAY_CMD_DFUNCTR, functionDataBuff, 2u);
    display_dr_sendCommandData(DISPLAY_CMD_MEMORY_ACCESS_CONTROL, &memoryAccessRegData, 1u);
}

static void display_dr_invertDisplay(const bool invert)
{
    const uint8_t command = invert ? DISPLAY_CMD_INVERSION_MODE_ON : DISPLAY_CMD_INVERSION_MODE_OFF;
    display_hal_sendCommand(command);
}

static void display_dr_setSize(DisplayDriver_s *p_driver)
{
	if ((Portrait == p_driver->orientation) ||
			(PortraitFlip == p_driver->orientation))
	{
		p_driver->displaySize.width = p_driver->defaultWidth;
		p_driver->displaySize.height = p_driver->defaultHeight;
	}
	else
	{
		p_driver->displaySize.width = p_driver->defaultHeight;
		p_driver->displaySize.height = p_driver->defaultWidth;
	}
}

static void display_dr_sendCommandData(const uint8_t command, const uint8_t *p_data, const uint8_t dataLength)
{
	display_hal_sendCommand(command);

    for (uint32_t i = 0; i < dataLength; i++)
    {
    	display_hal_sendU8Data(p_data[i]);
    }
}

static void display_dr_sendCommand(const uint8_t command)
{
	display_hal_sendCommand(command);
}

static void display_dr_hardwareReset(void)
{
	display_hal_resetHigh();
	display_hal_delay(50);
	display_hal_resetLow();
	display_hal_delay(50);
	display_hal_resetHigh();
	display_hal_delay(50);
}

static inline bool display_dr_checkAddressWindow(const uint16_t x, const uint16_t x1, const uint16_t y, const uint16_t y1)
{
    if (x > x1)
    {
        return false;
    }

	if (x1 >= m_p_display_driver->displaySize.width)
	{
		return false;
	}

    if (y > y1)
    {
        return false;
    }

    if (y1 >= m_p_display_driver->displaySize.height)
    {
        return false;
    }

    return true;
}


/*** end of file ***/
