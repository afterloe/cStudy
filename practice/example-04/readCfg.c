#include <stdio.h>
#include <stdlib.h>

#include "configModel.h"

int main(int argc, char** args) {
	//if (argc == 1) {
	//	printf("need config path \n");
	//	return EXIT_FAILURE;
	//}
	//args++;
	Config** cfg = readConfig("a.cfg");
	printCfg(*cfg);
	return EXIT_SUCCESS;
}