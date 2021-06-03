
#ifndef Motors_H_
#define Mototrs_H_

// bitMask
static uint8_t port2BitMask = 0xC0; //0b1110_1101;
static uint8_t port3BitMask = 0xC0; //0b1110_1101;
static uint8_t port5BitMask = 0x30; //0b1110_1101;

// Function declarations
void MotorInit();
void MotorStop();
void MotorFWD(uint16_t leftDuty, uint16_t rightDuty);
void MotorRt(uint16_t leftDuty, uint16_t rightDuty); 
void MotorLt(uint16_t leftDuty, uint16_t rightDuty);
void MotorReverse(uint16_t leftDuty, uint16_t rightDuty);

#endif 
