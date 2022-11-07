/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Fonction ODALID
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef SW_DEVICE_H
#define SW_DEVICE_H

#include "TypeDefs.h"
#include "Hardware.h"
#include "Librairie.h"

#if defined (__cplusplus)
extern "C" {
#endif

#define ReaderTCP           1                            /**< ???. */
#define ReaderCDC           2                            /**< ???. */
#define ReaderPCSC          3                            /**< ???. */

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t GetLibraryExtension(
                                        LIB_VERSION *Version
                                        );

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t OpenCOM(
							ReaderName *pName
							);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t CloseCOM(
								ReaderName *pName
								);

/**
* \brief ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t GestionDeconnection(
										ReaderName *pName, 
										int16_t statusconnection, 
										uint8_t nbreconnection
										);

#define LED_ON              0x17                            /**< ???. */
#define LED_OFF             0x00                            /**< ???. */
#define LED_GREEN_OFF       0x00                            /**< ???. */
#define LED_GREEN_ON        LED3_ON                         /**< ???. */
#define LED_YELLOW_OFF      0x00                            /**< ???. */
#define LED_YELLOW_ON       LED2_ON                         /**< ???. */
#define LED_RED_OFF         0x00                            /**< ???. */
#define LED_RED_ON          LED1_ON                         /**< ???. */
#define BUZZER_OFF          0x00                            /**< ???. */
#define BUZZER_ON           0x08                            /**< ???. */
#define GACHE1_OFF          0x00                            /**< ???. */
#define GACHE1_ON           LED1_ON                         /**< ???. */
#define GACHE2_OFF          0x00                            /**< ???. */
#define GACHE2_ON           LED2_ON                         /**< ???. */
#define GACHE3_OFF          0x00                            /**< ???. */
#define GACHE3_ON           LED3_ON                         /**< ???. */
#define GACHE4_OFF          0x00                            /**< ???. */
#define GACHE4_ON           LED4_ON                         /**< ???. */
#define LED1_ON             0x01                            /**< ???. */
#define LED2_ON             0x02                            /**< ???. */
#define LED3_ON             0x04                            /**< ???. */
#define LED4_ON             0x10                            /**< ???. */



/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB char* GetErrorMessage(
									int16_t status
									);

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Version(
							ReaderName *pName
							);

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Get_Property(
									ReaderName *pName, 
									uint8_t AddReg, 
									uint8_t *Reg
									);

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Set_Property(
									ReaderName *pName, 
									uint8_t AddReg, 
									uint8_t Reg	
									);
									
/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t RF_Power_Control(
										ReaderName *pName, 
										BOOL RFOnOff, 
										uint8_t Delay
										);
										
/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t RF_Config_Card_Mode(ReaderName *pName, uint8_t Type);

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Boot(ReaderName *pName);

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t LEDBuzzer(ReaderName *pName, uint8_t LEDBuzzer);

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t LCD(ReaderName *pName, uint8_t line, char *Send);

//#define KeepIV                  0x0004

//#define DESFire4                0x0000
//#define ISO_TDEA16              0x0008
//#define MIFARE                  0x0010
//#define TTDEA                   0x0018
//#define AES_128                 0x0020
//#define AES_192                 0x0028
//#define ISO_TDEA32              0x0030
//#define AES_256                 0x0038
//#define AES_128LRP              0x0040

//#define PLKey                   0x0080
//#define AuthKey                 0x0100
//#define DisableKeyEntry         0x0200
//#define LockKey                 0x0400
//#define DisableWritingKeyPICC   0x0800
//#define DisableDecryption       0x1000
//#define DisableEncryption       0x2000
//#define DisableVerifyMAC        0x4000
//#define DisableGenerateMAC      0x8000

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB uint8_t ByteToBcd(uint8_t input);

/**
* \brief Fonction permettant de generer le CRC A
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB uint8_t BcdToByte(uint8_t input);

/**
* \brief Fonction ???
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
int16_t ChercherCDC(ReaderName *pName);

#if defined (__cplusplus)
}
#endif

#endif /*SW_DEVICE_H*/
