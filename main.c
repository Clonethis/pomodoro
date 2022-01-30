#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

const int PAUSE_MIN = 5;
const int PAUSE_LONG_MIN = 15;
const int POMODORO_MIN = 25;
const int REPETITION_COUNT = 4;

void run(char *mode,int minutes){
    printf("%s\n",mode);
    sleep(minutes/5);
    printf("Mode ended\n");
}
void wait(){
    int num;
    while(1){
        num = getchar()

    }
}

int main(void) {
  printf("Hello, World! \a");
  while(1){
      getchar();
      for(int i =0; i<REPETITION_COUNT; i++){
          run("Pomodoro:",POMODORO_MIN);
          getch();
            if(i == REPETITION_COUNT-1){
                break;
            }
          run("Pause:",PAUSE_MIN);
          getch();
      }
        run("PauseLong:",PAUSE_LONG_MIN);
        getch();

  }

  return 0;
}
