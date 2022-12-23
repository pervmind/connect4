#include <stdio.h>
void mainMenu() {
	double md = 0;
	printf("						connect 4");
	printf("\n				****************************************\n");
	printf("Please Select GAME MODE :");
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
	printf("Player 1 has BLUE color");
	if (md == 2)
		printf("\nPlayer 2 has RED color");
}
