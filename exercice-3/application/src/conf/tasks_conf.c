/**
 * @file    tasks_conf.c
 * @author  Merlin Kooshmanian
 * @brief   Source file stocking configuration table for tasks
 * @date    26/04/2023
 * 
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

/******************************* Include Files *******************************/

#include "conf/tasks_conf.h"
#include "dummy_tasks.h"

/*************************** Variables Definitions ***************************/

/**
 * @var     g_tasks_static_conf
 * @brief   Configuration table where all tasks static parameters are stored
 */
const taskStaticConf_t g_tasks_static_conf[NB_TASKS] = 
{
    /* Task Ref    , Name       , Function      , Priority              , Stack Size , Default Period , Default Deadline , Privilege       */
    { MAIN_TASK    , "MainTask" , DummyMainTask , PRIORITY_ABOVE_NORMAL , 1024U      , 100u           , 100u             , TASK_PRIVILEGED },
};

/**
 * @var     g_tasks_dynamic_conf
 * @brief   Configuration table where all tasks dynamic parameters are stored
 */
taskDynamicConf_t g_tasks_dynamic_conf[NB_TASKS] = 
{
    /* Task Handle , Task Mode     , Period , Deadline , Last Wake-Up Tick */
    { 0u           , TASK_NOMINAL  , 0u     , 0u       , 0u                },
};
