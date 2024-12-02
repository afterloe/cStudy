#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <SDL2/SDL_version.h>
#include <SDL2/SDL_types.h>
#include <SDL2/SDL.h>

#include "include/minplayer.h"

// 每次读取2帧数据, 以1024个采样点一帧 2通道 16bit采样点为例
#define PCM_BUFFER_SIZE 2 * 1024 * 2 * 2

#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

static Uint8* s_audio_buf = NULL; // 存储当前读取的两帧数据
static Uint8* s_audio_pos = NULL; // 目前读取的位置
static Uint8* s_audio_end = NULL; // 缓存结束位置

struct sample_fmt_entry
{
    enum AVSampleFormat sample_fmt;
    const char* fmt_be, * fmt_le;
    SDL_AudioFormat code;
} sample_fmt_entries[] = {
    {AV_SAMPLE_FMT_U8, "u8", "u8", AUDIO_U8},
    {AV_SAMPLE_FMT_S16, "s16be", "s16le", AUDIO_S16LSB},
    {AV_SAMPLE_FMT_S32, "s32be", "s32le", AUDIO_S32LSB},
    {AV_SAMPLE_FMT_FLT, "f32be", "f32le", AUDIO_F32LSB},
    {AV_SAMPLE_FMT_FLTP, "f32be", "f32le", AUDIO_F32LSB},
    {AV_SAMPLE_FMT_DBL, "f64be", "f64le", AUDIO_F32LSB},
};

extern void fill_audio_pcm(void*, Uint8*, int);
extern int get_format_from_sample_fmt(const char**, enum AVSampleFormat);
extern SDL_AudioFormat get_format(enum AVSampleFormat sample_fmt);
extern void decode_mp3(AVCodecContext*, AVPacket*, AVFrame*, FILE*);
extern void decode_flac(SwrContext*, AVCodecContext*, AVPacket*, AVFrame*, FILE*);
extern void playmusic(int rate, SDL_AudioFormat sdl_fmt, AVChannelLayout ch_layout);
extern void initSwrCtx(SwrContext**, AVCodecContext*);


#define FILE_NAME_SIZE 256

typedef void CALLBACK(char*);

typedef struct linkedNode
{
    char* data;
    struct linkedNode* next;
} LinkedNode;

typedef struct linkedArray
{
    size_t size;
    LinkedNode* head;
} LinkeArray;

extern void loadMusic(LinkeArray* arr, char* dirname);
extern void appendItem(LinkeArray*, char*);
extern void iterator(LinkeArray*, CALLBACK);
extern void find_by_idx(LinkeArray* arr, int idx, CALLBACK callback);
extern int getRandomIndex(int max);

void loadMusic(LinkeArray* arr, char* dirname)
{
    char* ptr = NULL;
    DIR* dir = opendir(dirname);
    if (dir == NULL)
    {
        perror("opendir ");
        exit(1);
    }
    struct dirent* current = NULL;
    readdir(dir);

    while ((current = readdir(dir)) != NULL)
    {
        char* d_name = current->d_name;
        if (NULL == d_name)
        {
            continue;
        }
        if (!strcmp(".", d_name) || !strcmp("..", d_name))
        {
            continue;
        }
        if (strstr(d_name, ".flac") == NULL && strstr(d_name, ".mp3") == NULL)
        {
            continue;
        }

        char* filename = calloc(FILE_NAME_SIZE, sizeof(char));
        sprintf(filename, "%s/%s", dirname, d_name);
        if (current->d_type == DT_DIR)
        {
            loadMusic(arr, filename);
        }
        if (current->d_type == DT_REG)
        {
            appendItem(arr, filename);
        }
    }
    closedir(dir);
}

int getRandomIndex(int max)
{
    // 初始化随即种子
    srand(time(NULL));
    return rand() % max + 1;
}

void get_media_info(AVFormatContext** ptr, char* filename)
{
    int ret = avformat_open_input(ptr, filename, NULL, NULL);
    if (ret < 0)
    {
        fprintf(stderr, "can't open this. \n");
        exit(1);
    }
    AVFormatContext* ctx = *ptr;
    avformat_find_stream_info(ctx, NULL);

    // media file info
    fprintf(stdout, "Input: %s \n", filename);
    fprintf(stdout, "Format: %s \n", ctx->iformat->name);
    fprintf(stdout, "Duration: %ld seconds\n", ctx->duration / AV_TIME_BASE);
    AVDictionaryEntry* metadata = NULL;
    while ((metadata = av_dict_get(ctx->metadata, "", metadata, AV_DICT_IGNORE_SUFFIX)))
    {
        fprintf(stdout, "%s=%s\n", metadata->key, metadata->value);
    }
}

void initSwrCtx(SwrContext** ptr, AVCodecContext* codecCtx)
{
    int ret;
    SwrContext* swr_ctx = swr_alloc();
    // input
    AVChannelLayout src_ch_layout = codecCtx->ch_layout;
    int src_rate = codecCtx->sample_rate;
    enum AVSampleFormat src_sample_fmt = codecCtx->sample_fmt;
    // output
    AVChannelLayout dst_ch_layout = AV_CHANNEL_LAYOUT_STEREO;
    int dst_rate = codecCtx->sample_rate;
    enum AVSampleFormat dst_sample_fmt = AV_SAMPLE_FMT_S16;

    /* set options */
    av_opt_set_chlayout(swr_ctx, "in_chlayout", &src_ch_layout, 0);
    av_opt_set_int(swr_ctx, "in_sample_rate", src_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "in_sample_fmt", src_sample_fmt, 0);

    av_opt_set_chlayout(swr_ctx, "out_chlayout", &dst_ch_layout, 0);
    av_opt_set_int(swr_ctx, "out_sample_rate", dst_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "out_sample_fmt", dst_sample_fmt, 0);

    ret = swr_init(swr_ctx);
    if (ret < 0)
    {
        fprintf(stderr, "init swr failed. \n");
        exit(1);
    }

    *ptr = swr_ctx;
}

void to_pcm(AVFormatContext* ctx, char* filename, AVCodecContext** codecCtxPtr)
{
    FILE* tmpfd = fopen(".tmp.pcm", "wb");
    int ret;
    int streamIdx = av_find_best_stream(ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

    // begin decode
    AVStream* stream = ctx->streams[streamIdx];
    AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
    AVCodecParserContext* parserCtx = av_parser_init(codec->id);
    AVCodecContext* codecCtx = avcodec_alloc_context3(codec);
    avcodec_open2(codecCtx, codec, NULL);

    // 将信息复制到codecCtx内
    avcodec_parameters_to_context(codecCtx, stream->codecpar);
    *codecCtxPtr = codecCtx;
    FILE* src = fopen(filename, "rb");
    char filetype = 'd';

    if (NULL != strstr(filename, ".mp3"))
    {
        filetype = 'm';
        uint8_t mp3_header[10] = { 0 };
        fread(mp3_header, 1, 10, src);
        long frame_size = (mp3_header[6] & 0xff) << 21 | (mp3_header[7] & 0xff) << 14 | (mp3_header[8] & 0xff) << 7 | mp3_header[9] & 0xff;
        fseek(src, frame_size + 10, SEEK_SET);
    }

    SwrContext* swr_ctx = NULL;
    if (NULL != strstr(filename, ".flac"))
    {
        filetype = 'f';
        initSwrCtx(&swr_ctx, codecCtx);
    }

    uint8_t* data;
    uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE] = { 0 };
    data = inbuf;
    size_t data_size = fread(inbuf, 1, AUDIO_INBUF_SIZE, src);
    AVPacket* pkt = av_packet_alloc();
    size_t len;
    AVFrame* src_frame = av_frame_alloc();

    while (data_size > 0)
    {
        if (!src_frame)
        {
            if (!(src_frame = av_frame_alloc()))
            {
                fprintf(stderr, "Could not allocate audio frame\n");
                exit(1);
            }
        }

        ret = av_parser_parse2(parserCtx, codecCtx, &pkt->data, &pkt->size,
            data, data_size,
            AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        if (ret < 0)
        {
            fprintf(stderr, "Error while parsing\n");
            exit(1);
        }
        data += ret;
        data_size -= ret;

        // fprintf(stdout, "\033[A");
        // fprintf(stdout, "\033[K");
        // fprintf(stdout, "read %ld b \n", data_size);

        if (pkt->size)
        {
            switch (filetype)
            {
            case 'm':
                decode_mp3(codecCtx, pkt, src_frame, tmpfd);
                break;
            case 'f':
                decode_flac(swr_ctx, codecCtx, pkt, src_frame, tmpfd);
                break;
            default:
                break;
            }
        }

        if (data_size < AUDIO_REFILL_THRESH)
        {
            memmove(inbuf, data, data_size);
            data = inbuf;
            len = fread(data + data_size, 1, AUDIO_INBUF_SIZE - data_size, src);
            if (len > 0)
                data_size += len;
        }
    }

    pkt->data = NULL;
    pkt->size = 0;
    switch (filetype)
    {
    case 'm':
        decode_mp3(codecCtx, pkt, src_frame, tmpfd);
        break;
    case 'f':
        decode_flac(swr_ctx, codecCtx, pkt, src_frame, tmpfd);
        break;
    default:
        break;
    }

    fclose(src);
    fclose(tmpfd);
    if (swr_ctx != NULL)
    {
        swr_free(&swr_ctx);
    }
    av_parser_close(parserCtx);
    av_frame_free(&src_frame);
    av_free(codecCtx);
    free(s_audio_buf);
}

void decode_flac(SwrContext* swr_ctx, AVCodecContext* dec_ctx, AVPacket* pkt, AVFrame* frame, FILE* out)
{
    int i, ch;
    int ret, data_size;

    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0)
    {
        fprintf(stderr, "Error submitting the packet to the decoder\n");
        exit(1);
    }

    uint8_t** dst_data = NULL;
    int dst_linesize;
    size_t src_nb_samples, max_dst_nb_samples, dst_nb_samples;
    max_dst_nb_samples = dst_nb_samples =
        av_rescale_rnd(1024, dec_ctx->sample_rate, dec_ctx->sample_rate, AV_ROUND_UP);
    ret = av_samples_alloc_array_and_samples(&dst_data, &dst_linesize, dec_ctx->ch_layout.nb_channels,
        dst_nb_samples, AV_SAMPLE_FMT_S16, 0);
    int dst_bufsize;
    while (ret >= 0)
    {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0)
        {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }
        data_size = av_get_bytes_per_sample(dec_ctx->sample_fmt);
        if (data_size < 0)
        {
            fprintf(stderr, "Failed to calculate data size\n");
            exit(1);
        }

        // fprintf(stdout, "\033[A");
        // fprintf(stdout, "\033[K");
        // fprintf(stdout, "read %ld b \n", data_size);

        dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, dec_ctx->sample_rate) +
            frame->nb_samples,
            dec_ctx->sample_rate, dec_ctx->sample_rate, AV_ROUND_UP);
        if (dst_nb_samples > max_dst_nb_samples)
        {
            av_freep(&dst_data[0]);
            ret = av_samples_alloc(dst_data, &dst_linesize, dec_ctx->ch_layout.nb_channels,
                dst_nb_samples, AV_SAMPLE_FMT_S16, 1);
            if (ret < 0)
                break;
            max_dst_nb_samples = dst_nb_samples;
        }
        ret = swr_convert(swr_ctx, dst_data, dst_nb_samples, (const uint8_t**)frame->data, frame->nb_samples);
        if (dst_nb_samples > max_dst_nb_samples)
        {
            av_freep(&dst_data[0]);
            ret = av_samples_alloc(dst_data, &dst_linesize, dec_ctx->ch_layout.nb_channels,
                dst_nb_samples, AV_SAMPLE_FMT_S16, 1);
            if (ret < 0)
                break;
            max_dst_nb_samples = dst_nb_samples;
        }

        dst_bufsize = av_samples_get_buffer_size(&dst_linesize, dec_ctx->ch_layout.nb_channels,
            ret, AV_SAMPLE_FMT_S16, 1);
        if (dst_bufsize < 0)
        {
            fprintf(stderr, "Could not get sample buffer size\n");
            exit(1);
        }

        if (av_sample_fmt_is_planar(dec_ctx->sample_fmt))
        {
            for (i = 0; i < frame->nb_samples; i++)
            {
                for (ch = 0; ch < dec_ctx->ch_layout.nb_channels; ch++)
                {
                    fwrite(dst_data[0] + data_size * i, 1, data_size, out);
                }
            }
        }
        else
        {
            fwrite(dst_data[0], 1, dst_bufsize, out);
        }
    }
}

void decode_mp3(AVCodecContext* dec_ctx, AVPacket* pkt, AVFrame* frame, FILE* out)
{
    int i, ch;
    int ret, data_size;

    /* send the packet with the compressed data to the decoder */
    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0)
    {
        fprintf(stderr, "Error submitting the packet to the decoder\n");
        exit(1);
    }

    /* read all the output frames (in general there may be any number of them */
    while (ret >= 0)
    {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0)
        {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }
        data_size = av_get_bytes_per_sample(dec_ctx->sample_fmt);
        if (data_size < 0)
        {
            /* This should not occur, checking just for paranoia */
            fprintf(stderr, "Failed to calculate data size\n");
            exit(1);
        }

        if (av_sample_fmt_is_planar(dec_ctx->sample_fmt))
        {
            for (i = 0; i < frame->nb_samples; i++)
            {
                for (ch = 0; ch < dec_ctx->ch_layout.nb_channels; ch++)
                {
                    fwrite(frame->data[ch] + data_size * i, 1, data_size, out);
                }
            }
        }
        else
        {
            for (i = 0; i < frame->nb_samples; i++)
            {
                fwrite(frame->data[0] + data_size * i, 1, data_size, out);
            }
        }
    }
}

void playmusic(int rate, SDL_AudioFormat sdl_fmt, AVChannelLayout ch_layout)
{
    FILE* tmpfd = fopen(".tmp.pcm", "rb");
    int ret;
    SDL_AudioSpec spec;
    spec.freq = rate;
    spec.format = sdl_fmt;
    spec.channels = ch_layout.nb_channels;
    spec.silence = 0;
    spec.samples = 1024;
    spec.callback = fill_audio_pcm;
    spec.userdata = NULL;

    fseek(tmpfd, 0, SEEK_END);
    size_t file_size = ftell(tmpfd);
    fseek(tmpfd, 0, SEEK_SET);
    size_t read_buffer_len, data_count = 0;

    ret = SDL_Init(SDL_INIT_AUDIO);
    if (ret)
    {
        fprintf(stderr, "can't init SDL \n");
        exit(1);
    }

    ret = SDL_OpenAudio(&spec, 0);
    if (ret < 0)
    {
        fprintf(stderr, "can't open SDL \n");
        exit(1);
    }
    s_audio_buf = calloc(1, PCM_BUFFER_SIZE);
    SDL_PauseAudio(0);

    while (1)
    {
        read_buffer_len = fread(s_audio_buf, 1, PCM_BUFFER_SIZE, tmpfd);
        if (0 == read_buffer_len)
        {
            break;
        }
        data_count += read_buffer_len;

        printf("read %ld of %ld - %.2f %% \n", data_count, file_size, ((float)data_count / file_size) * 100);
        // 将当前光标往上移动一行
        printf("\033[A");
        // 删除光标后面的内容
        printf("\033[K");

        s_audio_end = s_audio_buf + read_buffer_len;
        s_audio_pos = s_audio_buf;

        while (s_audio_pos < s_audio_end)
        {
            SDL_Delay(10);
        }
    }

    fclose(tmpfd);
    unlink(tmpfd);

    SDL_CloseAudio();
    SDL_Quit();
}

void doPlay(char* filename)
{
    AVFormatContext* ctx = NULL;
    get_media_info(&ctx, filename);
    AVCodecContext* codecCtx = NULL;
    to_pcm(ctx, filename, &codecCtx);

    char* filetype = ctx->iformat->name;
    SDL_AudioFormat sdl_fmt;
    if (NULL != strstr(filetype, "flac"))
    {
        sdl_fmt = AUDIO_S16LSB;
    }
    else
    {
        sdl_fmt = get_format(codecCtx->sample_fmt);
    }
    AVChannelLayout dst_ch_layout = AV_CHANNEL_LAYOUT_STEREO;

    playmusic(codecCtx->sample_rate, sdl_fmt, dst_ch_layout);

    avcodec_free_context(&codecCtx);
    av_free(ctx);
}

void doPrint(char* filename)
{
    fprintf(stdout, "%s \n", filename);
    sleep(2);
}

int main(int argc, char** argv)
{
    // if (argc < 2)
    // {
    //     help(argv[0]);
    // }

    // begin:
    char* filename = "/home/afterloe/音乐";
    // char *filename = "/home/afterloe/音乐/莫文蔚-如果没有你.flac";
    // char *filename = "/home/afterloe/音乐/084.林子祥-敢爱敢做【玄音高端无损】.mp3";
    LinkeArray* arr = NULL;
    arr = calloc(1, sizeof(LinkeArray));
    loadMusic(arr, filename);
    fprintf(stdout, "find %ld \n", arr->size);

PLAY:
    int random_idx = getRandomIndex(arr->size);
    find_by_idx(arr, random_idx, doPlay);
    goto PLAY;
    
    free(arr);

    return EXIT_SUCCESS;
}

SDL_AudioFormat get_format(enum AVSampleFormat sample_fmt)
{
    for (int i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++)
    {
        struct sample_fmt_entry* entry = &sample_fmt_entries[i];
        if (sample_fmt == entry->sample_fmt)
        {
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
    int i;
    *fmt = NULL;

    for (i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++)
    {
        struct sample_fmt_entry* entry = &sample_fmt_entries[i];
        if (sample_fmt == entry->sample_fmt)
        {
            *fmt = AV_NE(entry->fmt_be, entry->fmt_le);
            return 0;
        }
    }

    fprintf(stderr,
        "sample format %s is not supported as output format\n",
        av_get_sample_fmt_name(sample_fmt));
    return -1;
}

// 音频设备回调函数
void fill_audio_pcm(void* udata, Uint8* stream, int len)
{
    // udata: 用户自定义数据
    SDL_memset(stream, 0, len);
    if (s_audio_pos >= s_audio_end) // （当前两帧）数据读取完毕
    {
        return;
    }

    // 数据够了就读预设长度，数据不够就只读部分（不够的时候剩多少就读取多少）
    int remain_buffer_len = s_audio_end - s_audio_pos;
    len = (len < remain_buffer_len) ? len : remain_buffer_len;
    // 将声音写入设备
    SDL_MixAudio(stream, s_audio_pos, len, SDL_MIX_MAXVOLUME);

    s_audio_pos += len; // 移动缓存指针（当前pos）
}

void help(const char* appname)
{
    fprintf(stdout, "usage %s <dir> \n", appname);
    fprintf(stdout, "supper file *.mp3, *.flac \n");
    exit(EXIT_SUCCESS);
}

void version()
{
    struct SDL_version sv = {};
    SDL_GetVersion(&sv);
    printf("power by ffmpeg %s , ", av_version_info());
    printf("SDL %d\n", sv.major);
}


void appendItem(LinkeArray* arr, char* that)
{
    LinkedNode* node = malloc(sizeof(LinkedNode));
    node->data = calloc(strlen(that), sizeof(that));
    memcpy(node->data, that, strlen(that));
    node->next = NULL;

    if (arr->size == 0)
    {
        arr->head = node;
        arr->size = 1;
        return;
    }

    LinkedNode* ptr = arr->head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = node;
    arr->size += 1;
}

void iterator(LinkeArray* arr, CALLBACK callback)
{
    if (NULL == arr || arr->size == 0)
    {
        return;
    }
    LinkedNode* ptr = arr->head;
    while (ptr != NULL)
    {
        callback(ptr->data);
        ptr = ptr->next;
    }
}

void find_by_idx(LinkeArray* arr, int idx, CALLBACK callback)
{
    if (NULL == arr || arr->size == 0)
    {
        return;
    }
    if (idx > arr->size)
    {
        return;
    }
    int rt = 0;
    LinkedNode* ptr = arr->head;
    while (ptr != NULL)
    {
        if (rt == idx)
        {
            callback(ptr->data);
            break;
        }
        ptr = ptr->next;
        rt++;
    }
}
