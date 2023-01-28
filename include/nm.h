#ifndef NM_H
#define MM_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Nm_Stack_Types.h"


/**
 * @brief Notification that the network management has entered Bus-Sleep Mode
 * 
 * [SWS_Nm_00162] 
 */
void Nm_BusSleepMode(NetworkHandleType nmNetworkHandleType);


/**
 * @brief Notification that the network management has entered Network Mode
 * 
 * [SWS_Nm_00156] 
 */
void Nm_NetworkMode(NetworkHandleType nmNetworkHandle);


/**
 * @brief Cancels an indication, when the NM Coordinator Sleep Ready bit in the
 * Control Bit Vector is set back to 0
 * 
 * [SWS_Nm_00272] 
 */
void Nm_CoordReadyToSleepCancellation(NetworkHandleType nmChannelHandle);


/**
 * @brief Sets an indication, when the NM Coordinator Sleep Ready bit in the 
 * Control Bit Vector is set
 * 
 * [SWS_Nm_00254] 
 */
void Nm_CoordReadyToSleepIndication(NetworkHandleType nmChannelHandle);


/**
 * @brief Notification that the network management has detected that all other
 * nodes on the network are ready to enter Bus-Sleep Mode.
 * 
 * [SWS_Nm_00192] 
 */
void Nm_RemoteSleepIndication(NetworkHandleType nmNetworkHandle);


/**
 * @brief Notification that the state of the lower layer <BusNm> has changed.
 * 
 * [SWS_Nm_00114] 
 */
void Nm_StateChangeNotification(NetworkHandleType nmNetworkHandle, Nm_StateType nmPreviousState, Nm_StateType nmCurrentState);



#endif /* NM_H */