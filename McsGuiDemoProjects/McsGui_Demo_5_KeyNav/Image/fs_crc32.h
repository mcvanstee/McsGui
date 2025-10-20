#ifndef FS_CRC32_H_
#define FS_CRC32_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

uint32_t crc_32(const unsigned char *input_str, size_t num_bytes);
uint32_t update_crc_32(uint32_t crc, const unsigned char *input_str, size_t num_bytes);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*FS_FILE_SEARCH_H_*/
