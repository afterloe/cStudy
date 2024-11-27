#include <stdio.h>
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

int main() {
    // 输入文件和参数
    FILE *in_file = fopen("input.pcm", "rb");
    const int in_sample_rate = 44100;
    AVSampleFormat in_sfmt = AV_SAMPLE_FMT_S16;
    uint64_t in_channel_layout = AV_CH_LAYOUT_STEREO;
    int in_channels = av_get_channel_layout_nb_channels(in_channel_layout);
    const int in_nb_samples = 2048;
    int in_spb = av_get_bytes_per_sample(in_sfmt);

    // 输出文件和参数
    FILE *out_file = fopen("output.pcm", "wb");
    const int out_sample_rate = 48000;
    AVSampleFormat out_sfmt = AV_SAMPLE_FMT_S32P;
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
    int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
    int out_nb_samples = av_rescale_rnd(in_nb_samples, out_sample_rate, in_sample_rate, AV_ROUND_UP);
    int out_spb = av_get_bytes_per_sample(out_sfmt);

    // 分配输入和输出帧
    AVFrame *in_frame = av_frame_alloc();
    av_samples_alloc(in_frame->data, in_frame->linesize, in_channels, in_nb_samples, in_sfmt, 1);
    AVFrame *out_frame = av_frame_alloc();
    av_samples_alloc(out_frame->data, out_frame->linesize, out_channels, out_nb_samples, out_sfmt, 1);

    // 初始化SwrContext
    SwrContext *swr_ctx = swr_alloc_set_opts(NULL,
                                             out_channel_layout, out_sfmt, out_sample_rate,
                                             in_channel_layout, in_sfmt, in_sample_rate,
                                             0, NULL);
    swr_init(swr_ctx);

    // 转换和保存音频数据
    int frameCnt = 0;
    while (1) {
        int read_samples = fread(in_frame->data[0], in_spb * in_channels, in_nb_samples, in_file);
        if (read_samples <= 0) break;

        int dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, in_sample_rate) + in_nb_samples,
                                            out_sample_rate,
                                            in_sample_rate, AV_ROUND_UP);
        if (dst_nb_samples > out_nb_samples) {
            av_frame_unref(out_frame);
            out_nb_samples = dst_nb_samples;
            av_samples_alloc(out_frame->data, out_frame->linesize, out_channels, out_nb_samples, out_sfmt, 1);
        }

        int out_samples = swr_convert(swr_ctx, out_frame->data, out_nb_samples, (const uint8_t **) in_frame->data,
                                      read_samples);

        if (av_sample_fmt_is_planar(out_sfmt)) {
            for (int i = 0; i < out_samples; i++) {
                for (int c = 0; c < out_channels; c++) {
                    fwrite(out_frame->data[c] + i * out_spb, 1, out_spb, out_file);
                }
            }
        } else {
            fwrite(out_frame->data[0], out_spb * out_channels, out_samples, out_file);
        }

        printf("Succeed to convert frame %4d, samples [%d]->[%d]\n", frameCnt++, read_samples, out_samples);
    }

    // 释放资源
    av_frame_free(&in_frame);
    av_frame_free(&out_frame);
    swr_free(&swr_ctx);
    fclose(in_file);
    fclose(out_file);

    return 0;
}
