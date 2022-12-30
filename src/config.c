#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/config.h"

struct config getConfig() {
	struct config config;
	FILE *fp;
	char path[256], content[2048];
	int failTimes = 0, def = 0;
	printf("Enter path for config xml file : \n");
	while (1) {
		gets(path);
		fp = fopen(path, "r");
		if (fp != NULL || failTimes >= 3) {
			if (failTimes >= 3)def = 1;
			break;
		}
		failTimes++;
		printf("File not found!! Enter a valid file path: ");

	}
	if (def == 1) {
		config.hieght = 9;
		config.width = 7;
		config.highscores = 10;
		//printf("%d %d %d", config.hieght, config.width, config.highscores);
	}
	else {
		char nospace[2048];
		int i = 0;
		while (!feof(fp)) {
			fgets(content, 2047, fp);
			int j = 0;
			while (content[j] != '\0') {
				if (!isspace(content[j])) {
					nospace[i++] = content[j++];
				}
				else j++;
			}
		}
		nospace[i] = '\0';
		//printf("%s", nospace);
		fclose(fp);

		char* height1 = strstr(nospace, "<Hieght>");
		char* height2 = strstr(nospace, "</Hieght>");
		char* width1 = strstr(nospace, "<Width>");
		char* width2 = strstr(nospace, "</Width>");
		char* highscore1 = strstr(nospace, "<Highscores>");
		char* highscore2 = strstr(nospace, "</Highscores>");
		height1 += 8;
		width1 += 7;
		highscore1 += 12;
		char heightValueStr[100];
		char widthValueStr[100];
		char highscoreValueStr[100];
		int h = 0, w = 0, s = 0;
		for (height1; height1 < height2; height1++) {
			heightValueStr[h++] = *height1;
		}
		for (width1; width1 < width2; width1++) {
			widthValueStr[w++] = *width1;
		}
		for (highscore1; highscore1 < highscore2; highscore1++) {
			highscoreValueStr[s++] = *highscore1;
		}
		heightValueStr[h] = '\0';
		widthValueStr[w] = '\0';
		highscoreValueStr[s] = '\0';

		config.hieght = atoi(heightValueStr);
		config.width = atoi(widthValueStr);
		config.highscores = atoi(highscoreValueStr);
	}

	if ((config.hieght == 0) || (config.width == 0) || (config.highscores == 0)) {
		printf("Corrupted File!! Missing Values!!");
		return getConfig();
	}
	else {
		return config;
	}


}