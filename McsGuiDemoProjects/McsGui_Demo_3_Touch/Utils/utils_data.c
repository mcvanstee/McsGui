#include "utils_data.h"

#include <string.h>


bool utils_data_loadStruct(const char *p_fileName, void *p_object, const size_t sizeofObject)
{
    FRESULT result;
    FIL file;
    UINT bytesRead = 0;

    result = f_open(&file, p_fileName, FA_READ | FA_OPEN_EXISTING);
    if (result != FR_OK)
    {
        return false;
    }

    f_read(&file, p_object, sizeofObject, &bytesRead);
    f_close(&file);

    return bytesRead == sizeofObject;
}

bool utils_data_saveStruct(const char *p_fileName, const void *p_object, const size_t sizeofObject)
{
    FRESULT result;
    FIL file;
    UINT bytesWritten = 0;

    result = f_open(&file, p_fileName, FA_WRITE | FA_CREATE_ALWAYS);
    if (result != FR_OK)
    {
        return false;
    }

    f_write(&file, p_object, sizeofObject, &bytesWritten);
    f_close(&file);

    return bytesWritten == sizeofObject;
}

bool utils_data_readStructFromFile(FIL *p_file, void *p_object, const size_t sizeofObject)
{
    UINT bytesRead = 0;

    f_read(p_file, p_object, sizeofObject, &bytesRead);

    return bytesRead == sizeofObject;
}

bool utils_data_writeStructToFile(FIL *p_file, const void *p_object, const size_t sizeofObject)
{
    UINT bytesWritten = 0;

    f_write(p_file, p_object, sizeofObject, &bytesWritten);

    return bytesWritten == sizeofObject;
}

bool utils_data_createFolderIfNotExist(const char *p_folderName)
{
    bool result = true;
    FILINFO fno;

    if (FR_OK != f_stat(p_folderName, &fno))  //Check if exists
    {
        result = FR_OK == f_mkdir(p_folderName); //Create folder
    }

    return result;
}

