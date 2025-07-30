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
#include "stm32f1xx_hal.h"

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
#define GPS_PPS_Pin GPIO_PIN_1
#define GPS_PPS_GPIO_Port GPIOC
#define VBATT_SENS_Pin GPIO_PIN_2
#define VBATT_SENS_GPIO_Port GPIOC
#define GPS_RX_Pin GPIO_PIN_2
#define GPS_RX_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_3
#define GPS_TX_GPIO_Port GPIOA
#define IMU_INT_Pin GPIO_PIN_6
#define IMU_INT_GPIO_Port GPIOC
#define KBD_COL_C_Pin GPIO_PIN_7
#define KBD_COL_C_GPIO_Port GPIOC
#define KBD_COL_B_Pin GPIO_PIN_8
#define KBD_COL_B_GPIO_Port GPIOC
#define KBD_COL_A_Pin GPIO_PIN_9
#define KBD_COL_A_GPIO_Port GPIOC
#define U_LED_Pin GPIO_PIN_8
#define U_LED_GPIO_Port GPIOA
#define ESP_RX0_Pin GPIO_PIN_9
#define ESP_RX0_GPIO_Port GPIOA
#define ESP_TX0_Pin GPIO_PIN_10
#define ESP_TX0_GPIO_Port GPIOA
#define KBD_ROW_C_Pin GPIO_PIN_10
#define KBD_ROW_C_GPIO_Port GPIOC
#define KBD_ROW_B_Pin GPIO_PIN_11
#define KBD_ROW_B_GPIO_Port GPIOC
#define KBD_ROW_A_Pin GPIO_PIN_12
#define KBD_ROW_A_GPIO_Port GPIOC
#define WIFI_LED_Pin GPIO_PIN_5
#define WIFI_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
