/*__________________________________________________________________________________
|                                                                                   |
|             McsGui - Generic GUI module for small embedded systems.               |
|___________________________________________________________________________________|
|                                                                                   |
|  Copyright (c) 2020, Marijn van Stee, all rights reserved.                        |
|                                                                                   |
|                                                                                   |
|  Redistribution and use in source and binary forms, with or without               |
|  modification, are permitted provided that the following condition is met:        |
|                                                                                   |
|  1. Redistributions of source code must retain the above copyright notice,        |
|     and the following disclaimer.                                                 |
|                                                                                   |
|  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  |
|  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    |
|  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           |
|  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR  |
|  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES   |
|  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     |
|  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      |
|  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       |
|  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    |
|  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     |
|___________________________________________________________________________________|
*/

/** @file mcsgui.h
 *
 * @brief Include this header in your application to use the GUI module
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_MCSGUI_H_
#define MCSGUI_MCSGUI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_config.h"

#include "McsGui/Components/gui_button.h"
#include "McsGui/Components/gui_checkbox.h"
#include "McsGui/Components/gui_label.h"
#include "McsGui/Components/gui_listview.h"
#include "McsGui/Components/gui_listviewitem.h"
#include "McsGui/Components/gui_radiogroup.h"
#include "McsGui/Components/gui_rectangle.h"
#include "McsGui/Components/gui_textblock.h"
#include "McsGui/Core/gui_view.h"
#include "McsGui/Utils/gui_touch.h"
#include "McsGui/Utils/gui_keynavigation.h"

#define MCSGUI_VERSION_MAJOR 1
#define MCSGUI_VERSION_MINOR 0
#define MCSGUI_VERSION_PATCH 0

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_MCSGUI_H_ */


/*** end of file ***/
