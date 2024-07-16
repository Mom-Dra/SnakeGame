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
	// �ʿ� ���� ������ ����

	// ������ ������ �������� ����
	
	// ���� ��Ҹ� �ľ�����
	// �׸���...

	SetMapBlock(aiArr[size - 1].x, aiArr[size - 1].y, BLOCK_BLANK);

	for (int i = size - 1; i >= 1; --i)
	{
		aiArr[i] = aiArr[i - 1];

		SetMapBlock(aiArr[i].x, aiArr[i].y, BLOCK_AI_BODY);
	}

	// �Ӹ� ����
	struct Vector2 nextPos = CalNextAIPos();

	SetMapBlock(nextPos.x, nextPos.y, BLOCK_AI_HEAD);
	aiArr[0].x = nextPos.x;
	aiArr[0].y = nextPos.y;

	pos = nextPos;
}

struct Vector2 CalNextAIPos()
{	
	// ���� ������ ���� ����!
	// �ƴϸ� �������� ������!
	struct Vector2 nextPos = pos;

	if (IsExistItem())
	{
		// ���� ����� ���� ���� ���� ���� ��찡 �ִ�..!

		// dx ������ ���� ��� -> Check!
		// dy ������ ���� ��� -> Check!

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
				// dir ó�� ����!!
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
				// �Ѵ� �� �� ���� ��
				// ��� �߿� �� �� �ִ��� üũ
				// ��濡 �� �� ������ �ڻ� ����
				// �� �� �ִ°� ������ ���� �������ΰ���

			}

			enum BlockType blockType = GetMapBlockType(nextPos.x, nextPos.y);

			if (blockType == BLOCK_ITEM)
			{ // �� ���� ����
				IncreaseAIBody();
				DecreaseItemCount(nextPos);

				return nextPos;
			}
			else if (blockType != BLOCK_BLANK)
			{ // ������ ���̽�
				continue;

				// �Ѵ� �װŸ�..
			}
			else
			{
				return nextPos;
			}
		}
	}
	else
	{ // ���� �ʿ� ���� ��
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