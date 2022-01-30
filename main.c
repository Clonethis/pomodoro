#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>

const int PAUSE_MIN = 5;
const int PAUSE_LONG_MIN = 15;
const int POMODORO_MIN = 25;
const int REPETITION_COUNT = 4;

void run(char *mode,int minutes){
    printf("%s\n",mode);
    sleep(1);
    printf("Mode ended\n");
}

int main(void) {

  printf("Starting pomodoro, waiting on enter...\n");


  while(1){
      printf("Looping \n");
        // wait();
      for(int i =0; i<REPETITION_COUNT; i++){
          run("Pomodoro:",POMODORO_MIN);
          printf("waiting on enter");
;
            if(i == REPETITION_COUNT-1){

              exit(1);

            }
          run("Pause:",PAUSE_MIN);
          printf("waiting on enter,to start again\n");

      }

        run("PauseLong:",PAUSE_LONG_MIN);
        printf("nice end\n");

  }

  return 0;
}
