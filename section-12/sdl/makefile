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


SRC = case_5 \

OBJS = $(addsuffix .o, $(SRC))

.PHONY: all build clean

all: $(OBJS) $(SRC)

build:
	$(CC) $(CFLAGS) -c -o case_4.o case_9.c
	$(CC) case_4.o $(LDLIBS) -o case_4

clean:
	$(RM) $(SRC) $(OBJS)
