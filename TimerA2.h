#ifndef __TIMERA2INTS_H__ 
#define __TIMERA2INTS_H__

void TimerA2Init(void(*task)(void), uint16_t period);
void TimerA2End();

#endif
