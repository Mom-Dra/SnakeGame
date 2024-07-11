#pragma once

#define MAP_HEIGHT 30
#define MAP_WIDTH 30

#define BLOCK_BLANK 0
#define BLOCK_WALL 1
#define BLOCK_PLAYER_HEAD 2
#define BLOCK_PLAYER_BODY 3
#define BLOCK_ITEM 4

extern int ORIGIN_MAP[MAP_HEIGHT][MAP_WIDTH];
extern const char BLOCK_TYPES[][4];
