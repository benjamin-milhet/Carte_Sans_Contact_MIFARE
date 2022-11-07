/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Fonction ISO14443A-3
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef SW_ISO14443A_3_H
#define SW_ISO14443A_3_H

#include "Librairie.h"
#include "TypeDefs.h"
#include "Hardware.h"

#if defined (__cplusplus)
extern "C" {
#endif

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ISO14443_3_A_PollCard(ReaderName *pName, uint8_t *atq, uint8_t *sak, uint8_t *uid, uint16_t *uid_len);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ISO14443_3_A_PollCardWU(ReaderName *pName, uint8_t *atq, uint8_t *sak, uint8_t *uid, uint16_t *uid_len);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ISO14443_3_A_Halt(ReaderName *pName);

#if defined (__cplusplus)
}
#endif

#endif /*SW_ISO14443A_3_H*/
