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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_LEFT_Pin GPIO_PIN_13
#define BTN_LEFT_GPIO_Port GPIOC
#define BTN_DOWN_Pin GPIO_PIN_14
#define BTN_DOWN_GPIO_Port GPIOC
#define BTN_UP_Pin GPIO_PIN_15
#define BTN_UP_GPIO_Port GPIOC
#define U_LED_Pin GPIO_PIN_0
#define U_LED_GPIO_Port GPIOC
#define GPS_PPS_Pin GPIO_PIN_1
#define GPS_PPS_GPIO_Port GPIOC
#define GPS_RX_Pin GPIO_PIN_2
#define GPS_RX_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_3
#define GPS_TX_GPIO_Port GPIOA
#define IMU_INT_Pin GPIO_PIN_6
#define IMU_INT_GPIO_Port GPIOC
#define ESP_RX0_Pin GPIO_PIN_9
#define ESP_RX0_GPIO_Port GPIOA
#define ESP_TX0_Pin GPIO_PIN_10
#define ESP_TX0_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define BTN_OK_Pin GPIO_PIN_11
#define BTN_OK_GPIO_Port GPIOC
#define BTN_RIGHT_Pin GPIO_PIN_12
#define BTN_RIGHT_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
