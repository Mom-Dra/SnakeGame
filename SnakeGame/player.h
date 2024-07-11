#pragma once

#include "vector2.h"

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80

struct Body
{
	struct Vector2 pos;
	int dir;
};

void InitPlayer();
void SetPlayerPos();
struct Vector2 GetPlayerPos();
void MovePlayer();
void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();
void InputKey();
struct Vector2 GetNextPlayerPos();
void IncreaseBody();