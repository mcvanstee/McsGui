/**
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2023, Marijn van Stee, all rights reserved.
 *
 */

#ifndef EXTERNAL_DISPLAY_H_
#define EXTERNAL_DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Core/gui_event.h"
#include "Graphics/gui_graphicsinstruction.h"

#define ED_CUSTOM_EVENT_BTNS 14
#define ED_DESCRIPTION_MAX_LENGTH 128

#define ED_BUTTON_DESCRIPTION_MAX_LENGTH 16

#define ED_IN_BUFFER_LENGTH 64U
#define ED_OUT_BUFFER_LENGTH 256U

#define ED_CRC_LENGTH_BYTES 4
#define ED_HEADER_LENGTH 5
#define ED_OUT_PACKET_MAX_PAYLOAD (ED_OUT_BUFFER_LENGTH - ED_HEADER_LENGTH - ED_CRC_LENGTH_BYTES)

#define ED_USE_CUSTOM_BUTTONS 1 /* Enable custom button support (0 OFF / 1 ON) */
#define ED_USE_FILE_TRANSFER 1 /* Enable file transfer support (0 OFF / 1 ON) */
#define ED_FILE_WRITE_TIMEOUT 5000U
#define ED_FILE_TRANSFER_BUFFER_LENGTH 512

typedef struct
{
	uint8_t index;
	uint8_t event;
	char description[ED_BUTTON_DESCRIPTION_MAX_LENGTH];
} __attribute__((__packed__)) EdButtonSetup_s;

typedef struct
{
	uint16_t width;
	uint16_t height;
	bool useKeyNav;
	bool useTouch;
	uint8_t customButtons;
	char description[ED_DESCRIPTION_MAX_LENGTH];
} __attribute__((__packed__)) EdSetup_s;


#if ED_USE_CUSTOM_BUTTONS == 1
extern EdButtonSetup_s ed_getCustomButton(const uint8_t index);
#endif /* ED_USE_CUSTOM_BUTTONS */

extern void ed_eventRecevied(GuiEvent_s guiEvent);
extern void ed_writeBuffer(uint8_t *p_buffer, uint32_t bytesToWrite);
extern uint32_t ed_calculateCrc(const uint8_t *p_data, const uint32_t length);
#if ED_USE_FILE_TRANSFER == 1
extern void ed_startFileWrite(uint32_t fileSize, const char *p_fileName);
#endif /* ED_USE_FILE_TRANSFER */

void ed_setSetup(const EdSetup_s setup);
void ed_handleRequest(uint8_t *p_packet);
void ed_updateDisplay(GraphicsInstruction_s *p_buffer, const uint16_t bufferLength);
void ed_log(const char *p_message);
void ed_requestRtcTime(void);

void ed_sendRequestResponseOK(void);
void ed_sendRequestResponseError(void);
void ed_sendRequestResponseData(uint8_t *p_data, const uint8_t dataLength);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* EXTERNAL_DISPLAY_H_ */
