#ifndef LINNM_CONFIGTYPES_H_
#define LINNM_CONFIGTYPES_H_

typedef struct {
    const uint32 TimeoutTime;
    const NetworkHandleType FrNmComMNetworkHandleRef;
} LinNm_ChannelConfigType;

typedef struct {
    const LinNm_ChannelConfigType* LinNmChannels;
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

#endif LINNM_CONFIGTYPES_H_