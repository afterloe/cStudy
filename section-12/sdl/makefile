SDL_2=  sdl2 \

FFMPEG_LIBS=     libavdevice                        \
                 libavformat                        \
                 libavfilter                        \
                 libavcodec                         \
                 libswresample                      \
                 libswscale                         \
                 libavutil                          \
 
CFLAGS += -Wall -g
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
CFLAGS := $(shell pkg-config --cflags $(SDL_2)) $(CFLAGS)

LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)
LDLIBS := $(shell pkg-config --libs $(SDL_2)) $(LDLIBS)

SRC = case_9

.PHONY: all build clean run

build:
	$(CC) $(CFLAGS) -c -o $(SRC).o $(SRC).c
	$(CC) $(SRC).o $(LDLIBS) -o $(SRC)

clean:
	$(RM) -rf $(SRC).o $(SRC)

define run-task
./case_9 /home/afterloe/音乐/莫文蔚-如果没有你.flac out.pcm
/usr/local/ffmpeg/bin/ffplay -f s16le -ch_layout stereo -sample_rate 44100 -i out.pcm
endef

run:
	$(run-task)
