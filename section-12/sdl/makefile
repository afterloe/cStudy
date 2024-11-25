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

.PHONY: all build clean

all: clean

build:
	$(CC) $(CFLAGS) -c -o case_6.o case_5.c
	$(CC) case_6.o $(LDLIBS) -o case_7

clean:
	rm -rf *.o
