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
/*[SWS_LinNm_00172]*/
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
    uint8_t error_code = LINNM_E_NO_ERROR;
    Std_ReturnType status = E_OK;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
		if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
			return E_NOT_OK;
        /*[SWS_LinNm_00025]*/
        /*[SWS_LinNm_00065]*/
		} else if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
            return E_NOT_OK;
        }
        
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON){
		if (error_code != LINNM_E_NO_ERROR){
			Det_ReportError( LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_PASSIVESTARTUP, error_code);
		}
	}

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
        /*[SWS_LinNm_00141] */
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
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (versioninfo == NULL) {
            /*[SWS_LinNm_00163] */
            error_code |= LINNM_E_PARAM_POINTER;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR ){
			Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_GETVERSIONINFO, error_code);
		}
	}

    versioninfo->vendorID = LINNM_VENDOR_ID;
    versioninfo->moduleID = LINNM_MODULE_ID;
    versioninfo->sw_major_version = LINNM_AR_RELEASE_MAJOR_VERSION;
    versioninfo->sw_minor_version = LINNM_AR_RELEASE_MINOR_VERSION;
    versioninfo->sw_patch_version = LINNM_AR_RELEASE_REVISION_VERSION;

}

/*[SWS_LinNm_00091]*/
#if (LINNM_PASSIVE_MODE_ENABLED == STD_OFF && LINNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)
/*[SWS_LinNm_00089]*/
Std_ReturnType LinNm_RequestBusSynchronization(NetworkHandleType NetworkHandle) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
		if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00025][SWS_LinNm_00090]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR ){
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_REQUESTBUSSYNCHRONIZATION, error_code);
        }
    }

    /*[SWS_LinNm_00042][SWS_LinNm_00095]*/
    return E_OK;
}
#endif

/*[SWS_LinNm_00096]*/
#if(LINNM_REMOTE_SLEEP_INDICATION_ENABLED == STD_ON)
/*[SWS_LinNm_00092]*/
Std_ReturnType LinNm_CheckRemoteSleepIndication(NetworkHandleType nmChannelHandle, boolean* nmRemoteSleepIndPtr) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
		if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00029]*/
        if (nmRemoteSleepIndPtr == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
        }
    }
    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00025][SWS_LinNm_00094]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_CHECKREMOTESLEEPIND, error_code);
        }
    }
    /*[SWS_LinNm_00093]*/
    return E_OK;
}
#endif

/*[SWS_LinNm_00176][SWS_LinNm_00169]*/
#if(LINNM_COORDINATOR_SYNC_SUPPORT == STD_ON)
/*[SWS_LinNm_00175]*/
Std_ReturnType LinNm_SetSleepReadyBit(NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
		if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00025]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_SETSLEEPREADYBIT, error_code);
        }
    }

    /*[SWS_LinNm_00177]*/
    return E_OK;
}
#endif

/*[SWS_LinNm_00110]*/
#if(LINNM_COM_CONTROL_ENABLED == STD_ON)
/*[SWS_LinNm_00108]*/
Std_ReturnType LinNm_DisableCommunication(NetworkHandleType NetworkHandle) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00025][SWS_LinNm_00109]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_DISABLECOMMUNICATION, error_code);
        }
    }

    return E_OK;
}
#endif
/*[SWS_LinNm_00113]*/
#if(LINNM_COM_CONTROL_ENABLED == STD_ON)
/*[SWS_LinNm_00111]*/
Std_ReturnType LinNm_EnableCommunication(NetworkHandleType NetworkHandle) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00025][SWS_LinNm_00112]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_ENABLECOMMUNICATION, error_code);
        }
    }

    return E_OK;
}
#endif

/*[SWS_LinNm_00116]*/
#if(LINNM_USER_DATA_ENABLED == STD_ON && LINNM_PASSIVE_MODE_ENABLED == STD_OFF && LINNM_COM_USER_DATA_SUPPORT == STD_OFF)
/*[SWS_LinNm_00114]*/
Std_ReturnType LinNm_SetUserData(NetworkHandleType NetworkHandle, const uint8* nmUserDataPtr) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00029]*/
        if (nmUserDataPtr == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
        }
        /*[SWS_LinNm_00025][SWS_LinNm_00115]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_SETUSERDATA, error_code);
        }
    }

    return E_OK;
}
#endif
/*[SWS_LinNm_00119]*/
#if(LINNM_USER_DATA_ENABLED == STD_ON)
/*[SWS_LinNm_00117]*/
Std_ReturnType LinNm_GetUserData(NetworkHandleType NetworkHandle, uint8* nmUserDataPtr) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00029]*/
        if (nmUserDataPtr == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
        }
        /*[SWS_LinNm_00025][SWS_LinNm_00118]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_GETUSERDATA, error_code);
        }
    }

    return E_OK;
}
#endif

/*[SWS_LinNm_00122]*/
#if(LINNM_NODE_ID_ENABLED == STD_ON || LINNM_USER_DATA_ENABLED == STD_ON)
/*[SWS_LinNm_00120]*/
Std_ReturnType LinNm_GetPduData(NetworkHandleType NetworkHandle, uint8* nmPduData) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00029]*/
        if (nmPduData == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
        }
        /*[SWS_LinNm_00025][SWS_LinNm_00121]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_GETPDUDATA, error_code);
        }
    }

    return E_OK;
}
#endif

/*[SWS_LinNm_00125]*/
#if(LINNM_NODE_DETECTION_ENABLED == STD_ON)
/*[SWS_LinNm_00123]*/
Std_ReturnType LinNm_RepeatMessageRequest(NetworkHandleType NetworkHandle) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00025][SWS_LinNm_00124]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_REPEATMESSAGEREQUEST, error_code);
        }
    }

    return E_OK;
}
#endif

/*[SWS_LinNm_00128]*/
#if(LINNM_NODE_ID_ENABLED == STD_ON)
/*[SWS_LinNm_00126]*/
Std_ReturnType LinNm_GetNodeIdentifier(NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00029]*/
        if (nmNodeIdPtr == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
        }
        /*[SWS_LinNm_00025][SWS_LinNm_00127]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_GETNODEIDENTIFIER, error_code);
        }
    }

    return E_OK;
}
#endif

/*[SWS_LinNm_00131]*/
#if(LINNM_NODE_ID_ENABLED == STD_ON)
/*[SWS_LinNm_00129]*/
Std_ReturnType LinNm_GetLocalNodeIdentifier(NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00029]*/
        if (nmNodeIdPtr == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
        }
        /*[SWS_LinNm_00025][SWS_LinNm_00130]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_GETLOCALNODEIDENTIFIER, error_code);
        }
    }

    return E_OK;
}
#endif

Std_ReturnType LinNm_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr) {
    Std_ReturnType status = E_OK;
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (nmStatePtr == NULL && nmModePtr == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
            return E_NOT_OK;
        }
        /*[SWS_LinNm_00029]*/
        if (nmNetworkHandle > LinNm_NumberOfLinNmChannels || nmNetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
			return E_NOT_OK;
        }
        /*[SWS_LinNm_00025][SWS_LinNm_00136]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
            return E_NOT_OK;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR ){
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_GETSTATE, error_code);
        }
    }

    *nmStatePtr = LinNm_Internal.LinNmChannels[nmNetworkHandle].State;
    *nmModePtr  = LinNm_Internal.LinNmChannels[nmNetworkHandle].Mode;

    return status;
}

/*[SWS_LinNm_00151]*/
#if(LINNM_COM_USER_DATA_SUPPORT == STD_ON)
/*[SWS_LinNm_00148]*/
Std_ReturnType LinNm_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {
    uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00029]*/
        if (NetworkHandle > LinNm_NumberOfLinNmChannels || NetworkHandle < 0){
			/*[SWS_LinNm_00038]*/
			error_code |= LINNM_E_INVALID_CHANNEL;
		}
        /*[SWS_LinNm_00029]*/
        if (PduInfoPtr == NULL) {
            error_code |= LINNM_E_PARAM_POINTER;
        }
        /*[SWS_LinNm_00025][SWS_LinNm_00150]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_TRANSMIT, error_code);
        }
    }
	/*[SWS_LinNm_00178]*/
    /*[SWS_LinNm_00149]*/
    return E_NOT_OK;
}
#endif


/*[SWS_LinNm_00153]*/
void LinNm_TxConfirmation(PduIdType TxPduId) {
     uint8_t error_code = LINNM_E_NO_ERROR;

    /*[SWS_LinNm_00034]*/
    if (LINNM_DEV_ERROR_DETECT == STD_ON) {
        /*[SWS_LinNm_00025][SWS_LinNm_00154]*/
        if (LinNm_Internal.InitStatus == LINNM_STATUS_UNINIT) {
            /*[SWS_LinNm_00037]*/
            error_code |= LINNM_E_UNINIT;
        }
    }

    if (LINNM_DEV_ERROR_REPORT == STD_ON) {
        if (error_code != LINNM_E_NO_ERROR) {
            Det_ReportError(LINNM_MODULE_ID, LINNM_INSTANCE_ID, LINNM_SID_TXCONFIRMATION, error_code);
        }
    }
}

void LinNm_MainFunction(void){
	
}

Nm_NetworkMode() {

}

Nm_BusSleepMode() {

}

Nm_StateChangeNotification() {

}




