#include <stdlib.h>
#include "event.h"
#include "player.h"
#include "map.h"

// �̺�Ʈ �Լ� ����ϴ°� ���߿� �غ���!
halfSecondInterval = 500;
oneSecondInterval = 3000;

void PlayerMoveEvent()
{
	MovePlayer(currentDir);
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

		if (ORIGIN_MAP[y][x] == BLOCK_BLANK)
		{
			break;
		}
	}

	ORIGIN_MAP[y][x] = BLOCK_ITEM;
}