/**
 * c invoke ffmpeg print medio info - 2
 */
#include <stdlib.h>
#include <stdio.h>

#include <libavformat/avformat.h>

int main(int argc, char** args)
{

    AVFormatContext* ctx = NULL;
    AVDictionaryEntry* dictionary = NULL;

    int ret;
    ret = avformat_open_input(&ctx, args[1], NULL, NULL);
    if (ret != 0)
    {
        perror("avopen :");
        goto handlE;
    }
    ret = avformat_find_stream_info(ctx, NULL);
    if (ret != 0)
    {
        perror("info :");
        goto handlE;
    }

    printf("File: %s\n", args[1]);
    printf("Format: %s\n", ctx->iformat->name);
    printf("Duration: %lld seconds\n", ctx->duration / AV_TIME_BASE);

    // 输出源信息
    while (dictionary = av_dict_get(ctx->metadata, "", dictionary, AV_DICT_IGNORE_SUFFIX))
    {
        printf("%s=%s\n", dictionary->key, dictionary->value);
    }

    for (int i = 0; i < ctx->nb_streams; i++)
    {
        AVStream* s = ctx->streams[i];

        AVRational time_base = s->time_base;
        const char* type = "Unknown";
        printf("时间基数: %d/%d\n", time_base.num, time_base.den);
        if (s->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            // 视频
            type = "Video";
            printf("\n%s Stream #%d:\n", type, i);
            printf("Codec: %s\n", avcodec_get_name(s->codecpar->codec_id));
            printf("Resolution: %dx%d\n", s->codecpar->width, s->codecpar->height);
            printf("Frame Rate: %.2f fps\n", av_q2d(s->avg_frame_rate));
            printf("Bit Rate: %lld kbps\n", s->codecpar->bit_rate / 1000);
        }
        else if (s->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            // 声音
            type = "Audio";
            printf("\n%s Stream #%d:\n", type, i);
            printf("Codec: %s\n", avcodec_get_name(s->codecpar->codec_id));
            printf("Sample Rate: %d Hz\n", s->codecpar->sample_rate);
            printf("Channels: %d\n", s->codecpar->bit_rate);
            printf("Bit Rate: %lld kbps\n", s->codecpar->bit_rate / 1000);
        }
    }

handlE:
    if (ctx != NULL)
    {
        avformat_close_input(ctx);
    }

    return EXIT_SUCCESS;
}