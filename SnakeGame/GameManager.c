#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "GameManager.h"
#include "screen.h"

static char maxScoreFileName[] = "MaxScore.txt";

static int gameOver = 0;
static int score = 0;
static int maxScore = 0;
static int itemScore = 10;
static void(*Subject) (int, int);

void InitGameManager()
{
	gameOver = 0;
	itemScore = 10;
	SetScore(0);
}

void GameOver()
{
	gameOver = 1;

	WriteMaxScore();
}

int IsGameOver()
{
	return gameOver;
}

void IncreaseScore(int _score)
{
	if (gameOver == 1) return;
	SetScore(score + _score);
}

void SetScore(int _score)
{
	score = _score;

	if (score > maxScore)
	{
		maxScore = score;
	}

	Notify(score, maxScore);
}

void RegistObserver(void (*func) (int, int))
{
	Subject = func;
}

void Notify(int _score, int _maxScore)
{
	Subject(_score, _maxScore);
}

int GetScore()
{
	return score;
}

void GenerateMaxScoreFile()
{
	FILE* fp;

	fp = fopen(maxScoreFileName, "w");

	if (fp == NULL)
	{
		fprintf(stderr, "Failed to Generate file '%s'.\n", maxScoreFileName);
		exit(1);
	}

	fclose(fp);
}

void ReadMaxScore()
{
	FILE* fp;
	int readVal;
	
	fp = fopen(maxScoreFileName, "r");

	if (fp == NULL)
	{
		// 파일 생성
		GenerateMaxScoreFile();
		maxScore = 0;
		return;
	}

	fscanf(fp, "%d", &readVal);
	maxScore = readVal;

	fclose(fp);
}

void WriteMaxScore()
{
	FILE* fp;
	
	fp = fopen(maxScoreFileName, "w");

	if (fp == NULL)
	{
		GenerateMaxScoreFile();
	}

	fprintf(fp, "%d", maxScore);

	fclose(fp);
}

void IncreaseItemScore()
{
	itemScore += 10;
}

int GetItemScore()
{
	return itemScore;
}