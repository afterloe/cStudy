#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

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
    const char* filename = "/home/afterloe/音乐/周杰伦-你听得到.flac";
    const char* output = "out.pcm";

    outfd = fopen(output, "wb+");

    AVFormatContext* ctx = NULL;
    int ret = avformat_open_input(&ctx, filename, NULL, NULL);

    avformat_find_stream_info(ctx, NULL);
    int streamIdx = av_find_best_stream(ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

    // media file info
    printf("Input: %s \n", filename);
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

    FILE* fd = fopen(filename, "rb");
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


    int frameCnt = 0;
    uint8_t* data;
    uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE] = { 0 };
    data = inbuf;
    AVPacket* pkt = av_packet_alloc();
    size_t len = fread(inbuf, 1, AUDIO_INBUF_SIZE, fd);
    AVFrame* src_frame = av_frame_alloc();
    uint8_t** dst_data = NULL;
    int dst_linesize, dst_nb_samples, max_dst_nb_samples;
    max_dst_nb_samples = dst_nb_samples =
        av_rescale_rnd(1024, dst_rate, src_rate, AV_ROUND_UP);
    ret = av_samples_alloc_array_and_samples(&dst_data, &dst_linesize, dst_ch_layout.nb_channels,
        dst_nb_samples, dst_sample_fmt, 0);
    int dst_bufsize;
    for (;;)
    {
        ret = av_parser_parse2(parserCtx, codecCtx, &pkt->data, &pkt->size, data, len, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        if (ret < 0)
        {
            fprintf(stdout, "can't parse %s \n", filename);
            exit(1);
        }
        data += ret;
        len -= ret;

        if (!pkt->size)
        {
            fprintf(stdout, "can't read any info \n");
            exit(1);
        }


        ret = avcodec_send_packet(codecCtx, pkt);
        if (ret < 0) {
            fprintf(stderr, "Error submitting the packet to the decoder\n");
            exit(1);
        }
        while (ret >= 0) {
            ret = avcodec_receive_frame(codecCtx, src_frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                return;
            }
            else if (ret < 0) {
                fprintf(stderr, "Error during decoding\n");
                exit(1);
            }
            int src_nb_samples = av_get_bytes_per_sample(codecCtx->sample_fmt);
            if (src_nb_samples < 0) {
                fprintf(stderr, "Failed to calculate data size\n");
                exit(1);
            }
            dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, src_rate) +
                src_nb_samples, dst_rate, src_rate, AV_ROUND_UP);
            if (dst_nb_samples > max_dst_nb_samples) {
                av_freep(&dst_data[0]);
                ret = av_samples_alloc(dst_data, &dst_linesize, dst_ch_layout.nb_channels,
                    dst_nb_samples, dst_sample_fmt, 1);
                if (ret < 0)
                    break;
                max_dst_nb_samples = dst_nb_samples;
            }

            ret = swr_convert(swr_ctx, dst_data, dst_nb_samples, (const uint8_t**)src_frame->data, src_frame->nb_samples);
            if (ret < 0) {
                fprintf(stderr, "Error while converting\n");
                exit(1);
            }
            dst_bufsize = av_samples_get_buffer_size(&dst_linesize, dst_ch_layout.nb_channels,
                ret, dst_sample_fmt, 1);
            if (dst_bufsize < 0) {
                fprintf(stderr, "Could not get sample buffer size\n");
                exit(1);
            }
            fwrite(dst_data[0], 1, dst_bufsize, outfd);
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