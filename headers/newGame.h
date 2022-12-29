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