#ifndef LINNM_H_
#define LINNM_H_

/**===================================================================================================================*\
  @file LinNm.h

  @brief LIN Network Managment

  @see LinNm.pdf
\*====================================================================================================================*/

/*====================================================================================================================*\
    Załączenie nagłówków
\*====================================================================================================================*/
#include "Nm_Stack_Types.h"
#include "LinNm_ConfigTypes.h"

/*====================================================================================================================*\
    Defines
\*====================================================================================================================*/

/*[SWS_LinNm_00029]*/
#define LINNM_E_NO_ERROR					0x00
#define LINNM_E_UNINIT						0x01
#define LINNM_E_INVALID_CHANNEL				0x02
#define LINNM_E_PARAM_POINTER				0x12
#define LINNM_E_INIT_FAILED					0x13
#define LINNM_E_INVALID_PARAMETER			0x14

#define LINNM_INSTANCE_ID					0x00

/* ----- API service IDs ----- */
# define LINNM_SID_INIT_ID                          (0x00u) /*!< Service ID: LinNm_Init() */
# define LINNM_SID_PASSIVESTARTUP                   (0x01u) /*!< Service ID: LinNm_PassiveStartUp() */
# define LINNM_SID_NETWORKREQUEST                   (0x02u) /*!< Service ID: LinNm_NetworkRequest() */
# define LINNM_SID_NETWORKRELEASE                   (0x03u) /*!< Service ID: LinNm_NetworkRelease() */
# define LINNM_SID_DISABLECOMMUNICATION             (0x04u) /*!< Service ID: LinNm_DisableCommunication */
# define LINNM_SID_ENABLECOMMUNICATION              (0x05u) /*!< Service ID: LinNm_EnableCommunication */
# define LINNM_SID_SETUSERDATA                      (0x06u) /*!< Service ID: LinNm_SetUserData */
# define LINNM_SID_GETUSERDATA                      (0x07u) /*!< Service ID: LinNm_GetUserData */
# define LINNM_SID_GETPDUDATA                       (0x08u) /*!< Service ID: LinNm_GetPduData */
# define LINNM_SID_REPEATMESSAGEREQUEST             (0x09u) /*!< Service ID: LinNm_RepeatMessageRequest */
# define LINNM_SID_GETNODEIDENTIFIER                (0x0Au) /*!< Service ID: LinNm_GetNodeIdentifier */
# define LINNM_SID_GETLOCALNODEIDENTIFIER           (0x0Bu) /*!< Service ID: LinNm_GetLocalNodeIdentifier */
# define LINNM_SID_GETSTATE                         (0x0Eu) /*!< Service ID: LinNm_GetState */
# define LINNM_SID_TRANSMIT                         (0x0Fu) /*!< Service ID: LinNm_Transmit */
# define LINNM_SID_SETSLEEPREADYBIT                 (0x10u) /*!< Service ID: LinNm_SetSleepReadyBit */
# define LINNM_SID_TXCONFIRMATION                   (0x40u) /*!< Service ID: LinNm_TxConfirmation */
# define LINNM_SID_REQUESTBUSSYNCHRONIZATION        (0xC0u) /*!< Service ID: LinNm_RequestBusSynchronization */
# define LINNM_SID_CHECKREMOTESLEEPIND              (0xD0u) /*!< Service ID: LinNm_CheckRemoteSleepIndication */
# define LINNM_SID_GETVERSIONINFO                   (0xF1u) /*!< Service ID: LinNm_GetVersionInfo */

/*====================================================================================================================*\
    Makra globalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Typy globalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Eksport zmiennych globalnych
\*====================================================================================================================*/
extern const LinNm_ConfigType LinNm_ConfigData;

/*====================================================================================================================*\
    Deklaracje funkcji globalnych
\*====================================================================================================================*/
void LinNm_Init( const LinNm_ConfigType* ConfigPtr );

Std_ReturnType LinNm_PassiveStartUp( NetworkHandleType nmChannelHandle );

Std_ReturnType LinNm_NetworkRequest(NetworkHandleType nmChannelHandle);

Std_ReturnType LinNm_NetworkRelease(NetworkHandleType nmChannelHandle);

void LinNm_GetVersionInfo(Std_VersionInfoType* versioninfo);

Std_ReturnType LinNm_RequestBusSynchronization(NetworkHandleType nmChannelHandle);

Std_ReturnType LinNm_CheckRemoteSleepIndication(NetworkHandleType nmChannelHandle, boolean* nmRemoteSleepIndPtr);

Std_ReturnType LinNm_SetSleepReadyBit(NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit);

Std_ReturnType LinNm_DisableCommunication(NetworkHandleType NetworkHandle);

Std_ReturnType LinNm_EnableCommunication(NetworkHandleType NetworkHandle);

Std_ReturnType LinNm_SetUserData(NetworkHandleType NetworkHandle, const uint8* nmUserDataPtr);

Std_ReturnType LinNm_GetUserData(NetworkHandleType NetworkHandle, uint8* nmUserDataPtr);

Std_ReturnType LinNm_GetPduData(NetworkHandleType NetworkHandle, uint8* nmPduData);

Std_ReturnType LinNm_RepeatMessageRequest(NetworkHandleType NetworkHandle);

Std_ReturnType LinNm_GetNodeIdentifier(NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr);

Std_ReturnType LinNm_GetLocalNodeIdentifier(NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr);

Std_ReturnType LinNm_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);

Std_ReturnType LinNm_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

void LinNm_TxConfirmation(PduIdType TxPduId);

//void LinNm_MainFunction(void);


/*====================================================================================================================*\
    Kod globalnych funkcji inline i makr funkcyjnych
\*====================================================================================================================*/


#endif /* LINNM_H_ */
