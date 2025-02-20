#ifndef TEMP_RECORDER_H_
#define TEMP_RECORDER_H_

#include <stdbool.h>
#include <stdint.h>

#define TEMP_RECORDER_DECIMALS 2

typedef struct
{
    uint32_t interval;
    uint32_t start_time;
    uint32_t end_time;
    uint32_t num_samples;
    int32_t min_temp;
    int32_t max_temp;
    int32_t decimals;
} RecFileHeader_s;

bool temp_recorder_handler(void);
bool temp_recorder_start(void);
void temp_recorder_stop(void);
bool temp_recorder_isRecording(void);
uint32_t temp_recorder_getNumSamples(void);

#endif /* TEMP_RECORDER_H_ */
