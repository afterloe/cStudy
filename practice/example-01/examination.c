#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "examination.h"

#define MAX_NUM   100
#define QUEST_FORMAT "%d\t%c\t%d\t=\t"
#define ANSWER_FORMAT "%d\t%c\t%d\t=\t%2g\n"

extern int getNum();
extern char getSymbol();
extern float work(int, int, char);

static const char symbol[4] = {'+', '-', '*', '/'};

char* getQuestions() {
	char* q = calloc(1, sizeof(char));
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
	char** testPaper = calloc(num, sizeof(char*));
	if (NULL == testPaper) {
		return NULL;
	}
	srand(time(NULL));
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

void doQuestions(const char* filepath, const char* destPath) {
	FILE* fp = fopen(filepath, "r");
	if (NULL == fp)
	{
		perror("open file :");
		return ;
	}
	FILE* answers = fopen(destPath, "w+");
	if (NULL == answers) {
		perror("open dest file :");
		return;
	}
	int a, b, num = 0;
	char s;
	while (!feof(fp))
	{
		fscanf(fp, QUEST_FORMAT, &a, &s, &b);
		const float r = work(a, b, s);
		fprintf(answers, ANSWER_FORMAT, a, s, b, r);
		num++;
	}
	printf("write %d question to %s \n", num, destPath);
	fclose(fp);
	fclose(answers);
}

int getQuestionsNum(const char* filepath) {
	return 0;

}

int getNum() {
	return rand() % MAX_NUM + 1;
}

char getSymbol() {
	return symbol[rand() % 4];
}

float work(int a, int b, char s) {
	switch (s) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return (float)a / b;
	default:
		return 0;
	}
}