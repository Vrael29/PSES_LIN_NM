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
#include "./../include/nm.h"

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
    const LinNm_ChannelConfigType* LinNmChannelsconf;
    LinNm_Internal_ChannelType* ChannelInternal;
    uint8_t channel;
	uint8_t error_code = 0;

    for (channel = 0; channel < LinNm_NumberOfLinNmChannels; channel++) {
        ChannelInternal = &LinNm_Internal.LinNmChannels[channel];
        /*[SWS_LinNm_00017]*/
        ChannelInternal->State = NM_STATE_UNINIT;
    }
    

    for (channel = 0; channel < LinNm_NumberOfLinNmChannels; channel++) {
        ChannelInternal = &LinNm_Internal.LinNmChannels[channel];
        /*[SWS_LinNm_00020]*/
        ChannelInternal->Mode = NM_MODE_BUS_SLEEP;
        /*[SWS_LinNm_00018][SWS_LinNm_00019]*/
        ChannelInternal->State = NM_STATE_BUS_SLEEP;
    }

    /*[SWS_LinNm_00102]*/
    if (LINNM_STATE_CHANGE_IND_ENABLED == STD_ON) {
        //No callouts shall be made from the init function, since it is not known if the other module is initialized
    }

    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
}

/*[SWS_LinNm_00063]*/
Std_ReturnType LinNm_PassiveStartUp(NetworkHandleType NetworkHandle) {
    LinNm_Internal_ChannelType* ChannelInternal = &LinNm_Internal.LinNmChannels[NetworkHandle];
   
    Std_ReturnType status = E_OK;

    /*[SWS_LinNm_00022]*/
    if (ChannelInternal->Mode == NM_MODE_NETWORK) {
        status = E_NOT_OK;
    }


    if (ChannelInternal->Mode == NM_MODE_BUS_SLEEP) {
        /*[SWS_LinNm_00161]*/
        ChannelInternal->Mode = NM_MODE_NETWORK;
        /*[SWS_LinNm_00160]*/
        ChannelInternal->State = NM_STATE_NORMAL_OPERATION;
        Nm_NetworkMode(NetworkHandle);
        if (LINNM_REMOTE_SLEEP_INDICATION_ENABLED == STD_ON) {
            Nm_RemoteSleepIndication(NetworkHandle);
        }
        /*[SWS_LinNm_00061]*/
        if (LINNM_STATE_CHANGE_IND_ENABLED == STD_ON) {
            Nm_StateChangeNotification(NetworkHandle, NM_STATE_BUS_SLEEP, NM_STATE_NORMAL_OPERATION);
        }
    } else {
        /*[SWS_LinNm_00064]*/
        status = E_NOT_OK;
    }
    /*[SWS_LinNm_00006]*/

    /* ----- Development Error Report -------------------------------- */

    return status;
}

/*[SWS_LinNm_00055]*/
Std_ReturnType LinNm_NetworkRequest(NetworkHandleType NetworkHandle) {	
    LinNm_Internal_ChannelType* ChannelInternal = &LinNm_Internal.LinNmChannels[NetworkHandle];
	uint8_t error_code = LINNM_E_NO_ERROR;
	
	/*[SWS_LinNm_00158]*/
	if (LINNM_PASSIVE_MODE_ENABLED == STD_ON){
		return E_NOT_OK;
	}
	
	/*[SWS_LinNm_00034]*/
	if (LINNM_DEV_ERROR_DETECT == STD_ON){
		/*[SWS_LinNm_00029]*/
		if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
			return E_NOT_OK;
		}
		/*[SWS_LinNm_00029][SWS_LinNm_00053]*/
		if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT){
			/*[SWS_LinNm_00037]*/
			error_code |= LINNM_E_UNINIT;
			return E_NOT_OK;
		}
	}
	
	if (LINNM_DEV_ERROR_REPORT == STD_ON){
		if (error_code != LINNM_E_NO_ERROR){
			Det_ReportError( LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_NETWORKREQUEST, error_code);
		}
	}

    Std_ReturnType status = E_OK;

    if (ChannelInternal->Mode == NM_MODE_BUS_SLEEP && LinNm_Internal.InitStatus == LINNM_STATUS_INIT) {
        /*[SWS_LinNm_00162]*/
        ChannelInternal->Mode = NM_MODE_NETWORK;
        /*[SWS_LinNm_00015]*/
        ChannelInternal->State = NM_STATE_NORMAL_OPERATION;
		/*[SWS_LinNm_00006][SWS_LinNm_00008]*/
        Nm_NetworkMode(NetworkHandle);
		/*[SWS_LinNm_00141]*/
		if (LINNM_REMOTE_SLEEP_INDICATION_ENABLED == STD_ON) {
            Nm_RemoteSleepIndication(NetworkHandle);
        }
        /*[SWS_LinNm_00061]*/
        if (LINNM_STATE_CHANGE_IND_ENABLED == STD_ON) {
            Nm_StateChangeNotification(NetworkHandle, NM_STATE_BUS_SLEEP, NM_STATE_NORMAL_OPERATION);
        }
    } else {
        /*[SWS_LinNm_00156][SWS_LinNm_00025]*/
        status = E_NOT_OK;
    }

    return status;
}

/*[SWS_LinNm_00056]*/
Std_ReturnType LinNm_NetworkRelease(NetworkHandleType NetworkHandle) {
    LinNm_Internal_ChannelType* ChannelInternal = &LinNm_Internal.LinNmChannels[NetworkHandle];
	uint8_t error_code = 0;
	
	/*[SWS_LinNm_00159]*/
	if (LINNM_PASSIVE_MODE_ENABLED == STD_ON){
		return E_NOT_OK;
	}
	
	/*[SWS_LinNm_00034]*/
	if (LINNM_DEV_ERROR_DETECT == STD_ON){
		/*[SWS_LinNm_00029]*/
		if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
			return E_NOT_OK;
		}
		/*[SWS_LinNm_00029][SWS_LinNm_00058]*/
		if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT){
			/*[SWS_LinNm_00037]*/
			error_code |= LINNM_E_UNINIT;
			return E_NOT_OK;
		}
	}
	
	if (LINNM_DEV_ERROR_REPORT == STD_ON){
		if (error_code != LINNM_E_NO_ERROR){
			Det_ReportError( LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_NETWORKRELEASE, error_code);
		}
	}
	
    Std_ReturnType status = E_OK;

    if (ChannelInternal->Mode == NM_MODE_NETWORK) {
        /*[SWS_LinNm_00004]*/
        ChannelInternal->Mode = NM_MODE_BUS_SLEEP;
        /*[SWS_LinNm_00016]*/
        ChannelInternal->State = NM_STATE_BUS_SLEEP;
		/*[SWS_LinNm_00006][SWS_LinNm_00012]*/
        Nm_BusSleepMode(NetworkHandle);
        /*[SWS_LinNm_00061]*/
        if (LINNM_STATE_CHANGE_IND_ENABLED == STD_ON) {
            Nm_StateChangeNotification(NetworkHandle, NM_STATE_NORMAL_OPERATION , NM_STATE_BUS_SLEEP);
        }
    } else {
        /*[SWS_LinNm_00157][SWS_LinNm_00025]*/
        status = E_NOT_OK;
    }

    return status;
}

/*[SWS_LinNm_00106]*/
void LinNm_GetVersionInfo(Std_VersionInfoType* versioninfo) {

    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        if (versioninfo == NULL) {
            /*[SWS_LinNm_00163] */
            /*If development error detection is enabled and the input 
            argument versioninfo has null pointer then the service LinNm_GetVersionInfo() shall 
            report an error LINNM_E_PARAM_POINTER to Default Error Tracer and return 
            without any action*/
            //Error code
        }
    }

    versioninfo->vendorID = LINNM_VENDOR_ID;
    versioninfo->moduleID = LINNM_MODULE_ID;
    versioninfo->sw_major_version = LINNM_AR_RELEASE_MAJOR_VERSION;
    versioninfo->sw_minor_version = LINNM_AR_RELEASE_MINOR_VERSION;
    versioninfo->sw_patch_version = LINNM_AR_RELEASE_REVISION_VERSION;

    /* ----- Development Error Report -------------------------------- */

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
    Std_ReturnType status = E_NOT_OK;
    return status;
}

Std_ReturnType LinNm_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr) {
    Std_ReturnType status = E_OK;

    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        if (nmStatePtr == NULL && nmModePtr == NULL) {
            /*[SWS_LinNm_00048] */
            //Error code LINNM_E_PARAM_POINTER
        }
    }

    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        if (LinNm_Internal.InitStatus == NM_STATE_UNINIT){
            /** [SWS_LinNm_00136] */
            //Error code LINNM_E_UNINIT
        }
    }

    *nmStatePtr = LinNm_Internal.LinNmChannels[nmNetworkHandle].State;
    *nmModePtr  = LinNm_Internal.LinNmChannels[nmNetworkHandle].Mode;

    /* ----- Development Error Report -------------------------------- */

    return status;
}

Std_ReturnType LinNm_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {
	/*[SWS_LinNm_00178]*/
    Std_ReturnType status = E_NOT_OK;
    return status;
}

void LinNm_TxConfirmation(PduIdType TxPduId, Std_ReturnType result) {

}

void LinNm_MainFunction(void){
	
}

Nm_NetworkMode() {

}

Nm_BusSleepMode() {

}

Nm_StateChangeNotification() {

}




