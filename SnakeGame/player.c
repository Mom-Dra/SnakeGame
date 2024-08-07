#include "player.h"
#include "map.h"
#include "vector2.h"
#include <conio.h>
#include <stdlib.h>

static struct Vector2 playerPos = { MAP_WIDTH / 2, MAP_HEIGHT / 2 };
static int currentDir = KEY_RIGHT;
static int beforeDir = KEY_RIGHT;

// Body의 0번째 인덱스는 항상 머리 인걸로;
static struct Body* playerArr;
static int capacity = 5;
static int size = 1;

void InitPlayer()
{
	if (playerArr == NULL)
	{
		playerArr = (struct Body*)malloc(capacity * sizeof(struct Body));
	}

	currentDir = KEY_RIGHT;
	beforeDir = KEY_RIGHT;

	size = 1;
	playerPos.x = MAP_WIDTH / 2;
	playerPos.y = MAP_HEIGHT / 2;

	playerArr[0].pos.x = playerPos.x;
	playerArr[0].pos.y = playerPos.y;
}

void SetPlayerPos()
{
	// 마지막에 있었던건 지우자
	// size가 2라면
	SetMapBlock(playerArr[size - 1].pos.x, playerArr[size - 1].pos.y, BLOCK_BLANK);

	// 처음에는 머리의 방향으로 갈거야 ! ! !
	for (int i = size - 1; i >= 1; --i)
	{
		playerArr[i] = playerArr[i - 1];

		SetMapBlock(playerArr[i].pos.x, playerArr[i].pos.y, BLOCK_PLAYER_BODY);
	}

	// 머리 설정
	SetMapBlock(playerPos.x, playerPos.y, BLOCK_PLAYER_HEAD);
	playerArr[0].pos.x = playerPos.x;
	playerArr[0].pos.y = playerPos.y;
}

struct Vector2 GetPlayerPos()
{
	return playerPos;
}

void MovePlayer()
{
	int isNewMoved = 0;
	switch (currentDir)
	{
	case KEY_LEFT:
		if (beforeDir != KEY_RIGHT)
		{
			MoveLeft();
			isNewMoved = 1;
		}
		else
		{
			MoveRight();
		}
		break;
	case KEY_RIGHT:
		if (beforeDir != KEY_LEFT)
		{
			MoveRight();
			isNewMoved = 1;
		}
		else
		{
			MoveLeft();
		}
		break;
	case KEY_UP:
		if (beforeDir != KEY_DOWN)
		{
			MoveUp();
			isNewMoved = 1;
		}
		else
		{
			MoveDown();
		}
		break;
	case KEY_DOWN:
		if (beforeDir != KEY_UP)
		{
			MoveDown();
			isNewMoved = 1;
		}
		else
		{
			MoveUp();
		}
		break;
	}

	if (isNewMoved)
		beforeDir = currentDir;
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
		if (beforeDir != KEY_RIGHT)
		{
			nextPos.x -= 1;
		}
		else
		{
			nextPos.x += 1;
		}
		break;
	case KEY_RIGHT:
		if (beforeDir != KEY_LEFT)
		{
			nextPos.x += 1;
		}
		else
		{
			nextPos.x -= 1;
		}
		break;
	case KEY_UP:
		if (beforeDir != KEY_DOWN)
		{
			nextPos.y -= 1;
		}
		else
		{
			nextPos.y += 1;
		}
		break;
	case KEY_DOWN:
		if (beforeDir != KEY_UP)
		{
			nextPos.y += 1;
		}
		else
		{
			nextPos.y -= 1;
		}
		break;
	}

	return nextPos;
}

void IncreaseBody()
{
	if (size >= capacity)
	{
		capacity *= 2;
		playerArr = (struct Body*)realloc(playerArr, capacity * sizeof(struct Body));
	}

	// 맨 뒤에 있는 블럭 방향의 (이동 방향의 반대 방향에 생성되어야 한다
	playerArr[size] = playerArr[size - 1];
	++size;
}