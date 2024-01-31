/**
 * @file    initialisation.c
 * @author  Merlin Kooshmanian
 * @brief   Source file initialising tools and HAL
 * @date    21/01/2023
 *
 * @copyright Copyright (c) TOLOSAT 2023
 */

/******************************* Include Files *******************************/

#include "initialisation.h"
#include "io_instances.h"
#include "tolosat_hal.h"
#include "fdir.h"

/***************************** Macros Definitions ****************************/

/*************************** Functions Declarations **************************/

extern void InitConsole(uartInst_t *uart_inst);
void InitCache(void);

/*************************** Variables Definitions ***************************/

/*************************** Functions Definitions ***************************/

/**
 * @fn      init(void)
 * @brief   Function that initialise tools and HAL
 */
void init(void)
{
    // Variable Initialisation
    uint32_t status = 0u;

    // Cache Initialisation
    InitCache();

    // HAL Initialisation
    status = InitHal();
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // GPIOs Initialisation
    status = GpioOpen(&led_inst, USER_LED_GPIO_PORT, USER_LED_PIN);
    CheckErrors(status, FDIR_ERROR_HANDLER);
    status = GpioOpen(&user_button_inst, USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN);
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // UARTs Initialisation
    status = UartOpen(&uart_print_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);
    status = UartOpen(&uart_generic_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // I2Cs Initialisation
    status = IicOpen(&iic_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // Console Initialisation
    InitConsole(&uart_print_inst);
}

/**
 *  @fn     InitCache(void)
 *  @brief  Function that initialises cache memories if it exists
 */
void InitCache(void)
{
#if defined(CACHE_AVAILABLE)
    // Enable Instruction Cache
    SCB_EnableICache();

    // Enable Data Cache
    SCB_EnableDCache();
#endif
}