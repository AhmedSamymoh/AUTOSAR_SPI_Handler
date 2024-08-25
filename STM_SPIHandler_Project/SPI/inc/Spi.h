#include <stdio.h>
#include <cstdint>
// Global variables
uint8_t DataBufferType, ChannelType, SequenceType, HWUnitType;
uint16_t NumberOfDataType, JobType;


// SPI ConfigType for SPI init 
typedef enum {
    UNINIT, IDLE, BUSY
    }StatusType;

typedef enum {
    OK, PENDING, FAILED, QUEUED
    }JobResultType;

typedef enum {
    OK, PENDING, FAILED, CANCELED 
    }SeqResultType;

typedef enum {
    POLLING, INTERRUPT
    }AsyncModeType;
