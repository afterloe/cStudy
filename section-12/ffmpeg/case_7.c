#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#define INBUF_SIZE 4096

static int get_format_from_sample_fmt(const char** fmt,
    enum AVSampleFormat sample_fmt)
{
    int i;
    struct sample_fmt_entry {
        enum AVSampleFormat sample_fmt; const char* fmt_be, * fmt_le;
    } sample_fmt_entries[] = {
        { AV_SAMPLE_FMT_U8,  "u8",    "u8"    },
        { AV_SAMPLE_FMT_S16, "s16be", "s16le" },
        { AV_SAMPLE_FMT_S32, "s32be", "s32le" },
        { AV_SAMPLE_FMT_FLT, "f32be", "f32le" },
        { AV_SAMPLE_FMT_FLTP, "f32be", "f32le"},
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

extern void decode(SwrContext*, AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt);

static FILE* outfd;

int main(int argc, char** argv)
{
    // if (argc < 2)
    // {
    //     fprintf(stderr, "usage <%s> <input> <output> \n", argv[0]);
    //     return EXIT_FAILURE;
    // }

    // const char* input = argv[1];
    // const char* output = argv[2];

    // const char* input = "/home/afterloe/音乐/014-谭咏麟 - 讲不出再见.mp3";
    const char* input = "/home/afterloe/音乐/周杰伦-你听得到.flac";
    const char* output = "out.pcm";

    outfd = fopen(output, "wb+");

    AVFormatContext* ctx = NULL;
    int ret = avformat_open_input(&ctx, input, NULL, NULL);

    avformat_find_stream_info(ctx, NULL);
    int streamIdx = av_find_best_stream(ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

    // media file info
    printf("Input: %s \n", input);
    printf("Format: %s \n", ctx->iformat->name);
    printf("Duration: %lld seconds\n", ctx->duration / AV_TIME_BASE);
    AVDictionaryEntry* metadata = NULL;
    while ((metadata = av_dict_get(ctx->metadata, "", metadata, AV_DICT_IGNORE_SUFFIX)))
    {
        printf("%s=%s\n", metadata->key, metadata->value);
    }

    // begin decode
    AVStream* stream = ctx->streams[streamIdx];
    AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
    AVCodecParserContext* parserCtx = av_parser_init(codec->id);
    AVCodecContext* codecCtx = avcodec_alloc_context3(codec);
    avcodec_open2(codecCtx, codec, NULL);

    // 将信息复制到codecCtx内
    avcodec_parameters_to_context(codecCtx, stream->codecpar);

    FILE* fd = fopen(input, "rb");
    AVFrame* decoded_frame = av_frame_alloc();

    // 初始化采样器
    SwrContext* swr_ctx = swr_alloc();
    // input
    AVChannelLayout src_ch_layout = codecCtx->ch_layout;
    int src_rate = codecCtx->sample_rate;
    enum AVSampleFormat src_sample_fmt = codecCtx->sample_fmt;
    // output
    AVChannelLayout dst_ch_layout = AV_CHANNEL_LAYOUT_STEREO;
    int dst_rate = 48000;
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

    const int in_nb_samples = 2048;
    int out_nb_samples = av_rescale_rnd(in_nb_samples, dst_rate, codecCtx->sample_rate, AV_ROUND_UP);
    AVFrame* inFrame = av_frame_alloc();
    av_samples_alloc(inFrame->data, inFrame->linesize, src_ch_layout.nb_channels, in_nb_samples, codecCtx->sample_fmt, 1);
    AVFrame* outFrame = av_frame_alloc();
    av_samples_alloc(outFrame->data, outFrame->linesize, dst_ch_layout.nb_channels, out_nb_samples, dst_sample_fmt, 1);

    int in_spb = av_get_bytes_per_sample(codecCtx->sample_fmt);
    int out_spb = av_get_bytes_per_sample(dst_sample_fmt);

    int frameCnt = 0;
    for (;;)
    {
        int read_samples = fread(inFrame->data[0], in_spb * src_ch_layout.nb_channels, in_nb_samples, fd);
        if (read_samples <= 0)
        {
            break;
        }

        int dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, codecCtx->sample_rate) + in_nb_samples,
            dst_rate,
            codecCtx->sample_rate, AV_ROUND_UP);
        if (dst_nb_samples > out_nb_samples) {
            av_frame_unref(outFrame);
            out_nb_samples = dst_nb_samples;
            av_samples_alloc(outFrame->data, outFrame->linesize, dst_ch_layout.nb_channels, out_nb_samples, dst_sample_fmt, 1);
        }

        int out_samples = swr_convert(swr_ctx, outFrame->data, out_nb_samples, (const uint8_t**)inFrame->data,
            read_samples);

        

        // if (av_sample_fmt_is_planar(dst_sample_fmt)) {
        //     for (int i = 0; i < out_samples; i++) {
        //         for (int c = 0; c < dst_ch_layout.nb_channels; c++) {
        //             fwrite(outFrame->data[c] + i * out_spb, 1, out_spb, outfd);
        //         }
        //     }
        // }
        // else {
        //     fwrite(outFrame->data[0], out_spb * dst_ch_layout.nb_channels, out_samples, outfd);
        //     // for (int i = 0; i < out_samples; i++) {
        //     //     fwrite(outFrame->data[0] + i * out_spb, 1, out_spb, outfd);
        //     // }
        // }

        printf("Succeed to convert frame %4d, samples [%d]->[%d]\n", frameCnt++, read_samples, out_samples);
    }

    enum AVSampleFormat sfmt = codecCtx->sample_fmt;
    char* fmt;
    get_format_from_sample_fmt(&fmt, sfmt);
    fprintf(stdout, "Play the output audio file with the command:\n"
        "/usr/local/ffmpeg/bin/ffplay -f %s -ch_layout stereo -sample_rate %d -i %s\n",
        fmt, codecCtx->sample_rate, output);

    // 回收资源
    fclose(fd);
    fclose(outfd);
    swr_free(&swr_ctx);
    avcodec_free_context(&codecCtx);
    av_parser_close(parserCtx);
    av_frame_free(&decoded_frame);
    av_free(codecCtx);

    return EXIT_SUCCESS;
}

void decode(SwrContext* au_convert_ctx, AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt)
{
    int i, ch;
    int ret, data_size;


    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error sending a packet for decoding\n");
        exit(1);
    }

    while (ret >= 0) {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            return;
        }
        else if (ret < 0)
        {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }

        // int out_nb_samples = swr_get_out_samples(au_convert_ctx, frame->nb_samples);
        // int ret = swr_convert(au_convert_ctx, frame->data, out_nb_samples,
        //                       (const uint8_t **)frame->data, frame->nb_samples);

        data_size = av_get_bytes_per_sample(dec_ctx->sample_fmt);
        if (data_size < 0) {
            fprintf(stderr, "Failed to calculate data size\n");
            exit(1);
        }
        for (i = 0; i < frame->nb_samples; i++)
        {
            for (ch = 0; ch < dec_ctx->ch_layout.nb_channels; ch++) {
                if (frame->data[ch]) {
                    fwrite(frame->data[ch] + data_size * i, 1, data_size, outfd);
                }
            }
        }
    }

    av_packet_unref(pkt);
}