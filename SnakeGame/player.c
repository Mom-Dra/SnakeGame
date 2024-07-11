#include "player.h"
#include "map.h"
#include "vector2.h"
#include <conio.h>

static struct Vector2 playerPos = { 15, 15 };
static int currentDir = KEY_RIGHT;

void SetPlayerPos()
{
	SetMapBlock(playerPos.x, playerPos.y, BLOCK_PLAYER_HEAD);
}

struct Vector2 GetPlayerPos()
{
	return playerPos;
}

void MovePlayer()
{
	SetMapBlock(playerPos.x, playerPos.y, BLOCK_BLANK);

	switch (currentDir)
	{
	case KEY_LEFT:
		MoveLeft();
		break;
	case KEY_RIGHT:
		MoveRight();
		break;
	case KEY_UP:
		MoveUp();
		break;
	case KEY_DOWN:
		MoveDown();
		break;
	}
}

void MoveLeft()
{
	playerPos.x -= 1;
}

void MoveRight()
{
	playerPos.x += 1;
}

void MoveUp()
{
	playerPos.y -= 1;
}

void MoveDown()
{	
	playerPos.y += 1;
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
			case KEY_LEFT:
				currentDir = KEY_LEFT;
				break;
			case KEY_RIGHT:
				currentDir = KEY_RIGHT;
				break;
			case KEY_UP:
				currentDir = KEY_UP;
				break;
			case KEY_DOWN:
				currentDir = KEY_DOWN;
				break;
			}
		}
	}
}

struct Vector2 GetNextPlayerPos()
{
	struct Vector2 nextPos = playerPos;

	switch (currentDir)
	{
	case KEY_LEFT:
		nextPos.x -= 1;
		break;
	case KEY_RIGHT:
		nextPos.x += 1;
		break;
	case KEY_UP:
		nextPos.y -= 1;
		break;
	case KEY_DOWN:
		nextPos.y += 1;
		break;
	}

	return nextPos;
}