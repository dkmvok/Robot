#include <stdint.h>
#include "msp.h"
#include "../inc/CortexM.h"
#include "../inc/PWM.h"
#include "../inc/Motors.h"



void MotorInit(){
	P5->SEL0 &= ~port5BitMask;		//0b11_0000 
	P5->SEL1 &= ~port5BitMask;
	P5->DIR |= port5BitMask;

	P2->SEL0 &= ~port2BitMask;		//0b1100_0000 
	P2->SEL1 &= ~port2BitMask;
	P2->DIR |= port2BitMask;
	
	P3->SEL0 &= ~port3BitMask;		//0b1100_0000
	P3->SEL1 &= ~port3BitMask;
	P3->DIR |= port3BitMask; 
}


void MotorStop(){
	P3->OUT &= ~port3BitMask;	
  
}


void MotorFWD(uint16_t leftDuty, uint16_t rightDuty){ 
 
	P5->OUT &= ~port5BitMask;		//0b11_0000
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= port3BitMask;	//2^14 Set High

  
}

void MotorRt(uint16_t leftDuty, uint16_t rightDuty){  
	
	P5->OUT &= ~0x10;	//0b1_0000
	P5->OUT |= 0x20;	//0b10_0000 
	PWMDutyD(leftDuty);
	PWMDutyC(rightDuty);
	P3->OUT |= port3BitMask;

}


void MotorLt(uint16_t leftDuty, uint16_t rightDuty){  
   
	P5->OUT &= ~0x20; 	 //0b100000
	P5->OUT |= 0x10;	 //0b10000
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= port3BitMask;


}

void MotorReverse(uint16_t leftDuty, uint16_t rightDuty){ 

	P5->OUT |= port5BitMask; //Backward = 1
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= port3BitMask;

}
