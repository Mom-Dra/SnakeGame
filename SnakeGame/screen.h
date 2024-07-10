#pragma once

#include <time.h>

// INPUT
// 입력 받기
// 
// UPDATE
// 입력에 따른 로직 세팅
// 입력에 따른 버퍼 세팅!
// 
// RENDER
// 출력

extern int g_numofFPS;
extern clock_t CurTime, OldTime;
extern char* FPSTextInfo;
extern int desiredFPS;

//extern void (*funcArr[])(void);

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, const char* string);
void Render();

void Map();