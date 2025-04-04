/**
 * @file SPI.c
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Serial Perpheral Interface Source File
 * @version info : @ module : SPI Handler/Driver @ Platform : stm32f446re @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 */

/********************************************** Section : Includes ********************************************/
#include "../inc/Spi_Cfg.h"  
#include "../inc/Spi.h"



/**************************************** Section: Data Type Declarations **************************************/

/***************************************** Section : User Configurations **************************************/



/************************************* Section : Global Variables Definations **********************************/

/* Define the current status of the SPI module 
    Shared variable between APIs 
	Defined By Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit)
*/
static Spi_StatusType Spi1_Status = SPI_UNINIT;
static Spi_StatusType Spi2_Status = SPI_UNINIT;
static Spi_StatusType Spi3_Status = SPI_UNINIT;
static Spi_StatusType Spi4_Status = SPI_UNINIT;


Std_VersionInfoType Spi_VersionInfo = {
    .vendorID = SPI_SW_vendor_ID,
    .moduleID = SPI_SW_moduleID,
    .sw_major_version = SPI_SW_major_version,
    .sw_minor_version = SPI_SW_minor_version,
    .sw_patch_version = SPI_SW_patch_version
};


/**************************************** Section : Functions Definations ***************************************/



/****************************************************************************************************************/
/******************************************* Section : Local Functions ******************************************/
/****************************************************************************************************************/
static void Spi_lhw_Init(const Spi_HWUnitType HWUnitId, const Spi_HWUnitConfigType * HWUnit );
static void Spi_GPIO_Init(Spi_HWUnitType Spi_select ,uint8 port);
static void Spi_ChipSelect_Init(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port );
static void Spi_ChipSelect_Write(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port , Std_ReturnType Level);



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
// adding new comment for testing
void Spi_Init(const Spi_ConfigType* ConfigPtr)
{
	if (ConfigPtr == NULL_PTR)
	{
		/*Det_ReportError*/
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_INIT_SID, SPI_E_PARAM_POINTER);
	}
	else
	{
		
		ConfigPtr->Spi_SeqConfigPtr->Seq_Status = SPI_SEQ_PENDING;

		for (uint8 Jobs_Index = 0; Jobs_Index < ConfigPtr->Spi_SeqConfigPtr->NoOfJobs; Jobs_Index++)
		{
		    Spi_JobConfigType *jobConfig = &(ConfigPtr->Spi_JobConfigPtr[Jobs_Index]);
		    for (uint8 channels_index = 0; channels_index < jobConfig->NoOfChannels; channels_index++)
		    {
		        Spi_ChannelType channelId = jobConfig->ChannelsPtr[channels_index]; // Access channel ID
		        Spi_ChannelConfigType *channelConfig = &(ConfigPtr->Spi_ChannelConfigPtr[channelId]);

		        if (channelConfig->Channel_Status == SPI_UNINIT)
		        {
		            /* Initialization of the Chip Select Pin */
		            Spi_ChipSelect_Init(channelConfig->spiCSPort, channelConfig->spiCSPin);

		            /* Set SPI status to SPI_IDLE after initialization */
		            channelConfig->Channel_Status = SPI_IDLE;

		        }
		        else
		        {
					/*	A re-initialization of a SPI Handler/Driver by executing the Spi_Init() function requires
						a de-initialization before by executing a Spi_DeInit().

						Spi_DeInit() */

					/*Det_ReportError with SPI_Init service called while the SPI driver has been already initialized */

		            Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_INIT_SID, SPI_E_ALREADY_INITIALIZED );
					 
					ConfigPtr->Spi_SeqConfigPtr->Seq_Status = SPI_SEQ_FAILED;
					ConfigPtr->Spi_JobConfigPtr[Jobs_Index].Job_Status = SPI_JOB_FAILED;
		        }
				
		    }

		    /* Initialize the SPI Hardware Unit */
		    Spi_lhw_Init(jobConfig->spiHWUint, jobConfig->SpiHWUnitConfig);
			ConfigPtr->Spi_JobConfigPtr[Jobs_Index].Job_Status = SPI_JOB_OK;
			
		}
		ConfigPtr->Spi_SeqConfigPtr->Seq_Status = SPI_SEQ_OK;

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
    Std_ReturnType retVar = E_NOT_OK;
	Spi_JobConfigType * jobConfig ;

	
	if (DataBufferPtr == (Spi_DataBufferType*)NULL_PTR)
	{
		/*Det_ReportError with wrong data buffer pointer */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_POINTER);

	}else if (Channel < SPI_Channel_1 || Channel > SPI_Channel_4){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_CHANNEL);

	}else if (Spi_Config_Ptr == (Spi_ConfigType*)NULL_PTR){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_UNINIT);
	
	}else if (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint > Spi_HWUnit_SPI4 || Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint < Spi_HWUnit_SPI1){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_UNIT);
	
	}else{

		/* Search for the job that contains the given channel */
		for (uint8 Jobs_Index = 0; Jobs_Index < Spi_Config.Spi_SeqConfigPtr->NoOfJobs; Jobs_Index++)
		{
			* jobConfig = (Spi_Config.Spi_JobConfigPtr[Jobs_Index]);
			if (jobConfig->ChannelsPtr[Channel] == Channel){
				break;
			}
		}

		/* Set the channel status to SPI_BUSY */
		Spi_Config.Spi_ChannelConfigPtr[Channel].Channel_Status=SPI_BUSY;

		switch (jobConfig->spiHWUint)
		{
			case Spi_HWUnit_SPI1:
				/* Write the data to the Data Register */
				SPI1->DR = *DataBufferPtr;
				retVar = E_OK;
				break;
			
			case Spi_HWUnit_SPI2:
				/* Write the data to the Data Register */
				SPI2->DR = *DataBufferPtr;
				retVar = E_OK;
				break;

			case Spi_HWUnit_SPI3:
				/* Write the data to the Data Register */
				SPI3->DR = *DataBufferPtr;
				retVar = E_OK;
				break;

			case Spi_HWUnit_SPI4:
				/* Write the data to the Data Register */
				SPI4->DR = *DataBufferPtr;
				retVar = E_OK;
				break;
				
			default: break;
		}

		/* Set the channel status to SPI_IDLE */
		Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].Channel_Status=SPI_IDLE;
		jobConfig->Job_Status = SPI_JOB_OK;
		Spi_Config.Spi_SeqConfigPtr->Seq_Status = SPI_JOB_OK;

	}

	return retVar;
}
////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief  [SWS_Spi_00179] Spi_ReadIB : Service for reading synchronously one or more data 
 * 		   from an IB SPI Handler/Driver Channel specified by parameter.
 *         
 * @param  Channel Channel ID.
 * @param  DataBufferPtr Pointer to source data buffer.
 * @return Std_ReturnType :
 * 	          E_OK: Spi_WriteIB command has been accepted 
 *            E_NOT_OK: Spi_WriteIB command has not been accepted
 */
Std_ReturnType Spi_ReadIB ( Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer ){

    Std_ReturnType retVar = E_NOT_OK;
	Spi_JobConfigType * jobConfig ;


    if (Spi_Config_Ptr == NULL_PTR || (Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].BufferType != InternalBuffer) )
    {
        Det_ReportError(SPI_SW_moduleID, 0, SPI_READ_IB_SID, SPI_E_UNINIT);
		retVar = E_NOT_OK;
    }
    else if (DataBufferPointer == (Spi_DataBufferType*)NULL_PTR)
	{
		/*Det_ReportError with wrong data buffer pointer */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_READ_IB_SID, SPI_E_PARAM_POINTER);
		retVar = E_NOT_OK;

	}else{
		/* Search for the job that contains the given channel */
		for (uint8 Jobs_Index = 0; Jobs_Index < Spi_Config.Spi_SeqConfigPtr->NoOfJobs; Jobs_Index++)
		{
			* jobConfig = (Spi_Config.Spi_JobConfigPtr[Jobs_Index]);
			if (jobConfig->ChannelsPtr[Channel] == Channel){
				break;
			}
		}
		
		
		/* Set the channel status to SPI_BUSY */
		Spi_Config.Spi_ChannelConfigPtr[Channel].Channel_Status=SPI_BUSY;
		jobConfig->Job_Status = SPI_JOB_PENDING;
		Spi_Config.Spi_SeqConfigPtr->Seq_Status = SPI_SEQ_PENDING;

		switch (jobConfig->spiHWUint)
		{
			case Spi_HWUnit_SPI1:
				* DataBufferPointer = SPI1->DR;
				retVar = E_OK; break;
			
			case Spi_HWUnit_SPI2:
				* DataBufferPointer = SPI2->DR;
				retVar = E_OK; break;

			case Spi_HWUnit_SPI3:
				* DataBufferPointer = SPI3->DR;
				retVar = E_OK; break;

			case Spi_HWUnit_SPI4:
				* DataBufferPointer = SPI4->DR;
				retVar = E_OK; break;
				
			default:
				/* Handle unknown SPI hardware unit */
				Det_ReportError(SPI_SW_moduleID, 0, SPI_READ_IB_SID, SPI_E_UNINIT);
				retVar = E_NOT_OK;

			break;
		}

		Spi_Config.Spi_ChannelConfigPtr[Channel].Channel_Status=SPI_IDLE;
		jobConfig->Job_Status = SPI_JOB_OK;
		Spi_Config.Spi_SeqConfigPtr->Seq_Status = SPI_JOB_OK;
    }
    return retVar;
}

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 * This function initializes the SPI driver according `Spi_ConfigType` structure.
 *  -> Disable the SPI Peripheral Clocks: For each SPI hardware unit (e.g., SPI1, SPI2, etc.)
 *  -> Reset SPI Control Registers: Reset the control registers (e.g., CR1, CR2, etc.)
 *  -> Clear the Driver Status: to indicate that the SPI peripheral is no longer initialized or in use.
 *       
 * 
 * @return Std_ReturnType 
 *
 * @note De-initialization requires prior Initialization.
 */
Std_ReturnType Spi_DeInit (void){

	Std_ReturnType retVar = E_NOT_OK;

	if (Spi_Config_Ptr == (Spi_ConfigType*)NULL_PTR){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_DEINIT_SID, SPI_E_UNINIT);
		retVar = E_NOT_OK;
	
	}else{
		for (uint8 Jobs_Index = 0; Jobs_Index < Spi_Config.Spi_SeqConfigPtr->NoOfJobs; Jobs_Index++)
		{
			Spi_JobConfigType *jobConfig = &(Spi_Config.Spi_JobConfigPtr[Jobs_Index]);
			switch (jobConfig->spiHWUint){
				case Spi_HWUnit_SPI1:
					/* Disable SPI1 Clock */
					SPI1_PCLK_DI();
					/* Reset SPI1 Control Registers */
					SPI1->CR1 = 0;
					SPI1->CR2 = 0;
					SPI1->SR = 0;
					/* Set the status to uninitialized */
					Spi1_Status = SPI_UNINIT;

					break;
				case Spi_HWUnit_SPI2:
					/* Disable SPI2 Clock */
					SPI2_PCLK_DI();
					/* Reset SPI2 Control Registers */
					SPI2->CR1 = 0;
					SPI2->CR2 = 0;
					SPI2->SR = 0;
					/* Set the status to uninitialized */
					Spi2_Status = SPI_UNINIT;

					break;
				case Spi_HWUnit_SPI3:
					/* Disable SPI3 Clock */
					SPI3_PCLK_DI();
					/* Reset SPI3 Control Registers */
					SPI3->CR1 = 0;
					SPI3->CR2 = 0;
					SPI3->SR = 0;
					/* Set the status to uninitialized */
					Spi3_Status = SPI_UNINIT;

					break;
				case Spi_HWUnit_SPI4:
					/* Disable SPI4 Clock */
					SPI4_PCLK_DI();
					/* Reset SPI4 Control Registers */
					SPI4->CR1 = 0;
					SPI4->CR2 = 0;
					SPI4->SR = 0;
					/* Set the status to uninitialized */
					Spi4_Status = SPI_UNINIT;

					break;	
				
				default:
					break;
				}
			for (uint8 channels_index = 0; channels_index < jobConfig->NoOfChannels; channels_index++)
			{
				Spi_ChannelType channelId = jobConfig->ChannelsPtr[channels_index]; // Access channel ID
				Spi_ChannelConfigType *channelConfig = &(Spi_Config.Spi_ChannelConfigPtr[channelId]);

				if (channelConfig->Channel_Status == SPI_IDLE )
				{
					channelConfig->Channel_Status = SPI_UNINIT;
				}
			}
			retVar = E_OK;
		}
	}
 	return retVar;
}



////////////////////////////////////////////////////////////////////////////////////////////

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
						Spi_Status = SPI_UNINIT; /* Bit 6 SPE: SPI enable 0: Peripheral disabled */ 
					}else if ( READ_BIT( (SPI1->SR) , SPI_SR_BSY) == 0) {
						Spi_Status = SPI_IDLE; /* 0: SPI (or I2S) not busy <Bit 7 BSY: Busy flag> */ 
					}else if ( READ_BIT( (SPI1->SR) , SPI_SR_BSY) == 1) {	
						Spi_Status = SPI_BUSY; /* 1: SPI (or I2S) is busy in communication or Tx buffer is not empty <Bit 7 BSY: Busy flag> */
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
						Spi_Status = SPI_IDLE;   /* 0: SPI (or I2S) not busy <Bit 7 BSY: Busy flag> */ 
					}else if ( READ_BIT( (SPI4->SR) , SPI_SR_BSY) == 1) {	
						Spi_Status = SPI_BUSY;   /* 1: SPI (or I2S) is busy in communication or Tx buffer is not empty <Bit 7 BSY: Busy flag> */
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
////////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief : Spi_GetJobResult [SWS_Spi_00182] : This service returns the last transmission
		  result of the specified Job.
*
* @param: Job: Job ID
* @return : Spi_JobResultType: SPI_JOB_OK - SPI_JOB_PENDING - SPI_JOB_FAILED - SPI_JOB_QUEUED
* 
* @Description: 
**/
Spi_JobResultType Spi_GetJobResult(Spi_JobType Job)
{
    return Spi_Config.Spi_JobConfigPtr[Job].Job_Status;
}

////////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief : Spi_GetSequenceResult [SWS_Spi_00183]:  This service returns the last transmission 
		  result of the specified Sequence.
*
* @param : Sequence: Sequence ID. 
* @return : Spi_SeqResultType: SPI_SEQ_OK - SPI_SEQ_PENDING - SPI_SEQ_FAILED - SPI_SEQ_QUEUED
* 
**/
Spi_SeqResultType Spi_GetSequenceResult(Spi_SequenceType Sequence)
{
    return Spi_Config.Spi_SeqConfigPtr[Sequence].Seq_Status;
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
			SPI1_PCLK_EN();

			/* Reset SPI1 Configuration */
			SPI1->CR1 = 0;

			/* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
			SET_BIT(SPI1->CR1, SPI_CR1_MSTR );

			/* SSM=1, SSi=1 -> Software Slave Management Setting SSI, > to avoid MODF Error*/
			SET_BIT( SPI1->CR1 , SPI_CR1_SSM );
			SET_BIT( SPI1->CR1 , SPI_CR1_SSI );

			/* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for Full Duplex */
			CLR_BIT(SPI1->CR1, SPI_CR1_BIDIMODE);


			/*SPI_CR1_LSBFIRST = 0 for MSB first*/
			CLR_BIT( SPI1->CR1 , SPI_CR1_LSBF );

			SPI1->CR2 = 0 ;

			/* Configure SPI Clock Polarity */
			if (HWUnit->spiCPOL == SPI_CPOL_LOW){
				CLR_BIT(SPI1->CR1, SPI_CR1_CPOL); /* 0: CK to 0 when idle */
			}else{
				SET_BIT(SPI1->CR1, SPI_CR1_CPOL); /* 1: CK to 1 when idle */
			}

			/* Configure SPI Clock Phase */
			if (HWUnit->spiCPHA == SPI_CPHA_LOW){
				CLR_BIT(SPI1->CR1, SPI_CR1_CPHA); /* 0: The first clock transition is the first data capture edge*/
			}else{
				SET_BIT(SPI1->CR1, SPI_CR1_CPHA); /* 1: The second clock transition is the first data capture edge */
			}

			if (HWUnit->spiDFF == SPI_DFF_16BITS){
				SET_BIT(SPI1->CR1, SPI_CR1_DFF); /* 1: 16-bit data frame format is selected for transmission/reception */
			}else if (HWUnit->spiDFF == SPI_DFF_8BITS){
				CLR_BIT(SPI1->CR1, SPI_CR1_DFF); /* 0: 8-bit data frame format is selected for transmission/reception */
			}else{/* Nothing */}

			/* Set Default Transmit Value */
			SPI1->DR = HWUnit->DefaultTransmitValue;

			/* Configure SPI Clock Speed */
			/* Clear the bits for clock speed <Mask bits 5:3> */
			SPI1->CR1 &= ~(0x7U << SPI_CR1_BR0);
			/* BR[2:0] bits for Baud Rate */
			SPI1->CR1 |= (HWUnit->SpiPrescaller << SPI_CR1_BR0);

			/* Enable SPI1 */
			SET_BIT(SPI1->CR1, SPI_CR1_SPE); // SPI_CR1_SPE = 1 to enable SPI

			/* Set SPI1 status to SPI_IDLE after initialization 
			* for avoiding Duplecated Initialization */ 
			Spi1_Status = SPI_IDLE;

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
					GPIOA->BSRR = (1 << CS_Pin);
				}else if (Level == STD_LOW){
					GPIOA->BSRR = (1 << (CS_Pin + 16));
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
				GPIOA->MODER &= ~( (0x3UL << ((CS_Pin*2))) | ( 0x3UL << (((CS_Pin*2)+1)) ) );
				GPIOA->MODER |=  (1 << ((CS_Pin*2)));
				// Set PIN to  medium speed mode
				GPIOA->OSPEEDR |= (1<< (CS_Pin*2));

				// Set PIN to  no pull or push
				GPIOA->PUPDR &= ~( (0x3UL << ((CS_Pin*2))) );
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
				/* Enable GPIOA Clock */
				GPIOA_PCLK_EN();

				/*===================================================================*/
				// Set PA5, PA6, and PA7 to alternate function mode (AF5 for SPI1)
				GPIOA->MODER &= ~( (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U)) ); // Clear mode bits
				GPIOA->MODER |= ( (0x2UL << (10U)) | (0x2UL << (12U)) | (0x2UL << (14U))  ); // Set to alternate function

				// Set alternate function to AF5 (SPI1)
				GPIOA->AFR[0] &= ~(  (0xF << (5 * 4)) | (0xF << (6 * 4)) | (0xF << (7 * 4))); // Clear AFR bits
				GPIOA->AFR[0] |=  (5 << (5 * 4)) | (5 << (6 * 4)) | (5 << (7 * 4)); // Set AF5 for PA5, PA6, PA7

				// Set PA5, PA6, and PA7 to very high speed
				GPIOA->OSPEEDR |= (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U));

				// Set PA5, PA6, and PA7 to no pull-up/pull-down
				GPIOA->PUPDR &= ~( (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U)));
				/*===================================================================*/
			}else if (port==PORTB){
				GPIOB_PCLK_EN();
				/*===================================================================*/
				// Set PB3, PB4, and PB5 to alternate function mode (AF5 for SPI1)
				GPIOB->MODER &= ~( (0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U))  ); // Clear mode bits
				GPIOB->MODER |= ( (0x2UL << (6U)) | (0x2UL << (8U)) | (0x2UL << (10U)) ); // Set to alternate function

				// Set alternate function to AF5 (SPI1)
				GPIOB->AFR[0] &= ~( (0xF << (3 * 4)) | (0xF << (4 * 4)) | (0xF << (5 * 4))); // Clear AFR bits
				GPIOB->AFR[0] |=  (5 << (3 * 4)) | (5 << (4 * 4)) | (5 << (5 * 4)); // Set AF5 for PB3, PB4, PB5

				// Set PB3, PB4, and PB5 to very high speed
				GPIOB->OSPEEDR |= (0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U)) ;

				// Set PB3, PB4, and PB5 to no pull-up/pull-down
				GPIOB->PUPDR &= ~((0x3UL << (6U)) | (0x3UL << (8U)) | (0x3UL << (10U)) );
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