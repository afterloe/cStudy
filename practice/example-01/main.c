#include <stdio.h>
#include <stdlib.h>

#include "examination.h"

extern void getTestPaper();
extern void doTestPaper(const char*, const char*);

int main(int argc, char** argv) {
	if (argc == 1) {
		getTestPaper();
	}
	else {
		argv++;
		doTestPaper(*argv, "b.txt");
	}

	return EXIT_SUCCESS;
}

void getTestPaper() {
	printf("how many questions you want to generator: ");
	int num;
	int ret = scanf("%d", &num);
	if (-1 == ret)
	{
		return;
	}
	char** questions = generatorTestPaper(num);
	printTestPaper(questions, num, "a.txt");
	free(questions);
	questions = NULL;
}

void doTestPaper(const char* paperPath, const char* answerPath)
{
	doQuestions(paperPath, answerPath);
}