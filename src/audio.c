#include "audio.h"

#include "helper.h"
#include "res.h"

#if ENABLE_AUDIO
extern const int bgmNums;
extern MIX_Mixer *mixer;
extern MIX_Track *bgmTrack;
extern MIX_Audio *bgms[AUDIO_BGM_SIZE];
extern MIX_Audio *sounds[AUDIO_SOUND_SIZE];

int nowBgmId = -1;
void playBgm(int id) {
  SDL_PropertiesID options;

  if (bgmTrack == NULL || id < 0 || id >= bgmNums || bgms[id] == NULL) return;
  if (nowBgmId == id) return;

  if (!MIX_SetTrackAudio(bgmTrack, bgms[id])) return;

  options = SDL_CreateProperties();
  if (options) {
    SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
    if (nowBgmId != -1) {
      SDL_SetNumberProperty(options, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER,
                            BGM_FADE_DURATION);
    }
  }

  if (!MIX_PlayTrack(bgmTrack, options)) {
    SDL_DestroyProperties(options);
    return;
  }

  SDL_DestroyProperties(options);
  nowBgmId = id;
}
void stopBgm() {
  if (bgmTrack != NULL) {
    Sint64 fadeFrames = MIX_TrackMSToFrames(bgmTrack, BGM_FADE_DURATION);
    if (fadeFrames < 0) fadeFrames = 0;
    MIX_StopTrack(bgmTrack, fadeFrames);
  }
  nowBgmId = -1;
}
void randomBgm() { playBgm(randInt(1, bgmNums - 1)); }
void playAudio(int id) {
  if (mixer != NULL && id >= 0 && id < AUDIO_SOUND_SIZE && sounds[id] != NULL) {
    MIX_PlayAudio(mixer, sounds[id]);
  }
}
void pauseSound() {
  if (mixer != NULL) MIX_PauseAllTracks(mixer);
}
void resumeSound() {
  if (mixer != NULL) MIX_ResumeAllTracks(mixer);
}

#else

void playBgm(int id) { (void)id; }
void stopBgm() {}
void randomBgm() {}
void playAudio(int id) { (void)id; }
void pauseSound() {}
void resumeSound() {}

#endif
