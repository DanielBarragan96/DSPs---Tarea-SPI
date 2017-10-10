#include "MK64F12.h"
#include "PIT.h"

static uint8 PIT_INTR_FLAG [3] = {FALSE};

void PIT0_IRQHandler(){//cuando el contador llega a 0 del PIT0 salta a esta función
	uint8 bug_var;
	//se limpia la bandera del Timer 0
	PIT->CHANNEL[0].TFLG |= (PIT_TFLG_TIF_MASK);
	//Se limpia el timer control del Timer 0
	PIT->CHANNEL[0].TCTRL &= 0x0;
	//Debido a bug de hardware
	bug_var = PIT->CHANNEL[0].TCTRL;
	//bandera del PIT0 se hace true
	PIT_INTR_FLAG[0] = TRUE;
}

void PIT1_IRQHandler(){//cuando el contador llega a 0 del PIT1 salta a esta función
	uint8 bug_var;
	//se limpia la bandera del Timer 0
	PIT->CHANNEL[1].TFLG |= (PIT_TFLG_TIF_MASK);
	//Se limpia el timer control del Timer 0
	PIT->CHANNEL[1].TCTRL &= 0x0;
	//Debido a bug de hardware
	bug_var = PIT->CHANNEL[1].TCTRL;
	//bandera del PIT0 se hace true
	PIT_INTR_FLAG[1] = TRUE;
}

void PIT2_IRQHandler(){//cuando el contador llega a 0 del PIT2 salta a esta función
	uint8 bug_var;
	//se limpia la bandera del Timer 0
	PIT->CHANNEL[2].TFLG |= (PIT_TFLG_TIF_MASK);
	//Se limpia el timer control del Timer 0
	PIT->CHANNEL[2].TCTRL &= 0x0;
	//Debido a bug de hardware
	bug_var = PIT->CHANNEL[2].TCTRL;
	//bandera del PIT0 se hace true
	PIT_INTR_FLAG[2] = TRUE;
}

void PIT3_IRQHandler(){//cuando el contador llega a 0 del PIT3 salta a esta función
	uint8 bug_var;
	//se limpia la bandera del Timer 0
	PIT->CHANNEL[3].TFLG |= (PIT_TFLG_TIF_MASK);
	//Se limpia el timer control del Timer 0
	PIT->CHANNEL[3].TCTRL &= 0x0;
	//Debido a bug de hardware
	bug_var = PIT->CHANNEL[3].TCTRL;
	//bandera del PIT0 se hace true
	PIT_INTR_FLAG[3] = TRUE;
}

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period){
	//para guardar periodo
	ufloat32 LDVAL_trigger;
	//Calculo del periodo
	LDVAL_trigger =(period/(1/(systemClock/2)))-1;
	//se configuran los clocks de los timers
	PIT->MCR = 0x00;
	//se carga el valor del periodo
	PIT->CHANNEL[pitTimer].LDVAL = LDVAL_trigger;
	//se habilita el timer
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TEN_MASK;
	//se habilita la interrupcion de los timers
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TIE_MASK;
}

void PIT_clockGating(void){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}


uint8 PIT_getIntrStutus(PIT_Timer_t pitTimer){
	//retorna la bandera deseada del pit deseado
	return PIT_INTR_FLAG[pitTimer];
}

void PIT_clear(PIT_Timer_t pitTimer){
	//borra la bandera del pit deseado
	PIT_INTR_FLAG[pitTimer] = FALSE;
}

void PIT_stop(PIT_Timer_t pitTimer){
	SIM->SCGC6 &= ~(SIM_SCGC6_PIT_MASK);
	PIT_clear(pitTimer);
	DAC0->DAT[0].DATL = (uint8) 0;
	DAC0->DAT[0].DATH = (uint8) 0;
}
