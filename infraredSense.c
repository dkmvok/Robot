#include <stdint.h>
#include "msp432.h"
#include "..\inc\Clock.h"


void IRInit(void){ //0000_1000
    
	P7->SEL0 &= ~0xFF; 		//regular gpio Sel0=0,Sel1 =0
	P7->SEL1 &= ~0xFF;
	//P7->DIR &= ~0xFF;		//make 7.0-7.7 an output
	P7->DIR =0x00;
	//LED
	P5->SEL0 &= ~0x08;  //Selectport 5.3
	P5->SEL1 &= ~0x08;
	P5->DIR |= 0x08; 	//Set output Direction
	//LED
	P9->SEL0 &= ~0x02;  //Selectport 9.2
	P9->SEL1 &= ~0x02;
	P9->DIR |= 0x02;		//Set to Output


}


uint8_t IRRead(uint32_t time){
	uint8_t result,i;

	P5->OUT |= 0x08;		//Turn on LEDS
	P7->DIR = 0xFF;
	P7->OUT = 0xFF;
	Clock_Delay1us(10);
	//P7->DIR &= ~0xFF;
	P7->DIR =0x00;		//change sensor to input
	Clock_Delay1us(10);

	result = P7->IN & 0xFF;

	P5->OUT &= ~0x08;		//Turn off LED
	Clock_Delay1ms(10);

    return result;
}


int32_t RobotPosition(uint8_t data){
  
	int	W[8] = {334,238,142,48,-48,-142,-238,-334};
	int bit[8],i;
	int32_t result,distanceSum = 0,denominator=0;
	if(data){
		for(i=0;i<8;i=i+1) {

			bit[i] = data % 2;	//remainder after division by 2
			data = data/2;		//top part
		}

		for(i=0;i<8;i=i+1) {

			distanceSum = (bit[i]*W[i]) + distanceSum;
			denominator = denominator + bit[i];

		}
		result = distanceSum/denominator;
	}

	return result;

}


void IRStart(){

	uint8_t data;
	P5->DIR |= 0x08; 		//Set output & Direction LED'S
	P5->OUT |= 0x08;

	P9->DIR |= 0x02;		//Set to Output
	P9->OUT |= 0x02;		//0b0000_0010

	P7->DIR = 0xFF;
	P7->OUT = 0xFF;
	Clock_Delay1us(10);		//wait for 10 us

	P7->DIR &= ~0xFF;			//Set all inputs TO read inputs - 6.2
	data = P7->IN & 0xFF;		//read all input pins

}

/*void setInput(){ 6.2
	P7->SEL0 &= ~0xFF;			//Set to all GPIO
	P7->SEL1 &= ~0xFF;
	P7->DIR &= ~0xFF;			//Set to input

}*/


uint8_t IRStop(){
	
	uint8_t data;
	data = P7->IN & 0xFF;		//read DATA all input pins
	P5->OUT &= ~0X08;			//Turn off LEDS
	P9->OUT &= ~0X02;

	return data;
}

