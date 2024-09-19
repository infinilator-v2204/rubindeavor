#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
	char path[128];
	int loopMusicId;
} Music;

extern int musicCount;
extern Music musicTracks[OBJECT_COUNT_MAX];

enum {
	MUS_menu,
	MUS_battle,
	MUS_battle2,
	MUS_boss1,
	MUS_boss2,
	MUS_boss2pre,
	MUS_boss3,
	MUS_scarybattle,
	MUS_battlerisk,
	MUS_battlepower,
	MUS_battleillus,
	MUS_battlegate,
	MUS_battlegate2,
	MUS_battlegate3,
	MUS_battlegate4,
	MUS_battlestrong,
	MUS_casual,
	MUS_hotel,
	MUS_field,
	MUS_cave,
	MUS_forest,
	MUS_scary,
	MUS_scary2,
	MUS_town,
	MUS_mansion,
	MUS_desert,
	MUS_city,
	MUS_tense_r,
	MUS_lu,
	MUS_lb,
	MUS_lbpre,
	MUS_navybattle,
	MUS_outside,
	MUS_bother,
	MUS_disco,
	MUS_discoquiet,
	MUS_ozone,
	MUS_unused,
	MUS_blue,
	MUS_mysterious,
	MUS_secretambience,
	MUS_hellgate,
	MUS_afterlab,
	MUS_illus,
	MUS_s,
	MUS_trance,
	MUS_singularity,
	MUS_brilliant1,
	MUS_brilliant2,
	MUS_brilliant3,
	MUS_brilliant3slow,
	MUS_brilliant4,
	MUS_bin,
	MUS_death,
	MUS_oh,
	MUS_unnamed28,
	MUS_unnamed29,
	MUS_lastresort_intro,
	MUS_lastresort,
	MUS_lastresort2,
	MUS_lastresort_pitchup,
	MUS_lastresort_pitchdown,
	MUS_lastresort2_pitchdown,
};



typedef struct {
	Mix_Chunk* sound;
} Sound;

extern int soundCount;
extern Sound soundEffects[OBJECT_COUNT_MAX];

extern int soundInterruptCount;
extern int soundInterrupts[16];

enum {
	SND_menu1,
	SND_menu2,
	SND_menu3,
	SND_menu4,
	SND_menu5,
	SND_menu6,
	SND_voice1,
	SND_voice2,
	SND_hit1,
	SND_hit2,
	SND_hit3,
	SND_dodge,
	SND_swing,
	SND_firemassattack,
	SND_explode,
	SND_gunfire,
	SND_gunfire2,
	SND_thunder,
	SND_slap,
	SND_minigun,
	SND_minigunambience,
	SND_heal,
	SND_mana,
	SND_boost,
	SND_burn,
	SND_poison,
	SND_freeze,
	SND_flower,
	SND_flower2,
	SND_flower3,
	SND_unknown1,
	SND_unknown2,
	SND_unknown3,
	SND_bonus1,
	SND_bonus2,
	SND_saw,
	SND_sawkill,
	SND_charge,
	SND_neutralize,
	SND_goner,
	SND_save,
	SND_no,
	SND_introwakeup,
	SND_encounter,
	SND_encountermg,
	SND_reset,
	SND_elevator,
	SND_gatedefeat,
	SND_crusherhit,
	SND_crusherhit2,
	SND_crusherhit3,
	SND_crusherhit4,
	SND_gunshot,
	SND_subspace_transform,
	SND_subspace_transform2,
	SND_chess_check,
	SND_chess_mate,
	SND_chess_move,
	SND_chess_wrong,
};



typedef struct {
	char title[32];
	int musicId;
} Soundtrack;

extern int soundtrackCount;
extern Soundtrack soundtracks[64];



typedef void (*SoundFilterFunction)(Sint16* buffer, int length);
typedef struct {
	SoundFilterFunction function;
} SoundFilter;

extern SoundFilter soundFilters[16];



typedef struct {
	int currentMusicId;
	Mix_Music* currentMusic;
	bool currentMusicCanLoop;
	int soundFilterId;
	void* bufferMemory;
	int bufferMemorySize;
} AudioSystem;

extern AudioSystem audioSystem;



void LoadAudio();
void LoadMusic(const char* path);
void LoadSound(const char* path);
void SetMusicLoop(int musicId, int loopMusicId);
void PlayMusic(int musicId);
void StopMusic();
void FadeOutMusic(int ms);
int MusicIsPlaying(int musicId);
void PlaySound(int soundId);
void PlaySoundInterrupt(int soundId);
void ApplySoundFilter(int soundFilterId);
void RemoveSoundFilter();
void FreeAudio();

void AddSoundtrack(const char* title, int musicId);

void AudioEffectFunctionCallback(int chan, void* stream, int len, void* udata);
void SoundFilterFunction__0(Sint16* buffer, int length);
void SoundFilterFunction__1(Sint16* buffer, int length);
void SoundFilterFunction__2(Sint16* buffer, int length);
void SoundFilterFunction__3(Sint16* buffer, int length);
