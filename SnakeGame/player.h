#pragma once

#define PLAYER_NUM 2
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

extern int playerX;
extern int playerY;
extern int currentDir;

void CalcPlayer();
void MovePlayer(int dir);
void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();
void InputKey();