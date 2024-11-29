/**
 * FFmpeg + SDL play *.pcm
 */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_types.h>
#include "SDL.h"

// 每次读取2帧数据, 以1024个采样点一帧 2通道 16bit采样点为例
#define PCM_BUFFER_SIZE (2 * 1024 * 2 * 2)

static Uint8* s_audio_buf = NULL;   // 存储当前读取的两帧数据
static Uint8* s_audio_pos = NULL;   // 目前读取的位置
static Uint8* s_audio_end = NULL;   // 缓存结束位置

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
    // 设置混音
    SDL_MixAudio(stream, s_audio_pos, len, SDL_MIX_MAXVOLUME);  // 音量的值 SDL_MIX_MAXVOLUME 128

    s_audio_pos += len;  // 移动缓存指针（当前pos）
}

int main(int argc, char** argv)
{
    char* filename = argv[1];

    int ret = -1;
    // int out_nb_samples = 1024;
    // int out_sample_rate = 44100;

    SDL_AudioSpec spec;
    spec.freq = 48000;     // 指定了每秒向音频设备发送的sample数。常用的值为：11025，22050，44100。值越高质量越好。
    spec.format = AUDIO_F32LSB; // 每个sample的大小
    spec.channels = 2; // 1 单通道 - 2双通道
    spec.silence = 0;
    spec.samples = 1024; // 这个值表示音频缓存区的大小（以sample计）。一个sample是一段大小为 format * channels 的音频数据。
    spec.callback = fill_audio_pcm;
    spec.userdata = NULL;

    // 步骤一：初始化音频子系统
    ret = SDL_Init(SDL_INIT_AUDIO);
    if (ret)
    {
        printf("can't init SDL \n");
        goto ERR_CLOSE;
    }

    // 步骤二：打开音频设备
    ret = SDL_OpenAudio(&spec, 0);
    if (ret < 0)
    {
        printf("can't open SDL \n");
        goto ERR_CLOSE;
    }
    s_audio_buf = malloc(PCM_BUFFER_SIZE);

    // 步骤三：开始播放
    SDL_PauseAudio(0);

    size_t read_buffer_len = 0;
    FILE* src = fopen(filename, "rb");
    if (src == NULL)
    {
        printf("read file \n");
        goto ERR_CLOSE;
    }
    int data_count = 0;
    while (1)
    {
        read_buffer_len = fread(s_audio_buf, 1, PCM_BUFFER_SIZE, src);
        if (0 == read_buffer_len)
        {
            break;
        }
        data_count += read_buffer_len;

        printf("read %10d KB \n", read_buffer_len / 1024);
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

    printf("play finish \n");

    if (s_audio_buf)
    {
        free(s_audio_buf);
    }

    SDL_CloseAudio();
    fclose(src);
    SDL_Quit();


ERR_CLOSE:
    perror("record:");
    exit(EXIT_FAILURE);

    return EXIT_SUCCESS;
}