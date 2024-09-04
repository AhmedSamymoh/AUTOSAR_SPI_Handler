
#include "includes.hpp"

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