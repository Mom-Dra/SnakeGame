#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdlib.h>
#include "screen.h"
#include "player.h"
#include "event.h"

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
// 1. 벽, 몸에 닿으면 게임 종료!!
// 2. 아이템을 먹으면 몸 길이 1 증가!
// 3. 아이템을 먹으면 이동 속도 증가

static int desiredFPS = 100;

int main()
{
	srand(time(NULL));

	ScreenInit();		

	clock_t lastTime = clock();
	int millisecondsPerFrame = 1000 / desiredFPS;

	oneEventTimer = lastTime;
	halfEventTimer = lastTime;

	while (1)
	{
		clock_t currentTime = clock();
		clock_t deltaTime = currentTime - lastTime;
		
		if (deltaTime >= millisecondsPerFrame)
		{
			InputKey();

			SetPlayerPos();

			ScreenClear();

			Render();

			ScreenFlipping();

			// 이벤트 1
			clock_t halfEventDeltaTime = currentTime - oneEventTimer;

			if (halfEventDeltaTime >= halfSecondInterval)
			{
				// 플레이어 움직임 이벤트
				CheckCollision();
				PlayerMoveEvent();

				oneEventTimer = currentTime;
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

	//Release();
	ScreenRelease();

	return 0;
}