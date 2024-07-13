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
// 입력 받기
// 
// UPDATE
// 입력에 따른 로직 세팅
// 입력에 따른 버퍼 세팅!
// 
// RENDER
// 출력

// 구현해야 할 것
// 
// 사운드
// 점수
// 최고기록 저장!
// 엔딩 씬에 점수 출력해주기

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

			// 이벤트 1
			clock_t playerMoveEventDeltaTime = currentTime - playerMoveEventTimer;

			if (playerMoveEventDeltaTime >= playerMoveInterval)
			{
				// 플레이어 움직임 이벤트
				CheckCollision();

				// 여기서 실제로 playerPos가 움직인다
				PlayerMoveEvent();

				SetPlayerPos();

				playerMoveEventTimer = currentTime;
			}

			// 이벤트 2
			clock_t itemGenerateEventDeltaTime = currentTime - itemGenerateEventTimer;

			if (itemGenerateEventDeltaTime >= itemGenerateInterval)
			{
				// 아이템 생성 이벤트
				GenerateBlockEvent(BLOCK_ITEM);

				itemGenerateEventTimer = currentTime;
			}

			// 이벤트 3
			clock_t wallGenerateEventDeltaTime = currentTime - wallGenerateEventTimer;

			if (wallGenerateEventDeltaTime >= wallGenerateInterval)
			{
				// 벽 생성 이벤트
				GenerateBlockEvent(BLOCK_WALL);
				wallGenerateEventTimer = currentTime;
			}
		}
	}
}
