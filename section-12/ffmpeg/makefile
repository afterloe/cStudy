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
