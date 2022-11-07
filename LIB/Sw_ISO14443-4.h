/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Commande ISO14443-4
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef SW_ISO14443_4_H
#define SW_ISO14443_4_H

#include "Librairie.h"
#include "TypeDefs.h"
#include "Hardware.h"

#if defined (__cplusplus)
extern "C" {
#endif

/* Max number of CID (0 to 14 = 15) */
#define TCL_CID_COUNT     15

/* Mark that we do not use CID */
#define TCL_UNUSED_CID    0xFF
/* Mark that we do not use NAD */
#define TCL_UNUSED_NAD    0xFF

/* Identification of a T=CL card into type A SAK */
#define PICC_SAK_ISO4     0x20

/* Identification of a NFCIP-1 object into type A SAK */
#define PICC_SAK_NFCIP1   0x40

/* Type mask in Block header */
#define PCB_Block_MASK    0xC2

/* Block type is I */
#define PCB_IS_I_Block    0x02
/* Block type is R */
#define PCB_IS_R_Block    0x82
/* Block type is S */
#define PCB_IS_S_Block    0xC2

/* Define a new I Block */
#define PCB_MK_I_Block    0x02
/* Define a new R Block */
#define PCB_MK_R_Block    0xA2
/* Define a new S Block */
#define PCB_MK_S_Block    0xC2

/* Chaining indicator in Block header */
#define PCB_CHAINING      0x10
/* CID indicator in Block header */
#define PCB_CID_FOLLOWING 0x08

/* NAD indicator in Block header */
#define PCB_NAD_FOLLOWING 0x04

/* ACK indicator in R Block header */
#define PCB_R_ACK         0x00
/* NAK indicator in R Block header */
#define PCB_R_NAK         0x10

/* DESELECT indicator in S Block header */
#define PCB_S_DESELECT    0x00
/* WTX indicator in S Block header */
#define PCB_S_WTX         0x30


typedef struct
{
    uint8_t  Type;                                      /**< ???. */
    uint8_t  Cid;                                       /**< ???. */
    uint8_t  Nad;                                       /**< ???. */
    uint8_t  Fci;                                       /**< ???. */
    uint8_t  glob_Block_num;                            /**< ???. */
    uint32_t current_Aid;						  		/**< ???. */
}
ISO14443_INFO;

/**
* \brief Fonction permettant de générer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
void InitISO144443_4(ISO14443_INFO *pISO14443_Info);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ISO14443_4_A_RATS(
										ReaderName *pName, 
										ISO14443_INFO *pISO14443_Info, 
										uint8_t CID, 
										uint8_t *ATS, 
										uint16_t *ATSLen
										);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ISO14443_4_A_PPS(
										ReaderName *pName, 
										ISO14443_INFO *pISO14443_Info, 
										uint8_t dsi, 
										uint8_t dri
										);

/**
* \brief Fonction permettant de générer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ISO14443_4_Deselect(
										ReaderName *pName, 
										ISO14443_INFO *pISO14443_Info
										);


/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t ISO14443_4_Transparent(
											ReaderName *pName, 
											ISO14443_INFO *pISO14443_Info, 
											uint8_t *CmdADPU, 
											uint16_t CmdADPULen, 
											uint8_t *RespADPU, 
											uint16_t *lenRespADPU
											);

/**
* \brief Fonction permettant de générer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t TclA_LowExchange(
                            ReaderName *pName, 
							uint8_t *pSendData, 
							uint16_t SendLen, 
							uint8_t *pRecvData, 
							uint16_t *pRecvLen, 
							uint32_t TimeOut
							);

/**
* \brief Fonction permettant de générer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t TclB_LowExchange(
							ReaderName *pName, 
							uint8_t *pSendData, 
							uint16_t SendLen, 
							uint8_t *pRecvData, 
							uint16_t *pRecvLen, 
							uint32_t TimeOut
							);

/**
* \brief Fonction permettant de générer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t TclA_Exchange(
						ReaderName *pName, 
                        ISO14443_INFO *pISO14443_Info,
						uint8_t *pSendData, 
						uint16_t SendLen, 
						uint8_t *pRecvData, 
						uint16_t *pRecvLen
						);

/**
* \brief Fonction permettant de générer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t TclB_Exchange(
						ReaderName *pName, 
                        ISO14443_INFO *pISO14443_Info,
						uint8_t *pSendData, 
						uint16_t SendLen, 
						uint8_t *pRecvData, 
						uint16_t *pRecvLen
						);

/**
* \brief Fonction permettant de générer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t Tcl_Exchange(
						ReaderName *pName, 
                        ISO14443_INFO *pISO14443_Info,
						uint8_t *pSendData, 
						uint16_t SendLen, 
						uint8_t *pRecvData, 
						uint16_t *pRecvLen
						);

#if defined (__cplusplus)
}
#endif

#endif /*SW_ISO14443_4_H*/
