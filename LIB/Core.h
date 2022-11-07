/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Commande coupleur
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef CORE_H
#define CORE_H

#include "TypeDefs.h"
#include "Hardware.h"
#include "Librairie.h"
#include "Core_Version.h"

#if defined (__cplusplus)
extern "C" {
#endif

#define TIMEOUT_TRANSPRENT_TypeA        50                              /**< ???. */
#define TIMEOUT_TRANSPRENT_TypeB        50                              /**< ???. */
#define TIMEOUT_TRANSPRENT_TypeCTS      50                              /**< ???. */
#define TIMEOUT_TRANSPRENT_TypeST       50                              /**< ???. */
#define TIMEOUT_TRANSPRENT_TypeInno     50                              /**< ???. */
#define TIMEOUT_TRANSPRENT_Type15693    500                             /**< ???. */
#define TIMEOUT_TRANSPRENT_SAM          500                             /**< ???. */
#define TIMEOUT_ATR_SAM          		1500                            /**< ???. */
#define TIMEOUT_CMD_Poll				3000                            /**< ???. */


#define TIMEOUT_Version					300                             /**< ???. */
#define TIMEOUT_Rf_Power_Control		3000                            /**< ???. */
#define TIMEOUT_GET_Property			300                             /**< ???. */
#define TIMEOUT_SET_Property			300                             /**< ???. */
#define TIMEOUT_Config_Card_Mode		300                             /**< ???. */
#define TIMEOUT_LCD						300                             /**< ???. */
#define TIMEOUT_Boot                    300                             /**< ???. */
#define TIMEOUT_Led_Buzzer				300                             /**< ???. */
#define TIMEOUT_AutoReader				300                             /**< ???. */
#define TIMEOUT_SelectSlot_SAM			300                             /**< ???. */

#define TypeA                           0x01                            /**< ???. */
#define TypeB                           0x02                            /**< ???. */
#define TypeCTS                         0x08                            /**< ???. */
#define TypeST                          0x10                            /**< ???. */
#define TypeInno                        0x20                            /**< ???. */
#define Type15693                       0x40                            /**< ???. */

#define CRCA                            0x01                            /**< ???. */
#define CRCB                            0x02                            /**< ???. */


#define DataMem                         512                             /**< ???. */
#define BlockingEnabled                 FALSE                           /**< ???. */


/*=============================================================================
  Définition de constantes
=============================================================================*/
#define RX_SIZE                 4096                            /**< taille tampon d'entrée.  */
#define TX_SIZE                 4096                            /**< taille tampon de sortie. */
#define MAX_WAIT_READ_TO_BIT    1                            	/**< temps max d'attente pour lecture (en ms). */
#define MAX_WAIT_READ           3000                            /**< temps max d'attente pour lecture (en ms). */

#define CMD_Reset               0x01                            /**< ???. */
#define CMD_Version             0x02                            /**< ???. */
#define CMD_Rf_Power_Control    0x03                            /**< ???. */
#define CMD_Download_Request    0x04                            /**< ???. */
#define CMD_Led_Buzzer          0x05                            /**< ???. */
#define CMD_GET_Property        0x06                            /**< ???. */
#define CMD_SET_Property        0x07                            /**< ???. */
#define CMD_TRAMSMIT            0x08                            /**< ???. */
#define CMD_Poll                0x09                            /**< ???. */
#define CMD_Mifare              0x0A                            /**< ???. */
#define CMD_SelectSlot_SAM      0x13                            /**< ???. */
#define CMD_SAM_Management      0x14                            /**< ???. */
#define CMD_TRASMIT_SAM         0x15                            /**< ???. */
#define CMD_Config_Card_Mode    0x16                            /**< ???. */
#define CMD_Load_Key_Mifare     0x17                            /**< ???. */
#define CMD_LCD                 0x18                            /**< ???. */
#define CMD_Load_Key_Mifare2    0x19                            /**< ???. */
#define CMD_ATECC               0x1A                            /**< ???. */
#define CMD_AutoReader          0x30                            /**< ???. */
#define CMD_Wifi                0x31                            /**< ???. */
#define CMD_Reboot              0x32                            /**< ???. */

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t GetLibraryCore(LIB_VERSION *Version);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t Enc_Trame_coupleur(
							uint8_t PCB, 
							uint8_t *info_field, 
							uint16_t len_info_field, 
							uint8_t *Trame, 
							uint16_t *len_Trame
							);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/							
int16_t Dec_Trame_coupleur(
							uint8_t PCB, 
							uint8_t *Trame, 
							uint16_t len_Trame, 
							uint8_t *info_field, 
							uint16_t *len_info_field
							);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/						
int16_t TransmitCoupleur(
							ReaderName *pName, 
							uint8_t PCB, 
							uint8_t *info_field, 
							uint16_t len_info_field, 
							uint8_t *resp_info_field, 
							uint16_t *resp_len_info_field, 
							uint16_t TimeOut
							);
							
							/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t AutoReader_Transmit(ReaderName *pName, uint8_t *Send, uint16_t SendLen, uint8_t *Recv, uint16_t *RecvLen, uint16_t TimeOut);

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ATECC_Coupleur(ReaderName *pName, uint8_t *Send, uint16_t SendLen, uint8_t *Recv, uint16_t *RecvLen, uint16_t TimeOut);

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
#if !defined(ODALID_Education_LIBRARY)
ODALID_LIB
#endif
int16_t Mf_Transmit(ReaderName *pName, uint8_t *Send, uint16_t SendLen, uint8_t *Recv, uint16_t *RecvLen, uint16_t TimeOut);

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
#if !defined(ODALID_Education_LIBRARY)
ODALID_LIB
#endif
int16_t RF_TransmitCRC(ReaderName *pName, uint8_t *Send, uint16_t SendLen, uint8_t *Recv, uint16_t *RecvLen, uint16_t TimeOut, uint8_t CRC);

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t SAM_Transmit(ReaderName *pName, uint8_t *Send, uint16_t SendLen, uint8_t *Recv, uint16_t *RecvLen, uint16_t TimeOut);

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t ConnectReader(ReaderName *pName, uint8_t cmd, uint8_t *bSend, uint16_t *SendLen, uint8_t *bRecv, uint16_t *RecvLen);

/**
* \brief Mise à jour de l'heure du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
void PluginVitesse(ReaderName *pName, uint16_t V_ReadIntervalTimeout, uint16_t V_ReadTotalTimeoutConstant);



#if defined (__cplusplus)
}
#endif

#endif /*CMD_WIFI_H*/
