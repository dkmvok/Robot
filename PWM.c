#include "msp.h"
#include "PWM.h"


void PWMInitA(uint16_t period, uint16_t duty){
	uint16_t tempPeriod;
	tempPeriod = period;
	
	if(duty >= tempPeriod) return;    	
	else {
		P2->DIR |= 0x10;              
		P2->SEL0 |= 0x10;             
		P2->SEL1 &= ~0x10;             
		TIMER_A0->CCTL[0] = 0x0080;   
		TIMER_A0->CCR[0] = period;     
		TIMER_A0->EX0 = 0x0000;        
		TIMER_A0->CCTL[1] = 0x0040;    
		TIMER_A0->CCR[1] = duty;       
		TIMER_A0->CTL = 0x0230;       
	}

}

void PWMInitAB(uint16_t period, uint16_t dutyA, uint16_t dutyB){
  if((dutyA >= period) || (dutyB >= period)) return; 
 else{
  P2->DIR |= 0x30;         
  P2->SEL0 |= 0x30;        
  P2->SEL1 &= ~0x30;        
  TIMER_A0->CCTL[0] = 0x0080;     
  TIMER_A0->CCR[0] = period;       
  TIMER_A0->EX0 = 0x0000;        
  TIMER_A0->CCTL[1] = 0x0040;      
  TIMER_A0->CCR[1] = dutyA;        
  TIMER_A0->CCTL[2] = 0x0040;      
  TIMER_A0->CCR[2] = dutyB;       
  TIMER_A0->CTL = 0x02F0;   
 }
}

void PWMDutyA(uint16_t dutyA){
  uint16_t test;
  
  test = TIMER_A0->CCR[0];
  
  if(dutyA >= test) {return;}
  else{
	TIMER_A0->CCR[1] = dutyA;        
  }
  
}

void PWMDutyB(uint16_t dutyB){
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


