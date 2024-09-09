
#include "Spi.hpp"

uint8 ChipSelect_count =0; 
uint8  Spi_lhw_count=0;
uint8 CHECK_LIMITS=0;
uint8 check =0;
uint8 CHECK_SPI_VAL1=0;
uint8 check_status=0;
uint8 check_read=0;
// Spi_ChannelType SPI_job1_channels[] = {0, 1};
// Spi_ChannelType SPI_job2_channels[] = {2, 3};

static void Spi_ChipSelect_Init(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port )
{
ChipSelect_count++;
return;

}


static void Spi_lhw_Init(const Spi_HWUnitType HWUnitId, const Spi_HWUnitConfigType * HWUnit ){
 Spi_lhw_count++;
return;
}

// Reset the SPI1 register before each test
void SetUp() {
    SPI1.CR1 = 0x00000800;  // Clear the CR1 register
    Det_Error_Buffer[Det_Error_Buffer_index] = {0}; 
	Spi_ConfigType*  Spi_Config_Ptr = (Spi_ConfigType* )NULL_PTR;
 ChipSelect_count =0; 
  Spi_lhw_count=0;

}


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
            Spi_JobConfigType *jobConfig = &(ConfigPtr->Spi_JobConfigPtr[Jobs_Index]);
            for (uint8 channels_index = 0; channels_index < jobConfig->NoOfChannels; channels_index++)
            {
                Spi_ChannelType channelId = jobConfig->ChannelsPtr[channels_index]; // Access channel ID
                Spi_ChannelConfigType *channelConfig = &(ConfigPtr->Spi_ChannelConfigPtr[channelId ]);

                if (channelConfig->Status == SPI_UNINIT)
                {
                    /* Initialization of the Chip Select Pin */
                    Spi_ChipSelect_Init(channelConfig->spiCSPort, channelConfig->spiCSPin);

                    /* Set SPI status to SPI_IDLE after initialization */
                    channelConfig->Status = SPI_IDLE;
                }
                else
                {
                    /*  A re-initialization of a SPI Handler/Driver by executing the Spi_Init() function requires
                        a de-initialization before by executing a Spi_DeInit().

                        Spi_DeInit() */

                    /*Det_ReportError with SPI_Init service called while the SPI driver has been already initialized */

                    Det_ReportError(SPI_SW_moduleID, (uint8)0, SPI_INIT_SID, SPI_E_ALREADY_INITIALIZED );
                }
            }
            /* Initialize the SPI Hardware Unit */
            Spi_lhw_Init(jobConfig->spiHWUint, jobConfig->SpiHWUnitConfig);
        }
    }
}




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
	Spi_JobConfigType * jobConfig ;
	Spi_JobConfigType * Temp_jobConfig ;
	if (DataBufferPtr == (Spi_DataBufferType*)NULL_PTR)
	{
		/*Det_ReportError with wrong data buffer pointer */
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_POINTER);

	}else if (Channel < SPI_Channel_1 || Channel > SPI_Channel_4){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_CHANNEL);

	}else if (Spi_Config_Ptr == (Spi_ConfigType*)NULL_PTR){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_UNINIT);
	
	}
	else if (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint > Spi_HWUnit_SPI4 || Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint < Spi_HWUnit_SPI1){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_WRITE_IB_SID, SPI_E_PARAM_UNIT);
	CHECK_SPI_VAL1=Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint;
	}
	else{



uint32 channelId = Spi_Config_Ptr->Spi_ChannelConfigPtr->SpiChannelId;
uint32 totalChannels = Spi_Config_Ptr->Spi_JobConfigPtr->NoOfChannels;
// // Check if the Channel is out of bounds (below minimum or above maximum)
// if (channelId + Channel >= totalChannels || channelId < Channel) {
//     CHECK_LIMITS = 8;  // Set a flag or error code
//     return ret;        // Return the error or status
// }


CHECK_SPI_VAL1=Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint;
		/* Set the channel status to SPI_BUSY */
		Spi_Config.Spi_ChannelConfigPtr[Channel].Status=SPI_BUSY;
		check_status=Spi_Config.Spi_ChannelConfigPtr[Channel].Status;
		check=65;

		switch (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint)
		{
			case Spi_HWUnit_SPI1:
			if ((SPI_job1_channels[totalChannels-1] < Channel ) || (SPI_job1_channels[0] > Channel) )
			{
				CHECK_LIMITS = 8;
			return ret;
			}
				/* Write the data to the Data Register */
				SPI1.DR = *DataBufferPtr;
				ret = E_OK;
			break;
			
			case Spi_HWUnit_SPI2:

			if ((SPI_job2_channels[totalChannels-1] < Channel) || (SPI_job1_channels[0] > Channel) )
			{
			CHECK_LIMITS = 8;
			return ret;
			}

				/* Write the data to the Data Register */
				SPI2.DR = *DataBufferPtr;
				ret = E_OK;
			break;

			case Spi_HWUnit_SPI3:
				/* Write the data to the Data Register */
				SPI3.DR = *DataBufferPtr;
				ret = E_OK;
				break;

			case Spi_HWUnit_SPI4:
				/* Write the data to the Data Register */
				SPI4.DR = *DataBufferPtr;
				ret = E_OK;
				break;
				
			default: break;
		}
		/* Set the channel status to SPI_IDLE */
		Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].Status= SPI_IDLE;
	}

	return ret;
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

	check_read=9;
	// Spi_ConfigType*  Spi_Config_Ptr = (Spi_ConfigType* )NULL_PTR;
// if (Spi_Config_Ptr == (Spi_ConfigType*)NULL_PTR){
// 		Det_ReportError(SPI_SW_moduleID, (uint8) 0,  SPI_READ_IB_SID, SPI_E_UNINIT);
// 		check_read=91;
	
// 	}
//  else 
if ( (Spi_Config_Ptr == (Spi_ConfigType*)NULL_PTR) || (Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].BufferType != InternalBuffer) )
    {
        Det_ReportError(SPI_SW_moduleID, 0, SPI_READ_IB_SID, SPI_E_UNINIT);
		retVar = E_NOT_OK;
		check_read=70;
    }
	
    else if (DataBufferPointer == (Spi_DataBufferType*)NULL_PTR)
	{
		/*Det_ReportError with wrong data buffer pointer */
		
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_READ_IB_SID, SPI_E_PARAM_POINTER);
		retVar = E_NOT_OK;
		check_read=80;
		

	}
	else if ( (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint > Spi_HWUnit_SPI4) || Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint < Spi_HWUnit_SPI1){
		Det_ReportError(SPI_SW_moduleID, (uint8) 0, SPI_READ_IB_SID, SPI_E_PARAM_UNIT);
		check_read=85;
	}
	
	else{
		check_read=90;

				/* Set the channel status to SPI_BUSY */
	Spi_Config.Spi_ChannelConfigPtr[Channel].Status=SPI_BUSY;

		switch (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint)
		{
			
			case Spi_HWUnit_SPI1:
				* DataBufferPointer = SPI1.DR;
				retVar = E_OK; 
				check_read=1;
				break;
			
			case Spi_HWUnit_SPI2:
				* DataBufferPointer = SPI2.DR;
				check_read=2;
				retVar = E_OK; break;

			case Spi_HWUnit_SPI3:
				* DataBufferPointer = SPI3.DR;
				check_read=3;
				retVar = E_OK; break;

			case Spi_HWUnit_SPI4:
				* DataBufferPointer = SPI4.DR;
				check_read=4;
				retVar = E_OK; break;
				
			default: break;
		}
    }
    return retVar;
}


