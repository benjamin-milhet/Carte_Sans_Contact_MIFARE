/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Type definition
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef TOOLS_H
#define TOOLS_H

#include "TypeDefs.h"
#include <unistd.h>

#if defined (__cplusplus)
extern "C" {
#endif

#ifdef _WIN32
    #define DELAYS_MS(ms) Sleep ((ms))                              /**< ???. */
    #define DELAYS_S(sec) Sleep ((sec) * 1000)                      /**< ???. */
#else
    #define DELAYS_MS(ms) usleep ((ms) * 1000)                      /**< ???. */
    #define DELAYS_S(sec) sleep ((sec))                             /**< ???. */
#endif

#if defined (__cplusplus)
}
#endif

#endif /*TOOLS_H*/
