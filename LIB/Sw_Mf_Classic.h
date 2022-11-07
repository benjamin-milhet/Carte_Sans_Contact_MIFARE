/*
*
* Copyright (c) 2009-2021 ODALID - https://odalid.com
*
*/

/** \file
* Fonction Mf_Classic
* \author Vincent T.
* \version 0.1
* \date 18 Novembre 2021
*
*/

#ifndef SW_MF_CLASSIC_H
#define SW_MF_CLASSIC_H

#include "Librairie.h"
#include "TypeDefs.h"
#include "Hardware.h"

#if defined (__cplusplus)
extern "C" {
#endif
			
//Valid access conditions for Bc0, Bc1 and Bc2
#define ACC_BLOCK_TRANSPORT     0x00                            /**< ???. */
#define ACC_BLOCK_READWRITE     0x04                            /**< ???. */
#define ACC_BLOCK_VALUE         0x06                            /**< ???. */
//Valid access conditions for Bc3
#define ACC_AUTH_TRANSPORT      0x01                            /**< ???. */
#define ACC_AUTH_NORMAL         0x03                            /**< ???. */

#define AuthKeyA				TRUE                            /**< ???. */
#define AuthKeyB				FALSE                           /**< ???. */

/**
* \brief Chargement des clés MIFARE dans l’EEPROM du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_LoadKey(
										ReaderName *pName, 		/**< [In] Information sur le lecteur. */
										BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */
										uint8_t *pKey, 			/**< [In] pKey[6] Clé */
										uint8_t KeyIndex		/**< [In] Index de l’EEPROM (0 à 15). */
										);

/**
* \brief Chargement des clés MIFARE dans l’EEPROM du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/				
ODALID_LIB int16_t Mf_Classic_LoadKey2(
										ReaderName *pName,  	/**< [In] Information sur le lecteur. */
										uint8_t *pKeyA,			/**< [In] pKeyA[6] Clé A */
										uint8_t *pKeyB,			/**< [In] pKeyB[6] Clé B  */
										uint8_t KeyIndex		/**< [In] Index de l’EEPROM (0 à 15). */
										);

/**
* \brief Chargement des clés MIFARE dans l’EEPROM du lecteur
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/			
ODALID_LIB int16_t Mf_Classic_PersonalizeUID(
												ReaderName *pName, 		/**< [In] Information sur le lecteur. */ 
												uint8_t Type			/**< [In] ???. */ 
												);

/**
* \brief Phase d'Authentification pour la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Authenticate(
											ReaderName *pName, 		/**< [In] Information sur le lecteur. */ 
											BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
											BOOL internal_Key,  	/**< [In] Authentification via les clés contenues dans le lecteur TRUE -> OK ou FALSE -> utilisation de la chaîne Key. */
											uint8_t Sector,  		/**< [In] secteur de la carte MIFARE Classic 1K (0 à 15) / MIFARE Classic 4K (0 à 39). */
                                            uint8_t *pKey,  		/**< [In] pKey[6] Clé ignorée si internal_Key = TRUE. */
											uint8_t KeyIndex	 	/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
											);
											
/**
* \brief Lecture d’un Block de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Read_Block(
											ReaderName *pName, 		/**< [In] Information sur le lecteur. */ 
											BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */ 
											uint8_t Block, 			/**< [In] Bloc de la carte MIFARE. */ 
                                            uint8_t *pData,			/**< [Out] pData[16] Données lu. */
											BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
											uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */ 
											);

/**
* \brief Écriture d’un Block de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Write_Block(
                                            ReaderName *pName,  	/**< [In] Information sur le lecteur. */
											BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */ 
											uint8_t Block, 			/**< [In] Bloc de la carte MIFARE. */
                                            uint8_t *pData, 		/**< [In] pData[16] Données à écrire. */
											BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
											uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
											);

/**
* \brief Lecture d’un Secteur de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Read_Sector(
                                            ReaderName *pName,  	/**< [In] Information sur le lecteur. */
											BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */
											uint8_t Sector, 		/**< [In] Secteur de la carte MIFARE. */
                                            uint8_t *pData, 		/**< [Out] pData[48] Données lu.. */
											BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
											uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
											);

/**
* \brief Ecriture d’un Secteur de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Write_Sector(
											ReaderName *pName, 		/**< [In] Information sur le lecteur. */
											BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */
											uint8_t Sector, 		/**< [In] Secteur de la carte MIFARE. */
											uint8_t *pData, 		/**< [In] pData[48] Données à écrire. */
											BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
											uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
											);

/**
* \brief Mise à jour des conditions d'accès et des clés de sécurité
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_UpdadeAccessBlock(
													ReaderName *pName,  	/**< [In] Information sur le lecteur. */
													BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */
													uint8_t Sector, 		/**< [In] Information sur le lecteur. */
													uint8_t OldKeyIndex, 	/**< [In] Information sur le lecteur. */
													uint8_t *pNewKeyA, 		/**< [In] pNewKeyA[6] Nouvelle Clé A. */
													uint8_t *pNewKeyB, 		/**< [In] pNewKeyB[6] Nouvelle Clé B. */
													uint8_t Bc0, 			/**< [In] Conditions d'accès pour le Block 0. */
													uint8_t Bc1, 			/**< [In] Conditions d'accès pour le Block 1. */
													uint8_t Bc2, 			/**< [In] Conditions d'accès pour le Block 2. */
													uint8_t Bc3, 			/**< [In] Conditions d'accès pour le Block 3. */
													BOOL AuthKey			/**< [In] Clé d'Authentification utilisé : AuthKeyA ou AuthKeyB. */ 
													);

/**
* \brief Lecture de la Value contenue dans le Block de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Read_Value(
											ReaderName *pName,  	/**< [In] Information sur le lecteur. */
											BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */
											uint8_t Block, 			/**< [In] Bloc de la carte MIFARE. */ 
											uint32_t *pValue, 		/**< [In] Valeur lue. */ 
											BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
											uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
											);

/**
* \brief Écriture d'une Value dans un Block de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Write_Value(
											ReaderName *pName, 		/**< [In] Information sur le lecteur. */
											BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */
											uint8_t Block, 			/**< [In] Bloc de la carte MIFARE. */ 
											uint32_t Value, 		/**< [In] Valeur à écrire. */ 
											BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
											uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
											);

/**
* \brief Incrément de la Value du Block de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Increment_Value(
												ReaderName *pName,		/**< [In] Information sur le lecteur. */
												BOOL Auth,				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */ 
												uint8_t Block, 			/**< [In] Bloc de la carte MIFARE. */ 
												uint32_t Value, 		/**< [In] Valeur d'incrémentation. */ 
												uint8_t trans_Block, 	/**< [In] Bloc dans lequel la Value sera transmise. */ 
												BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
												uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
												);

/**
* \brief Décrémentation du Block de la carte MIFARE Classic
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Decrement_Value(
												ReaderName *pName, 		/**< [In] Information sur le lecteur. */
												BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */
												uint8_t Block, 			/**< [In] Bloc de la carte MIFARE. */ 
												uint32_t Value, 		/**< [In] Valeur de décrémentation. */ 
												uint8_t trans_Block, 	/**< [In] Bloc dans lequel la Value sera transmise. */ 
												BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
												uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
												);

/**
* \brief Restauration de la Value
* \return Status code
* \retval #MI_OK Operation successful ou erreur
*/
ODALID_LIB int16_t Mf_Classic_Restore_Value(
												ReaderName *pName,		/**< [In] Information sur le lecteur. */
												BOOL Auth, 				/**< [In] Authentification automatique TRUE -> Authentification automatique dans le lecteur FALSE -> pas d’Authentification automatique. */
												uint8_t Block, 			/**< [In] Bloc de la carte MIFARE. */ 
												uint8_t trans_Block, 	/**< [In] Bloc dans lequel la Value sera transmise. */
												BOOL AuthKey, 			/**< [In] Clé d'Authentification AuthKeyA ou AuthKeyB. */ 
												uint8_t KeyIndex		/**< [In] Index de la clé stocké en interne dans le coupleur (0 à 15) ignorée si internal_Key = FALSE. */
												);

#if defined (__cplusplus)
}
#endif

#endif /*SW_MF_CLASSIC_H*/
