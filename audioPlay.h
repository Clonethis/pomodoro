#ifndef AUDIO
#define AUDIO

#include <stdbool.h>

#include "bass.h"

int initAudio(); // check for 1 -> error
void deinitAudio();
DWORD playAudio(char *filepath);

#endif
