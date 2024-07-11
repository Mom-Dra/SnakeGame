#include <stdlib.h>
#include "event.h"
#include "player.h"
#include "map.h"

// 이벤트 함수 등록하는건 나중에 해보자!
halfSecondInterval = 500;
oneSecondInterval = 3000;

void PlayerMoveEvent()
{
	MovePlayer(currentDir);
}

void GenerateItemEvent()
{
	int x, y;
	// 맵을 순회 하면서 0이면 랜덤 위치에 생성해야겠다
	
	// 랜덤 포지션 생성!
	// 맵이 0이 아니면  
	while (1)
	{
		x = rand() % MAP_WIDTH;
		y = rand() % MAP_HEIGHT;

		if (ORIGIN_MAP[y][x] == BLOCK_BLANK)
		{
			break;
		}
	}

	ORIGIN_MAP[y][x] = BLOCK_ITEM;
}