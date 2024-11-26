#include <stdlib.h>
#include <stdio.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/dict.h>

int main(int argv, char ** args)
{
    AVFormatContext* ctx = NULL;
    int ret;

    const char* input_file = args[1];

    ret = avformat_open_input(&ctx, input_file, NULL, NULL);
    if (ret != 0)
    {
        printf("can't open file");
        goto handle_error;
    }

    AVDictionaryEntry *metadata = NULL;
    while ((metadata = av_dict_get(ctx->metadata, "", metadata, AV_DICT_IGNORE_SUFFIX)))
    {
        printf("%s=%s\n", metadata->key, metadata->value);
    }

    printf("============== \n");
    av_dump_format(ctx, 0, input_file, 0); 
    printf("============== \n");

    ret = avformat_find_stream_info(ctx, NULL);
    if (ret != 0)
    {
        printf("can't find any info .");
        goto handle_error;
    }

    for (int i = 0; i < ctx->nb_streams; i++)
    {
        AVStream* s = ctx->streams[i];
        AVCodecParameters* params = s->codecpar;
        AVRational time_base = s->time_base;
        printf("#stream %d \n", i);
        printf("  时间基数: %d/%d\n", time_base.num, time_base.den);
        printf("  编码器ID: %d\n", params->codec_id);
        printf("  视频宽度: %d\n", params->width);
        printf("  视频高度：%d\n", params->height);
        printf("  帧率：%d/%d\n", s->avg_frame_rate.num, s->avg_frame_rate.den);
    }

handle_error:
    perror("faile :");

    if (NULL != ctx)
    {
        avformat_close_input(&ctx);
    }

    return EXIT_SUCCESS;
}