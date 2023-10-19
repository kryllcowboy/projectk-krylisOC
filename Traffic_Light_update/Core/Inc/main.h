/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define BUZZER_Pin GPIO_PIN_13
#define BUZZER_GPIO_Port GPIOC
#define BUTTON_Pin GPIO_PIN_0
#define BUTTON_GPIO_Port GPIOA
#define BUTTON_EXTI_IRQn EXTI0_IRQn
#define MY_HEAD_Pin GPIO_PIN_1
#define MY_HEAD_GPIO_Port GPIOA
#define PEDESTRIAN_SOUND_Pin GPIO_PIN_9
#define PEDESTRIAN_SOUND_GPIO_Port GPIOE
#define AUTO_TIME_CLK_Pin GPIO_PIN_12
#define AUTO_TIME_CLK_GPIO_Port GPIOE
#define AUTO_TIME_DATA_Pin GPIO_PIN_13
#define AUTO_TIME_DATA_GPIO_Port GPIOE
#define PEDESTRIAN_TIME_CLK_Pin GPIO_PIN_14
#define PEDESTRIAN_TIME_CLK_GPIO_Port GPIOE
#define PEDESTRIAN_TIME_DATA_Pin GPIO_PIN_15
#define PEDESTRIAN_TIME_DATA_GPIO_Port GPIOE
#define PEDESTRIAN_GREEN_Pin GPIO_PIN_10
#define PEDESTRIAN_GREEN_GPIO_Port GPIOD
#define PEDESTRIAN_RED_Pin GPIO_PIN_12
#define PEDESTRIAN_RED_GPIO_Port GPIOD
#define AUTO_GREEN_Pin GPIO_PIN_13
#define AUTO_GREEN_GPIO_Port GPIOD
#define AUTO_YELOW_Pin GPIO_PIN_14
#define AUTO_YELOW_GPIO_Port GPIOD
#define AUTO_RED_Pin GPIO_PIN_15
#define AUTO_RED_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
