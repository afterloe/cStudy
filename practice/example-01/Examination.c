#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Examination.h"

#define QUEST_LEN 15
#define MAX_NUM   100

extern int getNum();
extern char* getSymbol();

const char symbol[4][4] = {"+", "-", "*", "/"};
#define QUEST_FORMAT "%d\t%s\t%d\t=\t"

char* getQuestions() {
	char* q = calloc(QUEST_LEN, sizeof(char));
	if (NULL == q)
	{
		return NULL;
	}
	int a = getNum(), b = getNum();
	char* s = getSymbol();
	sprintf(q, QUEST_FORMAT, a, s, b);
	return q;
}

char** generatorTestPaper(const int num) {
	srand(time(NULL));
	char** testPaper = calloc(num, sizeof(char*));
	for (int idx = 0; idx < num; idx++) {
		*(testPaper + idx) = getQuestions();
	}
	return testPaper;
}

void printTestPaper(const char** questions, const int num, const char *filepath) {
	if (NULL == filepath)
	{
		for (int idx = 0; idx < num; idx++) {
			printf("%s\n", *(questions + idx));
		}
	}
	FILE* fp = fopen(filepath, "w+");
	if (NULL == fp) {
		return;
	}
	for (int idx = 0; idx < num; idx++) {
		//fputs(*(questions + idx), fp);
		fprintf(fp, "%s\n", *(questions + idx));
	}

	fclose(fp);
	fp = NULL;
}

int getNum() {
	return rand() % MAX_NUM + 1;
}

char* getSymbol() {
	return symbol[rand() % 4];
}