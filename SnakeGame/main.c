#define _CRT_SECURE_NO_WARNINGS
#define DEBUG
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include "screen.h"
#include "player.h"
#include "event.h"
#include "map.h"
#include "GameManager.h"

// INPUT
// �Է� �ޱ�
// 
// UPDATE
// �Է¿� ���� ���� ����
// �Է¿� ���� ���� ����!
// 
// RENDER
// ���

// �����ؾ� �� ��
// 
// ����
// ����
// �ְ��� ����!
// ���� ���� ���� ������ֱ�

static int desiredFPS = 100; // --> GameManager�� �ű���

void Init();
void GameLoop();

int main()
{
	srand(time(NULL));
	ScreenInit();
	ReadMaxScore();

	while (1)
	{
		DrawInitialScreen();

		BreakScreen();

		GameLoop();

		DrawEndingScreen();

		BreakScreen();
	}
	
	ScreenRelease();

	return 0;
}

void Init()
{	
	//ScreenInit();

	InitEvent();

	InitMap();

	InitPlayer();

	InitGameManager();
}

void GameLoop()
{
	Init();

	clock_t lastTime = clock();
	int millisecondsPerFrame = 1000 / desiredFPS;

	playerMoveEventTimer = lastTime;
	itemGenerateEventTimer = lastTime;
	wallGenerateEventTimer = lastTime;

	while (!IsGameOver())
	{
		clock_t currentTime = clock();
		clock_t deltaTime = currentTime - lastTime;
		
		if (deltaTime >= millisecondsPerFrame)
		{
			InputKey();

			ScreenClear();

			Render();

			ScreenFlipping();

			lastTime = currentTime;

			// �̺�Ʈ 1
			clock_t playerMoveEventDeltaTime = currentTime - playerMoveEventTimer;

			if (playerMoveEventDeltaTime >= playerMoveInterval)
			{
				// �÷��̾� ������ �̺�Ʈ
				CheckCollision();

				// ���⼭ ������ playerPos�� �����δ�
				PlayerMoveEvent();

				SetPlayerPos();

				playerMoveEventTimer = currentTime;
			}

			// �̺�Ʈ 2
			clock_t itemGenerateEventDeltaTime = currentTime - itemGenerateEventTimer;

			if (itemGenerateEventDeltaTime >= itemGenerateInterval)
			{
				// ������ ���� �̺�Ʈ
				GenerateBlockEvent(BLOCK_ITEM);

				itemGenerateEventTimer = currentTime;
			}

			// �̺�Ʈ 3
			clock_t wallGenerateEventDeltaTime = currentTime - wallGenerateEventTimer;

			if (wallGenerateEventDeltaTime >= wallGenerateInterval)
			{
				// �� ���� �̺�Ʈ
				GenerateBlockEvent(BLOCK_WALL);
				wallGenerateEventTimer = currentTime;
			}
		}
	}
}
