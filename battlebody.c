#include "generic.h"
#include "battlebody.h"
#include "battlesystem.h"
#include "sprites.h"

BattleHead battleHeadData[OBJECT_COUNT_MAX];
BattleBody battleBodyData[OBJECT_COUNT_MAX];

void LoadBattleBodyData() {
	BattleHead* battleHead;
	BattleBody* battleBody;
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		battleHeadData[i].spriteId = -1;
		battleHeadData[i].backSpriteId = -1;
		battleBodyData[i].spriteId = -1;
	}
	
	
	
	battleHead = &battleHeadData[0];
	battleHead->spriteId = -1;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[1];
	battleHead->spriteId = SPR_head_ruby;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[2];
	battleHead->spriteId = SPR_head_noah;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[3];
	battleHead->spriteId = SPR_head_emmet;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[4];
	battleHead->spriteId = SPR_head_sally;
	battleHead->backSpriteId = SPR_head_sally_b;
	
	battleHead = &battleHeadData[7];
	battleHead->spriteId = SPR_head_perry;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[11];
	battleHead->spriteId = SPR_head_generic_0;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[12];
	battleHead->spriteId = SPR_head_generic_1;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[13];
	battleHead->spriteId = SPR_head_generic_2;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[14];
	battleHead->spriteId = SPR_head_bashura;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[15];
	battleHead->spriteId = SPR_head_lisao;
	battleHead->backSpriteId = SPR_head_lisao_b;
	
	battleHead = &battleHeadData[16];
	battleHead->spriteId = SPR_head_lulu;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[17];
	battleHead->spriteId = SPR_head_generic_3;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[18];
	battleHead->spriteId = SPR_head_generic_4;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[19];
	battleHead->spriteId = SPR_head_generic_5;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[20];
	battleHead->spriteId = SPR_head_generic_6;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[21];
	battleHead->spriteId = SPR_head_generic_7;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[22];
	battleHead->spriteId = SPR_head_generic_8;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[23];
	battleHead->spriteId = SPR_head_jackie;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[24];
	battleHead->spriteId = SPR_head_electra;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[25];
	battleHead->spriteId = SPR_head_ray;
	battleHead->backSpriteId = SPR_head_ray_b;
	
	battleHead = &battleHeadData[26];
	battleHead->spriteId = SPR_head_generic_9;
	battleHead->backSpriteId = SPR_head_generic_9_b;
	
	battleHead = &battleHeadData[27];
	battleHead->spriteId = SPR_head_generic_10;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[28];
	battleHead->spriteId = SPR_head_generic_11;
	battleHead->backSpriteId = SPR_head_generic_11_b;
	
	battleHead = &battleHeadData[29];
	battleHead->spriteId = SPR_head_dia;
	battleHead->backSpriteId = SPR_head_dia_b;
	
	battleHead = &battleHeadData[30];
	battleHead->spriteId = SPR_head_policecap;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[31];
	battleHead->spriteId = SPR_head_sync;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[32];
	battleHead->spriteId = SPR_head_josh;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[33];
	battleHead->spriteId = SPR_head_pirate;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[34];
	battleHead->spriteId = SPR_head_piratecap;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[35];
	battleHead->spriteId = SPR_head_sanji;
	battleHead->backSpriteId = SPR_head_sanji_b;
	
	battleHead = &battleHeadData[36];
	battleHead->spriteId = SPR_head_ninja;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[37];
	battleHead->spriteId = SPR_head_generic_12;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[38];
	battleHead->spriteId = SPR_head_generic_13;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[39];
	battleHead->spriteId = SPR_head_generic_14;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[40];
	battleHead->spriteId = SPR_head_amp;
	battleHead->backSpriteId = SPR_head_amp_b;
	
	battleHead = &battleHeadData[41];
	battleHead->spriteId = SPR_head_river;
	battleHead->backSpriteId = SPR_head_river_b;
	
	battleHead = &battleHeadData[42];
	battleHead->spriteId = SPR_head_frank;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[43];
	battleHead->spriteId = SPR_head_waxknight;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[44];
	battleHead->spriteId = SPR_head_flora;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[45];
	battleHead->spriteId = SPR_head_generic_15;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[46];
	battleHead->spriteId = SPR_head_kelly;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[47];
	battleHead->spriteId = SPR_head_neveah;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[48];
	battleHead->spriteId = SPR_head_brook;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[49];
	battleHead->spriteId = SPR_head_tom;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[50];
	battleHead->spriteId = SPR_head_cindy;
	battleHead->backSpriteId = SPR_head_cindy_b;
	
	battleHead = &battleHeadData[51];
	battleHead->spriteId = SPR_head_anonymous;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[52];
	battleHead->spriteId = SPR_head_generic_16;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[53];
	battleHead->spriteId = SPR_head_don;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[54];
	battleHead->spriteId = SPR_head_nate;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[55];
	battleHead->spriteId = SPR_head_volcano;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[56];
	battleHead->spriteId = SPR_head_luna;
	battleHead->backSpriteId = SPR_head_luna_b;
	
	battleHead = &battleHeadData[57];
	battleHead->spriteId = SPR_head_perry_knife;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[58];
	battleHead->spriteId = SPR_head_brian;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[59];
	battleHead->spriteId = SPR_head_nekin;
	battleHead->backSpriteId = SPR_head_nekin_b;
	
	battleHead = &battleHeadData[60];
	battleHead->spriteId = SPR_head_lulu_subspace;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[61];
	battleHead->spriteId = SPR_head_adios;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[62];
	battleHead->spriteId = SPR_head_bulldog;
	battleHead->backSpriteId = -1;
	
	battleHead = &battleHeadData[63];
	battleHead->spriteId = SPR_head_generic_17;
	battleHead->backSpriteId = -1;
	
	
	
	battleBody = &battleBodyData[0];
	battleBody->spriteId = -1;
	
	battleBody = &battleBodyData[1];
	battleBody->spriteId = SPR_body_ruby;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[2];
	battleBody->spriteId = SPR_body_ruby_zero;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[3];
	battleBody->spriteId = SPR_body_noah;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[4];
	battleBody->spriteId = SPR_body_emmet;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[5];
	battleBody->spriteId = SPR_body_sally;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[8];
	battleBody->spriteId = SPR_body_perry;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[10];
	battleBody->spriteId = SPR_body_ruby_armed;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	
	
	
	battleBody = &battleBodyData[11];
	battleBody->spriteId = SPR_body_hobo;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[12];
	battleBody->spriteId = SPR_body_navygang;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[13];
	battleBody->spriteId = SPR_body_leafcrew;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[14];
	battleBody->spriteId = SPR_body_lisao;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 1, -14);
	
	battleBody = &battleBodyData[15];
	battleBody->spriteId = SPR_body_lulu;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 1, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 0, -15);
	
	battleBody = &battleBodyData[16];
	battleBody->spriteId = SPR_body_lulu_blaze;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 1, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[17];
	battleBody->spriteId = SPR_body_police;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[18];
	battleBody->spriteId = SPR_body_farmer;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[19];
	battleBody->spriteId = SPR_body_knifethug;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[20];
	battleBody->spriteId = SPR_body_vandal_knife;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[21];
	battleBody->spriteId = SPR_body_vandal_flail;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[22];
	battleBody->spriteId = SPR_body_nurse;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[23];
	battleBody->spriteId = SPR_body_jackie;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 0, 1, -14);
	
	battleBody = &battleBodyData[24];
	battleBody->spriteId = SPR_body_electra;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[25];
	battleBody->spriteId = SPR_body_ray;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[26];
	battleBody->spriteId = SPR_body_lulu_omega;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 1, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[27];
	battleBody->spriteId = SPR_body_slime;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[28];
	battleBody->spriteId = SPR_body_slimeboss;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[29];
	battleBody->spriteId = SPR_body_dia;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[30];
	battleBody->spriteId = SPR_body_spider;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[31];
	battleBody->spriteId = SPR_body_spiderboss;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[32];
	battleBody->spriteId = SPR_body_policecap;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[33];
	battleBody->spriteId = SPR_body_sync;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[34];
	battleBody->spriteId = SPR_body_josh;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[35];
	battleBody->spriteId = SPR_body_pirate;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[36];
	battleBody->spriteId = SPR_body_piratecap;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[37];
	battleBody->spriteId = SPR_body_sanji;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[38];
	battleBody->spriteId = SPR_body_ninja;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -13);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 0, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[39];
	battleBody->spriteId = SPR_body_agent;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 5, 4, -11);
	
	battleBody = &battleBodyData[40];
	battleBody->spriteId = SPR_body_bpolice;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[41];
	battleBody->spriteId = SPR_body_gpolice;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL4, 5, 4, -11);
	
	battleBody = &battleBodyData[42];
	battleBody->spriteId = SPR_body_amp;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL3, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL4, 4, 1, -14);
	
	battleBody = &battleBodyData[43];
	battleBody->spriteId = SPR_body_river;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[44];
	battleBody->spriteId = SPR_body_frank;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[45];
	battleBody->spriteId = SPR_body_waxknight;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[46];
	battleBody->spriteId = SPR_body_flora;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 0, 1, -14);
	
	battleBody = &battleBodyData[47];
	battleBody->spriteId = SPR_body_deathknife;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[48];
	battleBody->spriteId = SPR_body_energyentity;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[49];
	battleBody->spriteId = SPR_body_deathweight;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[50];
	battleBody->spriteId = SPR_misc_hellgateboss;
	
	battleBody = &battleBodyData[51];
	battleBody->spriteId = SPR_body_kelly;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[52];
	battleBody->spriteId = SPR_body_neveah;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[53];
	battleBody->spriteId = SPR_body_brook;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -17);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -13);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -16);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -17);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -13);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -13);
	
	battleBody = &battleBodyData[54];
	battleBody->spriteId = SPR_body_tom;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 1);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[55];
	battleBody->spriteId = SPR_body_cindy;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 1, -10);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 0, 1, -14);
	
	battleBody = &battleBodyData[56];
	battleBody->spriteId = SPR_body_slimesuit;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[57];
	battleBody->spriteId = SPR_body_spidersuit;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[58];
	battleBody->spriteId = SPR_body_ozone;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 5, 4, -11);
	
	battleBody = &battleBodyData[59];
	battleBody->spriteId = SPR_body_don;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 5, 4, -11);
	
	battleBody = &battleBodyData[60];
	battleBody->spriteId = SPR_body_nate;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 4, 0, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 4, -1, -12);
	
	battleBody = &battleBodyData[61];
	battleBody->spriteId = SPR_body_volcano;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 4, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 4, 5, -12);
	
	battleBody = &battleBodyData[62];
	battleBody->spriteId = SPR_body_luna;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 1, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 0, 1, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 6, 0, -14);
	
	battleBody = &battleBodyData[63];
	battleBody->spriteId = SPR_body_unknown1;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[64];
	battleBody->spriteId = SPR_body_unknown2;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[65];
	battleBody->spriteId = SPR_body_hellgoner;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL3, 2, 0, -1112);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL4, 2, 0, -1108);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL5, 2, 0, -1106);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL6, 2, 0, -1105);
	
	battleBody = &battleBodyData[66];
	battleBody->spriteId = SPR_misc_flowergame;
	
	battleBody = &battleBodyData[67];
	battleBody->spriteId = SPR_body_perry_knife;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	
	battleBody = &battleBodyData[68];
	battleBody->spriteId = SPR_body_brian;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 6, 0, -13);
	
	battleBody = &battleBodyData[69];
	battleBody->spriteId = SPR_body_nekin;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, -1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, -1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	
	battleBody = &battleBodyData[70];
	battleBody->spriteId = SPR_body_lulu_subspace;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -15);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 1, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 4, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL3, 0, 1, -14);
	
	battleBody = &battleBodyData[71];
	battleBody->spriteId = SPR_body_adios;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL2, 0, 1, -14);
	
	battleBody = &battleBodyData[72];
	battleBody->spriteId = SPR_body_bulldog;
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_IDLE, 0, 1, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_RUN, 1, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_BLOCK, 0, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_HURT, 2, 0, -14);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_DOWN, 3, -12, 4);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK1, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK2, 5, 4, -11);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_ATTACK3, 4, 5, -12);
	BattleBody_SetStateData(battleBody, FIGHTER_STATE_SPECIAL1, 0, 1, -15);
}

void BattleBody_SetStateData(BattleBody* battleBody, int state, int headFrame, int headOffsetX, int headOffsetY) {
	battleBody->headFrame[state] = headFrame;
	battleBody->headOffsetX[state] = headOffsetX;
	battleBody->headOffsetY[state] = headOffsetY;
}
