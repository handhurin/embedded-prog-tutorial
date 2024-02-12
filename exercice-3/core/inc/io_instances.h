/**
 * @file    io_instances.c
 * @author  Merlin Kooshmanian
 * @brief   Header file stocking instance for IO's
 * @date    15/07/2023
 * 
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

#ifndef IO_INSTANCES_H
#define IO_INSTANCES_H

/******************************* Include Files *******************************/

#include <stdint.h>
#include "generic_hal.h"

/***************************** Macros Definitions ****************************/

/***************************** Types Definitions *****************************/

/*************************** Variables Declarations **************************/

extern iicInst_t iic_inst;
extern uartInst_t uart_generic_inst;
extern uartInst_t uart_print_inst;
extern gpioInst_t led_inst;
extern gpioInst_t user_button_inst;

#endif /* IO_INSTANCES_H */