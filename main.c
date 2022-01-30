#include <curses.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #include "audioPlay.h"

int repetition = 4;
typedef enum { PAUSE = 0, PAUSE_LONG = 1, POMODORO = 2 } MODE;
int timeArray[] = {5, 15, 25};

char *names[] = {
    "Pause",
    "Long puase",
    "Pomodoro",
};

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

  for (int msec = timeArray[m] * 60 * 1000; msec >= 0; msec--) {
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

int main(int argc, char *argv[]) {
  // delka pauzy, dlouhe pauzy, kratke, pomodora, option bell file
  int temp;
  int option;
  int option_index = 0;
  struct option long_options[] = {{"pomodoro", required_argument, 0, 'p'},
                                  {"short", required_argument, 0, 's'},
                                  {"pomodoro", required_argument, 0, 'l'},
                                  {"repetition", required_argument, 0, 'r'},
                                  {0, 0, 0, 0}};
  option = getopt_long(argc, argv, "p:s:l:r:", long_options, &option_index);
  switch (option) {
  case 'p':
    temp = atoi(optarg);
    timeArray[POMODORO] = temp;
  case 's':
    temp = atoi(optarg);
    timeArray[PAUSE] = temp;
  case 'l':
    temp = atoi(optarg);
    timeArray[PAUSE_LONG] = temp;
  case 'r':
    temp = atoi(optarg);
    repetition = temp;
  }
  // FILE* file;

  WINDOW *w = initscr();
  nodelay(w, FALSE);

  printw("Pomodoro\n"
         "#Controls\n"
         "Press:\n"
         "- 'q' for quit\n"
         "- 's' for skip\n"
         "\n"
         "Ready for pomodoro, press enter to start...");
  getch();

  bool program_run = true;

  while (program_run) {
    printw("Looping \n");

    for (int i = 0; i < repetition; i++) {
      run(w, POMODORO);

      if (i == repetition - 1) {
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
