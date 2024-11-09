#include <stdio.h>
#include <stdlib.h>

#include "ConfigModel.h"

int main(int argc, char** args) {
	//if (argc == 1) {
	//	printf("need config path \n");
	//	return EXIT_FAILURE;
	//}
	//args++;
	Config* cfg = readConfig("a.cfg");
	do {
		printf("%s -> %s \n", cfg->key, cfg->value);
		cfg++;
	} while (cfg != NULL);
	return EXIT_SUCCESS;
}