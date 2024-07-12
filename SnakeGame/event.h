#pragma once
#include <time.h>
//#include "player.h"

clock_t playerMoveEventTimer;
clock_t halfEventTimer;
extern int playerMoveInterval;
extern int oneSecondInterval;

void InitEvent();
void PlayerMoveEvent();
void GenerateItemEvent();
void CheckCollision();
void DecreasePlayerMoveInterval();