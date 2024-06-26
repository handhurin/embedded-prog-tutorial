/**
 * @file    initialisation.c
 * @author  Merlin Kooshmanian
 * @brief   Source file initialising tools and HAL
 * @date    21/01/2023
 *
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

/******************************* Include Files *******************************/

#include "initialisation.h"
#include "io_instances.h"
#include "generic_hal.h"
#include "fdir.h"
#include "monitoring.h"
#include "tasks.h"
#include "buffers.h"
#include "mutex.h"

/***************************** Macros Definitions ****************************/

/*************************** Functions Declarations **************************/

extern void InitConsole(uartInst_t *uart_inst);
static void InitCache(void);

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
    status = GpioOpen(&led_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);
    status = GpioOpen(&user_button_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // UARTs Initialisation
    status = UartOpen(&uart_print_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);
    status = UartOpen(&uart_generic_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // I2Cs Initialisation
    status = IicOpen(&iic_inst);
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // RTC Initialisation
    status = RtcInit();
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // Monitor Initialisation
    status = InitMonitoring();
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // Console Initialisation
    InitConsole(&uart_print_inst);

    // Create all tasks
    status = CreateTasks();
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // Create all buffers
    status = CreateBuffers();
    CheckErrors(status, FDIR_ERROR_HANDLER);

    // Create all mutexes
    status = CreateMutexes();
    CheckErrors(status, FDIR_ERROR_HANDLER);
}

/**
 *  @fn     InitCache(void)
 *  @brief  Function that initialises cache memories if it exists
 */
static void InitCache(void)
{
#if defined(CACHE_AVAILABLE)
    // Enable Instruction Cache
    SCB_EnableICache();

    // Enable Data Cache
    SCB_EnableDCache();
#endif
}