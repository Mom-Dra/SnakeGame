#pragma once

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

void InitAI();
void MoveAI();
struct Vector2 CalNextAIPos();