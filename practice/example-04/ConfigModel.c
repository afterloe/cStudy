#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ConfigModel.h"

#define BUF_SIZE 1500

Config** readConfig(const char* filepath) {
	Config* head = NULL;
	FILE* fp = NULL;
	fp = fopen(filepath, "r");
	if (NULL == fp)
	{
		perror("open file :");
		return NULL;
	}

	char* buf = calloc(BUF_SIZE, sizeof(char));
	while (!feof(fp))
	{
		memset(buf, 0, BUF_SIZE);
		fgets(buf, BUF_SIZE, fp);
		int* ret = strchr(buf, '=');
		if (ret == NULL) {
			continue;
		}
		
		char* key = strtok(buf, "=");
		if (NULL == key) {
			continue;
		}
		Config* node = malloc(sizeof(Config));
		memset(node, 0, sizeof(Config));
		node->value = calloc(128, sizeof(char*));
		node->key = calloc(128, sizeof(char*));
		node->next = NULL;
		strcpy(node->key, key);
		key = strtok(NULL, cpy);
		strcpy(node->value, key);
		head = add(head, node);
	}


	free(buf);
	buf = NULL;
	fclose(fp);
	fp = NULL;

	return &head;
}

Config* add(Config* ptr, Config* node) {

	if (NULL != ptr) {
		node->next = ptr;
	}
	ptr = node;
	return ptr;
}

void printCfg( Config* ptr)
{
	if (NULL == ptr)
	{
		printf("Config is empty; \n");
			return;
	}
	while (ptr != NULL)
	{
		printf("%s -> %s \n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
	printf("\n");
}