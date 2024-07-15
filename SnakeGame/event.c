#include <stdlib.h>
#include "debug.h"
#include "event.h"
#include "player.h"
#include "map.h"
#include "vector2.h"
#include "GameManager.h"
#include "AI.h"

#ifdef DEBUG
aiMoveInterval = 100;
playerMoveInterval = 100;
itemGenerateInterval = 1000;
wallGenerateInterval = 1000;
#else
aiMoveInterval = 500;
playerMoveInterval = 500;
itemGenerateInterval = 5000;
wallGenerateInterval = 30000;
#endif // DEBUG

void InitEvent()
{
#ifdef DEBUG
	aiMoveInterval = 100;
	playerMoveInterval = 100;
	itemGenerateInterval = 1000;
	wallGenerateInterval = 1000;
#else
	aiMoveInterval = 500;
	playerMoveInterval = 500;
	itemGenerateInterval = 5000;
	wallGenerateInterval = 30000;
#endif // DEBUG
}

void AIMoveEvent()
{
	MoveAI();
}

void PlayerMoveEvent()
{
	MovePlayer();
	IncreaseScore(1);
}

void GenerateBlockEvent(enum BlockType blockType)
{
	int x, y;

	// ���� ��ȸ �ϸ鼭 blank �̸� ���� ��ġ�� �����ؾ߰ڴ�
	
	// ���� ������ ����!
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

	if (blockType == BLOCK_ITEM)
	{ 
		IncreaseItemCount(x, y);
	}
	else if (blockType == BLOCK_WALL)
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
		DecreaseItemCount();
		break;
	case BLOCK_AI_HEAD:
		GameOver();
		break;
	case BLOCK_AI_BODY:
		GameOver();
		break;
	}
}

void DecreasePlayerMoveInterval()
{
	playerMoveInterval -= 20;
	if (playerMoveInterval < 70) playerMoveInterval = 70;
}