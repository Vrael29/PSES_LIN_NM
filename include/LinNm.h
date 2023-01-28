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




/*====================================================================================================================*\
    Kod globalnych funkcji inline i makr funkcyjnych
\*====================================================================================================================*/


#endif /* LINNM_H_ */
