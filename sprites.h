#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

#define SPRITE_COUNT_MAX 1024

typedef struct {
	float projection_x;
	float projection_y;
	float projection_zoom;
	uint8_t color[3];
	uint8_t alpha;
	SDL_BlendMode blendMode;
	int fontSpriteId;
	int fontAlignment;
} GameDrawState;

extern GameDrawState gameDrawState;

typedef struct {
	SDL_Texture* texture;
	int w; int h;
	int subW; int subH;
	int subImages;
	int subImagesPerRow;
	int originX; int originY;
	
	uint8_t color[3];
	uint8_t alpha;
	SDL_BlendMode blendMode;
} Sprite;

extern int spriteCount;
extern Sprite sprites[SPRITE_COUNT_MAX];

enum {
	SPR_head_ruby,
	SPR_body_ruby,
	SPR_body_ruby_zero,
	SPR_body_ruby_armed,
	
	SPR_head_noah,
	SPR_body_noah,
	
	SPR_head_emmet,
	SPR_body_emmet,
	
	SPR_head_sally,
	SPR_head_sally_b,
	SPR_body_sally,
	
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
	
	
	
	SPR_owchar_ruby,
	SPR_owchar_ruby_run,
	SPR_owchar_ruby_run_prepare,
	SPR_owchar_ruby_flashlight,
	SPR_owchar_ruby_blush,
	SPR_owchar_ruby_zero,
	SPR_owchar_ruby_zero2,
	SPR_owchar_noah,
	SPR_owchar_noah_run,
	SPR_owchar_emmet,
	SPR_owchar_emmet_run,
	SPR_owchar_sally,
	SPR_owchar_sally_run,
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
	
	SPR_owchar_rubin,
	
	SPR_owchar_collapse_ruby,
	SPR_owchar_collapse_noah,
	SPR_owchar_collapse_emmet,
	SPR_owchar_collapse_sally,
	SPR_owchar_collapse_perry,
	SPR_owchar_collapse_dia,
	SPR_owchar_collapse_nekin,
	SPR_owchar_collapse_luna,
	SPR_owchar_collapse_lulu_omega,
	
	SPR_owchar_climb_ruby,
	SPR_owchar_climb_noah,
	SPR_owchar_climb_emmet,
	SPR_owchar_climb_sally,
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
	SPR_spark_saw,
	SPR_spark_snow,
	SPR_spark_ring,
	SPR_spark_boost,
	
	
	
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
	
	SPR_misc_backdrop_hell,
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
	
	SPR_misc_lisao_sleep,
	SPR_misc_ruby_wakeup,
	SPR_misc_ruby_think,
	SPR_misc_ruby_shrug,
	SPR_misc_emmet_facepalm,
	SPR_misc_sally_serious,
	SPR_misc_perry_sleep,
	SPR_misc_perryhomesleep,
	SPR_misc_lulu_omega_rage,
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
	SPR_misc_sally_phone,
	SPR_misc_npc_22_phone,
	
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
	
	SPR_misc_voidportal,
	SPR_misc_hellgate,
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
void LoadSprite(const char* path, const int sheetW, const int sheetH, const int originX, const int originY);
void FreeSprites();
void DrawSprite(int spriteId, float x, float y, int subImage, float xScale, float yScale);
void DrawSprite_Angle(int spriteId, float x, float y, int subImage, float xScale, float yScale, float angle);
void DrawText(const unsigned char* text, int length, float x, float y, float xScale, float yScale);
void FillRect(float x, float y, float w, float h);

void SetProjection(float x, float y, float zoom);
void SetDrawColor(uint8_t r, uint8_t g, uint8_t b);
void SetDrawAlpha(uint8_t a);
void SetDrawBlend(SDL_BlendMode blendMode);
void SetFontSprite(int spriteId);
void SetFontAlignment(int alignment);