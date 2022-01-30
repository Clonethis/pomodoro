#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "audioPlay.h"

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
    return 3;
  case PAUSE_LONG:
    return 5;
  case POMODORO:
    return 25;
  }
}

char *name(MODE m) { return names[m]; }

void play_bell(MODE m) {
  switch (m) {
  case PAUSE:
    printf("\a");
    usleep(500000);
    printf("\a");
    break;
  case PAUSE_LONG:
    printf("\a");
    usleep(500000);
    printf("\a");
    break;
  case POMODORO:
    printf("\a");
    break;
  }
}

void run(WINDOW *w, MODE m) {
  nodelay(w, TRUE);

  for (int msec = duration(m) * 60 * 1000; msec >= 0; msec--) {
    if (msec % 1000 == 0) {
      clear();
      int sec = msec / 1000;
      printw("%s %d:%02d\n", name(m), sec / 60, sec % 60);
    }

    usleep(1000);

    char c;
    bool skip = false;
    while ((c = getch()) != ERR) {
      if (c == 'q') {
        endwin();
        exit(0);
      }
      if (c == 's') {
        skip = true;
      }
    }

    if (skip) {
      break;
    }
  }

  nodelay(w, FALSE);

  clear();
  play_bell(m);
  printw("%s ended. Press a key to continue...\n", name(m));
  getch();
}

int main(void) {
  WINDOW *w = initscr();
  nodelay(w, FALSE);

  printw("Pomodoro\n"
         "\n"
         "# Controls\n"
         "Press:\n"
         " - 'q' for quit\n"
         " - 's' for skip\n"
         "\n"
         "Ready for pomodoro, press enter to start...");
  getch();

  bool program_run = true;

  while (program_run) {
    printw("Looping \n");

    for (int i = 0; i < REPETITION_COUNT; i++) {
      run(w, POMODORO);

      if (i == REPETITION_COUNT - 1) {
        program_run = false;
        break;
      }

      run(w, PAUSE);
    }

    run(w, PAUSE_LONG);
  }

  endwin();
  return 0;
}
