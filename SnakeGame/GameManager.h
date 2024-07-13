#pragma once

void InitGameManager();
void GameOver();
int IsGameOver();
void IncreaseScore(int score);
void SetScore(int _score);
void RegistObserver(void (*func) (int, int));
void Notify(int score, int maxScore);
int GetScore();
void GenerateMaxScoreFile();
void ReadMaxScore();
void WriteMaxScore();
void IncreaseItemScore();
int GetItemScore();