#pragma once


struct highscore {
	char name[100];
	int score;
};
void addHighscore(char name[100], int score, int highs);
void highscores(int highscores);