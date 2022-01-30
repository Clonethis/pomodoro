#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

const int PAUSE_MIN = 5;
const int PAUSE_LONG_MIN = 15;
const int POMODORO_MIN = 25;
const int REPETITION_COUNT = 4;

void run(char *mode, int minutes) {
  printf("Starting %s\n", mode);
  for (int sec = 0; sec < minutes / 5; sec++) {
    sleep(1);
    printf("sec: %d\n", sec);
  }
  printf("\a%s ended\n", mode);
  fflush(stdin);
}

void setup_nonbuffering_IO() {
  struct termios old_tio, new_tio;

  /* get the terminal settings for stdin */
  tcgetattr(STDIN_FILENO, &old_tio);

  /* we want to keep the old setting to restore them a the end */
  new_tio = old_tio;

  /* disable canonical mode (buffered i/o) and local echo */
  new_tio.c_lflag &= (~ICANON & ~ECHO);

  /* set the new settings immediately */
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

  /* restore the former settings */
  // tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
}

void waitJirka() {
  scanf(" ");
  fflush(stdin);
}

int main(void) {
  bool program_run = true;
  setup_nonbuffering_IO();

  printf("Starting pomodoro, waiting on enter...\n");
  waitJirka();

  while (program_run) {
    printf("Looping \n");

    for (int i = 0; i < REPETITION_COUNT; i++) {
      run("Pomodoro:", POMODORO_MIN);
      printf("waiting on enter");
      waitJirka();

      if (i == REPETITION_COUNT - 1) {
        program_run = false;
        break;
      }

      run("Pause:", PAUSE_MIN);
      printf("waiting on enter,to start again\n");
    }

    run("PauseLong:", PAUSE_LONG_MIN);
    printf("nice end\n");
    waitJirka();
  }

  return 0;
}
