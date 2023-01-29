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

  Funkcja testująca  #TODO
*/
void Test_Of_LinNm_Init(void)
{
    const LinNm_ConfigType* ConfigPtr;
    // TEST_CHECK();

}

/**
  @brief Test LinNm_PassiveStartUp

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_PassiveStartUp(void)
{
    Std_ReturnType status = E_OK;
    // NetworkHandleType NetworkHandle;
    // status = LinNm_PassiveStartUp(NetworkHandle);
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_NetworkRequest

  Funkcja testująca #TODO
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
    LinNm_Internal.LinNmChannels[nmChannelHandle].State = LINNM_STATUS_UNINIT;

    status = LinNm_NetworkRequest(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_BUS_SLEEP);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_UNINIT);

    //Test4 Function called with invalid channel
    LinNm_Internal.InitStatus = LINNM_STATUS_INIT;
    nmChannelHandle = -1;

    status = LinNm_NetworkRequest(nmChannelHandle);
    Det_ReportError_ctr++;

    TEST_CHECK(status == E_NOT_OK);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].Mode == NM_MODE_BUS_SLEEP);
    TEST_CHECK(LinNm_Internal.LinNmChannels[nmChannelHandle].State = NM_STATE_BUS_SLEEP);
    TEST_CHECK(Det_ReportError_fake.call_count == Det_ReportError_ctr);
    TEST_CHECK(Nm_NetworkMode_fake.call_count == Nm_NetworkMode_ctr);
    TEST_CHECK(Nm_BusSleepMode_fake.call_count == Nm_BusSleepMode_ctr);
    TEST_CHECK(Nm_RemoteSleepIndication_fake.call_count == Nm_RemoteSleepIndication_ctr);
    TEST_CHECK(Nm_StateChangeNotification_fake.call_count == Nm_StateChangeNotification_ctr);
    TEST_CHECK(Det_ReportError_fake.arg3_val == LINNM_E_INVALID_CHANNEL);

}

/**
  @brief Test LinNm_NetworkRelease

  Funkcja testująca #TODO
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

    //Test4 Function called with invalid channel
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

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_GetVersionInfo(void)
{
    Std_VersionInfoType* versioninfo;

    // TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_RequestBusSynchronization

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_RequestBusSynchronization(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType nmChannelHandle;

    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_CheckRemoteSleepIndication

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_CheckRemoteSleepIndication(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType nmChannelHandle;
    boolean* nmRemoteSleepIndPtr;

    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_SetSleepReadyBit

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_SetSleepReadyBit(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType nmChannelHandle;
    boolean nmSleepReadyBit;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_DisableCommunication

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_DisableCommunication(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_EnableCommunication

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_EnableCommunication(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_SetUserData

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_SetUserData(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    const uint8* nmUserDataPtr;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_GetUserData

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_GetUserData(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    uint8* nmUserDataPtr;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_GetPduData

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_GetPduData(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    uint8* nmPduData;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_RepeatMessageRequest

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_RepeatMessageRequest(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_GetNodeIdentifier

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_GetNodeIdentifier(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    uint8* nmNodeIdPtr;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_GetLocalNodeIdentifier

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_GetLocalNodeIdentifier(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    uint8* nmNodeIdPtr;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_GetState

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_GetState(void)
{
    Std_ReturnType status = E_OK;
    NetworkHandleType NetworkHandle;
    Nm_StateType* nmStatePtr;
    Nm_ModeType* nmModePtr;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_Transmit

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_Transmit(void)
{
    Std_ReturnType status = E_OK;
    PduIdType TxPduId;
    const PduInfoType* PduInfoPtr;
    
    TEST_CHECK(status == E_OK);
}

/**
  @brief Test LinNm_TxConfirmation

  Funkcja testująca #TODO
*/
void Test_Of_LinNm_TxConfirmation(void)
{
    PduIdType TxPduId;
    Std_ReturnType result;
    
    // TEST_CHECK(status == E_OK);
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

