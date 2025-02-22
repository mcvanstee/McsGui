/*
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2024, Marijn van Stee, all rights reserved.
 *
 */

#ifndef FS_FONT_SEARCH_H_
#define FS_FONT_SEARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef FS_PIXEL_DATA_CRC
#define FS_PIXEL_DATA_CRC 3709369534u
#endif

#define FS_FONTS 13
#define FS_CHAR_INFOS_IN_FONT 95
#define FS_BYTES_PER_PIXEL 2

typedef enum
{
    FONT_KEY_BUTTON_FONT_000 = 0,
    FONT_KEY_BUTTON_FONT_001 = 1,
    FONT_KEY_DEFAULT_FONT_000 = 2,
    FONT_KEY_DEFAULT_FONT_001 = 3,
    FONT_KEY_DEFAULT_FONT_002 = 4,
    FONT_KEY_DIGIT_INPUT_FONT_000 = 5,
    FONT_KEY_DIGIT_INPUT_FONT_001 = 6,
    FONT_KEY_KEYBOARD_FONT_000 = 7,
    FONT_KEY_KEYBOARD_FONT_001 = 8,
    FONT_KEY_TITLE_FONT_000 = 9,
    FONT_KEY_TITLE_FONT_001 = 10,
    FONT_KEY_TITLE_FONT_002 = 11,
    FONT_KEY_TITLE_FONT_003 = 12,
} font_key_e;

typedef struct
{
    uint32_t dataOffset;    // Pixeldata starts at this byte offset
    uint8_t width;          // Width of bmp in pixels
    uint8_t height;         // Height of bmp in pixels
} fs_char_info_s;

bool fs_getCharInfo(const char c, const font_key_e font_key, fs_char_info_s *p_out_char_info);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*FS_FONT_SEARCH_H_*/
