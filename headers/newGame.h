#pragma once
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

void newGame();