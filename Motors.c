#include <stdint.h>
#include "msp.h"
#include "../inc/CortexM.h"
#include "../inc/PWM.h"
#include "../inc/Motors.h"


void MotorInit(){
	P5->SEL0 &= ~0x30;		//0b11_0000 
	P5->SEL1 &= ~0x30;
	P5->DIR |= ~0x30;

	P2->SEL0 &= ~0xC0;		//0b1100_0000 
	P2->SEL1 &= ~0xC0;
	P2->DIR |= 0xC0;
	
	P3->SEL0 &= ~0xC0;		//0b1100_0000
	P3->SEL1 &= ~0xC0;
	P3->DIR |= 0xC0; 
}


void MotorStop(){
	P3->OUT &= ~0xC0;	
  
}


void MotorFWD(uint16_t leftDuty, uint16_t rightDuty){ 
 
	P5->OUT &= ~0x30;		//0b11_0000
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= 0xC0;	//2^14 Set High

  
}

void MotorRt(uint16_t leftDuty, uint16_t rightDuty){  
	
	P5->OUT &= ~0x10;	//0b1_0000
	P5->OUT |= 0x20;	//0b10_0000 
	PWMDutyD(leftDuty);
	PWMDutyC(rightDuty);
	P3->OUT |= 0xC0;

}


void MotorLt(uint16_t leftDuty, uint16_t rightDuty){  
   
	P5->OUT &= ~0x20; 	 //0b100000
	P5->OUT |= 0x10;	 //0b10000
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= 0xC0;


}

void MotorReverse(uint16_t leftDuty, uint16_t rightDuty){ 

	P5->OUT |= 0x30; //Backward = 1
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= 0xC0;

}
