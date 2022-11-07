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

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#if defined(__GNUC__ )
    #include <stdint.h>
#else
/** \defgroup Type
* \brief Type definition
* @{
*/

///** \brief
//*	BOOL
//*/
///*@{*/
//typedef unsigned int           BOOL;
///*@}*/

/** \brief 
*	8 bit non signÃ©
*/
/*@{*/
typedef unsigned char           uint8_t;
/*@}*/

/** \brief 
*	16 bit non signÃ©
*/
/*@{*/
typedef unsigned short          uint16_t;
/*@}*/

/** \brief
*	32 bit non signÃ©
*/
/*@{*/
typedef unsigned long int       uint32_t;
/*@}*/

/** \brief
*	64 bit non signÃ©
*/
/*@{*/
typedef unsigned long long int  uint64_t;
/*@}*/

/** \brief
*	8 bit signÃ©
*/
/*@{*/
typedef signed char             int8_t;
/*@}*/

/** \brief
*	16 bit signÃ©
*/
/*@{*/
typedef short                   int16_t;
/*@}*/

/** \brief
*	32 bit signÃ©
*/
/*@{*/
typedef long int                int32_t;
/*@}*/

/** \brief
*	64 bit signÃ©
*/
/*@{*/
typedef long long int           int64_t;
/*@}*/

/** @}
* fin
*/
#endif

#ifdef _WIN32
    #include <winsock2.h>
#else
    typedef uint8_t BOOL;
    typedef int16_t SOCKET;
    typedef int16_t HANDLE;
    #ifndef TRUE
        #define TRUE 1
    #endif
    #ifndef FALSE
       #define FALSE 0
    #endif
#endif

#endif /*TYPEDEFS_H*/
