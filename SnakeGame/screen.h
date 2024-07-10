#pragma once

#include <time.h>

// INPUT
// �Է� �ޱ�
// 
// UPDATE
// �Է¿� ���� ���� ����
// �Է¿� ���� ���� ����!
// 
// RENDER
// ���

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