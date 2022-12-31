#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/config.h"
#include "../headers/newGame.h"
#include "../headers/loadGame.h"
#include "../headers/highscores.h"

int validMode() {
    char input [256];
    printf("\nPlease Select a path : \n");
    fgets(input, 255, stdin);
    int output = atoi(input);
    if (output == 0 || output > 4) {
        printf("invalid input!!\n");
        return validMode();
    }
    else return output;
}

void mainMenu(struct config config)
{

    printf("                                                CONNECT 4 \n");
    printf("                                    ************************************\n");
    printf("1 : New Game\n");
    printf("2 : Load Game\n");
    printf("3 : Highscores\n");
    printf("4 : Exit\n");
    
    //path selection
    int p = validMode(); 
    switch (p)
    {
    case (1):
        newGame(config);
        break;
    case (2):
        loadGame();
        break;
     case (3):
         highscores(config.highscores);
         break;
     case (4):
         printf("Thank you for playing..");
         exit(0);
    }
}
