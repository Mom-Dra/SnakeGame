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
// 
// �ݴ�������� �̵� ���°� �߰�
// 
// 2. ��, ���� ������ ���� ����!!
// 3. �������� ������ �̵� �ӵ� ����
// 4. �ʱ�ȭ�� ���� �ƽ�Ű��Ʈ
// 5. ����

static int desiredFPS = 100; // --> GameManager�� �ű���

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

			// �̺�Ʈ 1
			clock_t playerMoveEventDeltaTime = currentTime - playerMoveEventTimer;

			if (playerMoveEventDeltaTime >= playerMoveInterval)
			{
				// �÷��̾� ������ �̺�Ʈ
				CheckCollision();

				// ���⼭ ������ playerPos�� �����δ�
				PlayerMoveEvent();

				// �ǰڳ�
				SetPlayerPos();

				playerMoveEventTimer = currentTime;
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
