#include <stdint.h>
#include "msp.h"
#include "timerA0.h"

void (*TimerA0Task)();
/*---------------------------------------
  IRQ = 8, PRIORITY 7-5
----------------------------------------*/
void TimerA0Init(void(*task)(void), uint16_t period){

	TimerA0Task = task;
	TIMER_A0->CTL = 0X0280;		
	TIMER_A0->CCTL[0] 0X0010;	
	TIMER_A0->CCR[0] = (period - 1);	
	TIMER_A0->EX0 = 0x0005;			
	NVIC->IP[2] = (NVIC->IP[2] & 0xFFFFFF00) | 0x00000040; 
	NVIC->ISER[0] = 0x00000100;		
	TIMER_A0->CTL |= 0x0014;

}
/*---------------------------------------
----------------------------------------*/
void TA0_0_IRQHandler(){
	TIMER_A0->CCTL[0] &= ~0x0001;	//Clear Ifg
	*TimerA0Task();

}
/*---------------------------------------
----------------------------------------*/
void TimerA0End(){

	TIMER_A0->CTL = ~(0xFFFF & 0x0030); 			
	NVIC->ICER[0] = 0x00000100;					//disable irq = 10

}
