/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

void setRTC(const uint32_t timeStamp);
bool updateDateTime(void);
bool adc1ConvCmplt(void);
float getAdcTemp(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Display_D2_Pin GPIO_PIN_2
#define Display_D2_GPIO_Port GPIOE
#define Display_D3_Pin GPIO_PIN_3
#define Display_D3_GPIO_Port GPIOE
#define Display_D4_Pin GPIO_PIN_4
#define Display_D4_GPIO_Port GPIOE
#define Display_D5_Pin GPIO_PIN_5
#define Display_D5_GPIO_Port GPIOE
#define Display_D6_Pin GPIO_PIN_6
#define Display_D6_GPIO_Port GPIOE
#define Debug_1_Pin GPIO_PIN_2
#define Debug_1_GPIO_Port GPIOF
#define BTN_OK_Pin GPIO_PIN_4
#define BTN_OK_GPIO_Port GPIOA
#define Display_CS_Pin GPIO_PIN_6
#define Display_CS_GPIO_Port GPIOA
#define Display_D7_Pin GPIO_PIN_7
#define Display_D7_GPIO_Port GPIOE
#define Display_D8_Pin GPIO_PIN_8
#define Display_D8_GPIO_Port GPIOE
#define Display_D9_Pin GPIO_PIN_9
#define Display_D9_GPIO_Port GPIOE
#define Display_D10_Pin GPIO_PIN_10
#define Display_D10_GPIO_Port GPIOE
#define Display_D11_Pin GPIO_PIN_11
#define Display_D11_GPIO_Port GPIOE
#define Display_D12_Pin GPIO_PIN_12
#define Display_D12_GPIO_Port GPIOE
#define Display_D13_Pin GPIO_PIN_13
#define Display_D13_GPIO_Port GPIOE
#define Display_D14_Pin GPIO_PIN_14
#define Display_D14_GPIO_Port GPIOE
#define Display_D15_Pin GPIO_PIN_15
#define Display_D15_GPIO_Port GPIOE
#define BTN_DOWN_Pin GPIO_PIN_12
#define BTN_DOWN_GPIO_Port GPIOB
#define BTN_RIGHT_Pin GPIO_PIN_13
#define BTN_RIGHT_GPIO_Port GPIOB
#define BTN_UP_Pin GPIO_PIN_15
#define BTN_UP_GPIO_Port GPIOB
#define BTN_LEFT_Pin GPIO_PIN_6
#define BTN_LEFT_GPIO_Port GPIOC
#define Display_DC_Pin GPIO_PIN_0
#define Display_DC_GPIO_Port GPIOD
#define Display_Reset_Pin GPIO_PIN_1
#define Display_Reset_GPIO_Port GPIOD
#define Display_D0_Pin GPIO_PIN_0
#define Display_D0_GPIO_Port GPIOE
#define Display_D1_Pin GPIO_PIN_1
#define Display_D1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
#define USE_DISPLAY_AND_SD_CARD
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
