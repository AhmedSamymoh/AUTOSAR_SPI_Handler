#include <stdio.h>


/**
 * @file Spi.h
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Serial Perpheral Interface Header file
 * @version info : @ module : SPI Handler/Driver @ Platform : stm32f446re @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 */



/********************************************** Section : Includes ********************************************/


#include "../../STM_SPIHandler_Project/AUTOSAR/Std_Types.h"
    


/**************************************** Section: Data Type Declarations **************************************/


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief   Spi_HWUnitType
 * [SWS_Spi_00381]
 * Specifies the identification (ID) for a SPI Hardware microcontroller peripheral (unit).
 * SPI1_HW_UNIT / SPI2_HW_UNIT / SPI3_HW_UNIT / SPI4_HW_UNIT
 */
typedef uint8       Spi_HWUnitType; 

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_ChannelType
 * [SWS_Spi_00378]
 * Specifies the identification (ID) for a Channel.
 */
typedef uint8       Spi_ChannelType;   
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_JobType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */
typedef uint16      Spi_JobType;     
////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief    Spi_SequenceType
 * [SWS_Spi_00380]
 * Specifies the identification (ID) for a sequence of jobs.
 */
typedef uint8       Spi_SequenceType;     
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief     Spi_DataBufferType
 * [SWS_Spi_00376]
 * Type of application data buffer elements.
 * Usage 0:  only Internal Buffers. (8 or 16 bits for SPIx_DR) 
 * Usage 1:  only External Buffers. (9, 17 or 5 Bits.. User defined )
 * Usage 2:  both buffers types : Internal and External Buffers.
 * Spi_DataBufferType = 8 / 16 > SPI1_CR1_DFF = 0/1
 */
typedef uint8       Spi_DataBufferType;     
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Spi_NumberOfDataType
 * [SWS_Spi_00377]
 * Type for defining the number of data elements to send and / or receive by Channel
 */
typedef uint16      Spi_NumberOfDataType;     

////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////

/*
 * SPI Module Version Info
 */
#define SPI_SW_vendor_ID                1u    
#define SPI_SW_moduleID                 1u
#define SPI_SW_major_version            1u
#define SPI_SW_minor_version            1u 
#define SPI_SW_patch_version            1u


/*
 * SPI Hardware Units 
 * @Spi_HWUnitType
 */
#define Spi_HWUnit_SPI1                 (Spi_HWUnitType)1u
#define Spi_HWUnit_SPI2                 (Spi_HWUnitType)2u
#define Spi_HWUnit_SPI3                 (Spi_HWUnitType)3u
#define Spi_HWUnit_SPI4                 (Spi_HWUnitType)4u



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


/**
 * @brief   
 * 
 */
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

    Spi_StatusType       Status;                /* Channel internal state. For First Init Config This should be SPI_UNINIT */

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

/************************************ Section: Macro Declarations ************************************/
                                                                                    

/************************************ Section : Global Variables Definations ************************************/

Std_VersionInfoType Spi_VersionInfo = {
    .vendorID = SPI_SW_vendor_ID,
    .moduleID = SPI_SW_moduleID,
    .sw_major_version = SPI_SW_major_version,
    .sw_minor_version = SPI_SW_minor_version,
    .sw_patch_version = SPI_SW_patch_version
};


/************************************* Section : Macro Functions Definations ************************************/

/*************************************** Section : Functions Declarations ***************************************/
/***************************************** Section : User Configurations **************************************/
/*
 * SPI Module Version Info
 */
#define DET_SW_vendor_ID                1u    
#define DET_SW_moduleID                 1u
#define DET_SW_major_version            1u
#define DET_SW_minor_version            1u 
#define DET_SW_patch_version            1u



typedef struct det
{
    uint16 ModuleId;
    uint8 InstanceId;
    uint8 ApiId;
    uint8 ErrorId;
} Det_ConfigType;

/**
 * @brief Maximum Error The Buffer can handle
 * 
 */
#define DET_MAX_ERROR_BUFFER            3u


Det_ConfigType Det_Error_Buffer[DET_MAX_ERROR_BUFFER];

static boolean Det_Init_Flag = FALSE;

static uint8 Det_Error_Buffer_index = 0;


/**
 * @brief Service to report development errors.
 * 
 * @param ModuleId : Module ID of calling module.
 * @param InstanceId : The identifier of the index based instance of a module
 * @param ApiId : ID of API service in which error is detected
 * @param ErrorId : ID of detected development error (defined in SWS of calling module).
 * @return Std_ReturnType : never returns a value, but has a return type for compatibility with
                            services and hooks
 */
Std_ReturnType Det_ReportError (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId){
 
    /* There is more space in the buffer */
    if (Det_Error_Buffer_index < DET_MAX_ERROR_BUFFER)
    {
        Det_Error_Buffer->ApiId = ApiId;
        Det_Error_Buffer->ErrorId=ErrorId;
        Det_Error_Buffer->InstanceId=InstanceId;
        Det_Error_Buffer->ModuleId =ModuleId;
    }
    else
    {
        /* Not enough buffer space */
        for(;;);

        return E_NOT_OK;
    }

    /* Error data stored in buffer */
    return E_OK;
}





/**
 * @brief Initializes the SPI driver. [SWS_Spi_00184]
 *
 * This function initializes the SPI driver according `Spi_ConfigType` structure. It is 
 * responsible for setting up the SPI channels, jobs, and hardware units as specified in the 
 * configuration. The function checks whether the driver has already been initialized and 
 * reports errors if there are issues with re-initialization or invalid pointers.
 * 
 * @param ConfigPtr Pointer to the SPI configuration structure.
 *                  If NULL , an error is reported.
 *
 * @return None.
 *
 * @note Re-initialization requires prior de-initialization.
 */
void Spi_Init(const Spi_ConfigType* ConfigPtr);


/**
 * @brief  Service for writing one or more data to an IB SPI Handler/Driver Channel specified by parameter
 *         [SWS_Spi_00177]  
 * @param  Channel Channel ID.
 * @param  DataBufferPtr Pointer to source data buffer.
 * @return Std_ReturnType :
 * 	          E_OK: Spi_WriteIB command has been accepted 
 *            E_NOT_OK: Spi_WriteIB command has not been accepted
 */
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, const Spi_DataBufferType* DataBufferPtr);

/**
 * @brief This service returns the status of the specified SPI Har
 * dware microcontroller 
 * peripheral.
 * Spi_GetHWUnitStatus : [SWS_Spi_00186]
 * 
 * @param HWUnit 
 * @return Spi_StatusType : SPI_UNINIT, SPI_IDLE, SPI_BUSY
 */
Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit);


/**
 * @brief This service returns the version information of this module.
 * Spi_GetVersionInfo : [SWS_Spi_00184]
 * 
 * @param VersionInfo 
 */
void Spi_GetVersionInfo(Std_VersionInfoType *VersionInfo);




/**************************************************************************************************************/
/***************************************** Section : User Configurations **************************************/
/**************************************************************************************************************/
#define SPI_Channel_1               0u
#define SPI_Channel_2               1u
#define SPI_Channel_3               2u
#define SPI_Channel_4               3u

/**************************************** Section: Data Type Declarations **************************************/




/************************************ Section: Macro Declarations ************************************/





/************************************ Section : Global Variables Definations ************************************/
Spi_ChannelType SPI_job1_channels[] = {SPI_Channel_1, SPI_Channel_2};
Spi_ChannelType SPI_job2_channels[] = {SPI_Channel_3, SPI_Channel_4};


Spi_HWUnitConfigType hwUnitConfig_Job_1 = {
    .SpiPrescaller = SPI_SCLK_SPEED_DIV256,   
    .spiCPOL = SPI_CPOL_LOW,       
    .spiCPHA = SPI_CPHA_LOW, 
	.spiDFF = SPI_DFF_16BITS,
	.DefaultTransmitValue = 0xAAAA 
};

Spi_HWUnitConfigType hwUnitConfig_Job_2 = {
    .SpiPrescaller = SPI_SCLK_SPEED_DIV32,   
    .spiCPOL = SPI_CPOL_HIGH,       
    .spiCPHA = SPI_CPHA_HIGH, 
	.spiDFF = SPI_DFF_8BITS,
	.DefaultTransmitValue = 0xFF
};

Spi_ChannelConfigType channels[]= {
    {
        .SpiChannelId = SPI_Channel_1,
        .BufferType = InternalBuffer,
        .Status = SPI_UNINIT,
		.spiCSPort = PORTA,       
    	.spiCSPin = PIN10     
    },
    {
        .SpiChannelId = SPI_Channel_2,
        .BufferType = InternalBuffer,
        .Status = SPI_UNINIT,
		.spiCSPort = PORTA,       
    	.spiCSPin = PIN11   
    },
	{
		.SpiChannelId = SPI_Channel_3,
		.BufferType = InternalBuffer,
		.Status = SPI_UNINIT,
		.spiCSPort = PORTA,       
		.spiCSPin = PIN12
	},
	{
		.SpiChannelId = SPI_Channel_4,
		.BufferType = InternalBuffer,
		.Status = SPI_UNINIT,
		.spiCSPort = PORTA,       
		.spiCSPin = PIN13
	}
};

Spi_JobConfigType jobConfig[] = {
    {
        .SpiJobId = 0,
        .JobPriority = 0,
        .ChannelsPtr = SPI_job1_channels,
		.NoOfChannels = sizeof(SPI_job1_channels)/sizeof(Spi_ChannelType),
        .spiHWUint = Spi_HWUnit_SPI1,
        .SpiHWUnitConfig = &hwUnitConfig_Job_1
    },
	{
		.SpiJobId = 1,
		.JobPriority = 1,
		.ChannelsPtr = SPI_job2_channels,
		.NoOfChannels = sizeof(SPI_job2_channels)/sizeof(Spi_ChannelType),
		.spiHWUint = Spi_HWUnit_SPI2,
		.SpiHWUnitConfig = &hwUnitConfig_Job_2
	}
};
Spi_SeqConfigType Spi_SeqConfig = {
	
	.SpiSeqId = 0,
    .JobLinkPtr = jobConfig,
	.NoOfJobs = 2

};

Spi_ConfigType Spi_Config = {
	.Spi_SeqConfigPtr = &Spi_SeqConfig,
    .Spi_JobConfigPtr = &jobConfig[0],
    .Spi_ChannelConfigPtr = &channels[0]
};


Spi_ConfigType * Spi_Config_Ptr = &Spi_Config;





/************************************* Section : Macro Functions Definations ************************************/





/**************************************** Section: Data Type Declarations **************************************/

/************************************* Section : Global Variables Definations **********************************/

/* Define the current status of the SPI module 
    Shared variable between APIs 
	Defined By Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit)
*/
static Spi_StatusType Spi1_Status = SPI_UNINIT;
static Spi_StatusType Spi2_Status = SPI_UNINIT;
static Spi_StatusType Spi3_Status = SPI_UNINIT;
static Spi_StatusType Spi4_Status = SPI_UNINIT;

/**************************************** Section : Functions Definations ***************************************/


/****************************************************************************************************************/
/******************************************* Section : Local Functions ******************************************/
/****************************************************************************************************************/
static void Spi_lhw_Init(const Spi_HWUnitType HWUnitId, const Spi_HWUnitConfigType * HWUnit );
static void Spi_GPIO_Init(Spi_HWUnitType Spi_select ,uint8 port);
static void Spi_ChipSelect_Init(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port );
static void Spi_ChipSelect_Write(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port , Std_ReturnType Level);
/*************************************** Section : Functions Declarations ***************************************/
void System_Init(void);
void GPIO_SPI_SlaveSelect_Init (uint8 port, uint8 pin);



////////////////////////////////////////////////////////////////////////////////////////////.

/**
 * @brief Initializes the SPI driver. [SWS_Spi_00184]
 *
 * This function initializes the SPI driver according `Spi_ConfigType` structure. It is 
 * responsible for setting up the SPI channels, jobs, and hardware units as specified in the 
 * configuration. The function checks whether the driver has already been initialized and 
 * reports errors if there are issues with re-initialization or invalid pointers.
 * 
 * @param ConfigPtr Pointer to the SPI configuration structure.
 *                  If NULL, an error is reported.
 *
 * @return None.
 *
 * @note Re-initialization requires prior de-initialization.
 */
void Spi_Init(const Spi_ConfigType* ConfigPtr)
{
	if (ConfigPtr == NULL_PTR)
	{
		/*Det_ReportError*/
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_INIT_SID, SPI_E_PARAM_POINTER);
	}
	else
	{
		for (uint8 Jobs_Index = 0; Jobs_Index < ConfigPtr->Spi_SeqConfigPtr->NoOfJobs; Jobs_Index++)
		{
			for (uint8 channels_index = 0; channels_index < (ConfigPtr->Spi_JobConfigPtr->NoOfChannels) ; channels_index++)
			{
				if (ConfigPtr->Spi_ChannelConfigPtr[channels_index].Status == SPI_UNINIT)
				{
					/* Initialization of the Chip Select Pin */
					Spi_ChipSelect_Init(ConfigPtr->Spi_ChannelConfigPtr[channels_index].spiCSPort, ConfigPtr->Spi_ChannelConfigPtr[channels_index].spiCSPort);
					
					/* Set SPI1 status to SPI_IDLE after initialization for avoiding Duplecated Initialization */ 
					ConfigPtr->Spi_ChannelConfigPtr[channels_index].Status = SPI_IDLE;
				}else{
					/*	A re-initialization of a SPI Handler/Driver by executing the Spi_Init() function requires 
						a de-initialization before by executing a Spi_DeInit().

						Spi_DeInit() */ 
				
					/*Det_ReportError with SPI_Init service called while the SPI driver has been already initialized */
					Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_INIT_SID, SPI_E_ALREADY_INITIALIZED );
				}	
			}

			/* Initialize the SPI Hardware Unit */
			Spi_lhw_Init((ConfigPtr->Spi_JobConfigPtr[Jobs_Index].spiHWUint), (ConfigPtr->Spi_JobConfigPtr[Jobs_Index].SpiHWUnitConfig) );
			
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Service for writing one or more data to an IB SPI Handler/Driver Channel specified by parameter
 *         [SWS_Spi_00177]  
 * @param  Channel Channel ID.
 * @param  DataBufferPtr Pointer to source data buffer.
 * @return Std_ReturnType :
 * 	          E_OK: Spi_WriteIB command has been accepted 
 *            E_NOT_OK: Spi_WriteIB command has not been accepted
 */
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, const Spi_DataBufferType* DataBufferPtr)
{
	Std_ReturnType ret = E_NOT_OK;
	
	if (DataBufferPtr == (Spi_DataBufferType*)NULL_PTR)
	{
		/*Det_ReportError with wrong data buffer pointer */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_POINTER);

	}else if (Channel < SPI_Channel_1 || Channel > SPI_Channel_4)
	{
		/*Det_ReportError with wrong channel ID */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_CHANNEL);

	}else if (Spi_Config_Ptr == (Spi_ConfigType*)NULL_PTR){

		/*Det_ReportError with wrong channel ID */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_UNINIT);
	
	}else if (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint > Spi_HWUnit_SPI4 || Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint < Spi_HWUnit_SPI1){

		/*Det_ReportError with wrong channel ID */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_UNIT);
	
	}else{

		/* Set the channel status to SPI_BUSY */
		Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].Status=SPI_BUSY;

		switch (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint)
		{
			case Spi_HWUnit_SPI1:
				/* Write the data to the Data Register */
				// SPI1->DR = *DataBufferPtr;
				// ret = E_OK;
				// break;
			
			case Spi_HWUnit_SPI2:
				/* Write the data to the Data Register */
				SPI2->DR = *DataBufferPtr;
				ret = E_OK;
				break;

			case Spi_HWUnit_SPI3:
				/* Write the data to the Data Register */
				SPI3->DR = *DataBufferPtr;
				ret = E_OK;
				break;

			case Spi_HWUnit_SPI4:
				/* Write the data to the Data Register */
				SPI4->DR = *DataBufferPtr;
				ret = E_OK;
				break;
				
			default: break;
		}

		/* Set the channel status to SPI_IDLE */
		Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].Status=SPI_BUSY;

	}

	return ret;
}


/**
 * @brief This service returns the status of the specified SPI Hardware microcontroller 
 * peripheral.
 * Spi_GetHWUnitStatus : [SWS_Spi_00186]
 * 
 * @param HWUnit 
 * @return Spi_StatusType : SPI_UNINIT, SPI_IDLE, SPI_BUSY
 */
Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit){
	
	uint8 Spi_Status = 0;

	if(HWUnit < Spi_HWUnit_SPI1 || HWUnit > Spi_HWUnit_SPI4)
	{
		/*Det_ReportError with wrong hardware unit */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_GET_HW_UNIT_STATUS_SID, SPI_E_PARAM_UNIT);
	}else{
		
		switch (HWUnit)
		{
			case Spi_HWUnit_SPI1:
				if (Spi1_Status == SPI_UNINIT){ /*Peripheral disabled */
					/*Det_ReportError with API service used without module initialization */
					Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_GET_HW_UNIT_STATUS_SID, SPI_E_UNINIT );
				}else{
					if (READ_BIT( (SPI1->CR1) , SPI_CR1_SPE) == 0){
						//Spi_Status = SPI_UNINIT; /* Bit 6 SPE: SPI enable 0: Peripheral disabled */ 
					}else if ( READ_BIT( (SPI1->SR) , SPI_SR_BSY) == 0) {
						//Spi_Status = SPI_IDLE; /* 0: SPI (or I2S) not busy <Bit 7 BSY: Busy flag> */ 
					}else if ( READ_BIT( (SPI1->SR) , SPI_SR_BSY) == 1) {	
						//Spi_Status = SPI_BUSY; /* 1: SPI (or I2S) is busy in communication or Tx buffer is not empty <Bit 7 BSY: Busy flag> */
					}else {
						/* Nothing */
					}	
				}

				break;
			
			case Spi_HWUnit_SPI2:
				if (Spi2_Status == SPI_UNINIT){ /*Peripheral disabled */
					/*Det_ReportError with API service used without module initialization */
					Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_GET_HW_UNIT_STATUS_SID, SPI_E_UNINIT);
				}else{
					if (READ_BIT( (SPI2->CR1) , SPI_CR1_SPE) == 0){
						Spi_Status = SPI_UNINIT; /* Bit 6 SPE: SPI enable 0: Peripheral disabled */ 
					}else if ( READ_BIT( (SPI2->SR) , SPI_SR_BSY) == 0) {
						Spi_Status = SPI_IDLE; /* 0: SPI (or I2S) not busy <Bit 7 BSY: Busy flag> */ 
					}else if ( READ_BIT( (SPI2->SR) , SPI_SR_BSY) == 1) {	
						Spi_Status = SPI_BUSY; /* 1: SPI (or I2S) is busy in communication or Tx buffer is not empty <Bit 7 BSY: Busy flag> */
					}else {
						/* Nothing */
					}
				}
			
				break;
			
			case Spi_HWUnit_SPI3:
				if (Spi3_Status == SPI_UNINIT){ /*Peripheral disabled */
					/*Det_ReportError with API service used without module initialization */
					Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_GET_HW_UNIT_STATUS_SID, SPI_E_UNINIT);
				}else{
					if (READ_BIT( (SPI3->CR1) , SPI_CR1_SPE) == 0){
						Spi_Status = SPI_UNINIT; /* Bit 6 SPE: SPI enable 0: Peripheral disabled */ 
					}else if ( READ_BIT( (SPI3->SR) , SPI_SR_BSY) == 0) {
						Spi_Status = SPI_IDLE; /* 0: SPI (or I2S) not busy <Bit 7 BSY: Busy flag> */ 
					}else if ( READ_BIT( (SPI3->SR) , SPI_SR_BSY) == 1) {	
						Spi_Status = SPI_BUSY; /* 1: SPI (or I2S) is busy in communication or Tx buffer is not empty <Bit 7 BSY: Busy flag> */
					}else {
						/* Nothing */
					}
				}
				
				break;
			
			case Spi_HWUnit_SPI4:
				if (Spi4_Status == SPI_UNINIT){ /*Peripheral disabled */
					/*Det_ReportError with API service used without module initialization */
					Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_GET_HW_UNIT_STATUS_SID, SPI_E_UNINIT);
				}else{
					if (READ_BIT( (SPI4->CR1) , SPI_CR1_SPE) == 0){
						Spi_Status = SPI_UNINIT; /* Bit 6 SPE: SPI enable 0: Peripheral disabled */ 
					}else if ( READ_BIT( (SPI4->SR) , SPI_SR_BSY) == 0) {
						Spi_Status = SPI_IDLE; /* 0: SPI (or I2S) not busy <Bit 7 BSY: Busy flag> */ 
					}else if ( READ_BIT( (SPI4->SR) , SPI_SR_BSY) == 1) {	
						Spi_Status = SPI_BUSY; /* 1: SPI (or I2S) is busy in communication or Tx buffer is not empty <Bit 7 BSY: Busy flag> */
					}else {
						/* Nothing */
					}
				}

				break;
			
			default:
				break;
		}
	}
	
	return Spi_Status;
}


/**
 * @brief This service returns the version information of this module.
 *  - Service ID [hex] 0x09
 *  - Spi_GetVersionInfo
 *  - [SWS_Spi_00184]
 * @param VersionInfo 
 */
void Spi_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{

    if (VersionInfo == NULL_PTR)
    {
        /*Det_ReportError with API service used without module initialization */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_GET_VERSION_INFO_SID, SPI_E_PARAM_POINTER);
    }
    else
    {
        VersionInfo->moduleID = SPI_SW_moduleID;
        VersionInfo->sw_major_version = SPI_SW_major_version;
        VersionInfo->sw_minor_version = SPI_SW_minor_version;
        VersionInfo->sw_patch_version = SPI_SW_patch_version;
        VersionInfo->vendorID = SPI_SW_vendor_ID;
    }
}




/****************************************************************************************************************/
/******************************************* Section : Local Functions ******************************************/
/****************************************************************************************************************/


/**
 * @brief Should be called from here or from Spi_Init() function
 * 
 * @param HWUnitId 
 * @param HWUnit 
 */
static void Spi_lhw_Init(const Spi_HWUnitType HWUnitId, const Spi_HWUnitConfigType * HWUnit ){

	switch (HWUnitId)
	{
		case Spi_HWUnit_SPI1:
			/* GPIO Port Enabling SPI1 To be alternative pin*/
			Spi_GPIO_Init(HWUnitId, SPI1_PORT);

			/* Enable SPI1 Clock */
			///SPI1_PCLK_EN();

			/* Reset SPI1 Configuration */
			//SPI1->CR1 = 0;

			/* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
			//SET_BIT(SPI1->CR1, SPI_CR1_MSTR );

			/* SSM=1, SSi=1 -> Software Slave Management Setting SSI, > to avoid MODF Error*/
			//SET_BIT( SPI1->CR1 , SPI_CR1_SSM );
			//SET_BIT( SPI1->CR1 , SPI_CR1_SSI );

			/* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for Full Duplex */
			//CLR_BIT(SPI1->CR1, SPI_CR1_BIDIMODE);


			/*SPI_CR1_LSBFIRST = 0 for MSB first*/
			//CLR_BIT( SPI1->CR1 , SPI_CR1_LSBF );

			SPI1->CR2 = 0 ;

			/* Configure SPI Clock Polarity */
			if (HWUnit->spiCPOL == SPI_CPOL_LOW){
				//CLR_BIT(SPI1->CR1, SPI_CR1_CPOL); /* 0: CK to 0 when idle */
			}else{
				//SET_BIT(SPI1->CR1, SPI_CR1_CPOL); /* 1: CK to 1 when idle */
			}

			/* Configure SPI Clock Phase */
			if (HWUnit->spiCPHA == SPI_CPHA_LOW){
				//CLR_BIT(SPI1->CR1, SPI_CR1_CPHA); /* 0: The first clock transition is the first data capture edge*/
			}else{
				//SET_BIT(SPI1->CR1, SPI_CR1_CPHA); /* 1: The second clock transition is the first data capture edge */
			}

			if (HWUnit->spiDFF == SPI_DFF_16BITS){
				//SET_BIT(SPI1->CR1, SPI_CR1_DFF); /* 1: 16-bit data frame format is selected for transmission/reception */
			}else if (HWUnit->spiDFF == SPI_DFF_8BITS){
				//CLR_BIT(SPI1->CR1, SPI_CR1_DFF); /* 0: 8-bit data frame format is selected for transmission/reception */
			}else{/* Nothing */}

			/* Set Default Transmit Value */
			//SPI1->DR = HWUnit->DefaultTransmitValue;

			/* Configure SPI Clock Speed */
			/* Clear the bits for clock speed <Mask bits 5:3> */
			//SPI1->CR1 &= ~(0x7U << SPI_CR1_BR0);
			/* BR[2:0] bits for Baud Rate */
			//SPI1->CR1 |= (HWUnit->SpiPrescaller << SPI_CR1_BR0);

			/* Enable SPI1 */
			//SET_BIT(SPI1->CR1, SPI_CR1_SPE); // SPI_CR1_SPE = 1 to enable SPI

			/* Set SPI1 status to SPI_IDLE after initialization 
			* for avoiding Duplecated Initialization */ 
			//Spi1_Status = SPI_IDLE;

			break;

		case Spi_HWUnit_SPI2:
			/* GPIO Port Enabling SPI2 To be alternative pin*/
			Spi_GPIO_Init(HWUnitId, SPI2_PORT);
			
			/* Enable SPI2 Clock */
			SPI2_PCLK_EN();

			/* Reset SPI2 Configuration */
			SPI2->CR1 = 0;

			/* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
			SET_BIT(SPI2->CR1, SPI_CR1_MSTR );

			/* SSM=1, SSi=1 -> Software Slave Management Setting SSI, > to avoid MODF Error*/
			SET_BIT( SPI2->CR1 , SPI_CR1_SSM );
			SET_BIT( SPI2->CR1 , SPI_CR1_SSI );

			/* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for Full Duplex */
			CLR_BIT(SPI2->CR1, SPI_CR1_BIDIMODE);

			/*SPI_CR1_LSBFIRST = 0 for MSB first*/
			CLR_BIT( SPI2->CR1 , SPI_CR1_LSBF );

			SPI2->CR2 = 0 ;

			/* Configure SPI Clock Polarity */
			if (HWUnit->spiCPOL == SPI_CPOL_LOW){
				CLR_BIT(SPI2->CR1, SPI_CR1_CPOL); /* 0: CK to 0 when idle */
			}else{
				SET_BIT(SPI2->CR1, SPI_CR1_CPOL); /* 1: CK to 1 when idle */
			}

			/* Configure SPI Clock Phase */
			if (HWUnit->spiCPHA == SPI_CPHA_LOW){
				CLR_BIT(SPI2->CR1, SPI_CR1_CPHA); /* 0: The first clock transition is the first data capture edge*/
			}else{
				SET_BIT(SPI2->CR1, SPI_CR1_CPHA); /* 1: The second clock transition is the first data capture edge */
			}
			
			if (HWUnit->spiDFF == SPI_DFF_16BITS){
				SET_BIT(SPI2->CR1, SPI_CR1_DFF); /* 1: 16-bit data frame format is selected for transmission/reception */
			}else if (HWUnit->spiDFF == SPI_DFF_8BITS){
				CLR_BIT(SPI2->CR1, SPI_CR1_DFF); /* 0: 8-bit data frame format is selected for transmission/reception */
			}else{/* Nothing */}

			/* Set Default Transmit Value */
			SPI2->DR = HWUnit->DefaultTransmitValue;

			/* Configure SPI Clock Speed */
			/* Clear the bits for clock speed <Mask bits 5:3> */
			SPI2->CR1 &= ~(0x7U << SPI_CR1_BR0);
			/* BR[2:0] bits for Baud Rate */
			SPI2->CR1 |= (HWUnit->SpiPrescaller << SPI_CR1_BR0);

			/* Enable SPI2 */
			SET_BIT(SPI2->CR1, SPI_CR1_SPE); // SPI_CR1_SPE = 1 to enable SPI

			/* Set SPI2 status to SPI_IDLE after initialization 
			* for avoiding Duplecated Initialization */ 
			Spi2_Status = SPI_IDLE;
			
			break;
		
		case Spi_HWUnit_SPI3:
			/* GPIO Port Enabling SPI3 To be alternative pin*/
			Spi_GPIO_Init(HWUnitId, SPI3_PORT);

			/* Enable SPI3 Clock */
			SPI3_PCLK_EN();

			/* Reset SPI3 Configuration */
			SPI3->CR1 = 0;

			/* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
			SET_BIT(SPI3->CR1, SPI_CR1_MSTR );

			/* SSM=1, SSi=1 -> Software Slave Management Setting SSI, > to avoid MODF Error*/
			SET_BIT( SPI3->CR1 , SPI_CR1_SSM );
			SET_BIT( SPI3->CR1 , SPI_CR1_SSI );

			/* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for (Full Duplex) */
			CLR_BIT(SPI3->CR1, SPI_CR1_BIDIMODE);

			/*SPI_CR1_LSBFIRST = 0 for MSB first*/
			CLR_BIT( SPI3->CR1 , SPI_CR1_LSBF );

			SPI3->CR2 = 0 ;

			/* Configure SPI Clock Polarity */
			if (HWUnit->spiCPOL == SPI_CPOL_LOW){
				CLR_BIT(SPI3->CR1, SPI_CR1_CPOL); /* 0: CK to 0 when idle */
			}else{
				SET_BIT(SPI3->CR1, SPI_CR1_CPOL); /* 1: CK to 1 when idle */
			}

			/* Configure SPI Clock Phase */
			if (HWUnit->spiCPHA == SPI_CPHA_LOW){
				CLR_BIT(SPI3->CR1, SPI_CR1_CPHA); /* 0: The first clock transition is the first data capture edge*/
			}else{
				SET_BIT(SPI3->CR1, SPI_CR1_CPHA); /* 1: The second clock transition is the first data capture edge */
			}
				
			if (HWUnit->spiDFF == SPI_DFF_16BITS){
				SET_BIT(SPI3->CR1, SPI_CR1_DFF); /* 1: 16-bit data frame format is selected for transmission/reception */
			}else if (HWUnit->spiDFF == SPI_DFF_8BITS){
				CLR_BIT(SPI3->CR1, SPI_CR1_DFF); /* 0: 8-bit data frame format is selected for transmission/reception */
			}else{/* Nothing */}

			/* Set Default Transmit Value */
			SPI3->DR = HWUnit->DefaultTransmitValue;


			/* Configure SPI Clock Speed */
			/* Clear the bits for clock speed <Mask bits 5:3> */
			SPI3->CR1 &= ~(0x7U << SPI_CR1_BR0);
			/* BR[2:0] bits for Baud Rate */
			SPI3->CR1 |= (HWUnit->SpiPrescaller << SPI_CR1_BR0);

			/* Enable SPI2 */
			SET_BIT(SPI3->CR1, SPI_CR1_SPE); // SPI_CR1_SPE = 1 to enable SPI

			/* Set SPI3 status to SPI_IDLE after initialization 
			* for avoiding Duplecated Initialization */ 
			Spi3_Status = SPI_IDLE;
			
			break;	
		
		case Spi_HWUnit_SPI4:
			/* GPIO Port Enabling SPI3 To be alternative pin*/
			Spi_GPIO_Init(HWUnitId, SPI4_PORT);

			/* Enable SPI3 Clock */
			SPI4_PCLK_EN();

			/* Reset SPI1 Configuration */
			SPI4->CR1 = 0;

			/* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
			SET_BIT(SPI4->CR1, SPI_CR1_MSTR );

			/* SSM=1, SSi=1 -> Software Slave Management Setting SSI, > to avoid MODF Error*/
			SET_BIT( SPI4->CR1 , SPI_CR1_SSM );
			SET_BIT( SPI4->CR1 , SPI_CR1_SSI );

			/* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for Full Duplex */
			CLR_BIT(SPI4->CR1, SPI_CR1_BIDIMODE);


			/*SPI_CR1_LSBFIRST = 0 for MSB first*/
			CLR_BIT( SPI4->CR1 , SPI_CR1_LSBF );

			SPI4->CR2 = 0 ;

			/* Configure SPI Clock Polarity */
			if (HWUnit->spiCPOL == SPI_CPOL_LOW){
				CLR_BIT(SPI4->CR1, SPI_CR1_CPOL); /* 0: CK to 0 when idle */
			}else{
				SET_BIT(SPI4->CR1, SPI_CR1_CPOL); /* 1: CK to 1 when idle */
			}

			/* Configure SPI Clock Phase */
			if (HWUnit->spiCPHA == SPI_CPHA_LOW){
				CLR_BIT(SPI4->CR1, SPI_CR1_CPHA); /* 0: The first clock transition is the first data capture edge*/
			}else{
				SET_BIT(SPI4->CR1, SPI_CR1_CPHA); /* 1: The second clock transition is the first data capture edge */
			}
						
			if (HWUnit->spiDFF == SPI_DFF_16BITS){
				SET_BIT(SPI3->CR1, SPI_CR1_DFF); /* 1: 16-bit data frame format is selected for transmission/reception */
			}else if (HWUnit->spiDFF == SPI_DFF_8BITS){
				CLR_BIT(SPI3->CR1, SPI_CR1_DFF); /* 0: 8-bit data frame format is selected for transmission/reception */
			}else{/* Nothing */}

			/* Set Default Transmit Value */
			SPI3->DR = HWUnit->DefaultTransmitValue;


			/* Configure SPI Clock Speed */
			/* Clear the bits for clock speed <Mask bits 5:3> */
			SPI4->CR1 &= ~(0x7U << SPI_CR1_BR0);
			/* BR[2:0] bits for Baud Rate */
			SPI4->CR1 |= (HWUnit->SpiPrescaller << SPI_CR1_BR0);

			/* Enable SPI4 */
			SET_BIT(SPI4->CR1, SPI_CR1_SPE); // SPI_CR1_SPE = 1 to enable SPI

			/* Set SPI3 status to SPI_IDLE after initialization 
			* for avoiding Duplecated Initialization */ 
			Spi3_Status = SPI_IDLE;
			
			break;	
	
		default:
			break;
	}

}





/**
 * @brief Spi_ChipSelect_Write : Service to set a level of a channel.
 * 
 * @param CS_Pin Pin of the Chip Select Pin (PIN0, ... PIN15)
 * @param CS_Port Port of the Chip Select Pin (PORTA,... PORTH)
 * @param Level Value to be written (STD_HIGH , STD_LOW)
 */
static void Spi_ChipSelect_Write(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port , Std_ReturnType Level)
{
    if ( (CS_Port >= PORTA && CS_Port <= PORTH )&& ( CS_Pin >= PIN0 && CS_Pin <= PIN15) && (Level == STD_HIGH || Level == STD_LOW))
    {
        /* 
        * USE BSRR register to provide atomic channel access 
        */
        switch (CS_Port)
		{
			case PORTA:
				if (Level == STD_HIGH){
					//GPIOA->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					//GPIOA->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;

			case PORTB:
				if (Level == STD_HIGH){
					GPIOB->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOB->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;

			case PORTC:
				if (Level == STD_HIGH){
					GPIOC->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOC->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;

			case PORTD:
				if (Level == STD_HIGH){
					GPIOD->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOD->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;
				
			case PORTE:
				if (Level == STD_HIGH){
					GPIOE->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOE->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;

			case PORTF:
				if (Level == STD_HIGH){
					GPIOF->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOF->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;

			case PORTG:
				if (Level == STD_HIGH){
					GPIOG->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOG->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;

			case PORTH:
				if (Level == STD_HIGH){
					GPIOH->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOH->BSRR = (1 << (CS_Pin + 16));
				}else{/*Nothing*/}
				break;
			
			default:
				break;
		}
	}
	else{
		return; // Exit the function
	}
}


/**
 * @brief 
 * 
 * @param port 
 * @param pin 
 */
static void Spi_ChipSelect_Init(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port ){

	switch(CS_Port){
			case PORTA:
				// Set PIN to  General purpose output mode
				//GPIOA->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				//GPIOA->MODER |=  (1 << ((CS_Pin*2)));
				/// Set PIN to  medium speed mode
				//GPIOA->OSPEEDR |= (1<< (CS_Pin*2));

				// Set PIN to  no pull or push
				//GPIOA->PUPDR &= ~( (0x3UL << ((CS_Pin*2))) );
			break;

			case PORTB:
				// Set PIN to  General purpose output mode
				GPIOB->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOB->MODER |=  (0x3UL << ((CS_Pin*2)));
				// Set PIN to  medium speed mode
				GPIOB->OSPEEDR |= (1<< (CS_Pin*2));
				// Set PIN to  no pull or push
				GPIOB->PUPDR &= ~( (0x3UL << ((CS_Pin*2))) );

				// Remove the unnecessary break statement
				// break;


				
			case PORTC:
				// Set PIN to  General purpose output mode
				GPIOC->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOC->MODER |=  (0x3UL << ((CS_Pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOC->OSPEEDR |= (1<< (CS_Pin*2));
				break;

				
			case PORTD:
				// Set PIN to  General purpose output mode
				GPIOD->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOD->MODER |=  (0x3UL << ((CS_Pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOD->OSPEEDR |= (1<< (CS_Pin*2));
				break;


			case PORTE:
				// Set PIN to  General purpose output mode
				GPIOE->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOE->MODER |=  (0x3UL << ((CS_Pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOE->OSPEEDR |= (1<< (CS_Pin*2));
				break;


			case PORTF:
				// Set PIN to  General purpose output mode
				GPIOF->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOF->MODER |=  (0x3UL << ((CS_Pin*2)));
				
				// Set PIN to  medium speed mode
				GPIOF->OSPEEDR |= (1<< (CS_Pin*2));
				break;



			case PORTG:
				// Set PIN to  General purpose output mode
				GPIOG->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOG->MODER |=  (0x3UL << ((CS_Pin*2)));

				// Set PIN to  medium speed mode
				GPIOG->OSPEEDR |= (1<< (CS_Pin*2));
				break;


			case PORTH:
				// Set PIN to  General purpose output mode
				GPIOH->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOH->MODER |=  (0x3UL << ((CS_Pin*2)));
				
				// Set PIN to  medium speed mode
				GPIOH->OSPEEDR |= (1<< (CS_Pin*2));
				break;

			default:
				break;
	}

}



/**
 * @brief 
 * 
 * @param Spi_select 
 * @param port 
 */
void Spi_GPIO_Init(Spi_HWUnitType Spi_select ,uint8 port){
	switch(Spi_select){
		case Spi_HWUnit_SPI1:
			if (port==PORTA)
			{
				// /* Enable GPIOA Clock */
				// GPIOA_PCLK_EN();

				// /*===================================================================*/
				// // Set PA5, PA6, and PA7 to alternate function mode (AF5 for SPI1)
				// GPIOA->MODER &= ~( (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U)) ); // Clear mode bits
				// GPIOA->MODER |= ( (0x2UL << (10U)) | (0x2UL << (12U)) | (0x2UL << (14U))  ); // Set to alternate function

				// // Set alternate function to AF5 (SPI1)
				// GPIOA->AFR[0] &= ~(  (0xF << (5 * 4)) | (0xF << (6 * 4)) | (0xF << (7 * 4))); // Clear AFR bits
				// GPIOA->AFR[0] |=  (5 << (5 * 4)) | (5 << (6 * 4)) | (5 << (7 * 4)); // Set AF5 for PA5, PA6, PA7

				// // Set PA5, PA6, and PA7 to very high speed
				// GPIOA->OSPEEDR |= (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U));

				// // Set PA5, PA6, and PA7 to no pull-up/pull-down
				// GPIOA->PUPDR &= ~( (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U)));
				/*===================================================================*/
			}else if (port==PORTB){
				// GPIOB_PCLK_EN();
				// /*===================================================================*/
				// // Set PB3, PB4, and PB5 to alternate function mode (AF5 for SPI1)
				// GPIOB->MODER &= ~( (0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U))  ); // Clear mode bits
				// GPIOB->MODER |= ( (0x2UL << (6U)) | (0x2UL << (8U)) | (0x2UL << (10U)) ); // Set to alternate function

				// // Set alternate function to AF5 (SPI1)
				// GPIOB->AFR[0] &= ~( (0xF << (3 * 4)) | (0xF << (4 * 4)) | (0xF << (5 * 4))); // Clear AFR bits
				// GPIOB->AFR[0] |=  (5 << (3 * 4)) | (5 << (4 * 4)) | (5 << (5 * 4)); // Set AF5 for PB3, PB4, PB5

				// // Set PB3, PB4, and PB5 to very high speed
				// GPIOB->OSPEEDR |= (0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U)) ;

				// // Set PB3, PB4, and PB5 to no pull-up/pull-down
				// GPIOB->PUPDR &= ~((0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U)) );
				/*===================================================================*/
			}else{/* Nothing */}
		break;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case Spi_HWUnit_SPI2:
			if (port==PORTB){
				GPIOB_PCLK_EN();	
				/*===================================================================*/
				// Set PB13, PB14, and PB15 to alternate function mode (AF5 for SPI2)
				GPIOB->MODER &= ~( (0x3UL << (26U)) | (0x3UL << (28U)) | (0x3UL << (30U))  ); // Clear mode bits
				GPIOB->MODER |= ( (0x2UL << (26U)) | (0x2UL << (28U)) | (0x2UL << (30U)) ); // Set to alternate function

				// Set alternate function to AF5 (SPI2)
				GPIOB->AFR[1] &= ~( (0xF << (5 * 4)) | (0xF << (6 * 4)) | (0xF << (7 * 4))); // Clear AFR bits
				GPIOB->AFR[1] |=  (5 << (5 * 4)) | (5 << (6 * 4)) | (5 << (7 * 4)); // Set AF5 for PB3, PB4, PB5

				// Set PB13, PB14, and PB15 to very high speed
				GPIOB->OSPEEDR |= (0x3UL << (26U)) | (0x3UL << (28U)) | (0x3UL << (30U)) ;

				// Set PB13, PB14, and PB15 to no pull-up/pull-down
				GPIOB->PUPDR &= ~((0x3UL << (26U)) | (0x3UL << (28U)) | (0x3UL << (30U)) );
				/*===================================================================*/
			}else if (port==PORTC){
				GPIOC_PCLK_EN();
				/*===================================================================*/
				// Set PC2, PC3, PC7 to alternate function mode (AF5 for SPI2)
				GPIOC->MODER &= ~( (0x3UL << (4U)) | (0x3UL << (6U)) | (0x3UL << (14U))  ); // Clear mode bits
				GPIOC->MODER |= ( (0x2UL << (4U)) | (0x2UL << (6U)) | (0x2UL << (14U)) ); // Set to alternate function

				// Set alternate function to AF5 (SPI2)
				GPIOC->AFR[1] &= ~( (0xF << (2 * 4)) | (0xF << (3 * 4)) | (0xF << (7 * 4))); // Clear AFR bits
				GPIOC->AFR[1] |=  (5 << (2 * 4)) | (5 << (3 * 4)) | (5 << (7 * 4)); // Set AF5 for PC2, PC3, PC7

				// Set PC2, PC3, PC7 to very high speed
				GPIOC->OSPEEDR |= (0x3UL << (4U)) | (0x3UL << (6U)) | (0x3UL << (14U)) ;

				// Set PC2, PC3, PC7 to no pull-up/pull-down
				GPIOC->PUPDR &= ~((0x3UL << (4U)) | (0x3UL << (6U)) | (0x3UL << (14U)) );
				/*===================================================================*/
			}else{/* Nothing */}

		break;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case Spi_HWUnit_SPI3:
			if (port==PORTB){
				GPIOB_PCLK_EN();
				/*===================================================================*/
				// Set PB3, PB4, and PB5 to alternate function mode (AF6 for SPI3)
				GPIOB->MODER &= ~( (0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U))  ); // Clear mode bits
				GPIOB->MODER |= ( (0x2UL << (6U)) | (0x2UL << (8U)) | (0x2UL << (10U)) ); // Set to alternate function

				// Set alternate function to AF5 (SPI1)
				GPIOC->AFR[0] &= ~((0xF << (3 * 4)) | (0xF << (4 * 4)) | (0xF << (5 * 4)) ); // Clear AFR bits
				GPIOC->AFR[0] |= (6 << (3 * 4)) | (6 << (4 * 4)) | (6 << (5 * 4)); // Set AF6 for PB3, PB4, PB5

				// Set PB3, PB4, and PB5 to very high speed
				GPIOC->OSPEEDR |= (0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U)) ;

				// Set PB3, PB4, and PB5 to no pull-up/pull-down
				GPIOC->PUPDR &= ~((0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U)) );
				/*===================================================================*/
			}else if (port==PORTC){
				GPIOC_PCLK_EN();
				/*===================================================================*/
				// Set PC10, PC11, PC12 to alternate function mode (AF6 for SPI3)
				GPIOC->MODER &= ~( (0x3UL << (20U)) | (0x3UL << (22U)) | (0x3UL << (24U))  ); // Clear mode bits
				GPIOC->MODER |= ( (0x2UL << (20U)) | (0x2UL << (22U)) | (0x2UL << (24U)) ); // Set to alternate function

				// Set alternate function to AF6 (SPI3)
				GPIOC->AFR[1] &= ~( (0xF << (2 * 4)) | (0xF << (3 * 4)) | (0xF << (4 * 4))); // Clear AFR bits
				GPIOC->AFR[1] |=  (6 << (2 * 4)) | (6 << (3 * 4)) | (6 << (4 * 4)); // Set AF5 for PC10, PC11, PC12

				// Set PC2, PC3, PC7 to very high speed
				GPIOC->OSPEEDR |= (0x3UL << (20U)) | (0x3UL << (22U)) | (0x3UL << (24U)) ;

				// Set PC2, PC3, PC7 to no pull-up/pull-down
				GPIOC->PUPDR &= ~((0x3UL << (20U)) | (0x3UL << (22U)) | (0x3UL << (24U)) );
				/*===================================================================*/
			}else{/* Nothing */}
			
		break;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case Spi_HWUnit_SPI4:
			if (port==PORTE){
				GPIOE_PCLK_EN();
				/*===================================================================*/
				// Set PE2, PE5, and PE6 to alternate function mode (AF5 for SPI4)
				GPIOE->MODER &= ~( (0x3UL << (4U)) | (0x3UL << (10U)) | (0x3UL << (12U))  ); // Clear mode bits
				GPIOE->MODER |= ( (0x2UL << (4U)) | (0x2UL << (10U)) | (0x2UL << (12U)) ); // Set to alternate function

				// Set alternate function to AF5 (SPI4)
				GPIOE->AFR[0] &= ~( (0xF << (2 * 4)) | (0xF << (5 * 4)) | (0xF << (6 * 4))); // Clear AFR bits
				GPIOE->AFR[0] |=  (5 << (2 * 4)) | (5 << (3 * 4)) | (5 << (4 * 4)); // Set AF5 for PE2, PE5, and PE6

				// Set PE2, PE5, and PE6 to very high speed
				GPIOE->OSPEEDR |= (0x3UL << (4U)) | (0x3UL << (10U)) | (0x3UL << (12U)) ;

				// Set PE2, PE5, and PE6 to no pull-up/pull-down
				GPIOE->PUPDR &= ~((0x3UL << (4U)) | (0x3UL << (10U)) | (0x3UL << (12U)) );
				/*===================================================================*/
			}else if (port==PORTG){
				GPIOG_PCLK_EN();
				/*===================================================================*/
				// Set PG11, PG12, and PG13 to alternate function mode (AF6 for SPI4)
				GPIOG->MODER &= ~( (0x3UL << (22U)) | (0x3UL << (24U)) | (0x3UL << (26U))  ); // Clear mode bits
				GPIOG->MODER |= ( (0x2UL << (22U)) | (0x2UL << (24U)) | (0x2UL << (26U)) ); // Set to alternate function

				// Set alternate function to AF6 (SPI3)
				GPIOG->AFR[1] &= ~( (0xF << (3 * 4)) | (0xF << (4 * 4)) | (0xF << (5 * 4))); // Clear AFR bits
				GPIOG->AFR[1] |=  (6 << (3 * 4)) | (6 << (4 * 4)) | (6 << (5 * 4)); // Set AF6 for PG11, PG12, and PG13

				// Set PG11, PG12, and PG13 to very high speed
				GPIOG->OSPEEDR |= (0x3UL << (22U)) | (0x3UL << (24U)) | (0x3UL << (26U)) ;

				// Set PG11, PG12, and PG13 to no pull-up/pull-down
				GPIOG->PUPDR &= ~((0x3UL << (22U)) | (0x3UL << (24U)) | (0x3UL << (26U)) );
				/*===================================================================*/
			}else{/* Nothing */}

		break;
	}
}




/**
 * @brief system initialization for mcu clock
 *  using RCC_CR register for using HSI clock source
 */
void System_Init(void){

	RCC->CFGR = 0x00000000;
	RCC->CR &= 0xFEF6FFFF;
	RCC->CR |= 1;
	while(READ_BIT((RCC->CR), 0));
}


/**
 * @brief 
 * 
 * @param port 
 * @param pin 
 */
void GPIO_SPI_SlaveSelect (uint8 port, uint8 pin){

	switch(port){
			case PORTA:
			
				// Set PIN to  General purpose output mode
				GPIOA->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOA->MODER |=  (1 << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOA->OSPEEDR |= (1<< (pin*2));

				// Set PIN to  no pull or push
				GPIOA->PUPDR &= ~( (0x3UL << ((pin*2))) );
			break;


			case PORTB:
				// Set PIN to  General purpose output mode
				GPIOB->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOB->MODER |=  (0x3UL << ((pin*2)));
				// Set PIN to  medium speed mode
				GPIOB->OSPEEDR |= (1<< (pin*2));
				// Set PIN to  no pull or push
				GPIOA->PUPDR &= ~( (0x3UL << ((pin*2))) );
				break;


				
			case PORTC:
				// Set PIN to  General purpose output mode
				GPIOC->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOC->MODER |=  (0x3UL << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOC->OSPEEDR |= (1<< (pin*2));
				break;

				
			case PORTD:
				// Set PIN to  General purpose output mode
				GPIOD->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOD->MODER |=  (0x3UL << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOD->OSPEEDR |= (1<< (pin*2));
				break;


			case PORTE:
				// Set PIN to  General purpose output mode
				GPIOE->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOE->MODER |=  (0x3UL << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOE->OSPEEDR |= (1<< (pin*2));
				break;


			case PORTF:
				// Set PIN to  General purpose output mode
				GPIOF->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOF->MODER |=  (0x3UL << ((pin*2)));
				
				// Set PIN to  medium speed mode
				GPIOF->OSPEEDR |= (1<< (pin*2));
				break;



			case PORTG:
				// Set PIN to  General purpose output mode
				GPIOG->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOG->MODER |=  (0x3UL << ((pin*2)));

				// Set PIN to  medium speed mode
				GPIOG->OSPEEDR |= (1<< (pin*2));
				break;


			case PORTH:
				// Set PIN to  General purpose output mode
				GPIOH->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOH->MODER |=  (0x3UL << ((pin*2)));
				
				// Set PIN to  medium speed mode
				GPIOH->OSPEEDR |= (1<< (pin*2));
				break;
	}

}




int main() {
    Spi_Init(&Spi_Config);

    return 0;
}