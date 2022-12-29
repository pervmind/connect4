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

void coloredChar(char color, char character ) {
    Color(color); //printing color
    printf("%c", character);
    Color('W'); //reseting color
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
            if (grid[i][j].player == 0) {
                printf("%c|", grid[i][j].value);
            }
            else {
                
                coloredChar(grid[i][j].color, grid[i][j].value);
                printf("|");
            }
        }
        printf("\n");
        for (int k = 0; k < 2 * width; k++) {
            printf("-");
        }
        printf("\n");
    }
    printf(" ");
    for (int i = 0; i < width; i++) {
        printf("%d ", i+1);
    }
}
int validateMove(int width) {
    printf("Enter a column number (type q to save and exit): ");
    char str[100];
    fgets(str, 99, stdin);
    int input = atoi(str);
    if (input >= 1 && input <= width) {
        return input-1;
    }
    else {
        if (str[0] == 'q') {
            return -1;
        }
        else {
            printf("invalid input!!\n");
            return validateMove(width);
        }
    }
    
}

void player1move(struct cell grid[100][100], int height, int width, struct player player1, struct player player2, int colsVolume[100], struct move moves[10000], int movesIndex) {
    printf("\nPlayer 1's turn..\n");
    int input = validateMove(width);
    if (input == -1) {
        printf("save game\n");
    }
    else {
        if (colsVolume[input] >= height) {
            printf("Column is full .. please choose another column\n");
            player1move(grid, height, width, player1, player2, colsVolume, moves, movesIndex);
        }
        else {
            moves[movesIndex].columnNo = input;
            moves[movesIndex].playerNo = 1;
            moves[movesIndex].postScore = player1.score;
            movesIndex++;
            grid[height - colsVolume[input] - 1][input].player = 1;
            grid[height - colsVolume[input] - 1][input].value = player1.symbol;
            grid[height - colsVolume[input] - 1][input].color = player1.color;
            colsVolume[input]++;
            // calculate score

        }
    }
    
}

void player2move(struct cell grid[100][100], int height, int width, struct player player1, struct player player2, int colsVolume[100], struct move moves[10000], int movesIndex) {
    printf("\nPlayer 2's turn..\n");
    int input = validateMove(width);
    if (input == -1) {
        printf("save game\n");
    }
    else {
        if (colsVolume[input] >= height) {
            printf("Column is full .. please choose another column\n");
            player2move(grid, height, width, player1, player2, colsVolume, moves, movesIndex);
        }
        else {
            moves[movesIndex].columnNo = input;
            moves[movesIndex].playerNo = 2;
            moves[movesIndex].postScore = player2.score;
            grid[height - colsVolume[input] - 1][input].player = 2;
            grid[height - colsVolume[input] - 1][input].value = player2.symbol;
            grid[height - colsVolume[input] - 1][input].color = player2.color;
            colsVolume[input]++;
            // calculate score
            
        }
    }

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
    struct move moves[10000];
    int movesIndex = 0;
    initiateGame(grid, height, width, colsVolume);
    printGrid(grid, height, width, player1, player2, initialTime);
    int plays = 0;
    int gameEnd = 1;
    while (gameEnd) {
        if (plays % 2 == 0) {
            player1move(grid, height, width, player1, player2, colsVolume, moves, movesIndex);
            printGrid(grid, height, width, player1, player2, initialTime);
            plays++;
            // check for game end
        }
        else {
            player2move(grid, height, width, player1, player2, colsVolume, moves, movesIndex);
            printGrid(grid, height, width, player1, player2, initialTime);
            plays++;
            // check for game end
        }

    }
    
}
