#include "generic.h"
#include "overworld.h"
#include "sprites.h"
#include "audio.h"
#include "dialog.h"
#include "party.h"
#include "battlesystem.h"
#include "profile.h"
#include "action.h"
#include "armor.h"
#include "items.h"
#include "passives.h"
#include "event.h"



void Overworld_ChangeArea(int id) {
	overworld.areaId = id;
	
	for (int i = 0; i < 8; i++) {
		overworld.objects[i].moveTarget.enabled = false;
		overworld.objects[i].state = OBJECT_STATE_IDLE;
		overworld.objects[i].spriteFrame %= 3;
	}
	for (int i = 8; i < OBJECT_COUNT_MAX; i++) {
		overworld.objects[i].type = 0;
	}
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		overworld.map.triggers[i].eventId = 0;
	}
	
	overworld.overlayId = 0;
	overworld.areaWrap = false;
	overworld.player.dashEnabled = true;
	Party_UpdateCaterpillar();
	
	overworld.map.doors[0].enabled = profile.flags[FLAG_PLOT] > 1;
	
	switch (id) {
		case 0:
			if (profile.flags[FLAG_PLOT] <= 2)
				PlayMusic(MUS_outside);
			else if (overworld.map.tilesetSpriteId == SPR_tileset_day_autumn)
				PlayMusic(MUS_mysterious);
			else if (overworld.map.tilesetSpriteId == SPR_tileset_day_forest)
				PlayMusic(MUS_forest);
			else
				PlayMusic(MUS_field);
			
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 0;
			
			Overworld_CreateNPC(73, 10000, 3056, 864, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(74, 10000, 2288, 5120, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(75, 10000, 3368, 5344, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(76, 10000, 6440, 3408, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(77, 10000, 7864, 3488, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(78, 10000, 3064, 1424, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(79, 10000, 11136, 4080, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateEnemy(80, 1, 3600, 5456);
			Overworld_CreateEnemy(81, 1, 5296, 5040);
			Overworld_CreateEnemy(82, 3, 5456, 4368);
			Overworld_CreateEnemy(83, 3, 5744, 4528);
			Overworld_CreateEnemy(84, 2, 4112, 4528);
			
			Overworld_CreateEnemy(85, 13, 6672, 4880);
			Overworld_CreateEnemy(86, 12, 6608, 4480);
			
			Overworld_CreateEnemy(87, 12, 9744, 3920);
			
			Overworld_CreateEnemy(88, 6, 3696, 3008);
			Overworld_CreateEnemy(89, 6, 3872, 2848);
			Overworld_CreateEnemy(90, 7, 3120, 2496);
			
			if (Random(1) < 0.25) {
				Overworld_CreateEnemy(91, 27, 4464, 2000);
			}
			
			Overworld_CreateNPC(19, 14, 8608, 3600, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] <= 13) {
				Overworld_CreateNPC(20, 24, 8472, 5216, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateObject(20, 1, SPR_misc_sapphirebus, 8456, 4864, OBJECT_DIRECTION_RIGHT);
				OverworldObject_ToggleGhost(20, true);
			}
			Overworld_CreateNPC(21, 13, 5536, 3328, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(29, 10007, 4376, 4360, OBJECT_DIRECTION_DOWN);
			
			//Overworld_CreateNPC_Wandering(30, 1000, 8400, 3648, OBJECT_DIRECTION_DOWN);
			//Overworld_CreateNPC_Wandering(31, 1001, 8832, 3680, OBJECT_DIRECTION_DOWN);
			//Overworld_CreateNPC_Wandering(32, 1000, 8688, 3824, OBJECT_DIRECTION_DOWN);
			//Overworld_CreateNPC_Wandering(33, 1001, 8992, 3776, OBJECT_DIRECTION_DOWN);
			//Overworld_CreateNPC_Wandering(34, 1000, 9280, 3568, OBJECT_DIRECTION_DOWN);
			//Overworld_CreateNPC_Wandering(35, 1001, 8720, 3984, OBJECT_DIRECTION_DOWN);
			//Overworld_CreateNPC_Wandering(36, 1002, 8656, 3584, OBJECT_DIRECTION_DOWN);
			//Overworld_CreateNPC_Wandering(37, 1003, 8992, 3584, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] <= 2) {
				Overworld_CreateTrigger(7, 3216, 5328, 3344, 5392, 23);
			}
			if (profile.flags[FLAG_PLOT] <= 4) {
				Overworld_CreateTrigger(0, 5632, 3872, 5664, 4064, 2);
				Overworld_CreateObject(11, 1, SPR_owchar_navygang, 5664, 3952, OBJECT_DIRECTION_LEFT);
				Overworld_CreateObject(12, 1, SPR_owchar_navygang, 5664, 3984, OBJECT_DIRECTION_LEFT);
			}
			if (profile.flags[FLAG_PLOT] <= 5) {
				Overworld_CreateTrigger(1, 5888, 3872, 5920, 4032, 3);
				Overworld_CreateObject(13, 1, SPR_owchar_sally, 6016, 3888, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(14, 1, SPR_owchar_frank, 6000, 3920, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(15, 1, SPR_owchar_river, 6032, 3920, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(16, 1, SPR_owchar_emmet, 6016, 3840, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] <= 9) {
				if (profile.flags[FLAG_SILVERBLOCK_PUSHED] == 0)
					Overworld_CreateNPC(17, 6, 7568, 3536, OBJECT_DIRECTION_DOWN);
				else
					Overworld_CreateNPC(17, 6, 7624, 3536, OBJECT_DIRECTION_DOWN);
				OverworldObject_SetCollisionSize(17, 16, 28);
				Overworld_CreateNPC(18, 1, 7728, 3488, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] <= 10) {
				Overworld_CreateTrigger(2, 8304, 3552, 8352, 4048, 4);
			}
			if (profile.flags[FLAG_PLOT] == 10) {
				//Overworld_CreateTrigger(3, 7488, 3488, 7504, 3552, 5);
			}
			if (profile.flags[FLAG_PLOT] <= 11) {
				Overworld_CreateNPC(22, 2, 3712, 3344, OBJECT_DIRECTION_RIGHT);
				Overworld_CreateNPC(23, 2, 3712, 3376, OBJECT_DIRECTION_RIGHT);
				Overworld_CreateWall(24, 3712, 3392, 16, 80);
			}
			if (profile.flags[FLAG_PLOT] == 12) {
				Overworld_CreateTrigger(4, 3232, 1392, 3248, 1504, 7);
				Overworld_CreateObject(11, 1, SPR_owchar_leafcrew_alt, 3296, 1456, OBJECT_DIRECTION_LEFT);
			}
			if (profile.flags[FLAG_PLOT] == 13) {
				Overworld_CreateTrigger(5, 3024, 528, 3088, 560, 8);
				Overworld_CreateObject(11, 1, SPR_owchar_lisao, 3056, 448, OBJECT_DIRECTION_UP);
			}
			if (profile.flags[FLAG_PLOT] == 14) {
				Overworld_CreateTrigger(5, 3040, 576, 3072, 592, 44);
			}
			if (profile.flags[FLAG_PLOT] == 15) {
				Overworld_CreateTrigger(6, 3008, 1904, 3072, 1920, 13);
			}
			if (profile.flags[FLAG_PLOT] <= 16) {
				Overworld_CreateNPC(25, 19, 3424, 1072, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(26, 20, 3496, 1424, OBJECT_DIRECTION_LEFT);
				if (!profile.flags[FLAG_LEAFCREW_OPTIONALFIGHT]) Overworld_CreateNPC(27, 21, 3608, 1168, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(28, 22, 3784, 1168, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PURCHASED_BUS_TICKET]) {
				Overworld_CreateTrigger(8, 8288, 4976, 8400, 5152, 25);
			}
			if (!profile.flags[FLAG_BRICKWALL_REMOVED]) {
				Overworld_CreateNPC(30, 10027, 6528, 3840, OBJECT_DIRECTION_DOWN);
				
				if (profile.flags[FLAG_PLOT] >= 11) {
					Overworld_CreateTrigger(9, 6400, 3424, 6576, 3472, 30);
				}
			}
			if (profile.flags[FLAG_PLOT] >= 11) {
				Overworld_CreateNPC(31, 32, 2008, 5080, OBJECT_DIRECTION_LEFT);
			}
			Overworld_CreateNPC(32, 33, 9384, 3512, OBJECT_DIRECTION_DOWN);
			
			if (!profile.flags[FLAG_ITEM_LEAFCREW_TOMATOSOUP]) {
				Overworld_CreateNPC(50, 10006, 3240, 2200, OBJECT_DIRECTION_DOWN);
			}
			if (!profile.flags[FLAG_ITEM_LEAFCREW_HEAL_B]) {
				Overworld_CreateNPC(51, 10041, 2448, 1120, OBJECT_DIRECTION_DOWN);
			}
			if (!profile.flags[FLAG_ITEM_VILLAGE_DANDELION]) {
				Overworld_CreateNPC(52, 10053, 11080, 4040, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC(53, 10043, 7520, 3904, OBJECT_DIRECTION_DOWN);
			overworld.objects[53].vars[7].i = 12;
			if (profile.flags[FLAG_ITEM_VILLAGE_GREENTEA]) OverworldObject_ChangeSpriteFrame(53, 1);
			break;
		case 1:
			StopMusic();
			Overworld_CreateNPC(10, 0, -5712, 2680, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(11, 10003, 752, 2680, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] <= 1) Overworld_CreateNPC(12, 10005, 552, 2656, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] == -1) Overworld_CreateTrigger(0, 64, 2416, 632, 2992, 1);
			break;
		case 2:
			PlayMusic(MUS_cave);
			break;
		case 3:
			PlayMusic(MUS_cave);
			
			Overworld_CreateEnemy(80, 24, 1680, 9456);
			Overworld_CreateEnemy(81, 24, 1504, 9696);
			Overworld_CreateEnemy(82, 24, 1840, 9984);
			
			if (profile.flags[FLAG_PLOT] <= 8) {
				Overworld_CreateTrigger(0, 2208, 9600, 2224, 9680, 6);
				Overworld_CreateObject(10, 1, SPR_owchar_slimeboss, 2320, 9648, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 4:
			Overworld_CreateEnemy(80, 25, 2208, 9088);
			
			if (!profile.flags[FLAG_ITEM_SLIMECAVE_TOMATOSOUP]) {
				Overworld_CreateNPC(10, 10006, 2232, 9264, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 5:
			PlayMusic(MUS_secretambience);
			
			Overworld_CreateNPC(10, 8, 464, 1272, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] <= 14) {
				Overworld_CreateTrigger(0, 496, 1328, 672, 1408, 9);
				Overworld_CreateNPC(11, 60001, 552, 1268, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 6:
			PlayMusic(MUS_town);
			
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 11;
			
			overworld.map.doors[17].enabled = profile.flags[FLAG_PLOT] >= 55 && profile.flags[FLAG_ALONE_PLOT] != 2;
			
			Overworld_CreateNPC(75, 10000, 13248, 7952, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(76, 10000, 17120, 8416, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(77, 10000, 17400, 6568, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(78, 10000, 20096, 7088, OBJECT_DIRECTION_DOWN);
			
			
			Overworld_CreateEnemy(80, 15, 15552, 7744);
			Overworld_CreateEnemy(81, 17, 17664, 7744);
			Overworld_CreateEnemy(82, 16, 16384, 8416);
			Overworld_CreateEnemy(83, 17, 17664, 8448);
			Overworld_CreateEnemy(84, 18, 14800, 6944);
			Overworld_CreateEnemy(85, 11, 16320, 6928);
			Overworld_CreateEnemy(86, 19, 16128, 6752);
			Overworld_CreateEnemy(87, 34, 16016, 5120);
			
			if (profile.flags[FLAG_PLOT] >= 74) {
				//Overworld_CreateEnemy(88, 44, 18840, 8612);
			}
			
			if (profile.flags[FLAG_PLOT] <= 51) {
				Overworld_CreateTrigger(1, 13616, 7872, 13632, 8000, 15);
				Overworld_CreateObject(10, 1, SPR_owchar_police_0, 13656, 7968, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(11, 1, SPR_owchar_police_0, 13688, 7968, OBJECT_DIRECTION_UP);
			}
			if (profile.flags[FLAG_PLOT] == 54) {
				if (profile.flags[FLAG_ALONE]) {
					Overworld_CreateNPC(18, 10, 16664, 8392, OBJECT_DIRECTION_DOWN);
				}
				else {
					Overworld_CreateTrigger(0, 17008, 8368, 17104, 8416, 17);
				}
			}
			if (profile.flags[FLAG_PLOT] == 59) {
				Overworld_CreateTrigger(0, 16352, 7664, 16432, 7712, 20);
				Overworld_CreateObject(10, 1, SPR_owchar_josh, 16224, 7696, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(11, 1, SPR_owchar_sync, 16192, 7696, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_owchar_sync, 16160, 7696, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] >= 59 && profile.flags[FLAG_SALLY_JOINED] == 0 && profile.flags[FLAG_SALLY_SPIDERTRAP] == 0) {
				Overworld_CreateTrigger(1, 14240, 6576, 14464, 6800, 21);
				Overworld_CreateTrigger(2, 14240, 6880, 14320, 7024, 21);
				Overworld_CreateObject(13, 1, SPR_owchar_sally, 14400, 6672, OBJECT_DIRECTION_UP);
			}
			if (profile.flags[FLAG_PLOT] == 73) {
				Overworld_CreateTrigger(0, 15504, 3552, 15648, 3616, 28);
				Overworld_CreateObject(10, 1, SPR_owchar_lulu, 15576, 3736, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(11, 1, SPR_owchar_sync, 15528, 3744, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(12, 1, SPR_owchar_sync, 15624, 3744, OBJECT_DIRECTION_UP);
			}
			Overworld_CreateNPC(17, 73, 20416, 7136, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(20, 74, 20200, 7128, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] >= 74) {
				//Overworld_CreateTrigger(1, 20192, 7104, 20256, 7200, 29);
				Overworld_CreateObject(13, 1, SPR_misc_sapphireship, 20328, 7096, OBJECT_DIRECTION_RIGHT);
				OverworldObject_ToggleGhost(13, true);
				OverworldObject_ChangeSpriteFrameSpeed(13, 0.05);
				
			}
			if (profile.flags[FLAG_PLOT] == 73 || profile.flags[FLAG_PLOT] == 74) {
				Overworld_CreateTrigger(1, 14576, 4672, 14640, 4704, 56);
			}
			if (profile.flags[FLAG_ALONE_PLOT] == 2) {
				Overworld_CreateNPC(19, 10012, 16392, 7672, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_SALLY_JOINED] && profile.flags[FLAG_ALONE_PLOT] > 2) {
				Overworld_CreateTrigger(1, 16372, 7680, 16412, 7726, 55);
			}
			
			if (!profile.flags[FLAG_VANDAL_OPTIONALFIGHT]) {
				Overworld_CreateNPC(15, 35, 19552, 6720, OBJECT_DIRECTION_DOWN);
			}
			
			Overworld_CreateNPC(16, 36, 18800, 8416, OBJECT_DIRECTION_DOWN);
			
			overworld.map.doors[23].enabled = profile.flags[FLAG_PLOT] >= 61;
			if (profile.flags[FLAG_PLOT] < 61) {
				Overworld_CreateNPC(14, 10015, 15576, 3544, OBJECT_DIRECTION_DOWN);
			}
			
			Overworld_CreateNPC(21, 89, 17224, 7080, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(22, 90, 17352, 7160, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(23, 91, 17144, 7352, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(24, 1001, 17160, 7080, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(25, 1005, 17288, 7080, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(26, 95, 16360, 7304, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(27, 1001, 15256, 7456, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(28, 96, 15528, 7368, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(29, 92, 15720, 7384, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_FUN] % 13 == 0) {
				Overworld_CreateNPC(30, 70011, 15912, 3216, OBJECT_DIRECTION_DOWN);
			}
			
			if (!profile.flags[FLAG_ITEM_TOWN_HEAL]) {
				Overworld_CreateNPC(50, 10040, 14976, 4256, OBJECT_DIRECTION_DOWN);
			}
			
			Overworld_CreateNPC(51, 10043, 19992, 5144, OBJECT_DIRECTION_DOWN);
			overworld.objects[51].vars[7].i = 26;
			if (profile.flags[FLAG_ITEM_TOWN_POWER]) OverworldObject_ChangeSpriteFrame(51, 1);
			
			Overworld_CreateNPC(52, 10043, 20024, 5144, OBJECT_DIRECTION_DOWN);
			overworld.objects[52].vars[7].i = 25;
			if (profile.flags[FLAG_ITEM_TOWN_ENERGYDRINK]) OverworldObject_ChangeSpriteFrame(52, 1);
			
			if (!profile.flags[FLAG_ITEM_TOWN_TOMATOSOUP]) {
				Overworld_CreateNPC(53, 10006, 20104, 7512, OBJECT_DIRECTION_DOWN);
			}
			break;
		
		case 7:
			PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 4, 10232, 8128, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 5, 10512, 8144, OBJECT_DIRECTION_DOWN);
			if (!profile.flags[FLAG_JACKIECAFE_BROKENGLASS]) {
				Overworld_CreateNPC(12, 57, 10360, 8272, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(13, 10034, 10356, 8284, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] <= 52 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateTrigger(0, 9920, 8384, 10544, 8432, 16);
			}
			break;
		
		case 9:
			if (!profile.flags[FLAG_ALONE_PERRY_SPARED] && (profile.flags[FLAG_PLOT] == 57 || profile.flags[FLAG_PLOT] == 58 || profile.flags[FLAG_ALONE_PLOT] >= 2))
				StopMusic();
			else
				PlayMusic(MUS_casual);
			
			overworld.map.doors[17].enabled = true;
			
			Overworld_CreateNPC(75, 10000, 9640, 8344, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] == 54) {
				Overworld_CreateObject(70, 1, SPR_owchar_perry, 9608, 8384, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] == 57) {
				Overworld_CreateTrigger(0, 9456, 8160, 9760, 8448, 18);
			}
			break;
		case 10:
			if (profile.flags[FLAG_PLOT] >= 59) {
				for (int i = 0; i < 3 - profile.flags[FLAG_PERRY_PIZZASLICES]; i++) {
					Overworld_CreateNPC(10 + i, 10010, 9280 - i * 22, 8384, OBJECT_DIRECTION_DOWN);
				}
			}
			if (profile.flags[FLAG_ALONE_PLOT] >= 2) {
				Overworld_CreateNPC(10, 10051, 9296, 8312, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 11:
			if (profile.flags[FLAG_ALONE_PLOT] < 2 && !profile.flags[FLAG_ALONE_PERRY_SPARED] && (profile.flags[FLAG_PLOT] <= 55 || profile.flags[FLAG_PLOT] >= 59)) {
				Overworld_CreateNPC(10, 10, 9000, 8416, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] == 58) {
				Overworld_CreateTrigger(0, 8880, 8368, 8928, 8448, 19);
				Overworld_CreateNPC(10, 10, 9120, 8456, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteId(10, SPR_misc_perry_sleep);
				OverworldObject_ChangeSpriteFrameSpeed(10, 0.01);
			}
			else if (profile.flags[FLAG_ALONE_PERRY_SPARED]) {
				Overworld_CreateNPC(10, 10, 9120, 8456, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteId(10, SPR_misc_perry_sleep);
				OverworldObject_ChangeSpriteFrameSpeed(10, 0.01);
			}
			if (profile.flags[FLAG_PLOT] >= 58) {
				Overworld_CreateObject(11, 1, SPR_misc_perryhomesleep, 8912, 8464, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(11, 0);
				if (!profile.flags[FLAG_ALONE]) {
					Overworld_CreateObject(12, 1, SPR_misc_perryhomesleep, 8960, 8464, OBJECT_DIRECTION_DOWN);
					OverworldObject_ChangeSpriteFrame(12, 1);
					Overworld_CreateObject(13, 1, SPR_misc_perryhomesleep, 9008, 8464, OBJECT_DIRECTION_DOWN);
					OverworldObject_ChangeSpriteFrame(13, 2);
				}
			}
			break;
		case 12:
			if (!profile.flags[FLAG_ALONE_PERRY_SPARED] && (profile.flags[FLAG_PLOT] == 57 || profile.flags[FLAG_PLOT] == 58 || profile.flags[FLAG_ALONE_PLOT] >= 2))
				StopMusic();
			else
				PlayMusic(MUS_casual);
			
			overworld.map.doors[21].enabled = profile.flags[FLAG_PLOT] >= 56;
			if (profile.flags[FLAG_PLOT] < 56) {
				Overworld_CreateNPC(10, 10012, 9512, 8688, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 13:
			if (profile.flags[FLAG_ALONE_PLOT] < 2 || profile.flags[FLAG_ALONE_PERRY_SPARED])
				PlayMusic(MUS_cave);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			if (profile.flags[FLAG_ALONE_PLOT] > 2) {
				Overworld_CreateNPC(10, 58, 9450, 9160, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(11, 1, SPR_misc_collapseblood, 9450, 9159, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(11, 2);
			}
			else if (profile.flags[FLAG_ALONE_PLOT] == 2 && !profile.flags[FLAG_ALONE_PERRY_SPARED]) {
				Overworld_CreateNPC(10, 10, 9368, 9144, OBJECT_DIRECTION_UP);
				Overworld_CreateTrigger(0, 9312, 9136, 9328, 9232, 45);
			}
			else {
				if (!profile.flags[FLAG_ALONE_PERRY_SPARED]) Overworld_CreateObject(70, 1, SPR_misc_knife, 9368, 9132, OBJECT_DIRECTION_DOWN);
				Overworld_CreateEnemy(80, 33, 9216, 8960);
				Overworld_CreateEnemy(81, 30, 9440, 9200);
			}
			
			if (profile.flags[FLAG_PLOT] <= 56) {
				Overworld_CreateNPC(10, 11, 9464, 9160, OBJECT_DIRECTION_DOWN);
			}
			if (!profile.flags[FLAG_FLASHLIGHT]) {
				Overworld_CreateNPC(11, 10011, 9424, 9008, OBJECT_DIRECTION_DOWN);
			}
			if (!profile.flags[FLAG_PERRY_BASEMENT_DIALOG]) {
				Overworld_CreateTrigger(0, 9488, 8800, 9536, 8832, 26);
			}
			break;
		case 14:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				StopMusic();
			else
				PlayMusic(MUS_mansion);
			
			Overworld_CreateNPC(75, 10000, 8104, 8008, OBJECT_DIRECTION_DOWN);
			break;
		
		case 17:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				StopMusic();
			else
				PlayMusic(MUS_mansion);
			
			Overworld_CreateNPC(75, 10000, 7352, 7912, OBJECT_DIRECTION_DOWN);
			
			overworld.map.doors[27].enabled = profile.flags[FLAG_MANSION_UNLOCKED_DIAMOND];
			if (!profile.flags[FLAG_MANSION_UNLOCKED_DIAMOND]) {
				Overworld_CreateNPC(10, 10018, 7400, 7896, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 18:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				StopMusic();
			else
				PlayMusic(MUS_mansion);
			
			if (profile.flags[FLAG_PLOT] <= 71) {
				Overworld_CreateTrigger(0, 7312, 7664, 7488, 7680, 12);
				Overworld_CreateNPC(10, 27, 7400, 7576, OBJECT_DIRECTION_UP);
			}
			break;
		case 19:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				StopMusic();
			else if (profile.flags[FLAG_PLOT] <= 72)
				PlayMusic(MUS_secretambience);
			else
				PlayMusic(MUS_mansion);
			
			if (profile.flags[FLAG_PLOT] <= 72) {
				Overworld_CreateNPC(10, 27, 7536, 7232, OBJECT_DIRECTION_UP);
				Overworld_CreateTrigger(0, 7360, 7296, 7440, 7344, 27);
				Overworld_CreateNPC(11, 60002, 7432, 7216, OBJECT_DIRECTION_DOWN);
			}
			else if (profile.flags[FLAG_ALONE_PLOT] >= 20) {
				Overworld_CreateNPC(10, 27, 7452, 7240, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(11, 1, SPR_misc_collapseblood, 7452, 7239, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(11, 1);
			}
			else {
				Overworld_CreateNPC(10, 27, 7528, 7264, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 20:
			overworld.map.doors[30].enabled = profile.flags[FLAG_MANSION_UNLOCKED_GOLD];
			if (!profile.flags[FLAG_MANSION_UNLOCKED_GOLD]) {
				Overworld_CreateNPC(10, 10017, 7560, 8344, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 21:
			PlayMusic(MUS_cave);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			break;
		case 22:
			PlayMusic(MUS_cave);
			
			Overworld_CreateNPC(75, 10000, 9696, 9880, OBJECT_DIRECTION_DOWN);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			Overworld_CreateNPC(15, 10022, 9412, 10216, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] <= 70) {
				Overworld_CreateTrigger(0, 9136, 9376, 9152, 9488, 11);
				Overworld_CreateObject(10, 1, SPR_owchar_spiderboss, 9040, 9456, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(11, 1, SPR_owchar_spider, 9056, 9408, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_owchar_spider, 9024, 9392, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(13, 1, SPR_owchar_spider, 8976, 9440, OBJECT_DIRECTION_DOWN);
				if (profile.flags[FLAG_ALONE] && !profile.flags[FLAG_SALLY_SPIDERTRAP]) {
					Overworld_CreateTrigger(1, 9348, 9824, 9408, 9872, 46);
				}
			}
			break;
		case 23:
			PlayMusic(MUS_secretambience);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			Overworld_CreateNPC(11, 10022, 8664, 9248, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 10049, 8664, 9208, OBJECT_DIRECTION_DOWN);
			
			if (!profile.flags[FLAG_MANSION_GOTKEY_DIAMOND]) Overworld_CreateNPC(10, 10020, 8664, 9224, OBJECT_DIRECTION_DOWN);
			break;
		case 24:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				StopMusic();
			else
				PlayMusic(MUS_mansion);
			
			Overworld_CreateNPC(15, 10022, 7672, 9864, OBJECT_DIRECTION_DOWN);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			if (profile.flags[FLAG_MANSION_FLOWERPUZZLE_3]) {
				Overworld_CreateEnemy(110, 50, 7528, 9640);
			}
			else {
				Overworld_CreateNPC(110, 10021, 7672, 9624, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(10, 10013, 7264, 9536, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(21, 10014, 7288, 9536, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(22, 10014, 7304, 9536, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(23, 10014, 7320, 9536, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(24, 10014, 7336, 9536, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(31, 1, SPR_misc_flowergame, 7288, 9520, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(32, 1, SPR_misc_flowergame, 7304, 9520, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(33, 1, SPR_misc_flowergame, 7320, 9520, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(34, 1, SPR_misc_flowergame, 7336, 9520, OBJECT_DIRECTION_DOWN);
				
				OverworldObject_ChangeSpriteFrame(31, 0);
				OverworldObject_ChangeSpriteFrame(32, 1);
				OverworldObject_ChangeSpriteFrame(33, 2);
				OverworldObject_ChangeSpriteFrame(34, 3);
			}
			
			if (profile.flags[FLAG_MANSION_FLOWERPUZZLE_4]) {
				Overworld_CreateEnemy(111, 50, 7816, 9640);
			}
			else {
				Overworld_CreateNPC(111, 10021, 7672, 9600, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(11, 10013, 8080, 9536, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(41, 10014, 8024, 9536, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(42, 10014, 8040, 9536, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(43, 10014, 8056, 9536, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(51, 1, SPR_misc_flowergame, 8024, 9520, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(52, 1, SPR_misc_flowergame, 8040, 9520, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(53, 1, SPR_misc_flowergame, 8056, 9520, OBJECT_DIRECTION_DOWN);
				
				OverworldObject_ChangeSpriteFrame(51, 3);
				OverworldObject_ChangeSpriteFrame(52, 3);
				OverworldObject_ChangeSpriteFrame(53, 3);
			}
			
			if (profile.flags[FLAG_MANSION_FLOWERPUZZLE_5]) {
				Overworld_CreateEnemy(112, 50, 7400, 9864);
			}
			else {
				Overworld_CreateNPC(112, 10021, 7672, 9576, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(12, 10013, 7264, 9928, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(61, 10014, 7288, 9928, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(62, 10014, 7304, 9928, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(63, 10014, 7320, 9928, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(64, 10014, 7336, 9928, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(71, 1, SPR_misc_flowergame, 7288, 9944, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(72, 1, SPR_misc_flowergame, 7304, 9944, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(73, 1, SPR_misc_flowergame, 7320, 9944, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(74, 1, SPR_misc_flowergame, 7336, 9944, OBJECT_DIRECTION_DOWN);
				
				OverworldObject_ChangeSpriteFrame(71, 0);
				OverworldObject_ChangeSpriteFrame(72, 1);
				OverworldObject_ChangeSpriteFrame(73, 1);
				OverworldObject_ChangeSpriteFrame(74, 0);
			}
			
			if (profile.flags[FLAG_MANSION_FLOWERPUZZLE_6]) {
				Overworld_CreateEnemy(113, 50, 7960, 9784);
			}
			else {
				Overworld_CreateNPC(113, 10021, 7672, 9552, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(13, 10013, 8080, 9928, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(81, 10014, 8024, 9928, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(82, 10014, 8040, 9928, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(83, 10014, 8056, 9928, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(91, 1, SPR_misc_flowergame, 8024, 9944, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(92, 1, SPR_misc_flowergame, 8040, 9944, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(93, 1, SPR_misc_flowergame, 8056, 9944, OBJECT_DIRECTION_DOWN);
				
				OverworldObject_ChangeSpriteFrame(91, 2);
				OverworldObject_ChangeSpriteFrame(92, 1);
				OverworldObject_ChangeSpriteFrame(93, 2);
			}
			break;
		
		case 26:
			if (!profile.flags[FLAG_ITEM_MANSION_DANDELION]) {
				Overworld_CreateNPC(10, 10053, 7592, 8060, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 27:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				StopMusic();
			else
				PlayMusic(MUS_mansion);
			
			if (profile.flags[FLAG_MANSION_SOFA_PUSHED]) {
				Overworld_CreateNPC(10, 10001, 8344, 8016, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateNPC(10, 10001, 8376, 8016, OBJECT_DIRECTION_DOWN);
			}
			overworld.map.doors[38].enabled = profile.flags[FLAG_MANSION_UNLOCKED_SILVER];
			if (!profile.flags[FLAG_MANSION_UNLOCKED_SILVER]) {
				Overworld_CreateNPC(11, 10016, 8376, 7992, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 28:
			Overworld_CreateNPC(11, 10022, 7896, 8280, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_MANSION_FLOWERPUZZLE_2]) {
				if (!profile.flags[FLAG_MANSION_GOTKEY_GOLD]) Overworld_CreateNPC(12, 10002, 7912, 8240, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateNPC(10, 10013, 7936, 8288, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(31, 10014, 7960, 8288, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(32, 10014, 7976, 8288, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(33, 10014, 7992, 8288, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(41, 1, SPR_misc_flowergame, 7960, 8272, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(42, 1, SPR_misc_flowergame, 7976, 8272, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(43, 1, SPR_misc_flowergame, 7992, 8272, OBJECT_DIRECTION_DOWN);
				
				OverworldObject_ChangeSpriteFrame(41, 0);
				OverworldObject_ChangeSpriteFrame(42, 2);
				OverworldObject_ChangeSpriteFrame(43, 1);
			}
			break;
		case 29:
			PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 15, 584, 864, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 16, 312, 864, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 17, 856, 864, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] < 14) Overworld_CreateNPC_Wandering(13, 18, 256, 1008, OBJECT_DIRECTION_UP);
			break;
		case 30:
			Overworld_CreateNPC(10, 10004, 516, 2948, OBJECT_DIRECTION_DOWN);
			if (!profile.flags[FLAG_RUBY_LABCOAT]) {
				Overworld_CreateNPC(11, 10004, 708, 2980, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 31:
			PlayMusic(MUS_casual);
			break;
		case 32:
			Overworld_CreateNPC(11, 10008, 1184, 2436, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_NOAH_JOINED] == 0) {
				Overworld_CreateNPC(10, 7, 1016, 2520, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 33:
			PlayMusic(MUS_casual);
			
			if (profile.flags[FLAG_PLOT] >= 14) {
				Overworld_CreateNPC(10, 37, 472, 2400, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 38, 424, 2376, OBJECT_DIRECTION_UP);
			}
			break;
		case 34:
			Overworld_CreateNPC(10, 10009, 726, 2260, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] < 14) Overworld_CreateNPC(11, 23, 728, 2280, OBJECT_DIRECTION_UP);
			break;
		case 35:
			if (profile.flags[FLAG_PLOT] >= 6 && !profile.flags[FLAG_EMMET_JOINED]) {
				Overworld_CreateNPC(10, 100, 712, 1960, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 36:
			PlayMusic(MUS_casual);
			
			if (profile.flags[FLAG_PURCHASED_BUS_TICKET]) {
				Overworld_CreateNPC(10, 25, 6824, 7032, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateNPC(10, 25, 6824, 7064, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC(11, 26, 6760, 7008, OBJECT_DIRECTION_DOWN);
			break;
		
		case 38:
			Overworld_CreateNPC(11, 10022, 8856, 8120, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 10022, 9000, 8056, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(13, 10023, 8848, 8064, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(14, 10024, 8880, 8064, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(15, 10025, 8880, 8032, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(16, 10026, 8848, 8032, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_MANSION_FLOWERPUZZLE_1]) {
				if (!profile.flags[FLAG_MANSION_GOTKEY_SILVER]) Overworld_CreateNPC(17, 10019, 8952, 7968, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateNPC(10, 10013, 8976, 8016, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(31, 10014, 9000, 8016, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(32, 10014, 9016, 8016, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(33, 10014, 9032, 8016, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(41, 1, SPR_misc_flowergame, 9000, 8000, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(42, 1, SPR_misc_flowergame, 9016, 8000, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(43, 1, SPR_misc_flowergame, 9032, 8000, OBJECT_DIRECTION_DOWN);
				
				OverworldObject_ChangeSpriteFrame(41, 4);
				OverworldObject_ChangeSpriteFrame(42, 1);
				OverworldObject_ChangeSpriteFrame(43, 4);
			}
			break;
		case 39:
			PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 29, 10328, 8864, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(11, 34, 10048, 9008, OBJECT_DIRECTION_LEFT);
			break;
		case 40:
			Overworld_CreateNPC(10, 30, 10376, 9312, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 31, 10504, 9312, OBJECT_DIRECTION_DOWN);
			break;
		case 41:
			PlayMusic(MUS_hotel);
			
			Overworld_CreateNPC(10, 93, 10328, 9840, OBJECT_DIRECTION_DOWN);
			break;
		
		case 43:
			Overworld_CreateNPC_Wandering(10, 94, 10424, 10328, OBJECT_DIRECTION_DOWN);
			break;
		
		case 44:
			PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 85, 10896, 9136, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 86, 10952, 9128, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 87, 11032, 9128, OBJECT_DIRECTION_DOWN);
			break;
		
		case 80:
			PlayMusic(MUS_city);
			
			overworld.map.doors[56].enabled = profile.flags[FLAG_PLOT] < 122 || profile.flags[FLAG_RCCLUB_PLOT] < 112;
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 5;
			
			Overworld_CreateNPC(75, 10000, 22440, 8608, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(76, 10000, 22776, 4568, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(77, 10000, 25608, 5800, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(78, 10000, 27496, 4808, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateEnemy(80, 37, 22920, 7448);
			Overworld_CreateEnemy(81, 39, 23944, 5304);
			if (profile.flags[FLAG_PLOT] >= 100) Overworld_CreateEnemy(82, 38, 22424, 7816);
			if (profile.flags[FLAG_PLOT] != 112) Overworld_CreateEnemy(83, 46, 23320, 4856);
			
			Overworld_CreateNPC_Wandering(10, 52, 25912, 4968, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(11, 53, 24624, 5312, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 54, 26040, 5896, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] == 112) {
				if (!profile.flags[FLAG_RCCLUB_CLEAR]) {
					Overworld_CreateTrigger(1, 22672, 4544, 22768, 4608, 52);
				}
				Overworld_CreateTrigger(0, 22984, 4672, 23024, 4768, 36);
				Overworld_CreateObject(70, 1, SPR_owchar_lulu_omega, 23088, 4416, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] <= 121) {
				Overworld_CreateNPC(13, 10050, 27048, 4800, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(14, 10050, 27096, 4800, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(15, 10050, 27160, 4800, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(16, 10050, 27208, 4800, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC(17, 71, 27256, 4824, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(18, 72, 27016, 4840, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] <= 100 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateNPC(19, 1001, 22888, 4580, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] <= 99 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateTrigger(0, 22368, 7456, 22416, 7872, 57);
			}
			Overworld_CreateObject(20, 1, SPR_misc_sapphireship, 22408, 8936, OBJECT_DIRECTION_RIGHT);
			OverworldObject_ChangeSpriteFrameSpeed(20, 0.05);
			Overworld_CreateNPC(21, 75, 22536, 8976, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(22, 36, 27208, 6264, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] >= 122 && profile.flags[FLAG_RCCLUB_PLOT] >= 112) {
				Overworld_CreateNPC(23, 10052, 22720, 4552, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_FUN] >= 900 && !profile.flags[FLAG_FUN_NOBODY_0]) {
				Overworld_CreateNPC(24, 70010, 22992, 5888, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 81:
			PlayMusic(MUS_discoquiet);
			
			if (profile.flags[FLAG_RCCLUB_PLOT] <= 101) {
				Overworld_CreateNPC(10, 39, 19936, 10224, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 40, 19968, 10224, OBJECT_DIRECTION_DOWN);
				Overworld_CreateTrigger(0, 19872, 10208, 20000, 10272, 31);
			}
			break;
		case 82:
			if (!profile.flags[FLAG_ALONE]) {
				if (profile.flags[FLAG_RCCLUB_PLOT] == 102) {
					Overworld_CreateTrigger(0, 20048, 10064, 20192, 10208, 32);
				}
				else if (profile.flags[FLAG_RCCLUB_PLOT] == 103) {
					Overworld_CreateTrigger(0, 20048, 10128, 20192, 10208, 33);
				}
			}
			break;
		case 83:
			if (profile.flags[FLAG_RCCLUB_PLOT] >= 102 && profile.flags[FLAG_RCCLUB_PLOT] <= 105) {
				Overworld_CreateNPC(10, 39, 19944, 9848, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 40, 19944, 9880, OBJECT_DIRECTION_UP);
			}
			break;
		case 84:
			PlayMusic(MUS_discoquiet);
			
			Overworld_CreateNPC(75, 10000, 20568, 10104, OBJECT_DIRECTION_DOWN);
			
			overworld.map.doors[62].enabled = profile.flags[FLAG_RCCLUB_DISCO_UNLOCKED];
			if (!profile.flags[FLAG_RCCLUB_DISCO_UNLOCKED]) {
				Overworld_CreateNPC(10, 10028, 20360, 9976, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 85:
			if (profile.flags[FLAG_RCCLUB_PLOT] <= 106) {
				Overworld_CreateNPC(10, 41, 19144, 10216, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 86:
			Overworld_CreateNPC(10, 42, 19240, 10560, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 43, 19304, 10560, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_RCCLUB_PLOT] <= 108) {
				Overworld_CreateTrigger(0, 19216, 10528, 19328, 10656, 51);
			}
			break;
		case 87:
			PlayMusic(MUS_disco);
			
			overworld.overlayId = 3;
			
			Overworld_CreateNPC(75, 10000, 20264, 10584, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(10, 44, 20104, 10592, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_RCCLUB_PLOT] <= 110) {
				Overworld_CreateNPC(11, 62, 20464, 10608, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateNPC(11, 62, 20376, 10616, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC_Wandering(12, 63, 19896, 10600, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(13, 64, 19976, 10680, OBJECT_DIRECTION_DOWN);
			break;
		
		case 90:
			if (profile.flags[FLAG_RCCLUB_PLOT] <= 111)
				StopMusic();
			else
				PlayMusic(MUS_blue);
			
			if (profile.flags[FLAG_RCCLUB_PLOT] <= 111) {
				Overworld_CreateTrigger(0, 19968, 11136, 20064, 11184, 35);
				Overworld_CreateNPC(10, 46, 20016, 11024, OBJECT_DIRECTION_UP);
			}
			else {
				Overworld_CreateNPC(10, 46, 20016, 11056, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 91:
			PlayMusic(MUS_hotel);
			
			Overworld_CreateNPC(10, 45, 18440, 11664, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] != 114) {
				Overworld_CreateNPC(11, 47, 18512, 11648, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] == 117) {
				Overworld_CreateObject(70, 1, SPR_owchar_npc_16, 18224, 11768, OBJECT_DIRECTION_RIGHT);
				Overworld_CreateTrigger(0, 17952, 11696, 18304, 11824, 39);
			}
			if (profile.flags[FLAG_PLOT] >= 122) {
				Overworld_CreateNPC(12, 48, 18056, 11656, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 92:
			StopMusic();
			
			overworld.map.doors[68].enabled = profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR] == 0;
			overworld.map.doors[69].enabled = profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR] == 1;
			overworld.map.doors[70].enabled = profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR] == 2;
			
			Overworld_CreateNPC(10, 10030, 18456, 12088, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] == 116) {
				Overworld_CreateObject(70, 1, SPR_owchar_npc_16, 18456, 12120, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 93:
			PlayMusic(MUS_hotel);
			
			overworld.map.doors[71].enabled = profile.flags[FLAG_PLOT] > 114 && profile.flags[FLAG_AZURETOPHOTEL_PLOT] >= 1;
			
			if (profile.flags[FLAG_PLOT] == 114) {
				Overworld_CreateNPC(10, 47, 18184, 11280, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] == 116) {
				Overworld_CreateTrigger(0, 18240, 11264, 18288, 11344, 38);
				Overworld_CreateObject(70, 1, SPR_owchar_npc_16, 18312, 11296, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 94:
			PlayMusic(MUS_hotel);
			break;
		case 95:
			Overworld_CreateNPC(10, 10038, 17760, 11156, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] <= 115) {
				if (profile.flags[FLAG_ALONE])
					Overworld_CreateTrigger(0, 17696, 10992, 17920, 11360, 37);
				else
					Overworld_CreateTrigger(0, 17696, 10992, 17920, 11176, 37);
			}
			if (profile.flags[FLAG_PLOT] >= 117 && profile.flags[FLAG_PLOT] <= 120) {
				Overworld_CreateNPC(11, 65, 17776, 11112, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(12, 66, 17712, 11112, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(13, 67, 17744, 11112, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] == 121) {
				Overworld_CreateNPC(11, 65, 17776, 11112, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(12, 66, 17800, 11272, OBJECT_DIRECTION_UP);
				Overworld_CreateNPC(13, 67, 17744, 11112, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 96:
			Overworld_CreateNPC(10, 10029, 17576, 11716, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 10036, 17536, 11712, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] == 118) {
				Overworld_CreateNPC(11, 48, 17600, 11760, OBJECT_DIRECTION_LEFT);
			}
			if (profile.flags[FLAG_PLOT] >= 122 && profile.flags[FLAG_AZURETOPHOTEL_PLOT] >= 3) {
				Overworld_CreateNPC(11, 68, 17568, 11712, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 97:
			PlayMusic(MUS_city);
			break;
		case 98:
			PlayMusic(MUS_desert);
			
			overworld.map.doors[107].enabled = profile.flags[FLAG_ALONE_PLOT] < 30;
			
			Overworld_CreateNPC(75, 10000, 22280, 13400, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(76, 10000, 24840, 11608, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateEnemy(80, 61, 22584, 12472);
			Overworld_CreateEnemy(81, 62, 24024, 12264);
			Overworld_CreateEnemy(82, 60, 25976, 13432);
			
			if (!profile.flags[FLAG_ITEM_LAPISDESERT_BRIAN_CASE]) {
				Overworld_CreateNPC(10, 69, 26408, 11912, OBJECT_DIRECTION_DOWN);
				OverworldObject_EnableFighterSprite(10, 58, 68, FIGHTER_STATE_SPECIAL1);
			}
			else if (!profile.flags[FLAG_BRIAN_OPTIONALFIGHT]) {
				Overworld_CreateNPC(10, 69, 26376, 11960, OBJECT_DIRECTION_LEFT);
				Overworld_CreateTrigger(0, 26304, 11920, 26352, 12000, 54);
			}
			
			Overworld_CreateNPC(11, 70, 23048, 13416, OBJECT_DIRECTION_DOWN);
			if (!profile.flags[FLAG_OZONE_LADDERFIGHT]) Overworld_CreateNPC(12, 70, 25736, 12640, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(13, 70, 24840, 12840, OBJECT_DIRECTION_UP);
			if (!profile.flags[FLAG_OZONE_GATEFIGHT]) {
				Overworld_CreateNPC(14, 70, 24828, 11352, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(15, 70, 24852, 11352, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_ALONE_PLOT] >= 30) {
				Overworld_CreateNPC(16, 10012, 24840, 11336, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 99:
			if (!profile.flags[FLAG_ITEM_LAPISDESERT_TOMATOSOUP]) {
				Overworld_CreateNPC(50, 10006, 19480, 13592, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 100:
			Overworld_CreateNPC(50, 10043, 18736, 13688, OBJECT_DIRECTION_DOWN);
			overworld.objects[50].vars[7].i = 30;
			if (profile.flags[FLAG_ITEM_LAPISDESERT_BOMB_B]) OverworldObject_ChangeSpriteFrame(50, 1);
			break;
		
		case 103:
			if (profile.flags[FLAG_PLOT] == 134)
				PlayMusic(MUS_lastresort_intro);
			else if (overworld.player.y <= 12432)
				PlayMusic(MUS_outside);
			else
				PlayMusic(MUS_desert);
			
			Overworld_CreateNPC(75, 10000, 12120, 13400, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(76, 10000, 13160, 11704, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateEnemy(80, 42, 13320, 10152);
			Overworld_CreateEnemy(81, 44, 15960, 9960);
			Overworld_CreateEnemy(82, 44, 15312, 12752);
			Overworld_CreateEnemy(83, 43, 14760, 13368);
			Overworld_CreateEnemy(84, 43, 15576, 11336);
			
			if (profile.flags[FLAG_PLOT] <= 130) {
				Overworld_CreateNPC(10, 55, 13904, 10160, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 55, 13952, 10160, OBJECT_DIRECTION_DOWN);
				Overworld_CreateWall(12, 13928, 10152, 112, 16);
			}
			else {
				Overworld_CreateNPC(10, 55, 13888, 10160, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 55, 13968, 10160, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC(13, 55, 13864, 9880, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(14, 55, 13992, 9880, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(15, 55, 11688, 13624, OBJECT_DIRECTION_RIGHT);
			Overworld_CreateNPC_Wandering(16, 99, 15928, 11208, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(17, 98, 14936, 11168, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(18, 55, 14664, 13256, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(19, 55, 15960, 12632, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(20, 12, 14712, 10728, OBJECT_DIRECTION_DOWN);
			
			if (!profile.flags[FLAG_ITEM_LAPISPEAKS_HEAL_B]) {
				Overworld_CreateNPC(50, 10041, 11240, 11544, OBJECT_DIRECTION_DOWN);
			}
			
			if (profile.flags[FLAG_PLOT] == 134) {
				Overworld_CreateTrigger(0, 12336, 11728, 12416, 11856, 58);
			}
			break;
		case 106:
			PlayMusic(MUS_desert);
			
			Overworld_CreateEnemy(80, 44, 5864, 14168);
			break;
		case 107:
			PlayMusic(MUS_desert);
			break;
		case 108:
			PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 76, 17609, 10040, OBJECT_DIRECTION_RIGHT);
			Overworld_CreateNPC(11, 77, 18103, 10008, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC_Wandering(12, 50, 17944, 9736, OBJECT_DIRECTION_UP);
			break;
		case 109:
			Overworld_CreateNPC(10, 78, 19431, 10920, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(11, 79, 19431, 11144, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC_Wandering(12, 49, 18992, 11152, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(13, 51, 19184, 11104, OBJECT_DIRECTION_UP);
			break;
		case 110:
			PlayMusic(MUS_outside);
			
			Overworld_CreateNPC(75, 10000, 8056, 13576, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(10, 55, 7944, 13464, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 55, 8072, 13464, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] <= 131) {
				Overworld_CreateTrigger(0, 7936, 13568, 8080, 13616, 41);
			}
			if (profile.flags[FLAG_PLOT] <= 133) {
				Overworld_CreateTrigger(1, 7936, 12416, 8080, 12544, 43);
				Overworld_CreateNPC(12, 60003, 8008, 12472, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 111:
			PlayMusic(MUS_blue);
			
			Overworld_CreateNPC(75, 10000, 6392, 12712, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] <= 132) {
				Overworld_CreateNPC(10, 56, 6344, 12984, OBJECT_DIRECTION_DOWN);
				Overworld_CreateTrigger(0, 6304, 13024, 6400, 13072, 42);
			}
			else {
				Overworld_CreateNPC(10, 56, 6344, 12840, OBJECT_DIRECTION_DOWN);
			}
			break;
		
		case 114:
			PlayMusic(MUS_ozone);
			break;
		case 115:
			Overworld_CreateNPC(10, 10037, 17559, 12928, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 59, 17560, 12944, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 60, 17528, 12968, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(13, 61, 17592, 12968, OBJECT_DIRECTION_DOWN);
			
			if (!profile.flags[FLAG_LUNA_OPTIONALFIGHT]) {
				Overworld_CreateTrigger(0, 17424, 13232, 17696, 13296, 50);
			}
			break;
		case 116:
			Overworld_CreateNPC(50, 10043, 19560, 13208, OBJECT_DIRECTION_DOWN);
			overworld.objects[50].vars[7].i = 25;
			if (profile.flags[FLAG_ITEM_LAPISDESERT_ENERGYDRINK]) OverworldObject_ChangeSpriteFrame(50, 1);
			break;
		case 117:
			Overworld_CreateNPC(10, 10043, 19104, 13176, OBJECT_DIRECTION_DOWN);
			overworld.objects[10].vars[7].i = 23;
			if (profile.flags[FLAG_ITEM_LAPISDESERT_BRIAN_CASE]) OverworldObject_ChangeSpriteFrame(10, 1);
			break;
		case 118:
			PlayMusic(MUS_desert);
			break;
		case 119:
			StopMusic();
			
			if (!profile.flags[FLAG_LAPISDESERT_SECRETBUNKER_UNLOCKED]) {
				overworld.map.doors[112].enabled = false;
				Overworld_CreateNPC(10, 10045, 18024, 14992, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 120:
			PlayMusic(MUS_lastresort_pitchdown);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			Overworld_CreateNPC(75, 10000, 18304, 14920, OBJECT_DIRECTION_DOWN);
			break;
		case 121:
			PlayMusic(MUS_lastresort_pitchdown);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			break;
		case 122:
			overworld.overlayId = 9;
			
			Overworld_CreateNPC(10, 10043, 19040, 14480, OBJECT_DIRECTION_DOWN);
			overworld.objects[10].vars[7].i = 22;
			if (profile.flags[FLAG_ITEM_SECRETBUNKER_ONYXMEAL]) OverworldObject_ChangeSpriteFrame(10, 1);
			break;
		case 123:
			overworld.overlayId = 9;
			
			if (!profile.flags[FLAG_ITEM_SECRETBUNKER_CARD]) {
				Overworld_CreateNPC(10, 10046, 18760, 14464, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 124:
			PlayMusic(MUS_lastresort_pitchdown);
			
			overworld.overlayId = 8;
			
			Overworld_CreateNPC(75, 10000, 19464, 14680, OBJECT_DIRECTION_DOWN);
			
			if (!profile.flags[FLAG_NEKIN_OPTIONALFIGHT]) {
				Overworld_CreateNPC(10, 10048, 19272, 14784, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(11, 1, SPR_tileset_day, 19248, 14785, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_tileset_day, 19264, 14785, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(13, 1, SPR_tileset_day, 19280, 14785, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(11, 4302);
				OverworldObject_ChangeSpriteFrame(12, 4302);
				OverworldObject_ChangeSpriteFrame(13, 4302);
				overworld.objects[11].z = -81;
				overworld.objects[12].z = -81;
				overworld.objects[13].z = -81;
				
				for (int i = 0; i < 9; i++) {
					Overworld_CreateObject(30 + i, 1, SPR_tileset_day, 19248 + (i % 3) * 16, 14785, OBJECT_DIRECTION_DOWN);
					OverworldObject_ChangeSpriteFrame(30 + i, 0);
					overworld.objects[30 + i].z = -97 - (i / 3) * 16;
				}
			}
			else if (profile.flags[FLAG_ALONE]) {
				PlayMusic(MUS_oh);
				Overworld_CreateObject(70, 1, SPR_owchar_collapse_nekin, 19272, 14784, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(71, 1, SPR_misc_collapseblood, 19272, 14783, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(70, 1);
				OverworldObject_ChangeSpriteFrame(71, 1);
				OverworldObject_SetCollisionSize(70, 14, 8);
			}
			Overworld_CreateNPC(14, 10047, 19304, 14776, OBJECT_DIRECTION_DOWN);
			break;
		case 125:
			if (!profile.flags[FLAG_ITEM_LAPISDESERT_MYSTERYKEY]) {
				Overworld_CreateNPC(10, 10044, 6808, 13928, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 126:
			PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 80, 18976, 11616, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 81, 19144, 11776, OBJECT_DIRECTION_RIGHT);
			Overworld_CreateNPC(12, 82, 19208, 11776, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(13, 1004, 19240, 11680, OBJECT_DIRECTION_RIGHT);
			Overworld_CreateNPC(14, 1005, 19272, 11648, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(15, 1006, 19304, 11680, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(16, 1009, 19272, 11744, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] == 122) {
				Overworld_CreateNPC(17, 83, 19112, 11680, OBJECT_DIRECTION_LEFT);
			}
			else if (profile.flags[FLAG_FUN] % 5 == 1 && profile.flags[FLAG_PLOT] > 122) {
				Overworld_CreateNPC(18, 97, 19080, 11648, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 127:
			PlayMusic(MUS_lastresort_intro);
			
			Overworld_CreateNPC(10, 84, 19088, 12192, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 84, 19120, 12192, OBJECT_DIRECTION_DOWN);
			break;
		
		case 230:
			PlayMusic(MUS_illus);
			
			overworld.overlayId = 4;
			overworld.areaWrap = true;
			
			Overworld_CreateNPC(75, 10000, 2456, 14544, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(10, 10039, 2488, 14544, OBJECT_DIRECTION_DOWN);
			break;
		case 231:
			overworld.map.doors[249].enabled = false;
			if (profile.flags[FLAG_PLOT] >= 134) {
				PlayMusic(MUS_unnamed29);
				
				overworld.overlayId = 12;
				profile.tempFlags[TEMPFLAG_ILLUSION_HYPERHELL] = 1;
				
				for (int i = 11; i < 60; i++) {
					Overworld_CreateNPC_Wandering(i, 70007, Random_IRange(920, 1944), Random_IRange(11272, 12312), OBJECT_DIRECTION_DOWN);
				}
				
				Overworld_CreateNPC(10, 70002, 1416, 11672, OBJECT_DIRECTION_DOWN);
			}
			else if (profile.flags[FLAG_ILLUSION_GATE_DEFEATED]) {
				PlayMusic(MUS_brilliant3slow);
				
				overworld.overlayId = 7;
			}
			else {
				PlayMusic(MUS_singularity);
				
				overworld.overlayId = 6;
			}
			overworld.areaWrap = true;
			
			if (profile.flags[FLAG_PLOT] < 134) Overworld_CreateNPC(10, 70004, 1416, 11672, OBJECT_DIRECTION_DOWN);
			break;
		case 232:
			overworld.map.doors[232].enabled = true;
			
			Overworld_CreateEnemy(80, 67, 304, 15072);
			break;
		case 233:
			PlayMusic(MUS_brilliant1);
			
			overworld.overlayId = 6;
			
			Overworld_CreateObject(10, 1, SPR_misc_illusgate, 2440, 10848, OBJECT_DIRECTION_DOWN);
			Overworld_CreateTrigger(0, 2400, 10848, 2480, 10992, 40);
			break;
		case 234:
			PlayMusic(MUS_illus);
			
			overworld.overlayId = 5;
			break;
		case 235:
			PlayMusic(MUS_illus);
			
			overworld.overlayId = 5;
			
			Overworld_CreateEnemy(80, 65, 2344, 13272);
			Overworld_CreateEnemy(81, 66, 2888, 13352);
			break;
		case 236:
			PlayMusic(MUS_illus);
			
			if (overworld.player.y <= 13320) {
				Overworld_CreateObject(10, 1, SPR_misc_gems, 0, 0, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(10, 0);
				OverworldObject_SetColor(0, 0, 255, 255);
			}
			else {
				Overworld_CreateObject(10, 1, SPR_misc_gems, 0, 0, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(10, 1);
				OverworldObject_SetColor(0, 255, 0, 255);
			}
			
			if ((profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] & 1) == 0) {
				Overworld_CreateNPC(11, 10031, 984, 13816, OBJECT_DIRECTION_DOWN);
			}
			if ((profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] & 2) == 0) {
				Overworld_CreateNPC(12, 10032, 824, 12824, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 237:
			PlayMusic(MUS_illus);
			
			OverworldObject_SetColor(0, 255, 255, 255);
			break;
		case 238:
			PlayMusic(MUS_illus);
			
			overworld.map.doors[232].enabled = false;
			OverworldObject_SetColor(0, 255, 255, 255);
			break;
		case 239:
			PlayMusic(MUS_illus);
			
			overworld.map.doors[235].enabled = (profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] & 4) > 0;
			overworld.overlayId = 4;
			
			Overworld_CreateEnemy(80, 52, 1640, 14296);
			Overworld_CreateEnemy(81, 53, 1960, 13976);
			Overworld_CreateEnemy(82, 54, 2280, 14296);
			
			Overworld_CreateNPC(10, 10033, 1960, 13936, OBJECT_DIRECTION_DOWN);
			break;
		
		case 240:
			PlayMusic(MUS_hellgate);
			
			Overworld_CreateNPC(10, 70001, 280, 9744, OBJECT_DIRECTION_DOWN);
			break;
		case 241:
			PlayMusic(MUS_afterlab);
			break;
		case 242:
			PlayMusic(MUS_s);
			
			Overworld_CreateNPC(10, 70003, 4360, 9312, OBJECT_DIRECTION_DOWN);
			break;
		case 243:
			PlayMusic(MUS_brilliant3slow);
			
			overworld.overlayId = 10;
			break;
		case 244:
			PlayMusic(MUS_brilliant3slow);
			
			overworld.overlayId = 10;
			break;
		case 245:
			PlayMusic(MUS_brilliant4);
			
			overworld.map.doors[248].enabled = profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] == 54321;
			
			if (profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] == 0) profile.tempFlags[TEMPFLAG_ILLUSION_TIME_COLOR] = 0xffffff;
			overworld.overlayId = 11;
			
			for (int i = 0; i < 5; i++) {
				Overworld_CreateNPC(10 + i, 70006, 7000 + i * 32, 10408, OBJECT_DIRECTION_DOWN);
				
				int base = 1;
				for (int j = 0; j < 5; j++) {
					int id = (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / base) % 10;
					if (id == i + 1) {
						OverworldObject_ChangeSpriteId(10 + i, SPR_misc_timelineblock);
						overworld.objects[10 + i].vars[7].i = j + 1;
						break;
					}
					base *= 10;
				}
			}
			
			if (profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] != 54321) {
				Overworld_CreateObject(15, 1, SPR_tileset_day, 7056, 10400, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(15, 4189);
				Overworld_CreateObject(16, 1, SPR_tileset_day, 7056, 10384, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(16, 4125);
			}
			
			if ((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE]) % 10 == 0) {
				Overworld_CreateNPC(17, 70005, 7064, 10504, OBJECT_DIRECTION_DOWN);
				overworld.objects[17].vars[7].i = 0;
			}
			if ((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 10) % 10 == 0) {
				Overworld_CreateNPC(18, 70005, 7920, 10384, OBJECT_DIRECTION_DOWN);
				overworld.objects[18].vars[7].i = 1;
			}
			if ((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 100) % 10 == 0) {
				Overworld_CreateNPC(19, 70005, 6040, 10200, OBJECT_DIRECTION_DOWN);
				overworld.objects[19].vars[7].i = 2;
			}
			Overworld_CreateNPC(20, 70008, 7064, 10488, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(21, 70008, 6040, 10184, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(22, 70002, 7144, 10440, OBJECT_DIRECTION_DOWN);
			break;
		case 246:
			overworld.overlayId = 11;
			
			if ((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 10000) % 10 == 0) {
				Overworld_CreateNPC(10, 70005, 5632, 11816, OBJECT_DIRECTION_DOWN);
				overworld.objects[10].vars[7].i = 4;
			}
			Overworld_CreateNPC(11, 70008, 5632, 11800, OBJECT_DIRECTION_DOWN);
			break;
		case 247:
			overworld.overlayId = 11;
			
			if ((profile.flags[FLAG_ILLUSION_TIME_PUZZLESTATE] / 1000) % 10 == 0) {
				Overworld_CreateNPC(10, 70005, 5368, 11848, OBJECT_DIRECTION_DOWN);
				overworld.objects[10].vars[7].i = 3;
			}
			Overworld_CreateNPC(11, 70008, 5360, 11832, OBJECT_DIRECTION_DOWN);
			break;
		case 248:
			overworld.overlayId = 11;
			break;
		case 249:
			overworld.overlayId = 11;
			
			Overworld_CreateNPC(10, 70008, 5992, 12024, OBJECT_DIRECTION_DOWN);
			break;
		case 250:
			overworld.overlayId = 11;
			overworld.map.doors[249].enabled = profile.flags[FLAG_FUN] >= 990;
			
			Overworld_CreateNPC(10, 70008, 4184, 11720, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_FUN] < 990) {
				profile.tempFlags[TEMPFLAG_ILLUSION_TIME_PUZZLECOMPLETE] = 1;
				Overworld_CreateNPC(11, 70009, 4216, 11704, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_tileset_day, 4208, 11696, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(12, 3935);
				Overworld_CreateObject(13, 1, SPR_tileset_day, 4208, 11680, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(13, 3871);
			}
			break;
	}
}
