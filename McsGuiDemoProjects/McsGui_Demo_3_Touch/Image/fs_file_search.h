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
#define FS_PIXEL_DATA_CRC 2215347319u
#endif

#define FS_FILES 277
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
    FILE_PROPERTY_THEME = 1,
    FILE_PROPERTY_SELECTION = 2,
    FILE_PROPERTY_RECORDING = 3,
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
    PROPERTY_THEME_VALUE_LIGHT = 0,
    PROPERTY_THEME_VALUE_DARK = 1,
} property_value_theme_e;

typedef enum
{
    PROPERTY_SELECTION_VALUE_FALSE = 0,
    PROPERTY_SELECTION_VALUE_TRUE = 1,
} property_value_selection_e;

typedef enum
{
    PROPERTY_RECORDING_VALUE_FALSE = 0,
    PROPERTY_RECORDING_VALUE_TRUE = 1,
} property_value_recording_e;


typedef enum
{
    FILE_KEY_BUTTON_MINUS = 0,
    FILE_KEY_BUTTON_PLAY = 1,
    FILE_KEY_BUTTON_PLAY_PRESSED = 2,
    FILE_KEY_BUTTON_PLUS = 3,
    FILE_KEY_BUTTON_STOP = 4,
    FILE_KEY_BUTTON_STOP_PRESSED = 5,
    FILE_KEY_ICON_ARROW_DOWN_SMALL = 6,
    FILE_KEY_ICON_ARROW_UP_SMALL = 7,
    FILE_KEY_ICON_BACK = 8,
    FILE_KEY_ICON_BULLSEYE = 9,            /* C: Selection D: Recording */
    FILE_KEY_ICON_CLOCK = 13,
    FILE_KEY_ICON_DATA = 14,               /* C: Selection */
    FILE_KEY_ICON_DISPLAY = 16,
    FILE_KEY_ICON_FOCUS = 17,              /* C: Selection */
    FILE_KEY_ICON_GEAR = 19,               /* C: Selection */
    FILE_KEY_ICON_HOME = 21,               /* C: Selection */
    FILE_KEY_ICON_LANGUAGE = 23,
    FILE_KEY_ICON_MINUS = 24,
    FILE_KEY_ICON_PANE_AGENDA = 25,
    FILE_KEY_ICON_PANE_CLOCK = 26,
    FILE_KEY_ICON_PLUS = 27,
    FILE_KEY_ICON_PULSE = 28,
    FILE_KEY_ICON_SCROLL_DOWN = 29,
    FILE_KEY_ICON_SCROLL_UP = 30,
    FILE_KEY_ICON_SLIDER_KNOB = 31,
    FILE_KEY_ICON_SLIDERS = 32,            /* C: Selection */
    FILE_KEY_ICON_SWITCH = 34,             /* C: Selection */
    FILE_KEY_ICON_THERMOMETER = 36,
    FILE_KEY_ICON_TRASH = 37,
    FILE_KEY_IRL_LOGO_128 = 38,
    FILE_KEY_IRL_LOGO_48 = 39,
    FILE_KEY_RADIO_BUTTON = 40,            /* C: Selection */
    FILE_KEY_TEXT_CHINESE_SIM = 42,
    FILE_KEY_TEXT_DATE_TIME = 43,          /* A: Language */
    FILE_KEY_TEXT_DEG_CEL = 53,
    FILE_KEY_TEXT_DEG_FAR = 54,
    FILE_KEY_TEXT_DISPLAY = 55,            /* A: Language */
    FILE_KEY_TEXT_DUTCH = 65,
    FILE_KEY_TEXT_ENGLISH = 66,
    FILE_KEY_TEXT_FRENCH = 67,
    FILE_KEY_TEXT_GERMAN = 68,
    FILE_KEY_TEXT_HASHTAG = 69,
    FILE_KEY_TEXT_HIDE_DATE = 70,          /* A: Language */
    FILE_KEY_TEXT_HIDE_TIME = 80,          /* A: Language */
    FILE_KEY_TEXT_ID = 90,
    FILE_KEY_TEXT_INTERVAL = 91,           /* A: Language */
    FILE_KEY_TEXT_ITALIAN = 101,
    FILE_KEY_TEXT_JAPANESE = 102,
    FILE_KEY_TEXT_KOREAN = 103,
    FILE_KEY_TEXT_LANGUAGE = 104,          /* A: Language */
    FILE_KEY_TEXT_MAX_DATA_POINTS = 114,   /* A: Language */
    FILE_KEY_TEXT_RUSSIAN = 124,
    FILE_KEY_TEXT_SAVE = 125,              /* A: Language */
    FILE_KEY_TEXT_SAVE_REC = 135,          /* A: Language */
    FILE_KEY_TEXT_SAVED = 145,             /* A: Language */
    FILE_KEY_TEXT_SHOW_DATE = 155,         /* A: Language */
    FILE_KEY_TEXT_SHOW_TIME = 165,         /* A: Language */
    FILE_KEY_TEXT_SPANISH = 175,
    FILE_KEY_TEXT_UNITS = 176,             /* A: Language */
    FILE_KEY_TITLE_BRIGHTNESS = 186,       /* A: Language */
    FILE_KEY_TITLE_CALIBRATE_TOUCH = 196,  /* A: Language */
    FILE_KEY_TITLE_DATE_TIME = 206,        /* A: Language */
    FILE_KEY_TITLE_ID = 216,
    FILE_KEY_TITLE_LANGUAGE = 217,         /* A: Language */
    FILE_KEY_TITLE_MEASUREMENTS = 227,     /* A: Language */
    FILE_KEY_TITLE_RECORDINGS = 237,       /* A: Language */
    FILE_KEY_TITLE_SETTINGS = 247,         /* A: Language */
    FILE_KEY_TITLE_START = 257,            /* A: Language */
    FILE_KEY_TITLE_STOP = 267,             /* A: Language */
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
