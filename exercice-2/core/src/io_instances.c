/**
 * @file    io_instances.c
 * @author  Merlin Kooshmanian
 * @brief   Source file stocking instance for IO's
 * @date    15/07/2023
 *
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

/******************************* Include Files *******************************/

#include "io_instances.h"

/*************************** Variables Definitions ***************************/

/**
 * @var     iic_inst
 * @brief   I2C instance declaration
 */
iicInst_t iic_inst = {
    .iic_ref = I2C_GENERIC,
    .drive_type = IIC_IT_MASTER_DRIVE,
};

/**
 * @var     uart_generic_inst
 * @brief   UART generic instance declaration
 */
uartInst_t uart_generic_inst = {
    .uart_ref = UART_GENERIC,
    .drive_type = UART_POLLING_DRIVE,
    .baud_rate = 115200,
};

/**
 * @var     uart_print_inst
 * @brief   UART print instance declaration
 */
uartInst_t uart_print_inst = {
    .uart_ref = UART_PRINT,
    .drive_type = UART_POLLING_DRIVE,
    .baud_rate = 115200,
};

/**
 * @var     led_inst
 * @brief   GPIO led instance declaration
 */
gpioInst_t led_inst = {
    .port = USER_LED_GPIO_PORT,
    .pin = USER_LED_PIN,
    .mode = GPIO_MODE_OUTPUT_PP,
    .pull = GPIO_NOPULL,
    .speed = GPIO_SPEED_FREQ_LOW,
};

/**
 * @var     user_button_inst
 * @brief   GPIO button instance declaration
 */
gpioInst_t user_button_inst = {
    .port = USER_BUTTON_GPIO_PORT,
    .pin = USER_BUTTON_PIN,
    .mode = GPIO_MODE_IT_FALLING,
    .pull = GPIO_NOPULL,
    .speed = GPIO_SPEED_FREQ_LOW,
};
