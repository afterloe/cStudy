#include<stdio.h>

int main(int argc, char** argv) {
    char str1[5] = "hello";
    char str2[6] = {'u', 'b', 'u', 'n', 't', 'u'};

    printf("%s\n", str2);

    for(int i = 0; i < sizeof(str1)/sizeof(str1[0]); i++) {
        printf("%c", str1[i]);
    }
    printf("\n");
}
