#pragma once
#include <time.h>
//#include "player.h"

clock_t aiMoveEventTimer;
clock_t playerMoveEventTimer;
clock_t itemGenerateEventTimer;
clock_t wallGenerateEventTimer;


// 지역 변수로 바꾸자!
extern int aiMoveInterval;
extern int playerMoveInterval;
extern int itemGenerateInterval;
extern int wallGenerateInterval;

void InitEvent();
void AIMoveEvent();
void PlayerMoveEvent();
void GenerateBlockEvent(enum BlockType blockType);
void CheckCollision();
void DecreasePlayerMoveInterval();
void DecreaseAIMoveInterval();
void IncreaseAIMoveInterval();
void DecreaseItemGenerateInterval();