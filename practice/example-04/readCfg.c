#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "configModel.h"
#include "decode.h"

int main(int argc, char** args) {
	if (argc == 1) {
		printf("need config path \n");
		return EXIT_FAILURE;
	}
	if (argc == 3) {
		args++;
		char src[128] = {0};
		strcpy(src, *args);
		args++;
		if (strcmp(*args, "c") == 0) {
			printf("code file %s \n", src);
			codeFile(src, "b.txt");
			return EXIT_SUCCESS;
		}
		if (strcmp(*args, "d") == 0) {
			printf("decode file %s \n", src);
			encodeFile(src, "a.txt");
			return EXIT_SUCCESS;
		}
	}
	args++;
	const Config* cfg = readConfig(*args);
	printCfg(cfg);
	return EXIT_SUCCESS;
}