#include "spi.cpp"
#include <gtest/gtest.h>

// Reset the SPI1 register before each test
void SetUp() {
    SPI1.CR1 = 0x00000800;  // Clear the CR1 register
    Det_Error_Buffer[Det_Error_Buffer_index] = {0}; 
 ChipSelect_count =0; 
  Spi_lhw_count=0;



}




Spi_ChannelType SPI_job1_channels[] = {0, 1};
Spi_ChannelType SPI_job2_channels[] = {2, 3};


Spi_HWUnitConfigType hwUnitConfig_Job_1 = {
    
    .spiDFF = SPI_DFF_16BITS,
    .SpiPrescaller = SPI_SCLK_SPEED_DIV256,  
    .DefaultTransmitValue = 0xAAAA  ,
    .spiCPOL = SPI_CPOL_LOW,       
    .spiCPHA = SPI_CPHA_LOW

};

Spi_HWUnitConfigType hwUnitConfig_Job_2 = {
    .spiDFF = SPI_DFF_8BITS,
    .SpiPrescaller = SPI_SCLK_SPEED_DIV32,   
    .DefaultTransmitValue = 0xFF,
    .spiCPOL = SPI_CPOL_HIGH,       
    .spiCPHA = SPI_CPHA_HIGH 
	
	
};

Spi_ChannelConfigType channels[]= {
    {
        .SpiChannelId = 0,
        .BufferType = InternalBuffer,
        .Status = SPI_UNINIT,
		.spiCSPort = 1,       
    	.spiCSPin = 10     
    },
    {
        .SpiChannelId = 1,
        .BufferType = InternalBuffer,
        .Status = SPI_UNINIT,
		.spiCSPort = 1,       
    	.spiCSPin = 11   
    },
	{
		.SpiChannelId = 2,
		.BufferType = InternalBuffer,
		.Status = SPI_UNINIT,
		.spiCSPort = 1,       
		.spiCSPin = 12
	},
	{
		.SpiChannelId = 3,
		.BufferType = InternalBuffer,
		.Status = SPI_UNINIT,
		.spiCSPort = 1,       
		.spiCSPin = 13
	}
};

Spi_JobConfigType jobConfig[] = {
    {
        .SpiJobId = 0,
        .spiHWUint = Spi_HWUnit_SPI1,
        .JobPriority = 0,
        .ChannelsPtr = SPI_job1_channels,
		.NoOfChannels = sizeof(SPI_job1_channels)/sizeof(Spi_ChannelType),
        .SpiHWUnitConfig = &hwUnitConfig_Job_1
    },
	{
		.SpiJobId = 1,
    .spiHWUint = Spi_HWUnit_SPI2,

		.JobPriority = 1,
		.ChannelsPtr = SPI_job2_channels,
		.NoOfChannels = sizeof(SPI_job2_channels)/sizeof(Spi_ChannelType),
		
		.SpiHWUnitConfig = &hwUnitConfig_Job_2
	}
};
Spi_SeqConfigType Spi_SeqConfig = {
	.JobLinkPtr = jobConfig,
	.NoOfJobs = sizeof(jobConfig)/sizeof(Spi_JobConfigType),	
	.SpiSeqId = 0

};

Spi_ConfigType Spi_Config = {
	.Spi_SeqConfigPtr = &Spi_SeqConfig,
    .Spi_JobConfigPtr = &jobConfig[0],
    .Spi_ChannelConfigPtr = &channels[0]
};




void SetUp_test3(const Spi_ConfigType* ConfigPtr) {


for (uint8 Jobs_Index = 0; Jobs_Index < ConfigPtr->Spi_SeqConfigPtr->NoOfJobs; Jobs_Index++)
        {
            Spi_JobConfigType *jobConfig = &(ConfigPtr->Spi_JobConfigPtr[Jobs_Index]);
            for (uint8 channels_index = 0; channels_index < jobConfig->NoOfChannels; channels_index++)
            {
                Spi_ChannelType channelId = jobConfig->ChannelsPtr[channels_index]; // Access channel ID
                Spi_ChannelConfigType *channelConfig = &(ConfigPtr->Spi_ChannelConfigPtr[channelId ]);

                channelConfig->Status =SPI_IDLE;
                    }
}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////



// Test Case
TEST(Spi_Init, Config_Null) {
    // Arrange
    SetUp();

    // Act
    Spi_Init(NULL_PTR);

    // Assert
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_INIT_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_POINTER);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////

// Test Case
TEST(Spi_Init,SPI_STATUS_SPI_UNINIT) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;


    // Act
    Spi_Init(&Spi_Config);


    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set
EXPECT_EQ(Spi_lhw_count,2); // Expect CR1 to have 16-bit data frame format bit set


    // EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    // EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    // EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_INIT_SID);
    // EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_POINTER);
}




// Test Case
TEST(Spi_Init,SPI_STATUS_SPI_IDLE) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
SetUp_test3(&Spi_Config);

    // Act
    Spi_Init(&Spi_Config);


    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set


    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_INIT_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_ALREADY_INITIALIZED);
}
/*
// Test Case
TEST(Spi_Init, Config_Nulll) {
    // Arrange
    SetUp();

    // Act
    Spi_Init(&Spi_Conf);

    // Assert
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_INIT_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_POINTER);
}

*/
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

