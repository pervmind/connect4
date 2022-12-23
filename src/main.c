#include <stdio.h>
#include "../headers/mainMenu.h"
#include "../headers/config.h"

int main()
{
	struct config config = getConfig();
	mainMenu();

	return 0;
}