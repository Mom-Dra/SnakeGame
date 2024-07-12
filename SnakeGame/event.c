#include <stdlib.h>
#include "debug.h"
#include "event.h"
#include "player.h"
#include "map.h"
#include "vector2.h"
#include "GameManager.h"

#ifdef DEBUG
playerMoveInterval = 100;
oneSecondInterval = 1000;
#else
playerMoveInterval = 500;
oneSecondInterval = 5000;
#endif // DEBUG

// �̺�Ʈ �Լ� ����ϴ°� ���߿� �غ���!


void InitEvent()
{
#ifdef DEBUG
	playerMoveInterval = 100;
	oneSecondInterval = 1000;
#else
	playerMoveInterval = 500;
	oneSecondInterval = 5000;
#endif // DEBUG
}

void PlayerMoveEvent()
{
	MovePlayer();
}

void GenerateItemEvent()
{
	int x, y;
	// ���� ��ȸ �ϸ鼭 0�̸� ���� ��ġ�� �����ؾ߰ڴ�
	
	// ���� ������ ����!
	// ���� 0�� �ƴϸ�  
	while (1)
	{
		x = rand() % MAP_WIDTH;
		y = rand() % MAP_HEIGHT;

		if (GetMapBlockType(x, y) == BLOCK_BLANK)
		{
			break;
		}
	}

	SetMapBlock(x, y, BLOCK_ITEM);
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
		break;
	default:
		break;
	}
}

void DecreasePlayerMoveInterval()
{
	playerMoveInterval -= 20;
	if (playerMoveInterval < 50)playerMoveInterval = 50;
}