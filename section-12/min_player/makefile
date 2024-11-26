SDL_2 =  sdl2 \

FFMPEG_LIBS =     libavdevice                        \
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

APP = minplayer

CFLAGS := ./include \
    $(CFLAGS)
    
SRC = minplayer \

OBJS = $(addsuffix .o, $(SRC))

.PHONY: all build clean

all: $(OBJS) $(SRC)

build: $(OBJS) 
	$(CC) $(OBJS) $(LDLIBS) -o $(APP)

.ONESHELL:
clean:
	$(RM) $(SRC) $(OBJS) $(APP)