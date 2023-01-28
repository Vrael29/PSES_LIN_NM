#ifndef LINNM_CONFIGTYPES_H_
#define LINNM_CONFIGTYPES_H_

#include "ComStack_Types.h"
#include "Nm_Stack_Types.h"

/*====================================================================================================================*\
    Defines
\*====================================================================================================================*/

/* [SRS_BSW_00397] */
#define LINNM_BUS_SYNCHRONIZATION_ENABLED       STD_OFF
#define LINNM_COM_CONTROL_ENABLED               STD_OFF
#define LINNM_COM_USER_DATA_SUPPORT             STD_OFF
#define LINNM_COORDINATOR_SYNC_SUPPORT          STD_OFF
#define LINNM_NODE_DETECTION_ENABLED            STD_OFF
#define LINNM_NODE_ID_ENABLED                   STD_OFF
#define LINNM_PASSIVE_MODE_ENABLED              STD_OFF
#define LINNM_REMOTE_SLEEP_INDICATION_ENABLED   STD_OFF
#define LINNM_STATE_CHANGE_IND_ENABLED          STD_OFF
#define LINNM_SYNCHRONIZATIONPOINT_ENABLED      STD_OFF
#define LINNM_USER_DATA_ENABLED                 STD_OFF
#define LINNM_VERSION_INFO_API                  STD_OFF

#define LINNM_DEV_ERROR_DETECT                  STD_OFF
#define LINNM_DEV_ERROR_REPORT                  STD_OFF

#define LinNm_NumberOfLinNmChannels             1u

#define LINNM_VENDOR_ID                         (30u)
#define LINNM_MODULE_ID                         (63u)
#define LINNM_AR_RELEASE_MAJOR_VERSION          (4u)
#define LINNM_AR_RELEASE_MINOR_VERSION          (0u)
#define LINNM_AR_RELEASE_REVISION_VERSION       (3u)


typedef enum {
    LINNM_STATUS_UNINIT,
    LINNM_STATUS_INIT
}LinNm_Internal_InitStatusType;

typedef struct {
    Nm_ModeType Mode;
    Nm_StateType State;
} LinNm_Internal_ChannelType;

typedef struct
{
    LinNm_Internal_InitStatusType InitStatus;
    LinNm_Internal_ChannelType LinNmChannels[LinNm_NumberOfLinNmChannels];
} LinNm_InternalType;

typedef struct
{
    const uint32 LinNmTimeoutTime;
    const boolean LinNmNodeDetectionEnabled;
    const boolean LinNmNodeIdEnabled;
    const NetworkHandleType LinNmComMNetworkHandleRef;
} LinNm_ChannelConfigType;

typedef struct {
    const LinNm_ChannelConfigType* LinNmChannels[LinNm_NumberOfLinNmChannels];
    const boolean BusSyncEnabled;
    const boolean ComCtrlEnabled;
    const boolean ComUserDataSupport;
    const boolean CoordinatorSyncSupport;
    const boolean DevErrorDetect;
    const boolean MainFunctionPeriod;
    const boolean NodeDetectionEnabled;
    const boolean NodeIdEnabled;
    const boolean PassiveModeEnabled;
    const boolean RemoteSleepIndicationEnabled;
    const boolean StateChangeIndEnabled;
    const boolean SyncPointEnabled;
    const boolean UserDataEnabled;
    const boolean VersionInfoApi;
}LinNm_ConfigType;

extern Nm_ModeType Nm_Mode[LinNm_NumberOfLinNmChannels];
extern Nm_StateType Nm_State[LinNm_NumberOfLinNmChannels];

#endif LINNM_CONFIGTYPES_H_