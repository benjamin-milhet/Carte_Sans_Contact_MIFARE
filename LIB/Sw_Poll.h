/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Fonction AutoReader
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef SW_POLL_H
#define SW_POLL_H

#include "Librairie.h"
#include "TypeDefs.h"
#include "Hardware.h"
#include "Sw_ISO14443-4.h"

#if defined (__cplusplus)
extern "C" {
#endif

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t RF_Poll(ReaderName *pName, uint8_t *Send, uint16_t SendLen, uint8_t *Recv, uint16_t *RecvLen, uint16_t TimeOut);

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t RF_Find(ReaderName *pName, uint8_t Type, ISO14443_INFO *pISO14443_Info, uint8_t *uid, uint16_t *uid_len, uint8_t *info, uint16_t *info_len);

#if defined (__cplusplus)
}
#endif

#endif /*SW_POLL_H*/
