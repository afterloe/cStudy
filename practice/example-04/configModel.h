#ifndef __CONFIG_MODEL__
#define __CONFIG_MODEL__

typedef struct c {
	char* key;
	char* value;

	struct c *next;
} Config;

extern Config** readConfig(const char*);
extern Config* add(Config*,  Config*);
extern void printCfg( Config*);

#endif // __CONFIG_MODEL__

