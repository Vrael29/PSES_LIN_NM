/** ==================================================================================================================*\
  @file UT_LinNm.c

  @brief Testy jednostkowe do LinNm
\*====================================================================================================================*/

#include "./../include/acutest.h"
#include "./../include/Std_Types.h"
#include "./../include/fff.h"

#include "LinNm.c"   

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(Det_ReportError, uint8_t, uint8_t, uint8_t, uint8_t);
FAKE_VOID_FUNC(Nm_NetworkMode, NetworkHandleType);
FAKE_VOID_FUNC(Nm_BusSleepMode, NetworkHandleType);
FAKE_VOID_FUNC(Nm_RemoteSleepIndication, NetworkHandleType);
FAKE_VOID_FUNC(Nm_StateChangeNotification, NetworkHandleType, Nm_StateType, Nm_StateType);

/**
  @brief Test LinNm_Init

  Funkcja testująca LinNm_Init
*/
void Test_Of_LinNm_Init(void)
{
    int Det_ReportError_ctr = 1;
    const LinNm_ConfigType* ConfigPtr;

    //Test1 Correct initialization
    LinNm_Init(ConfigPtr);

    for (int channel = 0; channel < LinNm_NumberOfLinNmChannels; channel++) {
        TEST_CHECK(LinNm_Internal.LinNmChannels[channel].Mode == NM_MODE_BUS_SLEEP);
        TEST_CHECK(LinNm_Internal.LinNmChannels[channel].State == NM_STATE_BUS_SLEEP);
    }
    TEST_CHECK(LinNm_Internal.InitStatus == LINNM_STATUS_INIT);

    //Test2 Null param pointer Error
    const LinNm_ConfigType* ConfigPtr_null;
    ConfigPtr_null = NULL;

    LinNm_Init(ConfigPtr_null);
    Det_ReportError_ctr++;

    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_PassiveStartUp

  Funkcja testująca LinNm_PassiveStartUp
*/
void Test_Of_LinNm_PassiveStartUp(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle = 0;
    int Det_ReportError_ctr = 0;
    int Nm_NetworkMode_ctr = 0;
    int Nm_BusSleepMode_ctr = 0;
    int Nm_RemoteSleepIndication_ctr = 0;
    int Nm_StateChangeNotification_ctr = 0;

    //Test1 Function changes mode correctly
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_BUS_SLEEP;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP;

    status = LinNm_PassiveStartUp(nmChannelHandle);
    Nm_NetworkMode_ctr++;
    Nm_RemoteSleepIndication_ctr++;
    Nm_StateChangeNotification_ctr++;
    // NetworkHandleType NetworkHandle;
    // status = LinNm_PassiveStartUp(NetworkHandle);
    TEST_CHECK(status == E_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_NETWORK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_NORMAL_OPERATION);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.arg1_val == NM_STATE_BUS_SLEEP);
    TEST_CHECK(Nm_StateChangeNotification_fake.arg2_val == NM_STATE_NORMAL_OPERATION);

    //Test2 Function called in wrong mode
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_NETWORK;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_NORMAL_OPERATION;

    status = LinNm_PassiveStartUp(nmChannelHandle);

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_NETWORK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_NORMAL_OPERATION);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);

    // //Test3 Function called while module not initialized
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_BUS_SLEEP;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP;

    status = LinNm_PassiveStartUp(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    // //Test4 Function called with invalid channel
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_PassiveStartUp(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

}

/**
  @brief Test LinNm_NetworkRequest

  Funkcja testująca LinNm_NetworkRequest
*/
void Test_Of_LinNm_NetworkRequest(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle = 0;
    int Det_ReportError_ctr = 0;
    int Nm_NetworkMode_ctr = 0;
    int Nm_BusSleepMode_ctr = 0;
    int Nm_RemoteSleepIndication_ctr = 0;
    int Nm_StateChangeNotification_ctr = 0;

    //Test1 Function changes mode correctly
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_BUS_SLEEP;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP;

    status = LinNm_NetworkRequest(nmChannelHandle);
    Nm_NetworkMode_ctr++;
    Nm_RemoteSleepIndication_ctr++;
    Nm_StateChangeNotification_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_NETWORK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_NORMAL_OPERATION);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.arg1_val == NM_STATE_BUS_SLEEP);
    TEST_CHECK(Nm_StateChangeNotification_fake.arg2_val == NM_STATE_NORMAL_OPERATION);

    //Test2 Function called in wrong mode
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_NETWORK;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_NORMAL_OPERATION;

    status = LinNm_NetworkRequest(nmChannelHandle);

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_NETWORK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_NORMAL_OPERATION);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);

    //Test3 Function called while module not initialized
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_BUS_SLEEP;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP;

    status = LinNm_NetworkRequest(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test4 Function called while channel not initialized
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_BUS_SLEEP;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_UNINIT;

    status = LinNm_NetworkRequest(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test5 Function called with invalid channel
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_NetworkRequest(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

}

/**
  @brief Test LinNm_NetworkRelease

  Funkcja testująca LinNm_NetworkRelease
*/
void Test_Of_LinNm_NetworkRelease(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle = 0;
    int Det_ReportError_ctr = 0;
    int Nm_NetworkMode_ctr = 0;
    int Nm_BusSleepMode_ctr = 0;
    int Nm_RemoteSleepIndication_ctr = 0;
    int Nm_StateChangeNotification_ctr = 0;

    //Test1 Function changes mode correctly
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_NETWORK;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_NORMAL_OPERATION;

    status = LinNm_NetworkRelease(nmChannelHandle);
    Nm_BusSleepMode_ctr++;
    Nm_StateChangeNotification_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_BUS_SLEEP);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.arg1_val == NM_STATE_NORMAL_OPERATION);
    TEST_CHECK(Nm_StateChangeNotification_fake.arg2_val == NM_STATE_BUS_SLEEP);

    //Test2 Function called in wrong mode
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_BUS_SLEEP;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP;

    status = LinNm_NetworkRelease(nmChannelHandle);

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_BUS_SLEEP);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);

    //Test3 Function called while module not initialized
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_NETWORK;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State =  NM_STATE_NORMAL_OPERATION;

    status = LinNm_NetworkRelease(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test4 Function called while channel not initialized
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_NETWORK;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State =  NM_STATE_UNINIT;

    status = LinNm_NetworkRelease(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test5 Function called with invalid channel
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_NetworkRelease(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);
}

/**
  @brief Test LinNm_GetVersionInfo

  Funkcja testująca LinNm_GetVersionInfo
*/
void Test_Of_LinNm_GetVersionInfo(void)
{
    int Det_ReportError_ctr = 0;
    const Std_VersionInfoType* version;

    //Test1 Function changes mode correctly

    LinNm_GetVersionInfo(version);

    TEST_CHECK(version->vendorID == LINNM_VENDOR_ID);
    TEST_CHECK(version->moduleID == LINNM_MODULE_ID);
    TEST_CHECK(version->sw_major_version == LINNM_AR_RELEASE_MAJOR_VERSION);
    TEST_CHECK(version->sw_minor_version == LINNM_AR_RELEASE_MINOR_VERSION);
    TEST_CHECK(version->sw_patch_version == LINNM_AR_RELEASE_REVISION_VERSION);

    //Test2 Function called in wrong mode
    version = NULL;
    LinNm_GetVersionInfo(version);
    Det_ReportError_ctr++;
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);

}

/**
  @brief Test LinNm_RequestBusSynchronization

  Funkcja testująca LinNm_RequestBusSynchronization
*/
void Test_Of_LinNm_RequestBusSynchronization(void)
{
    NetworkHandleType nmChannelHandle;
    Std_ReturnType status;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;

    status = LinNm_RequestBusSynchronization(nmChannelHandle);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;

    status = LinNm_RequestBusSynchronization(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_RequestBusSynchronization(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);
}

/**
  @brief Test LinNm_CheckRemoteSleepIndication

  Funkcja testująca LinNm_CheckRemoteSleepIndication
*/
void Test_Of_LinNm_CheckRemoteSleepIndication(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle;
    boolean* nmRemoteSleepIndPtr;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    *nmRemoteSleepIndPtr = 1;

    status = LinNm_CheckRemoteSleepIndication(nmChannelHandle, nmRemoteSleepIndPtr);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    *nmRemoteSleepIndPtr = 1;

    status = LinNm_CheckRemoteSleepIndication(nmChannelHandle, nmRemoteSleepIndPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;
    *nmRemoteSleepIndPtr = 1;

    status = LinNm_CheckRemoteSleepIndication(nmChannelHandle, nmRemoteSleepIndPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

    //Test4 Null param pointer Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    nmRemoteSleepIndPtr = NULL;

    status = LinNm_CheckRemoteSleepIndication(nmChannelHandle, nmRemoteSleepIndPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_SetSleepReadyBit

  Funkcja testująca LinNm_SetSleepReadyBit
*/
void Test_Of_LinNm_SetSleepReadyBit(void)
{
    NetworkHandleType nmChannelHandle;
    boolean nmSleepReadyBit;
    Std_ReturnType status;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    nmSleepReadyBit = 1;

    status = LinNm_SetSleepReadyBit(nmChannelHandle, nmSleepReadyBit);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    nmSleepReadyBit = 1;

    status = LinNm_SetSleepReadyBit(nmChannelHandle, nmSleepReadyBit);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;
    nmSleepReadyBit = 1;

    status = LinNm_SetSleepReadyBit(nmChannelHandle, nmSleepReadyBit);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);
}

/**
  @brief Test LinNm_DisableCommunication

  Funkcja testująca LinNm_DisableCommunication
*/
void Test_Of_LinNm_DisableCommunication(void)
{
    NetworkHandleType nmChannelHandle;
    Std_ReturnType status;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;

    status = LinNm_DisableCommunication(nmChannelHandle);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;

    status = LinNm_DisableCommunication(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_DisableCommunication(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);
}

/**
  @brief Test LinNm_EnableCommunication

  Funkcja testująca LinNm_EnableCommunication
*/
void Test_Of_LinNm_EnableCommunication(void)
{
    NetworkHandleType nmChannelHandle;
    Std_ReturnType status;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;

    status = LinNm_EnableCommunication(nmChannelHandle);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;

    status = LinNm_EnableCommunication(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_EnableCommunication(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);
}

/**
  @brief Test LinNm_SetUserData

  Funkcja testująca LinNm_SetUserData
*/
void Test_Of_LinNm_SetUserData(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle;
    const uint8* nmUserDataPtr = 1;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;

    status = LinNm_SetUserData(nmChannelHandle, nmUserDataPtr);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;

    status = LinNm_SetUserData(nmChannelHandle, nmUserDataPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_SetUserData(nmChannelHandle, nmUserDataPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

    //Test4 Null param pointer Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    const uint8* nmUserDataPtr_null;
    nmUserDataPtr_null = NULL;

    status = LinNm_SetUserData(nmChannelHandle, nmUserDataPtr_null);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_GetUserData

  Funkcja testująca LinNm_GetUserData
*/
void Test_Of_LinNm_GetUserData(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle;
    uint8* nmUserDataPtr;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    *nmUserDataPtr = 1;

    status = LinNm_GetUserData(nmChannelHandle, nmUserDataPtr);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    *nmUserDataPtr = 1;

    status = LinNm_GetUserData(nmChannelHandle, nmUserDataPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;
    *nmUserDataPtr = 1;

    status = LinNm_GetUserData(nmChannelHandle, nmUserDataPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

    //Test4 Null param pointer Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    nmUserDataPtr = NULL;

    status = LinNm_GetUserData(nmChannelHandle, nmUserDataPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_GetPduData

  Funkcja testująca LinNm_GetPduData
*/
void Test_Of_LinNm_GetPduData(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle;
    uint8* nmPduData;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    *nmPduData = 1;

    status = LinNm_GetPduData(nmChannelHandle, nmPduData);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    *nmPduData = 1;

    status = LinNm_GetPduData(nmChannelHandle, nmPduData);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;
    *nmPduData = 1;

    status = LinNm_GetPduData(nmChannelHandle, nmPduData);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

    //Test4 Null param pointer Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    nmPduData = NULL;

    status = LinNm_GetPduData(nmChannelHandle, nmPduData);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_RepeatMessageRequest

  Funkcja testująca LinNm_RepeatMessageRequest
*/
void Test_Of_LinNm_RepeatMessageRequest(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;

    status = LinNm_RepeatMessageRequest(nmChannelHandle);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;

    status = LinNm_RepeatMessageRequest(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_RepeatMessageRequest(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);
}

/**
  @brief Test LinNm_GetNodeIdentifier

  Funkcja testująca LinNm_GetNodeIdentifier
*/
void Test_Of_LinNm_GetNodeIdentifier(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle;
    uint8* nmNodeIdPtr;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    *nmNodeIdPtr = 1;

    status = LinNm_GetNodeIdentifier(nmChannelHandle, nmNodeIdPtr);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    *nmNodeIdPtr = 1;

    status = LinNm_GetNodeIdentifier(nmChannelHandle, nmNodeIdPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;
    *nmNodeIdPtr = 1;

    status = LinNm_GetNodeIdentifier(nmChannelHandle, nmNodeIdPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

    //Test4 Null param pointer Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    nmNodeIdPtr = NULL;

    status = LinNm_GetNodeIdentifier(nmChannelHandle, nmNodeIdPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_GetLocalNodeIdentifier

  Funkcja testująca LinNm_GetLocalNodeIdentifier
*/
void Test_Of_LinNm_GetLocalNodeIdentifier(void)
{
    Std_ReturnType status;
    NetworkHandleType nmChannelHandle;
    uint8* nmNodeIdPtr;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    *nmNodeIdPtr = 1;

    status = LinNm_GetLocalNodeIdentifier(nmChannelHandle, nmNodeIdPtr);

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    nmChannelHandle = 0;
    *nmNodeIdPtr = 1;

    status = LinNm_GetLocalNodeIdentifier(nmChannelHandle, nmNodeIdPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Invalid channel Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;
    *nmNodeIdPtr = 1;

    status = LinNm_GetLocalNodeIdentifier(nmChannelHandle, nmNodeIdPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

    //Test4 Null param pointer Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = 0;
    nmNodeIdPtr = NULL;

    status = LinNm_GetLocalNodeIdentifier(nmChannelHandle, nmNodeIdPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_GetState

  Funkcja testująca LinNm_GetState
*/
void Test_Of_LinNm_GetState(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType nmChannelHandle;
    Nm_StateType* nmStatePtr;
    Nm_ModeType* nmModePtr;
    int Det_ReportError_ctr = 0;

    //Test1 Function changes mode correctly
    nmChannelHandle = 0;
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    LinNm_Internal.LinNmChannels[nmChannelHandle].Mode = NM_MODE_BUS_SLEEP;
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP;
    status = LinNm_GetState(nmChannelHandle, nmStatePtr, nmModePtr);

    TEST_CHECK(status == E_OK);

    //Test2 Function called with wrong channel
    nmChannelHandle = -1;
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    status = LinNm_GetState(nmChannelHandle, nmStatePtr, nmModePtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status = E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

    //Test3 Function called with unitiliazed LinNm
    nmChannelHandle = 0;
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    status = LinNm_GetState(nmChannelHandle, nmStatePtr, nmModePtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status = E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test4 Function called with null pointer
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmModePtr = NULL;
    nmStatePtr = NULL;
    status = LinNm_GetState(nmChannelHandle, nmStatePtr, nmModePtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status = E_NOT_OK);
    TEST_CHECK(nmStatePtr == NULL);
    TEST_CHECK(nmModePtr == NULL);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_Transmit

  Funkcja testująca LinNm_Transmit
*/
void Test_Of_LinNm_Transmit(void)
{
    Std_ReturnType status;
    PduIdType TxPduId;
    const PduInfoType* PduInfoPtr = 1;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    TxPduId = 0;

    status = LinNm_Transmit(TxPduId, PduInfoPtr);

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    TxPduId = 0;

    status = LinNm_Transmit(TxPduId, PduInfoPtr);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test3 Null param pointer Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    TxPduId = 0;
    const PduInfoType* PduInfoPtr_null;
    PduInfoPtr_null = NULL;

    status = LinNm_Transmit(TxPduId, PduInfoPtr_null);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_PARAM_POINTER);
}

/**
  @brief Test LinNm_TxConfirmation

  Funkcja testująca LinNm_TxConfirmation
*/
void Test_Of_LinNm_TxConfirmation(void)
{
    PduIdType TxPduId;
    int Det_ReportError_ctr = 0;

    //Test1 No Error
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    TxPduId = 0;

    LinNm_TxConfirmation(TxPduId);

    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);

    //Test2 Uninit Error
    LinNm_Internal.InitStatus = LINNM_STATUS_UNINIT;
    TxPduId = 0;

    LinNm_TxConfirmation(TxPduId);
    Det_ReportError_ctr++;

    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);
}

/*
  Lista testów - wpisz tutaj wszystkie funkcje które mają być wykonane jako testy.
*/
TEST_LIST = {
    { "Test of LinNm_Init", Test_Of_LinNm_Init },   /* Format to { "nazwa testu", nazwa_funkcji } */
    { "Test of LinNm_PassiveStartUp", Test_Of_LinNm_PassiveStartUp },
    { "Test of LinNm_NetworkRequest", Test_Of_LinNm_NetworkRequest },
    { "Test of LinNm_NetworkRelease", Test_Of_LinNm_NetworkRelease },
    { "Test of LinNm_GetVersionInfo", Test_Of_LinNm_GetVersionInfo },
    { "Test of LinNm_RequestBusSynchronization", Test_Of_LinNm_RequestBusSynchronization },
    { "Test of LinNm_CheckRemoteSleepIndication", Test_Of_LinNm_CheckRemoteSleepIndication },
    { "Test of LinNm_SetSleepReadyBit", Test_Of_LinNm_SetSleepReadyBit },
    { "Test of LinNm_DisableCommunication", Test_Of_LinNm_DisableCommunication },
    { "Test of LinNm_EnableCommunication", Test_Of_LinNm_EnableCommunication },
    { "Test of LinNm_SetUserData", Test_Of_LinNm_SetUserData },
    { "Test of LinNm_GetUserData", Test_Of_LinNm_GetUserData },
    { "Test of LinNm_GetPduData", Test_Of_LinNm_GetPduData },
    { "Test of LinNm_RepeatMessageRequest", Test_Of_LinNm_RepeatMessageRequest },
    { "Test of LinNm_GetNodeIdentifier", Test_Of_LinNm_GetNodeIdentifier },
    { "Test of LinNm_GetLocalNodeIdentifier", Test_Of_LinNm_GetLocalNodeIdentifier },
    { "Test of LinNm_GetState", Test_Of_LinNm_GetState },
    { "Test of LinNm_Transmit", Test_Of_LinNm_Transmit },
    { "Test of LinNm_TxConfirmation", Test_Of_LinNm_TxConfirmation },
    { NULL, NULL }                                      /* To musi być na końcu */
};

