#include <stdlib.h>
#include <stdio.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>



void convert_flac_to_pcm(const char* input_filename, const char* output_filename) {
    AVFormatContext* format_ctx = NULL;
    AVCodecContext* codec_ctx = NULL;
    AVCodec* codec = NULL;
    AVPacket packet;
    AVFrame* frame = NULL;
    SwrContext* swr_ctx = NULL;
    AVFrame* pcm_frame = NULL;
    FILE* output_file = NULL;

    av_register_all();
    avformat_network_init();

    // Open input file
    if (avformat_open_input(&format_ctx, input_filename, NULL, NULL) != 0) {

        return;
    }

    // Retrieve stream information
    if (avformat_find_stream_info(format_ctx, NULL) < 0) {

        return;
    }

    // Find the first audio stream
    AVCodecParameters* codec_params = NULL;
    int audio_stream_index = -1;
    for (unsigned int i = 0; i < format_ctx->nb_streams; i++) {
        if (format_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_index = i;
            codec_params = format_ctx->streams[i]->codecpar;
            break;
        }
    }

    if (audio_stream_index == -1) {

        return;
    }

    // Find the decoder for the audio stream
    codec = avcodec_find_decoder(codec_params->codec_id);
    if (codec == NULL) {

        return;
    }

    // Allocate codec context for the decoder
    codec_ctx = avcodec_alloc_context3(codec);
    if (avcodec_parameters_to_context(codec_ctx, codec_params) < 0) {

        return;
    }

    // Open codec
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {

        return;
    }

    // Allocate AVFrame structure
    frame = av_frame_alloc();
    if (frame == NULL) {

        return;
    }

    // Initialize SWR context for resampling
    SwrContext* swr_ctx = swr_alloc_set_opts(
        NULL,
        AV_SAMPLE_FMT_S16, // Target sample format (PCM 16-bit)
        AV_CH_LAYOUT_STEREO, // Target channel layout (stereo)
        44100, // Target sample rate (44.1 kHz)
        codec_ctx->sample_fmt, // Source sample format
        codec_ctx->ch_layout, // Source channel layout
        codec_ctx->sample_rate, // Source sample rate
        0, NULL
    );
    swr_init(swr_ctx);

    // Allocate PCM frame
    pcm_frame = av_frame_alloc();
    if (pcm_frame == NULL) {

        return;
    }

    pcm_frame->format = AV_SAMPLE_FMT_S16;
    pcm_frame->ch_layout = AV_CHANNEL_LAYOUT_STEREO;
    pcm_frame->channels = av_get_channel_layout_nb_channels(pcm_frame->channel_layout);
    pcm_frame->sample_rate = 44100;

    // Allocate buffer for PCM data
    int num_bytes = av_samples_get_buffer_size(NULL, pcm_frame->channels, pcm_frame->nb_samples, pcm_frame->format, 1);
    uint8_t** pcm_data = av_malloc(av_samples_get_buffer_size(NULL, pcm_frame->channels, pcm_frame->nb_samples, pcm_frame->format, 1));
    av_frame_unref(pcm_frame);
    avcodec_fill_audio_frame(pcm_frame, pcm_frame->channels, pcm_frame->format, pcm_data, num_bytes, 0);

    // Open output file
    output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        std::cerr << "Could not open output file: " << output_filename << std::endl;
        return;
    }

    // Read frames from the input file
    while (av_read_frame(format_ctx, &packet) >= 0) {
        if (packet.stream_index == audio_stream_index) {
            // Decode audio frame
            if (avcodec_send_packet(codec_ctx, &packet) == 0) {
                while (avcodec_receive_frame(codec_ctx, frame) == 0) {
                    // Convert the decoded frame to PCM
                    swr_convert(swr_ctx, pcm_data, pcm_frame->nb_samples, (const uint8_t**)frame->data, frame->nb_samples);

                    // Write PCM data to output file
                    fwrite(pcm_data[0], 1, av_samples_get_buffer_size(NULL, pcm_frame->channels, pcm_frame->nb_samples, pcm_frame->format, 1), output_file);
                }
            }
        }
        av_packet_unref(&packet);
    }

    // Clean up
    fclose(output_file);
    av_frame_free(&frame);
    av_frame_free(&pcm_frame);
    avcodec_free_context(&codec_ctx);
    swr_free(&swr_ctx);
    avformat_close_input(&format_ctx);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_flac_file> <output_pcm_file>" << std::endl;
        return 1;
    }

    convert_flac_to_pcm(argv[1], argv[2]);

    return 0;
}
