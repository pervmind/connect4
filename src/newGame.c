#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/config.h"
#include "../headers/newGame.h"
void Color(char color) {
    switch (color)
    {
    case'R':
        printf("%s", KRED);
        break;
    case'Y':
        printf("%s", KYEL);
        break;
    case'B':
        printf("%s", KBLU);
        break;
    case'G':
        printf("%s", KGRN);
        break;
    case'W':
        printf("%s", KWHT);
        break;
    default:
        break;

    }
}
void scoreCalc(struct cell)
{
    int rowCheck()
    {

    }
    int colCheck()
    {

    }
    int diagCheck()
    {

    }
    int newScore = 0;
    
}
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

void initiateGame(struct cell grid[100][100], int height, int width, int colsVolume[100]) {
    
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

void printGrid(struct cell grid[100][100], int height, int width, struct player player1, struct player player2, time_t initialTime){
    printf("\nPlayer1(score: %d, moves: %d)\nPlayer2(score: %d, moves: %d)\n", player1.score, player1.moves, player2.score, player2.moves);
    time_t currentTime;
    time(&currentTime);
    long int timer = currentTime - initialTime;
    int seconds = timer % 60;
    int minutes = timer / 60;
    printf("Time: %d:%d\n", minutes, seconds);
    for (int i = 0; i < height; i++) {
        printf("|");
        for (int j = 0; j < width; j++) {
            printf("%c|", grid[i][j].value);
        }
        printf("\n");
        for (int k = 0; k < 2 * width; k++) {
            printf("-");
        }
        printf("\n");
    }
    printf(" ");
    for (int i = 0; i < width; i++) {
        printf("%d ", i);
    }
}

void player1move(struct cell grid[100][100], int height, int width, struct player player1) {
    printf("Player 1's turn.. Enter column number!: ");
}

void newGame(struct config config) {
    char game_colors[] = { 'R','B','Y','G' }; //all colors possible for players' disks
    
    printf("\n***************\n");
    printf("\nPlease Select GAME MODE :");
    printf("\n1 : Player 1 V.S PC");
    printf("\n2 : Player 2 V.S Player 2");
    int md = validGameMode();
    int C1, C2; // player 1 , 2 disks colors
    time_t t;
    srand((unsigned)time(&t)); // generating random numbers using time
    C1 = rand() % 4; //generating random in range 0 >> 4
    printf("Player 1 has "); 
    Color(game_colors[C1]); //printing color
    printf("%c Color", game_colors[C1]);
    Color('W'); //reseting color

    while (1)
    {
        C2 = rand() % 4; //generating random in range 0 >> 4
        if (C1 != C2) // check that every player has his independent color
            break;
    }
    if (md == 2) // check for mode 2
    {
        printf("\nPlayer 2 has ");
        Color(game_colors[C2]); //printing color
        printf("%c Color", game_colors[C2]);
        Color('W'); //reseting color
    }
    struct player player1 = { .no = 1, .moves = 0, .symbol = 'X', .score = 0 , .color = game_colors[C1]}; // <---  i added color here
    struct player player2 = { .no = 2, .moves = 0, .symbol = 'O', .score = 0 , .color = game_colors[C2]}; // <---  i added color here
    int height = config.hieght;
    int width = config.width;
    struct cell grid[100][100];
    time_t initialTime;
    time(&initialTime);
    int colsVolume[100];
    initiateGame(grid, height, width, colsVolume);
    printGrid(grid, height, width, player1, player2, initialTime);

}
