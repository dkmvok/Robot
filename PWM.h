
#ifndef PWM_H_
#define PWM_H_

void PWMInitA(uint16_t period, uint16_t duty);
void PWMInitAB(uint16_t period, uint16_t dutyA, uint16_t dutyB);
void PWMDutyA(uint16_t dutyA);
void PWMDutyB(uint16_t dutyB);
void PWMInitCD(uint16_t period, uint16_t dutyC, uint16_t dutyD);
void PWMDutyD(uint16_t dutyD);
void PWMDutyC(unint16_t dutyC);

#endif 