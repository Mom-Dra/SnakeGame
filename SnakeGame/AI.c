#include <stdlib.h>
#include "AI.h"
#include "vector2.h"
#include "map.h"
#include "event.h"

static struct Vector2 pos = { MAP_WIDTH / 3, MAP_HEIGHT / 3 };

static struct Vector2* aiArr;
static int capacity = 5;
static int size = 1;

static int dir = -1;

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

	dir = -1;
}

struct Vector2 ReGenerateAI()
{
	// ReGenerate �ؾ���!

	for (int i = 0; i < size; ++i)
	{
		SetMapBlock(aiArr[i].x, aiArr[i].y, BLOCK_BLANK);
	}

	size = 1;
	dir = -1;
	IncreaseAIMoveInterval();

	struct Vector2 newPos;

	while (1)
	{
		int x = rand() % MAP_WIDTH;
		int y = rand() % MAP_HEIGHT;

		enum BlockType blockType = GetMapBlockType(x, y);

		if (blockType == BLOCK_BLANK)
		{
			newPos.x = x;
			newPos.y = y;

			return newPos;
		}
	}
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

	struct Vector2 nextPos = CalNextAIPos();

	// �Ӹ� ����
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

	if (!CangoFourDir())
		return ReGenerateAI();

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

			int beforeDir = dir;
			
			if (abs(dx) > abs(dy))
			{
				// dir ó�� ����!!
				// x move
				nextPos.x += (dx > 0) ? 1 : -1;
				blockType = GetMapBlockType(nextPos.x, nextPos.y);
				dir = (dx > 0) ? RIGHT : LEFT;
				
				if (!CanGoBlock(blockType))
				{
					canMoveX = 0;
					nextPos.x -= (dx > 0) ? 1 : -1;

					nextPos.y += (dy > 0) ? 1 : -1;
					blockType = GetMapBlockType(nextPos.x, nextPos.y);
					dir = (dy > 0) ? DOWN : UP;

					if (!CanGoBlock(blockType))
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
				dir = (dy > 0) ? DOWN : UP;

				if (!CanGoBlock(blockType))
				{
					canMoveY = 0;
					nextPos.y -= (dy > 0) ? 1 : -1;

					nextPos.x += (dx > 0) ? 1 : -1;
					blockType = GetMapBlockType(nextPos.x, nextPos.y);
					dir = (dx > 0) ? RIGHT : LEFT;

					if (!CanGoBlock(blockType))
					{
						canMoveX = 0;
					}
				}
			}

			if (canMoveX == 0 && canMoveY == 0)
			{
				dir = beforeDir;
				// ��濡 �� �� ���� ��
				if (!CangoFourDir())
					return ReGenerateAI();
				
				return GetRandomPos();
			}

			blockType = GetMapBlockType(nextPos.x, nextPos.y);

			if (blockType == BLOCK_ITEM)
			{ // �� ���� ����
				IncreaseAIBody();
				DecreaseItemCount(nextPos);
				DecreaseAIMoveInterval();

				return nextPos;
			}
			else if (blockType == BLOCK_BLANK)
			{ 

				return nextPos;
			}
			else
			{
				// ������ ���̽�
				continue;
			}
		}
	}
	else
	{ // ���� �ʿ� ���� ��
		if (!CangoFourDir())
			return ReGenerateAI();

		return GetRandomPos();
	}
}

int CangoFourDir()
{
	enum BlockType blockType;

	// ��
	blockType = GetMapBlockType(pos.x, pos.y - 1);
	if (blockType == BLOCK_BLANK) return 1;

	// �� 
	blockType = GetMapBlockType(pos.x, pos.y + 1);
	if (blockType == BLOCK_BLANK) return 1;

	// ��
	blockType = GetMapBlockType(pos.x - 1, pos.y);
	if (blockType == BLOCK_BLANK) return 1;

	// ��
	blockType = GetMapBlockType(pos.x + 1, pos.y);
	if (blockType == BLOCK_BLANK) return 1;

	return 0;
}

struct Vector2 GetRandomPos()
{
	// ���� ���� �ִµ� �Դ� ���� �� �ڻ� ��������

	enum BlockType upBlockType, downBlockType, leftBlockType, rightBlockType;
	upBlockType = GetMapBlockType(pos.x, pos.y - 1);
	downBlockType = GetMapBlockType(pos.x, pos.y + 1);
	leftBlockType = GetMapBlockType(pos.x - 1, pos.y);
	rightBlockType = GetMapBlockType(pos.x + 1, pos.y);

	while (1)
	{
		struct Vector2 nextPos = pos;

		int num;
		num = rand() % 4;

		switch (num)
		{
		case UP:
			if (dir == DOWN)
			{
				if (!CanGoBlock(downBlockType) && !CanGoBlock(leftBlockType) && !CanGoBlock(rightBlockType))
					ReGenerateAI();

				continue;
			}
			nextPos.y -= 1;
			break;
		case DOWN:
			if (dir == UP)
			{
				if (!CanGoBlock(upBlockType) && !CanGoBlock(leftBlockType) && !CanGoBlock(rightBlockType))
					ReGenerateAI();

				continue;
			}
			nextPos.y += 1;
			break;
		case LEFT:
			if (dir == RIGHT)
			{
				if (!CanGoBlock(upBlockType) && !CanGoBlock(downBlockType) && !CanGoBlock(rightBlockType))
					ReGenerateAI();

				continue;
			}
			nextPos.x -= 1;
			break;
		case RIGHT:
			if (dir == LEFT)
			{
				if (!CanGoBlock(upBlockType) && !CanGoBlock(downBlockType) && !CanGoBlock(leftBlockType))
					ReGenerateAI();

				continue;
			}
			nextPos.x += 1;
			break;
		}

		enum BlockType type = GetMapBlockType(nextPos.x, nextPos.y);

		if (type == BLOCK_BLANK)
		{
			dir = num;
			return nextPos;
		}
		else if (type == BLOCK_ITEM)
		{
			dir = num;

			IncreaseAIBody();
			DecreaseItemCount(nextPos);
			DecreaseAIMoveInterval();

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