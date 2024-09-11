#include "Spi.cpp"
#include <gtest/gtest.h>



// Reset the SPI1 register before each test
void SetUp() {
    SPI1.CR1 = 0x00000800;  // Clear the CR1 register
    Det_Error_Buffer[Det_Error_Buffer_index] = {0}; 
 ChipSelect_count =0; 
  Spi_lhw_count=0;

}


Spi_ChannelType SPI_job1_channels[2] = {0, 1};
Spi_ChannelType SPI_job2_channels[2] = {2, 3};


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
        .spiHWUint = 1,
        .JobPriority = 0,
        .ChannelsPtr = SPI_job1_channels,
		.NoOfChannels = sizeof(SPI_job1_channels)/sizeof(Spi_ChannelType),
        .SpiHWUnitConfig = &hwUnitConfig_Job_1
    },
	{
		.SpiJobId = 1,
    .spiHWUint = 2,

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




// Spi_ConfigType * Spi_Config_Ptr = &Spi_Config;


////////////////////////////////////////
//Spi_Config_Ptr = &Spi_Config;
//Spi_DataBufferType* DataBufferPtr = &channels;
Spi_DataBufferType data =9;
Spi_DataBufferType* DataBufferPtr = &data;
Spi_ConfigType*  Spi_Config_Ptr = (Spi_ConfigType* )NULL_PTR;
Spi_JobConfigType *jobCConfig = &( Spi_Config.Spi_JobConfigPtr[0]);


//extern 
///////////////////////////////////////

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


// Test Case
TEST(Spi_WriteIB,NULL_PTRrr) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_WriteIB ( SPI_Channel_1 ,( Spi_DataBufferType* ) NULL_PTR);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set


    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_WRITE_IB_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_POINTER);
}

// Test Case
TEST(Spi_WriteIBB,channels_too_much) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_WriteIB ( 8 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set


    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_WRITE_IB_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId,  SPI_E_PARAM_CHANNEL);
}


TEST(Spi_WriteIBBB,Spi_Config_Ptr_null) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_WriteIB ( 3 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set


    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_WRITE_IB_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId,  SPI_E_UNINIT);
}

TEST(Spi_WriteIBBB,SPIs_too_much) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);
Spi_Config_Ptr = &Spi_Config;
    Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = -9; 

Spi_WriteIB ( 3 , DataBufferPtr);


EXPECT_EQ(CHECK_SPI_VAL1, 256-9);

    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set


    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_WRITE_IB_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_UNIT);
}
TEST(SpiS_LESS_MINI,SPIs_too_LOW) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);
Spi_Config_Ptr = &Spi_Config;
    Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 5; 


Spi_WriteIB ( 3 , DataBufferPtr);
EXPECT_EQ(CHECK_SPI_VAL1, 5);

    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set


    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_WRITE_IB_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_UNIT);
}


////////////////////////////////////////////////////////////////////



TEST(Spi_WriteIBBB_job,SPIs_if_much) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);
Spi_Config_Ptr = &Spi_Config;
//   Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
//   jobConfig-> spiHWUint = 7; 
Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 7;
Spi_WriteIB ( 3 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set

EXPECT_EQ(CHECK_SPI_VAL1, 7);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_WRITE_IB_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_UNIT);
}





TEST(SpiS_LESS_MINI_hw,SPIs_tooo_LOW) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_Config_Ptr = &Spi_Config;
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// jobConfig->spiHWUint = 7; 
Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 7;
Spi_WriteIB ( 2 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set
EXPECT_EQ(CHECK_SPI_VAL1, 7);

    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ModuleId, SPI_SW_moduleID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].InstanceId, 0);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ApiId, SPI_WRITE_IB_SID);
    EXPECT_EQ(Det_Error_Buffer[Det_Error_Buffer_index].ErrorId, SPI_E_PARAM_UNIT);
}



TEST(Spi_WriteIB_ELSE,RIGHT) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_Config_Ptr = &Spi_Config;
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// jobConfig->spiHWUint = 1;
Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 1;

Spi_WriteIB ( 0 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set

  EXPECT_EQ(check, 65);

   EXPECT_EQ(CHECK_SPI_VAL1, 1);
    EXPECT_EQ(SPI1.DR, 9);

/*

    EXPECT_EQ(SPI1.DR, 9);
    EXPECT_EQ(SPI2.DR, 9);*/

}


TEST(Spi1_WriteIB_ELSE,RIGHT) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_Config_Ptr = &Spi_Config;
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// jobConfig->spiHWUint = 1;
Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 1;

Spi_WriteIB ( 1 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set

//   EXPECT_EQ(check, 65);
  EXPECT_EQ(check, 40);
//  EXPECT_EQ(SPI1.DR, 9);
 EXPECT_EQ(SPI1.DR, 10);
   EXPECT_EQ(CHECK_SPI_VAL1, 1);



/*

    EXPECT_EQ(SPI1.DR, 9);
    EXPECT_EQ(SPI2.DR, 9);*/

}


TEST(Spi1_overflow,RIGHT) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_Config_Ptr = &Spi_Config;
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// jobConfig->spiHWUint = 1;
Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 1;

Spi_WriteIB ( 2 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set
  EXPECT_EQ(CHECK_LIMITS, 8);
  EXPECT_EQ(check, 65);
 EXPECT_EQ(check_status, 2);
  // EXPECT_EQ(CHECK_SPI_VAL1, 2);


    // EXPECT_EQ(SPI1.DR, 9);
    // EXPECT_EQ(SPI2.DR, 9);

}


TEST(Spi2_else,RIGHT) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_Config_Ptr = &Spi_Config;
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// jobConfig->spiHWUint = 1;
Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 2;

Spi_WriteIB ( 2 , DataBufferPtr);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set

  EXPECT_EQ(check, 65);

   EXPECT_EQ(CHECK_SPI_VAL1, 2);
 EXPECT_EQ(SPI2.DR, 9);
/*
    EXPECT_EQ(SPI1.DR, 9);
    EXPECT_EQ(SPI2.DR, 9);*/

}

TEST(Spi2_else2,RIGHT) {
   
    // Arrange
    SetUp();
    //static Spi_StatusType Spi1_Status = SPI_UNINIT;
//SetUp_test3(&Spi_Config);

    // // Act
    // Spi_Init(&Spi_Config);

Spi_Config_Ptr = &Spi_Config;
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// Spi_JobConfigType *jobConfig = &( Spi_Config_Ptr->Spi_JobConfigPtr[1]);
// jobConfig->spiHWUint = 1;
Spi_Config_Ptr->Spi_JobConfigPtr->spiHWUint = 2;

Spi_WriteIB ( 3 , DataBufferPtr);
EXPECT_EQ(SPI2.DR, 9);
    // Assert
    // Check if the DFF bit is set, indicating 16-bit data frame format
    // EXPECT_EQ(ChipSelect_count,4); // Expect CR1 to have 16-bit data frame format bit set

  EXPECT_EQ(check, 65);

   EXPECT_EQ(CHECK_SPI_VAL1, 2);

/*

    EXPECT_EQ(SPI1.DR, 9);
    EXPECT_EQ(SPI2.DR, 9);*/

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}







