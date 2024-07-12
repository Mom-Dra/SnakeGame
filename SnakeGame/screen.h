#pragma once

#include <time.h>

extern int g_numofFPS;
extern clock_t CurTime, OldTime;
extern char* FPSTextInfo;
extern int desiredFPS;

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, const char* string);
void Render();
void DrawMap();
void DrawInitialScreen();
void DrawEndingScreen();
void BreakScreen();