#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL2/SDL_version.h>

#include "include/minplayer.h"

#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

extern int get_format_from_sample_fmt(const char**, enum AVSampleFormat);
extern void decode(AVCodecContext*, AVPacket*, AVFrame*, int);

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        // help();
    }

    // char *filename = argv[1];
    char* filename = "/home/afterloe/音乐/051.谭咏麟-朋友【玄音高端无损】.mp3";

    int ret = -1, streamIdx;
    AVPacket* pkt = av_packet_alloc();
    AVFormatContext* ctx = NULL;
    ret = avformat_open_input(&ctx, filename, NULL, NULL);
    if (ret < 0)
    {
        perror("av open :");
        exit(EXIT_FAILURE);
    }
    ret = avformat_find_stream_info(ctx, NULL);
    if (ret < 0)
    {
    ERROR_AV:
        perror("av find stream :");
        avformat_close_input(&ctx);
        exit(EXIT_FAILURE);
    }
    streamIdx = av_find_best_stream(ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (ret < 0)
    {
        perror("no such this stream :");
        goto ERROR_AV;
    }
    AVStream* stream = ctx->streams[streamIdx];
    AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
    if (codec == NULL)
    {
        perror("Codec not fond :");
        goto ERROR_AV;
    }
    AVCodecParserContext* parserCtx = av_parser_init(codec->id);
    if (parserCtx == NULL)
    {
        perror(" Parser not found :");
        goto ERROR_AV;
    }
    AVCodecContext* codecCtx = avcodec_alloc_context3(codec);
    if (codecCtx == NULL)
    {
        perror("allocate audio codec context :");
        goto ERROR_AV;
    }
    ret = avcodec_open2(codecCtx, codec, NULL);
    if (ret < 0)
    {
        perror("Not open codec :");
    ERROR_CODEC_CTX:
        av_free(codecCtx);
        goto ERROR_AV;
    }

    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open src file :");
        goto ERROR_CODEC_CTX;
    }
    int dest = open("./a.pcm", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

    AVFrame* decoded_frame = av_frame_alloc();
    if (decoded_frame == NULL)
    {
        perror("allocate audio frame :");
        goto ERROR_CODEC_CTX;
    }

    uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t* data;
    if (NULL != strstr(filename, ".mp3"))
    {
        uint8_t mp3_header[10] = { 0 };
        read(fd, mp3_header, 10);
        long frame_size = (mp3_header[6] & 0xff) << 21 | (mp3_header[7] & 0xff) << 14 | (mp3_header[8] & 0xff) << 7 | mp3_header[9] & 0xff;
        lseek(fd, frame_size + 10, SEEK_SET);
    }

    data = inbuf;
    int len = read(fd, data, AUDIO_INBUF_SIZE);
    while (len > 0)
    {
        ret = av_parser_parse2(parserCtx, codecCtx, &pkt->data, &pkt->size, data, len, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        if (ret < 0)
        {
            perror("Error while parsing \n");
            goto ERROR_CODEC_CTX;
        }

        data += ret;
        len -= ret;

        if (pkt->size)
        {
            decode(codecCtx, pkt, decoded_frame, dest);
        }

        if (len < AUDIO_REFILL_THRESH)
        {
            memmove(inbuf, data, len);
            data = inbuf;
            int size = read(fd, data + len, AUDIO_INBUF_SIZE - len);
            if (size > 0)
            {
                len += size;
            }
        }
    }

    pkt->data = NULL;
    pkt->size = 0;
    decode(codecCtx, pkt, decoded_frame, dest);

    enum AVSampleFormat sfmt = codecCtx->sample_fmt;

    if (av_sample_fmt_is_planar(sfmt)) {
        const char* packed = av_get_sample_fmt_name(sfmt);
        printf("Warning: the sample format the decoder produced is planar "
            "(%s). This example will output the first channel only.\n",
            packed ? packed : "?");
        sfmt = av_get_packed_sample_fmt(sfmt);
    }

    int n_channels = codecCtx->ch_layout.nb_channels;
    const char* fmt;
    if ((ret = get_format_from_sample_fmt(&fmt, sfmt)) < 0) {
        goto end;
    }

end:
    if (fd > 0)
    {
        close(fd);
    }
    avcodec_free_context(&codecCtx);
    av_parser_close(parserCtx);
    av_frame_free(&decoded_frame);
    av_packet_free(&pkt);

    return EXIT_SUCCESS;
}


int get_format_from_sample_fmt(const char** fmt, enum AVSampleFormat sample_fmt)
{
    int i;
    struct sample_fmt_entry {
        enum AVSampleFormat sample_fmt; const char* fmt_be, * fmt_le;
    } sample_fmt_entries[] = {
        { AV_SAMPLE_FMT_U8,  "u8",    "u8"    },
        { AV_SAMPLE_FMT_S16, "s16be", "s16le" },
        { AV_SAMPLE_FMT_S32, "s32be", "s32le" },
        { AV_SAMPLE_FMT_FLT, "f32be", "f32le" },
        { AV_SAMPLE_FMT_DBL, "f64be", "f64le" },
    };
    *fmt = NULL;

    for (i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++) {
        struct sample_fmt_entry* entry = &sample_fmt_entries[i];
        if (sample_fmt == entry->sample_fmt) {
            *fmt = AV_NE(entry->fmt_be, entry->fmt_le);
            return 0;
        }
    }

    fprintf(stderr,
        "sample format %s is not supported as output format\n",
        av_get_sample_fmt_name(sample_fmt));
    return -1;
}


void decode(AVCodecContext* dec_ctx, AVPacket* pkt, AVFrame* frame, int fd)
{
    int i, ch;
    int ret, data_size;

    /* send the packet with the compressed data to the decoder */
    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error submitting the packet to the decoder\n");
        exit(1);
    }

    /* read all the output frames (in general there may be any number of them */
    while (ret >= 0) {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }
        data_size = av_get_bytes_per_sample(dec_ctx->sample_fmt);
        if (data_size < 0) {
            /* This should not occur, checking just for paranoia */
            fprintf(stderr, "Failed to calculate data size\n");
            exit(1);
        }
        for (i = 0; i < frame->nb_samples; i++)
        {
            for (ch = 0; ch < dec_ctx->ch_layout.nb_channels; ch++) {
                write(fd, frame->data[ch] + data_size * i, data_size);
            }
        }

    }
}


void help()
{
    printf("usage minplayer <file> \n");
    printf("supper file *.mp3 \n");
    exit(EXIT_SUCCESS);
}

void version()
{
    struct SDL_version sv = {};
    SDL_GetVersion(&sv);
    printf("power by ffmpeg %s , ", av_version_info());
    printf("SDL %d\n", sv.major);
}