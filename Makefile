all: pomodoro
	./pomodoro

pomodoro:
	gcc main.c -o pomodoro


clean:
	rm pomodoro
