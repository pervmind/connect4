#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/config.h"
#include "../headers/newGame.h"

int validGameMode() {
    char input[256];
    printf("\nSelect The MODE's Number : \n");
    fgets(input, 255, stdin);
    int output = atoi(input);
    if (output == 1 || output == 2) {
        return output;
    }
    else {
        printf("Invalid input!!!\n");
        return validGameMode();
    }
}

void initiateGame(struct cell grid[100][100], int height, int width) {
    int colsVolume[100];
    for (int i = 0; i < width; i++) {
        colsVolume[i] = 0;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j].player = 0;
            grid[i][j].value = ' ';
        }
    }
}

void printgrid(struct cell grid[100][100], int height, int width) {

}

void player1Move(struct cell grid[100][100], int height, int width) {

}

void newGame(struct config config) {
    char game_colors[] = { 'R','O','Y','G' }; //all colors possible for players' disks
    
    printf("\n***************\n");
    printf("\nPlease Select GAME MODE :");
    printf("\n1 : Player 1 V.S PC");
    printf("\n2 : Player 2 V.S Player 2");
    int md = validGameMode();
    int C1, C2; // player 1 , 2 disks colors
    time_t t;
    srand((unsigned)time(&t)); // generating random numbers using time
    C1 = rand() % 4; //generating random in range 0 >> 4
    printf("Player 1 has %c color", game_colors[C1]);
    if (md == 2) // check for mode 2
    {
        while (1)
        {
            C2 = rand() % 4; //generating random in range 0 >> 4
            if (C1 != C2) // check that every player has his independent color
                break;
        }
        printf("\nPlayer 2 has %c color", game_colors[C2]);
    }
    struct player player1 = { .no = 1, .moves = 0, .symbol = 'X', .score = 0 }; // <--- add color here
    struct player player2 = { .no = 2, .moves = 0, .symbol = 'O', .score = 0 }; // <--- add color here
    int height = config.hieght;
    int width = config.width;
    struct cell grid[100][100];
    initiateGame(grid, height, width);
    printgrid(grid, height, width);
    player1Move(grid, height, width);
}
