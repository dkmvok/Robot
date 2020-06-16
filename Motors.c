#include <stdint.h>
#include "msp.h"
#include "../inc/CortexM.h"
#include "../inc/PWM.h"

/* MOTORS New
Left motor direction connected to P5.4 (J3.29)  P5.4=DIRL
Left motor PWM connected to P2.7/TA0CCP4 (J4.40) P2.7=PWML
Left motor enable connected to P3.7 (J4.31)	P3.7=nSLPL
Right motor direction connected to P5.5 (J3.30) P5.5=DIRR
Right motor PWM connected to P2.6/TA0CCP3 (J4.39) P2.6=PWMR
Right motor enable connected to P3.6 (J2.11)	P3.6=nSLPR
*/
void Motor_Init(void){
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


void Motor_Stop(void){
	P3->OUT &= ~0xC0;	
  
}


void Motor_Forward(uint16_t leftDuty, uint16_t rightDuty){ 
 
	P5->OUT &= ~0x30;		//0b11_0000
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= 0xC0;	//2^14 Set High

  
}

void Motor_Right(uint16_t leftDuty, uint16_t rightDuty){  
	
	P5->OUT &= ~0x10;	//0b1_0000
	P5->OUT |= 0x20;	//0b10_0000 
	PWMDutyD(leftDuty);
	PWMDutyC(rightDuty);
	P3->OUT |= 0xC0;

}


void Motor_Left(uint16_t leftDuty, uint16_t rightDuty){  
   
	P5->OUT &= ~0x20; 	 //0b100000
	P5->OUT |= 0x10;	 //0b10000
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= 0xC0;


}

void Motor_Backward(uint16_t leftDuty, uint16_t rightDuty){ 

	P5->OUT |= 0x30; //Backward = 1
	PWMDutyC(rightDuty);
	PWMDutyD(leftDuty);
	P3->OUT |= 0xC0;

}
