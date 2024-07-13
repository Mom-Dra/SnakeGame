#include <stdlib.h>
#include "debug.h"
#include "event.h"
#include "player.h"
#include "map.h"
#include "vector2.h"
#include "GameManager.h"

#ifdef DEBUG
playerMoveInterval = 100;
itemGenerateInterval = 1000;
wallGenerateInterval = 1000;
#else
playerMoveInterval = 500;
itemGenerateInterval = 5000;
wallGenerateInterval = 30000;
#endif // DEBUG

void InitEvent()
{
#ifdef DEBUG
	playerMoveInterval = 100;
	itemGenerateInterval = 1000;
	wallGenerateInterval = 1000;
#else
	playerMoveInterval = 500;
	itemGenerateInterval = 5000;
	wallGenerateInterval = 30000;
#endif // DEBUG
}

void PlayerMoveEvent()
{
	MovePlayer();
	IncreaseScore(1);
}

void GenerateBlockEvent(enum BlockType blockType)
{
	int x, y;

	// 맵을 순회 하면서 blank 이면 랜덤 위치에 생성해야겠다
	
	// 랜덤 포지션 생성!
	while (1)
	{
		x = rand() % MAP_WIDTH;
		y = rand() % MAP_HEIGHT;

		if (GetMapBlockType(x, y) == BLOCK_BLANK)
		{
			break;
		}
	}

	SetMapBlock(x, y, blockType);

	if (blockType == BLOCK_WALL)
	{
		IncreaseItemScore();
	}
}

void CheckCollision()
{
	struct Vector2 nextPos = GetNextPlayerPos();

	enum BlockType block = GetMapBlockType(nextPos.x, nextPos.y);

	switch (block)
	{
	case BLOCK_BLANK:
		break;
	case BLOCK_WALL:
		GameOver();
		break;
	case BLOCK_PLAYER_HEAD:
		break;
	case BLOCK_PLAYER_BODY:
		GameOver();
		break;
	case BLOCK_ITEM:
		IncreaseBody();
		DecreasePlayerMoveInterval();
		IncreaseScore(GetItemScore());
		break;
	}
}

void DecreasePlayerMoveInterval()
{
	playerMoveInterval -= 20;
	if (playerMoveInterval < 50)playerMoveInterval = 50;
}