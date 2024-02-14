/**
 * @file    interrupts.c
 * @author  Merlin Kooshmanian
 * @brief   Source file containing all the interrupts
 * @date    16/04/2023
 *
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

/******************************* Include Files *******************************/

#include "interrupts.h"
#include "generic_hal.h"
#include "io_instances.h"

/***************************** Macros Definitions ****************************/

/*************************** Functions Declarations **************************/

/*************************** Variables Definitions ***************************/

/*************************** Functions Definitions ***************************/

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void)
{
    while (1)
    {
    }
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief This function is the BUTTON interruption handler.
 */
void USER_BUTTON_IRQ_HANDLER(void)
{
    // First clear interrupt flag
    if (__HAL_GPIO_EXTI_GET_IT(USER_BUTTON_PIN) != 0x00U)
    {
    __HAL_GPIO_EXTI_CLEAR_IT(USER_BUTTON_PIN);
    }

    // Then do the interrupt routine
    /* Do something here */
}

/**
 * @brief This function handles I2C GENERIC event interrupt.
 */
void I2C_GENERIC_EVT_IRQ_HANDLER(void)
{
    HAL_I2C_EV_IRQHandler(&iic_inst.handle_struct);
}

/**
 * @brief This function handles UART GENERIC global interrupt.
 */
void UART_GENERIC_IRQ_HANDLER(void)
{
    HAL_UART_IRQHandler(&uart_generic_inst.handle_struct);
}
