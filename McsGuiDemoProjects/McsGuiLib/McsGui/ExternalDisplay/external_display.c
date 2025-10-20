#include "external_display.h"

#include <string.h>

#include "utils_array.h"

#define ED_CONFIG_VERSION 1

#define ED_PACKET_TYPE_INDEX 3
#define ED_PAYLOAD_LENGTH_INDEX 4
#define ED_START_PAYLOAD_INDEX 5

#define ED_DISPLAY_INSTRUCTION_SIZE 20

typedef enum
{
	EdPacketType_Request = 0,
	EdPacketType_RequestResponse = 1,
	EdPacketType_Config,
	EdPacketType_Event,
	EdPacketType_ScreenUpdate,
	EdPacketType_ScreenUpdateCompressed,
	EdPacketType_LogMessage,
	EdPacketType_CustomButtonSetup,
	EdPacketType_SyncRtcTime,
	EdPacketType_Error,
} EdPacketType_s;

typedef enum
{
    EdRequestType_WriteFileToDevice = 0,
    EdRequestType_ReadFileFromDevice,
} EdRequestType_e;

typedef enum
{
    RequestResponseType_OK = 0,
    RequestResponseType_Data,
    RequestResponseType_Error,
} RequestResponseType_e;

typedef enum
{
	IPS_Idle,
	IPS_Sync_1_Received,
	IPS_WaitingForPayloadLength,
	IPS_WaitintForEndOfPacket,
} InPacketStatus_e;

typedef struct ed_config_s
{
	uint16_t version;
	EdSetup_s setup;
} __attribute__((__packed__)) EdConfig_s;

/*  */
static void ed_setSyncBytes(void);
static void ed_addCRC(void);
static bool ed_checkSyncBytes(const uint8_t *p_packet);
static bool ed_checkCRC(const uint8_t *p_packet);
static uint32_t ed_addInstructionToBuffer(GraphicsInstruction_s *p_instruction, const uint32_t payloadLength);
static void ed_sendConfig(void);
static void ed_sendCustomButtonSetup(const uint8_t *p_payload, const uint8_t payloadLength);
static void ed_handleRequestReceived(const uint8_t *p_payload, const uint8_t payloadLength);
static void ed_handleEventReceived(const uint8_t *p_payload, const uint8_t payloadLength);

/*  */
static uint8_t ed_outBuffer[ED_OUT_BUFFER_LENGTH];
static EdSetup_s ed_setup;
/*  */

void ed_setSetup(const EdSetup_s setup)
{
	ed_setup = setup;
}

void ed_handleRequest(uint8_t *p_packet)
{
	const bool syncBytesOK = ed_checkSyncBytes(p_packet);
	const bool crcOK = ed_checkCRC(p_packet);

	if (!syncBytesOK || !crcOK)
	{
		return;
	}

	EdPacketType_s packetType = (EdPacketType_s)p_packet[ED_PACKET_TYPE_INDEX];
	const uint8_t *p_payload = &p_packet[ED_START_PAYLOAD_INDEX];
	const uint8_t payloadLength = p_packet[ED_PAYLOAD_LENGTH_INDEX];

	switch (packetType)
	{
	    case EdPacketType_Request:
	        ed_handleRequestReceived(p_payload, payloadLength);
	        break;
		case EdPacketType_Config:
			ed_sendConfig();
			break;
		case EdPacketType_CustomButtonSetup:
			ed_sendCustomButtonSetup(p_payload, payloadLength);
			break;
		case EdPacketType_Event:
			ed_handleEventReceived(p_payload, payloadLength);
			break;
		default:
			break;
	}
}

void ed_updateDisplay(GraphicsInstruction_s *p_buffer, const uint16_t bufferLength)
{
	uint32_t payloadLength = 0U;

	ed_setSyncBytes();
	ed_outBuffer[ED_PACKET_TYPE_INDEX] =
	        (sizeof(GraphicsInstruction_s) == ED_DISPLAY_INSTRUCTION_SIZE) ? EdPacketType_ScreenUpdate : EdPacketType_ScreenUpdateCompressed;

    for (int32_t i = 0; i < bufferLength; i++)
    {
        GraphicsInstruction_s *p_instruction = &p_buffer[i];

        if (sizeof(GraphicsInstruction_s) <= (ED_OUT_PACKET_MAX_PAYLOAD - payloadLength))
        {
        	payloadLength += ed_addInstructionToBuffer(p_instruction, payloadLength);
        }

        if ((payloadLength + sizeof(GraphicsInstruction_s)) > ED_OUT_PACKET_MAX_PAYLOAD)
        {
        	const uint32_t bytesToWrite = ED_HEADER_LENGTH + payloadLength + ED_CRC_LENGTH_BYTES;

        	ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = payloadLength;
        	ed_addCRC();
        	ed_writeBuffer(ed_outBuffer, bytesToWrite);

        	payloadLength = 0U;
        }
    }

    if (payloadLength > 0)
    {
    	const uint32_t bytesToWrite = ED_HEADER_LENGTH + payloadLength + ED_CRC_LENGTH_BYTES;

    	ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = payloadLength;
    	ed_addCRC();
    	ed_writeBuffer(ed_outBuffer, bytesToWrite);
    }
}

void ed_log(const char *p_message)
{
	const uint32_t messageLength = strlen(p_message);

	ed_setSyncBytes();
	ed_outBuffer[ED_PACKET_TYPE_INDEX] = EdPacketType_LogMessage;
	ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = messageLength;
	utils_array_cpy(ed_outBuffer, (uint8_t *)p_message, ED_START_PAYLOAD_INDEX, 0, messageLength);
	ed_addCRC();

	const uint32_t bytesToWrite =
	        ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] + ED_CRC_LENGTH_BYTES;

	ed_writeBuffer(ed_outBuffer, bytesToWrite);
}

void ed_requestRtcTime(void)
{
    ed_setSyncBytes();
    ed_outBuffer[ED_PACKET_TYPE_INDEX] = EdPacketType_SyncRtcTime;
    ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = 0;
    ed_addCRC();

    const uint32_t bytesToWrite =
            ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] + ED_CRC_LENGTH_BYTES;

    ed_writeBuffer(ed_outBuffer, bytesToWrite);
}

void ed_sendRequestResponseOK(void)
{
    ed_setSyncBytes();
    ed_outBuffer[ED_PACKET_TYPE_INDEX] = EdPacketType_RequestResponse;
    ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = 1;
    ed_outBuffer[ED_START_PAYLOAD_INDEX] = RequestResponseType_OK;
    ed_addCRC();

    const uint32_t bytesToWrite =
            ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] + ED_CRC_LENGTH_BYTES;

    ed_writeBuffer(ed_outBuffer, bytesToWrite);
}

void ed_sendRequestResponseError(void)
{
    ed_setSyncBytes();
    ed_outBuffer[ED_PACKET_TYPE_INDEX] = EdPacketType_RequestResponse;
    ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = 1;
    ed_outBuffer[ED_START_PAYLOAD_INDEX] = RequestResponseType_Error;
    ed_addCRC();

    const uint32_t bytesToWrite =
            ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] + ED_CRC_LENGTH_BYTES;

    ed_writeBuffer(ed_outBuffer, bytesToWrite);
}

void ed_sendRequestResponseData(uint8_t *p_data, const uint8_t dataLength)
{
    ed_setSyncBytes();
    ed_outBuffer[ED_PACKET_TYPE_INDEX] = EdPacketType_RequestResponse;
    ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = 1 + dataLength;
    ed_outBuffer[ED_START_PAYLOAD_INDEX] = RequestResponseType_Data;
    utils_array_cpy(ed_outBuffer, p_data, ED_START_PAYLOAD_INDEX + 1, 0, dataLength);
    ed_addCRC();

    const uint32_t bytesToWrite =
            ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] + ED_CRC_LENGTH_BYTES;

    ed_writeBuffer(ed_outBuffer, bytesToWrite);
}

static void ed_sendConfig(void)
{
	EdConfig_s config = {0};
	config.version = ED_CONFIG_VERSION;
	config.setup = ed_setup;

	ed_setSyncBytes();
	ed_outBuffer[ED_PACKET_TYPE_INDEX] = EdPacketType_Config;
	ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = sizeof(EdConfig_s);
	utils_array_cpy(ed_outBuffer, (uint8_t *)&config, ED_START_PAYLOAD_INDEX, 0, sizeof(EdConfig_s));
	ed_addCRC();

	const uint32_t bytesToWrite = ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] + ED_CRC_LENGTH_BYTES;

	ed_writeBuffer(ed_outBuffer, bytesToWrite);
}

static void ed_sendCustomButtonSetup(const uint8_t *p_payload, const uint8_t payloadLength)
{
#if ED_USE_CUSTOM_BUTTONS == 1
	const uint8_t index = p_payload[0];
	EdButtonSetup_s buttonSetup = ed_getCustomButton(index);

	ed_setSyncBytes();
	ed_outBuffer[ED_PACKET_TYPE_INDEX] = EdPacketType_CustomButtonSetup;
	ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] = sizeof(EdButtonSetup_s);
	utils_array_cpy(ed_outBuffer, (uint8_t *)&buttonSetup, ED_START_PAYLOAD_INDEX, 0, sizeof(EdButtonSetup_s));
	ed_addCRC();

	const uint32_t bytesToWrite = ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX] + ED_CRC_LENGTH_BYTES;

	ed_writeBuffer(ed_outBuffer, bytesToWrite);
#endif /* ED_USE_CUSTOM_BUTTONS */
}

static void ed_handleRequestReceived(const uint8_t *p_payload, const uint8_t payloadLength)
{
    const uint8_t requestType = p_payload[0];

    switch (requestType)
    {
        case EdRequestType_WriteFileToDevice:
#if ED_USE_FILE_TRANSFER == 1
        {
            uint32_t fileSize = utils_array_getUint32(p_payload, 1);
            char fileName[64] = {0};
            utils_array_cpy((uint8_t *)fileName, p_payload, 0, 5, payloadLength - 5);
            ed_startFileWrite(fileSize, fileName);
        }
#else
        ed_sendRequestResponseError();
        ed_log("File transfer not supported");
#endif /* ED_USE_FILE_TRANSFER */
            break;
        case EdRequestType_ReadFileFromDevice:
            break;
        default:
            break;
    }
}

static void ed_handleEventReceived(const uint8_t *p_payload, const uint8_t payloadLength)
{
	GuiEvent_s guiEvent = {0};
	guiEvent.event = p_payload[0];

	if (payloadLength > 1)
	{
		const uint8_t eventArgLength = p_payload[1];
		utils_array_cpy(guiEvent.eventArgs, p_payload, 0, 2, eventArgLength);
	}

	ed_eventRecevied(guiEvent);
}

static void ed_setSyncBytes(void)
{
	ed_outBuffer[0] = 'I';
	ed_outBuffer[1] = 'R';
	ed_outBuffer[2] = 'L';
}

static void ed_addCRC(void)
{
	const uint32_t length = ED_HEADER_LENGTH + ed_outBuffer[ED_PAYLOAD_LENGTH_INDEX];
	const uint32_t crc = ed_calculateCrc(ed_outBuffer, length);
	utils_array_addUint32(ed_outBuffer, crc, length);
}

static bool ed_checkSyncBytes(const uint8_t *p_packet)
{
	return (p_packet[0] == 'I') && (p_packet[1] == 'R') && (p_packet[2] == 'L');
}

static bool ed_checkCRC(const uint8_t *p_packet)
{
	const uint32_t length = ED_HEADER_LENGTH + p_packet[ED_PAYLOAD_LENGTH_INDEX];
	const uint32_t crcFromPacket = utils_array_getUint32(p_packet, length);
	const uint32_t crc = ed_calculateCrc(p_packet, length);

	return crc == crcFromPacket;
}

static uint32_t ed_addInstructionToBuffer(GraphicsInstruction_s *p_instruction, const uint32_t payloadLength)
{
	uint32_t writeIndex = ED_START_PAYLOAD_INDEX + payloadLength;

	utils_array_cpy(ed_outBuffer, (uint8_t *)p_instruction, writeIndex, 0, sizeof(GraphicsInstruction_s));

	return sizeof(GraphicsInstruction_s);
}

