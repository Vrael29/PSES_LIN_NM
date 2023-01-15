/**===================================================================================================================*\
  @file Lib_Calc.c

  @brief Bibiloteka Lib_Calc - implementacja
  
  Implementacja funkcjonalności podstawowej kalkukatora 4-działaniowego z pamięcią.

  @see Lib_Calc.pdf
\*====================================================================================================================*/

/*====================================================================================================================*\
    Załączenie nagłówków
\*====================================================================================================================*/
#include "./../include/LinNm.h"

/*====================================================================================================================*\
    Makra lokalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Typy lokalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne globalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne lokalne (statyczne)
\*====================================================================================================================*/

/*====================================================================================================================*\
    Deklaracje funkcji lokalnych
\*====================================================================================================================*/

/*====================================================================================================================*\
    Kod globalnych funkcji inline i makr funkcyjnych
\*====================================================================================================================*/

/*====================================================================================================================*\
    Kod funkcji
\*====================================================================================================================*/

void LinNm_Init( const LinNm_ConfigType* ConfigPtr ) {

}


Std_ReturnType LinNm_PassiveStartUp( NetworkHandleType NetworkHandle ) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_NetworkRequest(NetworkHandleType nmChannelHandle) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_NetworkRelease(NetworkHandleType nmChannelHandle) {
    Std_ReturnType status = E_OK;
    return status;
}

void LinNm_GetVersionInfo(Std_VersionInfoType* versioninfo) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_RequestBusSynchronization(NetworkHandleType nmChannelHandle) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_CheckRemoteSleepIndication(NetworkHandleType nmChannelHandle, boolean* nmRemoteSleepIndPtr) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_SetSleepReadyBit(NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_DisableCommunication(NetworkHandleType NetworkHandle) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_EnableCommunication(NetworkHandleType NetworkHandle) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_SetUserData(NetworkHandleType NetworkHandle, const uint8* nmUserDataPtr) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_GetUserData(NetworkHandleType NetworkHandle, uint8* nmUserDataPtr) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_GetPduData(NetworkHandleType NetworkHandle, uint8* nmPduData) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_RepeatMessageRequest(NetworkHandleType NetworkHandle) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_GetNodeIdentifier(NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_GetLocalNodeIdentifier(NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr) {
    Std_ReturnType status = E_OK;
    return status;
}

Std_ReturnType LinNm_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {
    Std_ReturnType status = E_OK;
    return status;
}

void LinNm_TxConfirmation(PduIdType TxPduId, Std_ReturnType result) {

}



