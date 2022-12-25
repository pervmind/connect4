#include<stdio.h>
#include "../headers/config.h"

int mainMenu(struct config config)
{
    double pth;
    double md = 0;
    printf("                                                CONNECT 4 \n");
    printf("                                    ************************************\n");
    printf("1 : New Game\n");
    printf("2 : Load Game\n");
    printf("3 : Highscores");
    while (1)
    {
        printf("\nPlease Select a path! : \n");
        scanf_s("%lf", &pth);
        if (pth == 3 || pth == 2 || pth == 1)
        {
            int p = pth;
            switch (p)
            {
            case (1):
                printf("\n***************\n");
                printf("\nPlease Select GAME MODE :");
                printf("\n1 : Player 1 V.S PC");
                printf("\n2 : Player 2 V.S Player 2");
                while (1)
                {
                    printf("\nSelect The MODE's Number : \n");
                    scanf_s("%lf", &md);
                    if (md == 1 || md == 2)
                        break;
                    printf("Please Select a Valid Mode !");
                }
                printf("Player 1 has RED color");
                if (md == 2)
                    printf("\nPlayer 2 has YELLOW color");
                break;
            case (2):
                printf("check2");
                break;
            case (3):
                printf("check3");
                break;

            }
            break;
        }
        else
            printf("Enter a Valid path");
    }
    return 0;
}