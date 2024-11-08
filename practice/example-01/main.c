#include <stdio.h>
#include <stdlib.h>

#include "Examination.h"

int main(int argc, char** argv) {
	printf("how many questions you want to generator: ");
	int num;
	int ret = scanf("%d", &num);
	if (-1 == ret)
	{
		return EXIT_FAILURE;
	}
	char** questions = generatorTestPaper(num);
	printTestPaper(questions, num, "a.txt");
	free(questions);
	questions = NULL;
	return EXIT_SUCCESS;
}