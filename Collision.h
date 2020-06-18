#ifndef COLLISION_H_
#define COLLISION_H_

#define hitWallFlag 0
static uint8_t collisionTriggerVal = 0;
static uint8_t port4BitMask = 0xED; //0b1110_1101;

void collisionInit(void(*task)(uint8_t));
uint8_t collisionRead();
void collisionHandler(uint8_t collisionSense);
void collisionClear();

#endif 