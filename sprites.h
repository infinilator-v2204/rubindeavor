#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

#define SPRITE_COUNT_MAX 1024

typedef struct {
	int w; int h;
	int subW; int subH;
	int subImages;
	int subImagesPerRow;
	int originX; int originY;
	
	uint8_t color[3];
	uint8_t alpha;
	int blendMode;
	
	struct {
		SDL_Texture* texture;
	} internal;
} Sprite;

typedef struct {
	int spriteCount;
	Sprite sprites[SPRITE_COUNT_MAX];
	
	float projection_x;
	float projection_y;
	float projection_zoom;
	uint8_t color[3];
	uint8_t alpha;
	int blendMode;
	int fontSpriteId;
	int fontAlignment;
} DrawerSystem;

extern DrawerSystem drawerSystem;

enum {
	BLENDMODE_BLEND,
	BLENDMODE_ADD,
	BLENDMODE_MUL,
};

enum {
	SPR_head_ruby,
	SPR_body_ruby,
	SPR_body_ruby_zero,
	SPR_body_ruby_armed,
	SPR_head_ruby_god,
	
	SPR_body_rubin,
	
	SPR_head_noah,
	SPR_body_noah,
	
	SPR_head_emmet,
	SPR_body_emmet,
	
	SPR_head_sally,
	SPR_head_sally_b,
	SPR_body_sally,
	
	SPR_head_sally_neo,
	SPR_body_sally_neo,
	
	SPR_head_diego,
	SPR_body_diego,
	
	SPR_head_perry,
	SPR_body_perry,
	
	SPR_head_anonymous,
	SPR_head_generic_0,
	SPR_head_generic_1,
	SPR_head_generic_2,
	SPR_head_generic_3,
	SPR_head_generic_4,
	SPR_head_generic_5,
	SPR_head_generic_6,
	SPR_head_generic_7,
	SPR_head_generic_8,
	SPR_head_generic_9,
	SPR_head_generic_9_b,
	SPR_head_generic_10,
	SPR_head_generic_11,
	SPR_head_generic_11_b,
	SPR_head_generic_12,
	SPR_head_generic_13,
	SPR_head_generic_14,
	SPR_head_generic_15,
	SPR_head_generic_16,
	SPR_head_generic_17,
	SPR_head_generic_18,
	SPR_head_generic_19,
	SPR_head_generic_20,
	
	SPR_body_hobo,
	
	SPR_body_navygang,
	
	SPR_body_leafcrew,
	
	SPR_head_bashura,
	
	SPR_head_lisao,
	SPR_head_lisao_b,
	SPR_body_lisao,
	
	SPR_head_lulu,
	SPR_body_lulu,
	
	SPR_body_lulu_blaze,
	
	SPR_body_police,
	
	SPR_body_farmer,
	
	SPR_body_knifethug,
	
	SPR_body_vandal_knife,
	
	SPR_body_vandal_flail,
	
	SPR_body_nurse,
	
	SPR_head_jackie,
	SPR_body_jackie,
	
	SPR_head_electra,
	SPR_body_electra,
	
	SPR_head_ray,
	SPR_head_ray_b,
	SPR_body_ray,
	
	SPR_body_lulu_omega,
	
	SPR_body_slime,
	SPR_body_slimesuit,
	
	SPR_body_slimeboss,
	
	SPR_head_dia,
	SPR_head_dia_b,
	SPR_body_dia,
	
	SPR_body_spider,
	SPR_body_spidersuit,
	
	SPR_body_spiderboss,
	
	SPR_head_policecap,
	SPR_body_policecap,
	
	SPR_head_sync,
	SPR_body_sync,
	
	SPR_head_josh,
	SPR_body_josh,
	
	SPR_head_pirate,
	SPR_body_pirate,
	
	SPR_head_piratecap,
	SPR_body_piratecap,
	
	SPR_head_sanji,
	SPR_head_sanji_b,
	SPR_body_sanji,
	
	SPR_head_ninja,
	SPR_body_ninja,
	
	SPR_body_agent,
	
	SPR_body_bpolice,
	
	SPR_body_gpolice,
	
	SPR_head_amp,
	SPR_head_amp_b,
	SPR_body_amp,
	
	SPR_head_river,
	SPR_head_river_b,
	SPR_body_river,
	
	SPR_head_frank,
	SPR_body_frank,
	
	SPR_head_waxknight,
	SPR_body_waxknight,
	
	SPR_head_flora,
	SPR_body_flora,
	
	SPR_body_deathknife,
	SPR_body_energyentity,
	SPR_body_deathweight,
	
	SPR_head_kelly,
	SPR_body_kelly,
	
	SPR_head_neveah,
	SPR_body_neveah,
	
	SPR_head_brook,
	SPR_body_brook,
	
	SPR_head_tom,
	SPR_body_tom,
	
	SPR_head_cindy,
	SPR_head_cindy_b,
	SPR_body_cindy,
	
	SPR_body_ozone,
	
	SPR_head_don,
	SPR_body_don,
	
	SPR_head_nate,
	SPR_body_nate,
	
	SPR_head_volcano,
	SPR_body_volcano,
	
	SPR_head_luna,
	SPR_head_luna_b,
	SPR_body_luna,
	
	SPR_body_unknown1,
	SPR_body_unknown2,
	SPR_body_hellgoner,
	
	SPR_head_perry_knife,
	SPR_body_perry_knife,
	
	SPR_head_brian,
	SPR_body_brian,
	
	SPR_head_nekin,
	SPR_head_nekin_b,
	SPR_body_nekin,
	
	SPR_head_lulu_subspace,
	SPR_body_lulu_subspace,
	
	SPR_head_adios,
	SPR_body_adios,
	
	SPR_head_bulldog,
	SPR_body_bulldog,
	
	SPR_head_kyle,
	SPR_body_kyle,
	
	SPR_body_builder,
	
	SPR_head_tia,
	SPR_head_tia_b,
	SPR_body_tia,
	
	SPR_head_kara,
	SPR_body_kara,
	
	SPR_head_camilla,
	SPR_head_camilla_b,
	SPR_body_camilla,
	
	SPR_head_ayinoying,
	SPR_body_ayinoying,
	
	SPR_head_aztec,
	SPR_body_aztec,
	
	SPR_head_dirk,
	SPR_body_dirk,
	
	SPR_body_whitelight,
	
	SPR_head_rob,
	SPR_body_rob,
	
	SPR_head_mani,
	SPR_body_mani,
	
	SPR_head_timon,
	SPR_body_timon,
	
	SPR_head_gregory,
	SPR_body_gregory,
	
	SPR_head_violet,
	SPR_body_violet,
	
	SPR_head_reti,
	SPR_body_reti,
	
	SPR_head_lulu_master,
	SPR_body_lulu_master,
	
	SPR_head_lulu_god,
	SPR_body_lulu_god,
	
	SPR_head_panda,
	SPR_body_panda,
	
	SPR_head_maline,
	SPR_head_maline_b,
	SPR_body_maline,
	
	SPR_head_cory,
	SPR_body_cory,
	
	SPR_body_onyxagent,
	
	SPR_head_vincent,
	SPR_head_jerry,
	SPR_head_ohio,
	SPR_head_kaiser,
	
	SPR_head_lulu_ultimate,
	SPR_body_lulu_ultimate,
	
	
	
	SPR_owchar_ruby,
	SPR_owchar_ruby_run,
	SPR_owchar_ruby_run_prepare,
	SPR_owchar_ruby_flashlight,
	SPR_owchar_ruby_blush,
	SPR_owchar_ruby_zero,
	SPR_owchar_ruby_zero2,
	SPR_owchar_ruby_teen,
	SPR_owchar_ruby_nmg,
	SPR_owchar_ruby_god,
	SPR_owchar_ruby_god_run,
	SPR_owchar_ruby_god_run_prepare,
	SPR_owchar_noah,
	SPR_owchar_noah_run,
	SPR_owchar_emmet,
	SPR_owchar_emmet_run,
	SPR_owchar_sally,
	SPR_owchar_sally_run,
	SPR_owchar_sally_neo,
	SPR_owchar_sally_neo_run,
	SPR_owchar_diego,
	SPR_owchar_diego_run,
	SPR_owchar_perry,
	SPR_owchar_perry_run,
	SPR_owchar_hobo,
	SPR_owchar_hobo_1,
	SPR_owchar_navygang,
	SPR_owchar_navygang_1,
	SPR_owchar_leafcrew,
	SPR_owchar_leafcrew_alt,
	SPR_owchar_bashura,
	SPR_owchar_lisao,
	SPR_owchar_lulu,
	SPR_owchar_police_0,
	SPR_owchar_police_1,
	SPR_owchar_farmer,
	SPR_owchar_farmer_1,
	SPR_owchar_knifethug,
	SPR_owchar_vandal_knife,
	SPR_owchar_vandal_flail,
	SPR_owchar_nurse,
	SPR_owchar_jackie,
	SPR_owchar_electra,
	SPR_owchar_electra_purple,
	SPR_owchar_ray,
	SPR_owchar_lulu_omega,
	SPR_owchar_slime,
	SPR_owchar_slimeboss,
	SPR_owchar_dia,
	SPR_owchar_spider,
	SPR_owchar_spiderboss,
	SPR_owchar_policecap,
	SPR_owchar_sync,
	SPR_owchar_josh,
	SPR_owchar_pirate,
	SPR_owchar_pirate_1,
	SPR_owchar_piratecap,
	SPR_owchar_sanji,
	SPR_owchar_ninja,
	SPR_owchar_agent,
	SPR_owchar_bpolice_0,
	SPR_owchar_bpolice_1,
	SPR_owchar_gpolice_0,
	SPR_owchar_amp,
	SPR_owchar_ayaka,
	SPR_owchar_river,
	SPR_owchar_frank,
	SPR_owchar_sora,
	SPR_owchar_waxknight,
	SPR_owchar_sapphireton_diana,
	SPR_owchar_flora,
	SPR_owchar_kelly,
	SPR_owchar_neveah,
	SPR_owchar_brook,
	SPR_owchar_tom,
	SPR_owchar_cindy,
	SPR_owchar_ozone,
	SPR_owchar_don,
	SPR_owchar_nate,
	SPR_owchar_volcano,
	SPR_owchar_luna,
	SPR_owchar_viku,
	SPR_owchar_brian,
	SPR_owchar_nekin,
	SPR_owchar_lulu_subspace,
	SPR_owchar_adios,
	SPR_owchar_bulldog,
	SPR_owchar_kyle,
	SPR_owchar_builder,
	SPR_owchar_tia,
	SPR_owchar_kara,
	SPR_owchar_camilla,
	SPR_owchar_ayinoying,
	SPR_owchar_aztec,
	SPR_owchar_dirk,
	SPR_owchar_whitelight_0,
	SPR_owchar_whitelight_1,
	SPR_owchar_rob,
	SPR_owchar_mani,
	SPR_owchar_timon,
	SPR_owchar_gregory,
	SPR_owchar_violet,
	SPR_owchar_reti,
	SPR_owchar_reti_mask,
	SPR_owchar_lulu_cloak,
	SPR_owchar_lulu_cloak2,
	SPR_owchar_lulu_master,
	SPR_owchar_lulu_god,
	SPR_owchar_panda,
	SPR_owchar_maline,
	SPR_owchar_cory,
	SPR_owchar_vincent,
	SPR_owchar_jerry,
	SPR_owchar_ohio,
	SPR_owchar_kaiser,
	SPR_owchar_lulu_ultimate,
	
	SPR_owchar_npc_0,
	SPR_owchar_npc_1,
	SPR_owchar_npc_2,
	SPR_owchar_npc_3,
	SPR_owchar_npc_4,
	SPR_owchar_npc_5,
	SPR_owchar_npc_6,
	SPR_owchar_npc_7,
	SPR_owchar_npc_8,
	SPR_owchar_npc_9,
	SPR_owchar_npc_10,
	SPR_owchar_npc_11,
	SPR_owchar_npc_12,
	SPR_owchar_npc_13,
	SPR_owchar_npc_14,
	SPR_owchar_npc_15,
	SPR_owchar_npc_16,
	SPR_owchar_npc_17,
	SPR_owchar_npc_18,
	SPR_owchar_npc_19,
	SPR_owchar_npc_20,
	SPR_owchar_npc_21,
	SPR_owchar_npc_22,
	SPR_owchar_npc_23,
	SPR_owchar_npc_24,
	SPR_owchar_npc_25,
	SPR_owchar_npc_26,
	SPR_owchar_npc_27,
	SPR_owchar_npc_28,
	SPR_owchar_npc_29,
	SPR_owchar_npc_30,
	SPR_owchar_npc_31,
	SPR_owchar_npc_32,
	SPR_owchar_npc_33,
	SPR_owchar_npc_34,
	SPR_owchar_npc_35,
	SPR_owchar_npc_36,
	SPR_owchar_npc_37,
	SPR_owchar_npc_38,
	SPR_owchar_npc_39,
	SPR_owchar_npc_40,
	SPR_owchar_npc_41,
	SPR_owchar_npc_42,
	SPR_owchar_npc_43,
	SPR_owchar_npc_44,
	
	SPR_owchar_rubin,
	
	SPR_owchar_collapse_ruby,
	SPR_owchar_collapse_ruby_teen,
	SPR_owchar_collapse_ruby_god,
	SPR_owchar_collapse_noah,
	SPR_owchar_collapse_emmet,
	SPR_owchar_collapse_sally,
	SPR_owchar_collapse_sally_neo,
	SPR_owchar_collapse_diego,
	SPR_owchar_collapse_perry,
	SPR_owchar_collapse_panda,
	SPR_owchar_collapse_dia,
	SPR_owchar_collapse_nekin,
	SPR_owchar_collapse_luna,
	SPR_owchar_collapse_lulu_omega,
	SPR_owchar_collapse_amp,
	SPR_owchar_collapse_maline,
	SPR_owchar_collapse_cory,
	SPR_owchar_collapse_npc_41,
	SPR_owchar_collapse_npc_42,
	
	SPR_owchar_climb_ruby,
	SPR_owchar_climb_ruby_god,
	SPR_owchar_climb_noah,
	SPR_owchar_climb_emmet,
	SPR_owchar_climb_sally,
	SPR_owchar_climb_sally_neo,
	SPR_owchar_climb_diego,
	SPR_owchar_climb_perry,
	
	
	
	SPR_tileset_day,
	SPR_tileset_day_forest,
	SPR_tileset_day_autumn,
	SPR_tileset_night,
	
	
	
	SPR_spark_spark,
	SPR_spark_punch,
	SPR_spark_slash,
	SPR_spark_star,
	SPR_spark_vinespike,
	SPR_spark_vinetrap,
	SPR_spark_slashmagic,
	SPR_spark_slashfirelu,
	SPR_spark_slashicely,
	SPR_spark_slashamp,
	SPR_spark_slashbeam,
	SPR_spark_slashcory,
	SPR_spark_slashcorycombo,
	SPR_spark_slashmaline,
	SPR_spark_saw,
	SPR_spark_snow,
	SPR_spark_flower,
	SPR_spark_ring,
	SPR_spark_boost,
	SPR_spark_slashultra,
	SPR_spark_slashhyper,
	SPR_spark_slashcamilla,
	SPR_spark_brickwall,
	SPR_spark_petalbg,
	SPR_spark_blazeoblivion,
	SPR_spark_blazewave,
	SPR_spark_blazeimpact,
	SPR_spark_tsunami,
	SPR_spark_superfreeze,
	SPR_spark_ultlulubolt,
	SPR_spark_ultluluimpact,
	SPR_spark_ultlulubeam,
	SPR_spark_blood,
	
	
	
	SPR_misc_shuriken,
	SPR_misc_kunai,
	SPR_misc_bomb,
	SPR_misc_rocket,
	SPR_misc_diamondcast,
	SPR_misc_flameorb,
	SPR_misc_waterbullet,
	SPR_misc_ampbullet,
	SPR_misc_amppulse,
	SPR_misc_ampbeam,
	SPR_misc_ampbeamstart,
	SPR_misc_knife,
	SPR_misc_knife2,
	SPR_misc_rubydart,
	SPR_misc_paperplane,
	SPR_misc_hellspike,
	SPR_misc_pandadart,
	SPR_misc_malinewave,
	SPR_misc_malinewavebig,
	SPR_misc_ultluluorb,
	
	SPR_misc_backdrop_hell,
	SPR_misc_backdrop_brilliant,
	SPR_misc_backdrop_redmountains,
	SPR_misc_backdrop_lisaohouse,
	SPR_misc_darkoverlay,
	SPR_misc_darkoverlay_flashlight,
	SPR_misc_bossbattlebg_0,
	SPR_misc_bossbattlebg_1,
	SPR_misc_bossbattlebg_2,
	SPR_misc_bossbattlebg_3,
	SPR_misc_bossbattlebg_4,
	SPR_misc_bossbattlebg_5,
	SPR_misc_bossbattlebg_6,
	SPR_misc_bossbattlebg_7,
	SPR_misc_bossbattlebg_8,
	SPR_misc_bossbattlebg_9,
	SPR_misc_bossbattlebg_10,
	SPR_misc_savegem,
	SPR_misc_brickwall,
	SPR_misc_silverblock,
	SPR_misc_silversakura,
	SPR_misc_gems,
	SPR_misc_key,
	SPR_misc_spikes,
	SPR_misc_mansionsofa,
	SPR_misc_secretbossdoor,
	SPR_misc_secretbosskey,
	SPR_misc_secretbosskeylock,
	SPR_misc_collapseblood,
	SPR_misc_aquatree,
	SPR_misc_policebarrier,
	SPR_misc_spolis_exit,
	SPR_misc_spolis_exitbarrier,
	SPR_misc_brilliant_crystal1,
	SPR_misc_brilliant_crystal2,
	SPR_misc_brilliant_crystal3,
	SPR_misc_spyingtelescope,
	SPR_misc_gregoryguide,
	SPR_misc_gregoryscythe,
	SPR_misc_gregorygun,
	
	SPR_misc_lisao_sleep,
	SPR_misc_lisao_sleepawake,
	SPR_misc_lisao_sit,
	SPR_misc_lisao_hug,
	SPR_misc_lisao_happy,
	SPR_misc_ruby_wakeup,
	SPR_misc_ruby_think,
	SPR_misc_ruby_shrug,
	SPR_misc_ruby_hug,
	SPR_misc_ruby_suppressed,
	SPR_misc_ruby_sit,
	SPR_misc_ruby_rage,
	SPR_misc_ruby_teen_draw,
	SPR_misc_ruby_teen_slap,
	SPR_misc_ruby_nmg_suppressed,
	SPR_misc_noah_hug,
	SPR_misc_noah_sit,
	SPR_misc_emmet_facepalm,
	SPR_misc_emmet_sit,
	SPR_misc_sally_serious,
	SPR_misc_sally_phone,
	SPR_misc_sally_sit,
	SPR_misc_sally_neo_serious,
	SPR_misc_sally_neo_hug,
	SPR_misc_sally_neo_sit,
	SPR_misc_diego_greet,
	SPR_misc_diego_sit,
	SPR_misc_perry_sleep,
	SPR_misc_perry_sit,
	SPR_misc_perryhomesleep,
	SPR_misc_panda_beamsword,
	SPR_misc_lulu_omega_rage,
	SPR_misc_lulu_cloakthrow,
	SPR_misc_lulu_cloak_happy,
	SPR_misc_lulu_master_rage,
	SPR_misc_lulu_master_hug,
	SPR_misc_lulu_master_flushed,
	SPR_misc_lulu_master_broken,
	SPR_misc_lulu_god_rage,
	SPR_misc_lulu_god_hug,
	SPR_misc_lulu_god_entry,
	SPR_misc_lulu_god_entryland,
	SPR_misc_lulu_god_cry,
	SPR_misc_lulu_ultimate_stagger,
	SPR_misc_lulu_ultimate_rage,
	SPR_misc_kelly_prepare,
	SPR_misc_neveah_prepare,
	SPR_misc_cindy_laugh,
	SPR_misc_dia_hug,
	SPR_misc_ruby_raisehands,
	SPR_misc_ruby_beamsword,
	SPR_misc_nekin_prepare,
	SPR_misc_nate_worried,
	SPR_misc_luna_pain,
	SPR_misc_lulu_subspace_rage,
	SPR_misc_kara_jump,
	SPR_misc_amp_sit,
	SPR_misc_amp_kneel,
	SPR_misc_gregory_defeated,
	SPR_misc_npc_22_phone,
	SPR_misc_npc_33_arms,
	SPR_misc_npc_35_dj,
	SPR_misc_npc_36_floss,
	SPR_misc_npc_38_dance,
	SPR_misc_npc_39_sweep,
	SPR_misc_npc_41_slapped,
	SPR_misc_gemini,
	SPR_misc_gemini_collapsed,
	SPR_misc_redgreenbatterlookingidiot,
	SPR_misc_pbsuperhero,
	SPR_misc_pbsuperhero_certificate,
	SPR_misc_dystal,
	SPR_misc_dystal_final,
	SPR_misc_helltree,
	SPR_misc_helltree_collapsed,
	SPR_misc_helltree_overworld,
	
	SPR_misc_sign_0,
	SPR_misc_sign_1,
	SPR_misc_sign_2,
	SPR_misc_sign_3,
	SPR_misc_rubybed,
	SPR_misc_glasses,
	SPR_misc_labcoat,
	SPR_misc_rubycomputer,
	SPR_misc_kevincomputer,
	SPR_misc_laptop,
	SPR_misc_tomatosoup,
	SPR_misc_sapphirebus,
	SPR_misc_bar_glass,
	SPR_misc_perrypizza,
	SPR_misc_perrypizza_broken,
	SPR_misc_flashlight,
	SPR_misc_present,
	SPR_misc_flowergame,
	SPR_misc_flowergame_button,
	SPR_misc_diarynote,
	SPR_misc_offserieso,
	SPR_misc_computer,
	SPR_misc_computer_1,
	SPR_misc_ozonethrone,
	SPR_misc_briefcase,
	SPR_misc_healcapsule,
	SPR_misc_sapphireship,
	SPR_misc_dandelionneo,
	SPR_misc_web,
	SPR_misc_whitelight_kettlesandstuff,
	SPR_misc_guide_arrow,
	SPR_misc_guide_cross,
	SPR_misc_discotable,
	SPR_misc_turbospeaker,
	SPR_misc_discoequalizer,
	SPR_misc_janitorbucket,
	SPR_misc_antiretisheriff,
	SPR_misc_retichase_minimap,
	SPR_misc_retichase_dot,
	SPR_misc_ampbroadcast,
	SPR_misc_ampbroadcastframe,
	SPR_misc_amper_cubicle,
	SPR_misc_amper_workers,
	SPR_misc_amper_movebutton,
	SPR_misc_amper_theatreseat,
	SPR_misc_rubyteenartbook,
	
	SPR_misc_voidportal,
	SPR_misc_hellgate,
	SPR_misc_hellgate_open,
	SPR_misc_illusgate,
	SPR_misc_hellgateboss,
	SPR_misc_hellgateboss_off,
	SPR_misc_healgeyser,
	SPR_misc_illusknife,
	SPR_misc_illusdoor,
	SPR_misc_illusmonolith,
	SPR_misc_timelinepuzzle,
	SPR_misc_timelineblock,
	SPR_misc_timelineslot,
	SPR_misc_illusmemorygems,
	
	SPR_misc_rubynobody_0,
	
	SPR_misc_omegalulu,
	SPR_misc_omegalulugun,
	SPR_misc_omegalulugunfire,
	SPR_misc_omegalulucannon,
	SPR_misc_omegalulukatana,
	SPR_misc_subspace_beam,
	SPR_misc_subspace_redaura,
	
	SPR_misc_gemia_map1,
	SPR_misc_gemia_map2,
	SPR_misc_cinema_rubyhouse,
	SPR_misc_cinema_ruby,
	SPR_misc_cinema_gems,
	SPR_misc_cinema_rubyawakening,
	
	SPR_misc_chess_pieces,
	
	
	
	SPR_gui_rubindeavor,
	SPR_gui_charbar,
	SPR_gui_owcharbox,
	SPR_gui_portraitbg,
	SPR_gui_dialogbox,
	SPR_gui_valuearrow,
	SPR_gui_checkmark,
	SPR_gui_markergem,
	SPR_gui_speedgem,
	SPR_gui_status,
	SPR_gui_stat,
	
	
	
	SPR_font_main,
	SPR_font_main2,
	SPR_font_small,
	
	
	
	SPR_ENUMSIZE
};

extern const int FIRST_SPR_owchar;
extern const int LAST_SPR_owchar;

extern const int firstTilesetSpriteId;
extern const int lastTilesetSpriteId;

enum {
	FONT_ALIGN_LEFT = 0,
	FONT_ALIGN_MIDDLE = 1,
	FONT_ALIGN_RIGHT = 2,
	FONT_ALIGN_TOP = 0 << 2,
	FONT_ALIGN_CENTER = 1 << 2,
	FONT_ALIGN_BOTTOM = 2 << 2
};

void LoadSprites();
void FreeSprites();

void Drawer_LoadSprite(const char* path, const int sheetW, const int sheetH, const int originX, const int originY);
void Drawer_DrawSprite(int spriteId, float x, float y, int subImage, float xScale, float yScale);
void Drawer_DrawSprite_Angle(int spriteId, float x, float y, int subImage, float xScale, float yScale, float angle);
void Drawer_DrawText(const unsigned char* text, int length, float x, float y, float xScale, float yScale);
void Drawer_FillRect(float x, float y, float w, float h);

void Drawer_SetProjection(float x, float y, float zoom);
void Drawer_SetDrawColor(uint8_t r, uint8_t g, uint8_t b);
void Drawer_SetDrawAlpha(uint8_t a);
void Drawer_SetDrawBlend(int blendMode);
void Drawer_SetFontSprite(int spriteId);
void Drawer_SetFontAlignment(int alignment);