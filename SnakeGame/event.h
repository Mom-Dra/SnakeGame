#pragma once
#include <time.h>
//#include "player.h"

clock_t oneEventTimer;
clock_t halfEventTimer;
extern int halfSecondInterval;
extern int oneSecondInterval;

void PlayerMoveEvent();
void GenerateItemEvent();
void CheckCollision();