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
#define FS_PIXEL_DATA_CRC 2215347319u
#endif

#define FS_FONTS 8
#define FS_CHAR_INFOS_IN_FONT 95
#define FS_BYTES_PER_PIXEL 2

typedef enum
{
    FONT_KEY_TEXT_LARGE_ROBOTO_18_R_DEFAULT_TEXT = 0,
    FONT_KEY_TEXT_LARGE_ROBOTO_18_R_PANE_TEXT = 1,
    FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_DEFAULT_TEXT = 2,
    FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_PANE_TEXT = 3,
    FONT_KEY_TEXT_SMALL_ROBOTO_13_R_DEFAULT_TEXT = 4,
    FONT_KEY_TEXT_SMALL_ROBOTO_13_R_PANE_TEXT = 5,
    FONT_KEY_TITLE_ROBOTO_18_R_DEFAULT_TEXT = 6,
    FONT_KEY_TITLE_ROBOTO_18_R_PANE_TEXT = 7,
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
