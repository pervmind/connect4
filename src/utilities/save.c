#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/newGame.h"

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
void save(struct cell grid, struct player player1, struct player player2, char turn, int mode) {
	FILE* fp = NULL;
	int choice = validateSlot();
	switch (choice) {
	case 1:
		fp = open("../../save/save1.bin", "wb");
		break;
	case 2:
		fp = open("../../save/save1.bin", "wb");
		break;
	case 3:
		fp = open("../../save/save1.bin", "wb");
		break;
	}
	if (fp == NULL) {
		printf("Error opening the file.. try again please!!\n");
		save(grid, player1, player2, turn, mode);
	}
	else {
		char content[25000];
		if (mode == 1) {
			content[0] = '1';
		}
		else {
			content[0] = '2';
		}
		content[1] = turn;
		content[2] = player1.color;
		content[3] = player1.moves;
		content[4] = player1.score;
		content[5] = player1.symbol;
		content[6] = player2.color;
		content[7] = player2.moves;

	}
}