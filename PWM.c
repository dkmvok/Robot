#include "msp.h"


/***************************PWM_Init1*******************************
 PWM outputs on P2.4 Inputs:  period (166.67ns)
         duty (0<=duty<period-1)
 SMCLK = 48MHz/4 = 12 MHz, 83.33ns
 Counter counts up to TA0CCR0 and back down
 Let Timerclock period T = 1/12MHz = 83.33ns
 P2.4=1 when timer equals TA0CCR1 on way down, P2.4=0 when timer equals TA0CCR1 on way up
 Period of P2.4 is period*166.67ns, duty cycle is duty/period*/
void PWM_Init1(uint16_t period, uint16_t duty){
	uint16_t tempPeriod;
	tempPeriod = period;
	
	if(duty >= period) return;    	
	else {
		P2->DIR |= 0x10;               // P2.4 output
		P2->SEL0 |= 0x10;              // P2.4 Timer0A functions
		P2->SEL1 &= ~0x10;             // P2.4 Timer0A functions
		TIMER_A0->CCTL[0] = 0x0080;    // CCI0 toggle
		TIMER_A0->CCR[0] = period;     // Period is 2*period*8*83.33ns is 1.333*period
		TIMER_A0->EX0 = 0x0000;        //    divide by 1
		TIMER_A0->CCTL[1] = 0x0040;    // CCR1 toggle/reset
		TIMER_A0->CCR[1] = duty;       // CCR1 duty cycle is duty1/period
		TIMER_A0->CTL = 0x0230;        // SMCLK=12MHz, divide by 1, up-down mode
	}

}
//***************************PWM_Init12*******************************
// PWM outputs on P2.4, P2.5
// Inputs:  period (1.333us)
//          duty1
//          duty2
// Outputs: none
// SMCLK = 48MHz/4 = 12 MHz, 83.33ns
// Counter counts up to TA0CCR0 and back down
// Let Timerclock period T = 8/12MHz = 666.7ns
// P2.4=1 when timer equals TA0CCR1 on way down, P2.4=0 when timer equals TA0CCR1 on way up
// P2.5=1 when timer equals TA0CCR2 on way down, P2.5=0 when timer equals TA0CCR2 on way up
// Period of P2.4 is period*1.333us, duty cycle is duty1/period
// Period of P2.5 is period*1.333us, duty cycle is duty2/period
void PWM_Init12(uint16_t period, uint16_t dutyA, uint16_t dutyB){
  if(dutyA >= period) return; // bad input
  if(dutyB >= period) return; // bad input
  P2->DIR |= 0x30;          // P2.4, P2.5 output
  P2->SEL0 |= 0x30;         // P2.4, P2.5 Timer0A functions
  P2->SEL1 &= ~0x30;        // P2.4, P2.5 Timer0A functions
  TIMER_A0->CCTL[0] = 0x0080;      // CCI0 toggle
  TIMER_A0->CCR[0] = period;       // Period is 2*period*8*83.33ns is 1.333*period
  TIMER_A0->EX0 = 0x0000;        //    divide by 1
  TIMER_A0->CCTL[1] = 0x0040;      // CCR1 toggle/reset
  TIMER_A0->CCR[1] = dutyA;        // CCR1 duty cycle is duty1/period
  TIMER_A0->CCTL[2] = 0x0040;      // CCR2 toggle/reset
  TIMER_A0->CCR[2] = dutyB;        // CCR2 duty cycle is duty2/period
  TIMER_A0->CTL = 0x02F0;        // SMCLK=12MHz, divide by 8, up-down mode
}

void PWM_DutyA(uint16_t dutyA){
  uint16_t test;
  
  test = TIMER_A0->CCR[0];
  
  if(dutyA >= test) {return;}
  else{
	TIMER_A0->CCR[1] = dutyA;        
  }
  
}

void PWM_DutyB(uint16_t dutyB){
  uint16_t testB;
  
  testB = TIMER_A0->CCR[0];
  
  if(dutyB >= testB) {return;} 
  else{
	  TIMER_A0->CCR[2] = dutyB;        
  }
}

void PWMInitCD(uint16_t period, uint16_t dutyC, uint16_t dutyD){
  
  P2->SEL0 |= 0xC0;		//Set up PWM
  P2->SEL1 &= ~0xC0; 	
  P2->DIR |= 0XC0;

  TIMER_A0->CCTL[0] = 0X0080		//Set up timers
  TIMER_A0->CCR[0] = period;
  TIMER_A0->EX0 = 0x0000;

  TIMER_A0->CCTL[3] = 0x0040;
  TIMER_A0->CCR[3] = dutyC;

  TIMER_A0->CCTL[4] = 0x0040;
  TIMER_A0->CCR[4] = dutyD;
  TIMER_A0->CTL = 0x02F0;		
}

void PWMDutyD(uint16_t dutyD){
	uint16_t testD;
  
    testD = TIMER_A0->CCR[0];

	if(dutyD >= testD) return;
	TIMER_A0->CCR[4] = dutyD;

}

void PWMDutyC(unint16_t dutyC){
	uint16_t testC;
  
    testC = TIMER_A0->CCR[0];
	
	if(dutyC >= testC) return;
	TIMER_A0->CCR[3] = dutyC;
	
}


