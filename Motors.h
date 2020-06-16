
#ifndef Motors_H_
#define Mototrs_H_

void MotorInit();
void MotorStop();
void MotorFWD(uint16_t leftDuty, uint16_t rightDuty);
void MotorRt(uint16_t leftDuty, uint16_t rightDuty); 
void MotorLt(uint16_t leftDuty, uint16_t rightDuty);
void MotorReverse(uint16_t leftDuty, uint16_t rightDuty);

#endif 