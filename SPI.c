#include "MK64F12.h"
#include "SPI.h"

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
		break;
	}
}

static void SPI_clk(SPI_ChannelType channel)
{
	switch(channel)
	{
	case SPI_0:
		SIM_SCGC6 |= SPI0_CLOCK_GATING;
		break;
	case SPI_1:
		SIM_SCGC6 |= SPI1_CLOCK_GATING;
		break;
	case SPI_2:
		SIM_SCGC3 |= SPI2_CLOCK_GATING;
		break;
	default:
		break;
	}
}

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
		break;
	}
}

static void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_ENABLE_FIFO == enableOrDisable)
		{
			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
		}else{
			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;
		}
		break;
	case SPI_1:
		if(SPI_ENABLE_FIFO == enableOrDisable)
		{
			SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
		}else{
			SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;
			SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;
		}
		break;
	case SPI_2:
		if(SPI_ENABLE_FIFO == enableOrDisable)
		{
			SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
		}else{
			SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;
			SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;
		}
	default:
		break;
	}
}

static void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_LOW_POLARITY == cpol)
		{
			SPI0->CTAR(0) &= ~(SPI_CTAR_CPOL_MASK);
			SPI0->CTAR(1) &= ~(SPI_CTAR_CPOL_MASK);
			SPI0->CTAR_SLAVE &= ~(SPI_CTAR_CPOL_MASK);
		}else{
			SPI0->CTAR(0) |= SPI_CTAR_CPOL_MASK;
			SPI0->CTAR(1) |= SPI_CTAR_CPOL_MASK;
			SPI0->CTAR_SLAVE |= SPI_CTAR_CPOL_MASK;
		}
		break;
	case SPI_1:
		if(SPI_LOW_POLARITY == cpol)
		{
			SPI1->CTAR(0) &= ~(SPI_CTAR_CPOL_MASK);
			SPI1->CTAR(1) &= ~(SPI_CTAR_CPOL_MASK);
			SPI1->CTAR_SLAVE &= ~(SPI_CTAR_CPOL_MASK);
		}else{
			SPI1->CTAR(0) |= SPI_CTAR_CPOL_MASK;
			SPI1->CTAR(1) |= SPI_CTAR_CPOL_MASK;
			SPI1->CTAR_SLAVE |= SPI_CTAR_CPOL_MASK;
		}
		break;
	case SPI_2:
		if(SPI_LOW_POLARITY == cpol)
		{
			SPI2->CTAR(0) &= ~(SPI_CTAR_CPOL_MASK);
			SPI2->CTAR(1) &= ~(SPI_CTAR_CPOL_MASK);
			SPI2->CTAR_SLAVE &= ~(SPI_CTAR_CPOL_MASK);
		}else{
			SPI2->CTAR(0) |= SPI_CTAR_CPOL_MASK;
			SPI2->CTAR(1) |= SPI_CTAR_CPOL_MASK;
			SPI2->CTAR_SLAVE |= SPI_CTAR_CPOL_MASK;
		}
	default:
		break;
	}
}

static void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->CTAR(0) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI0->CTAR(0) |= frameSize;
		SPI0->CTAR(1) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI0->CTAR(1) |= frameSize;
		SPI0->CTAR_SLAVE &= ~(SPI_CTAR_FMSZ_MASK);
		SPI0->CTAR_SLAVE |= frameSize;
		break;
	case SPI_1:
		SPI1->CTAR(0) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI1->CTAR(0) |= frameSize;
		SPI1->CTAR(1) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI1->CTAR(1) |= frameSize;
		SPI1->CTAR_SLAVE &= ~(SPI_CTAR_FMSZ_MASK);
		SPI1->CTAR_SLAVE |= frameSize;
		break;
	case SPI_2:
		SPI2->CTAR(0) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR(0) |= frameSize;
		SPI2->CTAR(1) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR(1) |= frameSize;
		SPI2->CTAR_SLAVE &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR_SLAVE |= frameSize;
		break;
	default:
		break;
	}
}

static void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_LOW_PHASE == cpha)
		{
		SPI0->CTAR(0) &= ~(SPI_CTAR_CPHA_MASK);
		SPI0->CTAR(1) &= ~(SPI_CTAR_CPHA_MASK);
		SPI0->CTAR_SLAVE &= ~(SPI_CTAR_CPHA_MASK);
		} else{
			SPI0->CTAR(0) |= SPI_CTAR_CPHA_MASK;
			SPI0->CTAR(1) |= SPI_CTAR_CPHA_MASK;
			SPI0->CTAR_SLAVE |= SPI_CTAR_CPHA_MASK;
		}
		break;
	case SPI_1:
		if(SPI_LOW_PHASE == cpha)
		{
		SPI1->CTAR(0) &= ~(SPI_CTAR_CPHA_MASK);
		SPI1->CTAR(1) &= ~(SPI_CTAR_CPHA_MASK);
		SPI1->CTAR_SLAVE &= ~(SPI_CTAR_CPHA_MASK);
		} else{
			SPI1->CTAR(0) |= SPI_CTAR_CPHA_MASK;
			SPI1->CTAR(1) |= SPI_CTAR_CPHA_MASK;
			SPI1->CTAR_SLAVE |= SPI_CTAR_CPHA_MASK;
		}
		break;
	case SPI_2:
		if(SPI_LOW_PHASE == cpha)
		{
		SPI2->CTAR(0) &= ~(SPI_CTAR_CPHA_MASK);
		SPI2->CTAR(1) &= ~(SPI_CTAR_CPHA_MASK);
		SPI2->CTAR_SLAVE &= ~(SPI_CTAR_CPHA_MASK);
		} else{
			SPI2->CTAR(0) |= SPI_CTAR_CPHA_MASK;
			SPI2->CTAR(1) |= SPI_CTAR_CPHA_MASK;
			SPI2->CTAR_SLAVE |= SPI_CTAR_CPHA_MASK;
		}
		break;
	default:
		break;
	}
}

static void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->CTAR(0) &= ~(SPI_CTAR_BR_MASK);
		SPI0->CTAR(0) |= baudRate;
		SPI0->CTAR(1) &= ~(SPI_CTAR_BR_MASK);
		SPI0->CTAR(1) |= baudRate;
		break;
	case SPI_1:
		SPI1->CTAR(0) &= ~(SPI_CTAR_BR_MASK);
		SPI1->CTAR(0) |= baudRate;
		SPI1->CTAR(1) &= ~(SPI_CTAR_BR_MASK);
		SPI1->CTAR(1) |= baudRate;
		break;
	case SPI_2:
		SPI2->CTAR(0) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR(0) |= baudRate;
		SPI2->CTAR(1) &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR(1) |= baudRate;
		break;
	default:
		break;
	}
}

static void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_MSB == msb)
		{
			SPI0->CTAR(0) &= ~(SPI_CTAR_LSBFE_MASK);
			SPI0->CTAR(1) &= ~(SPI_CTAR_LSBFE_MASK);
			SPI0->CTAR_SLAVE &= ~(SPI_CTAR_LSBFE_MASK);
		}else{
			SPI0->CTAR(0) |= SPI_CTAR_LSBFE_MASK;
			SPI0->CTAR(1) |= SPI_CTAR_LSBFE_MASK;
			SPI0->CTAR_SLAVE |= SPI_CTAR_LSBFE_MASK;
		}
		break;
	case SPI_1:
		if(SPI_MSB == msb)
		{
			SPI1->CTAR(0) &= ~(SPI_CTAR_LSBFE_MASK);
			SPI1->CTAR(1) &= ~(SPI_CTAR_LSBFE_MASK);
			SPI1->CTAR_SLAVE &= ~(SPI_CTAR_LSBFE_MASK);
		}else{
			SPI1->CTAR(0) |= SPI_CTAR_LSBFE_MASK;
			SPI1->CTAR(1) |= SPI_CTAR_LSBFE_MASK;
			SPI1->CTAR_SLAVE |= SPI_CTAR_LSBFE_MASK;
		}
		break;
	case SPI_2:
		if(SPI_MSB == msb)
		{
			SPI2->CTAR(0) &= ~(SPI_CTAR_LSBFE_MASK);
			SPI2->CTAR(1) &= ~(SPI_CTAR_LSBFE_MASK);
			SPI2->CTAR_SLAVE &= ~(SPI_CTAR_LSBFE_MASK);
		}else{
			SPI2->CTAR(0) |= SPI_CTAR_LSBFE_MASK;
			SPI2->CTAR(1) |= SPI_CTAR_LSBFE_MASK;
			SPI2->CTAR_SLAVE |= SPI_CTAR_LSBFE_MASK;
		}
	default:
		break;
	}
}

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
		break;
	}
}

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
		break;
	}
}

void SPI_sendOneByte(uint8 Data)
{
	switch(channel)
	{
	case SPI_0:
		SPI0->PUSHR = (Data);
		while(0 == (SPI0->SR & SPI_SR_TCF_MASK))
		SPI0->SR |= SPI_SR_TCF_MASK;
		break;
	case SPI_1:
		SPI1->PUSHR = (Data);
		while(0 == (SPI1->SR & SPI_SR_TCF_MASK))
		SPI1->SR |= SPI_SR_TCF_MASK;
		break;
	case SPI_2:
		SPI2->PUSHR = (Data);
		while(0 == (SPI2->SR & SPI_SR_TCF_MASK))
		SPI2->SR |= SPI_SR_TCF_MASK;
		break;
	default:
		break;
	}
}

void SPI_init(const SPI_ConfigType* config)
{
	//start clock gate
	SPI_clk(SPI_Config->SPI_Channel);
	//GPIO init
	GPIO_clockGating(SPI_Config->GPIOForSPI.GPIO_portName);
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_clk , &(SPI_Config->pinConttrolRegisterPORTD));
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_Sout , &(SPI_Config->pinConttrolRegisterPORTD));
	//Select mode as master or slave
	SPI_setMaster(SPI_Config->SPI_Channel, SPI_Config->SPI_Master);
	//Activate or deactivate the fifo of the spi
	SPI_fIFO(SPI_Config->SPI_Channel, SPI_Config->SPI_EnableFIFO);
	//enables spi
	SPI_enable(SPI_Config->SPI_Channel);
	//select the polarity of the spi
	SPI_clockPolarity(SPI_Config->SPI_Channel, SPI_Config->SPI_Polarity);
	//select the framesize of the spi
	SPI_frameSize(SPI_Config->SPI_Channel, SPI_Config->frameSize);
	//Select the clock phase of the spi
	SPI_clockPhase(SPI_Config->SPI_Channel, SPI_Config->SPI_Phase);
	//Selects the baud rate of the SPI
	SPI_baudRate(SPI_Config->SPI_Channel, SPI_Config->baudrate);
	//LSB or MSB type of transference is selected
	SPI_mSBFirst(SPI_Config->SPI_Channel, SPI_MSB);
}
