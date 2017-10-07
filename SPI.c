#include "MK64F12.h"
#include "SPI.h"

static void SPI_enable(SPI_ChannelType channel){

}

static void SPI_clk(SPI_ChannelType channel){

}

static void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave){

}

static void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable){

}

static void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol){

}

static void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize){

}

static void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha){

}

static void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate){

}

static void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb){

}

void SPI_startTranference(SPI_ChannelType channel){

}

void SPI_stopTranference(SPI_ChannelType channel){

}

void SPI_sendOneByte(uint8 Data){

}

void SPI_init(const SPI_ConfigType* config){

}
