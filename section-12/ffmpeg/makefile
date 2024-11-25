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

build:
	g++ $(CFLAGS) -c -o dist/a.o case_5.cc
	g++ dist/a.o $(LDLIBS) -o dist/a

clean:
	rm -rf dist/*
