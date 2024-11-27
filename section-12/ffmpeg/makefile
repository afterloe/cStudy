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

SRC = case_7

.PHONY: all build clean

build:
	$(CC) $(CFLAGS) -c -o $(SRC).o $(SRC).c
	$(CC) $(SRC).o $(LDLIBS) -o $(SRC)

clean:
	rm -rf $(SRC).o $(SRC)
