#include <stdio.h>
#include <libavutil/log.h>
#include <stdlib.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <SDL2/SDL.h>
typedef struct _VideoState {
    AVCodecContext* avCtx;
    AVPacket* pkt;
    AVFrame* frame;
    SDL_Texture* texture;
} VideoState;
static int w_width = 640;
static int w_height = 480;
static SDL_Window* win = NULL;
static SDL_Renderer* renderer = NULL;
static Uint32 pix_format = 0;
static void render(VideoState* vs) {
    SDL_UpdateYUVTexture(vs->texture, NULL,
        vs->frame->data[0],
        vs->frame->linesize[0],
        vs->frame->data[1],
        vs->frame->linesize[1],
        vs->frame->data[2],
        vs->frame->linesize[2]);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, vs->texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

static int decode(VideoState* vs) {
    int ret = -1;
    ret = avcodec_send_packet(vs->avCtx, vs->pkt);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "failed to send packet to decoder: %s \n", av_err2str(ret));
        goto __OUT;
    }

    while (ret >= 0) {
        ret = avcodec_receive_frame(vs->avCtx, vs->frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            ret = 0;
            goto __OUT;
        }
        else if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "failed to receive packet to decoder: %s \n", av_err2str(ret));
            ret = -1;
            goto __OUT;
        }
        render(vs);
    }
__OUT:
    return ret;
}

int main(int argc, char* argv[]) {
    char* src;
    int ret = -1;
    int index = -1;
    int video_width = 0;
    int video_height = 0;
    AVFormatContext* pFmtCtx = NULL;
    AVStream* inStream = NULL;
    SDL_Texture* texture = NULL;
    const AVCodec* dec = NULL;
    AVCodecContext* ctx = NULL;
    AVPacket* pkt = NULL;
    AVFrame* frame = NULL;
    VideoState* vs = NULL;
    SDL_Event event;

    //1. 判断输入参数
    av_log_set_level(AV_LOG_DEBUG);
    if (argc < 2) {
        av_log(NULL, AV_LOG_INFO, "arguments must be more than 2\n");
        exit(-1);
    }
    src = argv[1];
    vs = av_mallocz(sizeof(VideoState));
    if (!vs) {
        av_log(NULL, AV_LOG_ERROR, "no memory\n");
        goto __END;
    }
    //2. 初始化SDL，并创建窗口和Render
    //2.1 initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }

    //2.2 creat window from SDL
    win = SDL_CreateWindow("Simple Player",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        w_width, w_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!win) {
        fprintf(stderr, "Failed to create window, %s\n", SDL_GetError());
        goto __END;
    }

    //2.3
    renderer = SDL_CreateRenderer(win, -1, 0);

    //3. 打开多媒体文件，并获得流信息
    ret = avformat_open_input(&pFmtCtx, src, NULL, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "%s\n", av_err2str(ret));
        goto __END;
    }
    //3.2
    ret = avformat_find_stream_info(pFmtCtx, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "%s\n", av_err2str(ret));
        goto __END;
    }

    //4. 查找最好的视频流
    index = av_find_best_stream(pFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (index < 0) {
        av_log(pFmtCtx, AV_LOG_ERROR, "does not include video stream \n");
        goto __END;
    }

    //5. 根据流中的codec_id, 获得解码器
    inStream = pFmtCtx->streams[index];
    dec = avcodec_find_decoder(inStream->codecpar->codec_id);
    if (!dec) {
        av_log(NULL, AV_LOG_ERROR, "don't find Codec: libx264\n");
        goto __END;
    }
    //6. 创建解码器上下文
    ctx = avcodec_alloc_context3(dec);
    if (!ctx) {
        av_log(NULL, AV_LOG_ERROR, "no memory!\n");
        goto __END;
    }

    //7. 从视频流中拷贝解码器参数到解码器上下文中
    ret = avcodec_parameters_to_context(ctx, inStream->codecpar);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "could not copy codecpar to codec ctx!\n");
        goto __END;
    }
    //8. 绑定解码器上下文
    ret = avcodec_open2(ctx, dec, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "don't open codec %s\n", av_err2str(ret));
        goto __END;
    }
    //9. 根据视频的宽/高创建纹理
    pix_format = SDL_PIXELFORMAT_IYUV;

    //create texture for render
    video_height = ctx->height;
    video_width = ctx->width;
    // texture = SDL_CreateTexture(renderer,
    //     pix_format,
    //     SDL_TEXTUREACCESS_STREAMING,
    //     video_width,
    //     video_height);
    // if (!texture) {
    //     SDL_Log("failed to create Texture");
    //     goto __END;
    // }

    //10. 从多媒体文件中读取数据，进行解码
    //10.1
    frame = av_frame_alloc();
    if (!frame) {
        av_log(NULL, AV_LOG_ERROR, "no memory\n");
        goto __END;
    }
    //10.2
    pkt = av_packet_alloc();
    if (!pkt) {
        av_log(NULL, AV_LOG_ERROR, "no memory\n");
        goto __END;
    }

    vs->texture = texture;
    vs->avCtx = ctx;
    vs->pkt = pkt;
    vs->frame = frame;

    while (av_read_frame(pFmtCtx, pkt) >= 0) {
        if (pkt->stream_index == index) {
            //11. 对解码后的视频帧进行渲染
            decode(vs);
        }
        //12. 处理SDL事件
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            goto __QUIT;
        default:break;
        }
        av_packet_unref(pkt);
    }
    vs->pkt = NULL;
    decode(vs);
__QUIT:
    ret = 0;
__END:
    //12. 收尾，释放资源
    if (frame) {
        av_frame_free(&frame);
    }

    if (pkt) {
        av_packet_free(&pkt);
    }

    if (ctx) {
        avcodec_free_context(&ctx);
    }

    if (pFmtCtx) {
        avformat_close_input(&pFmtCtx);
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    if (texture) {
        SDL_DestroyTexture(texture);
    }

    if (win) {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
    printf("Hello, World!\n");
    return ret;
}
