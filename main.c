#include <curses.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "audioPlay.h"
#include "bass.h"

char *bell_sound_path = "BestSoundEver.mp3";
int repetition = 4;
typedef enum { PAUSE = 0, PAUSE_LONG = 1, POMODORO = 2 } MODE;
int timeArray[] = {5, 15, 25};

char *names[] = {
    "Pause",
    "Long puase",
    "Pomodoro",
};

char *name(MODE m) { return names[m]; }

// void play_sound() { DWORD chan = playAudio(bell_sound_path); }

// void play_bell(MODE m) {
//   switch (m) {
//   case PAUSE:
//     play_sound();
//     play_sound();
//     break;
//   case PAUSE_LONG:
//     play_sound();
//     play_sound();
//     break;
//   case POMODORO:
//     play_sound();
//     break;
//   }
// }

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
  // play_bell(m);
  printw("%s ended. Press a key to continue...\n", name(m));
  getch();
}

int check_argument(const char *arg)
{
    for (int i = 0; arg[i] != '\0'; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
        {
          return 1;
        }
    }
return 0;
}



int main(int argc,char* argv[]) {
  // delka pauzy, dlouhe pauzy, kratke, pomodora, option bell file
int temp, option;

int option_index = 0;
int timeArray[] = {5,15,25,4};
struct option long_options[] = {
    {"pomodoro", required_argument, 0, 'p'},
    {"short", required_argument, 0, 's'},
    {"pomodoro", required_argument, 0, 'l'},
    {"repetition", required_argument, 0, 'r'},
    {0, 0, 0, 0}
};
option = getopt_long(argc, argv, "p:s:l:r:", long_options, &option_index);
switch(option){
  case 'p':
    if(check_argument(optarg)==1){
      printf("only numbers\n");
      return EXIT_FAILURE;
    };
    timeArray[POMODORO] = atoi(optarg); 
  case 's':
    if(check_argument(optarg)==1){
      printf("only numbers\n");
      return EXIT_FAILURE;
    };
    timeArray[PAUSE] = atoi(optarg); 
  case 'l':
    if(check_argument(optarg)==1){
      printf("only numbers\n");
      return EXIT_FAILURE;
    };
    timeArray[PAUSE_LONG] = atoi(optarg); 
  case'r':
    if(check_argument(optarg)){
      printf("only numbers\n");
      return EXIT_FAILURE;
    };
    repetition = atoi(optarg);
  default:
    printf("-s set short pause, \n-r set repetition counter, \n-l set long counter, \n-p length of pomodoro times ");
}
  // FILE* file;

  WINDOW *w = initscr();
  printw(
    "\nPomodoro\n \
# Controls\n \
Press:\n \
- 'q' for quit\n \
- 's' for skip\n \
\n ");
printw("Usage: ./pomodoro -s -r -t -p\n-s set short pause, \n-r set repetition counter, \n-l set long counter, \n-p length of pomodoro times\n");
printw("\nReady for pomodoro, press enter to start...");
  nodelay(w, FALSE);

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
