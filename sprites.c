#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "zip.h"

#include "generic.h"
#include "sprites.h"
#include "profile.h"

const int FIRST_SPR_owchar = SPR_owchar_ruby;
const int LAST_SPR_owchar = SPR_owchar_rubin;

const int firstTilesetSpriteId = SPR_tileset_day;
const int lastTilesetSpriteId = SPR_tileset_night;

DrawerSystem drawerSystem;

struct zip_t* za;
const char* ASSETS_PASSWORD = "the master lulu";
const char* TEMP_GFX_FILENAME = "TEMP";

void LoadSprites() {
	#ifndef RXS_LOAD_SPRITES_FROM_FOLDER
		za = zip_open("assets.dat", ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
		if (za == NULL) {
			printf("Failed to read assets.dat\n");
			return;
		}
	#endif
	
	
	
	drawerSystem.spriteCount = 0;
	
	Drawer_LoadSprite("gfx/head/ruby.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/ruby.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/ruby_zero.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/ruby_armed.png", 64, 48, 31, 33);
	Drawer_LoadSprite("gfx/head/ruby_god.png", 32, 32, 18, 22);
	
	Drawer_LoadSprite("gfx/body/rubin.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/noah.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/noah.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/emmet.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/emmet.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/sally.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/sally_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/sally.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/sally_neo.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/sally_neo.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/diego.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/diego.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/perry.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/perry.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/anonymous.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_0.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_1.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_2.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_3.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_4.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_5.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_6.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_7.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_8.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_9.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_9_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_10.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_11.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_11_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_12.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_13.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_14.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_15.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_16.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_17.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_18.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_19.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/generic_20.png", 32, 32, 18, 22);
	
	Drawer_LoadSprite("gfx/body/hobo.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/navygang.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/leafcrew.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/bashura.png", 32, 32, 18, 22);
	
	Drawer_LoadSprite("gfx/head/lisao.png", 32, 40, 18, 22);
	Drawer_LoadSprite("gfx/head/lisao_b.png", 32, 40, 18, 22);
	Drawer_LoadSprite("gfx/body/lisao.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/lulu.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/lulu.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/lulu_blaze.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/police.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/farmer.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/knifethug.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/vandal_knife.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/vandal_flail.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/nurse.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/jackie.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/jackie.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/electra.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/electra.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/ray.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/ray_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/ray.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/lulu_omega.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/slime.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/slimesuit.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/slimeboss.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/dia.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/dia_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/dia.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/spider.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/spidersuit.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/spiderboss.png", 64, 48, 31, 42);
	
	Drawer_LoadSprite("gfx/head/policecap.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/policecap.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/sync.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/sync.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/josh.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/josh.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/pirate.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/pirate.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/piratecap.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/piratecap.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/sanji.png", 32, 40, 18, 22);
	Drawer_LoadSprite("gfx/head/sanji_b.png", 32, 40, 18, 22);
	Drawer_LoadSprite("gfx/body/sanji.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/ninja.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/ninja.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/agent.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/bpolice.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/gpolice.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/amp.png", 32, 40, 18, 22);
	Drawer_LoadSprite("gfx/head/amp_b.png", 32, 40, 18, 22);
	Drawer_LoadSprite("gfx/body/amp.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/river.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/river_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/river.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/frank.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/frank.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/waxknight.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/waxknight.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/flora.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/flora.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/body/deathknife.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/energyentity.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/deathweight.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/kelly.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/kelly.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/neveah.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/neveah.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/brook.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/brook.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/tom.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/tom.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/cindy.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/cindy_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/cindy.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/ozone.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/don.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/don.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/nate.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/nate.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/volcano.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/volcano.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/luna.png", 40, 40, 21, 22);
	Drawer_LoadSprite("gfx/head/luna_b.png", 40, 40, 21, 22);
	Drawer_LoadSprite("gfx/body/luna.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/unknown1.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/unknown2.png", 48, 48, 23, 33);
	Drawer_LoadSprite("gfx/body/hellgoner.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/perry_knife.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/perry_knife.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/brian.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/brian.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/nekin.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/nekin_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/nekin.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/lulu_subspace.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/lulu_subspace.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/adios.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/adios.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/bulldog.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/bulldog.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/kyle.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/kyle.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/builder.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/tia.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/tia_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/tia.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/kara.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/kara.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/camilla.png", 40, 40, 21, 22);
	Drawer_LoadSprite("gfx/head/camilla_b.png", 40, 40, 21, 22);
	Drawer_LoadSprite("gfx/body/camilla.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/ayinoying.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/ayinoying.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/aztec.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/aztec.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/dirk.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/dirk.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/body/whitelight.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/rob.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/rob.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/mani.png", 40, 40, 21, 22);
	Drawer_LoadSprite("gfx/body/mani.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/timon.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/timon.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/gregory.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/gregory.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/violet.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/violet.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/reti.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/reti.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/lulu_master.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/lulu_master.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/lulu_god.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/lulu_god.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/panda.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/panda.png", 64, 48, 31, 33);
	
	Drawer_LoadSprite("gfx/head/maline.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/maline_b.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/maline.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/head/cory.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/cory.png", 96, 64, 47, 45);
	
	Drawer_LoadSprite("gfx/body/onyxagent.png", 48, 48, 23, 33);
	
	Drawer_LoadSprite("gfx/head/vincent.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/jerry.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/head/ohio.png", 40, 40, 21, 22);
	Drawer_LoadSprite("gfx/head/kaiser.png", 32, 32, 18, 22);
	
	Drawer_LoadSprite("gfx/head/lulu_ultimate.png", 32, 32, 18, 22);
	Drawer_LoadSprite("gfx/body/lulu_ultimate.png", 96, 64, 47, 45);
	
	
	
	Drawer_LoadSprite("gfx/owchar/ruby.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_run_prepare.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_flashlight.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_blush.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_zero.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_zero2.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_teen.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_nmg.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_god.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_god_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ruby_god_run_prepare.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/owchar/noah.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/noah_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/emmet.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/emmet_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sally.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sally_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sally_neo.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sally_neo_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/diego.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/diego_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/perry.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/perry_run.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/hobo.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/hobo_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/navygang.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/navygang_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/leafcrew.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/leafcrew_alt.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/bashura.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lisao.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lulu.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/police_0.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/police_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/farmer.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/farmer_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/knifethug.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/vandal_knife.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/vandal_flail.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/nurse.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/jackie.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/electra.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/electra_purple.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ray.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lulu_omega.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/slime.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/slimeboss.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/dia.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/spider.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/spiderboss.png", 64, 40, 31, 38);
	Drawer_LoadSprite("gfx/owchar/policecap.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sync.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/josh.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/pirate.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/pirate_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/piratecap.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sanji.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ninja.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/agent_0.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/bpolice_0.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/bpolice_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/gpolice_0.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/amp.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ayaka.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/river.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/frank.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sora.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/waxknight.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/sapphireton_diana.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/flora.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/kelly.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/neveah.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/brook.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/tom.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/cindy.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ozone.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/don.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/nate.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/volcano.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/luna.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/viku.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/brian.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/nekin.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lulu_subspace.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/adios.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/bulldog.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/kyle.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/builder.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/tia.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/kara.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/camilla.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ayinoying.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/aztec.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/dirk.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/whitelight_0.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/whitelight_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/rob.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/mani.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/timon.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/gregory.png", 64, 40, 31, 38);
	Drawer_LoadSprite("gfx/owchar/violet.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/reti.png", 32, 40, 15, 39);
	Drawer_LoadSprite("gfx/owchar/reti_mask.png", 32, 40, 15, 39);
	Drawer_LoadSprite("gfx/owchar/lulu_cloak.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lulu_cloak2.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lulu_master.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lulu_god.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/panda.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/maline.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/cory.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/vincent.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/jerry.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/ohio.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/kaiser.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/lulu_ultimate.png", 32, 40, 15, 38);
	
	Drawer_LoadSprite("gfx/owchar/npc_0.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_1.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_2.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_3.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_4.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_5.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_6.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_7.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_8.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_9.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_10.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_11.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_12.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_13.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_14.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_15.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_16.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_17.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_18.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_19.png", 48, 40, 23, 38);
	Drawer_LoadSprite("gfx/owchar/npc_20.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_21.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_22.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_23.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_24.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_25.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_26.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_27.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_28.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_29.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_30.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_31.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_32.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_33.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_34.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_35.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_36.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_37.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_38.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_39.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_40.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_41.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_42.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_43.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/npc_44.png", 32, 40, 15, 38);
	
	Drawer_LoadSprite("gfx/owchar/rubin.png", 32, 40, 15, 38);
	
	Drawer_LoadSprite("gfx/owchar/collapse/ruby.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/ruby_teen.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/ruby_god.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/noah.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/emmet.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/sally.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/sally_neo.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/diego.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/perry.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/panda.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/dia.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/nekin.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/luna.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/lulu_omega.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/amp.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/maline.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/cory.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/npc_41.png", 32, 64, 15, 38);
	Drawer_LoadSprite("gfx/owchar/collapse/npc_42.png", 32, 64, 15, 38);
	
	Drawer_LoadSprite("gfx/owchar/climb/ruby.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/climb/ruby_god.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/climb/noah.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/climb/emmet.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/climb/sally.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/climb/sally_neo.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/climb/diego.png", 32, 40, 15, 38);
	Drawer_LoadSprite("gfx/owchar/climb/perry.png", 32, 40, 15, 38);
	
	
	
	Drawer_LoadSprite("gfx/tileset/day.png", 16, 16, 0, 0);
	Drawer_LoadSprite("gfx/tileset/day_forest.png", 16, 16, 0, 0);
	Drawer_LoadSprite("gfx/tileset/day_autumn.png", 16, 16, 0, 0);
	Drawer_LoadSprite("gfx/tileset/night.png", 16, 16, 0, 0);
	
	
	
	Drawer_LoadSprite("gfx/spark/spark.png", 19, 0, 9, 9);
	Drawer_LoadSprite("gfx/spark/punch.png", 15, 0, 7, 4);
	Drawer_LoadSprite("gfx/spark/slash.png", 13, 0, 6, 15);
	Drawer_LoadSprite("gfx/spark/star.png", 27, 0, 13, 13);
	Drawer_LoadSprite("gfx/spark/vinespike.png", 8, 0, 4, 33);
	Drawer_LoadSprite("gfx/spark/vinetrap.png", 18, 0, 8, 14);
	Drawer_LoadSprite("gfx/spark/slashmagic.png", 15, 0, 8, 18);
	Drawer_LoadSprite("gfx/spark/slashfirelu.png", 51, 0, 19, 13);
	Drawer_LoadSprite("gfx/spark/slashicely.png", 60, 0, 31, 20);
	Drawer_LoadSprite("gfx/spark/slashamp.png", 49, 0, 18, 22);
	Drawer_LoadSprite("gfx/spark/slashbeam.png", 37, 0, 17, 21);
	Drawer_LoadSprite("gfx/spark/slashcory.png", 76, 0, 35, 50);
	Drawer_LoadSprite("gfx/spark/slashcorycombo.png", 99, 0, 35, 51);
	Drawer_LoadSprite("gfx/spark/slashmaline.png", 36, 0, 12, 16);
	Drawer_LoadSprite("gfx/spark/saw.png", 13, 0, 6, 24);
	Drawer_LoadSprite("gfx/spark/snow.png", 27, 0, 13, 14);
	Drawer_LoadSprite("gfx/spark/flower.png", 29, 0, 14, 14);
	Drawer_LoadSprite("gfx/spark/ring.png", 37, 0, 18, 18);
	Drawer_LoadSprite("gfx/spark/boost.png", 35, 0, 17, 28);
	Drawer_LoadSprite("gfx/spark/slashultra.png", 74, 0, 39, 87);
	Drawer_LoadSprite("gfx/spark/slashhyper.png", 137, 0, 63, 71);
	Drawer_LoadSprite("gfx/spark/slashcamilla.png", 54, 0, 33, 26);
	Drawer_LoadSprite("gfx/spark/brickwall.png", 0, 5, 20, 5);
	Drawer_LoadSprite("gfx/spark/petalbg.png", 32, 0, 0, 0);
	Drawer_LoadSprite("gfx/spark/blazeoblivion.png", 158, 0, 56, 34);
	Drawer_LoadSprite("gfx/spark/blazewave.png", 0, 0, 49, 85);
	Drawer_LoadSprite("gfx/spark/blazeimpact.png", 95, 0, 49, 124);
	Drawer_LoadSprite("gfx/spark/tsunami.png", 16, 0, 8, 24);
	Drawer_LoadSprite("gfx/spark/superfreeze.png", 72, 0, 35, 35);
	Drawer_LoadSprite("gfx/spark/ultlulubolt.png", 83, 0, 41, 221);
	Drawer_LoadSprite("gfx/spark/ultluluimpact.png", 95, 0, 49, 124);
	Drawer_LoadSprite("gfx/spark/ultlulubeam.png", 0, 136, 0, 68);
	Drawer_LoadSprite("gfx/spark/blood.png", 88, 0, 87, 56);
	
	
	
	Drawer_LoadSprite("gfx/misc/shuriken.png", 0, 0, 5, 5);
	Drawer_LoadSprite("gfx/misc/kunai.png", 0, 0, 10, 3);
	Drawer_LoadSprite("gfx/misc/bomb.png", 0, 0, 4, 4);
	Drawer_LoadSprite("gfx/misc/rocket.png", 0, 0, 10, 3);
	Drawer_LoadSprite("gfx/misc/diamondcast.png", 7, 0, 3, 10);
	Drawer_LoadSprite("gfx/misc/flameorb.png", 31, 0, 21, 9);
	Drawer_LoadSprite("gfx/misc/waterbullet.png", 21, 0, 16, 3);
	Drawer_LoadSprite("gfx/misc/ampbullet.png", 0, 0, 23, 4);
	Drawer_LoadSprite("gfx/misc/amppulse.png", 11, 0, 6, 9);
	Drawer_LoadSprite("gfx/misc/ampbeam.png", 1, 0, 0, 7);
	Drawer_LoadSprite("gfx/misc/ampbeamstart.png", 15, 0, 9, 9);
	Drawer_LoadSprite("gfx/misc/knife.png", 0, 0, 4, 2);
	Drawer_LoadSprite("gfx/misc/knife2.png", 0, 0, 7, 1);
	Drawer_LoadSprite("gfx/misc/rubydart.png", 0, 0, 3, 27);
	Drawer_LoadSprite("gfx/misc/paperplane.png", 11, 0, 5, 7);
	Drawer_LoadSprite("gfx/misc/hellspike.png", 0, 0, 26, 62);
	Drawer_LoadSprite("gfx/misc/pandadart.png", 0, 0, 16, 2);
	Drawer_LoadSprite("gfx/misc/malinewave.png", 15, 0, 7, 7);
	Drawer_LoadSprite("gfx/misc/malinewavebig.png", 33, 0, 16, 16);
	Drawer_LoadSprite("gfx/misc/ultluluorb.png", 49, 0, 24, 24);
	
	Drawer_LoadSprite("gfx/misc/backdrop_hell.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/backdrop_brilliant.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/backdrop_redmountains.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/backdrop_lisaohouse.png", 320, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/darkoverlay.png", 0, 0, 175, 175);
	Drawer_LoadSprite("gfx/misc/darkoverlay_flashlight.png", 0, 0, 175, 175);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_0.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_1.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_2.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_3.png", 0, 0, 32, 32);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_4.png", 0, 0, 32, 32);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_5.png", 0, 0, 7, 16);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_6.png", 0, 0, 8, 3);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_7.png", 0, 0, 8, 4);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_8.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_9.png", 0, 0, 32, 32);
	Drawer_LoadSprite("gfx/misc/bossbattlebg_10.png", 256, 0, 128, 128);
	Drawer_LoadSprite("gfx/misc/savegem.png", 18, 0, 8, 20);
	Drawer_LoadSprite("gfx/misc/brickwall.png", 0, 0, 48, 0);
	Drawer_LoadSprite("gfx/misc/silverblock.png", 0, 0, 7, 36);
	Drawer_LoadSprite("gfx/misc/silversakura.png", 0, 0, 16, 43);
	Drawer_LoadSprite("gfx/misc/gems.png", 16, 0, 8, 15);
	Drawer_LoadSprite("gfx/misc/key.png", 0, 0, 6, 6);
	Drawer_LoadSprite("gfx/misc/spikes.png", 16, 0, 0, 9);
	Drawer_LoadSprite("gfx/misc/mansionsofa.png", 0, 0, 15, 31);
	Drawer_LoadSprite("gfx/misc/secretbossdoor.png", 0, 0, 24, 63);
	Drawer_LoadSprite("gfx/misc/secretbosskey.png", 0, 0, 4, 3);
	Drawer_LoadSprite("gfx/misc/secretbosskeylock.png", 0, 0, 4, 4);
	Drawer_LoadSprite("gfx/misc/collapseblood.png", 23, 0, 11, 0);
	Drawer_LoadSprite("gfx/misc/aquatree.png", 0, 0, 11, 36);
	Drawer_LoadSprite("gfx/misc/policebarrier.png", 0, 0, 16, 15);
	Drawer_LoadSprite("gfx/misc/spolis_exit.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/spolis_exitbarrier.png", 0, 16, 96, 16);
	Drawer_LoadSprite("gfx/misc/brilliant_crystal1.png", 0, 0, 16, 32);
	Drawer_LoadSprite("gfx/misc/brilliant_crystal2.png", 0, 0, 24, 48);
	Drawer_LoadSprite("gfx/misc/brilliant_crystal3.png", 0, 0, 8, 80);
	Drawer_LoadSprite("gfx/misc/spyingtelescope.png", 0, 0, 7, 20);
	Drawer_LoadSprite("gfx/misc/gregoryguide.png", 0, 0, 55, 160);
	Drawer_LoadSprite("gfx/misc/gregoryscythe.png", 0, 0, 10, 0);
	Drawer_LoadSprite("gfx/misc/gregorygun.png", 0, 0, 5, 0);
	
	Drawer_LoadSprite("gfx/misc/lisao_sleep.png", 19, 0, 9, 13);
	Drawer_LoadSprite("gfx/misc/lisao_sleepawake.png", 0, 0, 9, 13);
	Drawer_LoadSprite("gfx/misc/lisao_sit.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lisao_hug.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lisao_happy.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_wakeup.png", 32, 0, 0, 6);
	Drawer_LoadSprite("gfx/misc/ruby_think.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_shrug.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_hug.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_suppressed.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_sit.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_rage.png", 19, 0, 10, 31);
	Drawer_LoadSprite("gfx/misc/ruby_teen_draw.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_teen_slap.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_nmg_suppressed.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/noah_hug.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/noah_sit.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/emmet_facepalm.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/emmet_sit.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/sally_serious.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/sally_phone.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/sally_sit.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/sally_neo_serious.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/sally_neo_hug.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/sally_neo_sit.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/diego_greet.png", 48, 0, 23, 38);
	Drawer_LoadSprite("gfx/misc/diego_sit.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/perry_sleep.png", 21, 0, 11, 15);
	Drawer_LoadSprite("gfx/misc/perry_sit.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/perryhomesleep.png", 32, 51, 15, 6);
	Drawer_LoadSprite("gfx/misc/panda_beamsword.png", 40, 0, 10, 30);
	Drawer_LoadSprite("gfx/misc/lulu_omega_rage.png", 27, 0, 14, 34);
	Drawer_LoadSprite("gfx/misc/lulu_cloakthrow.png", 0, 0, 17, 22);
	Drawer_LoadSprite("gfx/misc/lulu_cloak_happy.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_master_rage.png", 27, 0, 14, 34);
	Drawer_LoadSprite("gfx/misc/lulu_master_hug.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_master_flushed.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_master_broken.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_god_rage.png", 27, 0, 14, 34);
	Drawer_LoadSprite("gfx/misc/lulu_god_hug.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_god_entry.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_god_entryland.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_god_cry.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_ultimate_stagger.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_ultimate_rage.png", 28, 0, 15, 34);
	Drawer_LoadSprite("gfx/misc/kelly_prepare.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/neveah_prepare.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/cindy_laugh.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/dia_hug.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_raisehands.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/ruby_beamsword.png", 36, 0, 10, 29);
	Drawer_LoadSprite("gfx/misc/nekin_prepare.png", 0, 0, 12, 38);
	Drawer_LoadSprite("gfx/misc/nate_worried.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/luna_pain.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/lulu_subspace_rage.png", 32, 0, 19, 34);
	Drawer_LoadSprite("gfx/misc/kara_jump.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/amp_sit.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/amp_kneel.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/gregory_defeated.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/npc_22_phone.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/npc_33_arms.png", 0, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/npc_35_dj.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/npc_36_floss.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/npc_38_dance.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/npc_39_sweep.png", 32, 0, 15, 36);
	Drawer_LoadSprite("gfx/misc/npc_41_slapped.png", 32, 0, 15, 38);
	Drawer_LoadSprite("gfx/misc/gemini.png", 26, 0, 13, 34);
	Drawer_LoadSprite("gfx/misc/gemini_collapsed.png", 27, 0, 13, 16);
	Drawer_LoadSprite("gfx/misc/redgreenbatterlookingidiot.png", 24, 0, 12, 33);
	Drawer_LoadSprite("gfx/misc/pbsuperhero.png", 50, 0, 16, 43);
	Drawer_LoadSprite("gfx/misc/pbsuperhero_certificate.png", 42, 0, 25, 23);
	Drawer_LoadSprite("gfx/misc/dystal.png", 52, 0, 27, 57);
	Drawer_LoadSprite("gfx/misc/dystal_final.png", 47, 0, 23, 43);
	Drawer_LoadSprite("gfx/misc/helltree.png", 198, 0, 82, 165);
	Drawer_LoadSprite("gfx/misc/helltree_collapsed.png", 0, 0, 64, 138);
	Drawer_LoadSprite("gfx/misc/helltree_overworld.png", 0, 0, 82, 165);
	
	Drawer_LoadSprite("gfx/misc/sign_0.png", 0, 0, 8, 15);
	Drawer_LoadSprite("gfx/misc/sign_1.png", 0, 0, 10, 21);
	Drawer_LoadSprite("gfx/misc/sign_2.png", 0, 0, 8, 8);
	Drawer_LoadSprite("gfx/misc/sign_3.png", 0, 0, 8, 8);
	Drawer_LoadSprite("gfx/misc/rubybed.png", 32, 0, 0, 6);
	Drawer_LoadSprite("gfx/misc/glasses.png", 0, 0, 6, 6);
	Drawer_LoadSprite("gfx/misc/labcoat.png", 0, 0, 4, 16);
	Drawer_LoadSprite("gfx/misc/rubycomputer.png", 0, 0, 8, 17);
	Drawer_LoadSprite("gfx/misc/kevincomputer.png", 22, 0, 8, 17);
	Drawer_LoadSprite("gfx/misc/laptop.png", 0, 0, 8, 13);
	Drawer_LoadSprite("gfx/misc/tomatosoup.png", 0, 0, 3, 9);
	Drawer_LoadSprite("gfx/misc/sapphirebus.png", 0, 71, 82, 70);
	Drawer_LoadSprite("gfx/misc/bar_glass.png", 9, 9, 4, 8);
	Drawer_LoadSprite("gfx/misc/perrypizza.png", 0, 0, 7, 8);
	Drawer_LoadSprite("gfx/misc/perrypizza_broken.png", 0, 0, 7, 9);
	Drawer_LoadSprite("gfx/misc/flashlight.png", 0, 0, 5, 5);
	Drawer_LoadSprite("gfx/misc/present.png", 0, 0, 7, 19);
	Drawer_LoadSprite("gfx/misc/flowergame.png", 8, 15, 3, 14);
	Drawer_LoadSprite("gfx/misc/flowergame_button.png", 0, 0, 3, 5);
	Drawer_LoadSprite("gfx/misc/diarynote.png", 0, 0, 4, 0);
	Drawer_LoadSprite("gfx/misc/offserieso.png", 25, 0, 12, 10);
	Drawer_LoadSprite("gfx/misc/computer.png", 0, 0, 8, 16);
	Drawer_LoadSprite("gfx/misc/computer_1.png", 0, 0, 8, 14);
	Drawer_LoadSprite("gfx/misc/ozonethrone.png", 0, 0, 16, 38);
	Drawer_LoadSprite("gfx/misc/briefcase.png", 14, 0, 7, 14);
	Drawer_LoadSprite("gfx/misc/healcapsule.png", 11, 0, 5, 5);
	Drawer_LoadSprite("gfx/misc/sapphireship.png", 0, 128, 86, 127);
	Drawer_LoadSprite("gfx/misc/dandelionneo.png", 9, 0, 3, 10);
	Drawer_LoadSprite("gfx/misc/web.png", 0, 0, 7, 20);
	Drawer_LoadSprite("gfx/misc/whitelight_kettlesandstuff.png", 26, 19, 12, 18);
	Drawer_LoadSprite("gfx/misc/guide_arrow.png", 13, 0, 6, 32);
	Drawer_LoadSprite("gfx/misc/guide_cross.png", 13, 0, 6, 30);
	Drawer_LoadSprite("gfx/misc/discotable.png", 41, 0, 20, 28);
	Drawer_LoadSprite("gfx/misc/turbospeaker.png", 48, 0, 23, 45);
	Drawer_LoadSprite("gfx/misc/discoequalizer.png", 112, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/janitorbucket.png", 0, 0, 4, 11);
	Drawer_LoadSprite("gfx/misc/antiretisheriff.png", 0, 0, 40, 49);
	Drawer_LoadSprite("gfx/misc/retichase_minimap.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/retichase_dot.png", 0, 0, 3, 3);
	Drawer_LoadSprite("gfx/misc/ampbroadcast.png", 96, 0, 48, 47);
	Drawer_LoadSprite("gfx/misc/ampbroadcastframe.png", 0, 0, 54, 53);
	Drawer_LoadSprite("gfx/misc/amper_cubicle.png", 80, 0, 40, 112);
	Drawer_LoadSprite("gfx/misc/amper_workers.png", 20, 40, 10, 39);
	Drawer_LoadSprite("gfx/misc/amper_movebutton.png", 0, 0, 8, 25);
	Drawer_LoadSprite("gfx/misc/amper_theatreseat.png", 0, 0, 8, 22);
	Drawer_LoadSprite("gfx/misc/rubyteenartbook.png", 0, 0, 5, 0);
	
	Drawer_LoadSprite("gfx/misc/voidportal.png", 24, 0, 12, 24);
	Drawer_LoadSprite("gfx/misc/hellgate.png", 0, 0, 46, 120);
	Drawer_LoadSprite("gfx/misc/hellgate_open.png", 0, 0, 46, 120);
	Drawer_LoadSprite("gfx/misc/illusgate.png", 0, 0, 46, 120);
	Drawer_LoadSprite("gfx/misc/hellgateboss.png", 43, 0, 20, 105);
	Drawer_LoadSprite("gfx/misc/hellgateboss_off.png", 0, 0, 20, 105);
	Drawer_LoadSprite("gfx/misc/healgeyser.png", 12, 0, 5, 42);
	Drawer_LoadSprite("gfx/misc/illusknife.png", 0, 0, 4, 0);
	Drawer_LoadSprite("gfx/misc/illusdoor.png", 44, 0, 21, 65);
	Drawer_LoadSprite("gfx/misc/illusmonolith.png", 0, 0, 16, 65);
	Drawer_LoadSprite("gfx/misc/timelinepuzzle.png", 120, 0, 60, 60);
	Drawer_LoadSprite("gfx/misc/timelineblock.png", 8, 0, 4, 7);
	Drawer_LoadSprite("gfx/misc/timelineslot.png", 0, 0, 4, 7);
	Drawer_LoadSprite("gfx/misc/illusmemorygems.png", 24, 0, 12, 24);
	
	Drawer_LoadSprite("gfx/misc/rubynobody_0.png", 0, 0, 15, 38);
	
	Drawer_LoadSprite("gfx/misc/omegalulu.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/misc/omegalulugun.png", 0, 0, 78, 7);
	Drawer_LoadSprite("gfx/misc/omegalulugunfire.png", 0, 0, 72, 7);
	Drawer_LoadSprite("gfx/misc/omegalulucannon_copyrighted.png", 0, 0, 48, 18);
	Drawer_LoadSprite("gfx/misc/omegalulukatana.png", 0, 0, 12, 5);
	Drawer_LoadSprite("gfx/misc/subspace_beam.png", 80, 0, 40, 239);
	Drawer_LoadSprite("gfx/misc/subspace_redaura.png", 100, 0, 50, 50);
	
	Drawer_LoadSprite("gfx/misc/gemia_map1.png", 0, 0, 79, 59);
	Drawer_LoadSprite("gfx/misc/gemia_map2.png", 0, 0, 79, 59);
	Drawer_LoadSprite("gfx/misc/cinema_rubyhouse.png", 0, 0, 79, 59);
	Drawer_LoadSprite("gfx/misc/cinema_ruby.png", 0, 0, 79, 59);
	Drawer_LoadSprite("gfx/misc/cinema_gems.png", 0, 0, 79, 59);
	Drawer_LoadSprite("gfx/misc/cinema_rubyawakening.png", 0, 0, 79, 59);
	
	Drawer_LoadSprite("gfx/misc/chess_pieces.png", 16, 16, 0, 0);
	
	
	
	Drawer_LoadSprite("gfx/gui/rubindeavor.png", 0, 0, 29, 4);
	Drawer_LoadSprite("gfx/gui/charbar.png", 0, 0, 12, 0);
	Drawer_LoadSprite("gfx/gui/owcharbox.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/gui/portraitbg.png", 0, 0, 0, 0);
	Drawer_LoadSprite("gfx/gui/dialogbox.png", 4, 4, 0, 0);
	Drawer_LoadSprite("gfx/gui/valuearrow.png", 7, 0, 6, 6);
	Drawer_LoadSprite("gfx/gui/checkmark.png", 13, 0, 12, 6);
	Drawer_LoadSprite("gfx/gui/markergem.png", 0, 0, 9, 6);
	Drawer_LoadSprite("gfx/gui/speedgem.png", 0, 0, 8, 8);
	Drawer_LoadSprite("gfx/gui/status.png", 16, 16, 7, 7);
	Drawer_LoadSprite("gfx/gui/stat.png", 16, 16, 0, 0);
	
	
	
	Drawer_LoadSprite("gfx/font/main.png", 8, 16, 0, 0);
	Drawer_LoadSprite("gfx/font/main2.png", 8, 16, 0, 0);
	Drawer_LoadSprite("gfx/font/small.png", 5, 8, 0, 0);
	
	
	if (drawerSystem.spriteCount != SPR_ENUMSIZE) {
		printf("Invalid sprite count (number is %d, supposed to be %d)\n", drawerSystem.spriteCount, SPR_ENUMSIZE);
	}
	
	
	#ifndef RXS_LOAD_SPRITES_FROM_FOLDER
		remove(TEMP_GFX_FILENAME);
		zip_close(za);
	#endif
}

void FreeSprites() {
	for (int i = 0; i < drawerSystem.spriteCount; i++) {
		if (drawerSystem.sprites[i].internal.texture == NULL) continue;
		SDL_DestroyTexture(drawerSystem.sprites[i].internal.texture);
	}
}



void Drawer_LoadSprite(const char* path, const int subW, const int subH, const int originX, const int originY) {
	//printf("Loading sprite: %s\n", path);
	if (drawerSystem.spriteCount >= SPRITE_COUNT_MAX) {
		printf("Sprite count reached max\n");
		return;
	}
	
	#ifndef RXS_LOAD_SPRITES_FROM_FOLDER
		if (zip_entry_open(za, path) < 0) {
			printf("Sprite loading error: %s\n", path);
			return;
		}
		unsigned char* imgBuffer = NULL;
		size_t imgBufferSize = 0;
		if (zip_entry_read(za, (void**)&imgBuffer, &imgBufferSize) < 0) {
			printf("Sprite loading error: %s\n", path);
			return;
		}
		{
			int c = 0;
			for (int i = 0; i < imgBufferSize; i++) {
				if (ASSETS_PASSWORD[c] == 0) break;
				imgBuffer[i] ^= ASSETS_PASSWORD[c++];
			}
		}
		zip_entry_close(za);
		
		FILE* file = fopen(TEMP_GFX_FILENAME, "wb");
		fwrite(imgBuffer, sizeof(char), imgBufferSize * sizeof(char), file);
		fclose(file);
		free(imgBuffer);
		
		SDL_Surface* surface = IMG_Load(TEMP_GFX_FILENAME);
	#else
		SDL_Surface* surface = IMG_Load(path);
	#endif
	
	if (surface == NULL) {
		printf("Sprite loading error: %s\n", path);
		return;
	}
	
	#ifndef RXS_LOAD_SPRITES_FROM_FOLDER
		drawerSystem.sprites[drawerSystem.spriteCount].internal.texture = IMG_LoadTexture(game.internal.renderer, TEMP_GFX_FILENAME);
	#else
		drawerSystem.sprites[drawerSystem.spriteCount].internal.texture = IMG_LoadTexture(game.internal.renderer, path);
	#endif
	
	if (drawerSystem.sprites[drawerSystem.spriteCount].internal.texture == NULL) {
		printf("Sprite loading error: %s\n", path);
		return;
	}
	
	drawerSystem.sprites[drawerSystem.spriteCount].w = surface->w;
	drawerSystem.sprites[drawerSystem.spriteCount].h = surface->h;
	drawerSystem.sprites[drawerSystem.spriteCount].subW = (subW == 0) ? surface->w : subW;
	drawerSystem.sprites[drawerSystem.spriteCount].subH = (subH == 0) ? surface->h : subH;
	drawerSystem.sprites[drawerSystem.spriteCount].originX = originX;
	drawerSystem.sprites[drawerSystem.spriteCount].originY = originY;
	
	drawerSystem.sprites[drawerSystem.spriteCount].subImagesPerRow = drawerSystem.sprites[drawerSystem.spriteCount].w / drawerSystem.sprites[drawerSystem.spriteCount].subW;
	drawerSystem.sprites[drawerSystem.spriteCount].subImages = drawerSystem.sprites[drawerSystem.spriteCount].subImagesPerRow * drawerSystem.sprites[drawerSystem.spriteCount].h / drawerSystem.sprites[drawerSystem.spriteCount].subH;
	
	drawerSystem.sprites[drawerSystem.spriteCount].color[0] = 255;
	drawerSystem.sprites[drawerSystem.spriteCount].color[1] = 255;
	drawerSystem.sprites[drawerSystem.spriteCount].color[2] = 255;
	drawerSystem.sprites[drawerSystem.spriteCount].alpha = 255;
	drawerSystem.sprites[drawerSystem.spriteCount].blendMode = BLENDMODE_BLEND;
	
	drawerSystem.spriteCount++;
	SDL_FreeSurface(surface);
}

void Drawer_DrawSprite(int spriteId, float x, float y, int subImage, float xScale, float yScale) {
	if (spriteId < 0 || spriteId >= drawerSystem.spriteCount) return;
	if (subImage >= drawerSystem.sprites[spriteId].subImages) subImage = drawerSystem.sprites[spriteId].subImages - 1;
	
	int srcX = (subImage % drawerSystem.sprites[spriteId].subImagesPerRow) * drawerSystem.sprites[spriteId].subW;
	int srcY = (subImage / drawerSystem.sprites[spriteId].subImagesPerRow) * drawerSystem.sprites[spriteId].subH;
	int srcW = drawerSystem.sprites[spriteId].subW;
	int srcH = drawerSystem.sprites[spriteId].subH;
	
	double destX = GetScreenX(x - (double)drawerSystem.sprites[spriteId].originX * xScale);
	double destY = GetScreenY(y - (double)drawerSystem.sprites[spriteId].originY * yScale);
	double destW = (double)drawerSystem.sprites[spriteId].subW * xScale * drawerSystem.projection_zoom;
	double destH = (double)drawerSystem.sprites[spriteId].subH * yScale * drawerSystem.projection_zoom;
	
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
	
	if (1 || drawerSystem.sprites[spriteId].color[0] != drawerSystem.color[0] || drawerSystem.sprites[spriteId].color[1] != drawerSystem.color[1] || drawerSystem.sprites[spriteId].color[2] != drawerSystem.color[2]) {
		SDL_SetTextureColorMod(drawerSystem.sprites[spriteId].internal.texture, drawerSystem.color[0], drawerSystem.color[1], drawerSystem.color[2]);
		drawerSystem.sprites[spriteId].color[0] = drawerSystem.color[0];
		drawerSystem.sprites[spriteId].color[1] = drawerSystem.color[1];
		drawerSystem.sprites[spriteId].color[2] = drawerSystem.color[2];
	}
	if (1 || drawerSystem.sprites[spriteId].alpha != drawerSystem.alpha) {
		SDL_SetTextureAlphaMod(drawerSystem.sprites[spriteId].internal.texture, drawerSystem.alpha);
		drawerSystem.sprites[spriteId].alpha = drawerSystem.alpha;
	}
	if (1 || drawerSystem.sprites[spriteId].blendMode != drawerSystem.blendMode) {
		SDL_BlendMode sdlBlend = SDL_BLENDMODE_BLEND;
		switch (drawerSystem.blendMode) {
			case BLENDMODE_ADD: sdlBlend = SDL_BLENDMODE_ADD; break;
			case BLENDMODE_MUL: sdlBlend = SDL_BLENDMODE_MUL; break;
		}
		SDL_SetTextureBlendMode(drawerSystem.sprites[spriteId].internal.texture, sdlBlend);
		drawerSystem.sprites[spriteId].blendMode = drawerSystem.blendMode;
	}
	
	SDL_RenderCopyExF(game.internal.renderer, drawerSystem.sprites[spriteId].internal.texture,
		&(SDL_Rect){ srcX, srcY, srcW, srcH },
		&(SDL_FRect){ destX, destY, destW + 0.5, destH + 0.5 },
		0,
		&(SDL_FPoint){ drawerSystem.sprites[spriteId].originX, drawerSystem.sprites[spriteId].originY },
		flip
	);
}

void Drawer_DrawSprite_Angle(int spriteId, float x, float y, int subImage, float xScale, float yScale, float angle) {
	if (spriteId < 0 || spriteId >= drawerSystem.spriteCount) return;
	if (subImage >= drawerSystem.sprites[spriteId].subImages) subImage = drawerSystem.sprites[spriteId].subImages - 1;
	
	int srcX = (subImage % drawerSystem.sprites[spriteId].subImagesPerRow) * drawerSystem.sprites[spriteId].subW;
	int srcY = (subImage / drawerSystem.sprites[spriteId].subImagesPerRow) * drawerSystem.sprites[spriteId].subH;
	int srcW = drawerSystem.sprites[spriteId].subW;
	int srcH = drawerSystem.sprites[spriteId].subH;
	
	float destX = GetScreenX(x - (float)drawerSystem.sprites[spriteId].originX * xScale);
	float destY = GetScreenY(y - (float)drawerSystem.sprites[spriteId].originY * yScale);
	float destW = (float)drawerSystem.sprites[spriteId].subW * xScale * drawerSystem.projection_zoom;
	float destH = (float)drawerSystem.sprites[spriteId].subH * yScale * drawerSystem.projection_zoom;
	
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
	
	if (1 || drawerSystem.sprites[spriteId].color[0] != drawerSystem.color[0] || drawerSystem.sprites[spriteId].color[1] != drawerSystem.color[1] || drawerSystem.sprites[spriteId].color[2] != drawerSystem.color[2]) {
		SDL_SetTextureColorMod(drawerSystem.sprites[spriteId].internal.texture, drawerSystem.color[0], drawerSystem.color[1], drawerSystem.color[2]);
		drawerSystem.sprites[spriteId].color[0] = drawerSystem.color[0];
		drawerSystem.sprites[spriteId].color[1] = drawerSystem.color[1];
		drawerSystem.sprites[spriteId].color[2] = drawerSystem.color[2];
	}
	if (1 || drawerSystem.sprites[spriteId].alpha != drawerSystem.alpha) {
		SDL_SetTextureAlphaMod(drawerSystem.sprites[spriteId].internal.texture, drawerSystem.alpha);
		drawerSystem.sprites[spriteId].alpha = drawerSystem.alpha;
	}
	if (1 || drawerSystem.sprites[spriteId].blendMode != drawerSystem.blendMode) {
		SDL_BlendMode sdlBlend = SDL_BLENDMODE_BLEND;
		switch (drawerSystem.blendMode) {
			case BLENDMODE_ADD: sdlBlend = SDL_BLENDMODE_ADD; break;
			case BLENDMODE_MUL: sdlBlend = SDL_BLENDMODE_MUL; break;
		}
		SDL_SetTextureBlendMode(drawerSystem.sprites[spriteId].internal.texture, sdlBlend);
		drawerSystem.sprites[spriteId].blendMode = drawerSystem.blendMode;
	}
	
	SDL_RenderCopyEx(game.internal.renderer, drawerSystem.sprites[spriteId].internal.texture,
		&(SDL_Rect){ srcX, srcY, srcW, srcH },
		&(SDL_Rect){ destX, destY, destW, destH },
		angle,
		&(SDL_Point){ drawerSystem.sprites[spriteId].originX * xScale * drawerSystem.projection_zoom, drawerSystem.sprites[spriteId].originY * yScale * drawerSystem.projection_zoom },
		flip
	);
}

void Drawer_DrawText(const unsigned char* text, int length, float x, float y, float xScale, float yScale) {
	int spriteId = drawerSystem.fontSpriteId;
	float charX = x;
	float charY = y;
	float dx = drawerSystem.sprites[spriteId].subW * xScale;
	float dy = drawerSystem.sprites[spriteId].subH * yScale;
	
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
	
	int alignment = drawerSystem.fontAlignment;
	
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
	
	uint8_t prevColors[3] = { drawerSystem.color[0], drawerSystem.color[1], drawerSystem.color[2] };
	
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
				
				case 8: colors[0] = 255; colors[1] = 63; colors[2] = 63; break;
				case 9: colors[0] = 255; colors[1] = 159; colors[2] = 63; break;
				case 10: colors[0] = 255; colors[1] = 255; colors[2] = 63; break;
				case 11: colors[0] = 63; colors[1] = 255; colors[2] = 63; break;
				case 12: colors[0] = 63; colors[1] = 255; colors[2] = 255; break;
				case 13: colors[0] = 63; colors[1] = 63; colors[2] = 255; break;
				case 14: colors[0] = 255; colors[1] = 63; colors[2] = 255; break;
				
				case 255: colors[0] = prevColors[0]; colors[1] = prevColors[1]; colors[2] = prevColors[2]; break;
			}
			Drawer_SetDrawColor(colors[0], colors[1], colors[2]);
			continue;
		}
		else if (text[i] == 0x90) {
			i++;
			Drawer_DrawSprite(SPR_gui_stat, charX, charY, text[i] - 1, xScale, yScale);
			
			if (game.settings.showStatSymbolLabels) {
				int prevFont = spriteId;
				Drawer_SetFontSprite(SPR_font_small);
				switch (text[i] - 1) {
					case 0: SetString(game.textBuffer, "hp"); break;
					case 1: SetString(game.textBuffer, "mp"); break;
					case 2: SetString(game.textBuffer, "atk"); break;
					case 3: SetString(game.textBuffer, "def"); break;
					case 4: SetString(game.textBuffer, "spd"); break;
					case 5: SetString(game.textBuffer, "pow"); break;
					case 6: SetString(game.textBuffer, "gp"); break;
				}
				Drawer_DrawText(game.textBuffer, 4, charX + 2, charY + 16, 2, 2);
				Drawer_SetFontSprite(prevFont);
			}
		}
		else if (text[i] >= 33) {
			Drawer_DrawSprite(spriteId, charX, charY, text[i] - 33, xScale, yScale);
			if (profile.tempFlags[TEMPFLAG_ILLUSION_HYPERHELL]) {
				Drawer_SetDrawAlpha(255);
				Drawer_SetDrawBlend(BLENDMODE_MUL);
				Drawer_SetDrawColor(255, 127 * (game.timer % 32 >= 24), 0);
				Drawer_DrawSprite(SPR_misc_bossbattlebg_1, charX, charY, 0, 0.25, 0.5);
				Drawer_SetDrawAlpha(63);
				Drawer_SetDrawBlend(BLENDMODE_ADD);
				Drawer_SetDrawColor(255, 255 * (game.timer % 32 < 16), 0);
				Drawer_DrawSprite(SPR_misc_bossbattlebg_0, charX - 1, charY, 0, 0.25, 0.5);
				Drawer_SetDrawColor(255, 255 * (game.timer % 32 >= 16), 0);
				Drawer_DrawSprite(SPR_misc_bossbattlebg_0, charX + 1, charY, 0, 0.25, 0.5);
				Drawer_SetDrawAlpha(255);
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
				Drawer_SetDrawColor(prevColors[0], prevColors[1], prevColors[2]);
			}
		}
		charX += dx;
	}
	
	Drawer_SetDrawColor(prevColors[0], prevColors[1], prevColors[2]);
}

void Drawer_FillRect(float x, float y, float w, float h) {
	SDL_RenderFillRectF(game.internal.renderer,
	&(SDL_FRect){ GetScreenX(x),
	GetScreenY(y),
	w * drawerSystem.projection_zoom,
	h * drawerSystem.projection_zoom });
}



void Drawer_SetProjection(float x, float y, float zoom) {
	drawerSystem.projection_x = x;
	drawerSystem.projection_y = y;
	drawerSystem.projection_zoom = zoom;
}

void Drawer_SetDrawColor(uint8_t r, uint8_t g, uint8_t b) {
	drawerSystem.color[0] = r;
	drawerSystem.color[1] = g;
	drawerSystem.color[2] = b;
	SDL_SetRenderDrawColor(game.internal.renderer, drawerSystem.color[0], drawerSystem.color[1], drawerSystem.color[2], drawerSystem.alpha);
}

void Drawer_SetDrawAlpha(uint8_t a) {
	drawerSystem.alpha = a;
	SDL_SetRenderDrawColor(game.internal.renderer, drawerSystem.color[0], drawerSystem.color[1], drawerSystem.color[2], drawerSystem.alpha);
}

void Drawer_SetDrawBlend(int blendMode) {
	drawerSystem.blendMode = blendMode;
	SDL_BlendMode sdlBlend = SDL_BLENDMODE_BLEND;
	switch (drawerSystem.blendMode) {
		case BLENDMODE_ADD: sdlBlend = SDL_BLENDMODE_ADD; break;
		case BLENDMODE_MUL: sdlBlend = SDL_BLENDMODE_MUL; break;
	}
	SDL_SetRenderDrawBlendMode(game.internal.renderer, sdlBlend);
}

void Drawer_SetFontSprite(int spriteId) {
	drawerSystem.fontSpriteId = spriteId;
}

void Drawer_SetFontAlignment(int alignment) {
	drawerSystem.fontAlignment = alignment;
}
