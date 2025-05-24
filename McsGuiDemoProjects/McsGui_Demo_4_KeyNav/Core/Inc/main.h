/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
extern SPI_HandleTypeDef *g_p_displaySPI;
extern TIM_HandleTypeDef *g_p_displayBacklightPWMTimer;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void setRTC(const uint32_t timeStamp);
bool updateDateTime(void);
bool adc1ConvCmplt(void);
float getAdcTemp(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Debug_3_Pin GPIO_PIN_0
#define Debug_3_GPIO_Port GPIOA
#define Debug_2_Pin GPIO_PIN_0
#define Debug_2_GPIO_Port GPIOB
#define Display_Reset_Pin GPIO_PIN_12
#define Display_Reset_GPIO_Port GPIOF
#define Display_DC_Pin GPIO_PIN_13
#define Display_DC_GPIO_Port GPIOF
#define TP_CS_Pin GPIO_PIN_14
#define TP_CS_GPIO_Port GPIOF
#define TP_IRQ_Pin GPIO_PIN_15
#define TP_IRQ_GPIO_Port GPIOF
#define TP_BUSY_Pin GPIO_PIN_9
#define TP_BUSY_GPIO_Port GPIOE
#define BTN_DOWN_Pin GPIO_PIN_14
#define BTN_DOWN_GPIO_Port GPIOE
#define BTN_UP_Pin GPIO_PIN_15
#define BTN_UP_GPIO_Port GPIOE
#define BTN_LEFT_Pin GPIO_PIN_10
#define BTN_LEFT_GPIO_Port GPIOB
#define Display_CS_Pin GPIO_PIN_14
#define Display_CS_GPIO_Port GPIOD
#define Display_PWM_TIM4_CH4_Pin GPIO_PIN_15
#define Display_PWM_TIM4_CH4_GPIO_Port GPIOD
#define BTN_RIGHT_Pin GPIO_PIN_0
#define BTN_RIGHT_GPIO_Port GPIOD
#define BTN_OK_Pin GPIO_PIN_1
#define BTN_OK_GPIO_Port GPIOD
#define Debug_1_Pin GPIO_PIN_0
#define Debug_1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
#define USE_DISPLAY_AND_SD_CARD
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
