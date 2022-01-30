#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

const int REPETITION_COUNT = 4;

typedef enum { PAUSE = 0, PAUSE_LONG = 1, POMODORO = 2 } MODE;

char *names[] = {
    "Pause",
    "Long puase",
    "Pomodoro",
};

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

char *name(MODE m) { return names[m]; }

void run(WINDOW *w, MODE m) {
  nodelay(w, TRUE);

  int minutes = duration(m);

  printw("Starting %s\n", name(m));
  for (int sec = 0; sec < minutes / 5; sec++) {
    sleep(1);
    clear();
    printw("%s %d:%02d\n", name(m), sec / 60, sec);

    char c;
    while ((c = getch()) != ERR) {
      if (c == 'q')
        endwin();
      exit(0);
    }
  }
  printf("\a%s ended\n", name(m));

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
      run(w, POMODORO);
      printw("waiting on enter\n");
      getch();

      if (i == REPETITION_COUNT - 1) {
        program_run = false;
        break;
      }

      run(w, PAUSE);
      printw("waiting on enter,to start again\n");
    }

    run(w, PAUSE_LONG);
    printw("nice end\n");
    getch();
  }

  endwin();
  return 0;
}
