/**
 * @file    equipments_types.h
 * @author  Merlin Kooshmanian
 * @brief   Common types declaration for EQUIPMENTS
 * @date    13/02/2024
 *
 * @copyright Copyright (c) Merlin Kooshmanian 2024
 */

#ifndef EQUIPMENTS_TYPES_H
#define EQUIPMENTS_TYPES_H

/******************************* Include Files *******************************/

#include <stdint.h>

/***************************** Types Definitions *****************************/

/**
 * @enum    equipmentsStatus_t
 * @brief   EQUIPMENTS equipments functions specific returns
 */
typedef enum
{
    EQUIPMENTS_SUCCESSFUL            = 0u,    /**< Function succeed */
    EQUIPMENTS_ERROR                 = 1u,    /**< Function failed */
    EQUIPMENTS_INVALID_PARAM         = 2u,    /**< Function parameter is not valid */
    EQUIPMENTS_TIMEOUT               = 3u,    /**< Function returned a timeout */
} equipmentsStatus_t;

#endif /* EQUIPMENTS_TYPES_H */