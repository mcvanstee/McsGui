#include "display_driver.h"

#include "display_hal.h"

/* Extern declarations */

/* Constants */
// System Function Command Table 1
//
#define DISPLAY_CMD_NOP                          0x00u
#define DISPLAY_CMD_SOFTWARE_RESET               0x01u
#define DISPLAY_CMD_READ_ID                      0x04u
#define DISPLAY_CMD_READ_STATUS                  0x09u
#define DISPLAY_CMD_READ_POWER                   0x0Au
#define DISPLAY_CMD_READ_MEMORY_ACCESS           0x0Bu
#define DISPLAY_CMD_READ_PIXEL_FORMAT            0x0Cu
#define DISPLAY_CMD_READ_IMAGE_MODE              0x0Du
#define DISPLAY_CMD_READ_SIGNAL_MODE             0x0Eu
#define DISPLAY_CMD_READ_DIAGNOSTICS             0x0Fu

#define DISPLAY_CMD_SLEEP_IN                     0x10u
#define DISPLAY_CMD_SLEEP_OUT                    0x11u
#define DISPLAY_CMD_PARTIAL_MODE_ON              0x12u
#define DISPLAY_CMD_PARTIAL_MODE_OFF             0x13u

#define DISPLAY_CMD_INVERSION_MODE_OFF           0x20u
#define DISPLAY_CMD_INVERSION_MODE_ON            0x21u
#define DISPLAY_CMD_GAMMA_CURVE_SELECT           0x26u
#define DISPLAY_CMD_DISPLAY_OFF                  0x28u
#define DISPLAY_CMD_DISPLAY_ON                   0x29u

#define DISPLAY_CMD_SET_COLUMN_ADDRESS           0x2Au
#define DISPLAY_CMD_SET_ROW_ADDRESS              0x2Bu
#define DISPLAY_CMD_MEMORY_WRITE_START           0x2Cu
#define DISPLAY_CMD_MEMORY_READ_START            0x2Eu

#define DISPLAY_CMD_PARTIAL_ADDRESS_SET          0x30u
#define DISPLAY_CMD_VERTICAL_SCROLLING_SET       0x33u
#define DISPLAY_CMD_TEARING_LINE_OFF             0x34u
#define DISPLAY_CMD_TEARING_LINE_ON              0x35u
#define DISPLAY_CMD_MEMORY_ACCESS_CONTROL        0x36u
#define DISPLAY_CMD_VERTICAL_SCROLL_ADDRESS_SET  0x37u
#define DISPLAY_CMD_IDLE_MODE_ON                 0x39u
#define DISPLAY_CMD_IDLE_MODE_OFF                0x38u

#define DISPLAY_CMD_PIXEL_FORMAT_SET             0x3Au
#define DISPLAY_CMD_MEMORY_WRITE_CONTINUE        0x3Cu
#define DISPLAY_CMD_MEMORY_READ_CONTINUE         0x3Eu

#define DISPLAY_CMD_TEAR_SCANLINE_SET            0x44u
#define DISPLAY_CMD_TEAR_SCANLINE_GET            0x45u

#define DISPLAY_CMD_BRIGHTNESS_SET               0x51u
#define DISPLAY_CMD_BRIGHTNESS_GET               0x52u
#define DISPLAY_CMD_CONTROL_WRITE                0x53u
#define DISPLAY_CMD_CONTROL_READ                 0x54u
#define DISPLAY_CMD_CABC_WRITE                   0x55u
#define DISPLAY_CMD_CABC_READ                    0x56u
#define DISPLAY_CMD_CABC_MIN_BRIGHTNESS_WRITE    0x5Eu
#define DISPLAY_CMD_CABC_MIN_BRIGHTNESS_READ     0x5Fu
#define DISPLAY_CMD_CABC_READ_DIAGNOSTICS        0x68u
#define DISPLAY_CMD_READ_ID_1                    0xDAu
#define DISPLAY_CMD_READ_ID_2                    0xDBu
#define DISPLAY_CMD_READ_ID_3                    0xDCu

// System Function Command Table 2
//
#define DISPLAY_CMD_RAM_CTRL                     0xB0u
#define DISPLAY_CMD_RGB_CTRL                     0xB1u
#define DISPLAY_CMD_PORCH_CTRL                   0xB2u
#define DISPLAY_CMD_FRAME_RATE_CTRL_1            0xB3u
#define DISPLAY_CMD_PARTIAL_MODE_CTRL            0xB5u
#define DISPLAY_CMD_GATE_CTRL                    0xB7u
#define DISPLAY_CMD_GATE_ON_TIMING_ADJ           0xB8u
#define DISPLAY_CMD_DIGITAL_GAMMA_ENABLE         0xBAu
#define DISPLAY_CMD_VCOMS_SETTINGS               0xBBu
#define DISPLAY_CMD_LCM_CTRL                     0xC0u
#define DISPLAY_CMD_ID_SETTING                   0xC1u
#define DISPLAY_CMD_VDV_VRH_CMD_ENABLE           0xC2u
#define DISPLAY_CMD_VRH_SET                      0xC3u
#define DISPLAY_CMD_VDV_SETTING                  0xC4u
#define DISPLAY_CMD_VCOMS_OFFSET_SET             0xC5u
#define DISPLAY_CMD_FRAME_RATE_CTRL_2            0xC6u
#define DISPLAY_CMD_CABC_CTRL                    0xC7u
#define DISPLAY_CMD_REG_VAL_SEL_1                0xC8u
#define DISPLAY_CMD_REG_VAL_SEL_2                0xCAu
#define DISPLAY_CMD_PWM_FREQ_SEL                 0xCCu
#define DISPLAY_CMD_PWR_CTRL_1                   0xD0u
#define DISPLAY_CMD_VAP_VAN_ENABLE               0xD2u
#define DISPLAY_CMD_COMMAND_2_ENABLE_1           0xDFu
#define DISPLAY_CMD_COMMAND_2_ENABLE_2           0x5Au
#define DISPLAY_CMD_COMMAND_2_ENABLE_3           0x69u
#define DISPLAY_CMD_COMMAND_2_ENABLE_4           0x02u
#define DISPLAY_CMD_POSITIVE_VOLTAGE_GAMMA       0xE0u
#define DISPLAY_CMD_NEGATIVE_VOLTAGE_GAMMA       0xE1u
#define DISPLAY_CMD_DIGITAL_GAMMA_RED_LUT        0xE2u
#define DISPLAY_CMD_DIGITAL_GAMMA_BLUE_LUT       0xE3u
#define DISPLAY_CMD_GATE_CTRL2                   0xE4u
#define DISPLAY_CMD_SPI2_ENABLE                  0xE7u
#define DISPLAY_CMD_POWER_CTRL_2                 0xE8u
#define DISPLAY_CMD_EQUALIZE_TIME_CTRL           0xE9u
#define DISPLAY_CMD_PROGRAM_CONTROL              0xECu
#define DISPLAY_CMD_PROGRAM_MODE_ENABLE          0xFAu
#define DISPLAY_CMD_NVM_SETTING                  0xFCu
#define DISPLAY_CMD_PROGRAM_ACTION               0xFEu
#define DISPLAY_CMD_DELAY                        0xFFu

#define MEMORY_ACCESS_ROW_ORDER_BOTTOM_TO_TOP    0x80u
#define MEMORY_ACCESS_COLUMN_ORDER_RIGHT_TO_LEFT 0x40u
#define MEMORY_ACCESS_ROW_COLUMN_EXCHANGED       0x20u
#define MEMORY_ACCESS_REFRESH_BOTTOM_TO_TOP      0x10u
#define MEMORY_ACCESS_PIXEL_ORDER_BGR            0x08u
#define MEMORY_ACCESS_PIXEL_ORDER_RGB            0x00u
#define MEMORY_ACCESS_REFRESH_RIGHT_TO_LEFT      0x04u

typedef enum
{
    CONTROL_INTERFACE_12BPP = 0x03U,
    CONTROL_INTERFACE_16BPP = 0x05U,
    CONTROL_INTERFACE_18BPP = 0x06U,
    CONTROL_INTERFACE_24BPP = 0x07U
} Display_ControlInterfaceColorFormat_e;

typedef enum
{
    RGB_INTERFACE_65K = 0x50U,
    RGB_INTERFACE_262K = 0x60U
} Display_RGBInterfaceColorFormat_e;


/* Private function declarations */
static bool display_dr_setAddressWindow(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);
static void display_dr_setOrientation(const DisplayOrientation_e orientation);
static void display_dr_invertDisplay(const bool invert);
static void display_dr_setSize(DisplayDriver_s *p_driver);

static void display_dr_hardwareReset(void);
static inline bool display_dr_checkAddressWindow(const uint16_t x, const uint16_t x1, const uint16_t y, const uint16_t y1);


/* Global variables */
static DisplayDriver_s *m_p_display_driver;

static const uint8_t displayInitCMDSequence[] =
{
    DISPLAY_CMD_DISPLAY_OFF, 0,
    DISPLAY_CMD_SLEEP_OUT, 0,
    DISPLAY_CMD_DELAY, 1, 120,
    DISPLAY_CMD_MEMORY_ACCESS_CONTROL, 1, (MEMORY_ACCESS_PIXEL_ORDER_RGB),
    DISPLAY_CMD_PIXEL_FORMAT_SET, 1, ((uint8_t)RGB_INTERFACE_65K | (uint8_t)CONTROL_INTERFACE_16BPP),
    DISPLAY_CMD_RAM_CTRL, 2, 0x00, 0xE0,
    DISPLAY_CMD_PORCH_CTRL, 5, 0x0C, 0x0C, 0x00, 0x33, 0x33,
    DISPLAY_CMD_GATE_CTRL, 1, 0x35,
    DISPLAY_CMD_VCOMS_SETTINGS, 1, 0x2B,
    DISPLAY_CMD_LCM_CTRL, 1, 0x2C,
    DISPLAY_CMD_VDV_VRH_CMD_ENABLE, 2, 0x01, 0xFF,
    DISPLAY_CMD_VRH_SET, 1, 0x11,
    DISPLAY_CMD_VDV_SETTING, 1, 0x20,
    DISPLAY_CMD_FRAME_RATE_CTRL_2, 1, 0x0F, // 0x0F 60Hz, 0x1F 39Hz
    DISPLAY_CMD_PWR_CTRL_1, 2, 0xA4, 0xA1,
    DISPLAY_CMD_POSITIVE_VOLTAGE_GAMMA, 14,
    0xD0, 0x00, 0x05, 0x0E, 0x15, 0x0D, 0x37,
    0x43, 0x47, 0x09, 0x15, 0x12, 0x16, 0x19,
    DISPLAY_CMD_NEGATIVE_VOLTAGE_GAMMA, 14,
    0xD0, 0x00, 0x05, 0x0D, 0x0C, 0x06, 0x2D,
    0x44, 0x40, 0x0E, 0x1C, 0x18, 0x16, 0x19,
    DISPLAY_CMD_DELAY, 1, 10,
    DISPLAY_CMD_DISPLAY_ON, 0,
    DISPLAY_CMD_DELAY, 1, 150,
    0x00    /* End of list */
};


bool ST7789_init(DisplayDriver_s *p_driver)
{
    m_p_display_driver = p_driver;
    p_driver->setAddressWindow = display_dr_setAddressWindow;
    p_driver->setOrientation = display_dr_setOrientation;
    p_driver->invertDisplay = display_dr_invertDisplay;

    p_driver->orientation = Portrait;
    p_driver->displaySize.width = p_driver->defaultWidth;
    p_driver->displaySize.height = p_driver->defaultHeight;

    display_dr_hardwareReset();

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
            display_hal_sendCommand(command);
        }
        else
        {
            display_hal_sendCommandData(
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

    const bool isInAddressWindow = display_dr_checkAddressWindow(x, x1, y, y1);
    if (!isInAddressWindow)
    {
        return false;
    }

    uint8_t data_x[4] = {0};
    data_x[0] = x >> 8;
    data_x[1] = x & 0xFF;
    data_x[2] = x1 >> 8;
    data_x[3] = x1 & 0xFF;
    display_hal_sendCommandData(DISPLAY_CMD_SET_COLUMN_ADDRESS, data_x, 4u);

    uint8_t data_y[4] = {0};
    data_y[0] = y >> 8;
    data_y[1] = y & 0xFF;
    data_y[2] = y1 >> 8;
    data_y[3] = y1 & 0xFF;
    display_hal_sendCommandData(DISPLAY_CMD_SET_ROW_ADDRESS, data_y, 4u);

    display_hal_sendCommand(DISPLAY_CMD_MEMORY_WRITE_START);

    return isInAddressWindow;
}

static void display_dr_setOrientation(const DisplayOrientation_e orientation)
{
    uint8_t data = 0;
    bool orientationValid = true;

    switch (orientation)
    {
        case Portrait:
            data = MEMORY_ACCESS_PIXEL_ORDER_RGB;
            break;
        case Landscape:
            data = (MEMORY_ACCESS_ROW_COLUMN_EXCHANGED | MEMORY_ACCESS_COLUMN_ORDER_RIGHT_TO_LEFT | MEMORY_ACCESS_REFRESH_RIGHT_TO_LEFT);
            break;
        case PortraitFlip:
            data = (MEMORY_ACCESS_COLUMN_ORDER_RIGHT_TO_LEFT | MEMORY_ACCESS_ROW_ORDER_BOTTOM_TO_TOP | MEMORY_ACCESS_REFRESH_RIGHT_TO_LEFT | MEMORY_ACCESS_REFRESH_BOTTOM_TO_TOP);
            break;
        case LandscapeFlip:
            data = (MEMORY_ACCESS_ROW_COLUMN_EXCHANGED | MEMORY_ACCESS_ROW_ORDER_BOTTOM_TO_TOP | MEMORY_ACCESS_REFRESH_BOTTOM_TO_TOP);
            break;
        default:
            orientationValid = false;
            break;
    }

    if (orientationValid)
    {
        m_p_display_driver->orientation = orientation;
        display_dr_setSize(m_p_display_driver);
        display_hal_sendCommandData(DISPLAY_CMD_MEMORY_ACCESS_CONTROL, &data, 1u);
    }
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

static void display_dr_hardwareReset(void)
{
    display_hal_chipSelectLow();
    display_hal_dataMode();
    display_hal_resetLow();
    display_hal_delay(100);
    display_hal_resetHigh();
    display_hal_chipSelectHigh();
    display_hal_delay(120);
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










///**
// *
// * @par COPYRIGHT NOTICE:
// * Copyright (c) 2020, Marijn van Stee, all rights reserved.
// *
// */
//
//#include "display_driver.h"
//
//#include "stm32l4xx_hal.h"
//
///* Extern declarations */
//
///* Constants */
//// System Function Command Table 1
////
//#define DISPLAY_CMD_NOP                          0x00u
//#define DISPLAY_CMD_SOFTWARE_RESET               0x01u
//#define DISPLAY_CMD_READ_ID                      0x04u
//#define DISPLAY_CMD_READ_STATUS                  0x09u
//#define DISPLAY_CMD_READ_POWER                   0x0Au
//#define DISPLAY_CMD_READ_MEMORY_ACCESS           0x0Bu
//#define DISPLAY_CMD_READ_PIXEL_FORMAT            0x0Cu
//#define DISPLAY_CMD_READ_IMAGE_MODE              0x0Du
//#define DISPLAY_CMD_READ_SIGNAL_MODE             0x0Eu
//#define DISPLAY_CMD_READ_DIAGNOSTICS             0x0Fu
//
//#define DISPLAY_CMD_SLEEP_IN                     0x10u
//#define DISPLAY_CMD_SLEEP_OUT                    0x11u
//#define DISPLAY_CMD_PARTIAL_MODE_ON              0x12u
//#define DISPLAY_CMD_PARTIAL_MODE_OFF             0x13u
//
//#define DISPLAY_CMD_INVERSION_MODE_OFF           0x20u
//#define DISPLAY_CMD_INVERSION_MODE_ON            0x21u
//#define DISPLAY_CMD_GAMMA_CURVE_SELECT           0x26u
//#define DISPLAY_CMD_DISPLAY_OFF                  0x28u
//#define DISPLAY_CMD_DISPLAY_ON                   0x29u
//
//#define DISPLAY_CMD_SET_COLUMN_ADDRESS           0x2Au
//#define DISPLAY_CMD_SET_ROW_ADDRESS              0x2Bu
//#define DISPLAY_CMD_MEMORY_WRITE_START           0x2Cu
//#define DISPLAY_CMD_MEMORY_READ_START            0x2Eu
//
//#define DISPLAY_CMD_PARTIAL_ADDRESS_SET          0x30u
//#define DISPLAY_CMD_VERTICAL_SCROLLING_SET       0x33u
//#define DISPLAY_CMD_TEARING_LINE_OFF             0x34u
//#define DISPLAY_CMD_TEARING_LINE_ON              0x35u
//#define DISPLAY_CMD_MEMORY_ACCESS_CONTROL        0x36u
//#define DISPLAY_CMD_VERTICAL_SCROLL_ADDRESS_SET  0x37u
//#define DISPLAY_CMD_IDLE_MODE_ON                 0x39u
//#define DISPLAY_CMD_IDLE_MODE_OFF                0x38u
//
//#define DISPLAY_CMD_PIXEL_FORMAT_SET             0x3Au
//#define DISPLAY_CMD_MEMORY_WRITE_CONTINUE        0x3Cu
//#define DISPLAY_CMD_MEMORY_READ_CONTINUE         0x3Eu
//
//#define DISPLAY_CMD_TEAR_SCANLINE_SET            0x44u
//#define DISPLAY_CMD_TEAR_SCANLINE_GET            0x45u
//
//#define DISPLAY_CMD_BRIGHTNESS_SET               0x51u
//#define DISPLAY_CMD_BRIGHTNESS_GET               0x52u
//#define DISPLAY_CMD_CONTROL_WRITE                0x53u
//#define DISPLAY_CMD_CONTROL_READ                 0x54u
//#define DISPLAY_CMD_CABC_WRITE                   0x55u
//#define DISPLAY_CMD_CABC_READ                    0x56u
//#define DISPLAY_CMD_CABC_MIN_BRIGHTNESS_WRITE    0x5Eu
//#define DISPLAY_CMD_CABC_MIN_BRIGHTNESS_READ     0x5Fu
//#define DISPLAY_CMD_CABC_READ_DIAGNOSTICS        0x68u
//#define DISPLAY_CMD_READ_ID_1                    0xDAu
//#define DISPLAY_CMD_READ_ID_2                    0xDBu
//#define DISPLAY_CMD_READ_ID_3                    0xDCu
//
//// System Function Command Table 2
////
//#define DISPLAY_CMD_RAM_CTRL                     0xB0u
//#define DISPLAY_CMD_RGB_CTRL                     0xB1u
//#define DISPLAY_CMD_PORCH_CTRL                   0xB2u
//#define DISPLAY_CMD_FRAME_RATE_CTRL_1            0xB3u
//#define DISPLAY_CMD_PARTIAL_MODE_CTRL            0xB5u
//#define DISPLAY_CMD_GATE_CTRL                    0xB7u
//#define DISPLAY_CMD_GATE_ON_TIMING_ADJ           0xB8u
//#define DISPLAY_CMD_DIGITAL_GAMMA_ENABLE         0xBAu
//#define DISPLAY_CMD_VCOMS_SETTINGS               0xBBu
//#define DISPLAY_CMD_LCM_CTRL                     0xC0u
//#define DISPLAY_CMD_ID_SETTING                   0xC1u
//#define DISPLAY_CMD_VDV_VRH_CMD_ENABLE           0xC2u
//#define DISPLAY_CMD_VRH_SET                      0xC3u
//#define DISPLAY_CMD_VDV_SETTING                  0xC4u
//#define DISPLAY_CMD_VCOMS_OFFSET_SET             0xC5u
//#define DISPLAY_CMD_FRAME_RATE_CTRL_2            0xC6u
//#define DISPLAY_CMD_CABC_CTRL                    0xC7u
//#define DISPLAY_CMD_REG_VAL_SEL_1                0xC8u
//#define DISPLAY_CMD_REG_VAL_SEL_2                0xCAu
//#define DISPLAY_CMD_PWM_FREQ_SEL                 0xCCu
//#define DISPLAY_CMD_PWR_CTRL_1                   0xD0u
//#define DISPLAY_CMD_VAP_VAN_ENABLE               0xD2u
//#define DISPLAY_CMD_COMMAND_2_ENABLE_1           0xDFu
//#define DISPLAY_CMD_COMMAND_2_ENABLE_2           0x5Au
//#define DISPLAY_CMD_COMMAND_2_ENABLE_3           0x69u
//#define DISPLAY_CMD_COMMAND_2_ENABLE_4           0x02u
//#define DISPLAY_CMD_POSITIVE_VOLTAGE_GAMMA       0xE0u
//#define DISPLAY_CMD_NEGATIVE_VOLTAGE_GAMMA       0xE1u
//#define DISPLAY_CMD_DIGITAL_GAMMA_RED_LUT        0xE2u
//#define DISPLAY_CMD_DIGITAL_GAMMA_BLUE_LUT       0xE3u
//#define DISPLAY_CMD_GATE_CTRL2                   0xE4u
//#define DISPLAY_CMD_SPI2_ENABLE                  0xE7u
//#define DISPLAY_CMD_POWER_CTRL_2                 0xE8u
//#define DISPLAY_CMD_EQUALIZE_TIME_CTRL           0xE9u
//#define DISPLAY_CMD_PROGRAM_CONTROL              0xECu
//#define DISPLAY_CMD_PROGRAM_MODE_ENABLE          0xFAu
//#define DISPLAY_CMD_NVM_SETTING                  0xFCu
//#define DISPLAY_CMD_PROGRAM_ACTION               0xFEu
//#define DISPLAY_CMD_DELAY                        0xFFu
//
//#define MEMORY_ACCESS_ROW_ORDER_BOTTOM_TO_TOP    0x80u
//#define MEMORY_ACCESS_COLUMN_ORDER_RIGHT_TO_LEFT 0x40u
//#define MEMORY_ACCESS_ROW_COLUMN_EXCHANGED       0x20u
//#define MEMORY_ACCESS_REFRESH_BOTTOM_TO_TOP      0x10u
//#define MEMORY_ACCESS_PIXEL_ORDER_BGR            0x08u
//#define MEMORY_ACCESS_PIXEL_ORDER_RGB            0x00u
//#define MEMORY_ACCESS_REFRESH_RIGHT_TO_LEFT      0x04u
//
//typedef enum
//{
//    CONTROL_INTERFACE_12BPP = 0x03U,
//    CONTROL_INTERFACE_16BPP = 0x05U,
//    CONTROL_INTERFACE_18BPP = 0x06U,
//    CONTROL_INTERFACE_24BPP = 0x07U
//} Display_ControlInterfaceColorFormat_e;
//
//typedef enum
//{
//    RGB_INTERFACE_65K = 0x50U,
//    RGB_INTERFACE_262K = 0x60U
//} Display_RGBInterfaceColorFormat_e;
//
//
///* Global variables */
//static DisplayOrientation_e m_display_orientation;
//static uint16_t m_display_width;
//static uint16_t m_display_height;
//
//static const uint8_t displayInitCMDSequence[] =
//{
//    DISPLAY_CMD_DISPLAY_OFF, 0,
//    DISPLAY_CMD_SLEEP_OUT, 0,
//    DISPLAY_CMD_DELAY, 1, 120,
//    DISPLAY_CMD_MEMORY_ACCESS_CONTROL, 1, (MEMORY_ACCESS_PIXEL_ORDER_RGB),
//    DISPLAY_CMD_PIXEL_FORMAT_SET, 1, ((uint8_t)RGB_INTERFACE_65K | (uint8_t)CONTROL_INTERFACE_16BPP),
//    DISPLAY_CMD_RAM_CTRL, 2, 0x00, 0xE0,
//    DISPLAY_CMD_PORCH_CTRL, 5, 0x0C, 0x0C, 0x00, 0x33, 0x33,
//    DISPLAY_CMD_GATE_CTRL, 1, 0x35,
//    DISPLAY_CMD_VCOMS_SETTINGS, 1, 0x2B,
//    DISPLAY_CMD_LCM_CTRL, 1, 0x2C,
//    DISPLAY_CMD_VDV_VRH_CMD_ENABLE, 2, 0x01, 0xFF,
//    DISPLAY_CMD_VRH_SET, 1, 0x11,
//    DISPLAY_CMD_VDV_SETTING, 1, 0x20,
//    DISPLAY_CMD_FRAME_RATE_CTRL_2, 1, 0x0F, // 0x0F 60Hz, 0x1F 39Hz
//    DISPLAY_CMD_PWR_CTRL_1, 2, 0xA4, 0xA1,
//    DISPLAY_CMD_POSITIVE_VOLTAGE_GAMMA, 14,
//    0xD0, 0x00, 0x05, 0x0E, 0x15, 0x0D, 0x37,
//    0x43, 0x47, 0x09, 0x15, 0x12, 0x16, 0x19,
//    DISPLAY_CMD_NEGATIVE_VOLTAGE_GAMMA, 14,
//    0xD0, 0x00, 0x05, 0x0D, 0x0C, 0x06, 0x2D,
//    0x44, 0x40, 0x0E, 0x1C, 0x18, 0x16, 0x19,
//    DISPLAY_CMD_DELAY, 1, 10,
//    DISPLAY_CMD_DISPLAY_ON, 0,
//    DISPLAY_CMD_DELAY, 1, 150,
//    0x00    /* End of list */
//};
//
//
///* Private function declarations */
//static inline bool display_dr_checkAddressWindow(const uint16_t x, const uint16_t x1, const uint16_t y, const uint16_t y1);
//
//bool display_driver_init(void)
//{
//	display_hal_hardReset();
//
//    uint8_t command;
//    uint32_t index = 0;
//
//    // Send the power-on command sequence.
//    //
//    while ((command = displayInitCMDSequence[index++]) > 0)
//    {
//        const uint32_t numberOfArguments = displayInitCMDSequence[index];
//        index++;
//
//        if (command == DISPLAY_CMD_DELAY)
//        {
//            const uint32_t delay_msec = displayInitCMDSequence[index];
//            HAL_Delay(delay_msec);
//        }
//        else if (numberOfArguments == 0u)
//        {
//            display_hal_sendCommand(command);
//        }
//        else
//        {
//            display_hal_sendCommandData(
//                    command, &displayInitCMDSequence[index], (uint8_t)numberOfArguments);
//        }
//
//        index += numberOfArguments;
//    }
//
//    m_display_width = DISPLAY_DEFAULT_WIDTH_PIXELS;
//    m_display_height = DISPLAY_DEFAULT_HEIGHT_PIXELS;
//    m_display_orientation = Portrait;
//
//    return true;
//}
//
//bool display_dr_setAddressWindow(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height)
//{
//    const uint16_t x1 = (x + width) - 1u;
//    const uint16_t y1 = (y + height) - 1u;
//
//    const bool isInAddressWindow = display_dr_checkAddressWindow(x, x1, y, y1);
//    if (!isInAddressWindow)
//    {
//        return false;
//    }
//
//    uint8_t data_x[4] = {0};
//    data_x[0] = x >> 8;
//    data_x[1] = x & 0xFF;
//    data_x[2] = x1 >> 8;
//    data_x[3] = x1 & 0xFF;
//    display_hal_sendCommandData(DISPLAY_CMD_SET_COLUMN_ADDRESS, data_x, 4u);
//
//    uint8_t data_y[4] = {0};
//    data_y[0] = y >> 8;
//    data_y[1] = y & 0xFF;
//    data_y[2] = y1 >> 8;
//    data_y[3] = y1 & 0xFF;
//    display_hal_sendCommandData(DISPLAY_CMD_SET_ROW_ADDRESS, data_y, 4u);
//
//    display_hal_sendCommand(DISPLAY_CMD_MEMORY_WRITE_START);
//
//    return isInAddressWindow;
//}
//
//void display_dr_setOrientation(const DisplayOrientation_e orientation)
//{
//    uint8_t data = 0;
//    bool orientationValid = true;
//
//    switch (orientation)
//    {
//        case Portrait:
//            data = MEMORY_ACCESS_PIXEL_ORDER_RGB;
//            m_display_width = DISPLAY_DEFAULT_WIDTH_PIXELS;
//            m_display_height = DISPLAY_DEFAULT_HEIGHT_PIXELS;
//            break;
//        case Landscape:
//            data = (MEMORY_ACCESS_ROW_COLUMN_EXCHANGED | MEMORY_ACCESS_COLUMN_ORDER_RIGHT_TO_LEFT | MEMORY_ACCESS_REFRESH_RIGHT_TO_LEFT);
//            m_display_width = DISPLAY_DEFAULT_HEIGHT_PIXELS;
//            m_display_height = DISPLAY_DEFAULT_WIDTH_PIXELS;
//            break;
//        case PortraitFlip:
//            data = (MEMORY_ACCESS_COLUMN_ORDER_RIGHT_TO_LEFT | MEMORY_ACCESS_ROW_ORDER_BOTTOM_TO_TOP | MEMORY_ACCESS_REFRESH_RIGHT_TO_LEFT | MEMORY_ACCESS_REFRESH_BOTTOM_TO_TOP);
//            m_display_width = DISPLAY_DEFAULT_WIDTH_PIXELS;
//            m_display_height = DISPLAY_DEFAULT_HEIGHT_PIXELS;
//            break;
//        case LandscapeFlip:
//            data = (MEMORY_ACCESS_ROW_COLUMN_EXCHANGED | MEMORY_ACCESS_ROW_ORDER_BOTTOM_TO_TOP | MEMORY_ACCESS_REFRESH_BOTTOM_TO_TOP);
//            m_display_width = DISPLAY_DEFAULT_HEIGHT_PIXELS;
//            m_display_height = DISPLAY_DEFAULT_WIDTH_PIXELS;
//            break;
//        default:
//            orientationValid = false;
//            break;
//    }
//
//    if (orientationValid)
//    {
//        m_display_orientation = orientation;
//        display_hal_sendCommandData(DISPLAY_CMD_MEMORY_ACCESS_CONTROL, &data, 1u);
//    }
//}
//
//void display_dr_invertDisplay(const bool invert)
//{
//	const uint8_t command = invert ? DISPLAY_CMD_INVERSION_MODE_ON : DISPLAY_CMD_INVERSION_MODE_OFF;
//	display_hal_sendCommand(command);
//}
//
//void display_dr_tearingLineOn(void)
//{
//    uint8_t data = 0; // VSYNC
//    display_hal_sendCommandData(DISPLAY_CMD_TEARING_LINE_ON, &data, 1u);
//}
//
//void display_dr_sleepModeOn(void)
//{
//    display_hal_sendCommand(DISPLAY_CMD_SLEEP_IN);
//}
//
//void display_dr_sleepModeOff(void)
//{
//    display_hal_sendCommand(DISPLAY_CMD_SLEEP_OUT);
//}
//
//uint16_t display_dr_getWidthPixels(void)
//{
//    return m_display_width;
//}
//
//uint16_t display_dr_getHeightPixels(void)
//{
//    return m_display_height;
//}
//
//DisplayOrientation_e display_dr_getOrientation(void)
//{
//    return m_display_orientation;
//}
//
//DisplayIdRegister_s display_dr_getIdReg(void)
//{
//    DisplayIdRegister_s idReg = { 0 };
//
//    display_hal_sendCommand(DISPLAY_CMD_READ_ID);
//    display_hal_readData((uint8_t *)&idReg, sizeof(DisplayIdRegister_s));
//
//    return idReg;
//}
//
//static inline bool display_dr_checkAddressWindow(const uint16_t x, const uint16_t x1, const uint16_t y, const uint16_t y1)
//{
//    if (x > x1)
//    {
//        return false;
//    }
//
//    if (x1 >= m_display_width)
//    {
//        return false;
//    }
//
//    if (y > y1)
//    {
//        return false;
//    }
//
//    if (y1 >= m_display_height)
//    {
//        return false;
//    }
//
//    return true;
//}
//
///*** end of file ***/
