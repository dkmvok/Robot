#include <stdint.h>
#include "msp.h"
#include "..\inc\Clock.h"
#include "..\inc\Collision.h"

void collisionInit(void(*task)(uint8_t)){
   
	P4->SEL0 &= ~port4BitMask;
	P4->SEL1 &= ~port4BitMask;
	P4->DIR &= ~port4BitMask;
	P4->REN |= port4BitMask;
	P4->OUT |= port4BitMask;

	P4->IES |= port4BitMask;	//Interrupt Edge Select- High to low
	P4->IFG &= ~port4BitMask;		
	P4->IE |= port4BitMask;		
	NVIC_EnableIRQ(PORT4_IRQn);

}

uint8_t collisionRead(){
 
	uint8_t readData,retVal;
	char testSensor = '0';
	readData =  P4->IN & port4BitMask;
	
	switch(readData) {
	case 0b11101100:
		testSensor = '0';
		retVal = 1;
		break;
	case 0b11101001:
		testSensor = '1';
		retVal = 1;
		break;
	case 0b11100101:
		testSensor = '2';
		retVal = 2;
		break;
	case 0b11001101:
		testSensor = '3';
		retVal = 2;
		break;
	case 0b11000101://c5
		testSensor = 'x';
		retVal = 2;
		break;
	case 0b10101101://ad
		testSensor ='4';
		retVal = 3;
		break;
	case 0b01101101://6d
		testSensor = '5';
		retVal = 3;
		break;
	default:
		retVal=0;

	}

    return retVal; 
}

void PORT4_IRQHandler(void){
  
	collisionTriggerVal |= P4->IFG;		//see what was enabled
	P4->IFG = 0;
}

void collisionHandler(uint8_t collisionSense){
	Motor_Stop();
	collisionData = collisionSense;
	hitWallFlag = 1;
}
void collisionClear(){
	collisionTriggerValue = 0;
}
