/*
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2024, Marijn van Stee, all rights reserved.
 *
 */

#ifndef FS_FILE_SEARCH_H_
#define FS_FILE_SEARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef FS_PIXEL_DATA_CRC
#define FS_PIXEL_DATA_CRC 3709369534u
#endif

#define FS_FILES 1068
#define FS_MAX_FILE_PROPERTIES 4U
#define FS_BYTES_PER_PIXEL 2

typedef struct
{
    uint32_t dataOffset; /* Pixeldata starts at this byte offset */
    uint8_t properties;  /* Properties in use */
    uint16_t width;      /* Width of image in pixels */
    uint16_t height;     /* Height of image in pixels */
} fs_file_info_s;

typedef enum
{
    FILE_SEARCH_OK = 0,
    FILE_SEARCH_OUT_OF_BOUNDS = 1,
    FILE_SEARCH_PROPERTY_LENGTH = 2,
    FILE_SEARCH_PROPERTY_NOT_FOUND = 3,
    FILE_SEARCH_DUMMY_NO_DATA = 4,
    FILE_SEARCH_ERROR_READING_DATA = 5,
} file_search_result_e;

typedef enum
{
    FILE_PROPERTY_LANGUAGE = 0,
    FILE_PROPERTY_ANIMATION = 1,
    FILE_PROPERTY_THEME = 2,
    FILE_PROPERTY_ACCENTCOLOR = 3,
} file_property_e;

typedef enum
{
    PROPERTY_LANGUAGE_VALUE_ENGLISH = 0,
    PROPERTY_LANGUAGE_VALUE_DUTCH = 1,
    PROPERTY_LANGUAGE_VALUE_GERMAN = 2,
    PROPERTY_LANGUAGE_VALUE_FRENCH = 3,
    PROPERTY_LANGUAGE_VALUE_SPANISH = 4,
    PROPERTY_LANGUAGE_VALUE_ITALIAN = 5,
    PROPERTY_LANGUAGE_VALUE_RUSSIAN = 6,
    PROPERTY_LANGUAGE_VALUE_CHINESE = 7,
    PROPERTY_LANGUAGE_VALUE_JAPANESE = 8,
    PROPERTY_LANGUAGE_VALUE_KOREAN = 9,
} property_value_language_e;

typedef enum
{
    PROPERTY_ANIMATION_VALUE_0 = 0,
    PROPERTY_ANIMATION_VALUE_1 = 1,
    PROPERTY_ANIMATION_VALUE_2 = 2,
    PROPERTY_ANIMATION_VALUE_3 = 3,
    PROPERTY_ANIMATION_VALUE_4 = 4,
    PROPERTY_ANIMATION_VALUE_5 = 5,
    PROPERTY_ANIMATION_VALUE_6 = 6,
    PROPERTY_ANIMATION_VALUE_7 = 7,
    PROPERTY_ANIMATION_VALUE_8 = 8,
    PROPERTY_ANIMATION_VALUE_9 = 9,
    PROPERTY_ANIMATION_VALUE_10 = 10,
    PROPERTY_ANIMATION_VALUE_11 = 11,
    PROPERTY_ANIMATION_VALUE_12 = 12,
    PROPERTY_ANIMATION_VALUE_13 = 13,
    PROPERTY_ANIMATION_VALUE_14 = 14,
    PROPERTY_ANIMATION_VALUE_15 = 15,
    PROPERTY_ANIMATION_VALUE_16 = 16,
    PROPERTY_ANIMATION_VALUE_17 = 17,
    PROPERTY_ANIMATION_VALUE_18 = 18,
    PROPERTY_ANIMATION_VALUE_19 = 19,
    PROPERTY_ANIMATION_VALUE_20 = 20,
    PROPERTY_ANIMATION_VALUE_21 = 21,
    PROPERTY_ANIMATION_VALUE_22 = 22,
    PROPERTY_ANIMATION_VALUE_23 = 23,
} property_value_animation_e;

typedef enum
{
    PROPERTY_THEME_VALUE_DARK = 0,
    PROPERTY_THEME_VALUE_LIGHT = 1,
} property_value_theme_e;

typedef enum
{
    PROPERTY_ACCENTCOLOR_VALUE_WHITE = 0,
    PROPERTY_ACCENTCOLOR_VALUE_BLACK = 1,
    PROPERTY_ACCENTCOLOR_VALUE_RED = 2,
    PROPERTY_ACCENTCOLOR_VALUE_GREEN = 3,
    PROPERTY_ACCENTCOLOR_VALUE_BLUE = 4,
} property_value_accentcolor_e;


typedef enum
{
    FILE_KEY_ANIMATION_IRL_LOGO = 0,                  /* B: Animation */
    FILE_KEY_BUTTON_FOOTER_BUTTON = 24,               /* C: Theme */
    FILE_KEY_BUTTON_NUMINPUT_MINUS = 26,              /* C: Theme */
    FILE_KEY_BUTTON_NUMINPUT_PLUS = 28,               /* C: Theme */
    FILE_KEY_BUTTON_PAGE_BACKGROUND = 30,             /* C: Theme */
    FILE_KEY_BUTTON_SLIDER = 32,                      /* C: Theme */
    FILE_KEY_FOOTER_MCSGUI = 34,                      /* C: Theme */
    FILE_KEY_ICON_BTN_AGENDA = 36,                    /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_ARROW_BACK = 46,                /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_ARROW_DOWN = 56,                /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_ARROW_UP = 66,                  /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_BELL = 76,                      /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_BRIGHTNESS = 86,                /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_BRUSH = 96,                     /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_CANCEL = 106,                   /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_CHECKMARK_LARGE = 116,          /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_CLOCK = 126,                    /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_FOCUS = 136,                    /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_GEAR = 146,                     /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_GLOBAL = 156,                   /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_INFO = 166,                     /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_KEYBOARD = 176,                 /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_MINUS = 186,                    /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_PALETTE = 196,                  /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_PLUS = 206,                     /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_SLIDERS = 216,                  /* C: Theme D: AccentColor */
    FILE_KEY_ICON_BTN_WIFI = 226,                     /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_ARROW_DOWN = 236,               /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_ARROW_UP = 246,                 /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_CHECKBOX_CHECKED = 256,         /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_CHECKBOX_UNCHECKED = 266,       /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_CHECKMARK = 276,                /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_MINUS = 286,                    /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_PLUS = 296,                     /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_RADIO_BUTTON_CHECKED = 306,     /* C: Theme D: AccentColor */
    FILE_KEY_ICON_DFT_RADIO_BUTTON_UNCHECKED = 316,   /* C: Theme D: AccentColor */
    FILE_KEY_ICON_HEADER_BELL = 326,                  /* C: Theme */
    FILE_KEY_ICON_HEADER_CLOCK = 328,                 /* C: Theme */
    FILE_KEY_ICON_HEADER_WIFI = 330,                  /* C: Theme */
    FILE_KEY_IRL_LOGO_128 = 332,
    FILE_KEY_IRL_LOGO_48 = 333,
    FILE_KEY_KEYBOARD_LC = 334,                       /* C: Theme */
    FILE_KEY_KEYBOARD_NUM = 336,                      /* C: Theme */
    FILE_KEY_KEYBOARD_TEXTBOX = 338,                  /* C: Theme */
    FILE_KEY_KEYBOARD_UC = 340,                       /* C: Theme */
    FILE_KEY_TEXT_BUTTON_ACCENT_COLOR = 342,          /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_ALARM = 362,                 /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_BRIGHTNESS = 382,            /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_DATE = 402,                  /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_INFO = 422,                  /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_INTERN_TEMP = 442,           /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_KEYBOARD = 462,              /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_LANGUAGE = 482,              /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_MEASUREMENT = 502,           /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_SETTINGS = 522,              /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_SETUP = 542,                 /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_THEME = 562,                 /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_TIME = 582,                  /* A: Language C: Theme */
    FILE_KEY_TEXT_BUTTON_UNITS = 602,                 /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_ACCENT_COLOR = 622,             /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_ACTIVATE_ALARM = 642,           /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_ALARM = 662,                    /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_CHINESE_SIM = 682,              /* C: Theme */
    FILE_KEY_TEXT_DFT_CURSOR_COLOR = 684,             /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_DEG_CEL = 704,                  /* C: Theme */
    FILE_KEY_TEXT_DFT_DEG_FAR = 706,                  /* C: Theme */
    FILE_KEY_TEXT_DFT_DUTCH = 708,                    /* C: Theme */
    FILE_KEY_TEXT_DFT_ENGLISH = 710,                  /* C: Theme */
    FILE_KEY_TEXT_DFT_FRENCH = 712,                   /* C: Theme */
    FILE_KEY_TEXT_DFT_GERMAN = 714,                   /* C: Theme */
    FILE_KEY_TEXT_DFT_INTERN_TEMP = 716,              /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_ITALIAN = 736,                  /* C: Theme */
    FILE_KEY_TEXT_DFT_JAPANESE = 738,                 /* C: Theme */
    FILE_KEY_TEXT_DFT_KOREAN = 740,                   /* C: Theme */
    FILE_KEY_TEXT_DFT_MEASUREMENT = 742,              /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_RUSSIAN = 762,                  /* C: Theme */
    FILE_KEY_TEXT_DFT_SET_ALARM_IN = 764,             /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_SPANISH = 784,                  /* C: Theme */
    FILE_KEY_TEXT_DFT_THEME_DARK = 786,               /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_THEME_LIGHT = 806,              /* A: Language C: Theme */
    FILE_KEY_TEXT_DFT_TIME_MM = 826,                  /* C: Theme */
    FILE_KEY_TITLE_ALARM = 828,                       /* A: Language C: Theme */
    FILE_KEY_TITLE_BRIGHTNESS = 848,                  /* A: Language C: Theme */
    FILE_KEY_TITLE_COLORS = 868,                      /* A: Language C: Theme */
    FILE_KEY_TITLE_DATE = 888,                        /* A: Language C: Theme */
    FILE_KEY_TITLE_INFO = 908,                        /* A: Language C: Theme */
    FILE_KEY_TITLE_LANGUAGE = 928,                    /* A: Language C: Theme */
    FILE_KEY_TITLE_MAIN_MENU = 948,                   /* A: Language C: Theme */
    FILE_KEY_TITLE_MEASUREMENT = 968,                 /* A: Language C: Theme */
    FILE_KEY_TITLE_SETTINGS = 988,                    /* A: Language C: Theme */
    FILE_KEY_TITLE_SETUP = 1008,                      /* A: Language C: Theme */
    FILE_KEY_TITLE_THEME = 1028,                      /* A: Language C: Theme */
    FILE_KEY_TITLE_TIME = 1048,                       /* A: Language C: Theme */
    FILE_KEY_NONE = 0xFFFFFFFF
} file_key_e;

/**
* @brief  Search the file info according to the file-key
*         and copy the data to the fs_file_info_s struct.
* @param  file_key a value from the file_key_e enum
* @param  p_out_file_info Pointer to a fs_file_info_s structure
*         where the file info data is copied to.
* @retval file_search_result_e
*/
file_search_result_e fs_getFileInfo(
                            const file_key_e file_key,
                            const uint8_t *p_properties,
                            const uint8_t propertiesLength,
                            fs_file_info_s *p_out_file_info);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*FS_FILE_SEARCH_H_*/
