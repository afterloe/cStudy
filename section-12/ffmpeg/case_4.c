#include <libavcodec/avcodec.h>


int main()
{
    printf("test ffmpeg \n");
    const char *license = avcodec_license();
    printf("%s \n", license);
    return 0;
}
