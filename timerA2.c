
#include <stdint.h>
#include "msp.h"

void (*TimerA2Task)();
/*---------------------------------------
----------------------------------------*/
void TimerA2Init(){	//IRQ=12, PRIORITY = 7-5 BITS
	 TimerA2Task = task;
	 TIMER_A2->CTL =  0X0280;
	 TIMER_A2->CCTL[0] = 0x0010;
	 TIMER_A2->CCR[0] =(period-1);
	 TIMER_A2->EX0 = 0X0005;	
	 NVIC->IP[3] = (NVIC->IP[3] & 0xFFFFFF00) | 0x00000040;  
	 NVIC->ISER[0] = 0x00001000;		
	 TIMER_A2->CTL |= 0x0014;
 }
/*---------------------------------------
----------------------------------------*/
 void TA2_0_IRQHandler(void(*task)(void), uint16_t period){
	 TIMER_A2->CCTL[0] &= ~0x0001;	
	 *TimerA2Task();

 }
 /*---------------------------------------
 ----------------------------------------*/
 void TimerA2End(){

 	TIMER_A2->CTL = ~(0xFFFF & 0x0030);  			
 	NVIC->ICER[0] = 0x00001000;					

 }
