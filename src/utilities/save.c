#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/newGame.h"
#include "../../headers/mainMenu.h"
#include "../../headers/config.h"


int validateSlot() {
	printf("Choose saving slot !! \n1.save1\n2.save2\n3.save3\n");
	int choice;
	scanf_s("%d", &choice);
	if (choice >= 1 && choice <= 3) {
		return choice;
	}
	else {
		printf("Invalid input!!!!\n");
		return validateSlot();
	}

}
void save(struct cell grid[100][100], struct player player1, struct player player2, char turn, int mode, int width, int height, int highscores) {
	FILE* fp;
	int choice = validateSlot();
	if (choice == 1) {
		fp = fopen("save1.bin", "wb");
	}
	else if (choice == 2) {
		fp = fopen("save2.bin", "wb");
	} 
	else 
	{
		fp = fopen("save3.bin", "wb");
	}
	
	char content[10020];
	content[0] = mode;
	content[1] = turn;
	content[2] = player1.color;
	content[3] = player1.moves;
	content[4] = player1.score;
	content[5] = player1.symbol;
	content[6] = player2.color;
	content[7] = player2.moves;
	content[8] = player2.score;
	content[9] = player2.symbol;
	content[10] = width;
	content[11] = height;
	content[12] = highscores;
	int index = 13;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			content[index++] = grid[i][j].player;
		}
	}
	content[index] = '\0';
	fwrite(content, sizeof(content), 1, fp);
	fclose(fp);
	printf("Progress saved !! \nReturning to Main Menu.. \n");
	mainMenu(getConfig());
}