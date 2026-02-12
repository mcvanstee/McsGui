#ifndef UTILS_DATA_H_
#define UTILS_DATA_H_

#include <stdbool.h>
#include <stdlib.h>

#include "ff.h"

bool utils_data_loadStruct(const char *p_fileName, void *p_object, const size_t sizeofObject);
bool utils_data_saveStruct(const char *p_fileName, const void *p_object, const size_t sizeofObject);
bool utils_data_readStructFromFile(FIL *p_file, void *p_object, const size_t sizeofObject);
bool utils_data_writeStructToFile(FIL *p_file, const void *p_object, const size_t sizeofObject);
bool utils_data_createFolderIfNotExist(const char *p_folderName);

#endif /* UTILS_DATA_H_ */
