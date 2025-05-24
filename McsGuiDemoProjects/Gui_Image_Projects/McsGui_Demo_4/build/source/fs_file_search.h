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
#define FS_PIXEL_DATA_CRC 858239376u
#endif

#define FS_FILES 996
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
    FILE_PROPERTY_THEME = 0,
    FILE_PROPERTY_ANIMATION = 1,
    FILE_PROPERTY_LANGUAGE = 2,
    FILE_PROPERTY_FOCUS = 3,
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
    FILE_KEY_ANIMATION_IRL_LOGO = 0,             /* B: Animation */
    FILE_KEY_ICON_ARROW_BACK = 24,               /* A: Theme D: Focus */
    FILE_KEY_ICON_BRIGHTNESS = 28,               /* A: Theme D: Focus */
    FILE_KEY_ICON_BRUSH = 32,                    /* A: Theme D: Focus */
    FILE_KEY_ICON_CLOCK = 36,                    /* A: Theme */
    FILE_KEY_ICON_FOCUS = 38,                    /* A: Theme D: Focus */
    FILE_KEY_ICON_GEAR = 42,                     /* A: Theme D: Focus */
    FILE_KEY_ICON_GLOBAL = 46,                   /* A: Theme D: Focus */
    FILE_KEY_ICON_INFO = 50,                     /* A: Theme D: Focus */
    FILE_KEY_ICON_LIMIT = 54,                    /* A: Theme D: Focus */
    FILE_KEY_ICON_MINUS = 58,                    /* A: Theme D: Focus */
    FILE_KEY_ICON_PLUS = 62,                     /* A: Theme D: Focus */
    FILE_KEY_ICON_PULSE = 66,                    /* A: Theme D: Focus */
    FILE_KEY_ICON_RADIO_BUTTON_CHECKED = 70,     /* A: Theme D: Focus */
    FILE_KEY_ICON_RADIO_BUTTON_UNCHECKED = 74,   /* A: Theme D: Focus */
    FILE_KEY_ICON_SLIDERS = 78,                  /* A: Theme D: Focus */
    FILE_KEY_ICON_WIFI = 82,                     /* A: Theme */
    FILE_KEY_IRL_LOGO_128 = 84,
    FILE_KEY_IRL_LOGO_48 = 85,
    FILE_KEY_TEXT_BACK = 86,                     /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_BRIGHTNESS = 126,              /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_CHINESE_SIM = 166,             /* A: Theme D: Focus */
    FILE_KEY_TEXT_DEG_CEL = 170,                 /* A: Theme D: Focus */
    FILE_KEY_TEXT_DEG_FAR = 174,                 /* A: Theme D: Focus */
    FILE_KEY_TEXT_DUTCH = 178,                   /* A: Theme D: Focus */
    FILE_KEY_TEXT_ENGLISH = 182,                 /* A: Theme D: Focus */
    FILE_KEY_TEXT_FRENCH = 186,                  /* A: Theme D: Focus */
    FILE_KEY_TEXT_GERMAN = 190,                  /* A: Theme D: Focus */
    FILE_KEY_TEXT_HIGH = 194,                    /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_INFO = 234,                    /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_INTERN_TEMP = 274,             /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_INTERVAL = 314,                /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_ITALIAN = 354,                 /* A: Theme D: Focus */
    FILE_KEY_TEXT_JAPANESE = 358,                /* A: Theme D: Focus */
    FILE_KEY_TEXT_KOREAN = 362,                  /* A: Theme D: Focus */
    FILE_KEY_TEXT_LANGUAGE = 366,                /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_LIMITS = 406,                  /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_LOW = 446,                     /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_MCSGUI = 486,                  /* A: Theme */
    FILE_KEY_TEXT_MEASUREMENT = 488,             /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_RUSSIAN = 528,                 /* A: Theme D: Focus */
    FILE_KEY_TEXT_SETTINGS = 532,                /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_SETUP = 572,                   /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_SPANISH = 612,                 /* A: Theme D: Focus */
    FILE_KEY_TEXT_THEME = 616,                   /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_THEME_DARK = 656,              /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_THEME_LIGHT = 696,             /* A: Theme C: Language D: Focus */
    FILE_KEY_TEXT_UNITS = 736,                   /* A: Theme C: Language D: Focus */
    FILE_KEY_TITLE_BRIGHTNESS = 776,             /* A: Theme C: Language */
    FILE_KEY_TITLE_INFO = 796,                   /* A: Theme C: Language */
    FILE_KEY_TITLE_INTERVAL = 816,               /* A: Theme C: Language */
    FILE_KEY_TITLE_LANGUAGE = 836,               /* A: Theme C: Language */
    FILE_KEY_TITLE_LIMITS = 856,                 /* A: Theme C: Language */
    FILE_KEY_TITLE_MAIN_MENU = 876,              /* A: Theme C: Language */
    FILE_KEY_TITLE_MEASUREMENT = 896,            /* A: Theme C: Language */
    FILE_KEY_TITLE_SETTINGS = 916,               /* A: Theme C: Language */
    FILE_KEY_TITLE_SETUP = 936,                  /* A: Theme C: Language */
    FILE_KEY_TITLE_THEME = 956,                  /* A: Theme C: Language */
    FILE_KEY_TITLE_UNITS = 976,                  /* A: Theme C: Language */
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
