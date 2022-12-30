#pragma once
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KWHT  "\x1B[37m"
#define KMAG  "\x1B[35m"
struct cell {
	char player;
	char value;
	char color;
};

struct player {
	char no;
	int moves;
	int score;
	char symbol;
	char color;
};

struct move {
	char playerNo;
	int postScore;
	int columnNo;
};

void newGame();
void printGrid(struct cell grid[100][100], int height, int width, struct player player1, struct player player2, time_t initialTime);
void playermove(struct cell grid[100][100], int height, int width, struct player player1, struct player player2, int colsVolume[100], struct move moves[10000], struct move redos[10000], int movesIndex, time_t initialTime, int plays, char mode, int redosIndex, int undoTimes);
