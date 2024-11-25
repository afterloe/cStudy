
#include <stdio.h>
#include <SDL_types.h>
#include "SDL.h"

#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#define MAX_AUDIO_FRAME_SIZE 19200

static  Uint32  _audioLen = 0;
static  Uint8* _audioPos = NULL;

void allBack_fillAudioData(void* userdata, uint8_t* stream, int len)
{
    SDL_memset(stream, 0, len);
    if (_audioLen == 0)
    {
        return;
    }
    len = (len > _audioLen ? _audioLen : len);

    SDL_MixAudio(stream, _audioPos, len, SDL_MIX_MAXVOLUME);

    _audioPos += len;
    _audioLen -= len;
}

int main(int argc, char** argv) {

    char* filename = "/home/afterloe/音乐/排骨教主-搬走.flac";

    AVFormatContext* ctx = NULL;
    AVDictionaryEntry* dictionary = NULL;

    int ret;
    ret = avformat_open_input(&ctx, filename, NULL, NULL);
    if (EXIT_SUCCESS != ret)
    {
        perror("open file :");
        exit(EXIT_FAILURE);
    }
    ret = avformat_find_stream_info(ctx, NULL);
    if (EXIT_SUCCESS != ret)
    {
        perror("find stream :");
        exit(EXIT_FAILURE);
    }

    printf("FILE: \t %s \n", filename);
    printf("Format: \t %s \n", ctx->iformat->name);
    printf("Duration: \t %lld seconds \n", ctx->duration / AV_TIME_BASE);

    printf("Music Info \n");
    while (dictionary = av_dict_get(ctx->metadata, "", dictionary, AV_DICT_IGNORE_SUFFIX), dictionary != NULL)
    {
        printf("\t %s: \t %s", dictionary->key, dictionary->value);
    }

    int audioStreamIdx = av_find_best_stream(ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (-1 == audioStreamIdx)
    {
    ERR_CLOSE:
        perror("record:");
        printf("can't read any info \n");
        avformat_close_input(&ctx);
        exit(EXIT_FAILURE);

    }
    AVStream* stream = ctx->streams[audioStreamIdx];
    if (stream->codecpar->codec_type != AVMEDIA_TYPE_AUDIO)
    {
        printf("can't read any info \n");
        goto ERR_CLOSE;
    }

    // 音频流参数
    AVCodecParameters* pCodecParameters = ctx->streams[audioStreamIdx]->codecpar;

    // 获取解码器
    AVCodec* pCodec = avcodec_find_decoder(pCodecParameters->codec_id);
    if (NULL == pCodec)
    {
        printf("can't find codec \n");
        goto ERR_CLOSE;
    }

    // 解码器Ctx
    AVCodecContext* pCodecCtx = avcodec_alloc_context3(pCodec);
    if (NULL == pCodecCtx)
    {
        printf("can't get codecCtx \n");
        goto ERR_CLOSE;
    }

    // 打开解码器
    ret = avcodec_open2(pCodecCtx, pCodec, NULL);
    if (ret < 0)
    {
        printf("open codec failed \n");
        goto ERR_CLOSE;
    }

    AVPacket* packet = av_malloc(sizeof(AVPacket));  // 解码前的帧 
    av_init_packet(packet);
    AVFrame* pFrame = av_frame_alloc(); // 解码后的帧 
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO; // 输出声道
    enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16; // 输出格式S16

    SDL_AudioSpec spec;
    spec.freq = 44100;     // 指定了每秒向音频设备发送的sample数。常用的值为：11025，22050，44100。值越高质量越好。
    spec.format = AUDIO_S16; // 每个sample的大小
    spec.channels = 2; // 1 单通道 - 2双通道
    spec.silence = 0;
    spec.samples = 1024; // 这个值表示音频缓存区的大小（以sample计）。一个sample是一段大小为 format * channels 的音频数据。
    spec.callback = allBack_fillAudioData;
    spec.userdata = 0;

    // 步骤一：初始化音频子系统
    ret = SDL_Init(SDL_INIT_AUDIO);
    if (ret)
    {
        printf("can't init SDL \n");
        goto ERR_CLOSE;
    }

    // 步骤二：打开音频设备
    ret = SDL_OpenAudio(&spec, 0);
    if (ret)
    {
        printf("can't open SDL \n");
        goto ERR_CLOSE;
    }

    // 步骤三：开始播放
    SDL_PauseAudio(0);

    static Uint8* audio_chunk;
    uint8_t* out_buffer;
    struct SwrContext* au_convert_ctx;
    int audioStream = -1;
    int out_buffer_size = av_samples_get_buffer_size(NULL, 2, 1024, out_sample_fmt, 1);
    while (av_read_frame(ctx, packet) >= 0) {
        if (packet->stream_index == audioStreamIdx) {
            avcodec_send_packet(pCodecCtx, packet);
            while (avcodec_receive_frame(pCodecCtx, pFrame) == 0) {
                swr_convert(au_convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t**)pFrame->data, pFrame->nb_samples); // 转换音频
            }

            audio_chunk = (Uint8*)out_buffer;
            _audioLen = out_buffer_size;
            _audioPos = audio_chunk;

            while (_audioLen > 0) {
                SDL_Delay(1);//延迟播放
            }
        }
        av_packet_unref(packet);
    }

    swr_free(&au_convert_ctx);


    // 步骤五：播放完毕
    SDL_CloseAudio();
    SDL_Quit();
    printf("play is done");
    goto ERR_CLOSE;

    return 0;
}