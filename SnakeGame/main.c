#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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
// 1. �������� ������ �� ���� 1 ����!
// 2. ��, ���� ������ ���� ����!!
// 3. �������� ������ �̵� �ӵ� ����
// 4. �ʱ�ȭ��

static int desiredFPS = 100;

void Init();
void GameLoop();

int main()
{
	Init();

	while (1)
	{
		DrawInitialScreen();

		GameLoop();
	}
	
	//Release();
	ScreenRelease();

	return 0;
}

void Init()
{
	srand(time(NULL));
	
	ScreenInit();

	InitPlayer();
}

void GameLoop()
{
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

			ScreenClear();

			Render();

			ScreenFlipping();

			// �̺�Ʈ 1
			clock_t halfEventDeltaTime = currentTime - oneEventTimer;

			if (halfEventDeltaTime >= halfSecondInterval)
			{
				// �÷��̾� ������ �̺�Ʈ
				CheckCollision();

				// ���⼭ ������ playerPos�� �����δ�
				PlayerMoveEvent();

				// �ǰڳ�
				SetPlayerPos();

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
}