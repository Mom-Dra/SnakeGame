#include <stdio.h>
#include "GameManager.h"
#include "screen.h"

gameOver = 1;

void GameOver()
{
	gameOver = 0;
	ScreenRelease();
}