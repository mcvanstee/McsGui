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

bool fs_readData(const int32_t offset, uint8_t *p_out_data, const int32_t size);

#endif /* GUI_IMAGE_GUI_IMAGE_H_ */
