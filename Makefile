CFLAGS = -Wall -lcurses -Lbass24-osx -lbass# Flag for implicit rules. Turn on debug info
ASAN_FLAGS = -fsanitize-address-use-after-return=(runtime) -fno-omit-frame-pointer -Wno-format-security
ASAN_SYMBOLIZER_PATH = /usr/local/opt/llvm-symbolizer

all: pomodoro
	./pomodoro

pomodoro: main.o audioPlay.o 
	$(CC) $(CFLAGS) main.c audioPlay.o -o pomodoro 

audioPlay.o: audioPlay.c
	gcc -c -Lbass24-osx -lbass audioPlay.c

clean:
	rm pomodoro
	rm *.o
