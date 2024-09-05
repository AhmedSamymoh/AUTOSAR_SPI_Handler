#include "Spi.hpp"


uint8 ChipSelect_count =0; 
uint8  Spi_lhw_count=0;




static void Spi_ChipSelect_Init(Spi_CS_Pin CS_Pin ,Spi_CS_Port CS_Port )
{
ChipSelect_count++;
return;

}


static void Spi_lhw_Init(const Spi_HWUnitType HWUnitId, const Spi_HWUnitConfigType * HWUnit ){
 Spi_lhw_count++;
return;
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
	
	}
    
    else{
        

		/* Set the channel status to SPI_BUSY */
		Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].Status=SPI_BUSY;

		switch (Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint)
		{
			case Spi_HWUnit_SPI1:
				/* Write the data to the Data Register */
				SPI1.DR = *DataBufferPtr;
				ret = E_OK;
				break;
			
			case Spi_HWUnit_SPI2:
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
		Spi_Config_Ptr->Spi_ChannelConfigPtr[Channel].Status=SPI_BUSY;

	}

	return ret;
}






