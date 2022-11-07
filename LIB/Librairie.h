/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Commande Librairie
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include "TypeDefs.h"

typedef struct
{
    uint8_t VMajor;                  /*!< ??? */
    uint8_t VMinor;                 /*!< ??? */
    uint8_t VPatch;                  /*!< ??? */

}
LIB_VERSION;

#ifdef ODALID_LIB_EXPORTS
    #ifdef _WIN32
        #define ODALID_LIB __declspec(dllexport)                /**< ???. */
        #define DllExport __declspec(dllexport)                 /**< ???. */
    #else
        #define ODALID_LIB                                      /**< ???. */
        #define DllExport                                       /**< ???. */
    #endif
#else
	#if (defined (__GNUC__))
        #define ODALID_LIB                                      /**< ???. */
	#else
        #define ODALID_LIB __declspec(dllimport)                /**< ???. */
	#endif
	#define DllExport
#endif

#endif /*LIBRAIRIE_H*/
