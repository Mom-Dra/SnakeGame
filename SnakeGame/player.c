#include "player.h"
#include "map.h"
#include <conio.h>

playerX = 15;
playerY = 15;

currentDir = RIGHT;

void CalcPlayer()
{
	ORIGIN_MAP[playerY][playerX] = BLOCK_PLAYER_HEAD;
}

void MovePlayer(int dir)
{
	switch (dir)
	{
	case LEFT:
		MoveLeft();
		break;
	case RIGHT:
		MoveRight();
		break;
	case UP:
		MoveUp();
		break;
	case DOWN:
		MoveDown();
		break;
	}
}

void MoveLeft()
{
	ORIGIN_MAP[playerY][playerX] = BLOCK_BLANK;
	playerX -= 1;
}

void MoveRight()
{
	ORIGIN_MAP[playerY][playerX] = BLOCK_BLANK;
	playerX += 1;
}

void MoveUp()
{
	ORIGIN_MAP[playerY][playerX] = BLOCK_BLANK;
	playerY -= 1;
}

void MoveDown()
{
	ORIGIN_MAP[playerY][playerX] = BLOCK_BLANK;
	playerY += 1;
}

void InputKey()
{
	int key;

	if (_kbhit())
	{
		key = _getch();

		if (key == 224)
		{
			key = _getch();

			switch (key)
			{
			case LEFT:
				currentDir = LEFT;
				break;
			case RIGHT:
				currentDir = RIGHT;
				break;
			case UP:
				currentDir = UP;
				break;
			case DOWN:
				currentDir = DOWN;
				break;
			}
		}
	}
}