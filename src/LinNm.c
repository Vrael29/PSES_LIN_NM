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
#include "./../include/LinNm_Cbk.h"

/*====================================================================================================================*\
    Makra lokalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Typy lokalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne globalne
\*====================================================================================================================*/
const LinNm_ConfigType* LinNm_ConfigPtr;

/*[SWS_LinNm_00017]*/
LinNm_InternalType LinNm_Internal = {
    .InitStatus = LINNM_STATUS_UNINIT
};

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
/*[SWS_LinNm_00054]*/
void LinNm_Init(const LinNm_ConfigType* ConfigPtr) {
    LinNm_Internal_ChannelType* ChannelInternal;
    uint8_t channel;

    for (channel = 0; channel < LinNm_NumberOfLinNmChannels; channel++) {
        ChannelInternal = &LinNm_Internal.LinNmChannels[channel];
        /*[SWS_LinNm_00017]*/
        ChannelInternal->State = NM_STATE_UNINIT;
    }
    

    for (channel = 0; channel < LinNm_NumberOfLinNmChannels; channel++) {
        ChannelInternal = &LinNm_Internal.LinNmChannels[channel];
        /*[SWS_LinNm_00019]*/
        ChannelInternal->Mode = NM_MODE_BUS_SLEEP;
        /*[SWS_LinNm_00020]*/
        ChannelInternal->State = NM_STATE_BUS_SLEEP;
    }

    /*[SWS_LinNm_00102]*/
    if (LINNM_STATE_CHANGE_IND_ENABLED == STD_ON){
        //No callouts shall be made from the init function, since it is not known if the other module is initialized
    }

    LinNm_Internal = LINNM_STATUS_INIT;
}

/*[SWS_LinNm_00063]*/
Std_ReturnType LinNm_PassiveStartUp(NetworkHandleType NetworkHandle) {
    Std_ReturnType status = E_NOT_OK;
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

Nm_NetworkMode() {

}

Nm_BusSleepMode() {

}

Nm_StateChangeNotification() {

}




