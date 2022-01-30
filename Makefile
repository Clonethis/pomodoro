CFLAGS = -Wall -lcurses# Flag for implicit rules. Turn on debug info
ASAN_FLAGS = -fsanitize-address-use-after-return=(runtime) -fno-omit-frame-pointer -Wno-format-security
ASAN_SYMBOLIZER_PATH = /usr/local/opt/llvm-symbolizer

all: pomodoro
	./pomodoro  -s 2 
pomodoro: main.c 
	gcc $(CFLAGS) main.c -o pomodoro 
clean:
	rm pomodoro
