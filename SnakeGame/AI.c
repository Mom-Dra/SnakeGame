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
	// �ʿ� ���� ������ ����

	// ������ ������ �������� ����
	
	// ���� ��Ҹ� �ľ�����
	// �׸���...

	SetMapBlock(pos.x, pos.y, BLOCK_BLANK);

	struct Vector2 nextPos = CalNextAIPos();

	SetMapBlock(nextPos.x, nextPos.y, BLOCK_AI_HEAD);

	pos = nextPos;
}

struct Vector2 CalNextAIPos()
{	
	// UP �ٵ� DOWN �����ݾ�
	// �� �Ǵ� ���� �־� �׷� �����ݾ� ����!
	// ó������!

	// �ʿ� ���� ���� ���� ���� �� �������!!!


	// ���� ������ ���� ����!
	// �ƴϸ� �������� ������!

	// ������ �� �迭�� ������?
	
	// ���� ����� ���� ã��..

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
		// �������� ���� �ϴµ� �������� �̵����̾���.. �׷� �ȵ���..
		// ���� ���� �ϴµ� �Ʒ��� �̵��� �̾���.. �׷� �ȵ���..
		
		// x�� ���� ��������
		// y���� ���߿� ����

		// x�� ���� �����̰�

		// x ���� �����ϰǵ�..
		// ���� �����̴� ���� ������ ���� ���� �־�..
		// �׸��� �������� üũ �ؾ� �ϰ�!

		// �������� ���� �ϴµ� �������� �̵����̾���
		// ���� �����ϴµ� �Ʒ��� �̵����̾�����?

		// ��ģ���� ������ ��� ���� �Ұǵ�?
		
		if (dx != 0)
		{
			if (dx > 0)
			{ // ���������� ���� ��!
				nextPos.x += 1;
				
				if (dir == -1)
				{
					// y�ѹ� üũ ����
				}
			}
			else
			{ // �������� ���� ��!
				nextPos.x -= 1;

				
			}
		}
		else if(dy != 0)
		{
			if (dy > 0)
			{ // �Ʒ��� ���� ��!
				nextPos.y += 1;
			}
			else
			{ // ���� ���� ��!
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