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
#include "AI.h"
#include "sound.h"

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
// AI
// ����
// GameOver�� ����

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
		PlayGameStart();
		DrawInitialScreen();

		BreakScreen();

		GameLoop();

		PlayGameOverSound();
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

	InitAI();

	InitPlayer();

	InitGameManager();
}

void GameLoop()
{
	Init();

	clock_t lastTime = clock();
	int millisecondsPerFrame = 1000 / desiredFPS;

	aiMoveEventTimer = lastTime;
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

			// ������ ���� �̺�Ʈ
			clock_t itemGenerateEventDeltaTime = currentTime - itemGenerateEventTimer;

			if (itemGenerateEventDeltaTime >= itemGenerateInterval)
			{
				GenerateBlockEvent(BLOCK_ITEM);

				itemGenerateEventTimer = currentTime;
			}

			// �� ���� �̺�Ʈ
			clock_t wallGenerateEventDeltaTime = currentTime - wallGenerateEventTimer;

			if (wallGenerateEventDeltaTime >= wallGenerateInterval)
			{
				// �� ���� �̺�Ʈ
				GenerateBlockEvent(BLOCK_WALL);
				wallGenerateEventTimer = currentTime;
			}

			// AI ������ �̺�Ʈ
			clock_t aiMoveEventDeltaTime = currentTime - aiMoveEventTimer;

			if (aiMoveEventDeltaTime >= aiMoveInterval)
			{
				AIMoveEvent();

				aiMoveEventTimer = currentTime;
			}

			// �̺�Ʈ 1
			clock_t playerMoveEventDeltaTime = currentTime - playerMoveEventTimer;

			if (playerMoveEventDeltaTime >= playerMoveInterval)
			{
				// �÷��̾� ������ �̺�Ʈ
				CheckCollision();

				// ���⼭ ������ playerPos�� �����δ�
				PlayMoveSound();
				PlayerMoveEvent();

				SetPlayerPos();

				playerMoveEventTimer = currentTime;
			}
		}
	}
}
