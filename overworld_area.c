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
	overworld.backgroundId = 0;
	overworld.cameraClamping = false;
	overworld.areaWrap = false;
	overworld.player.dashEnabled = true;
	Party_UpdateCaterpillar();
	
	overworld.map.doors[0].enabled = profile.flags[FLAG_PLOT] > 1;
	
	switch (id) {
		case 0:
			if (profile.flags[FLAG_PLOT] <= 2 || profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 1006)
				Audio_PlayMusic(MUS_outside);
			else if (overworld.map.tilesetSpriteId == SPR_tileset_day_autumn)
				Audio_PlayMusic(MUS_mysterious);
			else if (overworld.map.tilesetSpriteId == SPR_tileset_day_forest)
				Audio_PlayMusic(MUS_forest);
			else
				Audio_PlayMusic(MUS_field);
			
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 0;
			profile.flags[FLAG_METRO_LOCATION] = 0;
			
			if (profile.flags[FLAG_FUN_RIVERGREEN_MYSTERY_ROOM]) {
				overworld.map.doors[43].x1 = 9952;
				overworld.map.doors[43].y1 = 4480;
				
				if (overworld.player.x >= 10016 && (profile.flags[FLAG_FUN] == 0 || Random(1) < 0.9)) {
					profile.flags[FLAG_FUN] = 0;
					Audio_StopMusic();
					Audio_PlayMusic(MUS_field);
					overworld.map.doors[43].x1 = 10272;
					overworld.map.doors[43].y1 = 4480;
					
					Event_Queue_Party_Leave(1);
					Event_Queue_Party_Leave(2);
					Event_Queue_Party_Leave(3);
					if (profile.flags[FLAG_NOAH_JOINED]) {
						Event_Queue_Party_Join(1);
					}
					if (profile.flags[FLAG_EMMET_JOINED]) {
						Event_Queue_Party_Join(2);
					}
					if (profile.flags[FLAG_SALLY_JOINED]) {
						Event_Queue_Party_Join(3);
					}
					
					profile.flags[FLAG_FUN_RIVERGREEN_MYSTERY_ROOM] = 0;
				}
				else if (overworld.player.x < 10016) {
					profile.flags[FLAG_FUN] = 0;
					profile.party[1] = -1;
					profile.party[2] = -1;
					profile.party[3] = -1;
					profile.party[4] = -1;
					Party_UpdateCaterpillar();
					Audio_StopMusic();
					Audio_PlayMusic(MUS_field);
					Overworld_CreateTrigger(0, 0, 0, 8523, 8924, 121);
				}
			}
			else if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 1006) {
				overworld.map.doors[9].x2 = 2248;
				overworld.map.doors[9].y2 = 1296;
				
				Overworld_CreateNPC(75, 10000, 2304, 784, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateNPC(10, 10069, 2560, 400, OBJECT_DIRECTION_DOWN);
				
				if (profile.flags[FLAG_FOREST_TELESCOPE_USED] == 2 && !profile.flags[FLAG_GREGORY_OPTIONALFIGHT]) {
					Overworld_CreateTrigger(0, 2064, 1104, 2224, 1120, 119);
				}
			}
			else if (overworld.map.tilesetSpriteId == SPR_tileset_day_forest) {
				if (profile.flags[FLAG_FOREST_FORK_PROGRESS] >= 104) {
					overworld.map.doors[10].x2 = 4104;
					overworld.map.doors[10].y2 = 1424;
				}
				else {
					overworld.map.doors[10].x2 = 2600;
					overworld.map.doors[10].y2 = 1552;
				}
				overworld.map.doors[9].x2 = 3032;
				overworld.map.doors[9].y2 = 1536;
				
				Overworld_CreateNPC(75, 10000, 3064, 1424, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(76, 10000, 3056, 864, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateEnemy(80, 6, 3696, 3008);
				Overworld_CreateEnemy(81, 6, 3872, 2848);
				Overworld_CreateEnemy(82, 7, 3120, 2496);
				
				if (profile.flags[FLAG_BASHURA_PLOT] == 0 && profile.flags[FLAG_PLOT] < 14) {
					Overworld_CreateEnemy(83, 27, 4464, 2000);
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
				
				if (!profile.flags[FLAG_ITEM_LEAFCREW_TOMATOSOUP]) {
					Overworld_CreateNPC(50, 10006, 3240, 2200, OBJECT_DIRECTION_DOWN);
				}
				if (!profile.flags[FLAG_ITEM_LEAFCREW_HEAL_B]) {
					Overworld_CreateNPC(51, 10041, 2448, 1120, OBJECT_DIRECTION_DOWN);
				}
			}
			else {
				overworld.map.doors[0].enabled = profile.flags[FLAG_PLOT] < 500;
				
				if (profile.flags[FLAG_PLOT] >= 500) {
					Overworld_CreateNPC(69, 10067, 3280, 5336, OBJECT_DIRECTION_DOWN);
				}
				
				Overworld_CreateTrigger(200, 9280, 5280, 9392, 5296, 107);
				
				Overworld_CreateNPC(75, 10000, 3368, 5344, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(76, 10000, 6440, 3408, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(77, 10000, 7864, 3488, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(78, 10000, 2288, 5120, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(79, 10000, 11136, 4080, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateEnemy(80, 1, 3600, 5456);
				Overworld_CreateEnemy(81, 1, 5296, 5040);
				Overworld_CreateEnemy(82, 3, 5456, 4368);
				Overworld_CreateEnemy(83, 3, 5744, 4528);
				Overworld_CreateEnemy(84, 2, 4112, 4528);
				
				Overworld_CreateEnemy(85, 13, 6672, 4880);
				Overworld_CreateEnemy(86, 12, 6608, 4480);
				
				Overworld_CreateEnemy(87, 12, 9744, 3920);
				
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
				if (profile.flags[FLAG_PURCHASED_BUS_TICKET]) {
					Overworld_CreateTrigger(8, 8288, 4976, 8400, 5152, 25);
				}
				if (!profile.flags[FLAG_BRICKWALL_REMOVED]) {
					Overworld_CreateNPC(30, 10027, 6528, 3840, OBJECT_DIRECTION_DOWN);
					
					if (profile.flags[FLAG_PLOT] >= 11) {
						Overworld_CreateTrigger(9, 6400, 3424, 6576, 3472, 30);
					}
				}
				if (profile.flags[FLAG_PLOT] >= 11 && profile.flags[FLAG_PLOT] <= 13) {
					Overworld_CreateNPC(31, 32, 2008, 5080, OBJECT_DIRECTION_LEFT);
				}
				Overworld_CreateNPC(32, 33, 9384, 3512, OBJECT_DIRECTION_DOWN);
				
				if (profile.flags[FLAG_PLOT] >= 500 && profile.flags[FLAG_PLOT] <= 501) {
					Overworld_CreateTrigger(0, 8544, 5344, 8672, 5392, 109);
				}
				
				if (!profile.flags[FLAG_ITEM_VILLAGE_DANDELION]) {
					Overworld_CreateNPC(50, 10053, 11080, 4040, OBJECT_DIRECTION_DOWN);
				}
				Overworld_CreateNPC(51, 10043, 7520, 3904, OBJECT_DIRECTION_DOWN);
				overworld.objects[51].vars[7].i = 12;
				if (profile.flags[FLAG_ITEM_VILLAGE_GREENTEA]) OverworldObject_ChangeSpriteFrame(51, 1);
			}
			break;
		case 1:
			Audio_StopMusic();
			Overworld_CreateNPC(10, 0, -5712, 2680, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(11, 10003, 752, 2680, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] <= 1) Overworld_CreateNPC(12, 10005, 552, 2656, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] == -1) Overworld_CreateTrigger(0, 64, 2416, 632, 2992, 1);
			break;
		case 2:
			Audio_PlayMusic(MUS_cave);
			break;
		case 3:
			Audio_PlayMusic(MUS_cave);
			
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
			if (profile.flags[FLAG_GREGORY_OPTIONALFIGHT])
				Audio_PlayMusic(MUS_casual);
			else
				Audio_PlayMusic(MUS_secretambience);
			
			if (profile.flags[FLAG_GREGORY_OPTIONALFIGHT]) {
				Overworld_CreateNPC(10, 8, 488, 1296, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(11, 1, SPR_misc_gregoryscythe, 492, 1234, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_misc_gregorygun, 510, 1262, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateNPC(10, 8, 464, 1272, OBJECT_DIRECTION_DOWN);
				if (profile.flags[FLAG_PLOT] <= 14) {
					Overworld_CreateTrigger(0, 496, 1328, 672, 1408, 9);
					Overworld_CreateNPC(11, 60001, 552, 1268, OBJECT_DIRECTION_DOWN);
				}
			}
			break;
		case 6:
			Audio_PlayMusic(MUS_town);
			
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 11;
			profile.flags[FLAG_METRO_LOCATION] = 1;
			Overworld_CreateTrigger(200, 14400, 7472, 14512, 7488, 107);
			
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
				Overworld_CreateTrigger(2, 14208, 6880, 14336, 7024, 21);
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
			if (profile.flags[FLAG_PLOT] >= 74 && profile.flags[FLAG_PLOT] < 500) {
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
			Audio_PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 4, 10232, 8128, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 5, 10512, 8144, OBJECT_DIRECTION_DOWN);
			if (!profile.flags[FLAG_JACKIECAFE_BROKENGLASS]) {
				Overworld_CreateNPC(12, 10034, 10356, 8284, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(13, 57, 10360, 8272, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] <= 52 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateTrigger(0, 9920, 8384, 10544, 8432, 16);
			}
			break;
		
		case 9:
			if (!profile.flags[FLAG_ALONE_PERRY_SPARED] && (profile.flags[FLAG_PLOT] == 57 || profile.flags[FLAG_PLOT] == 58 || profile.flags[FLAG_ALONE_PLOT] >= 2))
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_casual);
			
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
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_casual);
			
			overworld.map.doors[21].enabled = profile.flags[FLAG_PLOT] >= 56;
			if (profile.flags[FLAG_PLOT] < 56) {
				Overworld_CreateNPC(10, 10012, 9512, 8688, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 13:
			if (profile.flags[FLAG_ALONE_PLOT] < 2 || profile.flags[FLAG_ALONE_PERRY_SPARED])
				Audio_PlayMusic(MUS_cave);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			if (profile.flags[FLAG_ALONE_PLOT] > 2) {
				Overworld_CreateNPC(10, 58, 9450, 9160, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(11, 1, SPR_misc_collapseblood, 9450, 9159, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(11, 1);
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
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_mansion);
			
			Overworld_CreateNPC(75, 10000, 8104, 8008, OBJECT_DIRECTION_DOWN);
			break;
		
		case 17:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_mansion);
			
			Overworld_CreateNPC(75, 10000, 7352, 7912, OBJECT_DIRECTION_DOWN);
			
			overworld.map.doors[27].enabled = profile.flags[FLAG_MANSION_UNLOCKED_DIAMOND];
			if (!profile.flags[FLAG_MANSION_UNLOCKED_DIAMOND]) {
				Overworld_CreateNPC(10, 10018, 7400, 7896, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 18:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_mansion);
			
			if (profile.flags[FLAG_PLOT] <= 71) {
				Overworld_CreateTrigger(0, 7312, 7664, 7488, 7680, 12);
				Overworld_CreateNPC(10, 27, 7400, 7576, OBJECT_DIRECTION_UP);
			}
			break;
		case 19:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				Audio_StopMusic();
			else if (profile.flags[FLAG_PLOT] <= 72)
				Audio_PlayMusic(MUS_secretambience);
			else
				Audio_PlayMusic(MUS_mansion);
			
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
			Audio_PlayMusic(MUS_cave);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			break;
		case 22:
			Audio_PlayMusic(MUS_cave);
			
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
			Audio_PlayMusic(MUS_secretambience);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			Overworld_CreateNPC(11, 10022, 8664, 9248, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 10049, 8664, 9208, OBJECT_DIRECTION_DOWN);
			
			if (!profile.flags[FLAG_MANSION_GOTKEY_DIAMOND]) Overworld_CreateNPC(10, 10020, 8664, 9224, OBJECT_DIRECTION_DOWN);
			break;
		case 24:
			if (profile.flags[FLAG_ALONE_PLOT] >= 20)
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_mansion);
			
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
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_mansion);
			
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
			Audio_PlayMusic(MUS_casual);
			
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
			Audio_PlayMusic(MUS_casual);
			break;
		case 32:
			Overworld_CreateNPC(11, 10008, 1184, 2436, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_NOAH_JOINED] == 0) {
				Overworld_CreateNPC(10, 7, 1016, 2520, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 33:
			Audio_PlayMusic(MUS_casual);
			
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
			Audio_PlayMusic(MUS_casual);
			
			if (profile.flags[FLAG_PURCHASED_BUS_TICKET] && profile.flags[FLAG_PLOT] < 500) {
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
			Audio_PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 29, 10328, 8864, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(11, 34, 10048, 9008, OBJECT_DIRECTION_LEFT);
			break;
		case 40:
			Overworld_CreateNPC(10, 30, 10376, 9312, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 31, 10504, 9312, OBJECT_DIRECTION_DOWN);
			break;
		case 41:
			Audio_PlayMusic(MUS_hotel);
			
			Overworld_CreateNPC(10, 93, 10328, 9840, OBJECT_DIRECTION_DOWN);
			break;
		
		case 43:
			Overworld_CreateNPC_Wandering(10, 94, 10424, 10328, OBJECT_DIRECTION_DOWN);
			break;
		
		case 44:
			Audio_PlayMusic(MUS_casual);
			
			Overworld_CreateNPC(10, 85, 10896, 9136, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 86, 10952, 9128, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 87, 11032, 9128, OBJECT_DIRECTION_DOWN);
			break;
		
		case 80:
			Audio_PlayMusic(MUS_city);
			
			overworld.map.doors[56].enabled = profile.flags[FLAG_PLOT] < 122 || profile.flags[FLAG_RCCLUB_PLOT] < 112;
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 5;
			profile.flags[FLAG_METRO_LOCATION] = 2;
			Overworld_CreateTrigger(200, 26864, 6816, 26976, 6832, 107);
			
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
				if (!profile.flags[FLAG_ALONE]) {
					Overworld_CreateTrigger(0, 22984, 4672, 23024, 4768, 36);
					Overworld_CreateObject(70, 1, SPR_owchar_lulu_omega, 23088, 4416, OBJECT_DIRECTION_DOWN);
				}
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
			Audio_PlayMusic(MUS_discoquiet);
			
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
			Audio_PlayMusic(MUS_discoquiet);
			
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
			Audio_PlayMusic(MUS_disco);
			
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
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_blue);
			
			if (profile.flags[FLAG_RCCLUB_PLOT] <= 111) {
				Overworld_CreateTrigger(0, 19968, 11136, 20064, 11184, 35);
				Overworld_CreateNPC(10, 46, 20016, 11024, OBJECT_DIRECTION_UP);
			}
			else {
				Overworld_CreateNPC(10, 46, 20016, 11056, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 91:
			Audio_PlayMusic(MUS_hotel);
			
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
			Audio_StopMusic();
			
			overworld.map.doors[68].enabled = profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR] == 0;
			overworld.map.doors[69].enabled = profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR] == 1;
			overworld.map.doors[70].enabled = profile.flags[FLAG_AZURETOPHOTEL_ELEVATOR_FLOOR] == 2;
			
			Overworld_CreateNPC(10, 10030, 18456, 12088, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_PLOT] == 116) {
				Overworld_CreateObject(70, 1, SPR_owchar_npc_16, 18456, 12120, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 93:
			Audio_PlayMusic(MUS_hotel);
			
			overworld.map.doors[71].enabled = profile.flags[FLAG_PLOT] > 114 && profile.flags[FLAG_AZURETOPHOTEL_PLOT] >= 1;
			
			if (profile.flags[FLAG_PLOT] == 114) {
				Overworld_CreateNPC(10, 47, 18184, 11280, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_PLOT] == 116) {
				Overworld_CreateTrigger(0, 18240, 11264, 18288, 11360, 38);
				Overworld_CreateObject(70, 1, SPR_owchar_npc_16, 18312, 11296, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 94:
			Audio_PlayMusic(MUS_hotel);
			break;
		case 95:
			Overworld_CreateNPC(10, 10038, 17760, 11156, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_PLOT] <= 115) {
				if (profile.flags[FLAG_ALONE])
					Overworld_CreateTrigger(0, 17696, 10992, 17920, 11360, 37);
				else
					Overworld_CreateTrigger(0, 17696, 10992, 17920, 11176, 37);
			}
			if (!profile.flags[FLAG_ALONE]) {
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
			Audio_PlayMusic(MUS_city);
			break;
		case 98:
			Audio_PlayMusic(MUS_desert);
			
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
			if (overworld.player.y <= 12432)
				Audio_PlayMusic(MUS_outside);
			else
				Audio_PlayMusic(MUS_desert);
			
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
				Overworld_CreateObject(70, 1, SPR_owchar_lulu_omega, 11864, 11656, OBJECT_DIRECTION_RIGHT);
				Overworld_CreateTrigger(0, 12336, 11728, 12416, 11856, 110);
			}
			break;
		case 106:
			Audio_PlayMusic(MUS_desert);
			
			Overworld_CreateEnemy(80, 44, 5864, 14168);
			break;
		case 107:
			Audio_PlayMusic(MUS_desert);
			break;
		case 108:
			Audio_PlayMusic(MUS_casual);
			
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
			Audio_PlayMusic(MUS_outside);
			
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
			Audio_PlayMusic(MUS_blue);
			
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
			Audio_PlayMusic(MUS_ozone);
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
			Audio_PlayMusic(MUS_desert);
			break;
		case 119:
			Audio_StopMusic();
			
			if (!profile.flags[FLAG_LAPISDESERT_SECRETBUNKER_UNLOCKED]) {
				overworld.map.doors[112].enabled = false;
				Overworld_CreateNPC(10, 10045, 18024, 14992, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 120:
			Audio_PlayMusic(MUS_lastresort_pitchdown);
			
			overworld.overlayId = 1 + profile.flags[FLAG_FLASHLIGHT];
			overworld.player.dashEnabled = false;
			if (profile.flags[FLAG_FLASHLIGHT]) OverworldObject_ChangeSpriteId(0, SPR_owchar_ruby_flashlight);
			
			Overworld_CreateNPC(75, 10000, 18304, 14920, OBJECT_DIRECTION_DOWN);
			break;
		case 121:
			Audio_PlayMusic(MUS_lastresort_pitchdown);
			
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
			Audio_PlayMusic(MUS_lastresort_pitchdown);
			
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
				Audio_PlayMusic(MUS_oh);
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
			Audio_PlayMusic(MUS_casual);
			
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
			Audio_PlayMusic(MUS_lastresort_intro);
			
			Overworld_CreateNPC(10, 84, 19088, 12192, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 84, 19120, 12192, OBJECT_DIRECTION_DOWN);
			break;
		
		case 150:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_outside);
			else
				Audio_PlayMusic(MUS_megacity);
			
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 16;
			profile.flags[FLAG_METRO_LOCATION] = 3;
			Overworld_CreateTrigger(200, 21840, 3568, 21952, 3584, 107);
			
			if (profile.flags[FLAG_ALONE]) {
				if (profile.flags[FLAG_PLOT] <= 150) {
					Overworld_CreateTrigger(0, 21840, 3488, 21952, 3504, 111);
				}
				
				if (profile.flags[FLAG_SAPPHIREHOTEL_PLOT] == 2 && profile.flags[FLAG_ALONE_PLOT] >= 30) {
					Overworld_CreateTrigger(0, 25840, 3520, 25936, 3552, 112);
					Overworld_CreateObject(70, 1, SPR_owchar_panda, 25976, 3560, OBJECT_DIRECTION_DOWN);
				}
				
				if (profile.flags[FLAG_PLOT] >= 250) {
					Overworld_CreateNPC(50, 10043, 27520, 3560, OBJECT_DIRECTION_DOWN);
					overworld.objects[50].vars[7].i = 176;
					if (profile.flags[FLAG_PLOT] > 250) OverworldObject_ChangeSpriteFrame(50, 1);
				}
				
				if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
					Overworld_CreateNPC(51, 10043, 27360, 3536, OBJECT_DIRECTION_DOWN);
					overworld.objects[51].vars[7].i = 28;
					if (profile.flags[FLAG_ITEM_SAPPHIREPOLIS_ALONE_MEDKIT]) OverworldObject_ChangeSpriteFrame(51, 1);
					
					Overworld_CreateNPC(52, 10043, 27392, 3536, OBJECT_DIRECTION_DOWN);
					overworld.objects[52].vars[7].i = 24;
					if (profile.flags[FLAG_ITEM_SAPPHIREPOLIS_ALONE_HEAL_G]) OverworldObject_ChangeSpriteFrame(52, 1);
					
					Overworld_CreateNPC(53, 10043, 27680, 3536, OBJECT_DIRECTION_DOWN);
					overworld.objects[53].vars[7].i = 28;
					if (profile.flags[FLAG_ITEM_SAPPHIREPOLIS_ALONE_MEDKIT_1]) OverworldObject_ChangeSpriteFrame(53, 1);
				}
			}
			else {
				if (profile.flags[FLAG_PLOT] <= 150) {
					Overworld_CreateTrigger(0, 26048, 1040, 26304, 1152, 59);
				}
				if (profile.flags[FLAG_PLOT] == 152) {
					Overworld_CreateTrigger(0, 26048, 1040, 26304, 1152, 61);
					Overworld_CreateObject(70, 1, SPR_owchar_timon, 26344, 1064, OBJECT_DIRECTION_DOWN);
				}
				if (profile.flags[FLAG_PLOT] == 250) {
					Overworld_CreateTrigger(0, 27328, 3512, 27712, 3600, 84);
					Overworld_CreateObject(70, 1, SPR_owchar_kara, 27520, 3600, OBJECT_DIRECTION_DOWN);
				}
				if (profile.flags[FLAG_PLOT] == 500) {
					Overworld_CreateTrigger(0, 26688, 1056, 26928, 1072, 108);
				}
				
				if (profile.flags[FLAG_SAPPHIREHOTEL_PLOT] == 2) {
					Overworld_CreateTrigger(0, 25840, 3520, 25936, 3552, 69);
					Overworld_CreateObject(70, 1, SPR_misc_sally_neo_sit, 26008, 3550, OBJECT_DIRECTION_DOWN);
				}
			}
			
			if (profile.flags[FLAG_PLOT] <= 151 || profile.flags[FLAG_ALONE_PLOT] >= 50) {
				Overworld_CreateNPC(10, 101, 29856, 2248, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 102, 29888, 2248, OBJECT_DIRECTION_DOWN);
				Overworld_CreateWall(12, 29872, 2232, 64, 16);
			}
			break;
		case 151:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_border);
			
			Overworld_CreateObject(10, 1, SPR_misc_spolis_exit, 26896, 9504, OBJECT_DIRECTION_DOWN);
			if (!profile.flags[FLAG_BRILLIANT_ACCESS_GRANTED]) {
				Overworld_CreateObject(11, 1, SPR_misc_spolis_exitbarrier, 26992, 9608, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(11, 0.25);
				OverworldObject_SetCollisionSize(11, 192, 8);
			}
			
			Overworld_CreateNPC(12, 129, 26992, 9648, OBJECT_DIRECTION_DOWN);
			break;
		case 152:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_shutdownslow);
			else
				Audio_PlayMusic(MUS_amper);
			
			if (profile.flags[FLAG_PLOT] < 200) {
				Overworld_CreateNPC(10, 84, 27792, 9680, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 84, 27824, 9680, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(12, 84, 27856, 9680, OBJECT_DIRECTION_DOWN);
				Overworld_CreateWall(13, 27824, 9680, 96, 16);
			}
			break;
		case 153:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_shutdownslow);
			else
				Audio_PlayMusic(MUS_amper);
			
			overworld.map.doors[124].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 0;
			overworld.map.doors[125].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 1;
			overworld.map.doors[126].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 2;
			overworld.map.doors[127].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 3;
			overworld.map.doors[128].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 4;
			overworld.map.doors[129].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 5;
			overworld.map.doors[186].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 6;
			overworld.map.doors[189].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 7;
			overworld.map.doors[130].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 8;
			overworld.map.doors[131].enabled = profile.flags[FLAG_AMPERCORP_ELEVATOR_FLOOR] == 9;
			
			Overworld_CreateNPC(10, 10054, 27824, 9296, OBJECT_DIRECTION_DOWN);
			break;
		case 154:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_shutdownslow);
			else
				Audio_PlayMusic(MUS_amper);
			
			Overworld_CreateNPC(10, 84, 27792, 9680, OBJECT_DIRECTION_DOWN);
			break;
		case 155:
			Audio_PlayMusic(MUS_amper);
			
			Overworld_CreateObject(10, 102, 0, 28904, 10608, OBJECT_DIRECTION_DOWN);
			OverworldObject_ChangeSpriteId(10, SPR_misc_antiretisheriff);
			OverworldObject_SetCollisionSize(10, 80, 16);
			overworld.objects[10].collisionOffsetY = -8;
			
			if (profile.flags[FLAG_AMPERCORP_PLOT] == 20) {
				Overworld_CreateTrigger(0, 28560, 10592, 28608, 10624, 71);
			}
			break;
		case 156:
			if (overworld.player.x >= 29840 && overworld.player.x <= 29984 && overworld.player.y >= 10416 && overworld.player.y <= 10672) {
				Audio_PlayMusic(MUS_discodoomsday);
				overworld.overlayId = 14;
				
				Overworld_CreateNPC(10, 10062, 29904, 10544, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 112, 29912, 10532, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteId(11, SPR_misc_npc_35_dj);
				OverworldObject_ChangeSpriteFrameSpeed(11, 0.1);
				Overworld_CreateNPC(12, 113, 29880, 10568, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteId(12, SPR_misc_npc_36_floss);
				OverworldObject_ChangeSpriteFrameSpeed(12, 0.25);
				Overworld_CreateNPC(13, 114, 29968, 10576, OBJECT_DIRECTION_LEFT);
				OverworldObject_ChangeSpriteFrameSpeed(13, 0.5);
				Overworld_CreateNPC(14, 115, 29960, 10612, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteId(14, SPR_misc_npc_38_dance);
				OverworldObject_ChangeSpriteFrameSpeed(14, 0.25);
				Overworld_CreateNPC(15, 118, 29864, 10616, OBJECT_DIRECTION_RIGHT);
				Overworld_CreateNPC(16, 10063, 29860, 10544, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(17, 10063, 29964, 10544, OBJECT_DIRECTION_DOWN);
				
				Overworld_CreateObject(18, 1, SPR_misc_discoequalizer, 29856, 10416, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(18, 0.25);
				
				if (profile.flags[FLAG_AMPERCORP_PLOT] < 20) {
					Overworld_CreateTrigger(0, 29888, 10640, 29936, 10672, 70);
				}
				else if (profile.flags[FLAG_AMPERCORP_PLOT] == 21) {
					Overworld_CreateTrigger(0, 29888, 10640, 29936, 10672, 75);
				}
			}
			break;
		case 157:
			if (overworld.player.x >= 30480 && overworld.player.x <= 30624 && overworld.player.y >= 10416 && overworld.player.y <= 10672) {
				Overworld_CreateNPC(10, 117, 30520, 10568, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteId(10, SPR_misc_npc_39_sweep);
				OverworldObject_ChangeSpriteFrameSpeed(10, 0.09);
				Overworld_CreateNPC(11, 10064, 30496, 10568, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 158:
			if (profile.flags[FLAG_AMPERCORP_FLOORS_UNLOCKED] <= 2) {
				Overworld_CreateNPC(10, 10065, 30056, 11096, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 159:
			Audio_PlayMusic(MUS_tech);
			
			Overworld_CreateNPC(10, 119, 28248, 12264, OBJECT_DIRECTION_UP);
			break;
		case 160:
			Audio_PlayMusic(MUS_casualneo);
			
			Overworld_CreateObject(10, 1, SPR_misc_ampbroadcastframe, 29104, 12704, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 120, 29128, 13352, OBJECT_DIRECTION_LEFT);
			
			Overworld_CreateNPC(12, 121, 29080, 12920, OBJECT_DIRECTION_RIGHT);
			Overworld_CreateNPC(13, 122, 29128, 12920, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(14, 123, 29104, 12952, OBJECT_DIRECTION_UP);
			
			if (profile.flags[FLAG_AMPERCORP_PLOT] < 50) {
				Overworld_CreateTrigger(0, 29040, 12800, 29168, 12832, 76);
			}
			break;
		case 161:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_shutdownslow);
			else
				Audio_PlayMusic(MUS_amper2);
			
			overworld.map.doors[148].enabled = true;
			
			if (profile.flags[FLAG_AMPERCORP_PLOT] < 81) {
				overworld.map.doors[148].enabled = false;
				Overworld_CreateNPC(10, 10012, 31040, 12288, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 162:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_shutdownslow);
			else
				Audio_PlayMusic(MUS_amper2);
			
			overworld.map.doors[147].enabled = true;
			
			if (profile.flags[FLAG_AMPERCORP_PLOT] < 80) {
				overworld.map.doors[147].enabled = false;
				Overworld_CreateNPC(10, 10012, 32064, 12680, OBJECT_DIRECTION_DOWN);
				Overworld_CreateTrigger(0, 32016, 12672, 32160, 12752, 79);
			}
			break;
		case 163:
			overworld.map.doors[147].enabled = true;
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_shutdownslow);
			else
				Audio_PlayMusic(MUS_core);
			
			if (profile.flags[FLAG_ALONE_PLOT] < 50) {
				Overworld_CreateNPC(10, 127, 32456, 11784, OBJECT_DIRECTION_DOWN);
			}
			if (profile.flags[FLAG_AMPERCORP_PLOT] < 81 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateTrigger(0, 32528, 12000, 32592, 12048, 81);
			}
			break;
		case 164:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_StopMusic();
			else if (profile.flags[FLAG_ALONE_PLOT] >= 40 && profile.flags[FLAG_PLOT] < 250)
				Audio_PlayMusic(MUS_unnervingslow);
			else if (profile.flags[FLAG_AMPERCORP_PLOT] >= 91 && profile.flags[FLAG_PLOT] < 250)
				Audio_PlayMusic(MUS_perspective);
			else if (profile.flags[FLAG_AMPERCORP_PLOT] != 90)
				Audio_PlayMusic(MUS_unnerving);
			break;
		case 165:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_StopMusic();
			else if (profile.flags[FLAG_AMPERCORP_PLOT] >= 91 && profile.flags[FLAG_PLOT] < 250 && !profile.flags[FLAG_ALONE])
				Audio_PlayMusic(MUS_perspective);
			else
				Audio_PlayMusic(MUS_ominous);
			
			if (profile.flags[FLAG_PLOT] < 250) {
				if (profile.flags[FLAG_ALONE]) {
					Overworld_CreateTrigger(0, 30992, 13104, 31024, 13232, 114);
				}
				else if (profile.flags[FLAG_AMPERCORP_PLOT] < 90) {
					Overworld_CreateTrigger(0, 30992, 13104, 31024, 13232, 82);
				}
				else {
					Overworld_CreateTrigger(0, 30992, 13104, 31024, 13232, 83);
				}
				Overworld_CreateNPC(10, 60004, 31320, 13044, OBJECT_DIRECTION_DOWN);
				
				if (profile.flags[FLAG_ALONE]) {
					Overworld_CreateObject(70, 1, SPR_misc_amp_sit, 31544, 13156, OBJECT_DIRECTION_LEFT);
				}
			}
			else if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
				Overworld_CreateNPC(11, 128, 31096, 13168, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_misc_collapseblood, 31096, 13167, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(12, 1);
			}
			else {
				Overworld_CreateNPC(11, 128, 31544, 13156, OBJECT_DIRECTION_LEFT);
			}
			break;
		case 166:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_outside);
			else if (overworld.player.x >= 2688)
				Audio_PlayMusic(MUS_forest);
			else
				Audio_PlayMusic(MUS_border);
			
			if (profile.flags[FLAG_PLOT] < 252) {
				Overworld_CreateTrigger(0, 2496, 7648, 2528, 7824, 85);
				Overworld_CreateObject(70, 1, SPR_owchar_lulu_cloak, 2624, 7728, OBJECT_DIRECTION_UP);
			}
			break;
		case 167:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_mysteriousalt);
			else
				Audio_PlayMusic(MUS_mysterious);
			
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 16;
			profile.tempFlags[TEMPFLAG_DISABLEBATTLEMUSIC] = 0;
			
			overworld.backgroundId = 1;
			overworld.cameraClamping = true;
			break;
		case 168:
			if (overworld.player.y <= 6416) {
				if (profile.flags[FLAG_ALONE_PLOT] >= 50)
					Audio_PlayMusic(MUS_mountainsalt);
				else
					Audio_PlayMusic(MUS_mountains);
			}
			else {
				if (profile.flags[FLAG_ALONE_PLOT] >= 50)
					Audio_PlayMusic(MUS_mysteriousalt);
				else
					Audio_PlayMusic(MUS_mysterious);
			}
			
			profile.flags[FLAG_DEFAULT_BATTLE_BG] = 17;
			
			if (profile.flags[FLAG_PLOT] < 255) {
				Overworld_CreateTrigger(0, 30384, 5904, 30496, 5928, 86);
				Overworld_CreateObject(70, 1, SPR_misc_gemini, 30440, 5832, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateEnemy(80, 89, 30376, 5416);
			Overworld_CreateEnemy(81, 92, 29528, 5496);
			Overworld_CreateEnemy(82, 90, 28584, 5656);
			Overworld_CreateEnemy(83, 97, 29832, 5048);
			
			Overworld_CreateEnemy(84, 93, 30648, 5064);
			Overworld_CreateEnemy(85, 99, 31896, 4888);
			Overworld_CreateEnemy(86, 96, 31080, 5640);
			
			if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
				profile.tempFlags[TEMPFLAG_DISABLEBATTLEMUSIC] = 1;
			}
			break;
		case 169:
			Audio_StopMusic();
			
			overworld.map.doors[157].enabled = true;
			break;
		case 170:
			if (overworld.map.doors[157].enabled) {
				overworld.map.doors[157].enabled = false;
				overworld.map.doors[158].enabled = true;
			}
			else {
				overworld.map.doors[157].enabled = true;
				overworld.map.doors[158].enabled = false;
			}
			break;
		case 171:
			overworld.map.doors[158].enabled = true;
			
			Overworld_CreateEnemy(80, 95, 29064, 8904);
			break;
		case 172:
			Audio_PlayMusic(MUS_ominous);
			
			profile.tempFlags[TEMPFLAG_DISABLEBATTLEMUSIC] = 0;
			break;
		case 173:
			Audio_PlayMusic(MUS_ominous);
			break;
		case 174:
			if (profile.flags[FLAG_ALONE_PLOT] >= 100)
				Audio_StopMusic();
			else if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_singularity);
			else
				Audio_PlayMusic(MUS_brilliant1);
			
			overworld.backgroundId = 2;
			overworld.overlayId = 13;
			
			if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
				Overworld_CreateNPC(75, 10000, 32384, 15008, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 175:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_shutdownslow);
			else
				Audio_PlayMusic(MUS_amper);
			
			if (profile.flags[FLAG_ALONE_PLOT] < 50) {
				Overworld_CreateNPC(10, 116, 30088, 9536, OBJECT_DIRECTION_DOWN);
			}
			
			if (profile.flags[FLAG_ALONE] && profile.flags[FLAG_AMPERCORP_FLOORS_UNLOCKED] <= 0) {
				Overworld_CreateTrigger(0, 29984, 9696, 30208, 9712, 113);
				Overworld_CreateObject(70, 1, SPR_owchar_kara, 30040, 9608, OBJECT_DIRECTION_LEFT);
			}
			break;
		case 176:
			Audio_PlayMusic(MUS_amper);
			
			Overworld_CreateNPC(10, 10066, 28968, 14464, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 10066, 28808, 14880, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 10066, 28568, 15104, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(13, 10066, 28728, 14464, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(14, 10066, 28808, 14464, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(15, 10066, 29416, 14656, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(16, 10066, 29576, 14464, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(17, 10066, 29496, 14464, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_AMPERCORP_PLOT] < 60) {
				if (profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DEFEATED] == 0) {
					Overworld_CreateNPC(61, 124, 29152, 14008, OBJECT_DIRECTION_DOWN);
				}
				Overworld_CreateNPC(62, 125, 29176, 13856, OBJECT_DIRECTION_RIGHT);
			}
			Overworld_CreateObject(63, 1, SPR_misc_ampbroadcastframe, 29152, 14384, OBJECT_DIRECTION_DOWN);
			Overworld_CreateObject(64, 1, SPR_misc_ampbroadcastframe, 29152, 13712, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateObject(69, 104, 0, 0, 0, OBJECT_DIRECTION_DOWN);
			
			{
				const int cU = 1, cL = 2, cR = 3, cD = 4;
				char cubicles[168] = {
					 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0,
					 0,cL,cU,cU,cL, 0, 0,   0,cU,cU,cU,cL, 0, 0,
					cU,cU,cU,cL,cL, 0,cR,  cL, 0, 0, 0,cL, 0, 0,
					cD, 0,cL, 0,cL,cU,cU,  cU,cU,cU,cU,cU,cU,cL,
					
					cR, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0,cL,
					cR,cD, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0,cL,
					
					 0, 0,cD,cD,cL, 0,cL,  cL, 0,cD,cL,cD,cD,cL,
					 0,cR,cU,cR,cL,cL,cU,  cU,cL, 0,cL, 0, 0, 0,
					cU,cR, 0,cR,cD,cL,cL,   0,cU,cU,cL, 0, 0, 0,
					 0,cR, 0, 0,cL,cU,cL,   0, 0, 0,cL, 0, 0, 0,
					cD,cU,cU,cD,cL, 0,cL,   0, 0, 0,cL, 0, 0, 0,
					 0,cL, 0, 0,cR,cU, 0,   0, 0, 0,cL, 0, 0, 0,
				};
				
				int workerCount = 0;
				for (int i = 0; i < 168; i++) {
					if (cubicles[i] == 0) continue;
					int x = 28568 + i % 7 * 80 + (i % 14 >= 7) * (29256-28568);
					int y = 13904 + i / 14 * 112;
					
					int objectId = 85 + i;
					Overworld_CreateObject(objectId, 1, SPR_misc_amper_cubicle, x, y, OBJECT_DIRECTION_DOWN);
					OverworldObject_ChangeSpriteFrame(objectId, cubicles[i] - 1);
					switch (cubicles[i]) {
						case 1:
							overworld.objects[objectId].w = 80;
							overworld.objects[objectId].h = 34;
							overworld.objects[objectId].y -= 80;
							overworld.objects[objectId].z += 80;
							overworld.objects[objectId].collisionOffsetY = 10;
							break;
						case 2:
							overworld.objects[objectId].w = 16;
							overworld.objects[objectId].h = 96;
							overworld.objects[objectId].y -= 80;
							overworld.objects[objectId].z += 80;
							overworld.objects[objectId].collisionOffsetX = -32;
							overworld.objects[objectId].collisionOffsetY = 72;
							break;
						case 3:
							overworld.objects[objectId].w = 16;
							overworld.objects[objectId].h = 96;
							overworld.objects[objectId].y -= 80;
							overworld.objects[objectId].z += 80;
							overworld.objects[objectId].collisionOffsetX = 32;
							overworld.objects[objectId].collisionOffsetY = 72;
							break;
						case 4:
							overworld.objects[objectId].w = 80;
							overworld.objects[objectId].h = 6;
							overworld.objects[objectId].collisionOffsetY = -8;
							break;
					}
					overworld.objects[objectId].vars[0].i = -1;
					
					if (i == 34) {
						overworld.objects[objectId].x += 64;
						overworld.objects[objectId].y -= 1000;
						continue;
					}
					if (i == 35) {
						overworld.objects[objectId].x -= 64;
						overworld.objects[objectId].y -= 1000;
						continue;
					}
					if (i == 48) {
						overworld.objects[objectId].x += 64;
						continue;
					}
					if (i == 49) {
						overworld.objects[objectId].x -= 64;
						continue;
					}
					
					if (i % 3 < 2 && workerCount < 40 && cubicles[i] != 4 && profile.flags[FLAG_AMPERCORP_PLOT] < 60 && (i < 56 || i >= 70)) {
						if (i > 0)
						if ((cubicles[i] == 2 && cubicles[i - 1] == 3) || (cubicles[i] == 3 && cubicles[i + 1] == 2)) {
							continue;
						}
						int workerId = 20 + workerCount;
						Overworld_CreateObject(workerId, 1, SPR_misc_amper_workers, x, y, OBJECT_DIRECTION_DOWN);
						OverworldObject_ChangeSpriteFrame(workerId, (i % 2) * 4);
						overworld.objects[workerId].vars[0].i = objectId;
						switch (cubicles[i]) {
							case 1:
								overworld.objects[workerId].y -= 54;
								overworld.objects[workerId].w = 16;
								overworld.objects[workerId].h = 4;
								overworld.objects[workerId].collisionOffsetY = -4;
								overworld.objects[workerId].direction = OBJECT_DIRECTION_UP;
								break;
							case 2:
								overworld.objects[workerId].x -= 46;
								overworld.objects[workerId].y -= 46;
								overworld.objects[workerId].w = 16;
								overworld.objects[workerId].h = 4;
								overworld.objects[workerId].collisionOffsetY = -4;
								overworld.objects[workerId].spriteFrame += 2;
								overworld.objects[workerId].direction = OBJECT_DIRECTION_RIGHT;
								break;
							case 3:
								overworld.objects[workerId].x += 46;
								overworld.objects[workerId].y -= 46;
								overworld.objects[workerId].w = 8;
								overworld.objects[workerId].h = 4;
								overworld.objects[workerId].collisionOffsetY = -4;
								overworld.objects[workerId].spriteFrame += 2;
								overworld.objects[workerId].direction = OBJECT_DIRECTION_LEFT;
								break;
						}
						workerCount++;
					}
				}
			}
			break;
		case 177:
			Audio_PlayMusic(MUS_amper3);
			
			for (int i = 0; i < 54; i++) {
				Overworld_CreateObject(100 + i, 1, SPR_misc_amper_theatreseat, 29016 + (i % 18) * 16, 15712 + (i / 18) * 48, OBJECT_DIRECTION_DOWN);
				overworld.objects[100 + i].w = 8;
				overworld.objects[100 + i].h = 1;
				overworld.objects[100 + i].collisionOffsetY = -1;
			}
			
			Overworld_CreateNPC(10, 126, 29240, 16312, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_AMPERCORP_PLOT] < 70) {
				Overworld_CreateTrigger(0, 28976, 15520, 29328, 15568, 78);
				Overworld_CreateNPC(11, 125, overworld.player.x, 15584, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(20, 1, SPR_owchar_kyle, 29112, 15702, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(21, 1, SPR_owchar_dirk, 29144, 15702, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(22, 1, SPR_owchar_tia, 29176, 15702, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(23, 1, SPR_owchar_npc_35, 29144, 15750, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(24, 1, SPR_owchar_npc_36, 29160, 15750, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(25, 1, SPR_owchar_npc_37, 29176, 15750, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(26, 1, SPR_owchar_npc_38, 29192, 15750, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(27, 1, SPR_owchar_camilla, 29240, 15702, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(28, 1, SPR_owchar_reti, 29256, 15798, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(29, 1, SPR_owchar_npc_11, 29288, 15702, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(30, 1, SPR_owchar_npc_12, 29288, 15750, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(31, 1, SPR_owchar_npc_12, 29016, 15798, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(32, 1, SPR_owchar_npc_12, 29032, 15798, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(33, 1, SPR_owchar_agent, 29048, 15798, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(34, 1, SPR_owchar_npc_28, 29064, 15798, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(35, 1, SPR_owchar_agent, 29112, 15798, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(36, 1, SPR_owchar_npc_12, 29080, 15702, OBJECT_DIRECTION_UP);
			}
			break;
		
		case 186:
			if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_StopMusic();
			else
				Audio_PlayMusic(MUS_cozy);
			
			Overworld_CreateNPC(10, 78, 20552, 15040, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 78, 20712, 15040, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(12, 1004, 20568, 15200, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(13, 1005, 20714, 15136, OBJECT_DIRECTION_RIGHT);
			Overworld_CreateNPC(14, 1004, 20774, 15136, OBJECT_DIRECTION_LEFT);
			Overworld_CreateNPC(15, 1005, 20374, 15136, OBJECT_DIRECTION_LEFT);
			
			if (profile.flags[FLAG_PLOT] <= 151 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateTrigger(0, 20608, 15248, 20704, 15282, 60);
			}
			break;
		case 187:
			Overworld_CreateNPC(10, 77, 20727, 15768, OBJECT_DIRECTION_LEFT);
			
			Overworld_CreateNPC(11, 1004, 20440, 15728, OBJECT_DIRECTION_DOWN);
			if (profile.flags[FLAG_WHITELIGHT_PLOT] <= 1 && profile.flags[FLAG_SAPPHIREHOTEL_PLOT] <= 1) {
				Overworld_CreateNPC(12, 102, 20602, 15760, OBJECT_DIRECTION_RIGHT);
			}
			break;
		case 188:
			Audio_PlayMusic(MUS_whitelight);
			
			overworld.map.doors[171].enabled = profile.flags[FLAG_WHITELIGHT_PLOT] >= 1 || profile.flags[FLAG_ALONE];
			break;
		case 189:
			if (!profile.flags[FLAG_ALONE]) {
				if (!profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_DISABLED]) {
					char safeTiles[30] = {
						1, 0, 0, 0, 0,
						1, 0, 1, 1, 1,
						1, 1, 1, 0, 1,
						0, 0, 0, 0, 1,
						1, 1, 1, 1, 1,
						1, 0, 0, 0, 0,
					};
					
					for (int i = 0; i < 30; i++) {
						int x = 19412 + i % 5 * 32;
						int y = 15748 + i / 5 * 32;
						if (safeTiles[i] == 0)
							Overworld_CreateTrigger(i, x, y, x + 40, y + 40, 62);
						
						y = 15476 + i / 5 * 32;
						Overworld_CreateTrigger(30 + i, x, y, x + 40, y + 40, 62);
					}
					
					for (int i = 0; i < 30; i++) {
						int x = 19424 + i % 5 * 32;
						int y = 15488 + i / 5 * 32;
						Overworld_CreateObject(20 + i, 1, SPR_tileset_day, x, y, OBJECT_DIRECTION_DOWN);
						OverworldObject_ChangeSpriteFrame(20 + i, 6241);
					}
				}
				
				Overworld_CreateNPC(10, 10055, 19592, 15696, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 10058, 19560, 15392, OBJECT_DIRECTION_DOWN);
				
				if (profile.flags[FLAG_WHITELIGHT_ELECTROFLOOR_SOLUTION_FOUND] < 2) {
					Overworld_CreateTrigger(60, 19408, 15696, 19600, 15748, 63);
				}
			}
			break;
		case 190:
			Overworld_CreateEnemy(80, 81, 19976, 15920);
			Overworld_CreateEnemy(81, 82, 20096, 15520);
			break;
		case 191:
			if (profile.flags[FLAG_WHITELIGHT_PLOT] < 1 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateNPC(10, 10059, 19800, 15768, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC(11, 10060, 19720, 15784, OBJECT_DIRECTION_DOWN);
			break;
		case 192:
			overworld.map.doors[171].enabled = profile.flags[FLAG_WHITELIGHT_ELEVATOR_FLOOR] == 0;
			overworld.map.doors[172].enabled = profile.flags[FLAG_WHITELIGHT_ELEVATOR_FLOOR] == 1;
			overworld.map.doors[173].enabled = profile.flags[FLAG_WHITELIGHT_ELEVATOR_FLOOR] == 2;
			
			Overworld_CreateNPC(10, 10056, 19768, 16016, OBJECT_DIRECTION_DOWN);
			break;
		case 193:
			Audio_PlayMusic(MUS_whitelight);
			
			overworld.map.doors[172].enabled = true;
			
			if (profile.flags[FLAG_WHITELIGHT_PLOT] <= 1 && profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] >= 4) {
				Overworld_CreateNPC(10, 107, 18864, 16048, OBJECT_DIRECTION_DOWN);
				overworld.map.doors[172].enabled = false;
			}
			break;
		case 194:
			{
				char randomData[] = { 1, 0, 2, 3, 2, -1, 1, 5, 3, 1, 2, 1, 2, -1, 5, 4, 1, -1, 4, 2, 1, 5, 1, 3, -1, 1, 5, 2, 3 };
				
				for (int i = 0; i < 64; i++) {
					int c = randomData[i % sizeof(randomData)];
					if (c < 0) continue;
					int x = 18696 + i % 4 * 32 + i / 8 % 2 * 240;
					int y = 15382 + i / 4 % 2 * 28 + i / 16 * 96;
					Overworld_CreateObject(80 + i, 1, SPR_misc_whitelight_kettlesandstuff, x, y, OBJECT_DIRECTION_DOWN);
					OverworldObject_ChangeSpriteFrame(80 + i, c);
					if (c < 3 && randomData[((i + 3) % (sizeof(randomData) / 2 + 1)) & 1] == 1) {
						OverworldObject_ChangeDirection(80 + i, OBJECT_DIRECTION_LEFT);
					}
				}
				Overworld_CreateObject(144, 1, SPR_misc_whitelight_kettlesandstuff, 19096, 15764, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(144, 0);
				if (profile.flags[FLAG_WHITELIGHT_HIDEANDSEEK_ATTEMPTS] > 0) {
					OverworldObject_ChangeSpriteFrame(89, 0);
				}
				
				for (int i = 0; i < 64; i++) {
					int x = 18696 + i % 4 * 32 + i / 8 % 2 * 240;
					int y = 15386 + i / 4 % 2 * 26 + i / 16 * 96;
					Overworld_CreateNPC(160 + i, 10057, x, y - 1000, OBJECT_DIRECTION_DOWN);
					OverworldObject_ChangeSpriteFrameSpeed(160 + i, 0.06667);
					if (i / 4 % 2 == 0)
						overworld.objects[160 + i].vars[6].i = OBJECT_DIRECTION_UP;
					else
						overworld.objects[160 + i].vars[6].i = OBJECT_DIRECTION_DOWN;
				}
				Overworld_CreateNPC(224, 10057, 19120, 15680 - 1000, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(224, 0.06667);
				overworld.objects[224].vars[6].i = OBJECT_DIRECTION_LEFT;
				
				Overworld_CreateNPC(225, 10057, 19090, 15768 - 1000, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(225, 0.06667);
				overworld.objects[225].vars[6].i = OBJECT_DIRECTION_LEFT;
				
				Overworld_CreateNPC(226, 10057, 18608, 15392 - 1000, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(226, 0.06667);
				overworld.objects[226].vars[6].i = OBJECT_DIRECTION_RIGHT;
				
				Overworld_CreateNPC(227, 10057, 18656, 15328 - 1000, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(227, 0.06667);
				overworld.objects[227].vars[6].i = OBJECT_DIRECTION_DOWN;
				
				Overworld_CreateNPC(228, 10057, 18632, 15312 - 1000, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(228, 0.06667);
				overworld.objects[228].vars[6].i = OBJECT_DIRECTION_DOWN;
				
				Overworld_CreateNPC(229, 10057, 18680, 15312 - 1000, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrameSpeed(229, 0.06667);
				overworld.objects[229].vars[6].i = OBJECT_DIRECTION_DOWN;
			}
			if (profile.flags[FLAG_WHITELIGHT_PLOT] <= 1 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateNPC(10, 103, 18864, 15656, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 195:
			Audio_PlayMusic(MUS_cozy);
			
			overworld.map.doors[173].enabled = true;
			
			if (profile.flags[FLAG_WHITELIGHT_PLOT] == 3 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateTrigger(0, 18064, 16032, 18128, 16128, 67);
			}
			break;
		case 196:
			Audio_PlayMusic(MUS_cozy);
			
			Overworld_CreateNPC(10, 104, 18096, 15568, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(11, 105, 18064, 15568, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC(12, 106, 18000, 15600, OBJECT_DIRECTION_DOWN);
			
			if (profile.flags[FLAG_WHITELIGHT_PLOT] <= 2 && !profile.flags[FLAG_ALONE]) {
				Overworld_CreateTrigger(0, 17984, 15792, 18208, 15840, 65);
				Overworld_CreateObject(70, 1, SPR_owchar_noah, 17944, 15640, OBJECT_DIRECTION_LEFT);
			}
			break;
		case 197:
			Audio_PlayMusic(MUS_casualneo);
			
			overworld.map.doors[179].enabled = true;
			overworld.map.doors[180].enabled = true;
			overworld.map.doors[181].enabled = true;
			overworld.map.doors[182].enabled = profile.flags[FLAG_SAPPHIREHOTEL_ELEVATOR_FLOOR] == 2;
			
			if (profile.flags[FLAG_SAPPHIREHOTEL_MAN_ANNOYED]) {
				Overworld_CreateNPC(10, 109, 16984, 15984, OBJECT_DIRECTION_DOWN);
			}
			else {
				Overworld_CreateNPC(10, 108, 16984, 15984, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC(11, 110, 17096, 15984, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(20, 1004, 16208, 16032, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(21, 1005, 16368, 16032, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(22, 1004, 16528, 16032, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(23, 1005, 16688, 16032, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(24, 1004, 16848, 16032, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(25, 1005, 17048, 16032, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(26, 1004, 17088, 16160, OBJECT_DIRECTION_DOWN);
			Overworld_CreateNPC_Wandering(27, 1005, 16224, 16192, OBJECT_DIRECTION_DOWN);
			break;
		case 198:
			Audio_PlayMusic(MUS_casualneo);
			
			overworld.map.doors[179].enabled = profile.flags[FLAG_SAPPHIREHOTEL_ELEVATOR_FLOOR] == 0;
			overworld.map.doors[180].enabled = profile.flags[FLAG_SAPPHIREHOTEL_ELEVATOR_FLOOR] == 1;
			overworld.map.doors[181].enabled = profile.flags[FLAG_SAPPHIREHOTEL_ELEVATOR_FLOOR] >= 2;
			
			Overworld_CreateNPC(10, 10061, 15960, 16304, OBJECT_DIRECTION_DOWN);
			break;
		case 199:
			Audio_PlayMusic(MUS_hotel);
			
			overworld.map.doors[182].enabled = true;
			
			if (profile.flags[FLAG_ALONE]) {
				Overworld_CreateNPC(10, 10068, 15760, 16120, OBJECT_DIRECTION_DOWN);
			}
			else if (profile.flags[FLAG_SAPPHIREHOTEL_PLOT] == 1) {
				Overworld_CreateTrigger(0, 15696, 16256, 15792, 16320, 68);
			}
			break;
		case 200:
			if (profile.flags[FLAG_ALONE_PLOT] >= 100)
				Audio_StopMusic();
			else if (profile.flags[FLAG_ALONE_PLOT] >= 50)
				Audio_PlayMusic(MUS_singularity);
			else
				Audio_PlayMusic(MUS_brilliant1);
			
			overworld.backgroundId = 2;
			overworld.overlayId = 13;
			
			if (profile.flags[FLAG_ALONE_PLOT] >= 100) {
				Overworld_CreateNPC(10, 133, 30328, 15000, OBJECT_DIRECTION_DOWN);
				Overworld_CreateNPC(11, 134, 30328, 15048, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_misc_collapseblood, 30328, 14999, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(12, 1);
				Overworld_CreateObject(13, 1, SPR_misc_collapseblood, 30328, 15047, OBJECT_DIRECTION_DOWN);
				OverworldObject_ChangeSpriteFrame(13, 1);
			}
			else {
				Overworld_CreateNPC(10, 133, 30280, 14928, OBJECT_DIRECTION_DOWN);
				if (profile.flags[FLAG_ALONE_PLOT] >= 50) {
					Overworld_CreateNPC(11, 134, 30352, 15024, OBJECT_DIRECTION_LEFT);
					Overworld_CreateTrigger(0, 30096, 14960, 30368, 15088, 116);
				}
			}
			break;
		case 201:
			if (profile.flags[FLAG_ALONE_PLOT] >= 110)
				Audio_PlayMusic(MUS_finale_corrupt);
			else if (profile.flags[FLAG_ALONE_PLOT] >= 100)
				Audio_PlayMusic(MUS_something);
			else if (overworld.player.x >= 12768 && profile.flags[FLAG_PLOT] < 300) {
				Audio_PlayMusic(MUS_finale_intro);
				overworld.overlayId = 4;
				
				Overworld_CreateObject(70, 1, SPR_misc_dystal, 13456, 15232, OBJECT_DIRECTION_DOWN);
				Overworld_CreateTrigger(0, 13296, 15104, 13456, 15360, 87);
			}
			else {
				Audio_PlayMusic(MUS_brilliant5);
			}
			
			Overworld_CreateObject(100, 1, SPR_misc_brilliant_crystal1, 10696, 15040, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(100, 255, 0, 255);
			Overworld_CreateObject(101, 1, SPR_misc_brilliant_crystal1, 10648, 15200, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(101, 0, 0, 255);
			Overworld_CreateObject(102, 1, SPR_misc_brilliant_crystal1, 11128, 15472, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(102, 255, 0, 0);
			Overworld_CreateObject(103, 1, SPR_misc_brilliant_crystal1, 11192, 15216, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(103, 0, 255, 255);
			Overworld_CreateObject(104, 1, SPR_misc_brilliant_crystal1, 11928, 15168, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(104, 0, 255, 0);
			Overworld_CreateObject(105, 1, SPR_misc_brilliant_crystal3, 12552, 15040, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(105, 255, 255, 255);
			Overworld_CreateObject(106, 1, SPR_misc_brilliant_crystal3, 12632, 15040, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(106, 255, 255, 255);
			
			Overworld_CreateObject(150, 1, SPR_misc_brilliant_crystal2, 11272, 15392, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(150, 0, 255, 0);
			Overworld_CreateObject(151, 1, SPR_misc_brilliant_crystal2, 11736, 15072, OBJECT_DIRECTION_DOWN); OverworldObject_SetColor(151, 255, 255, 0);
			
			
			
			for (int i = 100; i < 200; i++) {
				if (overworld.objects[i].type == 0) continue;
				
				overworld.objects[i].collisionOffsetY = -8;
				if (overworld.objects[i].spriteId == SPR_misc_brilliant_crystal3) {
					overworld.objects[i].w = 16;
					overworld.objects[i].h = 1;
					continue;
				}
				if (overworld.objects[i].spriteId == SPR_misc_brilliant_crystal2) {
					overworld.objects[i].w = 48;
					overworld.objects[i].h = 32;
					continue;
				}
				overworld.objects[i].w = 32;
				overworld.objects[i].h = 1;
			}
			
			if (profile.flags[FLAG_ALONE_PLOT] >= 110) {
				Overworld_CreateObject(10, 1, SPR_owchar_vincent, 13352, 15224, OBJECT_DIRECTION_LEFT);
				Overworld_CreateObject(11, 1, SPR_owchar_jerry, 13320, 15192, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(12, 1, SPR_owchar_ohio, 13320, 15256, OBJECT_DIRECTION_UP);
				Overworld_CreateObject(13, 1, SPR_owchar_kaiser, 13288, 15224, OBJECT_DIRECTION_RIGHT);
				Overworld_CreateTrigger(0, 13472, 15152, 13536, 15328, 118);
			}
			break;
		case 202:
			if (overworld.player.x < 6368) {
				if (profile.flags[FLAG_ALONE_PLOT] >= 110)
					Audio_PlayMusic(MUS_finale_corrupt);
				else if (profile.flags[FLAG_ALONE_PLOT] >= 100)
					Audio_PlayMusic(MUS_something);
				else
					Audio_PlayMusic(MUS_postclimax);
				
				overworld.overlayId = 15;
				
				if (profile.flags[FLAG_PLOT] < 301) {
					Overworld_CreateObject(70, 1, SPR_owchar_rubin, 4792, 15256, OBJECT_DIRECTION_RIGHT);
					Overworld_CreateTrigger(0, 4752, 15232, 4784, 15312, 88);
					Overworld_CreateTrigger(1, 5040, 14928, 5056, 15024, 90);
					Overworld_CreateTrigger(2, 5152, 15312, 5264, 15328, 91);
					Overworld_CreateTrigger(3, 4512, 15456, 4640, 15472, 92);
					Overworld_CreateTrigger(4, 4240, 15536, 4336, 15552, 93);
					Overworld_CreateTrigger(5, 4720, 15872, 4736, 15968, 94);
					Overworld_CreateTrigger(6, 5184, 15664, 5216, 15760, 95);
					Overworld_CreateTrigger(7, 5184, 15760, 5216, 15856, 96);
					Overworld_CreateTrigger(8, 5184, 15856, 5216, 15952, 97);
					Overworld_CreateTrigger(9, 5424, 15472, 5520, 15488, 98);
					Overworld_CreateTrigger(10, 6240, 15632, 6336, 15728, 99);
				}
				else if (profile.flags[FLAG_PLOT] < 500) {
					Overworld_CreateTrigger(0, 4560, 14880, 4656, 14896, 89);
				}
				
				Overworld_CreateObject(100, 1, SPR_misc_brilliant_crystal3, 6008, 15712, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(101, 1, SPR_misc_brilliant_crystal3, 6040, 15712, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(102, 1, SPR_misc_brilliant_crystal3, 6072, 15712, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(103, 1, SPR_misc_brilliant_crystal3, 6104, 15712, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(104, 1, SPR_misc_brilliant_crystal3, 6136, 15712, OBJECT_DIRECTION_DOWN);
				
				for (int i = 100; i < 200; i++) {
					if (overworld.objects[i].type == 0) continue;
					
					overworld.objects[i].collisionOffsetY = -8;
					if (overworld.objects[i].spriteId == SPR_misc_brilliant_crystal3) {
						overworld.objects[i].w = 16;
						overworld.objects[i].h = 1;
						continue;
					}
					if (overworld.objects[i].spriteId == SPR_misc_brilliant_crystal2) {
						overworld.objects[i].w = 48;
						overworld.objects[i].h = 32;
						continue;
					}
					overworld.objects[i].w = 32;
					overworld.objects[i].h = 1;
				}
			}
			else if (overworld.player.y < 15360) {
				if (profile.flags[FLAG_ALONE_PLOT] >= 110)
					Audio_PlayMusic(MUS_finale_corrupt);
				else if (profile.flags[FLAG_ALONE_PLOT] >= 100)
					Audio_PlayMusic(MUS_something);
				else
					Audio_PlayMusic(MUS_brilliant5);
				
				if (profile.flags[FLAG_PLOT] < 501 && profile.flags[FLAG_ALONE_PLOT] < 110) {
					Overworld_CreateNPC(10, 131, 6704, 15088, OBJECT_DIRECTION_UP);
				}
			}
			else {
				if (profile.flags[FLAG_ALONE_PLOT] >= 110)
					Audio_PlayMusic(MUS_finale_corrupt);
				else if (profile.flags[FLAG_ALONE_PLOT] >= 100)
					Audio_PlayMusic(MUS_something);
				else
					Audio_PlayMusic(MUS_postclimax);
				
				if (profile.flags[FLAG_PLOT] < 500) {
					if (profile.flags[FLAG_ALONE]) {
						Overworld_CreateTrigger(0, 6608, 16064, 6832, 16208, 117);
						Overworld_CreateObject(70, 1, SPR_owchar_lulu_god, 6704, 16072, OBJECT_DIRECTION_DOWN);
					}
					else {
						Overworld_CreateTrigger(0, 6608, 16064, 6800, 16144, 100);
					}
					Overworld_CreateNPC(10, 60000, 6704, 16024, OBJECT_DIRECTION_DOWN);
				}
			}
			break;
		case 203:
			Audio_PlayMusic(MUS_metro);
			
			Overworld_CreateTrigger(200, 22384, 10176, 22496, 10192, 107);
			
			Overworld_CreateNPC(10, 130, 23032, 10352, OBJECT_DIRECTION_DOWN);
			break;
		
		case 230:
			Audio_PlayMusic(MUS_illus);
			
			overworld.overlayId = 4;
			overworld.areaWrap = true;
			
			Overworld_CreateNPC(75, 10000, 2456, 14544, OBJECT_DIRECTION_DOWN);
			
			Overworld_CreateNPC(10, 10039, 2488, 14544, OBJECT_DIRECTION_DOWN);
			break;
		case 231:
			overworld.map.doors[249].enabled = false;
			if (profile.flags[FLAG_PLOT] >= 134) {
				Audio_PlayMusic(MUS_unnamed29);
				
				overworld.overlayId = 12;
				profile.tempFlags[TEMPFLAG_ILLUSION_HYPERHELL] = 1;
				
				for (int i = 11; i < 60; i++) {
					Overworld_CreateNPC_Wandering(i, 70007, Random_IRange(920, 1944), Random_IRange(11272, 12312), OBJECT_DIRECTION_DOWN);
				}
				
				Overworld_CreateNPC(10, 70002, 1416, 11672, OBJECT_DIRECTION_DOWN);
			}
			else if (profile.flags[FLAG_ILLUSION_GATE_DEFEATED]) {
				Audio_PlayMusic(MUS_brilliant3slow);
				
				overworld.overlayId = 7;
			}
			else {
				Audio_PlayMusic(MUS_singularity);
				
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
			Audio_PlayMusic(MUS_brilliant1);
			
			overworld.overlayId = 6;
			
			Overworld_CreateObject(10, 1, SPR_misc_illusgate, 2440, 10848, OBJECT_DIRECTION_DOWN);
			Overworld_CreateTrigger(0, 2400, 10848, 2480, 10992, 40);
			break;
		case 234:
			Audio_PlayMusic(MUS_illus);
			
			overworld.overlayId = 5;
			break;
		case 235:
			Audio_PlayMusic(MUS_illus);
			
			overworld.overlayId = 5;
			
			Overworld_CreateEnemy(80, 65, 2344, 13272);
			Overworld_CreateEnemy(81, 66, 2888, 13352);
			break;
		case 236:
			Audio_PlayMusic(MUS_illus);
			
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
			Audio_PlayMusic(MUS_illus);
			
			OverworldObject_SetColor(0, 255, 255, 255);
			break;
		case 238:
			Audio_PlayMusic(MUS_illus);
			
			overworld.map.doors[232].enabled = false;
			OverworldObject_SetColor(0, 255, 255, 255);
			break;
		case 239:
			Audio_PlayMusic(MUS_illus);
			
			overworld.map.doors[235].enabled = (profile.flags[FLAG_ILLUSION_BOOSTPADPUZZLE_KEYS] & 4) > 0;
			overworld.overlayId = 4;
			
			Overworld_CreateEnemy(80, 52, 1640, 14296);
			Overworld_CreateEnemy(81, 53, 1960, 13976);
			Overworld_CreateEnemy(82, 54, 2280, 14296);
			
			Overworld_CreateNPC(10, 10033, 1960, 13936, OBJECT_DIRECTION_DOWN);
			break;
		
		case 240:
			Audio_PlayMusic(MUS_hellgate);
			
			if (profile.flags[FLAG_PLOT] >= 500) {
				Overworld_CreateNPC(10, 70012, 280, 9712, OBJECT_DIRECTION_DOWN);
				Overworld_CreateObject(70, 1, SPR_owchar_rubin, 280, 9784, OBJECT_DIRECTION_UP);
				Overworld_CreateTrigger(0, 192, 9728, 368, 9840, 103);
			}
			else {
				Overworld_CreateNPC(10, 70001, 280, 9744, OBJECT_DIRECTION_DOWN);
			}
			break;
		case 241:
			Audio_PlayMusic(MUS_afterlab);
			break;
		case 242:
			Audio_PlayMusic(MUS_s);
			
			Overworld_CreateNPC(10, 70003, 4360, 9312, OBJECT_DIRECTION_DOWN);
			break;
		case 243:
			Audio_PlayMusic(MUS_brilliant3slow);
			
			overworld.overlayId = 10;
			break;
		case 244:
			Audio_PlayMusic(MUS_brilliant3slow);
			
			overworld.overlayId = 10;
			break;
		case 245:
			Audio_PlayMusic(MUS_brilliant4);
			
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
		case 251:
			if (profile.flags[FLAG_RUBY_GODMODE])
				Audio_PlayMusic(MUS_tense_r_slow);
			else
				Audio_PlayMusic(MUS_darkunknown);
			
			Overworld_CreateTrigger(0, 240, 10720, 320, 10752, 104);
			break;
		case 252:
			if (profile.flags[FLAG_RUBY_GODMODE])
				Audio_PlayMusic(MUS_brilliant2);
			else
				Audio_PlayMusic(MUS_darkmemory);
			
			overworld.cameraClamping = true;
			
			if (!(profile.flags[FLAG_ILLUSION_MEMORY_GEMS] & 0x1)) {
				Overworld_CreateNPC(10, 70013, 1016, 10552, OBJECT_DIRECTION_DOWN);
			}
			if (!(profile.flags[FLAG_ILLUSION_MEMORY_GEMS] & 0x2)) {
				Overworld_CreateNPC(11, 70014, 1224, 10552, OBJECT_DIRECTION_DOWN);
			}
			if (!(profile.flags[FLAG_ILLUSION_MEMORY_GEMS] & 0x4)) {
				Overworld_CreateNPC(12, 70015, 1120, 10616, OBJECT_DIRECTION_DOWN);
			}
			Overworld_CreateNPC(13, 70017, 1120, 10520, OBJECT_DIRECTION_DOWN);
			break;
		
		case 254:
			if (profile.flags[FLAG_RUBY_GODMODE])
				Audio_PlayMusic(MUS_tense_r_slow);
			else
				Audio_PlayMusic(MUS_darkunknown);
			
			Overworld_CreateTrigger(0, 2512, 11632, 2592, 11680, 105);
			Overworld_CreateTrigger(1, 2512, 11744, 2592, 11760, 106);
			Overworld_CreateObject(10, 1, SPR_misc_helltree_overworld, 2552, 11664, OBJECT_DIRECTION_DOWN);
			break;
	}
}
