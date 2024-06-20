/**
  ******************************************************************************
  * File Name          : CAN.c
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

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

static 			CAN_TxHeaderTypeDef   	TxMsg;
static volatile uint8_t 				TxData[8];
static 			uint32_t 				TxMailbox;

/* USER CODE END 0 */

uint8_t send_date(GNSS_StateHandle *GNSS)
{
	TxMsg.StdId = GPS_DATE;
	TxMsg.IDE = CAN_ID_STD;
	TxMsg.DLC = 8;

	TxData[0] = GNSS->year - 2000;	// Offset of +2000
	TxData[1] = GNSS->month;
	TxData[2] = GNSS->day;
	TxData[3] = GNSS->hour;
	TxData[4] = GNSS->min;
	TxData[5] = GNSS->sec;
	TxData[6] = (uint8_t)(GNSS->msec & 0xFF);
	TxData[7] = (uint8_t)((GNSS->msec >> 8) & 0xFF);

	while(HAL_CAN_IsTxMessagePending(&hcan, TxMailbox));	// Wait until Mailbox is ready to compute next message

	if (HAL_CAN_AddTxMessage(&hcan, &TxMsg, (uint8_t*)TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t send_position(GNSS_StateHandle *GNSS)
{
	TxMsg.StdId = GPS_POSITION;
	TxMsg.IDE = CAN_ID_STD;
	TxMsg.DLC = 8;

	long lat = (long)GNSS->fLat * 10000000;
	for(int i=0; i<4; i++)
	{
		TxData[i] = (uint8_t)((lat >> (i * 8)) & 0xFF);
	}

	long lon = (long)GNSS->fLon * 10000000;
	for(int i=4; i<8; i++)
	{
		TxData[i] = (uint8_t)((lon >> (i * 8)) & 0xFF);
	}

	while(HAL_CAN_IsTxMessagePending(&hcan, TxMailbox));	// Wait until Mailbox is ready to compute next message

	if (HAL_CAN_AddTxMessage(&hcan, &TxMsg, (uint8_t*)TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t send_speed(GNSS_StateHandle *GNSS)
{
	TxMsg.StdId = GPS_SPEED;
	TxMsg.IDE = CAN_ID_STD;
	TxMsg.DLC = 4;

	uint16_t tmp = (uint16_t)(GNSS->gSpeed * 100);
	TxData[0] = (uint8_t)(tmp & 0xFF);
	TxData[1] = (uint8_t)((tmp >> 8) & 0xFF);

	tmp = (uint16_t)(GNSS->headMot * 100);
	TxData[2] = (uint8_t)(tmp & 0xFF);
	TxData[3] = (uint8_t)((tmp >> 8) & 0xFF);

	while(HAL_CAN_IsTxMessagePending(&hcan, TxMailbox));	// Wait until Mailbox is ready to compute next message

	if (HAL_CAN_AddTxMessage(&hcan, &TxMsg, (uint8_t*)TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t send_status(GNSS_StateHandle *GNSS)
{
	TxMsg.StdId = GPS_STATUS;
	TxMsg.IDE = CAN_ID_STD;
	TxMsg.DLC = 4;

	uint16_t tmp = (uint16_t)(GNSS->hDOP * 100);
	TxData[0] = (uint8_t)(tmp & 0xFF);
	TxData[1] = (uint8_t)((tmp >> 8) & 0xFF);

	TxData[2] = GNSS->numSv;
	TxData[3] = GNSS->fixType;

	while(HAL_CAN_IsTxMessagePending(&hcan, TxMailbox));	// Wait until Mailbox is ready to compute next message

	if (HAL_CAN_AddTxMessage(&hcan, &TxMsg, (uint8_t*)TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
		return 1;
	}
	else
	{
		return 0;
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
