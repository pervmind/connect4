#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/config.h"
#include "../headers/newGame.h"

int validMode() {
    char input [256];
    printf("\nPlease Select a path : \n");
    fgets(input, 255, stdin);
    int output = atoi(input);
    if (output == 0 || output > 3) {
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
    printf("3 : Highscores");
    
    //path selection
    int p = validMode(); 
    switch (p)
    {
    case (1):
        newGame(config);
        break;
    case (2):
          printf("check2"); // <<<<<<<<<< we need save file here to load a previous game
          break;
     case (3):
          printf("check3"); // <<<<<<<<<< we need save file here to view highscores
          break;
    }
}
