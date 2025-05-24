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
#define FS_PIXEL_DATA_CRC 3017595173u
#endif

#define FS_FILES 864
#define FS_MAX_FILE_PROPERTIES 5U
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
    FILE_PROPERTY_THEME = 0,
    FILE_PROPERTY_ANIMATION = 1,
    FILE_PROPERTY_LANGUAGE = 2,
    FILE_PROPERTY_FOCUS = 3,
    FILE_PROPERTY_ACCENT_COLOR = 4,
} file_property_e;

typedef enum
{
    PROPERTY_THEME_VALUE_LIGHT = 0,
    PROPERTY_THEME_VALUE_DARK = 1,
} property_value_theme_e;

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
    PROPERTY_FOCUS_VALUE_FALSE = 0,
    PROPERTY_FOCUS_VALUE_TRUE = 1,
} property_value_focus_e;

typedef enum
{
    PROPERTY_ACCENT_COLOR_VALUE_RED = 0,
    PROPERTY_ACCENT_COLOR_VALUE_GREEN = 1,
    PROPERTY_ACCENT_COLOR_VALUE_BLUE = 2,
    PROPERTY_ACCENT_COLOR_VALUE_WHITE = 3,
} property_value_accent_color_e;


typedef enum
{
    FILE_KEY_ANIMATION_IRL_LOGO = 0,                  /* B: Animation */
    FILE_KEY_BUTTON_FOOTER_BUTTON = 24,               /* A: Theme */
    FILE_KEY_BUTTON_NUMINPUT_MINUS = 26,              /* A: Theme */
    FILE_KEY_BUTTON_NUMINPUT_PLUS = 28,               /* A: Theme */
    FILE_KEY_BUTTON_PAGE_BACKGROUND = 30,             /* A: Theme */
    FILE_KEY_BUTTON_SLIDER = 32,                      /* A: Theme */
    FILE_KEY_ICON_BUTTON_AGENDA = 34,                 /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_ARROW_BACK = 42,             /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_BELL = 50,                   /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_BRIGHTNESS = 58,             /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_BRUSH = 66,                  /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_CANCEL = 74,                 /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_CHECKMARK_LARGE = 82,        /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_CLOCK = 90,                  /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_FOCUS = 98,                  /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_GEAR = 106,                  /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_GLOBAL = 114,                /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_INFO = 122,                  /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_KEYBOARD = 130,              /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_PALETTE = 138,               /* A: Theme E: Accent Color */
    FILE_KEY_ICON_BUTTON_SLIDERS = 146,               /* A: Theme E: Accent Color */
    FILE_KEY_ICON_HEADER_BELL = 154,                  /* A: Theme */
    FILE_KEY_ICON_HEADER_CLOCK = 156,                 /* A: Theme */
    FILE_KEY_ICON_HEADER_WIFI = 158,                  /* A: Theme */
    FILE_KEY_ICON_PANE_ARROW_DOWN = 160,              /* A: Theme */
    FILE_KEY_ICON_PANE_ARROW_UP = 162,                /* A: Theme */
    FILE_KEY_ICON_PANE_CHECKMARK = 164,               /* A: Theme */
    FILE_KEY_ICON_PANE_MINUS = 166,                   /* A: Theme */
    FILE_KEY_ICON_PANE_PLUS = 168,                    /* A: Theme */
    FILE_KEY_ICON_PANE_RADIO_BUTTON_CHECKED = 170,    /* A: Theme E: Accent Color */
    FILE_KEY_ICON_PANE_RADIO_BUTTON_UNCHECKED = 178,  /* A: Theme E: Accent Color */
    FILE_KEY_IRL_LOGO_128 = 186,
    FILE_KEY_IRL_LOGO_48 = 187,
    FILE_KEY_KEYBOARD_LC = 188,                       /* A: Theme */
    FILE_KEY_KEYBOARD_NUM = 190,                      /* A: Theme */
    FILE_KEY_KEYBOARD_TEXTBOX = 192,                  /* A: Theme */
    FILE_KEY_KEYBOARD_UC = 194,                       /* A: Theme */
    FILE_KEY_TEXT_ACCENT_COLOR = 196,                 /* A: Theme C: Language */
    FILE_KEY_TEXT_ALARM = 216,                        /* A: Theme C: Language */
    FILE_KEY_TEXT_BRIGHTNESS = 236,                   /* A: Theme C: Language */
    FILE_KEY_TEXT_COLORS = 256,                       /* A: Theme C: Language */
    FILE_KEY_TEXT_DATE = 276,                         /* A: Theme C: Language */
    FILE_KEY_TEXT_FOOTER_MCSGUI = 296,                /* A: Theme */
    FILE_KEY_TEXT_INFO = 298,                         /* A: Theme C: Language */
    FILE_KEY_TEXT_KEYBOARD = 318,                     /* A: Theme C: Language */
    FILE_KEY_TEXT_LANGUAGE = 338,                     /* A: Theme C: Language */
    FILE_KEY_TEXT_MEASUREMENT = 358,                  /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_ACCENT_COLOR = 378,            /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_ACTIVATE_ALARM = 398,          /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_CHINESE_SIM = 418,             /* A: Theme */
    FILE_KEY_TEXT_PANE_CURSOR_COLOR = 420,            /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_DEG_CEL = 440,                 /* A: Theme */
    FILE_KEY_TEXT_PANE_DEG_FAR = 442,                 /* A: Theme */
    FILE_KEY_TEXT_PANE_DUTCH = 444,                   /* A: Theme */
    FILE_KEY_TEXT_PANE_ENGLISH = 446,                 /* A: Theme */
    FILE_KEY_TEXT_PANE_FRENCH = 448,                  /* A: Theme */
    FILE_KEY_TEXT_PANE_GERMAN = 450,                  /* A: Theme */
    FILE_KEY_TEXT_PANE_INTERN_TEMP = 452,             /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_ITALIAN = 472,                 /* A: Theme */
    FILE_KEY_TEXT_PANE_JAPANESE = 474,                /* A: Theme */
    FILE_KEY_TEXT_PANE_KOREAN = 476,                  /* A: Theme */
    FILE_KEY_TEXT_PANE_RUSSIAN = 478,                 /* A: Theme */
    FILE_KEY_TEXT_PANE_SET_ALARM_IN = 480,            /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_SPANISH = 500,                 /* A: Theme */
    FILE_KEY_TEXT_PANE_THEME_DARK = 502,              /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_THEME_LIGHT = 522,             /* A: Theme C: Language */
    FILE_KEY_TEXT_PANE_TIME_MM = 542,                 /* A: Theme */
    FILE_KEY_TEXT_SETTINGS = 544,                     /* A: Theme C: Language */
    FILE_KEY_TEXT_SETUP = 564,                        /* A: Theme C: Language */
    FILE_KEY_TEXT_THEME = 584,                        /* A: Theme C: Language */
    FILE_KEY_TEXT_TIME = 604,                         /* A: Theme C: Language */
    FILE_KEY_TITLE_ALARM = 624,                       /* A: Theme C: Language */
    FILE_KEY_TITLE_BRIGHTNESS = 644,                  /* A: Theme C: Language */
    FILE_KEY_TITLE_COLORS = 664,                      /* A: Theme C: Language */
    FILE_KEY_TITLE_DATE = 684,                        /* A: Theme C: Language */
    FILE_KEY_TITLE_INFO = 704,                        /* A: Theme C: Language */
    FILE_KEY_TITLE_LANGUAGE = 724,                    /* A: Theme C: Language */
    FILE_KEY_TITLE_MAIN_MENU = 744,                   /* A: Theme C: Language */
    FILE_KEY_TITLE_MEASUREMENT = 764,                 /* A: Theme C: Language */
    FILE_KEY_TITLE_SETTINGS = 784,                    /* A: Theme C: Language */
    FILE_KEY_TITLE_SETUP = 804,                       /* A: Theme C: Language */
    FILE_KEY_TITLE_THEME = 824,                       /* A: Theme C: Language */
    FILE_KEY_TITLE_TIME = 844,                        /* A: Theme C: Language */
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
