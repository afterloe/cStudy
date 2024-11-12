//
// Created by afterloe on 2024/11/12.
//

#ifndef DICT_H
#define DICT_H

typedef struct dict {
    char *key;
    char *val;

    struct dict *next;
} Dict;

extern Dict *dict_new(Dict **, const char*);

extern void find(const char *word, Dict *dict);

extern void free_dict(Dict **dict);

extern void help();

extern Dict *add_dict(Dict *, Dict *);

#endif //DICT_H
