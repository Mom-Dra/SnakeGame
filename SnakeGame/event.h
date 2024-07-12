#pragma once
#include <time.h>
//#include "player.h"

clock_t playerMoveEventTimer;
clock_t itemGenerateEventTimer;
clock_t wallGenerateEventTimer;

extern int playerMoveInterval;
extern int itemGenerateInterval;
extern int wallGenerateInterval;

void InitEvent();
void PlayerMoveEvent();
void GenerateBlockEvent(enum BlockType blockType);
void CheckCollision();
void DecreasePlayerMoveInterval();