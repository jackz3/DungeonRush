#ifndef SNAKE_AUDIO_H_
#define SNAKE_AUDIO_H_
#include <SDL3/SDL.h>
#if ENABLE_AUDIO
#include <SDL3_mixer/SDL_mixer.h>
#endif

#define BGM_FADE_DURATION 800
void playBgm(int);
void playAudio(int);
void randomBgm();
void stopBgm();
void pauseSound();
void resumeSound();
#endif
