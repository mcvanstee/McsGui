/**
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef GUI_IMAGE_GUI_IMAGE_H_
#define GUI_IMAGE_GUI_IMAGE_H_

#include <stdbool.h>
#include <stdint.h>

#define GUI_IMAGE_DIRECTORY "GuiImage/"

bool gui_image_initialize(void);

void gui_image_drawImage(
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint32_t dataAddress, const uint32_t dataSize);

bool fs_readData(const int32_t offset, uint8_t *p_out_data, const int32_t size);

#endif /* GUI_IMAGE_GUI_IMAGE_H_ */
