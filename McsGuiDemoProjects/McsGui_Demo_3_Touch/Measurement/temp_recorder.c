#include "temp_recorder.h"

#include <stdio.h>

#include "main.h"
#include "gui_app.h"
#include "gui_settings.h"
#include "gui_utils_time_converter.h"
#include "utils_data.h"
#include "utils_math.h"

typedef struct
{
    uint32_t id;
} RecorderInfo_t;

static FIL m_recFile = {0};
static RecFileHeader_s m_recHeader = {0};
static bool m_isRecording = false;
static uint32_t m_nextSampleTime = 0;

static uint32_t temp_recorder_getNextId(void);
static void temp_recorder_addSample(void);

extern RTC_HandleTypeDef hrtc;


bool temp_recorder_handler(void)
{
    bool sampleAdded = false;

    if (!m_isRecording)
    {
        return sampleAdded;
    }

    const uint32_t timestamp = gui_app_getTimeStamp();

    if (timestamp >= m_nextSampleTime)
    {
        temp_recorder_addSample();
        sampleAdded = true;
    }

    return sampleAdded;
}

bool temp_recorder_start(void)
{
    bool result = false;

    if (m_isRecording)
    {
        return result;
    }

    const uint32_t id = temp_recorder_getNextId();

    if (id == 0)
    {
        return result;
    }

    RTC_TimeTypeDef time = {0};
    RTC_DateTypeDef date = {0};

    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

    char startTimeStr[16] = {0};
    sprintf(startTimeStr, "%02d-%02d-%02d", time.Hours, time.Minutes, time.Seconds);

    const uint32_t timestamp = time_converter_rtcTimeToTimeStamp(&time, &date);

    char filename[64] = {0};
    sprintf(filename, "Recordings/new/rec_%lu_%s", id, startTimeStr);

    FRESULT res = f_open(&m_recFile, filename, FA_READ | FA_WRITE | FA_CREATE_NEW);

    if (FR_OK == res)
    {
        UINT bytesWritten = 0;
        m_recHeader.interval = settings_getInterval();
        m_recHeader.start_time = timestamp;
        m_recHeader.end_time = 0;
        m_recHeader.num_samples = 0;
        m_recHeader.min_temp = 0;
        m_recHeader.max_temp = 0;
        m_recHeader.decimals = TEMP_RECORDER_DECIMALS;

        f_write(&m_recFile, &m_recHeader, sizeof(RecFileHeader_s), &bytesWritten);

        result = (bytesWritten == sizeof(RecFileHeader_s));
        m_isRecording = result;
        m_nextSampleTime = m_recHeader.start_time;

        if (m_isRecording)
        {
            temp_recorder_addSample();
        }
        else
        {
            f_close(&m_recFile);
            f_unlink(filename);
        }
    }

    return result;
}

void temp_recorder_stop(void)
{
    if (!m_isRecording)
    {
        return;
    }

    m_isRecording = false;

    UINT bytesWritten = 0;
    m_recHeader.end_time = gui_app_getTimeStamp();

    f_lseek(&m_recFile, 0);
    f_write(&m_recFile, &m_recHeader, sizeof(RecFileHeader_s), &bytesWritten);
    f_close(&m_recFile);
}

static void temp_recorder_addSample(void)
{
    if (!m_isRecording)
    {
        return;
    }

    m_nextSampleTime += m_recHeader.interval;

    const float_t temp_C = getAdcTemp();
    const int32_t temp_dC = (uint32_t)(temp_C * utils_math_ipow(10, TEMP_RECORDER_DECIMALS));

    if (m_recHeader.num_samples == 0)
    {
        m_recHeader.min_temp = temp_dC;
        m_recHeader.max_temp = temp_dC;
    }
    else
    {
        m_recHeader.min_temp = (temp_dC < m_recHeader.min_temp) ? temp_dC : m_recHeader.min_temp;
        m_recHeader.max_temp = (temp_dC > m_recHeader.max_temp) ? temp_dC : m_recHeader.max_temp;
    }

    m_recHeader.num_samples++;

    UINT bytesWritten = 0;
    f_write(&m_recFile, &temp_dC, sizeof(int32_t), &bytesWritten);
}

static uint32_t temp_recorder_getNextId(void)
{
    FIL recInfoFile = {0};
    RecorderInfo_t info = {0};

    if (FR_OK == f_open(&recInfoFile, "Recordings/recinfo.dat", FA_WRITE | FA_READ | FA_OPEN_EXISTING))
    {
        utils_data_readStructFromFile(&recInfoFile, &info, sizeof(RecorderInfo_t));
        info.id++;
        f_lseek(&recInfoFile, 0);
        utils_data_writeStructToFile(&recInfoFile, &info, sizeof(RecorderInfo_t));
    }
    else if (FR_OK == f_open(&recInfoFile, "Recordings/recinfo.dat", FA_WRITE | FA_OPEN_ALWAYS))
    {
        info.id = 1;
        utils_data_writeStructToFile(&recInfoFile, &info, sizeof(RecorderInfo_t));
    }
    else
    {
    }

    f_close(&recInfoFile);

    return info.id;
}

bool temp_recorder_isRecording(void)
{
    return m_isRecording;
}

uint32_t temp_recorder_getNumSamples(void)
{
    return m_recHeader.num_samples;
}
