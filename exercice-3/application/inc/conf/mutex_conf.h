/**
 * @file    mutex_conf.h
 * @author  Merlin Kooshmanian
 * @brief   Header file stocking configuration table for mutex
 * @date    28/10/2023
 * 
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

#ifndef MUTEX_CONF_H
#define MUTEX_CONF_H

/******************************* Include Files *******************************/

#include "mutex.h"

/***************************** Macros Definitions ****************************/

/***************************** Types Definitions *****************************/

/**
 * @enum    MUTEX_ENUM
 * @brief   Enum defining mutexes reference numbers
 */
enum MUTEX_ENUM 
{
    FS_MUTEX,
    NB_MUTEXES,
};

/*************************** Variables Declarations **************************/

extern mutexConf_t g_mutex_conf[NB_MUTEXES];

#endif /* MUTEX_H */