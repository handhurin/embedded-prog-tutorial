/**
 * @file    main.c
 * @author  Merlin Kooshmanian
 * @brief   Source file for main
 * @date    26/12/2022
 *
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

/******************************* Include Files *******************************/

#include <stdio.h>

#include "main.h"
#include "initialisation.h"
#include "io_instances.h"

/***************************** Macros Definitions ****************************/

/*************************** Functions Declarations **************************/

/*************************** Variables Definitions ***************************/

/*************************** Functions Definitions ***************************/

/**
 * @fn      main(void)
 * @brief   Flight Software Main is the entrypoint of the code
 * @return  0
 */
int main(void)
{
    // Initialisation
    init();

    // Function Core
    while (1)
    {
        (void) GpioToggle(&led_inst);
        printf("Hello \n");
        HAL_Delay(500);
    }

    return 0;
}
