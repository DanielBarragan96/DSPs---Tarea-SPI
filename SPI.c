
#include "GPIO.h"
#include "DatatypeDefinitions.h"
#include "SPI.h"

//depending on which spi you only enable bit 14 of the Module Configuration Register
static void SPI_enable(SPI_ChannelType channel)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);
		break;
	case SPI_1:
		SPI1->MCR &= ~(SPI_MCR_MDIS_MASK);
		break;
	case SPI_2:
		SPI2->MCR &= ~(SPI_MCR_MDIS_MASK);
		break;
	default:
		return;
	}
}

//Enables the clock gating depending on the SPI you want to use
static void SPI_clk(SPI_ChannelType channel)
{
	switch(channel)
	{
	case SPI_0:
		SIM->SCGC6 |= SPI0_CLOCK_GATING;
		break;
	case SPI_1:
		SIM->SCGC6 |= SPI1_CLOCK_GATING;
		break;
	case SPI_2:
		SIM->SCGC3 |= SPI2_CLOCK_GATING;
		break;
	default:
		return;
	}
}

//if you want to configure the SPI as slave we assign a 0 if master we assign 1 bit 31 of the MCR
static void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_SLAVE == masterOrSlave)
		{
			SPI0->MCR &= ~(SPI_MCR_MSTR_MASK);
		}else
			SPI0->MCR |= SPI_MCR_MSTR_MASK;
		break;
	case SPI_1:
		if(SPI_SLAVE == masterOrSlave)
		{
			SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);
		}else
			SPI1->MCR |= SPI_MCR_MSTR_MASK;
		break;
	case SPI_2:
		if(SPI_SLAVE == masterOrSlave)
		{
			SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);
		}else
			SPI2->MCR |= SPI_MCR_MSTR_MASK;
		break;
	default:
		return;
	}
}

//to enable fifo we assign a 0 to disable we assign a 1, bit 13 TX, bit 12 RX
static void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_ENABLE_FIFO == enableOrDisable)
		{
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
		}else{
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;
			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;
		}
		break;
	case SPI_1:
		if(SPI_ENABLE_FIFO == enableOrDisable)
		{
			SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
			SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
		}else{
			SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;
			SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;
		}
		break;
	case SPI_2:
		if(SPI_ENABLE_FIFO == enableOrDisable)
		{
			SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
			SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
		}else{
			SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;
			SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;
		}
	default:
		return;
	}
}

//if we want low polarity we write 0 to the bit 26
static void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_LOW_POLARITY == cpol)
		{
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			SPI0->CTAR[1] &= ~(SPI_CTAR_CPOL_MASK);
			SPI0->CTAR_SLAVE[0] &= ~(SPI_CTAR_CPOL_MASK);
		}else{
			SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			SPI0->CTAR[1] |= SPI_CTAR_CPOL_MASK;
			SPI0->CTAR_SLAVE[0] |= SPI_CTAR_CPOL_MASK;
		}
		break;
	case SPI_1:
		if(SPI_LOW_POLARITY == cpol)
		{
			SPI1->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			SPI1->CTAR[1] &= ~(SPI_CTAR_CPOL_MASK);
			SPI1->CTAR_SLAVE[0] &= ~(SPI_CTAR_CPOL_MASK);
		}else{
			SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			SPI1->CTAR[1] |= SPI_CTAR_CPOL_MASK;
			SPI1->CTAR_SLAVE[0] |= SPI_CTAR_CPOL_MASK;
		}
		break;
	case SPI_2:
		if(SPI_LOW_POLARITY == cpol)
		{
			SPI2->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			SPI2->CTAR[1] &= ~(SPI_CTAR_CPOL_MASK);
			SPI2->CTAR_SLAVE[0] &= ~(SPI_CTAR_CPOL_MASK);
		}else{
			SPI2->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			SPI2->CTAR[1] |= SPI_CTAR_CPOL_MASK;
			SPI2->CTAR_SLAVE[0] |= SPI_CTAR_CPOL_MASK;
		}
	default:
		return;
	}
}

//cleans the value of the bits and sets the wanted ones.
static void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI0->CTAR[0] |= frameSize;
		SPI0->CTAR[1] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI0->CTAR[1] |= frameSize;
		SPI0->CTAR_SLAVE[0] &= ~(SPI_CTAR_SLAVE_FMSZ_MASK);
		SPI0->CTAR_SLAVE[0] |= frameSize;
		break;
	case SPI_1:
		SPI1->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI1->CTAR[0] |= frameSize;
		SPI1->CTAR[1] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI1->CTAR[1] |= frameSize;
		SPI1->CTAR_SLAVE[0] &= ~(SPI_CTAR_SLAVE_FMSZ_MASK);
		SPI1->CTAR_SLAVE[0] |= frameSize;
		break;
	case SPI_2:
		SPI2->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR[0] |= frameSize;
		SPI2->CTAR[1] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR[1] |= frameSize;
		SPI2->CTAR_SLAVE[0] &= ~(SPI_CTAR_SLAVE_FMSZ_MASK);
		SPI2->CTAR_SLAVE[0] |= frameSize;
		break;
	default:
		return;
	}
}

//we write a 0 for low phase in bit 25
static void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_LOW_PHASE == cpha)
		{
		SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
		SPI0->CTAR[1] &= ~(SPI_CTAR_CPHA_MASK);
		SPI0->CTAR_SLAVE[0] &= ~(SPI_CTAR_CPHA_MASK);
		} else{
			SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			SPI0->CTAR[1] |= SPI_CTAR_CPHA_MASK;
			SPI0->CTAR_SLAVE[0] |= SPI_CTAR_CPHA_MASK;
		}
		break;
	case SPI_1:
		if(SPI_LOW_PHASE == cpha)
		{
		SPI1->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
		SPI1->CTAR[1] &= ~(SPI_CTAR_CPHA_MASK);
		SPI1->CTAR_SLAVE[0] &= ~(SPI_CTAR_CPHA_MASK);
		} else{
			SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			SPI1->CTAR[1] |= SPI_CTAR_CPHA_MASK;
			SPI1->CTAR_SLAVE[0] |= SPI_CTAR_CPHA_MASK;
		}
		break;
	case SPI_2:
		if(SPI_LOW_PHASE == cpha)
		{
		SPI2->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
		SPI2->CTAR[1] &= ~(SPI_CTAR_CPHA_MASK);
		SPI2->CTAR_SLAVE[1] &= ~(SPI_CTAR_CPHA_MASK);
		} else{
			SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			SPI2->CTAR[1] |= SPI_CTAR_CPHA_MASK;
			SPI2->CTAR_SLAVE[0] |= SPI_CTAR_CPHA_MASK;
		}
		break;
	default:
		return;
	}
}

//erases the value and writes the wanted baudrate in the first bits
static void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
		SPI0->CTAR[1] &= ~(SPI_CTAR_BR_MASK);
		SPI0->CTAR[0] |= baudRate;
		SPI0->CTAR[1] |= baudRate;
		break;
	case SPI_1:
		SPI1->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
		SPI1->CTAR[0] |= baudRate;
		SPI1->CTAR[1] &= ~(SPI_CTAR_BR_MASK);
		SPI1->CTAR[1] |= baudRate;
		break;
	case SPI_2:
		SPI2->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
		SPI2->CTAR[0] |= baudRate;
		SPI2->CTAR[1] &= ~(SPI_CTAR_BR_MASK);
		SPI2->CTAR[1] |= baudRate;
		break;
	default:
		return;
	}
}

//For MSB we write a 0 in the bit 24 of the clock and transfer attributes register
static void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_MSB == msb)
		{
			SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			SPI0->CTAR[1] &= ~(SPI_CTAR_LSBFE_MASK);
			//SPI0->CTAR_SLAVE[0] &= ~(SPI_CTAR_LSBFE_MASK);
		}else{
			SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			SPI0->CTAR[1] |= SPI_CTAR_LSBFE_MASK;
			//SPI0->CTAR_SLAVE[0] |= SPI_CTAR_LSBFE_MASK;
		}
		break;
	case SPI_1:
		if(SPI_MSB == msb)
		{
			SPI1->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			SPI1->CTAR[1] &= ~(SPI_CTAR_LSBFE_MASK);
			SPI1->CTAR_SLAVE[0] &= ~(SPI_CTAR_LSBFE_MASK);
		}else{
			SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			SPI1->CTAR[1] |= SPI_CTAR_LSBFE_MASK;
			SPI1->CTAR_SLAVE[0] |= SPI_CTAR_LSBFE_MASK;
		}
		break;
	case SPI_2:
		if(SPI_MSB == msb)
		{
			SPI2->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			SPI2->CTAR[1] &= ~(SPI_CTAR_LSBFE_MASK);
			SPI2->CTAR_SLAVE[0] &= ~(SPI_CTAR_LSBFE_MASK);
		}else{
			SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			SPI2->CTAR[1] |= SPI_CTAR_LSBFE_MASK;
			SPI2->CTAR_SLAVE[0] |= SPI_CTAR_LSBFE_MASK;
		}
	default:
		return;
	}
}

//to start transfer we write a 0 on the halt of the mcr
void SPI_startTranference(SPI_ChannelType channel)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->MCR &= ~(SPI_MCR_HALT_MASK);
		break;
	case SPI_1:
		SPI1->MCR &= ~(SPI_MCR_HALT_MASK);
		break;
	case SPI_2:
		SPI2->MCR &= ~(SPI_MCR_HALT_MASK);
		break;
	default:
		return;
	}
}

//to stop transfer we write a 1 on the halt of the mcr
void SPI_stopTranference(SPI_ChannelType channel)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->MCR |= SPI_MCR_HALT_MASK;
		break;
	case SPI_1:
		SPI1->MCR |= SPI_MCR_HALT_MASK;
		break;
	case SPI_2:
		SPI2->MCR |= SPI_MCR_HALT_MASK;
		break;
	default:
		return;
	}
}


void SPI_sendOneByte(SPI_ChannelType channel, uint8 Data)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->PUSHR = Data;
		while(0 == (SPI0->SR & SPI_SR_TCF_MASK));
		SPI0->SR |= SPI_SR_TCF_MASK;
		break;
	case SPI_1:
		SPI1->PUSHR = Data;
		while(0 == (SPI1->SR & SPI_SR_TCF_MASK));
		SPI1->SR |= SPI_SR_TCF_MASK;
		break;
	case SPI_2:
		SPI2->PUSHR = Data;
		while(0 == (SPI2->SR & SPI_SR_TCF_MASK));
		SPI2->SR |= SPI_SR_TCF_MASK;
		break;
	default:
		return;
	}
}

void SPI_init(const SPI_ConfigType* configure)
{
	//start clock gate
	SPI_clk(configure->SPI_Channel);
	//enables spi
	SPI_enable(configure->SPI_Channel);
	//Select mode as master or slave
	SPI_setMaster(configure->SPI_Channel, configure->SPI_Master);
	//Activate or deactivate the fifo of the spi
	SPI_fIFO(configure->SPI_Channel, configure->SPI_EnableFIFO);
	//select the polarity of the spi
	SPI_clockPolarity(configure->SPI_Channel, configure->SPI_Polarity);
	//select the framesize of the spi
	SPI_frameSize(configure->SPI_Channel, configure->frameSize);
	//Select the clock phase of the spi
	SPI_clockPhase(configure->SPI_Channel, configure->SPI_Phase);
	//Selects the baud rate of the SPI
	SPI_baudRate(configure->SPI_Channel, configure->baudrate);
	//LSB or MSB type of transference is selected
	SPI_mSBFirst(configure->SPI_Channel, configure->SPI_LSMorMSB);
	//GPIO init
	GPIO_clockGating(configure->GPIOForSPI.GPIO_portName);
	GPIO_pinControlRegister(configure->GPIOForSPI.GPIO_portName,configure->GPIOForSPI.SPI_Sout , &configure->pinConttrolRegisterPORTD);
	GPIO_pinControlRegister(configure->GPIOForSPI.GPIO_portName,configure->GPIOForSPI.SPI_clk , &configure->pinConttrolRegisterPORTD);
}
