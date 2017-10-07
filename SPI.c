#include "MK64F12.h"
#include "SPI.h"

static void SPI_enable(SPI_ChannelType channel){
	SPI_MCR_CONT_SCKE(channel);
}

static void SPI_clk(SPI_ChannelType channel){
	if(SPI_0) SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK;
	else if(SPI_1) SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;
}

static void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave){
	SPI_MCR_MSTR(masterOrSlave);
}

static void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable){
	SPI_MCR_DIS_TXF(enableOrDisable);
	SPI_MCR_DIS_RXF(enableOrDisable);
}

static void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol){
	SPI_CTAR_CPOL(cpol);
}

static void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize){
	SPI_CTAR_FMSZ(frameSize);
}

static void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha){
	SPI_CTAR_CPHA(cpha);
}

static void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate){
	SPI_CTAR_DBR(baudRate);
}

static void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb){
	SPI_CTAR_LSBFE(msb);
}

void SPI_startTranference(SPI_ChannelType channel){
	SPI_MCR_HALT(FALSE);
}

void SPI_stopTranference(SPI_ChannelType channel){
	SPI_MCR_HALT(TRUE);
}

void SPI_sendOneByte(uint8 Data){

}

void SPI_init(const SPI_ConfigType* config){

}
