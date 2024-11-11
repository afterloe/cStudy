#ifndef __EXAMINATION_H__
#define __EXAMINATION_H__

extern char* getQuestions();
extern char** generatorTestPaper(const int);
extern void printTestPaper(const char**, const int, const char*);
extern void doQuestions(const char*, const char* destPath);
extern int getQuestionsNum(const char*);

#endif