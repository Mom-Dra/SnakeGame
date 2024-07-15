#include <stdlib.h>
#include "AI.h"
#include "vector2.h"
#include "map.h"

static struct Vector2 pos = { MAP_WIDTH / 3, MAP_HEIGHT / 3 };

static struct Vector2* aiArr;
static int capacity = 5;
static int size = 1;

static int dir = 0;

void InitAI()
{
	if (aiArr == NULL)
	{
		aiArr = (struct Vector2*)malloc(capacity * sizeof(struct Vector2));
	}

	pos.x = MAP_WIDTH / 3;
	pos.y = MAP_HEIGHT / 3;

	size = 1;

	dir = 0;
}

void MoveAI()
{
	// 맵에 별이 있으면 별로

	// 없으면 무조건 랜덤으로 ㅇㅇ
	
	// 다음 장소를 파악하자
	// 그리고...

	SetMapBlock(pos.x, pos.y, BLOCK_BLANK);

	struct Vector2 nextPos = CalNextAIPos();

	SetMapBlock(nextPos.x, nextPos.y, BLOCK_AI_HEAD);

	pos = nextPos;
}

struct Vector2 CalNextAIPos()
{	
	// UP 근데 DOWN 못가잖아
	// 벽 또는 몸이 있어 그럼 못가잖아 ㅇㅇ!
	// 처리하자!

	// 맵에 별이 있을 때와 없을 때 계산하자!!!


	// 별이 있으면 별로 가기!
	// 아니면 랜덤으로 돌리자!

	// 생성할 때 배열에 저장해?
	
	// 가장 가까운 별을 찾기..

	struct Vector2 nextPos = pos;

	if (IsExistItem())
	{
		struct Vector2* items = GetItems();
		int* isInclude = GetIsIncluded();

		int minDistance = INT_MAX;
		int minIndex = 0;

		for (int i = 0; i < ITEM_ARR_LENGTH; ++i)
		{
			if (isInclude[i])
			{
				int distance = CalDistance(pos, items[i]);
				minDistance = distance < minDistance ? distance : minDistance;
				
				minIndex = i;
			}
		}

		int dx = items[minIndex].x - pos.x;
		int dy = items[minIndex].y - pos.y;
		// 우측으로 가야 하는데 좌측으로 이동중이었어.. 그럼 안되지..
		// 위로 가야 하는데 아래로 이동중 이었어.. 그럼 안되지..
		
		// x축 먼저 움직이자
		// y축은 나중에 ㄱㄱ

		// x축 먼저 움직이고

		// x 먼저 움직일건데..
		// 만약 움직이는 방향 때문에 못갈 수도 있어..
		// 그리고 벽인지도 체크 해야 하고!

		// 우측으로 가야 하는데 좌측으로 이동중이었어
		// 위로 가야하는데 아래로 이동중이었으면?

		// 이친구의 행위를 어떻게 정의 할건데?
		
		if (dx != 0)
		{
			if (dx > 0)
			{ // 오른쪽으로 가야 함!
				nextPos.x += 1;
				
				if (dir == -1)
				{
					// y한번 체크 하자
				}
			}
			else
			{ // 왼쪽으로 가야 함!
				nextPos.x -= 1;

				
			}
		}
		else if(dy != 0)
		{
			if (dy > 0)
			{ // 아래로 가야 함!
				nextPos.y += 1;
			}
			else
			{ // 위로 가야 함!
				nextPos.y -= 1;
			}
		}
	}
	else
	{
		while (1)
		{
			nextPos = pos;

			int num;
			num = rand() % 4;

			switch (num)
			{
			case UP:
				if (dir == DOWN) continue;
				nextPos.y -= 1;
				break;
			case DOWN:
				if (dir == UP) continue;
				nextPos.y += 1;
				break;
			case LEFT:
				if (dir == RIGHT) continue;
				nextPos.x -= 1;
				break;
			case RIGHT:
				if (dir == LEFT) continue;
				nextPos.x += 1;
				break;
			}

			enum BlockType type = GetMapBlockType(nextPos.x, nextPos.y);

			if (type = BLOCK_BLANK)
			{
				dir = num;
				return nextPos;
			}
		}
	}
}

void IncreaseAIBody()
{
	if (size >= capacity)
	{
		capacity *= 2;
		aiArr = (struct Vector2*)realloc(aiArr, capacity * sizeof(struct Vector2));
	}

	aiArr[size] = aiArr[size - 1];
	++size;
}

int CalDistance(struct Vector2 pos1, struct Vector2 pos2)
{
	int x = pos1.x - pos2.x;
	int y = pos1.y - pos2.y;

	return x * x + y * y;
}