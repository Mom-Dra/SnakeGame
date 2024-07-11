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

// �����ؾ� �� ��
// �浹 �̺�Ʈ
// 1. ��, ���� ������ ���� ����!!
// 2. �������� ������ �� ���� 1 ����!
// 3. �������� ������ �̵� �ӵ� ����

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

			// �̺�Ʈ 1
			clock_t halfEventDeltaTime = currentTime - oneEventTimer;

			if (halfEventDeltaTime >= halfSecondInterval)
			{
				// �÷��̾� ������ �̺�Ʈ
				CheckCollision();
				PlayerMoveEvent();

				oneEventTimer = currentTime;
			}

			// �̺�Ʈ 2
			clock_t oneEventDeltaTime = currentTime - halfEventTimer;

			if (oneEventDeltaTime >= oneSecondInterval)
			{
				// ������ ���� �̺�Ʈ
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