CFLAGS = -Wall
EX_FLAGS = -lcurses -Lbass24-osx -lbass
ASAN_FLAGS = -fsanitize-address-use-after-return=(runtime) -fno-omit-frame-pointer -Wno-format-security
ASAN_SYMBOLIZER_PATH = /usr/local/opt/llvm-symbolizer

all: pomodoro
	./pomodoro

pomodoro: main.o audioPlay.o 
	$(CC) $(EX_FLAGS) main.c audioPlay.o -o pomodoro 

clean:
	rm pomodoro
	rm *.o
