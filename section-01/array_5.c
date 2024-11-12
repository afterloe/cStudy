#include <stdio.h>
#include <string.h>

int main() {
    char word[10] = "allocated";
    printf("%s \n", word); // allocated
    // 不要前3个字母
    printf("%s \n", word + 3); // ocated

    // 不要后3个字母 - API
    char cut[10] = {0};
    strncpy(cut, word, strlen(word) - 3 ); // alloca
    printf("%s \n", cut);
    
    // 不要后3个字符 - 字符串指针
    memset(cut, 0, 10);
    char *start = word;
    char *end = word + (strlen(word) - 3);
    strncpy(cut, start, end - start);
    printf("%s \n", cut); // alloca
    return 0;
}