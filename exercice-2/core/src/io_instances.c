/**
 * @file    io_instances.c
 * @author  Merlin Kooshmanian
 * @brief   Source file stocking instance for IO's
 * @date    15/07/2023
 *
 * @copyright Copyright (c) TOLOSAT 2023
 */

/******************************* Include Files *******************************/

#include "io_instances.h"

/*************************** Variables Definitions ***************************/

/**
 * @var     iic_inst
 * @brief   I2C instance declaration
 */
iicInst_t iic_inst = {
    .iic_ref = TAPAS_I2C_AVIONIC,
    .drive_type = IIC_IT_MASTER_DRIVE,
};

/**
 * @var     uart_generic_inst
 * @brief   UART generic instance declaration
 */
uartInst_t uart_generic_inst = {
    .uart_ref = TAPAS_UART_TMTC,
    .drive_type = UART_POLLING_DRIVE,
    .baud_rate = 115200,
};

/**
 * @var     uart_print_inst
 * @brief   UART print instance declaration
 */
uartInst_t uart_print_inst = {
    .uart_ref = TAPAS_UART_PRINT,
    .drive_type = UART_POLLING_DRIVE,
    .baud_rate = 115200,
};

/**
 * @var     led_inst
 * @brief   GPIO led instance declaration
 */
gpioInst_t led_inst = {
    .mode = GPIO_MODE_OUTPUT_PP,
    .pull = GPIO_NOPULL,
    .speed = GPIO_SPEED_FREQ_LOW,
};

/**
 * @var     user_button_inst
 * @brief   GPIO button instance declaration
 */
gpioInst_t user_button_inst = {
    .mode = GPIO_MODE_IT_FALLING,
    .pull = GPIO_NOPULL,
    .speed = GPIO_SPEED_FREQ_LOW,
};
