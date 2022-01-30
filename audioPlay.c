#include <stdio.h>

#include "audioPlay.h"
#include "bass.h"

int initAudio() {
  // check the correct BASS was loaded
  if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
    return 1;
  }

  // initialize output device
  printf("Can't initialize device");
  if (!BASS_Init(1, 48000, 0, 0, NULL))
    return 1;

  return 0;
}

void deinitAudio() { BASS_Free(); }

DWORD playAudio(char *filename) {
  DWORD chan = BASS_StreamCreateFile(FALSE, filename, 0, 0, 0);
  if (!chan)
    /* error happened */;

  BASS_ChannelPlay(chan, FALSE);

  return chan;
}
