#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

typedef enum { PAUSE, PAUSE_LONG, POMODORO } MODE;

int duration(MODE m) {
  switch (m) {
  case PAUSE:
    return 5;
  case PAUSE_LONG:
    return 15;
  case POMODORO:
    return 25;
  }
}

const int REPETITION_COUNT = 4;

void run(WINDOW *w, char *mode, MODE m) {
  nodelay(w, TRUE);

  int minutes = duration(m);

  printw("Starting %s\n", mode);
  for (int sec = 0; sec < minutes / 5; sec++) {
    sleep(1);
    clear();
    printw("%s %d:%02d\n", mode, sec / 60, sec);

    char c;
    while ((c = getch()) != ERR) {
      if (c == 'q')
        endwin();
      exit(0);
    }
  }
  printf("\a%s ended\n", mode);

  nodelay(w, FALSE);
}

int main(void) {
  WINDOW *w = initscr();
  nodelay(w, FALSE);

  bool program_run = true;

  printw("Starting pomodoro, waiting on enter...\n");
  getch();

  while (program_run) {
    printw("Looping \n");

    for (int i = 0; i < REPETITION_COUNT; i++) {
      run(w, "Pomodoro:", POMODORO);
      printw("waiting on enter\n");
      getch();

      if (i == REPETITION_COUNT - 1) {
        program_run = false;
        break;
      }

      run(w, "Pause:", PAUSE);
      printw("waiting on enter,to start again\n");
    }

    run(w, "PauseLong:", PAUSE_LONG);
    printw("nice end\n");
    getch();
  }

  endwin();
  return 0;
}
