#include <stdio.h>
#include <Windows.h>
#include "GameManager.h"
#include "screen.h"

gameOver = 1;

void InitGameManager()
{
	gameOver = 1;
}

void GameOver()
{
	gameOver = 0;
}