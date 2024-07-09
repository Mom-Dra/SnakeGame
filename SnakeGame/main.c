#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// INPUT
// 입력 받기
// 
// UPDATE
// 입력에 따른 로직 세팅
// 입력에 따른 버퍼 세팅!
// 
// RENDER
// 출력

static int g_nScreenIndex;
static HANDLE g_hScreen[2];
int g_numofFPS;
clock_t CurTime, OldTime;
char* FPSTextInfo;

int desiredFPS = 100;

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
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void Render()
{
	

	/*if (CurTime - OldTime >= 1000)
	{
		sprintf(FPSTextInfo, "FPS : %d", g_numofFPS);
		OldTime = CurTime;
		g_numofFPS = 0;
	}*/

	//g_numofFPS++;
	//ScreenPrint(0, 0, FPSTextInfo);
	ScreenPrint(1, 1, "★");
	ScreenPrint(1, 2, "★");
	ScreenPrint(1, 3, "★");
	ScreenPrint(1, 4, "★");
	
	
}

//void Release()
//{
//	free(FPSTextInfo);
//}

void InputKey()
{
	int key;

	if (_kbhit())
	{
		char ch = _getch();

		if (ch == 'q')
		{
			ScreenPrint(1, 5, "★");
		}
	}
}

int main()
{
	ScreenInit();

	clock_t lastTime = clock();
	int millisecondsPerFrame = 1000 / desiredFPS;

	// 무한 루프!
	while (1)
	{
		clock_t currentTime = clock();
		clock_t deltaTime = currentTime - lastTime;
		
		if (deltaTime >= millisecondsPerFrame)
		{
			InputKey();


			Render();
			ScreenClear();
			ScreenFlipping();

			lastTime = currentTime;
		}

		
	}

	//Release();
	ScreenRelease();

	return 0;
}