//
// Created by afterloe on 2024/11/12.
//

#ifndef DICT_H
#define DICT_H

typedef struct dict {
    char *ch;
    char *en;

    struct dict *next;
} Dict;

extern Dict *dict_new();

extern void find(const char *word, Dict *dict);

extern void free_dict(Dict **dict);

extern void help();

#endif //DICT_H
