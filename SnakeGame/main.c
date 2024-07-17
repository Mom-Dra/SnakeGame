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
// 입력 받기
// 
// UPDATE
// 입력에 따른 로직 세팅
// 입력에 따른 버퍼 세팅!
// 
// RENDER
// 출력

// 구현해야 할 것
// AI
// 사운드
// GameOver로 수정

static int desiredFPS = 100; // --> GameManager로 옮기자

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

			// 아이템 생성 이벤트
			clock_t itemGenerateEventDeltaTime = currentTime - itemGenerateEventTimer;

			if (itemGenerateEventDeltaTime >= itemGenerateInterval)
			{
				GenerateBlockEvent(BLOCK_ITEM);

				itemGenerateEventTimer = currentTime;
			}

			// 벽 생성 이벤트
			clock_t wallGenerateEventDeltaTime = currentTime - wallGenerateEventTimer;

			if (wallGenerateEventDeltaTime >= wallGenerateInterval)
			{
				// 벽 생성 이벤트
				GenerateBlockEvent(BLOCK_WALL);
				wallGenerateEventTimer = currentTime;
			}

			// AI 움직임 이벤트
			clock_t aiMoveEventDeltaTime = currentTime - aiMoveEventTimer;

			if (aiMoveEventDeltaTime >= aiMoveInterval)
			{
				AIMoveEvent();

				aiMoveEventTimer = currentTime;
			}

			// 이벤트 1
			clock_t playerMoveEventDeltaTime = currentTime - playerMoveEventTimer;

			if (playerMoveEventDeltaTime >= playerMoveInterval)
			{
				// 플레이어 움직임 이벤트
				CheckCollision();

				// 여기서 실제로 playerPos가 움직인다
				PlayMoveSound();
				PlayerMoveEvent();

				SetPlayerPos();

				playerMoveEventTimer = currentTime;
			}
		}
	}
}
