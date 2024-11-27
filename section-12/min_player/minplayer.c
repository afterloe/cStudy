#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_types.h>
#include <SDL2/SDL.h>

#include "include/minplayer.h"

// 每次读取2帧数据, 以1024个采样点一帧 2通道 16bit采样点为例
#define PCM_BUFFER_SIZE (2 * 1024 * 2 * 2)

#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

static Uint8* s_audio_buf = NULL;   // 存储当前读取的两帧数据
static Uint8* s_audio_pos = NULL;   // 目前读取的位置
static Uint8* s_audio_end = NULL;   // 缓存结束位置

struct sample_fmt_entry {
    enum AVSampleFormat sample_fmt;
    const char* fmt_be, * fmt_le;
    SDL_AudioFormat code;
} sample_fmt_entries[] = {
    { AV_SAMPLE_FMT_U8,  "u8",    "u8"    , AUDIO_U8},
    { AV_SAMPLE_FMT_S16, "s16be", "s16le" , AUDIO_S16LSB},
    { AV_SAMPLE_FMT_S32, "s32be", "s32le" , AUDIO_S32LSB},
    { AV_SAMPLE_FMT_FLT, "f32be", "f32le" , AUDIO_F32LSB},
    { AV_SAMPLE_FMT_FLTP, "f32be", "f32le" , AUDIO_F32LSB},
    { AV_SAMPLE_FMT_DBL, "f64be", "f64le" , AUDIO_F32LSB},
};

extern void fill_audio_pcm(void*, Uint8*, int);
extern int get_format_from_sample_fmt(const char**, enum AVSampleFormat);
extern SDL_AudioFormat get_format(enum AVSampleFormat sample_fmt);
extern void decode(AVCodecContext*, AVPacket*, AVFrame*);

static FILE* out = NULL;

int getIndex(int max)
{
    // 初始化随即种子
    srand(time(NULL));
    return rand() % max + 1;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        help();
    }

begin:
    char* filename = argv[getIndex(argc - 1)];
    // char* filename = "/home/afterloe/音乐/莫文蔚-如果没有你.flac";
    // char* filename = "/home/afterloe/音乐/11.Free Loop - Daniel Powter【十倍音质】.mp3";
    out = fopen("c.pcm", "wb+");

    int ret = -1, streamIdx;
    AVPacket* pkt = av_packet_alloc();
    AVFormatContext* ctx = NULL;
    ret = avformat_open_input(&ctx, filename, NULL, NULL);
    if (ret < 0)
    {
        fprintf(stdout, "no such file %s \n", filename);
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
    // /usr/local/ffmpeg/bin/ffmpeg -i ~/音乐/后弦-单车恋人.flac -y -acodec pcm_f32le -f f32le -ac 2 -ar 48000 output.pcm
    AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id); // AV_CODEC_ID_FLAC
    // AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_FLAC);
    if (codec == NULL)
    {
        perror("Codec not fond :");
        goto ERROR_AV;
    }
    AVCodecParserContext* parserCtx = av_parser_init(codec->id);
    if (parserCtx == NULL)
    {
        perror("Parser not found :");
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

    FILE* fd = fopen(filename, "rb");
    if (fd < 0)
    {
        perror("open src file :");
        goto ERROR_CODEC_CTX;
    }

    AVFrame* decoded_frame = av_frame_alloc();
    if (decoded_frame == NULL)
    {
        perror("allocate audio frame :");
        goto ERROR_CODEC_CTX;
    }

    printf("Input: %s \n", filename);
    printf("Format: %s \n", ctx->iformat->name);
    printf("Duration: %lld seconds\n", ctx->duration / AV_TIME_BASE);

    AVDictionaryEntry* metadata = NULL;
    while ((metadata = av_dict_get(ctx->metadata, "", metadata, AV_DICT_IGNORE_SUFFIX)))
    {
        printf("%s=%s\n", metadata->key, metadata->value);
    }

    uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t* data;
    if (NULL != strstr(filename, ".mp3"))
    {
        uint8_t mp3_header[10] = { 0 };
        fread(mp3_header, 1, 10, fd);
        long frame_size = (mp3_header[6] & 0xff) << 21 | (mp3_header[7] & 0xff) << 14 | (mp3_header[8] & 0xff) << 7 | mp3_header[9] & 0xff;
        fseek(fd, frame_size + 10, SEEK_SET);
    }

    data = inbuf;
    size_t len = fread(inbuf, 1, AUDIO_INBUF_SIZE, fd);

    ret = av_parser_parse2(parserCtx, codecCtx, &pkt->data, &pkt->size, data, len, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
    if (ret < 0 || ret == AUDIO_INBUF_SIZE)
    {
        fprintf(stdout, "can't parse %s \n", filename);
        perror("parser: ");
        goto ERROR_CODEC_CTX;
    }

    SDL_AudioSpec spec;
    spec.freq = codecCtx->sample_rate;
    spec.format = get_format(codecCtx->sample_fmt);
    spec.channels = codecCtx->ch_layout.nb_channels;
    spec.silence = 0;
    spec.samples = 1024;
    spec.callback = fill_audio_pcm;
    spec.userdata = parserCtx;

    ret = SDL_Init(SDL_INIT_AUDIO);
    if (ret)
    {
        perror("can't init SDL \n");
        goto ERROR_CODEC_CTX;
    }

    ret = SDL_OpenAudio(&spec, 0);
    if (ret < 0)
    {
        perror("can't open SDL \n");
        goto ERROR_CODEC_CTX;
    }
    s_audio_buf = calloc(1, PCM_BUFFER_SIZE);
    SDL_PauseAudio(0);

    do
    {
        if (ret < 0)
        {
            perror("Error while parsing \n");
            goto ERROR_CODEC_CTX;
        }

        data += ret;
        len -= ret;

        if (pkt->size)
        {
            decode(codecCtx, pkt, decoded_frame);
        }

        if (len < AUDIO_REFILL_THRESH)
        {
            memmove(inbuf, data, len);
            data = inbuf;
            int size = fread(data + len, 1, AUDIO_INBUF_SIZE - len, fd);
            if (size > 0)
            {
                len += size;
            }
        }
        ret = av_parser_parse2(parserCtx, codecCtx, &pkt->data, &pkt->size, data, len, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
    } while (len > 0);

    pkt->data = NULL;
    pkt->size = 0;
    decode(codecCtx, pkt, decoded_frame);

    enum AVSampleFormat sfmt = codecCtx->sample_fmt;

    fseek(out, 0, SEEK_END);
    size_t file_size = ftell(out);
    fseek(out, 0, SEEK_SET);
    size_t read_buffer_len, data_count = 0;
    while (1)
    {
        read_buffer_len = fread(s_audio_buf, 1, PCM_BUFFER_SIZE, out);
        if (0 == read_buffer_len)
        {
            break;
        }
        data_count += read_buffer_len;

        printf("read %ld of %ld - %.2f %% \n", data_count, file_size, ((float)data_count / file_size) * 100);
        //将当前光标往上移动一行
        printf("\033[A");
        //删除光标后面的内容
        printf("\033[K");

        s_audio_end = s_audio_buf + read_buffer_len;
        s_audio_pos = s_audio_buf;

        while (s_audio_pos < s_audio_end)
        {
            SDL_Delay(10);
        }

    }

    fclose(out);

    if (av_sample_fmt_is_planar(sfmt)) {
        const char* packed = av_get_sample_fmt_name(sfmt);
        printf("Warning: the sample format the decoder produced is planar "
            "(%s). This example will output the first channel only.\n",
            packed ? packed : "?");
        sfmt = av_get_packed_sample_fmt(sfmt);
    }

    const char* fmt;
    if ((ret = get_format_from_sample_fmt(&fmt, sfmt)) < 0) {
        goto end;
    }
    printf("%s \n", fmt);

    SDL_CloseAudio();
    SDL_Quit();

end:
    if (fd > 0)
    {
        fclose(fd);
    }
    avcodec_free_context(&codecCtx);
    av_parser_close(parserCtx);
    av_frame_free(&decoded_frame);
    av_packet_free(&pkt);

    goto begin;

    return EXIT_SUCCESS;
}

SDL_AudioFormat get_format(enum AVSampleFormat sample_fmt)
{
    for (int i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++) {
        struct sample_fmt_entry* entry = &sample_fmt_entries[i];
        if (sample_fmt == entry->sample_fmt) {
            return entry->code;
        }
    }

    fprintf(stderr,
        "sample format %s is not supported as output format\n",
        av_get_sample_fmt_name(sample_fmt));
    return -1;
}

int get_format_from_sample_fmt(const char** fmt, enum AVSampleFormat sample_fmt)
{
    int i; *fmt = NULL;

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


void decode(AVCodecContext* dec_ctx, AVPacket* pkt, AVFrame* frame)
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
                fwrite(frame->data[ch] + data_size * i, 1, data_size, out);
            }
        }

    }
}

//音频设备回调函数
void fill_audio_pcm(void* udata, Uint8* stream, int len)
{
    // udata: 用户自定义数据
    SDL_memset(stream, 0, len);
    if (s_audio_pos >= s_audio_end)            // （当前两帧）数据读取完毕
    {
        return;
    }

    // 数据够了就读预设长度，数据不够就只读部分（不够的时候剩多少就读取多少）
    int remain_buffer_len = s_audio_end - s_audio_pos;
    len = (len < remain_buffer_len) ? len : remain_buffer_len;
    // 将声音写入设备
    SDL_MixAudio(stream, s_audio_pos, len, SDL_MIX_MAXVOLUME);

    s_audio_pos += len;  // 移动缓存指针（当前pos）
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