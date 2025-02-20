#ifndef FS_FILE_SEARCH_H_
#define FS_FILE_SEARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

uint32_t crc_32(const unsigned char *input_str, size_t num_bytes);
uint32_t update_crc_32(uint32_t crc, unsigned char c);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*FS_FILE_SEARCH_H_*/
