#pragma once

#define ROW_NUM_TITLE 9

#define MAP_HEIGHT 30
#define MAP_WIDTH 30

#define TITLE_WIDTH 51
#define ENDING_WIDTH 90

#define ITEM_ARR_LENGTH 100

//#define BLOCK_BLANK 0
//#define BLOCK_WALL 1
//#define BLOCK_PLAYER_HEAD 2
//#define BLOCK_PLAYER_BODY 3
//#define BLOCK_ITEM 4

enum BlockType
{
	BLOCK_BLANK,
	BLOCK_WALL,
	BLOCK_PLAYER_HEAD,
	BLOCK_PLAYER_BODY,
	BLOCK_ITEM,
	BLOCK_AI_HEAD,
	BLOCK_AI_BODY
};

extern const char Title[][51];
extern const char Ending[][91];

void InitMap();
const char* GetBlockString(int x, int y);
void SetMapBlock(int x, int y, enum BlockType blockType);
//void SetMapBlock(struct Vector2 pos, enum BlockType blockType);
enum BlockType GetMapBlockType(int x, int y);
//int GetMapBlock(struct Vector2 pos);
void IncreaseItemCount(int x, int y);
void DecreaseItemCount();
int IsExistItem();
int* GetIsIncluded();
struct Vector2* GetItems();