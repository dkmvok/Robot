#include <stdint.h>
#include "msp.h"

void (*TimerA2Task)();
/*---------------------------------------
  IRQ = 8, PRIORITY 7-5
----------------------------------------*/
void TimerA0Init(void(*task)(void), uint16_t period){

	TimerA0Task = task;
	TIMER_A0->CTL = 0X0280;		//0000_0010_1000_0000 TASSEL = 10(SMCLK), Prescale = 4
	TIMER_A0->CCTL[0] 0X0010;	//0b0001_0000 enable cc interrupt
	TIMER_A0->CCR[0] = (period - 1);	//counts
	TIMER_A0->EX0 = 0x0005;			//0b0000_0101 TAIDEX divide by six
	NVIC->IP[2] = (NVIC->IP[2] & 0xFFFFFF00) | 0x00000040;  //0b0100_0000, priority 2
	NVIC->ISER[0] = 0x00000100;		//IRQ = 8
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

	TIMER_A0->CTL = ~(0xFFFF & 0x0030); 			//0b11_0000	//MC=00 Mode changed
	NVIC->ICER[0] = 0x00000100;					//disable irq = 10

}
