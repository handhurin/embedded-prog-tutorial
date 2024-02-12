/**
 * @file    generic_hal_tim.h
 * @author  Merlin Kooshmanian
 * @brief   Header file for GENERIC HAL timers and ticks for HAL
 * @date    07/05/2023
 *
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

#ifndef generic_hal_TIM_H
#define generic_hal_TIM_H

/******************************* Include Files *******************************/

#include "generic_hal_types.h"

/***************************** Macros Definitions ****************************/

/***************************** Types Definitions *****************************/

/** @brief Timer instance type definition */
typedef TIM_HandleTypeDef timerInst_t;

/*************************** Variables Declarations **************************/

/*************************** Functions Declarations **************************/

HAL_StatusTypeDef HAL_InitTick(uint32_t TimPriority);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);

#endif /* generic_hal_TIM_H */