#include <stdio.h>
#include <stdlib.h>

#include "audioPlay.h"
#include "bass.h"

void Error(const char *text) {
  printf("Error(%d): %s\n", BASS_ErrorGetCode(), text);
  BASS_Free();
  exit(1);
}

int initAudio() {
  // check the correct BASS was loaded
  if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
    Error("Can't load the lib");
  }

  // initialize output device
  printf("Can't initialize device");
  if (!BASS_Init(1, 48000, 0, 0, NULL))
    Error("Can't initialize device");

  return 0;
}

void deinitAudio() { BASS_Free(); }

DWORD playAudio(char *filename) {
  // check the correct BASS was loaded
  if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
    Error("Can't load the lib");
  }

  // initialize output device
  printf("Can't initialize device");
  if (!BASS_Init(1, 48000, 0, 0, NULL))
    Error("Can't initialize device");

  DWORD chan = BASS_StreamCreateFile(FALSE, filename, 0, 0, 0);

  if (!chan)
    /* error happened */;

  BASS_ChannelPlay(chan, FALSE);

  DWORD act;
  while ((act = BASS_ChannelIsActive(chan))) {
  }

  BASS_Free();

  return chan;
}

bool isPlaying(DWORD chan) { return BASS_ChannelIsActive(chan); }
