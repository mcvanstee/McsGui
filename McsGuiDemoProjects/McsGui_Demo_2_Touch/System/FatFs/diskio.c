/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"         /* Obtains integer types */
#include "diskio.h"     /* Declarations of disk functions */

#include "stm32l4xx_hal.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM     0   /* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC     1   /* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB     2   /* Example: Map USB MSD to physical drive 2 */

#define SD_DEFAULT_BLOCK_SIZE 512
#define SD_TIMEOUT (/*30 */1000)

#define BSP_SD_CardInfo HAL_SD_CardInfoTypeDef

static volatile DSTATUS Stat = STA_NOINIT;

#define   MSD_OK                        ((uint8_t)0x00)
#define   MSD_ERROR                     ((uint8_t)0x01)
#define   MSD_ERROR_SD_NOT_PRESENT      ((uint8_t)0x02)

#define   SD_TRANSFER_OK                ((uint8_t)0x00)
#define   SD_TRANSFER_BUSY              ((uint8_t)0x01)
#define   SD_TRANSFER_ERROR             ((uint8_t)0x02)

extern SD_HandleTypeDef hsd1;

static inline DSTATUS SD_CheckStatus(BYTE lun);
static inline uint8_t BSP_SD_GetCardState(void);
static inline void BSP_SD_GetCardInfo(BSP_SD_CardInfo *CardInfo);
static inline uint8_t BSP_SD_Init(void);


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv       /* Physical drive nmuber to identify the drive */
)
{
    return SD_CheckStatus(pdrv);
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv               /* Physical drive nmuber to identify the drive */
)
{
    Stat = STA_NOINIT;

    if (BSP_SD_Init() == MSD_OK)
    {
        Stat = SD_CheckStatus(pdrv);
    }

    return Stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,      /* Physical drive nmuber to identify the drive */
    BYTE *buff,     /* Data buffer to store read data */
    LBA_t sector,   /* Start sector in LBA */
    UINT count      /* Number of sectors to read */
)
{
    UNUSED(pdrv);

    DRESULT res = RES_ERROR;

    if (HAL_SD_ReadBlocks_DMA(&hsd1, (uint8_t *)buff, (uint32_t)(sector), count) == HAL_OK)
    {
        /* wait until the read operation is finished */
        while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER)
        {
        }

        res = RES_OK;
    }

    return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,          /* Physical drive nmuber to identify the drive */
    const BYTE *buff,   /* Data to be written */
    LBA_t sector,       /* Start sector in LBA */
    UINT count          /* Number of sectors to write */
)
{
    UNUSED(pdrv);

    DRESULT res = RES_ERROR;

    if (HAL_SD_WriteBlocks(&hsd1, (uint8_t *)buff, (uint32_t)(sector), count, SD_TIMEOUT) == HAL_OK)
    {
        /* wait until the Write operation is finished */
        while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER)
        {
        }

        res = RES_OK;
    }

    return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,      /* Physical drive nmuber (0..) */
    BYTE cmd,       /* Control code */
    void *buff      /* Buffer to send/receive control data */
)
{
    UNUSED(pdrv);

      DRESULT res = RES_ERROR;
      BSP_SD_CardInfo CardInfo;

      if (Stat & STA_NOINIT) return RES_NOTRDY;

      switch (cmd)
      {
      /* Make sure that no pending write process */
      case CTRL_SYNC :
        res = RES_OK;
        break;

      /* Get number of sectors on the disk (DWORD) */
      case GET_SECTOR_COUNT :
        BSP_SD_GetCardInfo(&CardInfo);
        *(DWORD*)buff = CardInfo.LogBlockNbr;
        res = RES_OK;
        break;

      /* Get R/W sector size (WORD) */
      case GET_SECTOR_SIZE :
        BSP_SD_GetCardInfo(&CardInfo);
        *(WORD*)buff = CardInfo.LogBlockSize;
        res = RES_OK;
        break;

      /* Get erase block size in unit of sector (DWORD) */
      case GET_BLOCK_SIZE :
        BSP_SD_GetCardInfo(&CardInfo);
        *(DWORD*)buff = CardInfo.LogBlockSize / SD_DEFAULT_BLOCK_SIZE;
        res = RES_OK;
        break;

      default:
        res = RES_PARERR;
      }

      return res;
}


DWORD get_fattime (void)
{
    return 0;
}

static inline DSTATUS SD_CheckStatus(BYTE lun)
{
    UNUSED(lun);

    Stat = STA_NOINIT;

    if (BSP_SD_GetCardState() == MSD_OK)
    {
        Stat &= ~STA_NOINIT;
    }

    return Stat;
}

static inline uint8_t BSP_SD_GetCardState(void)
{
    return ((HAL_SD_GetCardState(&hsd1) == HAL_SD_CARD_TRANSFER) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}

static inline void BSP_SD_GetCardInfo(BSP_SD_CardInfo *CardInfo)
{
  /* Get SD card Information */
  HAL_SD_GetCardInfo(&hsd1, CardInfo);
}

static inline uint8_t BSP_SD_Init(void)
{
  uint8_t sd_state = MSD_OK;

  /* HAL SD initialization */
  sd_state = HAL_SD_Init(&hsd1);
  /* Configure SD Bus width (4 bits mode selected) */
  if (sd_state == MSD_OK)
  {
    /* Enable wide operation */
    if (HAL_SD_ConfigWideBusOperation(&hsd1, SDMMC_BUS_WIDE_4B) != HAL_OK)
    {
      sd_state = MSD_ERROR;
    }
  }

  return sd_state;
}
