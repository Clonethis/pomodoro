all: pomodoro
	gcc main.c -o pomodoro
	./pomodoro

clean:
	rm pomodoro
