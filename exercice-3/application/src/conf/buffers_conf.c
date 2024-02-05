/**
 * @file    buffers_conf.c
 * @author  Merlin Kooshmanian
 * @brief   Source file stocking configuration table for buffers
 * @date    26/04/2023
 *
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

/******************************* Include Files *******************************/

#include "conf/buffers_conf.h"
#include "conf/tasks_conf.h"

/*************************** Variables Definitions ***************************/

/**
 * @var     g_buffers_static_conf
 * @brief   Configuration table where all buffers static parameters are stored
 */
const bufferStaticConf_t g_buffers_static_conf[NB_BUFFERS] = 
{
    /* Buffer Ref   , Sender Ref   , Receiver Ref , Msg Size , Msg Nb */
    { BUFF01_BUFFER , MAIN_TASK    , MAIN_TASK    , 12U      , 1U     },
};

/**
 * @var     g_buffers_dynamic_conf
 * @brief   Configuration table where all buffers dynamic parameters are stored
 */
bufferDynamicConf_t g_buffers_dynamic_conf[NB_BUFFERS] = 
{
    /* Buffer Handle  , Nb Msg */
    { 0u              , 0u     },
};
