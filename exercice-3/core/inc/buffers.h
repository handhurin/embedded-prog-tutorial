/**
 * @file    buffers.h
 * @author  Merlin Kooshmanian
 * @brief   Header file defining buffers
 * @date    27/04/2023
 * 
 * @copyright Copyright (c) TOLOSAT & Merlin Kooshmanian 2024
 */

/**
 * @defgroup core_functions Core Functions
 * @{
 * @defgroup buffers Buffers Management
 * Functions that allows to manage buffers
 * @{
 */

#ifndef BUFFERS_H
#define BUFFERS_H

/******************************* Include Files *******************************/

#include <stdint.h>

#include "os.h"
#include "tasks.h"

/***************************** Macros Definitions ****************************/

#define NO_BUFFER_REF        0xffffffffu /**< Reference number to refer for no buffer */

/***************************** Types Definitions *****************************/

/** 
 * @enum    bufferStatus_t
 * @brief   Buffer functions specific returns 
 */
typedef enum
{
    BUFFER_SUCCESSFUL      = 0u,    /**< Function succeed */
    BUFFER_ERROR           = 1u,    /**< Function failed */
    BUFFER_INVALID_PARAM   = 2u,    /**< Function parameter is not valid */
    BUFFER_TIMEOUT         = 3u,    /**< Function returned a timeout */
    BUFFER_EMPTY           = 4u,    /**< Buffer is empty */
    BUFFER_FULL            = 5u,    /**< Buffer is full */
} bufferStatus_t;

/** @brief Buffer Handle type */
typedef QueueHandle_t bufferHandle_t;

/** @brief Buffer reference number type */
typedef uint32_t bufferRef_t;

/** @brief Buffer width type */
typedef uint32_t bufferSize_t;

/** @brief Buffer depth type */
typedef uint32_t bufferDepth_t;

/** @brief Buffer message address type */
typedef void *bufferMsgAddr_t;

/** 
 * @struct  bufferStaticConf_t
 * @struct  bufferStaticConf_t
 * @brief   Struct type definition of a buffer
 */
typedef struct
{
    bufferRef_t ref;            /**< @brief Buffer reference number as it is declared in BUFFERS_ENUM */
    taskRef_t sender;           /**< @brief Task reference number of the sender */
    taskRef_t receiver;         /**< @brief Task reference number of the receiver */
    bufferSize_t max_size;      /**< @brief Maximum message size the buffer can handle */
    bufferDepth_t max_nb;       /**< @brief Maximum number of message the buffer can handle */
} bufferStaticConf_t;

/** 
 * @struct  bufferDynamicConf_t
 * @brief   Struct type of a buffer dynamic parameters
 */
typedef struct
{                            
    bufferHandle_t handle;      /**< @brief Buffer handle */
    uint32_t nb_msg;            /**< @brief Current number of messages in buffer */
} bufferDynamicConf_t;

/*************************** Variables Declarations **************************/

/*************************** Functions Declarations **************************/

bufferStatus_t CreateBuffers(void);
bufferStatus_t WriteBuffer(bufferRef_t buffer, bufferMsgAddr_t msg, bufferSize_t length);
bufferStatus_t ReadBuffer(bufferRef_t buffer, bufferMsgAddr_t msg, bufferSize_t length);
bufferStatus_t GetBufferCount(bufferRef_t buffer, bufferDepth_t *count);

#endif /* BUFFERS_H */

/** 
 * @} 
 * @} 
 */