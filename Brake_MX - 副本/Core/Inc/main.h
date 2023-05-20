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
#define RC522_RST_Pin GPIO_PIN_0
#define RC522_RST_GPIO_Port GPIOA
#define SR_Pin GPIO_PIN_2
#define SR_GPIO_Port GPIOA
#define RC522_NSS_Pin GPIO_PIN_4
#define RC522_NSS_GPIO_Port GPIOA
#define Door_Button_Pin GPIO_PIN_10
#define Door_Button_GPIO_Port GPIOB
#define Door_Button_EXTI_IRQn EXTI15_10_IRQn
#define RELAY_Cmd_Pin GPIO_PIN_11
#define RELAY_Cmd_GPIO_Port GPIOB
#define KEY_Pin GPIO_PIN_8
#define KEY_GPIO_Port GPIOA
#define KEY_EXTI_IRQn EXTI9_5_IRQn
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOD
#define I2C_SCL_Pin GPIO_PIN_6
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_7
#define I2C_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
