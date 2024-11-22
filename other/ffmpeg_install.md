Linux 下编译ffmpeg
===

## SDL2.x
SDL是编译 ffplayer 所必须的外部库，而 Ubuntu 环境并不会对其默认安装，故而需要用户手动安装
> https://github.com/libsdl-org/SDL/releases/tag/release-2.30.9 

```shell
wget https://objects.githubusercontent.com/github-production-release-asset-2e65be/330008801/97bea7bc-7dce-4dd2-bc06-f250351e81ea?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=releaseassetproduction%2F20241121%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20241121T080606Z&X-Amz-Expires=300&X-Amz-Signature=5ca1a3058ab3ea879969ae6def97fcbf94b8d12637cecba39889aa117c06204c&X-Amz-SignedHeaders=host&response-content-disposition=attachment%3B%20filename%3DSDL2-2.30.9.tar.gz&response-content-type=application%2Foctet-stream

tar -xzvf SDL2-2.30.9.tar.gz
cd SDL2-2.30.9

./configure --prefix=/usr/local
sudo make -j4
sudo make install

# 动态库
cd /usr/local/lib
ls | grep SDL

libSDL2-2.0.so.0
libSDL2-2.0.so.0.3000.9
libSDL2.a

# 头文件
cd /usr/local/include/SDL2
```
安装位置在 `/usr/local` 下

## FFmpeg

### 前置依赖
```shell
sudo apt-get update -qq && sudo apt-get -y install \
  autoconf \
  automake \
  build-essential \
  cmake \
  git-core \
  libass-dev \
  libfreetype6-dev \
  libgnutls28-dev \
  libmp3lame-dev \
  libsdl2-dev \
  libtool \
  libva-dev \
  libvdpau-dev \
  libvorbis-dev \
  libxcb1-dev \
  libxcb-shm0-dev \
  libxcb-xfixes0-dev \
  meson \
  ninja-build \
  pkg-config \
  texinfo \
  wget \
  yasm \
  zlib1g-dev

# 插件 h264/5 
sudo apt-get install nasm, libx264-dev, libx265-dev libnuma-dev \
    libvpx-dev libfdk-aac-dev, libopus-dev 

# 可选 AV1
sudo apt install libsvtav1-dev libsvtav1enc-dev libsvtav1dec-dev \
    libdav1d-dev
```

### 配置FFmpeg
```shell
git clone git@github.com:FFmpeg/FFmpeg.git
cd FFmpeg

./configure \
  --prefix="/usr/local/ffmpeg" \
  --pkg-config-flags="--static" \
  --extra-cflags="-I/usr/local/ffmpeg/include" \
  --extra-ldflags="-L/usr/local/ffmpeg/lib" \
  --extra-libs="-lpthread -lm" \
  --ld="g++" \
  --bindir="/usr/local/ffmpeg/bin" \
  --enable-gpl \
  --enable-gnutls \
  --disable-libaom \
  --enable-libass \
  --enable-libfdk-aac \
  --enable-libfreetype \
  --enable-libmp3lame \
  --enable-libopus \
  --disable-libsvtav1 \
  --disable-libdav1d \
  --enable-libvorbis \
  --enable-libvpx \
  --enable-libx264 \
  --enable-libx265 \
  --enable-nonfree

sudo make -j8
sudo make install
hash -r
```
安装位置在 `/usr/local/ffmpeg`

> `--pkg-config-flags="--shared"`  为动态库， 这里采用静态库

* **头文件**: `/usr/local/ffmpeg/include`
* **库**: `/usr/local/ffmpeg/lib`

### 更新pkg-config
方式一： profile添加
```shell
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/ffmpeg/lib/pkgconfig
export PKG_CONFIG_PATH
```

方式二： 软连接
```shell
cd /usr/share/pkgconfig
sudo ln -s /usr/local/ffmpeg/lib/pkgconfig/*.pc .
```

### 测试

#### pkg-config 测试
```shell
pkg-config --cflags  libavcodec
-I/usr/local/ffmpeg/include

pkg-config --libs  libavcodec
-L/usr/local/ffmpeg/lib -lavcodec -lvpx -lm -lfdk-aac -lmp3lame -lopus -lvorbisenc -lvorbis -logg -lx264 -lx265 -lstdc++ -lgcc_s -lgcc -lrt -ldl -lnuma -lz -lswresample -lavutil -pthread -lva-drm -lva-x11 -lvdpau -ldrm -lm -lva -latomic -lX11 -lpthread -lxcb -lXau -lXdmcp
```

#### 代码测试
```shell
echo '
#include <libavcodec/avcodec.h>


int main()
{
    printf("test ffmpeg \\n");
    const char *license = avcodec_license();
    printf("%s \\n", license);
    return 0;
}
' > test_ffmpeg.c

cc `pkg-config --cflags libavcodec` -c -o test_ffmpeg.o test_ffmpeg.c
cc test_ffmpeg.o `pkg-config --libs libavcodec` -o test_ffmpeg

./test_ffmpeg
test ffmpeg 
nonfree and unredistributable

rm -rf test_ffmpeg.*
```

### Makefile

多文件 - 官方
```Makefile
# use pkg-config for getting CFLAGS and LDLIBS
FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \

CFLAGS += -Wall -g
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)

# missing the following targets, since they need special options in the FFmpeg build:
# qsv_decode
# qsv_transcode
# vaapi_encode
# vaapi_transcode

EXAMPLES=\
		 case_4
#                avio_http_serve_files              \
#                avio_list_dir                      \
#                avio_read_callback                 \
                decode_audio                       \
                decode_filter_audio                \
                decode_filter_video                \
                decode_video                       \
                demux_decode                       \
                encode_audio                       \
                encode_video                       \
                extract_mvs                        \
                hw_decode                          \
                mux                                \
                remux                              \
                resample_audio                     \
                scale_video                        \
                show_metadata                      \
                transcode_aac                      \
                transcode

OBJS=$(addsuffix .o,$(EXAMPLES))

# the following examples make explicit use of the math library
avcodec:           LDLIBS += -lm
encode_audio:      LDLIBS += -lm
mux:               LDLIBS += -lm
resample_audio:    LDLIBS += -lm

.phony: all clean-test clean

all: $(OBJS) $(EXAMPLES)

clean-test:
	$(RM) test*.pgm test.h264 test.mp2 test.sw test.mpg

clean: clean-test
	$(RM) $(EXAMPLES) $(OBJS)
```

单文件
```Makefile
FFMPEG_LIBS=     libavdevice                        \
                 libavformat                        \
                 libavfilter                        \
                 libavcodec                         \
                 libswresample                      \
                 libswscale                         \
                 libavutil                          \
 
CFLAGS += -Wall -g
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)

.PHONY: all build clean

build:
	g++ $(CFLAGS) -c -o dist/a.o case_4.cc
	g++ dist/a.o $(LDLIBS) -o dist/a

clean:
	rm -rf dist/*
```

