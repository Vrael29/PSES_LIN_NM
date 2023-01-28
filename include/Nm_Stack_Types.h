#ifndef NMSTACK_TYPES_H_
#define NMSTACK_TYPES_H_

/** Operational modes of the network management */
typedef enum {
    NM_MODE_BUS_SLEEP,
    NM_MODE_NETWORK
} Nm_ModeType;

/** States of the network management state machine */
typedef enum {
    NM_STATE_UNINIT,
    NM_STATE_BUS_SLEEP,
    NM_STATE_NORMAL_OPERATION
} Nm_StateType;


#endif /* NMSTACK_TYPES_H_ */