#include "gui_memory.h"

#include "McsGui/Utils/gui_log.h"

#if GUI_USE_DYNAMIC_MEMORY

static uint32_t totalMalloced = 0;
static uint32_t totalFreed = 0;


/**
 * @brief Allocates memory and addes the size to the totalMalloced. This function calles the stdlib malloc function.
 * @param[in] size of the memory to be allocated.
 * @return Pointer to the allocated memory.
 *
 */
void *gui_mem_malloc(size_t size)
{
    void *mem = malloc(size);
    if (mem != NULL)
    {
        totalMalloced += size;
    }
    else
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "Failed to allocate memory");
    }

    return mem;
}


/**
 * @brief Free the memory of pointer p_mem, the size is added to totalFreed. This function calles the stdlib free function.
 * @param[in] p_mem Pointer to the memory to be freed.
 * @param[in] size of the memory to be freed.
 *
 */
void gui_mem_free(void *p_mem, size_t size)
{
    if (p_mem != NULL)
    {
        free(p_mem);
        totalFreed += size;
        p_mem = NULL;
    }
    else
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "Failed to free memory");
    }
}


/**
 * @brief The total amound of memory (bytes) allocated during the runtime of the application.
 * @return totalMalloced.
 *
 */
uint32_t gui_mem_totalMalloced(void)
{
    return totalMalloced;
}


/**
 * @brief The total amound of memory (bytes) freed during the runtime of the application.
 * @return totalFreed.
 *
 */
uint32_t gui_mem_totalFreed(void)
{
    return totalFreed;
}


/**
 * @brief The total memory currently in use.
 * @return Memory in use.
 */
uint32_t gui_mem_inUse(void)
{
    return (totalMalloced - totalFreed);
}

#endif /* GUI_USE_DYNAMIC_MEMORY */

/*** end of file ***/
