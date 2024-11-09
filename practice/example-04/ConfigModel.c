#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ConfigModel.h"

#define BUF_SIZE 1500

Config* readConfig(const char* filepath) {
	Config* arr = NULL;
	FILE* fp = NULL;
	fp = fopen(filepath, "r");
	if (NULL == fp)
	{
		perror("open file :");
		return NULL;
	}

	int line = 1, idx = 0;
	while (!feof(fp)) {
		if (fgetc(fp) == '\n') {
			line++;
		}
	}
	printf("%d config item \n", line);
	fseek(fp, 0, SEEK_SET);

	arr = calloc(line, sizeof(Config));
	char* buf = calloc(BUF_SIZE, sizeof(char));
	while (!feof(fp))
	{
		memset(buf, 0, BUF_SIZE);
		fgets(buf, BUF_SIZE, fp);
		char* key = strtok(buf, "=");
		if (NULL == key) {
			continue;
		}
		Config* cfg = malloc(sizeof(Config));
		memset(cfg, 0, sizeof(Config));
		cfg->value = calloc(128, sizeof(char*));
		cfg->key = calloc(128, sizeof(char*));


		strcpy(cfg->key, key);
		key = strtok(NULL, buf);
		strcpy(cfg->value, key);
		arr[idx] = *cfg;
		idx++;

	}


	free(buf);
	buf = NULL;
	fclose(fp);
	fp = NULL;

	return arr;
}