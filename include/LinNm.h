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

#define LINNM_MODULE_ID						0x00
#define LINNM_INSTANCE_ID					0x00

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

void LinNm_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void LinNm_MainFunction(void);


/*====================================================================================================================*\
    Kod globalnych funkcji inline i makr funkcyjnych
\*====================================================================================================================*/


#endif /* LINNM_H_ */
