/* MOTORS New
Left motor direction connected to P5.4 (J3.29)
Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
Left motor enable connected to P3.7 (J4.31)
Right motor direction connected to P5.5 (J3.30)
Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
Right motor enable connected to P3.6 (J2.11)*/

/* Motors OLD
// Sever VCCMD=VREG jumper on Motor Driver and Power Distribution Board and connect VCCMD to 3.3V.
//   This makes P3.7 and P3.6 low power disables for motor drivers.  0 to sleep/stop.
// Sever nSLPL=nSLPR jumper.
//   This separates P3.7 and P3.6 allowing for independent control

// Left motor direction connected to P1.7 (J2.14)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P1.6 (J2.15)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)
*/

void Motor_InitSimple(void){ //0b011000000
// Initializes the 6 GPIO lines and puts driver to sleep
	P1->SEL0 &= ~0xC0;  //1.6,1.7 - //0b1100_0000 = 0xC0
	P1->SEL1 &= ~0xC0;
	P1->DIR |= 0xC0;
	
	P2->SEL0 &= ~0xC0;
	P2->SEL1 &= ~0xC0;
	P2->DIR |= 0xC0;
	
	P3->SEL0 &= ~0xC0;
	P3->SEL1 &= ~0xC0;
	P3->DIR |= 0xC0;
	
// initialize P1.6 and P1.7 and make them outputs
	P5->SEL0 &= ~0x30;  //5.4,5.5 - 0011_0000 = 0x30
	P5->SEL1 &= ~0x30;
	P5->DIR |= 0x30;
	
	P2->SEL0 &= ~0xC0; //2.6,2.7
	P2->SEL1 &= ~0xC0;
	P2->DIR |= 0xC0;
	
	P3->SEL0 &= ~0xC0; //3.6,3.7
	P3->SEL1 &= ~0xC0;
	P3->DIR |= 0xC0;

}

void Motor_StopSimple(void){
// Stops both motors, puts driver to sleep
// Returns right away
  P1->OUT &= ~0xC0;
  P2->OUT &= ~0xC0;   // off
  P3->OUT &= ~0xC0;   // low current sleep mode
  P%->OUT &= ~0x30;
  
}
//Motor_ForwardSimple(5000,2000);
void Motor_ForwardSimple(uint16_t duty, uint32_t time){
// Drives both motors forward at duty (100 to 9900)
// Runs for time duration (units=10ms), and then stops
// Stop the motors and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit
uint16_t count = 0;
for(count = 0; count < time; count=count+period) {
	
	P1->OUT &= ~0xC0;
	P2->OUT |= 0xC0;	
	SysTick_Wait10ms(duty);		//delay
	P2->OUT &= ~0xC0; 			//stop
	SysTick_Wait10ms(duty);		//delay
	P3->OUT |= 0xC0; 			
	//..check bumper switch active if so return from fx
	//return after time*10ms or if bumper hit switch
	
}
	
	P1->OUT &= ~0xC0;
	P2->OUT &= ~0xC0;
	P3->OUT |= 0xC0;	
}


  // write this as part of Lab 12
}
void Motor_BackwardSimple(uint16_t duty, uint32_t time){
// Drives both motors backward at duty (100 to 9900)
// Runs for time duration (units=10ms), and then stops
// Runs even if any bumper switch is active
// Returns after time*10ms
uint16_t count = 0;
for(count = 0; count < time; count=count + period) {
	
	P1->OUT |= 0xC0;			//on
	P2->OUT |= 0xC0;
	SysTick_Wait10ms(duty);		//delay
	
	P1->OUT &= ~0xC0;	
	SysTick_Wait10ms(period-duty);
	P2->OUT |= 0xC0;
	
}
	P1->OUT &= ~0xC0;
	P2->OUT &= ~0xC0;
	P3->OUT |= 0xC0;


  // write this as part of Lab 12
}
void Motor_LeftSimple(uint16_t duty, uint32_t time){
// Drives just the left motor forward at duty (100 to 9900)
// Right motor is stopped (sleeping)
// Runs for time duration (units=10ms), and then stops
// Stop the motor and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit
uint16_t count = 0;
for(count = 0; count<time;count=count+period) {
	P1->OUT &= ~0xC0;
	P2->OUT |= ~0x40;
	SysTick_Wait10ms(duty);		//delay
	P2->OUT &= ~0x40;
	SysTick_Wait10ms(period-duty);		//delay
	P3->OUT |= 0xC0;
}

	P1->OUT &= ~0xC0;
	P2->OUT &= ~0xC0;
	P3->OUT |= 0xC0;

  // write this as part of Lab 12
}
void Motor_RightSimple(uint16_t duty, uint32_t time){
// Drives just the right motor forward at duty (100 to 9900)
// Left motor is stopped (sleeping)
// Runs for time duration (units=10ms), and then stops
// Stop the motor and return if any bumper switch is active
// Returns after time*10ms or if a bumper switch is hit
uint16_t count = 0;
for(count = 0; count<time; count=count+period) {
	P1->OUT &= ~0xC0;
	P2->OUT |= 0x80;
	SysTick_Wait10ms(duty);
	P2->OUT &= ~0x80;
	SysTick_Wait10ms(period-duty);
	P3->OUT |= 0xC0;
	
}

	P1->OUT &= ~0xC0;
	P2->OUT &= ~0xC0;
	P3->OUT |= 0xC0;


  // write this as part of Lab 12
}
/*----------------------------------------------
------------------------------------------------*/
bumpSwitch() {
	config = false;
	numPins = 0;
	bumpSWPin = 0;
}
bool bumpBegin(uint8_t pinNum, uint8_t mode) {
	bumpSWPin = pinNum;
	pinMode(bumpSWPin, mode);
	return true;
	
}

bool read() {
	return digitalRead(bumpSWPin);
}