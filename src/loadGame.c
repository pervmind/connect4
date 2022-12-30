#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/config.h"
#include "../headers/newGame.h"
char validateLoad() {
	printf("Please select save slot\n1.save1\n2.save2\n3.save3\n");
	int choice;
	scanf("%d", &choice);
	if (choice >= 1 && choice <= 3) {
		return choice;
	}
	else {
		printf("Invalid input!!\n");
		return validateLoad();
	}
}
void loadGame() {

	FILE *fp = NULL;
	
	int flag = 1;
	while (flag) {
		char choice = validateLoad();
		if (choice == 1) {
			fp = fopen("save1.bin", "rb");
		}
		else if (choice == 2) {
			fp = fopen("save2.bin", "rb");
		}
		else {
			fp = fopen("save3.bin", "rb");
		}
		if (fp == NULL) {
			printf("Save slot is empty .. choose another slot!!\n");
			
		}
		else {
			flag = 0;
		}
	}
	
	char info[10021];
	fread(info, sizeof(info), 1, fp);
	fclose(fp);
	char mode = info[0];
	char turn = info[1];
	struct player player1 = { .color = info[2], .moves = info[3], .no = 1, .score = info[4], .symbol = info[5] };
	struct player player2 = { .color = info[6], .moves = info[7], .no = 2, .score = info[8], .symbol = info[9] };
	int width = (int)info[10];
	int height = (int)info[11];
	int index = 12;
	struct cell grid[100][100];
	int colsVolume[100];
	for (int i = 0; i < width; i++) {
		colsVolume[i] = 0;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j].player = info[index];
			if (info[index] == 1) {
				grid[i][j].color = player1.color;
				grid[i][j].value = player1.symbol;
				colsVolume[j] += 1;
			}
			else if (info[index] == 2) {
				grid[i][j].color = player2.color;
				grid[i][j].value = player2.symbol;
				colsVolume[j] += 1;
			}
			else {
				grid[i][j].value = ' ';
			}
			index++;
		}
	}
	time_t initialTime;
	time(&initialTime);
	struct move moves[10000];
	struct move redos[10000];
	int movesIndex = 0;
	int redosIndex = 0;
	int undoTimes = 0;
	printGrid(grid, height, width, player1, player2, initialTime);
	int plays = 0;
	if (turn == 2) {
		plays = 1;
	}
	playermove(grid, height, width, player1, player2, colsVolume, moves, redos,movesIndex, initialTime, plays, mode, redosIndex, undoTimes);
}