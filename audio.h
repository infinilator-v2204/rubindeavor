#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
	char path[128];
	int loopMusicId;
} Music;

enum {
	MUS_menu,
	MUS_battle,
	MUS_battle2,
	MUS_battle3,
	MUS_boss1,
	MUS_boss2,
	MUS_boss2pre,
	MUS_boss3,
	MUS_boss4,
	MUS_boss4pre,
	MUS_scarybattle,
	MUS_battlerisk,
	MUS_battlepower,
	MUS_battleillus,
	MUS_battlegate,
	MUS_battlegate2,
	MUS_battlegate3,
	MUS_battlegate4,
	MUS_battlestrong,
	MUS_battlegreed,
	MUS_battlewrath,
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
	MUS_tense_r_slow,
	MUS_lu,
	MUS_lb,
	MUS_lbpre,
	MUS_navybattle,
	MUS_outside,
	MUS_metro,
	MUS_transport,
	MUS_bother,
	MUS_disco,
	MUS_discoquiet,
	MUS_ozone,
	MUS_unused,
	MUS_blue,
	MUS_megacity,
	MUS_casualneo,
	MUS_cozy,
	MUS_whitelight,
	MUS_countdown,
	MUS_amper,
	MUS_amper2,
	MUS_amper3,
	MUS_discodoomsday,
	MUS_retichase,
	MUS_core,
	MUS_tech,
	MUS_unnerving,
	MUS_unnervingslow,
	MUS_ominous,
	MUS_perspective,
	MUS_border,
	MUS_mysterious,
	MUS_lux,
	MUS_luxpre,
	MUS_lbx,
	MUS_ru,
	MUS_secretambience,
	MUS_hellgate,
	MUS_afterlab,
	MUS_illus,
	MUS_s,
	MUS_trance,
	MUS_mountains,
	MUS_singularity,
	MUS_brilliant1,
	MUS_brilliant2,
	MUS_brilliant3,
	MUS_brilliant3slow,
	MUS_brilliant4,
	MUS_brilliant5,
	MUS_postclimax,
	MUS_bin,
	MUS_death,
	MUS_oh,
	MUS_shutdown,
	MUS_shutdownpre,
	MUS_shutdownslow,
	MUS_feelnothing,
	MUS_darkunknown,
	MUS_darkmemory,
	MUS_risk,
	MUS_unnamed28,
	MUS_unnamed29,
	MUS_finale_intro,
	MUS_finale,
	MUS_tally,
	MUS_tally_slow,
	MUS_karma,
	MUS_mysteriousalt,
	MUS_mountainsalt,
	MUS_superboss,
	MUS_something,
	MUS_ultboss,
	MUS_ultboss_short,
	MUS_ultboss_shortpre,
	MUS_finale_corrupt,
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
	SND_nerf,
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
	SND_electric,
	SND_neutralize,
	SND_heatray,
	SND_goner,
	SND_save,
	SND_no,
	SND_introwakeup,
	SND_encounter,
	SND_encountermg,
	SND_encountermg_slow,
	SND_reset,
	SND_elevator,
	SND_gatedefeat,
	SND_aztecrage,
	SND_aztecslice,
	SND_absorb,
	SND_weird1,
	SND_deflect,
	SND_luxuryswing,
	SND_paperfold,
	SND_shards,
	SND_snowqueenwannabeapproaches,
	SND_beamsword,
	SND_ampbroadcast,
	SND_beep_square,
	SND_amper_feedback,
	SND_transportend,
	SND_ruentry,
	SND_tallyancientgem,
	SND_shadyboost,
	SND_error,
	SND_birchswing1,
	SND_birchswing2,
	SND_birchhit1,
	SND_birchhit2,
	SND_birchteleport,
	SND_closeskill,
	SND_ultimateskill,
	SND_ultbeam,
	SND_surprise,
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
	SND_fm,
};



typedef struct {
	char title[32];
	int musicId;
} Soundtrack;



typedef void (*SoundFilterFunction)(Sint16* buffer, int length);
typedef struct {
	SoundFilterFunction function;
} SoundFilter;



typedef struct {
	int musicCount;
	Music musicTracks[OBJECT_COUNT_MAX];
	
	int soundCount;
	Sound soundEffects[OBJECT_COUNT_MAX];
	
	int soundtrackCount;
	Soundtrack soundtracks[OBJECT_COUNT_MAX];
	
	SoundFilter soundFilters[16];
	
	
	
	int soundInterruptCount;
	int soundInterrupts[16];
	
	int currentMusicId;
	Mix_Music* currentMusic;
	bool currentMusicCanLoop;
	int soundFilterId;
	void* bufferMemory;
	int bufferMemorySize;
} AudioSystem;

extern AudioSystem audioSystem;



void LoadAudio();
void FreeAudio();

void Audio_LoadMusic(const char* path);
void Audio_LoadSound(const char* path);
void Audio_SetMusicLoop(int musicId, int loopMusicId);
void Audio_AddSoundtrack(const char* title, int musicId);
void Audio_PlayMusic(int musicId);
void Audio_StopMusic();
void Audio_FadeOutMusic(int ms);
int Audio_MusicIsPlaying(int musicId);
void Audio_PlaySound(int soundId);
void Audio_PlaySoundLoop(int soundId);
void Audio_PlaySoundInterrupt(int soundId);
void Audio_StopSoundLoop();
void Audio_StopAllSounds();
void Audio_ApplySoundFilter(int soundFilterId);
void Audio_RemoveSoundFilter();

void AudioEffectFunctionCallback(int chan, void* stream, int len, void* udata);
void SoundFilterFunction__0(Sint16* buffer, int length);
void SoundFilterFunction__1(Sint16* buffer, int length);
void SoundFilterFunction__2(Sint16* buffer, int length);
void SoundFilterFunction__3(Sint16* buffer, int length);
