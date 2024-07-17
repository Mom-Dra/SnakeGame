#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void PlayGameStart()
{
	PlaySound(TEXT("GameStart.wav"), NULL, SND_ASYNC);
}

void PlayItemEatSound()
{
	PlaySound(TEXT("PowerUp.wav"), NULL, SND_ASYNC);
}

void PlayMoveSound()
{
	PlaySound(TEXT("Move.wav"), NULL, SND_ASYNC);
}

void PlayGameOverSound()
{
	PlaySound(TEXT("GameOver.wav"), NULL, SND_ASYNC);
}