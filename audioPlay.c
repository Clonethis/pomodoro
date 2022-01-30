// // #include "./bass24-osx/bass.h"
// // #define AUDIO
// // #include "mainHeader.h"
// #include<stdio.h>

// void playAudio(){
//     printf("I music player, am running");
// }
// int playBGM (char *filename)
// {
//    FILE *fptr = fopen (filename, "r");

//    if (fptr == NULL)
//       {
//          fclose (fptr);
//          return EXIT_FAILURE;
//       }
//    else
//       {
         
//         BASS_Init(-1, 44100, 0, 0, NULL);
//         BASS_SetVolume(1);
//         HSAMPLE sample = BASS_SampleLoad(FALSE, filename, 0, 0, 1, BASS_SAMPLE_MONO);
//         HCHANNEL channel=BASS_SampleGetChannel(sample, FALSE);
//         BASS_ChannelPlay (channel, FALSE);
//       }
//    fclose(fptr);
//    return EXIT_SUCCESS;
// }