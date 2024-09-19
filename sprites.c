#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <zip.h>

#include "generic.h"
#include "sprites.h"
#include "profile.h"

#define LOAD_SPRITES_FROM_FOLDER

const int FIRST_SPR_owchar = SPR_owchar_ruby;
const int LAST_SPR_owchar = SPR_owchar_rubin;

const int firstTilesetSpriteId = SPR_tileset_day;
const int lastTilesetSpriteId = SPR_tileset_night;

GameDrawState gameDrawState;

int spriteCount;
Sprite sprites[SPRITE_COUNT_MAX];

zip_t* za;
const char* ASSETS_PASSWORD = "the master lulu";
const char* TEMP_GFX_FILENAME = "TEMP";

void LoadSprites() {
	#ifndef LOAD_SPRITES_FROM_FOLDER
	int za_errorCode = 0;
	za = zip_open("assets.dat", ZIP_RDONLY, &za_errorCode);
	if (za == NULL) {
		zip_error_t error;
		zip_error_init_with_code(&error, za_errorCode);
		printf("Zip open error: %s\n", zip_error_strerror(&error));
		zip_error_fini(&error);
		return;
	}
	#endif
	
	
	
	spriteCount = 0;
	
	LoadSprite("gfx/head/ruby.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/ruby.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/ruby_zero.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/ruby_armed.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/noah.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/noah.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/emmet.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/emmet.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/sally.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/sally_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/sally.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/perry.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/perry.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/anonymous.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_0.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_1.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_2.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_3.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_4.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_5.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_6.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_7.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_8.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_9.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_9_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_10.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_11.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_11_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_12.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_13.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_14.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_15.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_16.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/generic_17.png", 32, 32, 18, 22);
	
	LoadSprite("gfx/body/hobo.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/navygang.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/leafcrew.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/bashura.png", 32, 32, 18, 22);
	
	LoadSprite("gfx/head/lisao.png", 32, 40, 18, 22);
	LoadSprite("gfx/head/lisao_b.png", 32, 40, 18, 22);
	LoadSprite("gfx/body/lisao.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/lulu.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/lulu.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/lulu_blaze.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/police.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/farmer.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/knifethug.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/vandal_knife.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/vandal_flail.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/nurse.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/jackie.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/jackie.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/electra.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/electra.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/ray.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/ray_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/ray.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/lulu_omega.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/slime.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/slimesuit.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/slimeboss.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/dia.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/dia_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/dia.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/spider.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/spidersuit.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/spiderboss.png", 64, 48, 31, 42);
	
	LoadSprite("gfx/head/policecap.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/policecap.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/sync.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/sync.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/josh.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/josh.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/pirate.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/pirate.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/piratecap.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/piratecap.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/sanji.png", 32, 40, 18, 22);
	LoadSprite("gfx/head/sanji_b.png", 32, 40, 18, 22);
	LoadSprite("gfx/body/sanji.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/ninja.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/ninja.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/agent.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/bpolice.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/gpolice.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/amp.png", 32, 40, 18, 22);
	LoadSprite("gfx/head/amp_b.png", 32, 40, 18, 22);
	LoadSprite("gfx/body/amp.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/river.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/river_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/river.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/frank.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/frank.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/waxknight.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/waxknight.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/flora.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/flora.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/body/deathknife.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/energyentity.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/deathweight.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/kelly.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/kelly.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/neveah.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/neveah.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/brook.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/brook.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/tom.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/tom.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/cindy.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/cindy_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/cindy.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/ozone.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/don.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/don.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/nate.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/nate.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/volcano.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/volcano.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/luna.png", 40, 40, 21, 22);
	LoadSprite("gfx/head/luna_b.png", 40, 40, 21, 22);
	LoadSprite("gfx/body/luna.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/body/unknown1.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/unknown2.png", 48, 48, 23, 33);
	LoadSprite("gfx/body/hellgoner.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/perry_knife.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/perry_knife.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/brian.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/brian.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/nekin.png", 32, 32, 18, 22);
	LoadSprite("gfx/head/nekin_b.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/nekin.png", 96, 64, 47, 45);
	
	LoadSprite("gfx/head/lulu_subspace.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/lulu_subspace.png", 64, 48, 31, 33);
	
	LoadSprite("gfx/head/adios.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/adios.png", 48, 48, 23, 33);
	
	LoadSprite("gfx/head/bulldog.png", 32, 32, 18, 22);
	LoadSprite("gfx/body/bulldog.png", 48, 48, 23, 33);
	
	
	
	LoadSprite("gfx/owchar/ruby.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ruby_run.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ruby_run_prepare.png", 32, 0, 15, 38);
	LoadSprite("gfx/owchar/ruby_flashlight.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ruby_blush.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ruby_zero.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ruby_zero2.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/noah.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/noah_run.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/emmet.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/emmet_run.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/sally.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/sally_run.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/perry.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/perry_run.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/hobo.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/hobo_1.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/navygang.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/navygang_1.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/leafcrew.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/leafcrew_alt.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/bashura.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/lisao.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/lulu.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/police_0.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/police_1.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/farmer.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/farmer_1.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/knifethug.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/vandal_knife.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/vandal_flail.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/nurse.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/jackie.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/electra.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/electra_purple.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ray.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/lulu_omega.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/slime.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/slimeboss.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/dia.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/spider.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/spiderboss.png", 64, 40, 31, 38);
	LoadSprite("gfx/owchar/policecap.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/sync.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/josh.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/pirate.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/pirate_1.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/piratecap.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/sanji.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ninja.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/agent_0.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/bpolice_0.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/bpolice_1.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/gpolice_0.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/amp.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ayaka.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/river.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/frank.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/sora.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/waxknight.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/sapphireton_diana.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/flora.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/kelly.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/neveah.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/brook.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/tom.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/cindy.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/ozone.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/don.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/nate.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/volcano.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/luna.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/viku.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/brian.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/nekin.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/lulu_subspace.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/adios.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/bulldog.png", 32, 40, 15, 38);
	
	LoadSprite("gfx/owchar/npc_0.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_1.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_2.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_3.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_4.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_5.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_6.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_7.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_8.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_9.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_10.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_11.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_12.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_13.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_14.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_15.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_16.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_17.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_18.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_19.png", 48, 40, 23, 38);
	LoadSprite("gfx/owchar/npc_20.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_21.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_22.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_23.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_24.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_25.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_26.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/npc_27.png", 32, 40, 15, 38);
	
	LoadSprite("gfx/owchar/rubin.png", 32, 40, 15, 38);
	
	LoadSprite("gfx/owchar/collapse/ruby.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/noah.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/emmet.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/sally.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/perry.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/dia.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/nekin.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/luna.png", 32, 64, 15, 38);
	LoadSprite("gfx/owchar/collapse/lulu_omega.png", 32, 64, 15, 38);
	
	LoadSprite("gfx/owchar/climb/ruby.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/climb/noah.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/climb/emmet.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/climb/sally.png", 32, 40, 15, 38);
	LoadSprite("gfx/owchar/climb/perry.png", 32, 40, 15, 38);
	
	
	
	LoadSprite("gfx/tileset/day.png", 16, 16, 0, 0);
	LoadSprite("gfx/tileset/day_forest.png", 16, 16, 0, 0);
	LoadSprite("gfx/tileset/day_autumn.png", 16, 16, 0, 0);
	LoadSprite("gfx/tileset/night.png", 16, 16, 0, 0);
	
	
	
	LoadSprite("gfx/spark/spark.png", 19, 0, 9, 9);
	LoadSprite("gfx/spark/punch.png", 15, 0, 7, 4);
	LoadSprite("gfx/spark/slash.png", 13, 0, 6, 15);
	LoadSprite("gfx/spark/star.png", 27, 0, 13, 13);
	LoadSprite("gfx/spark/vinespike.png", 8, 0, 4, 33);
	LoadSprite("gfx/spark/vinetrap.png", 18, 0, 8, 14);
	LoadSprite("gfx/spark/slashmagic.png", 15, 0, 8, 18);
	LoadSprite("gfx/spark/slashfirelu.png", 51, 0, 19, 13);
	LoadSprite("gfx/spark/saw.png", 13, 0, 6, 24);
	LoadSprite("gfx/spark/snow.png", 27, 0, 13, 14);
	LoadSprite("gfx/spark/ring.png", 37, 0, 18, 18);
	LoadSprite("gfx/spark/boost.png", 35, 0, 17, 28);
	
	
	
	LoadSprite("gfx/misc/shuriken.png", 0, 0, 5, 5);
	LoadSprite("gfx/misc/kunai.png", 0, 0, 10, 3);
	LoadSprite("gfx/misc/bomb.png", 0, 0, 4, 4);
	LoadSprite("gfx/misc/rocket.png", 0, 0, 10, 3);
	LoadSprite("gfx/misc/diamondcast.png", 7, 0, 3, 10);
	LoadSprite("gfx/misc/flameorb.png", 31, 0, 21, 9);
	LoadSprite("gfx/misc/waterbullet.png", 21, 0, 16, 3);
	LoadSprite("gfx/misc/ampbullet.png", 0, 0, 23, 4);
	LoadSprite("gfx/misc/amppulse.png", 11, 0, 6, 9);
	LoadSprite("gfx/misc/ampbeam.png", 1, 0, 0, 7);
	LoadSprite("gfx/misc/ampbeamstart.png", 15, 0, 9, 9);
	LoadSprite("gfx/misc/knife.png", 0, 0, 4, 2);
	LoadSprite("gfx/misc/knife2.png", 0, 0, 7, 1);
	LoadSprite("gfx/misc/rubydart.png", 0, 0, 3, 27);
	
	LoadSprite("gfx/misc/backdrop_hell.png", 0, 0, 0, 0);
	LoadSprite("gfx/misc/darkoverlay.png", 0, 0, 175, 175);
	LoadSprite("gfx/misc/darkoverlay_flashlight.png", 0, 0, 175, 175);
	LoadSprite("gfx/misc/bossbattlebg_0.png", 0, 0, 0, 0);
	LoadSprite("gfx/misc/bossbattlebg_1.png", 0, 0, 0, 0);
	LoadSprite("gfx/misc/bossbattlebg_2.png", 0, 0, 0, 0);
	LoadSprite("gfx/misc/bossbattlebg_3.png", 0, 0, 32, 32);
	LoadSprite("gfx/misc/bossbattlebg_4.png", 0, 0, 32, 32);
	LoadSprite("gfx/misc/bossbattlebg_5.png", 0, 0, 7, 16);
	LoadSprite("gfx/misc/bossbattlebg_6.png", 0, 0, 8, 3);
	LoadSprite("gfx/misc/bossbattlebg_7.png", 0, 0, 8, 4);
	LoadSprite("gfx/misc/bossbattlebg_8.png", 0, 0, 0, 0);
	LoadSprite("gfx/misc/savegem.png", 18, 0, 8, 20);
	LoadSprite("gfx/misc/brickwall.png", 0, 0, 48, 0);
	LoadSprite("gfx/misc/silverblock.png", 0, 0, 7, 36);
	LoadSprite("gfx/misc/silversakura.png", 0, 0, 16, 43);
	LoadSprite("gfx/misc/gems.png", 16, 0, 8, 15);
	LoadSprite("gfx/misc/key.png", 0, 0, 6, 6);
	LoadSprite("gfx/misc/spikes.png", 16, 0, 0, 9);
	LoadSprite("gfx/misc/mansionsofa.png", 0, 0, 15, 31);
	LoadSprite("gfx/misc/secretbossdoor.png", 0, 0, 24, 63);
	LoadSprite("gfx/misc/secretbosskey.png", 0, 0, 4, 3);
	LoadSprite("gfx/misc/secretbosskeylock.png", 0, 0, 4, 4);
	LoadSprite("gfx/misc/collapseblood.png", 23, 0, 11, 0);
	LoadSprite("gfx/misc/aquatree.png", 0, 0, 11, 36);
	LoadSprite("gfx/misc/policebarrier.png", 0, 0, 16, 15);
	
	LoadSprite("gfx/misc/lisao_sleep.png", 19, 0, 9, 13);
	LoadSprite("gfx/misc/ruby_wakeup.png", 32, 0, 0, 6);
	LoadSprite("gfx/misc/ruby_think.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/ruby_shrug.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/emmet_facepalm.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/sally_serious.png", 32, 0, 15, 38);
	LoadSprite("gfx/misc/perry_sleep.png", 21, 0, 11, 15);
	LoadSprite("gfx/misc/perryhomesleep.png", 32, 51, 15, 6);
	LoadSprite("gfx/misc/lulu_omega_rage.png", 27, 0, 14, 34);
	LoadSprite("gfx/misc/kelly_prepare.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/neveah_prepare.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/cindy_laugh.png", 32, 0, 15, 38);
	LoadSprite("gfx/misc/dia_hug.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/ruby_raisehands.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/ruby_beamsword.png", 36, 0, 10, 29);
	LoadSprite("gfx/misc/nekin_prepare.png", 0, 0, 12, 38);
	LoadSprite("gfx/misc/nate_worried.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/luna_pain.png", 0, 0, 15, 38);
	LoadSprite("gfx/misc/lulu_subspace_rage.png", 32, 0, 19, 34);
	LoadSprite("gfx/misc/sally_phone.png", 32, 0, 15, 38);
	LoadSprite("gfx/misc/npc_22_phone.png", 0, 0, 15, 38);
	
	LoadSprite("gfx/misc/sign_0.png", 0, 0, 8, 15);
	LoadSprite("gfx/misc/sign_1.png", 0, 0, 10, 21);
	LoadSprite("gfx/misc/sign_2.png", 0, 0, 8, 8);
	LoadSprite("gfx/misc/sign_3.png", 0, 0, 8, 8);
	LoadSprite("gfx/misc/rubybed.png", 32, 0, 0, 6);
	LoadSprite("gfx/misc/glasses.png", 0, 0, 6, 6);
	LoadSprite("gfx/misc/labcoat.png", 0, 0, 4, 16);
	LoadSprite("gfx/misc/rubycomputer.png", 0, 0, 8, 17);
	LoadSprite("gfx/misc/kevincomputer.png", 22, 0, 8, 17);
	LoadSprite("gfx/misc/laptop.png", 0, 0, 8, 13);
	LoadSprite("gfx/misc/tomatosoup.png", 0, 0, 3, 9);
	LoadSprite("gfx/misc/sapphirebus.png", 0, 71, 82, 70);
	LoadSprite("gfx/misc/bar_glass.png", 9, 9, 4, 8);
	LoadSprite("gfx/misc/perrypizza.png", 0, 0, 7, 8);
	LoadSprite("gfx/misc/perrypizza_broken.png", 0, 0, 7, 9);
	LoadSprite("gfx/misc/flashlight.png", 0, 0, 5, 5);
	LoadSprite("gfx/misc/present.png", 0, 0, 7, 19);
	LoadSprite("gfx/misc/flowergame.png", 8, 15, 3, 14);
	LoadSprite("gfx/misc/flowergame_button.png", 0, 0, 3, 5);
	LoadSprite("gfx/misc/diarynote.png", 0, 0, 4, 0);
	LoadSprite("gfx/misc/offserieso.png", 25, 0, 12, 10);
	LoadSprite("gfx/misc/computer.png", 0, 0, 8, 16);
	LoadSprite("gfx/misc/computer_1.png", 0, 0, 8, 14);
	LoadSprite("gfx/misc/ozonethrone.png", 0, 0, 16, 38);
	LoadSprite("gfx/misc/briefcase.png", 14, 0, 7, 14);
	LoadSprite("gfx/misc/healcapsule.png", 11, 0, 5, 5);
	LoadSprite("gfx/misc/sapphireship.png", 0, 128, 86, 127);
	LoadSprite("gfx/misc/dandelionneo.png", 9, 0, 3, 10);
	LoadSprite("gfx/misc/web.png", 0, 0, 7, 20);
	
	LoadSprite("gfx/misc/voidportal.png", 24, 0, 12, 24);
	LoadSprite("gfx/misc/hellgate.png", 0, 0, 46, 120);
	LoadSprite("gfx/misc/illusgate.png", 0, 0, 46, 120);
	LoadSprite("gfx/misc/hellgateboss.png", 43, 0, 20, 105);
	LoadSprite("gfx/misc/hellgateboss_off.png", 0, 0, 20, 105);
	LoadSprite("gfx/misc/healgeyser.png", 12, 0, 5, 42);
	LoadSprite("gfx/misc/illusknife.png", 0, 0, 4, 0);
	LoadSprite("gfx/misc/illusdoor.png", 44, 0, 21, 65);
	LoadSprite("gfx/misc/illusmonolith.png", 0, 0, 16, 65);
	LoadSprite("gfx/misc/timelinepuzzle.png", 120, 0, 60, 60);
	LoadSprite("gfx/misc/timelineblock.png", 8, 0, 4, 7);
	LoadSprite("gfx/misc/timelineslot.png", 0, 0, 4, 7);
	
	LoadSprite("gfx/misc/rubynobody_0.png", 0, 0, 15, 38);
	
	LoadSprite("gfx/misc/omegalulu.png", 0, 0, 0, 0);
	LoadSprite("gfx/misc/omegalulugun.png", 0, 0, 78, 7);
	LoadSprite("gfx/misc/omegalulugunfire.png", 0, 0, 72, 7);
	LoadSprite("gfx/misc/omegalulucannon_copyrighted.png", 0, 0, 48, 18);
	LoadSprite("gfx/misc/omegalulukatana.png", 0, 0, 12, 5);
	LoadSprite("gfx/misc/subspace_beam.png", 80, 0, 40, 239);
	LoadSprite("gfx/misc/subspace_redaura.png", 100, 0, 50, 50);
	
	LoadSprite("gfx/misc/gemia_map1.png", 0, 0, 79, 59);
	LoadSprite("gfx/misc/gemia_map2.png", 0, 0, 79, 59);
	LoadSprite("gfx/misc/cinema_rubyhouse.png", 0, 0, 79, 59);
	LoadSprite("gfx/misc/cinema_ruby.png", 0, 0, 79, 59);
	LoadSprite("gfx/misc/cinema_gems.png", 0, 0, 79, 59);
	LoadSprite("gfx/misc/cinema_rubyawakening.png", 0, 0, 79, 59);
	
	LoadSprite("gfx/misc/chess_pieces.png", 16, 16, 0, 0);
	
	
	
	LoadSprite("gfx/gui/rubindeavor.png", 0, 0, 29, 4);
	LoadSprite("gfx/gui/charbar.png", 0, 0, 12, 0);
	LoadSprite("gfx/gui/owcharbox.png", 0, 0, 0, 0);
	LoadSprite("gfx/gui/portraitbg.png", 0, 0, 0, 0);
	LoadSprite("gfx/gui/dialogbox.png", 4, 4, 0, 0);
	LoadSprite("gfx/gui/valuearrow.png", 7, 0, 6, 6);
	LoadSprite("gfx/gui/checkmark.png", 13, 0, 12, 6);
	LoadSprite("gfx/gui/markergem.png", 0, 0, 9, 6);
	LoadSprite("gfx/gui/speedgem.png", 0, 0, 8, 8);
	LoadSprite("gfx/gui/status.png", 16, 16, 7, 7);
	LoadSprite("gfx/gui/stat.png", 16, 16, 0, 0);
	
	
	
	LoadSprite("gfx/font/main.png", 8, 16, 0, 0);
	LoadSprite("gfx/font/main2.png", 8, 16, 0, 0);
	LoadSprite("gfx/font/small.png", 5, 8, 0, 0);
	
	
	#ifndef LOAD_SPRITES_FROM_FOLDER
	remove(TEMP_GFX_FILENAME);
	zip_close(za);
	#endif
}

void LoadSprite(const char* path, const int subW, const int subH, const int originX, const int originY) {
	//printf("Loading sprite: %s\n", path);
	if (spriteCount >= SPRITE_COUNT_MAX) {
		printf("Sprite count reached max\n");
		return;
	}
	
	#ifndef LOAD_SPRITES_FROM_FOLDER
	zip_file_t* zf = zip_fopen_encrypted(za, path, 0, ASSETS_PASSWORD);
	
	void* zbuf = malloc(1024*1024);
	int zbuf_size = zip_fread(zf, zbuf, 1024*1024);
	
	FILE* tf = fopen(TEMP_GFX_FILENAME, "wb");
	fwrite(zbuf, 1, zbuf_size, tf);
	fclose(tf);
	
	zip_fclose(zf);
	
	
	
	SDL_Surface* surface = IMG_Load(TEMP_GFX_FILENAME);
	#else
	SDL_Surface* surface = IMG_Load(path);
	#endif
	
	if (surface == NULL) {
		printf("Sprite loading error: %s\n", path);
		return;
	}
	
	#ifndef LOAD_SPRITES_FROM_FOLDER
	sprites[spriteCount].texture = IMG_LoadTexture(globalRenderer, TEMP_GFX_FILENAME);
	#else
	sprites[spriteCount].texture = IMG_LoadTexture(globalRenderer, path);
	#endif
	
	if (sprites[spriteCount].texture == NULL) {
		printf("Sprite loading error: %s\n", path);
		return;
	}
	
	sprites[spriteCount].w = surface->w;
	sprites[spriteCount].h = surface->h;
	sprites[spriteCount].subW = (subW == 0) ? surface->w : subW;
	sprites[spriteCount].subH = (subH == 0) ? surface->h : subH;
	sprites[spriteCount].originX = originX;
	sprites[spriteCount].originY = originY;
	
	sprites[spriteCount].subImagesPerRow = sprites[spriteCount].w / sprites[spriteCount].subW;
	sprites[spriteCount].subImages = sprites[spriteCount].subImagesPerRow * sprites[spriteCount].h / sprites[spriteCount].subH;
	
	sprites[spriteCount].color[0] = 255;
	sprites[spriteCount].color[1] = 255;
	sprites[spriteCount].color[2] = 255;
	sprites[spriteCount].alpha = 255;
	sprites[spriteCount].blendMode = SDL_BLENDMODE_BLEND;
	
	spriteCount++;
	SDL_FreeSurface(surface);
}

void FreeSprites() {
	for (int i = 0; i < spriteCount; i++) {
		if (sprites[i].texture == NULL) continue;
		SDL_DestroyTexture(sprites[i].texture);
	}
}

void DrawSprite(int spriteId, float x, float y, int subImage, float xScale, float yScale) {
	if (spriteId < 0 || spriteId >= spriteCount) return;
	if (subImage >= sprites[spriteId].subImages) subImage = sprites[spriteId].subImages - 1;
	
	int srcX = (subImage % sprites[spriteId].subImagesPerRow) * sprites[spriteId].subW;
	int srcY = (subImage / sprites[spriteId].subImagesPerRow) * sprites[spriteId].subH;
	int srcW = sprites[spriteId].subW;
	int srcH = sprites[spriteId].subH;
	
	double destX = GetScreenX(x - (double)sprites[spriteId].originX * xScale);
	double destY = GetScreenY(y - (double)sprites[spriteId].originY * yScale);
	double destW = (double)sprites[spriteId].subW * xScale * gameDrawState.projection_zoom;
	double destH = (double)sprites[spriteId].subH * yScale * gameDrawState.projection_zoom;
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (xScale < 0) {
		destW = -destW;
		destX -= destW;
		flip |= SDL_FLIP_HORIZONTAL;
	}
	if (yScale < 0) {
		destH = -destH;
		destY -= destH;
		flip |= SDL_FLIP_VERTICAL;
	}
	
	if (1 || sprites[spriteId].color[0] != gameDrawState.color[0] || sprites[spriteId].color[1] != gameDrawState.color[1] || sprites[spriteId].color[2] != gameDrawState.color[2]) {
		SDL_SetTextureColorMod(sprites[spriteId].texture, gameDrawState.color[0], gameDrawState.color[1], gameDrawState.color[2]);
		sprites[spriteId].color[0] = gameDrawState.color[0];
		sprites[spriteId].color[1] = gameDrawState.color[1];
		sprites[spriteId].color[2] = gameDrawState.color[2];
	}
	if (1 || sprites[spriteId].alpha != gameDrawState.alpha) {
		SDL_SetTextureAlphaMod(sprites[spriteId].texture, gameDrawState.alpha);
		sprites[spriteId].alpha = gameDrawState.alpha;
	}
	if (1 || sprites[spriteId].blendMode != gameDrawState.blendMode) {
		SDL_SetTextureBlendMode(sprites[spriteId].texture, gameDrawState.blendMode);
		sprites[spriteId].blendMode = gameDrawState.blendMode;
	}
	
	SDL_RenderCopyEx(globalRenderer, sprites[spriteId].texture,
		&(SDL_Rect){ srcX, srcY, srcW, srcH },
		&(SDL_Rect){ destX, destY, destW, destH },
		0,
		&(SDL_Point){ sprites[spriteId].originX, sprites[spriteId].originY },
		flip
	);
}

void DrawSprite_Angle(int spriteId, float x, float y, int subImage, float xScale, float yScale, float angle) {
	if (spriteId < 0 || spriteId >= spriteCount) return;
	if (subImage >= sprites[spriteId].subImages) subImage = sprites[spriteId].subImages - 1;
	
	int srcX = (subImage % sprites[spriteId].subImagesPerRow) * sprites[spriteId].subW;
	int srcY = (subImage / sprites[spriteId].subImagesPerRow) * sprites[spriteId].subH;
	int srcW = sprites[spriteId].subW;
	int srcH = sprites[spriteId].subH;
	
	float destX = GetScreenX(x - (float)sprites[spriteId].originX * xScale);
	float destY = GetScreenY(y - (float)sprites[spriteId].originY * yScale);
	float destW = (float)sprites[spriteId].subW * xScale * gameDrawState.projection_zoom;
	float destH = (float)sprites[spriteId].subH * yScale * gameDrawState.projection_zoom;
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (xScale < 0) {
		destW = -destW;
		destX -= destW;
		flip |= SDL_FLIP_HORIZONTAL;
		xScale = -xScale;
	}
	if (yScale < 0) {
		destH = -destH;
		destY -= destH;
		flip |= SDL_FLIP_VERTICAL;
		yScale = -yScale;
	}
	
	if (1 || sprites[spriteId].color[0] != gameDrawState.color[0] || sprites[spriteId].color[1] != gameDrawState.color[1] || sprites[spriteId].color[2] != gameDrawState.color[2]) {
		SDL_SetTextureColorMod(sprites[spriteId].texture, gameDrawState.color[0], gameDrawState.color[1], gameDrawState.color[2]);
		sprites[spriteId].color[0] = gameDrawState.color[0];
		sprites[spriteId].color[1] = gameDrawState.color[1];
		sprites[spriteId].color[2] = gameDrawState.color[2];
	}
	if (1 || sprites[spriteId].alpha != gameDrawState.alpha) {
		SDL_SetTextureAlphaMod(sprites[spriteId].texture, gameDrawState.alpha);
		sprites[spriteId].alpha = gameDrawState.alpha;
	}
	if (1 || sprites[spriteId].blendMode != gameDrawState.blendMode) {
		SDL_SetTextureBlendMode(sprites[spriteId].texture, gameDrawState.blendMode);
		sprites[spriteId].blendMode = gameDrawState.blendMode;
	}
	
	SDL_RenderCopyEx(globalRenderer, sprites[spriteId].texture,
		&(SDL_Rect){ srcX, srcY, srcW, srcH },
		&(SDL_Rect){ destX, destY, destW, destH },
		angle,
		&(SDL_Point){ sprites[spriteId].originX * xScale * gameDrawState.projection_zoom, sprites[spriteId].originY * yScale * gameDrawState.projection_zoom },
		flip
	);
}

void DrawText(const unsigned char* text, int length, float x, float y, float xScale, float yScale) {
	int spriteId = gameDrawState.fontSpriteId;
	float charX = x;
	float charY = y;
	float dx = sprites[spriteId].subW * xScale;
	float dy = sprites[spriteId].subH * yScale;
	
	if (spriteId == SPR_font_main || spriteId == SPR_font_main2) dy = dy * 7 / 8;
	
	float w = dx;
	float h = dy;
	
	{
		int tempLength = 0;
		int maxLength = 0;
		for (int i = 0; i < 65536; i++) {
			if (text[i] == 0) {
				if (tempLength > maxLength) maxLength = tempLength;
				tempLength = 0;
				break;
			}
			if (text[i] == '\n') {
				h += dy;
				if (tempLength > maxLength) maxLength = tempLength;
				tempLength = 0;
				continue;
			}
			tempLength++;
		}
		w *= maxLength;
	}
	
	int alignment = gameDrawState.fontAlignment;
	
	if ((alignment & 3) == FONT_ALIGN_MIDDLE) {
		x -= w / 2;
		charX -= w / 2;
	}
	else if ((alignment & 3) == FONT_ALIGN_RIGHT) {
		x -= w;
		charX -= w;
	}
	
	if ((alignment & 12) == FONT_ALIGN_CENTER) {
		y -= h / 2;
		charY -= h / 2;
	}
	else if ((alignment & 12) == FONT_ALIGN_BOTTOM) {
		y -= h;
		charY -= h;
	}
	
	uint8_t prevColors[3] = { gameDrawState.color[0], gameDrawState.color[1], gameDrawState.color[2] };
	
	for (int i = 0; i < length; i++) {
		if (text[i] == 0) break;
		
		if (text[i] == '\n') {
			charX = x;
			charY += dy;
			continue;
		}
		
		if (text[i] == 0x8f) {
			uint8_t colors[3] = {255, 255, 255};
			i++;
			switch (text[i]) {
				case 1: colors[0] = 255; colors[1] = 0; colors[2] = 0; break;
				case 2: colors[0] = 0; colors[1] = 191; colors[2] = 0; break;
				case 3: colors[0] = 0; colors[1] = 0; colors[2] = 255; break;
				case 4: colors[0] = 255; colors[1] = 255; colors[2] = 0; break;
				case 5: colors[0] = 255; colors[1] = 0; colors[2] = 255; break;
				case 6: colors[0] = 0; colors[1] = 191; colors[2] = 255; break;
				case 7: colors[0] = 255; colors[1] = 255; colors[2] = 255; break;
				case 255: colors[0] = prevColors[0]; colors[1] = prevColors[1]; colors[2] = prevColors[2]; break;
			}
			SetDrawColor(colors[0], colors[1], colors[2]);
			continue;
		}
		else if (text[i] == 0x90) {
			i++;
			DrawSprite(SPR_gui_stat, charX, charY, text[i] - 1, xScale, yScale);
			
			if (game.settings.showStatSymbolLabels) {
				int prevFont = spriteId;
				SetFontSprite(SPR_font_small);
				switch (text[i] - 1) {
					case 0: SetString(game.textBuffer, "hp"); break;
					case 1: SetString(game.textBuffer, "mp"); break;
					case 2: SetString(game.textBuffer, "atk"); break;
					case 3: SetString(game.textBuffer, "def"); break;
					case 4: SetString(game.textBuffer, "spd"); break;
					case 5: SetString(game.textBuffer, "pow"); break;
					case 6: SetString(game.textBuffer, "gp"); break;
				}
				DrawText(game.textBuffer, 4, charX + 2, charY + 16, 2, 2);
				SetFontSprite(prevFont);
			}
		}
		else if (text[i] >= 33) {
			DrawSprite(spriteId, charX, charY, text[i] - 33, xScale, yScale);
			if (profile.tempFlags[TEMPFLAG_ILLUSION_HYPERHELL]) {
				SetDrawAlpha(255);
				SetDrawBlend(SDL_BLENDMODE_MUL);
				SetDrawColor(255, 127 * (game.timer % 32 >= 24), 0);
				DrawSprite(SPR_misc_bossbattlebg_1, charX, charY, 0, 0.25, 0.5);
				SetDrawAlpha(63);
				SetDrawBlend(SDL_BLENDMODE_ADD);
				SetDrawColor(255, 255 * (game.timer % 32 < 16), 0);
				DrawSprite(SPR_misc_bossbattlebg_0, charX - 1, charY, 0, 0.25, 0.5);
				SetDrawColor(255, 255 * (game.timer % 32 >= 16), 0);
				DrawSprite(SPR_misc_bossbattlebg_0, charX + 1, charY, 0, 0.25, 0.5);
				SetDrawAlpha(255);
				SetDrawBlend(SDL_BLENDMODE_BLEND);
				SetDrawColor(prevColors[0], prevColors[1], prevColors[2]);
			}
		}
		charX += dx;
	}
	
	SetDrawColor(prevColors[0], prevColors[1], prevColors[2]);
}

void FillRect(float x, float y, float w, float h) {
	SDL_RenderFillRectF(globalRenderer,
	&(SDL_FRect){ GetScreenX(x),
	GetScreenY(y),
	w * gameDrawState.projection_zoom,
	h * gameDrawState.projection_zoom });
}



void SetProjection(float x, float y, float zoom) {
	gameDrawState.projection_x = x;
	gameDrawState.projection_y = y;
	gameDrawState.projection_zoom = zoom;
}

void SetDrawColor(uint8_t r, uint8_t g, uint8_t b) {
	gameDrawState.color[0] = r;
	gameDrawState.color[1] = g;
	gameDrawState.color[2] = b;
	SDL_SetRenderDrawColor(globalRenderer, gameDrawState.color[0], gameDrawState.color[1], gameDrawState.color[2], gameDrawState.alpha);
}

void SetDrawAlpha(uint8_t a) {
	gameDrawState.alpha = a;
	SDL_SetRenderDrawColor(globalRenderer, gameDrawState.color[0], gameDrawState.color[1], gameDrawState.color[2], gameDrawState.alpha);
}

void SetDrawBlend(SDL_BlendMode blendMode) {
	gameDrawState.blendMode = blendMode;
	SDL_SetRenderDrawBlendMode(globalRenderer, blendMode);
}

void SetFontSprite(int spriteId) {
	gameDrawState.fontSpriteId = spriteId;
}

void SetFontAlignment(int alignment) {
	gameDrawState.fontAlignment = alignment;
}
