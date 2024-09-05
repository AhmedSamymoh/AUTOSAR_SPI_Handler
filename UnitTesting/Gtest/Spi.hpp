typedef unsigned char       uint8;
typedef unsigned long       uint32;
typedef uint8               Std_ReturnType;
typedef unsigned short      uint16;
typedef uint8       Spi_DataBufferType;
typedef uint8       Spi_SequenceType;  
typedef uint16      Spi_JobType;    
typedef uint8       Spi_ChannelType;   
typedef uint8       Spi_HWUnitType; 
#define BIT_MASK            0x01

#define SPI_Channel_1               0u
#define SPI_Channel_2               1u
#define SPI_Channel_3               2u
#define SPI_Channel_4               3u



/* APIs called with an unexpected value for the pointer */
#define SPI_E_PARAM_POINTER             ((uint8)0x10u)
/* API service called with wrong hardware unit */
#define SPI_E_PARAM_UNIT                ((uint8)0x0Eu)
/* API SPI_Init service called while the SPI driver has been already initialized */
#define SPI_E_ALREADY_INITIALIZED       ((uint8)0x4Au)
/* API service used without module initialization */
#define SPI_E_UNINIT                    ((uint8)0x1Au)
/* API service called with wrong lenghth for EB */
#define SPI_E_PARAM_LENGTH              ((uint8)0x0Du)


#define SET_BIT(REG , BIT_POSN)         (REG |=  (BIT_MASK << BIT_POSN))
#define CLR_BIT(REG , BIT_POSN)         (REG &= ~(BIT_MASK << BIT_POSN))
#define TOG_BIT(REG , BIT_POSN)         (REG ^=  (BIT_MASK << BIT_POSN))
#define READ_BIT(REG , BIT_POSN)        ((REG >> BIT_POSN ) & BIT_MASK )


#define SPI_E_ALREADY_INITIALIZED       ((uint8)0x4Au)
#define SPI_CR1_DFF         11
///////////////////////////////////////////////////////////////////////////
/**
 * @brief Spi_StatusType
 * [SWS_Spi_00373] 
 * This type defines a range of specific status for SPI Handler/Driver.
 */
typedef enum{
    SPI_UNINIT,         /*  not initialized or not usable      */
    SPI_IDLE,           /* not currently transmitting any Job. */
    SPI_BUSY,           /* performing a SPI Job (transmit).    */
} Spi_StatusType;

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Spi_JobResultType
 * [SWS_Spi_00374]
 * This type defines a range of specific Jobs status for SPI Handler/Driver.
 */
typedef enum {
    SPI_JOB_OK,          /* Job has been finished */   
    SPI_JOB_PENDING,     /* The meaning of this status is equal to @SPI_BUSY. */    
    SPI_JOB_FAILED,      /* the Job has failed. */       
    SPI_JOB_QUEUED       /*  An asynchronous transmit Job has been accepted, while 
                             actual transmission for this Job has not started yet.*/       
}Spi_JobResultType;

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Spi_SeqResultType
 * [SWS_Spi_00375]
 * This type defines a range of specific Sequences status for SPI Handler/Driver.
 */
typedef enum {
    SPI_SEQ_OK,                 
    SPI_SEQ_PENDING,                
    SPI_SEQ_FAILED,                 
    SPI_SEQ_CANCELED            
}Spi_SeqResultType;            

////////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief   The enumeration containing the designated values for buffer types (internal or external).
*
*/
typedef enum
{
    InternalBuffer = 0,     /* Configured using Internal Buffer. */
    ExternalBuffer          /* Configured using External Buffer. */
} Spi_BufferType;   

/*
 * Data Frame Format
 */
typedef enum {
    SPI_DFF_8BITS,
    SPI_DFF_16BITS
}Spi_DataFrameFormat;

/*
 * Clock Speed
 */
typedef enum {
    SPI_SCLK_SPEED_DIV2,
    SPI_SCLK_SPEED_DIV4,
    SPI_SCLK_SPEED_DIV8,
    SPI_SCLK_SPEED_DIV16,
    SPI_SCLK_SPEED_DIV32,
    SPI_SCLK_SPEED_DIV64,
    SPI_SCLK_SPEED_DIV128,
    SPI_SCLK_SPEED_DIV256
}Spi_ClockSpeed;




/*
 * Clock Polarity
 */

typedef enum {
   SPI_CPOL_LOW, 
   SPI_CPOL_HIGH
}Spi_ClockPolarity;

/*
 * Clock Phase
 */
typedef enum {
   SPI_CPHA_LOW	, 
   SPI_CPHA_HIGH
}Spi_ClockPhase;


/*
 * Async Mode
 */
typedef enum {
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE
}Spi_AsyncModeType;

/*
 * CS Port
 */
typedef uint8 Spi_CS_Port;


/*
 * CS Pin
 */
typedef uint8 Spi_CS_Pin;


typedef uint16 Spi_NumberOfDataType;

typedef struct{
    Spi_DataFrameFormat  spiDFF;                /* Data Frame Format:  ( SPI_DFF_8BITS : SPI_DFF_16BITS ) */    

    Spi_ClockSpeed       SpiPrescaller;         /* SpiPrescaller Clock Speed  ( SPI_SCLK_SPEED_DIV2 : SPI_SCLK_SPEED_DIV256 ) */

    uint32               DefaultTransmitValue;  /* Default Transmit Value.    ( 0x0000 : 0xFFFF ) */  
    
	Spi_ClockPolarity    spiCPOL;               /* Clock Polarity             ( SPI_CPOL_LOW : SPI_CPOL_HIGH ) */
                  
	Spi_ClockPhase       spiCPHA;               /* Clock Phase                ( SPI_CPHA_LOW : SPI_CPHA_HIGH ) */ 

} Spi_HWUnitConfigType;


typedef struct
{
    Spi_ChannelType      SpiChannelId;          /* Channel ID used with APIs */

    Spi_BufferType       BufferType;            /* Buffer Type InternalBuffer/ExternalBuffer. */

    Spi_StatusType       Status;                /* Channel internal state. */

    Spi_CS_Port          spiCSPort;             /* Chip Select Port  ( PORTA : PORTH )*/
    
    Spi_CS_Pin           spiCSPin;              /* Chip Select Pin  ( PIN0 : PIN15 ) */

} Spi_ChannelConfigType;


typedef struct 
{   
    Spi_JobType           SpiJobId;             /* Job ID used with APIs */

    Spi_HWUnitType        spiHWUint;            /*SPI Hardware Unit: SPI1/SPI4/SPI3/SPI4 */
    
    uint8                 JobPriority;          /* Job Priority ranging from 0 (Lowest) to 3 (Highest)*/ 
    
    Spi_ChannelType       *ChannelsPtr;         /* Ptr to channels asscociated with the job */ 
    
    Spi_ChannelType       NoOfChannels;         /* Number of Channels configured asscociated with the job*/
    
    Spi_HWUnitConfigType  *SpiHWUnitConfig;     /* Pointer to HW unit configuration */  

}Spi_JobConfigType;

////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
    Spi_JobConfigType     *JobLinkPtr;           /* Ptr to jobs IDs asscociated with the Sequence*/

    Spi_JobType           NoOfJobs;			     /* Number of Jobs configured */

    Spi_SequenceType      SpiSeqId;              /* Sequence ID used with APIs */ 
}Spi_SeqConfigType;

////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Spi_ConfigType
{
    /* pointer to sequence configuration */
    Spi_SeqConfigType * Spi_SeqConfigPtr;

    /* pointer to job configuration */
    Spi_JobConfigType * Spi_JobConfigPtr; 
   
    /* Pointer to channel configuration  */
    Spi_ChannelConfigType * Spi_ChannelConfigPtr ;   

} Spi_ConfigType;
///////////////////////////////////////////////////////////////////////////
typedef struct det
{

    uint16 ModuleId;
    uint8 InstanceId;
    uint8 ApiId;
    uint8 ErrorId;

} Det_ConfigType;


#define Det_Error_Buffer_index  0

#define DET_MAX_ERROR_BUFFER 1


Det_ConfigType Det_Error_Buffer[DET_MAX_ERROR_BUFFER];


#define NULL_PTR    ((const Spi_ConfigType*)0)
#define SPI_SW_moduleID                 1u
#define SPI_INIT_SID                    ((uint8)0x00u)
#define SPI_E_PARAM_POINTER             ((uint8)0x10u)

Std_ReturnType Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId){
    /* There is more space in the buffer */

if (Det_Error_Buffer_index < DET_MAX_ERROR_BUFFER)
{

Det_Error_Buffer->ApiId = ApiId;
Det_Error_Buffer->ErrorId=ErrorId;
Det_Error_Buffer->InstanceId=InstanceId;
Det_Error_Buffer->ModuleId =ModuleId;

}
return 0;
}


static Spi_StatusType Spi1_Status = SPI_UNINIT;
static Spi_StatusType Spi2_Status = SPI_UNINIT;
static Spi_StatusType Spi3_Status = SPI_UNINIT;
static Spi_StatusType Spi4_Status = SPI_UNINIT;


typedef struct{
     uint32 CR1;
     uint32 CR2;
     uint32 SR;
    uint32 DR;
    uint32 CRCPR;
    uint32 RXCRCR;
   uint32 TXCRCR;
} SPI_Registers;

SPI_Registers SPI1={0};
SPI_Registers SPI2={0};
SPI_Registers SPI3={0};
SPI_Registers SPI4={0};

#define Spi_HWUnit_SPI1                 (Spi_HWUnitType)1u
#define Spi_HWUnit_SPI2                 (Spi_HWUnitType)2u
#define Spi_HWUnit_SPI3                 (Spi_HWUnitType)3u
#define Spi_HWUnit_SPI4                 (Spi_HWUnitType)4u

//////////////////////////////////////////////////////////////////////////////////////////



/*
 * Device Modes
 * [SWS_Spi_00040] The SPI Handler/Driver handles only the Master mode.
 */
#define SPI_DEVICE_MODE_MASTER         1u

/*
 * Bus Configuration
 * [SWS_Spi_00050] ⌈The SPI Handler/Driver only supports full-duplex mode.
 */
#define SPI_BUS_CONFIG_FULL_DUPLEX     1u

#define SPI1_PORT PORTA
#define SPI2_PORT PORTB
#define SPI3_PORT PORTC
#define SPI4_PORT PORTE


#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4 
#define PORTF 5
#define PORTG 6
#define PORTH 7


#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
/**
 * nOT USED, BUT hw PIN AND SHOULD BE HERE
 * 
 */
#define PIN14 14
#define PIN15 15


#define E_OK            ((Std_ReturnType)0x00U)      /* Function Return OK */
#define E_NOT_OK        ((Std_ReturnType)0x01U)      /* Function Return NOT OK */


#define STD_ON              0x01u
#define STD_OFF             0x00u







/*
 * Spi_ErrorCodes_define
 * [SWS_Spi_91001]
 */
/* APIs called with an unexpected value for the pointer */
#define SPI_E_PARAM_POINTER             ((uint8)0x10u)
/* API service called with wrong hardware unit */
#define SPI_E_PARAM_UNIT                ((uint8)0x0Eu)
/* API SPI_Init service called while the SPI driver has been already initialized */
#define SPI_E_ALREADY_INITIALIZED       ((uint8)0x4Au)
/* API service used without module initialization */
#define SPI_E_UNINIT                    ((uint8)0x1Au)
/* API service called with wrong lenghth for EB */
#define SPI_E_PARAM_LENGTH              ((uint8)0x0Du)
/* API service called with wrong channel */
#define SPI_E_PARAM_CHANNEL             ((uint8)0x0Fu)


/**
 * @brief Service ID for Spi_Init 
 */
#define SPI_INIT_SID                    ((uint8)0x00u)

/**
 * @brief Service ID for Spi_DeInit 
 */
#define SPI_DEINIT_SID                  ((uint8)0x01u)

/**
 * @brief Service ID for Spi_WriteIB 
 */
#define SPI_WRITE_IB_SID                ((uint8)0x02u)

/**
 * @brief Service ID for Spi_GetVersionInfo 
 */
#define SPI_GET_VERSION_INFO_SID        ((uint8)0x09u)

/**
 * @brief Service ID for Spi_GetHWUnitStatus 
 */
#define SPI_GET_HW_UNIT_STATUS_SID      ((uint8)0x0bu)


extern Spi_ConfigType* Spi_Config_Ptr;



