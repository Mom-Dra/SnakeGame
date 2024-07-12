#define _CRT_SECURE_NO_WARNINGS
#define DEBUG
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "screen.h"
#include "player.h"
#include "event.h"
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
// 충돌 이벤트
// 
// 반대방향으로 이동 막는거 추가
// 
// 2. 벽, 몸에 닿으면 게임 종료!!
// 3. 아이템을 먹으면 이동 속도 증가
// 4. 초기화면 엔딩 아스키아트
// 5. 사운드

static int desiredFPS = 100; // --> GameManager로 옮기자

void Init();
void GameLoop();

int main()
{
	while (1)
	{
		DrawInitialScreen();

		BreakScreen();

		GameLoop();

		//BreakScreen();
	}
	
	//Release();
	ScreenRelease();

	return 0;
}

void Init()
{
	srand(time(NULL));
	
	ScreenInit();

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
	halfEventTimer = lastTime;

	while (gameOver)
	{
		clock_t currentTime = clock();
		clock_t deltaTime = currentTime - lastTime;
		
		if (deltaTime >= millisecondsPerFrame)
		{
			InputKey();

			ScreenClear();

			Render();

			ScreenFlipping();

			// 이벤트 1
			clock_t playerMoveEventDeltaTime = currentTime - playerMoveEventTimer;

			if (playerMoveEventDeltaTime >= playerMoveInterval)
			{
				// 플레이어 움직임 이벤트
				CheckCollision();

				// 여기서 실제로 playerPos가 움직인다
				PlayerMoveEvent();

				// 되겠네
				SetPlayerPos();

				playerMoveEventTimer = currentTime;
			}

			// 이벤트 2
			clock_t oneEventDeltaTime = currentTime - halfEventTimer;

			if (oneEventDeltaTime >= oneSecondInterval)
			{
				// 아이템 생성 이벤트
				GenerateItemEvent();

				halfEventTimer = currentTime;
			}

			lastTime = currentTime;
		}
	}
}
