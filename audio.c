#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "generic.h"
#include "audio.h"

int musicCount;
Music musicTracks[OBJECT_COUNT_MAX];

int soundCount;
Sound soundEffects[OBJECT_COUNT_MAX];

int soundInterruptCount;
int soundInterrupts[16];

int soundtrackCount;
Soundtrack soundtracks[64];

SoundFilter soundFilters[16];

AudioSystem audioSystem;



void LoadAudio() {
	musicCount = 0;
	soundCount = 0;
	
	LoadMusic("sfx/mus/menu.ogg");
	LoadMusic("sfx/mus/battle.ogg");
	LoadMusic("sfx/mus/battle2.ogg");
	LoadMusic("sfx/mus/boss1.ogg");
	LoadMusic("sfx/mus/boss2.ogg");
	LoadMusic("sfx/mus/boss2pre.ogg");
	LoadMusic("sfx/mus/boss3.ogg");
	LoadMusic("sfx/mus/scarybattle.ogg");
	LoadMusic("sfx/mus/battlerisk.ogg");
	LoadMusic("sfx/mus/battlepower.ogg");
	LoadMusic("sfx/mus/battleillus.ogg");
	LoadMusic("sfx/mus/battlegate.ogg");
	LoadMusic("sfx/mus/battlegate2.ogg");
	LoadMusic("sfx/mus/battlegate3.ogg");
	LoadMusic("sfx/mus/battlegate4.ogg");
	LoadMusic("sfx/mus/battlestrong.ogg");
	LoadMusic("sfx/mus/casual.ogg");
	LoadMusic("sfx/mus/hotel.ogg");
	LoadMusic("sfx/mus/field.ogg");
	LoadMusic("sfx/mus/cave.ogg");
	LoadMusic("sfx/mus/forest.ogg");
	LoadMusic("sfx/mus/scary.ogg");
	LoadMusic("sfx/mus/scary2.ogg");
	LoadMusic("sfx/mus/town.ogg");
	LoadMusic("sfx/mus/mansion.ogg");
	LoadMusic("sfx/mus/desert.ogg");
	LoadMusic("sfx/mus/city.ogg");
	LoadMusic("sfx/mus/tense_r.ogg");
	LoadMusic("sfx/mus/lu.ogg");
	LoadMusic("sfx/mus/lb.ogg");
	LoadMusic("sfx/mus/lbpre.ogg");
	LoadMusic("sfx/mus/navybattle.ogg");
	LoadMusic("sfx/mus/outside.ogg");
	LoadMusic("sfx/mus/bother.ogg");
	LoadMusic("sfx/mus/disco.ogg");
	LoadMusic("sfx/mus/discoquiet.ogg");
	LoadMusic("sfx/mus/ozone.ogg");
	LoadMusic("sfx/mus/unused.ogg");
	LoadMusic("sfx/mus/blue.ogg");
	LoadMusic("sfx/mus/mysterious.ogg");
	LoadMusic("sfx/mus/secretambience.ogg");
	LoadMusic("sfx/mus/hellgate.ogg");
	LoadMusic("sfx/mus/afterlab.ogg");
	LoadMusic("sfx/mus/illus.ogg");
	LoadMusic("sfx/mus/s.ogg");
	LoadMusic("sfx/mus/trance.ogg");
	LoadMusic("sfx/mus/singularity.ogg");
	LoadMusic("sfx/mus/brilliant1.ogg");
	LoadMusic("sfx/mus/brilliant2.ogg");
	LoadMusic("sfx/mus/brilliant3.ogg");
	LoadMusic("sfx/mus/brilliant3slow.ogg");
	LoadMusic("sfx/mus/brilliant4.ogg");
	LoadMusic("sfx/mus/bin.ogg");
	LoadMusic("sfx/mus/death.ogg");
	LoadMusic("sfx/mus/oh.ogg");
	LoadMusic("sfx/mus/unnamed28.ogg");
	LoadMusic("sfx/mus/unnamed29.ogg");
	LoadMusic("sfx/mus/lastresort_intro.ogg");
	LoadMusic("sfx/mus/lastresort.ogg");
	LoadMusic("sfx/mus/lastresort2.ogg");
	LoadMusic("sfx/mus/lastresort_pitchup.ogg");
	LoadMusic("sfx/mus/lastresort_pitchdown.ogg");
	LoadMusic("sfx/mus/lastresort2_pitchdown.ogg");
	
	SetMusicLoop(MUS_boss2pre, MUS_boss2);
	SetMusicLoop(MUS_lbpre, MUS_lb);
	
	LoadSound("sfx/menu1.ogg");
	LoadSound("sfx/menu2.ogg");
	LoadSound("sfx/menu3.ogg");
	LoadSound("sfx/menu4.ogg");
	LoadSound("sfx/menu5.ogg");
	LoadSound("sfx/menu6.ogg");
	LoadSound("sfx/voice1.ogg");
	LoadSound("sfx/voice2.ogg");
	LoadSound("sfx/hit1.ogg");
	LoadSound("sfx/hit2.ogg");
	LoadSound("sfx/hit3.ogg");
	LoadSound("sfx/dodge.ogg");
	LoadSound("sfx/swing.ogg");
	LoadSound("sfx/firemassattack.ogg");
	LoadSound("sfx/explode.ogg");
	LoadSound("sfx/gunfire.ogg");
	LoadSound("sfx/gunfire2.ogg");
	LoadSound("sfx/thunder.ogg");
	LoadSound("sfx/slap.ogg");
	LoadSound("sfx/minigun.ogg");
	LoadSound("sfx/minigunambience.ogg");
	LoadSound("sfx/heal.ogg");
	LoadSound("sfx/mana.ogg");
	LoadSound("sfx/boost.ogg");
	LoadSound("sfx/burn.ogg");
	LoadSound("sfx/poison.ogg");
	LoadSound("sfx/freeze.ogg");
	LoadSound("sfx/flower.ogg");
	LoadSound("sfx/flower2.ogg");
	LoadSound("sfx/flower3.ogg");
	LoadSound("sfx/unknown1.ogg");
	LoadSound("sfx/unknown2.ogg");
	LoadSound("sfx/unknown3.ogg");
	LoadSound("sfx/bonus1.ogg");
	LoadSound("sfx/bonus2.ogg");
	LoadSound("sfx/saw.ogg");
	LoadSound("sfx/sawkill.ogg");
	LoadSound("sfx/charge.ogg");
	LoadSound("sfx/neutralize.ogg");
	LoadSound("sfx/goner.ogg");
	LoadSound("sfx/save.ogg");
	LoadSound("sfx/no.ogg");
	LoadSound("sfx/introwakeup.ogg");
	LoadSound("sfx/encounter.ogg");
	LoadSound("sfx/encountermg.ogg");
	LoadSound("sfx/reset.ogg");
	LoadSound("sfx/elevator.ogg");
	LoadSound("sfx/gatedefeat.ogg");
	LoadSound("sfx/crusherhit.ogg");
	LoadSound("sfx/crusherhit2.ogg");
	LoadSound("sfx/crusherhit3.ogg");
	LoadSound("sfx/crusherhit4.ogg");
	LoadSound("sfx/gunshot.ogg");
	LoadSound("sfx/subspace_transform.ogg");
	LoadSound("sfx/subspace_transform2.ogg");
	LoadSound("sfx/chess_check.ogg");
	LoadSound("sfx/chess_mate.ogg");
	LoadSound("sfx/chess_move.ogg");
	LoadSound("sfx/chess_wrong.ogg");
	
	
	
	soundtrackCount = 0;
	
	AddSoundtrack("Menu", MUS_menu);
	AddSoundtrack("Hey, finish the game first!", MUS_unused);
	AddSoundtrack("Bother", MUS_bother);
	AddSoundtrack("Rivergreen Town", MUS_field);
	AddSoundtrack("Navy Encounter", MUS_navybattle);
	AddSoundtrack("Battle", MUS_battle);
	AddSoundtrack("Peaceful Underground", MUS_cave);
	AddSoundtrack("Casual Stuff", MUS_casual);
	AddSoundtrack("Miss L", MUS_lu);
	AddSoundtrack("Blind Rage", MUS_lbpre);
	AddSoundtrack("Leaf of Hope", MUS_forest);
	AddSoundtrack("Nervous", MUS_scary);
	AddSoundtrack("Nothing but a Joke", MUS_boss1);
	AddSoundtrack("Bluesteel Town", MUS_town);
	AddSoundtrack("Her Home", MUS_mansion);
	AddSoundtrack("Arachnid Storm", MUS_scarybattle);
	AddSoundtrack("Witchhunter", MUS_boss2pre);
	AddSoundtrack("The Gate", MUS_hellgate);
	AddSoundtrack("After Something", MUS_afterlab);
	AddSoundtrack("Unreal", MUS_s);
	AddSoundtrack("Call of Hell", MUS_bin);
	AddSoundtrack("Death", MUS_death);
	AddSoundtrack("Land's End", MUS_mysterious);
	AddSoundtrack("Last Resort Intro", MUS_lastresort_intro);
	AddSoundtrack("Last Resort", MUS_lastresort);
	AddSoundtrack("Last Resort 2", MUS_lastresort2);
	
	
	
	audioSystem.currentMusicId = -1;
	audioSystem.currentMusic = NULL;
	audioSystem.currentMusicCanLoop = false;
	audioSystem.soundFilterId = -1;
	audioSystem.bufferMemory = NULL;
	
	soundFilters[0].function = SoundFilterFunction__0;
	soundFilters[1].function = SoundFilterFunction__1;
	soundFilters[2].function = SoundFilterFunction__2;
	soundFilters[3].function = SoundFilterFunction__3;
	
	if (!Mix_RegisterEffect(MIX_CHANNEL_POST, (Mix_EffectFunc_t)AudioEffectFunctionCallback, NULL, NULL)) {
		printf("SDL_mixer error: %s\n", Mix_GetError());
	}
}

void LoadMusic(const char* path) {
	SetString(musicTracks[musicCount].path, path);
	musicTracks[musicCount].loopMusicId = -1;
	
	musicCount++;
}

void LoadSound(const char* path) {
	soundEffects[soundCount].sound = Mix_LoadWAV(path);
	
	soundCount++;
}

void SetMusicLoop(int musicId, int loopMusicId) {
	musicTracks[musicId].loopMusicId = loopMusicId;
}

void PlayMusic(int musicId) {
	if (musicId < 0) return;
	if (MusicIsPlaying(musicId)) return;
	
	if (audioSystem.currentMusicId >= 0) {
		Mix_FreeMusic(audioSystem.currentMusic);
	}
	
	audioSystem.currentMusic = Mix_LoadMUS(musicTracks[musicId].path);
	
	if (musicTracks[musicId].loopMusicId >= 0)
		Mix_PlayMusic(audioSystem.currentMusic, 0);
	else
		Mix_PlayMusic(audioSystem.currentMusic, -1);
	audioSystem.currentMusicId = musicId;
	audioSystem.currentMusicCanLoop = true;
}

void StopMusic() {
	Mix_HaltMusic();
	if (audioSystem.currentMusicId >= 0) {
		Mix_FreeMusic(audioSystem.currentMusic);
	}
	audioSystem.currentMusicId = -1;
	audioSystem.currentMusicCanLoop = false;
}

void FadeOutMusic(int ms) {
	Mix_FadeOutMusic(ms);
	audioSystem.currentMusicCanLoop = false;
}

int MusicIsPlaying(int musicId) {
	return audioSystem.currentMusicId == musicId;
}

void PlaySound(int soundId) {
	if (soundId < 0) return;
	Mix_PlayChannel(-1, soundEffects[soundId].sound, 0);
}

void PlaySoundInterrupt(int soundId) {
	if (soundInterruptCount >= 16) return;
	
	for (int i = 0; i < soundInterruptCount; i++) {
		if (soundInterrupts[i] == soundId) return;
	}
	
	soundInterrupts[soundInterruptCount++] = soundId;
}

void ApplySoundFilter(int soundFilterId) {
	audioSystem.soundFilterId = soundFilterId;
}

void RemoveSoundFilter() {
	audioSystem.soundFilterId = -1;
}

void FreeAudio() {
	if (audioSystem.currentMusicId >= 0) {
		Mix_FreeMusic(audioSystem.currentMusic);
	}
	for (int i = 0; i < musicCount; i++) {
		Mix_FreeChunk(soundEffects[i].sound);
	}
}



void AddSoundtrack(const char* title, int musicId) {
	SetString(soundtracks[soundtrackCount].title, title);
	soundtracks[soundtrackCount].musicId = musicId;
	
	soundtrackCount++;
}



void AudioEffectFunctionCallback(int chan, void* stream, int len, void* udata) {
	if (audioSystem.soundFilterId < 0) return;
	
	soundFilters[audioSystem.soundFilterId].function((Sint16*)stream, len / sizeof(Sint16));
}

void SoundFilterFunction__0(Sint16* buffer, int length) {
	int s = 2;
	
	for (int i = 0; i < length - s; i += s) {
		Sint16 avg = 0;
		for (int j = i; j < i + s; j++) {
			avg += buffer[j] / s;
		}
		for (int j = i; j < i + s; j++) {
			buffer[j] = avg;
		}
	}
}

void SoundFilterFunction__1(Sint16* buffer, int length) {
	int s = 8;
	
	for (int i = 0; i < length - s; i += s) {
		Sint16 avg = 0;
		for (int j = i; j < i + s; j++) {
			avg += buffer[j] / s;
		}
		for (int j = i; j < i + s; j++) {
			buffer[j] = avg;
		}
	}
}

void SoundFilterFunction__2(Sint16* buffer, int length) {
	int s = 128;
	
	for (int i = 0; i < length; i += s) {
		Sint16 avg = 0;
		for (int j = i; j < i + s && j < length; j++) {
			avg += buffer[j] / s;
		}
		for (int j = i; j < i + s && j < length; j++) {
			buffer[j] = avg;
		}
	}
}

void SoundFilterFunction__3(Sint16* buffer, int length) {
	if (audioSystem.bufferMemory == NULL) {
		audioSystem.bufferMemorySize = Min(length, 2048);
		audioSystem.bufferMemory = malloc(audioSystem.bufferMemorySize * sizeof(Sint16));
		if (audioSystem.bufferMemory == NULL) return;
		Sint16* bufferMemory = (Sint16*)audioSystem.bufferMemory;
		for (int i = 0; i < audioSystem.bufferMemorySize; i++) {
			bufferMemory[i] = buffer[i];
		}
		return;
	}
	
	Sint16* bufferMemory = (Sint16*)audioSystem.bufferMemory;
	for (int i = 0; i < length; i++) {
		buffer[i] = bufferMemory[i % audioSystem.bufferMemorySize];
	}
}
