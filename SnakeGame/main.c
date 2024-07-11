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

			CalcPlayer();

			ScreenClear();

			Render();

			ScreenFlipping();
			  
			lastTime = currentTime;
		}

		clock_t halfEventDeltaTime = currentTime - oneEventTimer;

		if (halfEventDeltaTime >= halfSecondInterval)
		{
			// 플레이어 움직임 이벤트
			PlayerMoveEvent();

			oneEventTimer = currentTime;
		}

		clock_t oneEventDeltaTime = currentTime - halfEventTimer;

		if(oneEventDeltaTime >= oneSecondInterval)
		{
			// 아이템 생성 이벤트
			GenerateItemEvent();

			halfEventTimer = currentTime;
		}
	}

	//Release();
	ScreenRelease();

	return 0;
}