#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "generic.h"
#include "audio.h"

AudioSystem audioSystem;



void LoadAudio() {
	audioSystem.musicCount = 0;
	audioSystem.soundCount = 0;
	
	Audio_LoadMusic("sfx/mus/menu.ogg");
	Audio_LoadMusic("sfx/mus/battle.ogg");
	Audio_LoadMusic("sfx/mus/battle2.ogg");
	Audio_LoadMusic("sfx/mus/battle3.ogg");
	Audio_LoadMusic("sfx/mus/boss1.ogg");
	Audio_LoadMusic("sfx/mus/boss2.ogg");
	Audio_LoadMusic("sfx/mus/boss2pre.ogg");
	Audio_LoadMusic("sfx/mus/boss3.ogg");
	Audio_LoadMusic("sfx/mus/boss4.ogg");
	Audio_LoadMusic("sfx/mus/boss4pre.ogg");
	Audio_LoadMusic("sfx/mus/scarybattle.ogg");
	Audio_LoadMusic("sfx/mus/battlerisk.ogg");
	Audio_LoadMusic("sfx/mus/battlepower.ogg");
	Audio_LoadMusic("sfx/mus/battleillus.ogg");
	Audio_LoadMusic("sfx/mus/battlegate.ogg");
	Audio_LoadMusic("sfx/mus/battlegate2.ogg");
	Audio_LoadMusic("sfx/mus/battlegate3.ogg");
	Audio_LoadMusic("sfx/mus/battlegate4.ogg");
	Audio_LoadMusic("sfx/mus/battlestrong.ogg");
	Audio_LoadMusic("sfx/mus/battlegreed.ogg");
	Audio_LoadMusic("sfx/mus/battlewrath.ogg");
	Audio_LoadMusic("sfx/mus/casual.ogg");
	Audio_LoadMusic("sfx/mus/hotel.ogg");
	Audio_LoadMusic("sfx/mus/field.ogg");
	Audio_LoadMusic("sfx/mus/cave.ogg");
	Audio_LoadMusic("sfx/mus/forest.ogg");
	Audio_LoadMusic("sfx/mus/scary.ogg");
	Audio_LoadMusic("sfx/mus/scary2.ogg");
	Audio_LoadMusic("sfx/mus/town.ogg");
	Audio_LoadMusic("sfx/mus/mansion.ogg");
	Audio_LoadMusic("sfx/mus/desert.ogg");
	Audio_LoadMusic("sfx/mus/city.ogg");
	Audio_LoadMusic("sfx/mus/tense_r.ogg");
	Audio_LoadMusic("sfx/mus/tense_r_slow.ogg");
	Audio_LoadMusic("sfx/mus/lu.ogg");
	Audio_LoadMusic("sfx/mus/lb.ogg");
	Audio_LoadMusic("sfx/mus/lbpre.ogg");
	Audio_LoadMusic("sfx/mus/navybattle.ogg");
	Audio_LoadMusic("sfx/mus/outside.ogg");
	Audio_LoadMusic("sfx/mus/metro.ogg");
	Audio_LoadMusic("sfx/mus/transport.ogg");
	Audio_LoadMusic("sfx/mus/bother.ogg");
	Audio_LoadMusic("sfx/mus/disco.ogg");
	Audio_LoadMusic("sfx/mus/discoquiet.ogg");
	Audio_LoadMusic("sfx/mus/ozone.ogg");
	Audio_LoadMusic("sfx/mus/unused.ogg");
	Audio_LoadMusic("sfx/mus/blue.ogg");
	Audio_LoadMusic("sfx/mus/megacity.ogg");
	Audio_LoadMusic("sfx/mus/casualneo.ogg");
	Audio_LoadMusic("sfx/mus/cozy.ogg");
	Audio_LoadMusic("sfx/mus/whitelight.ogg");
	Audio_LoadMusic("sfx/mus/countdown.ogg");
	Audio_LoadMusic("sfx/mus/amper.ogg");
	Audio_LoadMusic("sfx/mus/amper2.ogg");
	Audio_LoadMusic("sfx/mus/amper3.ogg");
	Audio_LoadMusic("sfx/mus/discodoomsday.ogg");
	Audio_LoadMusic("sfx/mus/retichase.ogg");
	Audio_LoadMusic("sfx/mus/core.ogg");
	Audio_LoadMusic("sfx/mus/tech.ogg");
	Audio_LoadMusic("sfx/mus/unnerving.ogg");
	Audio_LoadMusic("sfx/mus/unnervingslow.ogg");
	Audio_LoadMusic("sfx/mus/ominous.ogg");
	Audio_LoadMusic("sfx/mus/perspective.ogg");
	Audio_LoadMusic("sfx/mus/border.ogg");
	Audio_LoadMusic("sfx/mus/mysterious.ogg");
	Audio_LoadMusic("sfx/mus/lux.ogg");
	Audio_LoadMusic("sfx/mus/luxpre.ogg");
	Audio_LoadMusic("sfx/mus/lbx.ogg");
	Audio_LoadMusic("sfx/mus/ru.ogg");
	Audio_LoadMusic("sfx/mus/secretambience.ogg");
	Audio_LoadMusic("sfx/mus/hellgate.ogg");
	Audio_LoadMusic("sfx/mus/afterlab.ogg");
	Audio_LoadMusic("sfx/mus/illus.ogg");
	Audio_LoadMusic("sfx/mus/s.ogg");
	Audio_LoadMusic("sfx/mus/trance.ogg");
	Audio_LoadMusic("sfx/mus/mountains.ogg");
	Audio_LoadMusic("sfx/mus/singularity.ogg");
	Audio_LoadMusic("sfx/mus/brilliant1.ogg");
	Audio_LoadMusic("sfx/mus/brilliant2.ogg");
	Audio_LoadMusic("sfx/mus/brilliant3.ogg");
	Audio_LoadMusic("sfx/mus/brilliant3slow.ogg");
	Audio_LoadMusic("sfx/mus/brilliant4.ogg");
	Audio_LoadMusic("sfx/mus/brilliant5.ogg");
	Audio_LoadMusic("sfx/mus/postclimax.ogg");
	Audio_LoadMusic("sfx/mus/bin.ogg");
	Audio_LoadMusic("sfx/mus/death.ogg");
	Audio_LoadMusic("sfx/mus/oh.ogg");
	Audio_LoadMusic("sfx/mus/shutdown.ogg");
	Audio_LoadMusic("sfx/mus/shutdownpre.ogg");
	Audio_LoadMusic("sfx/mus/shutdownslow.ogg");
	Audio_LoadMusic("sfx/mus/feelnothing.ogg");
	Audio_LoadMusic("sfx/mus/darkunknown.ogg");
	Audio_LoadMusic("sfx/mus/darkmemory.ogg");
	Audio_LoadMusic("sfx/mus/risk.ogg");
	Audio_LoadMusic("sfx/mus/unnamed28.ogg");
	Audio_LoadMusic("sfx/mus/unnamed29.ogg");
	Audio_LoadMusic("sfx/mus/finale_intro.ogg");
	Audio_LoadMusic("sfx/mus/finale.ogg");
	Audio_LoadMusic("sfx/mus/tally.ogg");
	Audio_LoadMusic("sfx/mus/tally_slow.ogg");
	Audio_LoadMusic("sfx/mus/karma.ogg");
	Audio_LoadMusic("sfx/mus/mysteriousalt.ogg");
	Audio_LoadMusic("sfx/mus/mountainsalt.ogg");
	Audio_LoadMusic("sfx/mus/superboss.ogg");
	Audio_LoadMusic("sfx/mus/something.ogg");
	Audio_LoadMusic("sfx/mus/ultboss.ogg");
	Audio_LoadMusic("sfx/mus/ultboss_short.ogg");
	Audio_LoadMusic("sfx/mus/ultboss_shortpre.ogg");
	Audio_LoadMusic("sfx/mus/finale_corrupt.ogg");
	Audio_LoadMusic("sfx/mus/lastresort_intro.ogg");
	Audio_LoadMusic("sfx/mus/lastresort.ogg");
	Audio_LoadMusic("sfx/mus/lastresort2.ogg");
	Audio_LoadMusic("sfx/mus/lastresort_pitchup.ogg");
	Audio_LoadMusic("sfx/mus/lastresort_pitchdown.ogg");
	Audio_LoadMusic("sfx/mus/lastresort2_pitchdown.ogg");
	
	Audio_SetMusicLoop(MUS_boss2pre, MUS_boss2);
	Audio_SetMusicLoop(MUS_boss4pre, MUS_boss4);
	Audio_SetMusicLoop(MUS_lbpre, MUS_lb);
	Audio_SetMusicLoop(MUS_luxpre, MUS_lux);
	Audio_SetMusicLoop(MUS_shutdownpre, MUS_shutdown);
	Audio_SetMusicLoop(MUS_ultboss_shortpre, MUS_ultboss_short);
	
	Audio_LoadSound("sfx/menu1.ogg");
	Audio_LoadSound("sfx/menu2.ogg");
	Audio_LoadSound("sfx/menu3.ogg");
	Audio_LoadSound("sfx/menu4.ogg");
	Audio_LoadSound("sfx/menu5.ogg");
	Audio_LoadSound("sfx/menu6.ogg");
	Audio_LoadSound("sfx/voice1.ogg");
	Audio_LoadSound("sfx/voice2.ogg");
	Audio_LoadSound("sfx/hit1.ogg");
	Audio_LoadSound("sfx/hit2.ogg");
	Audio_LoadSound("sfx/hit3.ogg");
	Audio_LoadSound("sfx/dodge.ogg");
	Audio_LoadSound("sfx/swing.ogg");
	Audio_LoadSound("sfx/firemassattack.ogg");
	Audio_LoadSound("sfx/explode.ogg");
	Audio_LoadSound("sfx/gunfire.ogg");
	Audio_LoadSound("sfx/gunfire2.ogg");
	Audio_LoadSound("sfx/thunder.ogg");
	Audio_LoadSound("sfx/slap.ogg");
	Audio_LoadSound("sfx/minigun.ogg");
	Audio_LoadSound("sfx/minigunambience.ogg");
	Audio_LoadSound("sfx/heal.ogg");
	Audio_LoadSound("sfx/mana.ogg");
	Audio_LoadSound("sfx/boost.ogg");
	Audio_LoadSound("sfx/nerf.ogg");
	Audio_LoadSound("sfx/burn.ogg");
	Audio_LoadSound("sfx/poison.ogg");
	Audio_LoadSound("sfx/freeze.ogg");
	Audio_LoadSound("sfx/flower.ogg");
	Audio_LoadSound("sfx/flower2.ogg");
	Audio_LoadSound("sfx/flower3.ogg");
	Audio_LoadSound("sfx/unknown1.ogg");
	Audio_LoadSound("sfx/unknown2.ogg");
	Audio_LoadSound("sfx/unknown3.ogg");
	Audio_LoadSound("sfx/bonus1.ogg");
	Audio_LoadSound("sfx/bonus2.ogg");
	Audio_LoadSound("sfx/saw.ogg");
	Audio_LoadSound("sfx/sawkill.ogg");
	Audio_LoadSound("sfx/charge.ogg");
	Audio_LoadSound("sfx/electric.ogg");
	Audio_LoadSound("sfx/neutralize.ogg");
	Audio_LoadSound("sfx/heatray.ogg");
	Audio_LoadSound("sfx/goner.ogg");
	Audio_LoadSound("sfx/save.ogg");
	Audio_LoadSound("sfx/no.ogg");
	Audio_LoadSound("sfx/introwakeup.ogg");
	Audio_LoadSound("sfx/encounter.ogg");
	Audio_LoadSound("sfx/encountermg.ogg");
	Audio_LoadSound("sfx/encountermg_slow.ogg");
	Audio_LoadSound("sfx/reset.ogg");
	Audio_LoadSound("sfx/elevator.ogg");
	Audio_LoadSound("sfx/gatedefeat.ogg");
	Audio_LoadSound("sfx/aztecrage.ogg");
	Audio_LoadSound("sfx/aztecslice.ogg");
	Audio_LoadSound("sfx/absorb.ogg");
	Audio_LoadSound("sfx/weird1.ogg");
	Audio_LoadSound("sfx/deflect.ogg");
	Audio_LoadSound("sfx/luxuryswing.ogg");
	Audio_LoadSound("sfx/paperfold.ogg");
	Audio_LoadSound("sfx/shards.ogg");
	Audio_LoadSound("sfx/snowqueenwannabeapproaches.ogg");
	Audio_LoadSound("sfx/beamsword.ogg");
	Audio_LoadSound("sfx/ampbroadcast.ogg");
	Audio_LoadSound("sfx/beep_square.ogg");
	Audio_LoadSound("sfx/amper_feedback.ogg");
	Audio_LoadSound("sfx/transportend.ogg");
	Audio_LoadSound("sfx/ruentry.ogg");
	Audio_LoadSound("sfx/tallyancientgem.ogg");
	Audio_LoadSound("sfx/shadyboost.ogg");
	Audio_LoadSound("sfx/error.ogg");
	Audio_LoadSound("sfx/birchswing1.ogg");
	Audio_LoadSound("sfx/birchswing2.ogg");
	Audio_LoadSound("sfx/birchhit1.ogg");
	Audio_LoadSound("sfx/birchhit2.ogg");
	Audio_LoadSound("sfx/birchteleport.ogg");
	Audio_LoadSound("sfx/closeskill.ogg");
	Audio_LoadSound("sfx/ultimateskill.ogg");
	Audio_LoadSound("sfx/ultbeam.ogg");
	Audio_LoadSound("sfx/surprise.ogg");
	Audio_LoadSound("sfx/crusherhit.ogg");
	Audio_LoadSound("sfx/crusherhit2.ogg");
	Audio_LoadSound("sfx/crusherhit3.ogg");
	Audio_LoadSound("sfx/crusherhit4.ogg");
	Audio_LoadSound("sfx/gunshot.ogg");
	Audio_LoadSound("sfx/subspace_transform.ogg");
	Audio_LoadSound("sfx/subspace_transform2.ogg");
	Audio_LoadSound("sfx/chess_check.ogg");
	Audio_LoadSound("sfx/chess_mate.ogg");
	Audio_LoadSound("sfx/chess_move.ogg");
	Audio_LoadSound("sfx/chess_wrong.ogg");
	Audio_LoadSound("sfx/fm.ogg");
	
	
	
	audioSystem.soundtrackCount = 0;
	
	Audio_AddSoundtrack("Menu", MUS_menu);
	Audio_AddSoundtrack("Hey, finish the game first!", MUS_unused);
	Audio_AddSoundtrack("Bother", MUS_bother);
	Audio_AddSoundtrack("Rivergreen Town", MUS_field);
	Audio_AddSoundtrack("Navy Encounter", MUS_navybattle);
	Audio_AddSoundtrack("Battle", MUS_battle);
	Audio_AddSoundtrack("Peaceful Underground", MUS_cave);
	Audio_AddSoundtrack("Casual Stuff", MUS_casual);
	Audio_AddSoundtrack("Miss L", MUS_lu);
	Audio_AddSoundtrack("Blind Rage", MUS_lbpre);
	Audio_AddSoundtrack("Leaf of Hope", MUS_forest);
	Audio_AddSoundtrack("Nervous", MUS_scary);
	Audio_AddSoundtrack("Nothing but a Joke", MUS_boss1);
	Audio_AddSoundtrack("Bluesteel Town", MUS_town);
	Audio_AddSoundtrack("Her Home", MUS_mansion);
	Audio_AddSoundtrack("Arachnid Storm", MUS_scarybattle);
	Audio_AddSoundtrack("Witchhunter", MUS_boss2pre);
	Audio_AddSoundtrack("The Gate", MUS_hellgate);
	Audio_AddSoundtrack("After Something", MUS_afterlab);
	Audio_AddSoundtrack("Unreal", MUS_s);
	Audio_AddSoundtrack("Call of Hell", MUS_bin);
	Audio_AddSoundtrack("Death", MUS_death);
	Audio_AddSoundtrack("Land's End", MUS_mysterious);
	Audio_AddSoundtrack("Last Resort Intro", MUS_lastresort_intro);
	Audio_AddSoundtrack("Last Resort", MUS_lastresort);
	Audio_AddSoundtrack("Last Resort 2", MUS_lastresort2);
	
	
	
	audioSystem.currentMusicId = -1;
	audioSystem.currentMusic = NULL;
	audioSystem.currentMusicCanLoop = false;
	audioSystem.soundFilterId = -1;
	audioSystem.bufferMemory = NULL;
	
	audioSystem.soundFilters[0].function = SoundFilterFunction__0;
	audioSystem.soundFilters[1].function = SoundFilterFunction__1;
	audioSystem.soundFilters[2].function = SoundFilterFunction__2;
	audioSystem.soundFilters[3].function = SoundFilterFunction__3;
	
	if (!Mix_RegisterEffect(MIX_CHANNEL_POST, (Mix_EffectFunc_t)AudioEffectFunctionCallback, NULL, NULL)) {
		printf("SDL_mixer error: %s\n", Mix_GetError());
	}
}

void FreeAudio() {
	if (audioSystem.currentMusicId >= 0) {
		Mix_FreeMusic(audioSystem.currentMusic);
	}
	for (int i = 0; i < audioSystem.soundCount; i++) {
		Mix_FreeChunk(audioSystem.soundEffects[i].sound);
	}
}



void Audio_LoadMusic(const char* path) {
	SetString(audioSystem.musicTracks[audioSystem.musicCount].path, path);
	audioSystem.musicTracks[audioSystem.musicCount].loopMusicId = -1;
	
	audioSystem.musicCount++;
}

void Audio_LoadSound(const char* path) {
	audioSystem.soundEffects[audioSystem.soundCount].sound = Mix_LoadWAV(path);
	
	audioSystem.soundCount++;
}

void Audio_SetMusicLoop(int musicId, int loopMusicId) {
	audioSystem.musicTracks[musicId].loopMusicId = loopMusicId;
}

void Audio_AddSoundtrack(const char* title, int musicId) {
	SetString(audioSystem.soundtracks[audioSystem.soundtrackCount].title, title);
	audioSystem.soundtracks[audioSystem.soundtrackCount].musicId = musicId;
	
	audioSystem.soundtrackCount++;
}

void Audio_PlayMusic(int musicId) {
	if (musicId < 0) return;
	if (Audio_MusicIsPlaying(musicId)) return;
	
	if (audioSystem.currentMusicId >= 0) {
		Mix_FreeMusic(audioSystem.currentMusic);
	}
	
	audioSystem.currentMusic = Mix_LoadMUS(audioSystem.musicTracks[musicId].path);
	
	if (audioSystem.musicTracks[musicId].loopMusicId >= 0)
		Mix_PlayMusic(audioSystem.currentMusic, 0);
	else
		Mix_PlayMusic(audioSystem.currentMusic, -1);
	audioSystem.currentMusicId = musicId;
	audioSystem.currentMusicCanLoop = true;
}

void Audio_StopMusic() {
	Mix_HaltMusic();
	if (audioSystem.currentMusicId >= 0) {
		Mix_FreeMusic(audioSystem.currentMusic);
	}
	audioSystem.currentMusicId = -1;
	audioSystem.currentMusicCanLoop = false;
}

void Audio_FadeOutMusic(int ms) {
	Mix_FadeOutMusic(ms);
	audioSystem.currentMusicCanLoop = false;
}

int Audio_MusicIsPlaying(int musicId) {
	return audioSystem.currentMusicId == musicId;
}

void Audio_PlaySound(int soundId) {
	if (soundId < 0) return;
	Mix_PlayChannel(-1, audioSystem.soundEffects[soundId].sound, 0);
}

void Audio_PlaySoundLoop(int soundId) {
	if (soundId < 0) return;
	Mix_PlayChannel(63, audioSystem.soundEffects[soundId].sound, -1);
}

void Audio_PlaySoundInterrupt(int soundId) {
	if (audioSystem.soundInterruptCount >= 16) return;
	
	for (int i = 0; i < audioSystem.soundInterruptCount; i++) {
		if (audioSystem.soundInterrupts[i] == soundId) return;
	}
	
	audioSystem.soundInterrupts[audioSystem.soundInterruptCount++] = soundId;
}

void Audio_StopSoundLoop() {
	Mix_HaltChannel(63);
}

void Audio_StopAllSounds() {
	Mix_HaltChannel(-1);
}

void Audio_ApplySoundFilter(int soundFilterId) {
	audioSystem.soundFilterId = soundFilterId;
}

void Audio_RemoveSoundFilter() {
	audioSystem.soundFilterId = -1;
}



void AudioEffectFunctionCallback(int chan, void* stream, int len, void* udata) {
	if (audioSystem.soundFilterId < 0) return;
	
	audioSystem.soundFilters[audioSystem.soundFilterId].function((Sint16*)stream, len / sizeof(Sint16));
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
