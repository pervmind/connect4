#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/config.h"
#include "../headers/newGame.h"
#include "../headers/save.h"



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
    case'M':
        printf("%s", KMAG);
        break;
    default:
        break;

    }
}
int startVal(int start) {
    if (start > 0)
        return start;
    else
        return 0;
}
int endVal(int end , int limit) {
    if (end < limit)
        return end;
    else
        return limit;
}
int ScoreCalc(struct player player, int columnNo, struct cell grid[100][100],int index, int hight, int width, int colsVolume[100]) {
    int NewScore = player.score;
    //row scorecheck
    int count = 0;
    int start = columnNo - 3 ;
    int end   = columnNo + 3 ;
    start = startVal(start);
    end = endVal(end, width);
    int vol = colsVolume[columnNo];
    for (int i = start; i <= end; i++) {
        if (grid[hight - vol][i].value == player.symbol)
            count++;
        else
            count = 0;
        if (count >= 4)
            NewScore++;
    }
    //col scorecheck
    count = 0;
    start = hight - colsVolume[columnNo] - 3;
    end   = hight - colsVolume[columnNo] + 3;
    start = startVal(start);
    end = endVal(end, hight);
    for (int i = start; i <= end; i++) {
         if (grid[i][columnNo].value == player.symbol)
             count++;
         else
             count = 0;
         if (count >= 4)
             NewScore++;
    }
    //first diagonalcheck '/'
    int colstart = columnNo - 3;
    int rowstart = hight - colsVolume[columnNo] + 3;
    int colend   = columnNo + 3;
    int rowend   = hight - colsVolume[columnNo] - 3;
    int j = rowstart;
    for (int i = colstart; i <= colend; i++) {
        if (grid[j][i].value == player.symbol)
            count++;
        else
            count = 0;
        if (count >= 4)
            NewScore++;
        j--;
    }
    //second diagonalcheck '\'
     colstart = columnNo - 3;
     rowstart = hight - colsVolume[columnNo] - 3;
     colend = columnNo + 3;
     rowend = hight - colsVolume[columnNo] + 3;
     j = rowstart;
    for (int i = colstart; i <= colend; i++) {
        if (grid[j][i].value == player.symbol)
            count++;
        else
            count = 0;
        if (count >= 4)
            NewScore++;
        j++;
    }
    return NewScore;
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
    Color('M');
    printf("Time: %d:%d\n", minutes, seconds);
    Color('W');
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
    printf("Enter a column number (type q to save and exit, u to undo, r to redo): ");
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
        else if (str[0] == 'u') {
            return -2;
        }
        else if (str[0] == 'r') {
            return -3;
        }
        else {
            printf("invalid input!!\n");
            return validateMove(width);
        }
    }
    
}

void playermove(struct cell grid[100][100], int height, int width, struct player player1, struct player player2, int colsVolume[100], struct move moves[10000], struct move redos[10000], int movesIndex, time_t initialTime, int plays, char mode, int redosIndex, int undoTimes){
    if (plays % 2 == 0) {
        printf("\nPlayer 1's turn..\n");
    }
    else {
        printf("\nPlayer 2's turn..\n");
    }
    int input = validateMove(width);
    if (input == -1) {
        printf("save game\n"); 
        char turn;
        if (plays % 2 == 0) {
            turn = 1;
        }
        else {
            turn = 2;
        }
        save(grid, player1, player2, turn, mode, width, height);
    }
    else if (input == -2) {
        printf("undo");
        if (plays % 2 != 0 && movesIndex > 0) {
            redos[redosIndex].postScore = player1.score; //initiating for REDO
            plays--;
            movesIndex--;
            //update score
            player1.score = moves[movesIndex].postScore;
            //moves++
                //if (player1.moves > 0)
            player1.moves--;
            //update grid
            int lastcol = moves[movesIndex].columnNo;
            redos[redosIndex].columnNo = lastcol; //initiating for REDO
            grid[height - colsVolume[lastcol]][lastcol].value = ' ';
            grid[height - colsVolume[lastcol]][lastcol].player = 0;
            //update columnvolume
                //if (colsVolume > 0)
            colsVolume[lastcol]--;
            undoTimes++;
            redosIndex++;
            //continue

        }
        else if (plays % 2 == 0 && movesIndex > 0) {
            redos[redosIndex].postScore = player2.score; //initiating for REDO
            plays--;
            movesIndex--;
            //update score
            player2.score = moves[movesIndex].postScore;
            //moves++
                //if (player2.moves > 0)
            player2.moves--;
            //update grid
            int lastcol = moves[movesIndex].columnNo;
            redos[redosIndex].columnNo = lastcol; //initiating for REDO
            grid[height - colsVolume[lastcol]][lastcol].value = ' ';
            grid[height - colsVolume[lastcol]][lastcol].player = 0;
            //update columnvolume
                //if (colsVolume > 0)
            colsVolume[lastcol]--;
            undoTimes++;
            redosIndex++;
            //continue
        }
        else {
            printf("\n-------------------------------------------");
            printf("\n| You cannot undo .. No Undos saved      ! |\n");
            printf("-------------------------------------------");
        }
        printGrid(grid, height, width, player1, player2, initialTime);
        playermove(grid, height, width, player1, player2, colsVolume, moves, redos, movesIndex, initialTime, plays, mode, redosIndex, undoTimes);
    }
    else if (input == -3) {
        printf("redo");
        if (plays % 2 == 0 && undoTimes > 0){
            plays++;
            int lastcol = redos[redosIndex -1].columnNo;
            moves[movesIndex].columnNo = lastcol;
            moves[movesIndex].playerNo = 1;
            moves[movesIndex].postScore = player1.score;
            player1.score = redos[redosIndex - 1].postScore;
            grid[height - colsVolume[lastcol] - 1][lastcol].value = player1.symbol;
            grid[height - colsVolume[lastcol] - 1][lastcol].player = 1;
            grid[height - colsVolume[lastcol] - 1][lastcol].color = player1.color;
            player1.moves++;
            colsVolume[lastcol]++;
            undoTimes--;
            redosIndex--;
            movesIndex++;
        }
        else if (plays % 2 != 0 && undoTimes > 0) {
            plays++;
            int lastcol = redos[redosIndex - 1].columnNo;
            moves[movesIndex].columnNo = lastcol;
            moves[movesIndex].playerNo = 2;
            moves[movesIndex].postScore = player2.score;
            player2.score = redos[redosIndex - 1].postScore;
            grid[height - colsVolume[lastcol] - 1][lastcol].value = player2.symbol;
            grid[height - colsVolume[lastcol] - 1][lastcol].player = 2;
            grid[height - colsVolume[lastcol] - 1][lastcol].color = player2.color;
            player2.moves++;
            colsVolume[lastcol]++;
            undoTimes--;
            redosIndex--;
            movesIndex++;
        }
        else {
            printf("\n-----------------------------------------------");
            printf("\n| You cannot Redo, you haven't not undoed enough ! |\n");
            printf("-----------------------------------------------");
            
        }
        printGrid(grid, height, width, player1, player2, initialTime);
        playermove(grid, height, width, player1, player2, colsVolume, moves, redos, movesIndex, initialTime, plays, mode, redosIndex, undoTimes);
        
    }
    else {
        if (colsVolume[input] >= height) {
            printf("Column is full .. please choose another column\n");
            playermove(grid, height, width, player1, player2, colsVolume, moves, redos, movesIndex, initialTime, plays, mode, redosIndex, undoTimes);
        }
        else {
            undoTimes = 0;
            redosIndex = 0;
            if (plays % 2 == 0) {
                moves[movesIndex].playerNo = 1;
                moves[movesIndex].postScore = player1.score;
                moves[movesIndex].columnNo = input;
                movesIndex++;
                grid[height - colsVolume[input] - 1][input].player = 1;
                grid[height - colsVolume[input] - 1][input].value = player1.symbol;
                grid[height - colsVolume[input] - 1][input].color = player1.color;
                colsVolume[input]++;
                player1.moves = player1.moves + 1;
                if (player1.moves >= 4) {
                    player1.score = ScoreCalc(player1, input, grid, movesIndex - 1, height, width, colsVolume);
                }
            }
            else {
                moves[movesIndex].playerNo = 2;
                moves[movesIndex].postScore = player2.score;
                moves[movesIndex].columnNo = input;
                movesIndex++;
                grid[height - colsVolume[input] - 1][input].player = 2;
                grid[height - colsVolume[input] - 1][input].value = player2.symbol;
                grid[height - colsVolume[input] - 1][input].color = player2.color;
                colsVolume[input]++;
                player2.moves = player2.moves + 1;
                if (player2.moves >= 4) {
                    player2.score = ScoreCalc(player2, input, grid, movesIndex - 1, height, width, colsVolume);
                }
            }
            plays++;
            printGrid(grid, height, width, player1, player2, initialTime);
            //check for game end
            playermove(grid, height, width, player1, player2, colsVolume, moves, redos, movesIndex, initialTime, plays, mode, redosIndex, undoTimes);
        }
    }
    
}
void newGame(struct config config) {
    
    char game_colors[] = { 'R','B','Y','G' }; //all colors possible for players' disks
    printf("\n***************\n");
    printf("\nPlease Select GAME MODE :");
    printf("\n1 : Player 1 V.S PC");
    printf("\n2 : Player 2 V.S Player 2");
    char md = validGameMode();
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
    struct move redos[10000];
    int movesIndex = 0;
    int redosIndex = 0;
    int undoTimes = 0;
    initiateGame(grid, height, width, colsVolume);
    printGrid(grid, height, width, player1, player2, initialTime);
    int plays = 0;
    /*while (gameEnd) {
        if (plays % 2 == 0) {
            player1move(grid, height, width, player1, player2, colsVolume, moves, movesIndex);
            player1.moves++;
            if (player1.moves >= 4)
            player1.score = ScoreCalc(player1, moves, grid, movesIndex, height, width, colsVolume);
            printGrid(grid, height, width, player1, player2, initialTime);
            plays++;
            // check for game end
            if (player1.moves + player2.moves == height * width) {
                if (player1.score != player2.score) {
                    printf("\n********************");
                    printf("\nTHE GMAE HAS ENDED\n");
                    printf("The Winner is player ");
                    if (player1.score > player2.score)
                        printf("1\n");
                    else
                        printf("2\n");
                }
                else
                    printf("The Game Ended With A Tie");
                
            }

        }
        else {
            player2move(grid, height, width, player1, player2, colsVolume, moves, movesIndex);
            player2.moves++;
            if(player2.moves >= 4)
            player2.score = ScoreCalc(player2, moves, grid, movesIndex, height, width, colsVolume);
            printGrid(grid, height, width, player1, player2, initialTime);
            plays++;
            // check for game end
            if (player1.moves + player2.moves == height * width) {
                if (player1.score != player2.score) {
                    printf("\n********************");
                    printf("\nTHE GMAE HAS ENDED\n");
                    printf("The Winner is player ");
                    if (player1.score > player2.score)
                        printf("1\n");
                    else
                        printf("2\n");
                }
                else
                    printf("The Game Ended With A Tie");
            
            }
        }

    }*/
    playermove(grid, height, width, player1, player2, colsVolume, moves, redos,movesIndex, initialTime, plays, md, redosIndex, undoTimes);
     
}
