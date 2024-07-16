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

	size = 1;

	pos.x = MAP_WIDTH / 3;
	pos.y = MAP_HEIGHT / 3;

	aiArr[0].x = pos.x;
	aiArr[0].y = pos.y;

	dir = 0;
}

void MoveAI()
{
	// 맵에 별이 있으면 별로

	// 없으면 무조건 랜덤으로 ㅇㅇ
	
	// 다음 장소를 파악하자
	// 그리고...

	SetMapBlock(aiArr[size - 1].x, aiArr[size - 1].y, BLOCK_BLANK);

	for (int i = size - 1; i >= 1; --i)
	{
		aiArr[i] = aiArr[i - 1];

		SetMapBlock(aiArr[i].x, aiArr[i].y, BLOCK_AI_BODY);
	}

	// 머리 설정
	struct Vector2 nextPos = CalNextAIPos();

	SetMapBlock(nextPos.x, nextPos.y, BLOCK_AI_HEAD);
	aiArr[0].x = nextPos.x;
	aiArr[0].y = nextPos.y;

	pos = nextPos;
}

struct Vector2 CalNextAIPos()
{	
	// 별이 있으면 별로 가기!
	// 아니면 랜덤으로 돌리자!
	struct Vector2 nextPos = pos;

	if (IsExistItem())
	{
		// 가장 가까운 별로 가는 길이 막힌 경우가 있다..!

		// dx 방향이 막힌 경우 -> Check!
		// dy 방향이 막힌 경우 -> Check!

		struct Vector2* items = GetItems();
		int* isInclude = GetIsIncluded();

		int minDistance = INT_MAX;
		int minIndex = 0;

		for (int i = 0; i < ITEM_ARR_LENGTH; ++i)
		{
			if (isInclude[i])
			{
				int distance = CalDistance(pos, items[i]);

				if (distance < minDistance)
				{
					minDistance = distance;
					minIndex = i;
				}
			}
		}

		while (1)
		{
			nextPos = pos;

			enum BlockType blockType;

			int dx = items[minIndex].x - pos.x;
			int dy = items[minIndex].y - pos.y;

			int canMoveX = 1;
			int canMoveY = 1;
			
			if (abs(dx) > abs(dy))
			{
				// dir 처리 하자!!
				// x move
				nextPos.x += (dx > 0) ? 1 : -1;
				blockType = GetMapBlockType(nextPos.x, nextPos.y);

				if (blockType != BLOCK_BLANK)
				{
					canMoveX = 0;
					nextPos.x -= (dx > 0) ? 1 : -1;

					nextPos.y += (dy > 0) ? 1 : -1;
					blockType = GetMapBlockType(nextPos.x, nextPos.y);

					if (blockType != BLOCK_BLANK)
					{
						canMoveY = 0;
					}
				}
			}
			else
			{
				// y move
				nextPos.y += (dy > 0) ? 1 : -1;
				blockType = GetMapBlockType(nextPos.x, nextPos.y);

				if (blockType != BLOCK_BLANK)
				{
					canMoveY = 0;
					nextPos.y -= (dy > 0) ? 1 : -1;

					nextPos.x += (dx > 0) ? 1 : -1;
					blockType = GetMapBlockType(nextPos.x, nextPos.y);

					if (blockType != BLOCK_BLANK)
					{
						canMoveX = 0;
					}
				}
			}

			if (canMoveX == 0 && canMoveY)
			{
				// 둘다 갈 수 없을 때
				// 사방 중에 갈 수 있는지 체크
				// 사방에 갈 수 없으면 자살 로직
				// 갈 수 있는게 있으면 랜덤 로직으로가자

			}

			enum BlockType blockType = GetMapBlockType(nextPos.x, nextPos.y);

			if (blockType == BLOCK_ITEM)
			{ // 몸 길이 증가
				IncreaseAIBody();
				DecreaseItemCount(nextPos);

				return nextPos;
			}
			else if (blockType != BLOCK_BLANK)
			{ // 못가는 케이스
				continue;

				// 둘다 그거면..
			}
			else
			{
				return nextPos;
			}
		}
	}
	else
	{ // 별이 맵에 없을 때
		return GetRandomPos();
	}
}

struct Vector2 GetRandomPos()
{
	while (1)
	{
		struct Vector2 nextPos = pos;

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

		if (type == BLOCK_BLANK)
		{
			dir = num;
			return nextPos;
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