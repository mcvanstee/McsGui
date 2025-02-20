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
#define FS_PIXEL_DATA_CRC 2459289286u
#endif

#define FS_FILES 273
#define FS_MAX_FILE_PROPERTIES 2U
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
    FILE_PROPERTY_SELECTED = 0,
    FILE_PROPERTY_LANGUAGE = 1,
} file_property_e;

typedef enum
{
    PROPERTY_SELECTED_VALUE_FALSE = 0,
    PROPERTY_SELECTED_VALUE_TRUE = 1,
} property_value_selected_e;

typedef enum
{
    PROPERTY_LANGUAGE_VALUE_ENGLISH = 0,
    PROPERTY_LANGUAGE_VALUE_DUTCH = 1,
    PROPERTY_LANGUAGE_VALUE_GERMAN = 2,
    PROPERTY_LANGUAGE_VALUE_FRENCH = 3,
    PROPERTY_LANGUAGE_VALUE_SPANISH = 4,
    PROPERTY_LANGUAGE_VALUE_ITALIAN = 5,
    PROPERTY_LANGUAGE_VALUE_RUSSIAN = 6,
    PROPERTY_LANGUAGE_VALUE_CHINESE_SIMPLIFIED = 7,
    PROPERTY_LANGUAGE_VALUE_JAPANESE = 8,
    PROPERTY_LANGUAGE_VALUE_KOREAN = 9,
} property_value_language_e;


typedef enum
{
    FILE_KEY_BUTTON_PLAY = 0,
    FILE_KEY_BUTTON_PLAY_PRESSED = 1,
    FILE_KEY_BUTTON_STOP = 2,
    FILE_KEY_BUTTON_STOP_PRESSED = 3,
    FILE_KEY_CHINESE_SIM = 4,
    FILE_KEY_DEG_CEL = 5,
    FILE_KEY_DEG_FAR = 6,
    FILE_KEY_DUTCH = 7,
    FILE_KEY_ENGLISH = 8,
    FILE_KEY_FRENCH = 9,
    FILE_KEY_GERMAN = 10,
    FILE_KEY_HASHTAG = 11,
    FILE_KEY_HIDE_DATE = 12,               /* B: Language */
    FILE_KEY_HIDE_TIME = 22,               /* B: Language */
    FILE_KEY_ICON_AGENDA = 32,
    FILE_KEY_ICON_ARROW_DOWN_SMALL = 33,
    FILE_KEY_ICON_ARROW_UP_SMALL = 34,
    FILE_KEY_ICON_BACK = 35,               /* A: Selected */
    FILE_KEY_ICON_BULLSEYE = 37,           /* A: Selected */
    FILE_KEY_ICON_BULLSEYE_RED = 39,       /* A: Selected */
    FILE_KEY_ICON_BUTTONMINUS = 41,
    FILE_KEY_ICON_BUTTONPLUS = 42,
    FILE_KEY_ICON_CLOCK = 43,
    FILE_KEY_ICON_DISPLAY = 44,            /* A: Selected */
    FILE_KEY_ICON_FOCUS = 46,              /* A: Selected */
    FILE_KEY_ICON_GEAR = 48,               /* A: Selected */
    FILE_KEY_ICON_HOME = 50,               /* A: Selected */
    FILE_KEY_ICON_LANGUAGE = 52,           /* A: Selected */
    FILE_KEY_ICON_MINUS = 54,              /* A: Selected */
    FILE_KEY_ICON_PLUS = 56,               /* A: Selected */
    FILE_KEY_ICON_PULSE = 58,              /* A: Selected */
    FILE_KEY_ICON_RADIO = 60,              /* A: Selected */
    FILE_KEY_ICON_REC_RECORDING = 62,      /* A: Selected */
    FILE_KEY_ICON_SCROLL_DOWN = 64,
    FILE_KEY_ICON_SCROLL_UP = 65,
    FILE_KEY_ICON_SLIDERS = 66,            /* A: Selected */
    FILE_KEY_ICON_SWITCH = 68,             /* A: Selected */
    FILE_KEY_ICON_THERMOMETER = 70,        /* A: Selected */
    FILE_KEY_ICON_TRASH = 72,              /* A: Selected */
    FILE_KEY_ID = 74,
    FILE_KEY_INTERVAL = 75,                /* B: Language */
    FILE_KEY_IRL_LOGO_128 = 85,
    FILE_KEY_IRL_LOGO_48 = 86,
    FILE_KEY_ITALIAN = 87,
    FILE_KEY_JAPANESE = 88,
    FILE_KEY_KOREAN = 89,
    FILE_KEY_MAX_DATA_POINTS = 90,         /* B: Language */
    FILE_KEY_RUSSIAN = 100,
    FILE_KEY_SAVE_REC = 101,               /* B: Language */
    FILE_KEY_SAVED = 111,                  /* B: Language */
    FILE_KEY_SHOW_DATE = 121,              /* B: Language */
    FILE_KEY_SHOW_TIME = 131,              /* B: Language */
    FILE_KEY_SLIDER_KNOB_ROUND = 141,
    FILE_KEY_SPANISH = 142,
    FILE_KEY_TEXT_BUTTON_SAVE = 143,       /* B: Language */
    FILE_KEY_TITLE_BRIGHTNESS = 153,       /* B: Language */
    FILE_KEY_TITLE_CALIBRATE_TOUCH = 163,  /* B: Language */
    FILE_KEY_TITLE_DATE_TIME = 173,        /* B: Language */
    FILE_KEY_TITLE_DISPLAY = 183,          /* B: Language */
    FILE_KEY_TITLE_ID = 193,               /* B: Language */
    FILE_KEY_TITLE_LANGUAGE = 203,         /* B: Language */
    FILE_KEY_TITLE_MEASUREMENTS = 213,     /* B: Language */
    FILE_KEY_TITLE_RECORDINGS = 223,       /* B: Language */
    FILE_KEY_TITLE_SETTINGS = 233,         /* B: Language */
    FILE_KEY_TITLE_START = 243,            /* B: Language */
    FILE_KEY_TITLE_STOP = 253,             /* B: Language */
    FILE_KEY_UNITS = 263,                  /* B: Language */
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
