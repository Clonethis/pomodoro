#ifndef AUDIO
#define AUDIO

#include <stdbool.h>

#include "bass.h"

int initAudio(); // check for 1 -> error
void deinitAudio();
bool isPlaying(DWORD chan);
DWORD playAudio(char *filepath);

#endif
