#include "screen.h"
#include <Windows.h>
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

	//funcArr = (void (**)(void))malloc(capacity * sizeof(void (*)(void)));
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
	Map();

	// 플레이ㅓ 그리기

	/*if (CurTime - OldTime >= 1000)
	{
		sprintf(FPSTextInfo, "FPS : %d", g_numofFPS);
		OldTime = CurTime;
		g_numofFPS = 0;
	}*/

	//g_numofFPS++;
	//ScreenPrint(0, 0, FPSTextInfo);
	
}


//void Release()
//{
//	free(FPSTextInfo);
//}



//void AddRenderFunc(void (*func)(void))
//{
//	if (size >= capacity)
//	{
//		capacity *= 2;
//
//		funcArr = (void (**)(void))realloc(funcArr, capacity * sizeof(void(*)(void)));
//	}
//
//	funcArr[size] = func;
//	++size;
//}

void Map()
{
	// width 2 * 29 = 58 -> 0 ~ 58
	// height 0 ~ 29

	/*for (int i = 0; i < 30; ++i)
	{
		ScreenPrint(i * 2, 0, "■");
		ScreenPrint(0, i, "■");
		ScreenPrint(29 * 2, i, "■");

		ScreenPrint(i * 2, 29, "■");
	}*/      

	for (int nY = 0; nY < MAP_HEIGHT; ++nY)
	{
		for (int nX = 0; nX < MAP_WIDTH; ++nX)
		{
			ScreenPrint(nX * 2, nY, BLOCK_TYPES[ORIGIN_MAP[nY][nX]]);
		}
	}
}