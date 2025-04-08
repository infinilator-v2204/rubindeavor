#include <stdlib.h>

#include "generic.h"
#include "console.h"
#include "sprites.h"
#include "party.h"
#include "profile.h"
#include "overworld.h"
#include "battlesystem.h"
#include "audio.h"
#include "event.h"
#include "mapeditor.h"
#include "chess.h"
#include "dialog.h"
#if defined(_WIN32)
	#include <errhandlingapi.h>
	#include <minwinbase.h>
#endif
#if defined(__linux__)
	#include <signal.h>
#endif

#define CONSOLE_ACTION_TOP_ID 186
#define CONSOLE_ARMOR_TOP_ID 81

DevConsole devConsole;

void DevConsole_Init() {
	devConsole.enabled = 0;
	devConsole.stringLength = 0;
	devConsole.stringCursor = 0;
	devConsole.logLength = 0;
	
	for (int i = 0; i < 128; i++) devConsole.string[i] = 0;
	for (int i = 0; i < 4096; i++) devConsole.log[i] = 0;
	
	devConsole.stringLogCount = 0;
	devConsole.stringLogCursor = -1;
}

void DevConsole_Print(const char* text) {
	int c = 0;
	for (int i = devConsole.logLength; i < 4095; i++) {
		devConsole.log[i] = text[c++];
		if (devConsole.log[i] == 0) break;
		devConsole.logLength++;
	}
	
	if (devConsole.logLength >= 3072) {
		for (int i = 0; i < 3072; i++) {
			devConsole.log[i] = devConsole.log[i + 1024];
		}
		devConsole.logLength -= 1024;
	}
}

void DevConsole_ExecuteCommand() {
	int argc = 0;
	char argv[50][80];
	
	int tempLength = 0;
	
	char c = 0;
	for (int i = 0; i < 128; i++) {
		c = devConsole.string[i];
		
		if (c == 0) {
			if (tempLength > 0) {
				argv[argc][tempLength] = 0;
				argc++;
			}
			break;
		}
		if (c == ' ') {
			if (tempLength > 0) {
				argv[argc][tempLength] = 0;
				argc++;
				tempLength = 0;
			}
			if (argc >= 50) break;
			continue;
		}
		
		argv[argc][tempLength++] = c;
	}
	
	if (argc == 0) return;
	
	if (StringsEqual(argv[0], "print")) {
		if (argc == 1) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		for (int i = 1; i < argc; i++) {
			DevConsole_Print(argv[i]);
			if (i < argc - 1) DevConsole_Print(" ");
		}
		DevConsole_Print("\n");
		return;
	}
	
	if (StringsEqual(argv[0], "frameskip")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempValue = strtol(argv[1], NULL, 10);
		game.frameskip = tempValue;
		return;
	}
	
	if (StringsEqual(argv[0], "music")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		if (tempId < 0)
			Audio_StopMusic();
		else
			Audio_PlayMusic(tempId);
		return;
	}
	
	if (StringsEqual(argv[0], "soundfilter")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		if (tempId < 0)
			Audio_RemoveSoundFilter();
		else
			Audio_ApplySoundFilter(tempId);
		return;
	}
	
	if (StringsEqual(argv[0], "encounter")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		EngageBattle(tempId, -1);
		return;
	}
	
	if (StringsEqual(argv[0], "battlevar")) {
		if (argc == 2) {
			int tempId = strtol(argv[1], NULL, 10);
			snprintf(game.textBuffer, 64, "BattleEvent variable %d is %d\n", tempId, battle.battleEventVars[tempId]);
			DevConsole_Print(game.textBuffer);
			return;
		}
		if (argc == 3) {
			int tempId = strtol(argv[1], NULL, 10);
			int tempValue = strtol(argv[2], NULL, 10);
			battle.battleEventVars[tempId] = tempValue;
			snprintf(game.textBuffer, 64, "BattleEvent variable %d set to %d\n", tempId, battle.battleEventVars[tempId]);
			DevConsole_Print(game.textBuffer);
			return;
		}
		
		DevConsole_Print("Invalid usage\n");
		return;
	}
	
	if (StringsEqual(argv[0], "win")) {
		if (game.scene != SCENE_BATTLE) {
			DevConsole_Print("Not in battle\n");
			return;
		}
		
		battle.state = BATTLE_STATE_END;
		battle.timer = 0;
		return;
	}
	
	if (StringsEqual(argv[0], "status")) {
		if (game.scene != SCENE_BATTLE) {
			DevConsole_Print("Not in battle\n");
			return;
		}
		
		if (argc != 4) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		int tempStatus = strtol(argv[2], NULL, 10);
		int tempCount = strtol(argv[3], NULL, 10);
		
		battle.fighters[tempId].status[tempStatus] = tempCount;
		return;
	}
	
	if (StringsEqual(argv[0], "party")) {
		if (argc == 1) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		if (StringsEqual(argv[1], "join")) {
			if (argc != 3) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			Party_Join(tempId);
			return;
		}
		if (StringsEqual(argv[1], "leave")) {
			if (argc != 3) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			Party_Leave(tempId);
			return;
		}
		if (StringsEqual(argv[1], "level")) {
			if (argc != 4) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			int tempValue = strtol(argv[3], NULL, 10);
			Party_SetLevel(tempId, tempValue);
			return;
		}
		if (StringsEqual(argv[1], "exp")) {
			if (argc != 4) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			int tempValue = strtol(argv[3], NULL, 10);
			Party_SetExp(tempId, tempValue);
			return;
		}
		if (StringsEqual(argv[1], "expgain")) {
			if (argc != 4) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			int tempValue = strtol(argv[3], NULL, 10);
			Party_GainExp(tempId, tempValue);
			return;
		}
		if (StringsEqual(argv[1], "orderadd")) {
			if (argc != 3) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			Profile_InventoryPartyOrderAdd(tempId);
			return;
		}
		if (StringsEqual(argv[1], "orderremove")) {
			if (argc != 3) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			Profile_InventoryPartyOrderRemove(tempId);
			return;
		}
		if (StringsEqual(argv[1], "head")) {
			if (argc != 4) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			int tempValue = strtol(argv[3], NULL, 10);
			partyMembers[tempId].headId = tempValue;
			return;
		}
		if (StringsEqual(argv[1], "defaultarmor")) {
			if (argc != 4) {
				DevConsole_Print("Invalid usage\n");
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			int tempValue = strtol(argv[3], NULL, 10);
			partyMembers[tempId].defaultArmorId = tempValue;
			return;
		}
		DevConsole_Print("Unknown party command\n");
		return;
	}
	
	if (StringsEqual(argv[0], "save")) {
		if (game.scene != SCENE_OVERWORLD) {
			DevConsole_Print("Not in overworld\n");
			return;
		}
		/*if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		
		int ret = Profile_SaveGameSlot(tempId);
		if (ret == 1)
			DevConsole_Print("Saved successfully\n");
		else if (ret == -1)
			DevConsole_Print("Failed to save\n");*/
		
		Event_Trigger(1010000);
		
		return;
	}
	if (StringsEqual(argv[0], "load")) {
		if (game.scene != SCENE_OVERWORLD) {
			DevConsole_Print("Not in overworld\n");
			return;
		}
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		
		int ret = Profile_LoadGameSlot(tempId);
		if (ret == 1)
			DevConsole_Print("Loaded successfully\n");
		else if (ret == -1)
			DevConsole_Print("Failed to load\n");
		else if (ret == -2)
			DevConsole_Print("Save file is corrupt\n");
		else if (ret == -3)
			DevConsole_Print("Outdated save file\n");
		
		return;
	}
	
	if (StringsEqual(argv[0], "mapeditor")) {
		ChangeScene(SCENE_MAPEDITOR);
		
		if (argc == 2) {
			snprintf(game.textBuffer, 196, "cp level/%s.bin level/_temp.bin", argv[1]);
			system(game.textBuffer);
			
			snprintf(game.textBuffer, 196, "cp level/%s.bin _levelbackup/%s.bin", argv[1], argv[1]);
			system(game.textBuffer);
			
			MapEditor_LoadMap();
			SetString(mapEditor.levelFileName, argv[1]);
		}
		else {
			MapEditor_LoadMap();
			SetString(mapEditor.levelFileName, "_temp");
		}
		return;
	}
	
	if (StringsEqual(argv[0], "tp")) {
		if (argc != 3) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempX = strtol(argv[1], NULL, 10);
		int tempY = strtol(argv[2], NULL, 10);
		
		overworld.player.x = tempX;
		overworld.player.y = tempY;
		return;
	}
	
	if (StringsEqual(argv[0], "tpr")) {
		if (argc != 3) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempX = strtol(argv[1], NULL, 10);
		int tempY = strtol(argv[2], NULL, 10);
		
		overworld.player.x += tempX;
		overworld.player.y += tempY;
		return;
	}
	
	if (StringsEqual(argv[0], "obtain")) {
		if (argc != 4) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		if (StringsEqual(argv[1], "action")) {
			if (StringsEqual(argv[2], "all")) {
				int tempCount = strtol(argv[3], NULL, 10);
				for (int i = 1; i <= CONSOLE_ACTION_TOP_ID; i++) {
					Profile_AddAction(i, tempCount);
				}
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			int tempCount = strtol(argv[3], NULL, 10);
			Profile_AddAction(tempId, tempCount);
			return;
		}
		if (StringsEqual(argv[1], "armor")) {
			if (StringsEqual(argv[2], "all")) {
				int tempCount = strtol(argv[3], NULL, 10);
				for (int i = 11; i <= CONSOLE_ARMOR_TOP_ID; i++) {
					Profile_AddArmor(i, tempCount);
				}
				return;
			}
			int tempId = strtol(argv[2], NULL, 10);
			int tempCount = strtol(argv[3], NULL, 10);
			Profile_AddArmor(tempId, tempCount);
			return;
		}
		DevConsole_Print("Unknown obtainable type\n");
		return;
	}
	
	if (StringsEqual(argv[0], "gemme")) {
		for (int i = 1; i <= CONSOLE_ACTION_TOP_ID; i++) {
			Profile_AddAction(i, 99);
		}
		for (int i = 11; i <= CONSOLE_ARMOR_TOP_ID; i++) {
			Profile_AddArmor(i, 99);
		}
		return;
	}
	
	if (StringsEqual(argv[0], "item")) {
		if (argc != 3) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		if (StringsEqual(argv[1], "add")) {
			int tempId = strtol(argv[2], NULL, 10);
			Profile_ItemAdd(tempId);
			return;
		}
		if (StringsEqual(argv[1], "keyadd")) {
			int tempId = strtol(argv[2], NULL, 10);
			Profile_KeyItemAdd(tempId);
			return;
		}
		DevConsole_Print("Unknown item command\n");
		return;
	}
	
	if (StringsEqual(argv[0], "shop")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		Overworld_OpenShopMenu(tempId);
		return;
	}
	
	if (StringsEqual(argv[0], "flag")) {
		if (argc == 2) {
			int tempId = strtol(argv[1], NULL, 10);
			snprintf(game.textBuffer, 64, "Flag %d is %d\n", tempId, profile.flags[tempId]);
			DevConsole_Print(game.textBuffer);
			return;
		}
		if (argc == 3) {
			int tempId = strtol(argv[1], NULL, 10);
			int tempValue = strtol(argv[2], NULL, 10);
			profile.flags[tempId] = tempValue;
			snprintf(game.textBuffer, 64, "Flag %d set to %d\n", tempId, profile.flags[tempId]);
			DevConsole_Print(game.textBuffer);
			return;
		}
		
		DevConsole_Print("Invalid usage\n");
		return;
	}
	
	if (StringsEqual(argv[0], "loadarea")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		Overworld_ChangeArea(tempId);
		return;
	}
	
	if (StringsEqual(argv[0], "help")) {
		int tempId;
		if (argc == 1) {
			DevConsole_Print("Error: page number not specified\n");
			return;
		}
		if (argc == 2) {
			DevConsole_Print("Error: command category not specified\n");
			return;
		}
		if (Random(1) < 0.09 * argc) {
			DevConsole_Print("Error: critical error\n");
			return;
		}
		if (!StringsEqual(argv[2], "game") && !StringsEqual(argv[2], "system") && !StringsEqual(argv[2], "misc")) {
			DevConsole_Print("Invalid command category (must be\n'game', 'system' or 'misc')\n");
			return;
		}
		for (int i = 0; i < StringLength(argv[1]); i++) {
			if (argv[1][i] < '0' || argv[1][i] > '9') {
				DevConsole_Print("Invalid page number\n");
				return;
			}
		}
		tempId = strtol(argv[1], NULL, 10);
		if (tempId != 0) {
			DevConsole_Print("Invalid page number\n");
			return;
		}
		if (argc == 3) {
			DevConsole_Print("Required parameter missing\n");
			return;
		}
		if (argc == 4) {
			DevConsole_Print("Error: level not specified\n");
			return;
		}
		tempId = strtol(argv[4], NULL, 10);
		if (tempId != partyMembers[0].level && tempId > 0) {
			DevConsole_Print("Invalid level\n");
			return;
		}
		if (argc == 5) {
			DevConsole_Print("Error: result of 2+2 not specified\n");
			return;
		}
		tempId = strtol(argv[5], NULL, 10);
		if (tempId != 4) {
			DevConsole_Print("Error: you are stOOpid\n");
			return;
		}
		if (argc == 6) {
			DevConsole_Print("Error: your IQ not specified\n");
			return;
		}
		tempId = strtol(argv[6], NULL, 10);
		if (tempId > 1) {
			DevConsole_Print("Failed to verify specified IQ\n");
			return;
		}
		if (argv[4][0] != '[' && argv[4][StringLength(argv[4]) - 1] != ']') {
			DevConsole_Print("Level must be enclosed with\nbrackets\n");
			return;
		}
		if (argc == 7) {
			DevConsole_Print("Commands: help\n");
			return;
		}
		
		DevConsole_Print("Invalid usage\n");
		return;
	}
	
	if (StringsEqual(argv[0], "chess")) {
		if (argc >= 3) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		if (argc == 2) {
			if (game.scene != SCENE_CHESS) {
				DevConsole_Print("Not in chess\n");
				return;
			}
			if (StringsEqual(argv[1], "solve")) {
				chessSystem.puzzleState = 2;
				Audio_PlaySound(SND_chess_mate);
				chessSystem.puzzleCooldown = 120;
				return;
			}
			DevConsole_Print("Invalid usage\n");
			return;
		}
		ChangeScene(SCENE_CHESS);
		return;
	}
	
	if (StringsEqual(argv[0], "dialog")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		Dialog_Run(tempId);
		return;
	}
	
	if (StringsEqual(argv[0], "cash")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempValue = strtol(argv[1], NULL, 10);
		profile.cash += tempValue;
		return;
	}
	
	if (StringsEqual(argv[0], "ending")) {
		if (argc != 2) {
			DevConsole_Print("Invalid usage\n");
			return;
		}
		
		int tempId = strtol(argv[1], NULL, 10);
		ShowEnding(tempId);
		return;
	}
	if (StringsEqual(argv[0], "encounterdata")) {
		int tempValue1 = 0;
		int tempValue2 = 500;
		if (argc == 3) {
			tempValue1 = strtol(argv[1], NULL, 10);
			tempValue2 = strtol(argv[2], NULL, 10);
		}
		for (int i = tempValue1; i < tempValue2; i++) {
			printf("Encounter %d: %d, %d, %d, %d, %d, %d, %d, %d; music %d; bg %d\n", i, battleEncounterData[i].fighterIds[0], battleEncounterData[i].fighterIds[1], battleEncounterData[i].fighterIds[2], battleEncounterData[i].fighterIds[3], battleEncounterData[i].fighterIds[4], battleEncounterData[i].fighterIds[5], battleEncounterData[i].fighterIds[6], battleEncounterData[i].fighterIds[7], battleEncounterData[i].musicId, battleEncounterData[i].backgroundId);
		}
		return;
	}
	
	if (StringsEqual(argv[0], "crash")) {
		#if defined(_WIN32)
		RaiseException(0xDEADDEAD, 0, 0, NULL);
		#endif
		#if defined(__linux__)
		raise(SIGUSR1);
		#endif
		return;
	}
	
	DevConsole_Print("Unknown command\n");
}

void DevConsole_Draw() {
	Drawer_SetProjection(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1);
	
	Drawer_SetDrawColor(0, 0, 0);
	Drawer_SetDrawAlpha(127);
	Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Drawer_SetDrawAlpha(255);
	
	Drawer_SetDrawColor(31, 31, 31);
	Drawer_FillRect(4, SCREEN_HEIGHT - 40, SCREEN_WIDTH - 8, 32);
	Drawer_SetDrawColor(255, 255, 255);
	
	Drawer_FillRect(8 + devConsole.stringCursor*16, SCREEN_HEIGHT - 12, 16, 4);
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_CENTER);
	Drawer_DrawText(devConsole.string, 65536, 8, SCREEN_HEIGHT - 24, 2, 2);
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_BOTTOM);
	Drawer_DrawText(devConsole.log, 65536, 8, SCREEN_HEIGHT - 48, 2, 2);
}
