#ifndef __CONFIG_MODEL__
#define __CONFIG_MODEL__

typedef struct c {
	char* key;
	char* value;
} Config;

extern Config* readConfig(const char*);

#endif // __CONFIG_MODEL__

