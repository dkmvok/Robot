#ifndef __TIMERA0INTS_H__ 
#define __TIMERA0INTS_H__

void TimerA0Init(void(*task)(void), uint16_t period);
void TimerA0End();

#endif 