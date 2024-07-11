#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdlib.h>
#include "screen.h"
#include "player.h"
#include "event.h"

// INPUT
// �Է� �ޱ�
// 
// UPDATE
// �Է¿� ���� ���� ����
// �Է¿� ���� ���� ����!
// 
// RENDER
// ���


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
			// �÷��̾� ������ �̺�Ʈ
			PlayerMoveEvent();

			oneEventTimer = currentTime;
		}

		clock_t oneEventDeltaTime = currentTime - halfEventTimer;

		if(oneEventDeltaTime >= oneSecondInterval)
		{
			// ������ ���� �̺�Ʈ
			GenerateItemEvent();

			halfEventTimer = currentTime;
		}
	}

	//Release();
	ScreenRelease();

	return 0;
}