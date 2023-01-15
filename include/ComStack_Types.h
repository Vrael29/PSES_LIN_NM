#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_

#include "Std_Types.h"
#include "Platform_Types.h"

typedef uint8 PduIdType;
typedef uint16 PduLengthType;
typedef struct {
    uint8 *SduDataPtr;			// payload
    PduLengthType SduLength;	// length of SDU
} PduInfoType;



typedef uint8 NetworkHandleType;


#endif /* COMSTACK_TYPES_H_*/