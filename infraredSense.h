#ifndef INFRAREDSENSE_H_
#define INFRAREDSENSE_H_

void IRStart();
uint8_t IRStop();
void Reflectance_Init(void);
int32_t RobotPosition(uint8_t data);
uint8_t IRRead(uint32_t time);

#endif
