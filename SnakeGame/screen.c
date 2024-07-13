#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "screen.h"
#include "map.h"
#include "GameManager.h"

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

static int RainbowColor[7] = { 12, 6, 3, 10, 9, 1, 13 };

static int score = 0;
static int maxScore = 0;
static char score_buffer[100];

void ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	// 화면 버퍼 2개를 만든다
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서를 숨긴다
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);

	RegistObserver(UpdateScore);
	score = 0;
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;

	// height * width 같은데?
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 60 * 60, Coor, &dw);
}

void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, const char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void Render()
{
	// 맵그리기
	DrawMap();
	DrawScore(MAP_WIDTH * 2, 0, score);
	DrawMaxScore(MAP_WIDTH * 2, 1, maxScore);
}

void DrawMap()
{
	int rainbowIndex = 0;

	for (int nY = 0; nY < MAP_HEIGHT; ++nY)
	{
		for (int nX = 0; nX < MAP_WIDTH; ++nX)
		{
			int blockType = GetMapBlockType(nX, nY);
			if(blockType == BLOCK_PLAYER_HEAD)
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 6);
			else if(blockType == BLOCK_ITEM)
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 14);
			else if (blockType == BLOCK_PLAYER_BODY)
			{
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], RainbowColor[rainbowIndex]);
				rainbowIndex = (rainbowIndex + 1) % 7;
			}
			else
				SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], 15);
			ScreenPrint(nX * 2, nY, GetBlockString(nX, nY));
		}
	}
}

void DrawInitialScreen()
{
	ScreenClear();

	// 더블 버퍼링으로 아스키 아트 그리기
	for (int i = 0; i < ROW_NUM_TITLE; ++i)
	{
		ScreenPrint(15, i, Title[i]);
	}

	ScreenPrint(15 + 10, 11, "PRESS SPACE BAR TO START");
	ScreenFlipping();
}

void DrawEndingScreen()
{
	ScreenClear();

	for (int i = 0; i < ROW_NUM_TITLE; ++i)
	{
		ScreenPrint(15, i, Ending[i]);
	}

	DrawScore(15 + 40, 11, score);
	DrawMaxScore(15 + 40, 12, maxScore);
	ScreenPrint(15 + 30, 14, "PRESS SPACE BAR TO CONTINUE");

	ScreenFlipping();
}

void DrawScore(int x, int y, int _score)
{
	sprintf(score_buffer, "점수: %d", _score);
	ScreenPrint(x, y, score_buffer);
}

void DrawMaxScore(int x, int y, int _score)
{
	sprintf(score_buffer, "최고 점수: %d", _score);
	ScreenPrint(x, y, score_buffer);
}

void BreakScreen()
{
	while (1)
	{
		if (_getch() == 32) break;
	}
}

void UpdateScore(int _score, int _maxScore)
{
	score = _score;
	maxScore = _maxScore;
}