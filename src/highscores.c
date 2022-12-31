#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/highscores.h"
#include "../headers/mainMenu.h"
#include "../headers/config.h"

void addHighscore(char name[100], int score, int highs) {
	FILE* fp;
	fp = fopen("highscores.txt", "a");
	fprintf(fp, "%s %d\n", name, score);
	fclose(fp);
	highscores(highs);
}
void menuOrExit() {
	int selection;
	printf("Do you want to exit or go to main menu?!\n1.main menu\n2.exit\n");
	scanf("%d", &selection);
	if (selection == 1) {
		mainMenu(getConfig());
	}
	else if (selection == 2) {
		printf("Thank you for playing..");
		exit(0);
	}
	else {
		menuOrExit();
	}
}
void highscores(int highscores) {
	FILE* fp;
	fp = fopen("highscores.txt", "r");
	struct highscore highscoresArr[100];
	int index = 0;
	if (fp == NULL) {
		printf("No highscores to display\n");
	}
	else {
		int end = 0;
		while (end == 0) {
			int check = fscanf(fp, "%s %d", highscoresArr[index].name, &highscoresArr[index].score);
			//printf("%s %d", highscoresArr[index].name, highscoresArr[index].score);
			if (check <= 0) {
				end = 1;
			}
			else {
				index++;
			}
		}
		for (int i = 0; i < index - 1; i++) {
			for (int j = 0; j < index - i - 1; j++) {
				if (highscoresArr[j].score < highscoresArr[j + 1].score) {
					struct highscore temp = highscoresArr[j];
					highscoresArr[j] = highscoresArr[j + 1];
					highscoresArr[j + 1] = temp;
				}
			}
		}
		printf("Highscores: \n");
		for (int i = 0; i < index && i < highscores; i++) {
			printf("%d. %s %d\n", i + 1, highscoresArr[i].name, highscoresArr[i].score);
		}

	}
	menuOrExit();
}