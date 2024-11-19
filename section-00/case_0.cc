#include <iostream>

#ifndef SIZE
#define SIZE 10
#endif

// 编译时指定SIZE的值
// gcc case_0.c -DSIZE=11
/*
SIZE is 11
*/
int main(void)
{
    std::cout << "SIZE IS " << SIZE << std::endl;
    return EXIT_SUCCESS;
}