#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "screen.h"
#include "map.h"

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

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
}

void DrawMap()
{
	for (int nY = 0; nY < MAP_HEIGHT; ++nY)
	{
		for (int nX = 0; nX < MAP_WIDTH; ++nX)
		{
			ScreenPrint(nX * 2, nY, GetBlockString(nX, nY));
		}
	}
}

void DrawInitialScreen()
{
	printf("DrawInitialScreen\n");
	/*for (int nY = 0; nY < MAP_HEIGHT; ++nY)
	{
		for (int nX = 0; nX < MAP_WIDTH; ++nX)
		{
			ScreenPrint(nX * 2, nY, GetBlockString(nX, nY));
		}
	}*/
}

void DrawEndingScreen()
{
	printf("DrawEndingScreen\n");
	/*for (int nY = 0; nY < MAP_HEIGHT; ++nY)
	{
		for (int nX = 0; nX < MAP_WIDTH; ++nX)
		{
			ScreenPrint(nX * 2, nY, GetBlockString(nX, nY));
		}
	}*/
}

void BreakScreen()
{
	printf("아무키를 누르면 시작됩니다!\n");

	while (!_kbhit())
	{

	}
}