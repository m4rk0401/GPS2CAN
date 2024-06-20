/**
  ******************************************************************************
  * File Name          : CAN.h
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_CAN_H_
#define INC_CAN_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */
#include "GNSS.h"

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan;

/* USER CODE BEGIN Private defines */

#define CAN_ID_TimeINT 0x90

#define GPS_DATE 		0x70
#define GPS_POSITION	0x71
#define GPS_SPEED		0x72
#define GPS_STATUS		0x73

/* USER CODE END Private defines */
uint8_t send_date(GNSS_StateHandle *GNSS);
uint8_t send_position(GNSS_StateHandle *GNSS);
uint8_t send_speed(GNSS_StateHandle *GNSS);
uint8_t send_status(GNSS_StateHandle *GNSS);

#ifdef __cplusplus
}
#endif

#endif /* INC_CAN_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
