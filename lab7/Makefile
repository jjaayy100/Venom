CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

all: snake

snake: snake.cpp log.cpp ybond.cpp dware.cpp jambriz.cpp jbankston.cpp ptakkar.cpp help.cpp help.h
	g++ $(CFLAGS) snake.cpp log.cpp ybond.cpp help.cpp jambriz.cpp dware.cpp jbankston.cpp ptakkar.cpp libggfonts.a \
	/usr/lib/x86_64-linux-gnu/libopenal.so \
	/usr/lib/x86_64-linux-gnu/libalut.so \
	-Wall -Wextra $(LFLAGS) -o snake

clean:
	rm -f snake
	rm -f *.o

