/**
 * @file    generic_hal.h
 * @author  Merlin Kooshmanian
 * @brief   Header including all GENERIC HAL headers
 * @date    29/04/2023
 *
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

#ifndef GENERIC_HAL_H
#define GENERIC_HAL_H

/******************************* Include Files *******************************/

#if defined(ART_PI)
#include "art_pi_bsp.h"
#elif defined(NUCLEO_H745ZI)
#include "nucleo_h745zi_bsp.h"
#elif defined(NUCLEO_F411RE)
#include "nucleo_f411re_bsp.h"
#elif defined(DISCOVERY_F407VG)
#include "discovery_f407vg_bsp.h"
#elif defined(NUCLEO_F103RB)
#include "nucleo_f103rb_bsp.h"
#else
#error "Board is not supported"
#endif

#include "generic_hal_types.h"
#include "generic_hal_init.h"
#include "generic_hal_gpio.h"
#include "generic_hal_uart.h"
#include "generic_hal_iic.h"
#include "generic_hal_spi.h"
#include "generic_hal_ow.h"
#include "generic_hal_rtc.h"
#include "generic_hal_ecc.h"

/***************************** Macros Definitions ****************************/

/***************************** Types Definitions *****************************/

/*************************** Variables Declarations **************************/

/*************************** Functions Declarations **************************/

#endif /* GENERIC_HAL_H */