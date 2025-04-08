#include <stdlib.h>
#include <stddef.h>

#include "generic.h"
#include "overworld.h"
#include "overworld_tiledata.h"
#include "battlesystem.h"
#include "sprites.h"
#include "audio.h"
#include "fighters.h"
#include "battlebody.h"
#include "action.h"
#include "armor.h"
#include "items.h"
#include "passives.h"
#include "dialog.h"
#include "party.h"
#include "profile.h"
#include "console.h"
#include "mapeditor.h"
#include "chess.h"
#include "event.h"

Game game;

int StringLength(const char* string) {
	int length = 0;
	for (int i = 0; i < 65536; i++) {
		if (string[i] == 0) break;
		length++;
	}
	return length;
}

int StringsEqual(const char* s1, const char* s2) {
	for (int i = 0; i < 65536; i++) {
		if (s1[i] != s2[i]) return 0;
		if (s1[i] == 0) break;
	}
	return 1;
}

int StringLineCount(const char* string) {
	int count = 1;
	for (int i = 0; i < 65536; i++) {
		if (string[i] == 0) break;
		if (string[i] == '\n') {
			count++;
		}
	}
	return count;
}

int StringMaxLineWidth(const char* string) {
	int width = 0;
	int maxWidth = 0;
	for (int i = 0; i < 65536; i++) {
		if (string[i] == 0) {
			if (width > maxWidth) {
				maxWidth = width;
			}
			width = 0;
			break;
		}
		if (string[i] == '\n') {
			if (width > maxWidth) {
				maxWidth = width;
			}
			width = 0;
			continue;
		}
		width++;
	}
	return maxWidth;
}

void SetString(char* string, const char* value) {
	for (int i = 0; i < 65536; i++) {
		string[i] = value[i];
		if (value[i] == 0) break;
	}
}

float GetWorldX(float x) { return (x - SCREEN_WIDTH / 2) / drawerSystem.projection_zoom + drawerSystem.projection_x; }
float GetWorldY(float y) { return (y - SCREEN_HEIGHT / 2) / drawerSystem.projection_zoom + drawerSystem.projection_y; }
float GetScreenX(float x) { return (x - drawerSystem.projection_x) * drawerSystem.projection_zoom + SCREEN_WIDTH / 2; }
float GetScreenY(float y) { return (y - drawerSystem.projection_y) * drawerSystem.projection_zoom + SCREEN_HEIGHT / 2; }

float PointDistance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

float PointDirection(float x1, float y1, float x2, float y2) {
	return atan2(y2 - y1, x2 - x1);
}

float Random(float x) {
	return (float)rand() / (float)RAND_MAX * x;
}

float Random_Range(float x1, float x2) {
	return x1 + (float)rand() / (float)RAND_MAX * (x2 - x1);
}

int Random_IRange(int x1, int x2) {
	int x = x1 + (int)((float)rand() / (float)RAND_MAX * (float)(x2 - x1 + 1));
	if (x > x2) x = x2;
	return x;
}

int Max(int x1, int x2) {
	return (x1 > x2) ? x1 : x2;
}

int Min(int x1, int x2) {
	return (x1 < x2) ? x1 : x2;
}



void UpdateFullscreenMode() {
	if (game.settings.fullscreen) {
		if (game.settings.softwareRendering)
			SDL_SetWindowFullscreen(game.internal.window, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(game.internal.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
		SDL_SetWindowFullscreen(game.internal.window, 0);
}



int PlayerButtonPressed(int button) {
	return game.playerKeyPressed[button];
}

int PlayerButtonHeld(int button) {
	return game.playerKeyStates[button];
}



int MouseRectangleHover(float x, float y, float w, float h) {
	return GetWorldX(game.mouseX) >= x && GetWorldY(game.mouseY) >= y && GetWorldX(game.mouseX) <= x + w && GetWorldY(game.mouseY) <= y + h;
}

int MouseCircleHover(float x, float y, float r) {
	return PointDistance(x, y, GetWorldX(game.mouseX), GetWorldY(game.mouseY)) < r;
}

int MouseRectangleHoverFirst(float x, float y, float w, float h) {
	return (GetWorldX(game.mouseX) >= x && GetWorldY(game.mouseY) >= y && GetWorldX(game.mouseX) <= x + w && GetWorldY(game.mouseY) <= y + h) && !(GetWorldX(game.mouseXPrev) >= x && GetWorldY(game.mouseYPrev) >= y && GetWorldX(game.mouseXPrev) <= x + w && GetWorldY(game.mouseYPrev) <= y + h);
}

int MousePressed(int button) {
	return game.mousePressed[button];
}

int MouseHeld(int button) {
	return game.mouseHeld[button];
}

int MouseReleased(int button) {
	return game.mouseReleased[button];
}



void EngageBattle(int id, int enemyObjectId) {
	overworld.lastMusicId = audioSystem.currentMusicId;
	if (!profile.tempFlags[TEMPFLAG_DISABLEBATTLEMUSIC]) {
		Audio_StopMusic();
	}
	battle.encounter = id;
	battle.canFlee = false;
	overworld.transition.id = 2;
	overworld.transition.timer = 0;
	overworld.transition.vars[0] = enemyObjectId;
}

void CreatePopup(const char* message) {
	game.popup.enabled = true;
	SetString(game.popup.message, message);
}

void ShowCinemaCutscene(int id) {
	game.cinema.id = id;
	game.cinema.timer = 0;
	game.cinema.spriteId = -1;
	game.cinema.transitionTimer = 0;
	game.cinema.transitionSpriteId = 0;
	ChangeScene(SCENE_CINEMA);
}

void ShowEnding(int id) {
	game.ending.id = id;
	ChangeScene(SCENE_ENDING);
}



void DrawDialogBox(int x, int y, int w, int h) {
	for (int j = y; j < y + h; j += 8)
	for (int i = x; i < x + w; i += 8) {
		int sub = 4;
		
		if (i >= x + w - 8) i = x + w - 8;
		if (j >= y + h - 8) j = y + h - 8;
		
		if (i == x && j == y)
			sub = 0;
		else if (i == x + w - 8 && j == y)
			sub = 2;
		else if (i == x && j == y + h - 8)
			sub = 6;
		else if (i == x + w - 8 && j == y + h - 8)
			sub = 8;
		else if (i == x)
			sub = 3;
		else if (i == x + w - 8)
			sub = 5;
		else if (j == y)
			sub = 1;
		else if (j == y + h - 8)
			sub = 7;
		
		Drawer_DrawSprite(SPR_gui_dialogbox, i, j, sub, 2, 2);
		if (profile.tempFlags[TEMPFLAG_ILLUSION_HYPERHELL]) {
			Drawer_SetDrawAlpha(255);
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 127 * (game.timer % 32 >= 24), 0);
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, i, j, 0, 0.125, 0.125);
			Drawer_SetDrawAlpha(63);
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			Drawer_SetDrawColor(255, 255 * (game.timer % 32 < 16), 0);
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, i - 1, j, 0, 0.125, 0.125);
			Drawer_SetDrawColor(255, 255 * (game.timer % 32 >= 16), 0);
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, i + 1, j, 0, 0.125, 0.125);
			Drawer_SetDrawAlpha(255);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
			Drawer_SetDrawColor(255, 255, 255);
		}
	}
}

void DrawSaveFile(int id, int x, int y, int variation, bool selected) {
	int w = 576;
	int h = 100;
	
	if (selected)
		Drawer_SetDrawColor(255, 255, 0);
	else
		Drawer_SetDrawColor(127, 127, 127);
	
	DrawDialogBox(x, y, w, h);
	
	if (selected)
		Drawer_SetDrawColor(255, 255, 255);
	else
		Drawer_SetDrawColor(127, 127, 127);
	
	if (variation == 2) {
		Drawer_DrawText("Delete this file?", 32, x + 8, y + 4, 2, 2);
		return;
	}
	
	if (variation == 3) {
		Drawer_DrawText("Game saved", 32, x + 8, y + 4, 2, 2);
	}
	else {
		snprintf(game.textBuffer, 32, "File %d", id + 1);
		Drawer_DrawText(game.textBuffer, 32, x + 8, y + 4, 2, 2);
	}
	
	if (!profile.saveFiles[id].exists) {
		Drawer_DrawText("Empty", 32, x + 8, y + 32, 2, 2);
		return;
	}
	
	if (variation == 0 || variation == 3) {
		for (int i = 0; i < 5; i++) {
			if (profile.saveFiles[id].party[i] < 0) continue;
			
			int spriteId = SPR_head_ruby;
			switch (profile.saveFiles[id].party[i]) {
				case 0: spriteId = SPR_head_ruby; break;
				case 1: spriteId = SPR_head_noah; break;
				case 2: spriteId = SPR_head_emmet; break;
				case 3: spriteId = SPR_head_sally; break;
				
				case 6: spriteId = SPR_head_perry; break;
			}
			
			Drawer_DrawSprite(spriteId, x + 32 + i * 40, y + 72, 0, -2, 2);
		}
	}
	
	snprintf(game.textBuffer, 32, "Level %d", profile.saveFiles[id].level);
	Drawer_DrawText(game.textBuffer, 32, x + w - 152, y + 4, 2, 2);
}

void DrawActionDetailBox(int actionId, int x, int y, int manaCostReduction, bool armorLocked, bool rangeLocked) {
	Action* action = &actionData[actionId];
	
	DrawDialogBox(x, y, 464, 128);
	DrawDialogBox(x + 464, y, 176, 128);
	
	if (actionId == 0) return;
	if (armorLocked) {
		snprintf(game.textBuffer, 128, "Requires %s's armor", armorData[action->armorOnlyId].name);
		Drawer_DrawText(game.textBuffer, 128, x + 8, y + 4, 2, 2);
		return;
	}
	if (rangeLocked) {
		snprintf(game.textBuffer, 128, "Requires armor with a ranged\nweapon");
		Drawer_DrawText(game.textBuffer, 128, x + 8, y + 4, 2, 2);
		return;
	}
	Drawer_DrawText(GetDialogString(action->descriptionDialogId), 128, x + 8, y + 4, 2, 2);
	if (manaCostReduction < 0)
		snprintf(game.textBuffer, 128, "\x90\x02 \x8f\x01%d", Max(0, action->cost - manaCostReduction));
	else if (manaCostReduction > 0)
		snprintf(game.textBuffer, 128, "\x90\x02 \x8f\x02%d", Max(0, action->cost - manaCostReduction));
	else
		snprintf(game.textBuffer, 128, "\x90\x02 %d", action->cost);
	Drawer_DrawText(game.textBuffer, 128, x + 472, y + 4, 2, 2);
	if (action->category == ACTIONCATEGORY_ATTACK) {
		snprintf(game.textBuffer, 128, "\x90\x03 x%g", action->attackMultiplier);
		Drawer_DrawText(game.textBuffer, 128, x + 472, y + 32, 2, 2);
		
		if (action->power[1] < 0) {
			if (action->powerRepeat >= 2)
				snprintf(game.textBuffer, 128, "\x90\x06 %d (x%d)", action->power[0], action->powerRepeat);
			else
				snprintf(game.textBuffer, 128, "\x90\x06 %d", action->power[0]);
		}
		else if (action->power[2] < 0) {
			if (action->powerRepeat >= 2)
				snprintf(game.textBuffer, 128, "\x90\x06 %d+%d (x%d)", action->power[0], action->power[1], action->powerRepeat);
			else
				snprintf(game.textBuffer, 128, "\x90\x06 %d+%d", action->power[0], action->power[1]);
		}
		else if (action->power[3] < 0) {
			if (action->powerRepeat >= 2)
				snprintf(game.textBuffer, 128, "\x90\x06 %d+%d+%d (x%d)", action->power[0], action->power[1], action->power[2], action->powerRepeat);
			else
				snprintf(game.textBuffer, 128, "\x90\x06 %d+%d+%d", action->power[0], action->power[1], action->power[2]);
		}
		else {
			if (action->powerRepeat >= 2)
				snprintf(game.textBuffer, 128, "\x90\x06 %d+%d+%d+%d (x%d)", action->power[0], action->power[1], action->power[2], action->power[3], action->powerRepeat);
			else
				snprintf(game.textBuffer, 128, "\x90\x06 %d+%d+%d+%d", action->power[0], action->power[1], action->power[2], action->power[3]);
		}
		Drawer_DrawText(game.textBuffer, 128, x + 472, y + 60, 2, 2);
	}
}



void Setup() {
	LoadEventData();
	LoadPartyData();
	for (int i = 0; i < 1000; i++) {
		profile.actions[i] = 0;
		profile.actionsEquipped[i] = 0;
		profile.actionsProgress[i] = 0;
		profile.armors[i] = 0;
		profile.armorsEquipped[i] = 0;
		profile.armorsProgress[i] = 0;
		profile.passives[i] = 0;
		profile.passivesEquipped[i] = 0;
		
		profile.flags[i] = 0;
	}
	profile.flags[FLAG_FUN] = Random_IRange(0, 999);
	
	Profile_ClearItemInventory();
	
	Profile_KeyItemAdd(160);
	Profile_KeyItemAdd(173);
	Profile_ItemAdd(3);
	Profile_ItemAdd(6);
	Profile_ItemAdd(6);
	Profile_ItemAdd(6);
	
	for (int i = 0; i < 5; i++) {
		profile.party[i] = -1;
		profile.partyOrder[i] = -1;
	}
	
	profile.cash = 0;
	profile.gp = 0;
	Party_RefreshGemPoints();
	
	Party_Join(0);
	Profile_InventoryPartyOrderAdd(0);
	Party_InventoryUnlock(0);
	
	Profile_AddAction(1, 999);
	
	if (0) {
		Profile_AddAction(2, 999);
		Profile_AddAction(3, 999);
		Profile_AddAction(4, 999);
		
		Profile_AddArmor(11, 999);
		Profile_AddArmor(12, 999);
		Profile_AddArmor(13, 999);
		Profile_AddArmor(14, 999);
		Profile_AddArmor(15, 999);
		Profile_AddArmor(16, 999);
		Profile_AddArmor(17, 999);
		Profile_AddArmor(18, 999);
	}
	
	Profile_EquipAction(0, 1);
	
	Profile_EquipAction(1, 1);
	
	Profile_EquipAction(2, 1);
	
	Profile_EquipAction(3, 1);
	
	Profile_EquipAction(4, 1);
	
	Profile_EquipAction(5, 1);
	
	Profile_EquipAction(6, 1);
	
	Party_SetExp(3, 45);
	
	
	
	overworld.state = OVERWORLD_STATE_IDLE;
	overworld.fadeAlpha = 0;
	
	overworld.player.state = PLAYER_STATE_IDLE;
	overworld.player.timer = 0;
	overworld.player.x = 320;
	overworld.player.y = 240;
	overworld.player.direction = OBJECT_DIRECTION_DOWN;
	overworld.player.xPrev = overworld.player.x;
	overworld.player.yPrev = overworld.player.y;
	
	
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		overworld.objects[i].type = 0;
	}
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		overworld.map.triggers[i].eventId = 0;
	}
	
	Overworld_CreateObject(0, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	Overworld_CreateObject(1, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	Overworld_CreateObject(2, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	Overworld_CreateObject(3, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	Overworld_CreateObject(4, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	Overworld_CreateObject(5, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	Overworld_CreateObject(6, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	Overworld_CreateObject(7, 1, 0, overworld.player.x, overworld.player.y, overworld.player.direction);
	
	for (int i = 0; i < 8; i++) {
		OverworldObject_ChangeSpriteId(i, -1);
	}
	
	Party_UpdateCaterpillar();
	
	overworld.camera.x = overworld.player.x;
	overworld.camera.y = overworld.player.y;
	overworld.camera.zoom = 2;
	
	overworld.map.decorationCount = 0;
	
	Overworld_LoadMap("level/_temp.bin");
	overworld.map.tilesetSpriteId = SPR_tileset_day;
	for (int i = 0; i < 8192; i++) {
		overworld.map.tileData[i] = roTileData[i];
	}
	
	// Village
	Overworld_CreateArea(0, 111, 0, 770, 359);
	Overworld_CreateArea(1, 25, 163, 48, 174);
	// Village - Cave
	Overworld_CreateArea(2, 74, 573, 97, 583);
	Overworld_CreateArea(3, 89, 585, 163, 625);
	Overworld_CreateArea(4, 127, 563, 145, 583);
	// Village - Lisao Home
	Overworld_CreateArea(5, 28, 75, 50, 87);
	
	// Town
	Overworld_CreateArea(6, 771, 155, 1297, 551);
	// Town - Club
	Overworld_CreateArea(7, 620, 499, 658, 527);
	Overworld_CreateArea(8, 632, 480, 658, 496);
	// Town - Perry Home
	Overworld_CreateArea(9, 591, 510, 609, 527);
	Overworld_CreateArea(10, 573, 514, 587, 526);
	Overworld_CreateArea(11, 554, 519, 570, 531);
	Overworld_CreateArea(12, 587, 534, 595, 541);
	Overworld_CreateArea(13, 574, 546, 595, 576);
	// Town - Mansion
	Overworld_CreateArea(14, 494, 496, 512, 506);
	Overworld_CreateArea(15, 498, 477, 508, 489);
	Overworld_CreateArea(16, 498, 454, 508, 465);
	Overworld_CreateArea(17, 448, 490, 464, 501);
	Overworld_CreateArea(18, 457, 466, 467, 481);
	Overworld_CreateArea(19, 457, 446, 473, 458);
	// Town - Mansion - Basement
	Overworld_CreateArea(20, 471, 518, 473, 525);
	Overworld_CreateArea(21, 478, 555, 480, 579);
	Overworld_CreateArea(22, 553, 582, 607, 644);
	Overworld_CreateArea(23, 538, 569, 544, 581);
	Overworld_CreateArea(24, 452, 584, 506, 623);
	// Town - Mansion
	Overworld_CreateArea(25, 532, 479, 542, 489);
	Overworld_CreateArea(26, 471, 489, 487, 505);
	Overworld_CreateArea(27, 516, 496, 533, 505);
	Overworld_CreateArea(28, 492, 511, 517, 538);
	// Village - Shop
	Overworld_CreateArea(29, 12, 46, 60, 71);
	// Village - Ruby's House
	Overworld_CreateArea(30, 25, 181, 48, 196);
	// Village - Noah's House
	Overworld_CreateArea(31, 60, 166, 71, 176);
	Overworld_CreateArea(32, 60, 148, 82, 160);
	// Village - Emmet's House
	Overworld_CreateArea(33, 5, 140, 29, 157);
	Overworld_CreateArea(34, 35, 137, 47, 149);
	Overworld_CreateArea(35, 35, 116, 47, 128);
	// Village - Bus Station
	Overworld_CreateArea(36, 416, 432, 426, 447);
	// Town - Mansion
	Overworld_CreateArea(37, 517, 511, 531, 520);
	Overworld_CreateArea(38, 540, 494, 566, 509);
	// Town - Shop
	Overworld_CreateArea(39, 625, 545, 665, 568);
	Overworld_CreateArea(40, 625, 572, 665, 593);
	// Town - Hotel
	Overworld_CreateArea(41, 637, 608, 651, 622);
	Overworld_CreateArea(42, 629, 626, 660, 634);
	Overworld_CreateArea(43, 629, 639, 660, 649);
	// Town - Hospital
	Overworld_CreateArea(44, 678, 565, 693, 577);
	
	// Lapis City
	Overworld_CreateArea(80, 1363, 270, 1746, 585);
	// Lapis City - Sanji Club
	Overworld_CreateArea(81, 1242, 625, 1250, 643);
	Overworld_CreateArea(82, 1253, 625, 1261, 637);
	Overworld_CreateArea(83, 1243, 609, 1260, 619);
	Overworld_CreateArea(84, 1268, 620, 1292, 648);
	Overworld_CreateArea(85, 1190, 633, 1211, 648);
	Overworld_CreateArea(86, 1194, 655, 1211, 664);
	Overworld_CreateArea(87, 1237, 652, 1313, 673);
	Overworld_CreateArea(88, 1298, 678, 1313, 690);
	Overworld_CreateArea(89, 1276, 686, 1281, 704);
	Overworld_CreateArea(90, 1235, 681, 1266, 698);
	// Lapis City - Hotel
	Overworld_CreateArea(91, 1122, 721, 1163, 743);
	Overworld_CreateArea(92, 1151, 752, 1155, 760);
	Overworld_CreateArea(93, 1134, 699, 1163, 708);
	Overworld_CreateArea(94, 1134, 680, 1163, 689);
	Overworld_CreateArea(95, 1106, 687, 1119, 708);
	Overworld_CreateArea(96, 1092, 723, 1103, 738);
	// Lapis City - Lapis Peaks
	Overworld_CreateArea(97, 1031, 705, 1049, 781);
	Overworld_CreateArea(98, 1338, 669, 1680, 895);
	Overworld_CreateArea(99, 1205, 838, 1243, 868);
	Overworld_CreateArea(100, 1152, 839, 1186, 875);
	Overworld_CreateArea(101, 1147, 795, 1172, 830);
	Overworld_CreateArea(102, 1245, 723, 1250, 757);
	// Lapis City - Ninja Area
	Overworld_CreateArea(103, 641, 589, 1029, 908);
	Overworld_CreateArea(104, 381, 854, 396, 863);
	Overworld_CreateArea(105, 384, 833, 396, 851);
	Overworld_CreateArea(106, 283, 830, 410, 903);
	Overworld_CreateArea(107, 302, 770, 348, 828);
	// Lapis City - Shop
	Overworld_CreateArea(108, 1091, 596, 1140, 644);
	Overworld_CreateArea(109, 1182, 672, 1219, 709);
	// Lapis City - Ninja Area Dojo
	Overworld_CreateArea(110, 466, 732, 534, 936);
	Overworld_CreateArea(111, 362, 789, 430, 816);
	Overworld_CreateArea(112, 365, 766, 381, 782);
	// Lapis City - Lapis Peaks
	Overworld_CreateArea(113, 1252, 723, 1257, 757);
	// Lapis City - Ozone Castle
	Overworld_CreateArea(114, 1089, 768, 1105, 791);
	Overworld_CreateArea(115, 1089, 798, 1105, 830);
	// Lapis City - Lapis Peaks
	Overworld_CreateArea(116, 1221, 821, 1227, 830);
	Overworld_CreateArea(117, 1193, 818, 1215, 830);
	Overworld_CreateArea(118, 1101, 918, 1119, 937);
	Overworld_CreateArea(119, 1125, 891, 1127, 935);
	// Lapis City - Weird Dungeon
	Overworld_CreateArea(120, 1137, 898, 1147, 936);
	Overworld_CreateArea(121, 1152, 911, 1181, 935);
	Overworld_CreateArea(122, 1189, 900, 1199, 908);
	Overworld_CreateArea(123, 1172, 900, 1184, 908);
	Overworld_CreateArea(124, 1196, 913, 1220, 930);
	// Lapis City - Lapis Peaks
	Overworld_CreateArea(125, 421, 863, 429, 871);
	// Lapis City
	Overworld_CreateArea(126, 1181, 719, 1207, 740);
	Overworld_CreateArea(127, 1186, 751, 1201, 766);
	//Overworld_CreateArea(128, , , , );
	//Overworld_CreateArea(129, , , , );
	//Overworld_CreateArea(130, , , , );
	//Overworld_CreateArea(131, , , , );
	//Overworld_CreateArea(132, , , , );
	//Overworld_CreateArea(133, , , , );
	
	// Sapphirepolis
	Overworld_CreateArea(150, 1363, 47, 1932, 249);
	Overworld_CreateArea(151, 1667, 586, 1706, 618);
	// Sapphirepolis - Ampercorp
	Overworld_CreateArea(152, 1726, 594, 1751, 617);
	Overworld_CreateArea(153, 1735, 574, 1742, 589);
	Overworld_CreateArea(154, 1764, 579, 1858, 607);
	Overworld_CreateArea(155, 1766, 635, 1838, 666);
	Overworld_CreateArea(156, 1845, 629, 1883, 665);
	Overworld_CreateArea(157, 1885, 629, 1923, 665);
	Overworld_CreateArea(158, 1770, 679, 1886, 715);
	Overworld_CreateArea(159, 1761, 728, 1869, 771);
	Overworld_CreateArea(160, 1791, 790, 1846, 836);
	Overworld_CreateArea(161, 1896, 718, 1954, 771);
	Overworld_CreateArea(162, 1964, 754, 2008, 795);
	Overworld_CreateArea(163, 2005, 722, 2043, 751);
	Overworld_CreateArea(164, 1898, 792, 1919, 841);
	Overworld_CreateArea(165, 1935, 806, 1976, 830);
	// Brilliant Mountains
	Overworld_CreateArea(166, 33, 376, 406, 546);
	Overworld_CreateArea(167, 357, 554, 396, 568);
	Overworld_CreateArea(168, 1772, 265, 2020, 487);
	Overworld_CreateArea(169, 1837, 470, 1839, 489);
	Overworld_CreateArea(170, 1865, 547, 1869, 559);
	Overworld_CreateArea(171, 1783, 506, 1849, 570);
	Overworld_CreateArea(172, 1894, 526, 2047, 614);
	Overworld_CreateArea(173, 1983, 617, 1985, 744);
	Overworld_CreateArea(174, 1964, 824, 2039, 947);
	// Sapphirepolis - Ampercorp
	Overworld_CreateArea(175, 1874, 585, 1887, 607);
	Overworld_CreateArea(176, 1783, 853, 1860, 945);
	Overworld_CreateArea(177, 1808, 961, 1835, 1021);
	//Overworld_CreateArea(178, , , , );
	// Sapphirepolis - Restaurant
	Overworld_CreateArea(186, 1268, 931, 1299, 955);
	Overworld_CreateArea(187, 1268, 961, 1299, 988);
	// Sapphirepolis - Whitelight
	Overworld_CreateArea(188, 1227, 960, 1242, 971);
	Overworld_CreateArea(189, 1213, 957, 1225, 1000);
	Overworld_CreateArea(190, 1244, 957, 1256, 1000);
	Overworld_CreateArea(191, 1227, 975, 1242, 991);
	Overworld_CreateArea(192, 1233, 998, 1237, 1006);
	Overworld_CreateArea(193, 1172, 996, 1185, 1006);
	Overworld_CreateArea(194, 1162, 950, 1195, 988);
	Overworld_CreateArea(195, 1124, 996, 1137, 1006);
	Overworld_CreateArea(196, 1117, 964, 1144, 988);
	// Sapphirepolis - Hotel
	Overworld_CreateArea(197, 1003, 918, 1092, 1019);
	Overworld_CreateArea(198, 994, 1015, 1000, 1026);
	Overworld_CreateArea(199, 970, 999, 988, 1018);
	// Brilliant Mountains
	Overworld_CreateArea(200, 1868, 910, 1952, 1010);
	Overworld_CreateArea(201, 649, 931, 886, 976);
	Overworld_CreateArea(202, 266, 922, 431, 1026);
	// Metro
	Overworld_CreateArea(203, 1373, 606, 1451, 655);
	//Overworld_CreateArea(204, , , , );
	//Overworld_CreateArea(205, , , , );
	
	// Illusion - Lapis Hotel
	Overworld_CreateArea(230, 149, 896, 159, 915);
	Overworld_CreateArea(231, 56, 703, 122, 770);
	Overworld_CreateArea(232, 0, 922, 193, 943); // GLITCH AREA
	Overworld_CreateArea(233, 150, 678, 154, 792);
	Overworld_CreateArea(234, 171, 777, 177, 788);
	Overworld_CreateArea(235, 109, 800, 195, 845);
	Overworld_CreateArea(236, 40, 785, 72, 871);
	Overworld_CreateArea(237, 151, 874, 188, 893);
	Overworld_CreateArea(238, 21, 880, 87, 896);
	Overworld_CreateArea(239, 100, 861, 144, 911);
	// Illusion - Gateway to Hell
	Overworld_CreateArea(240, 7, 600, 27, 659);
	// Illusion - Sapphireton Island
	Overworld_CreateArea(241, 279, 596, 338, 659);
	Overworld_CreateArea(242, 262, 568, 334, 587);
	// Illusion - Time Waterflows
	Overworld_CreateArea(243, 298, 703, 308, 720);
	Overworld_CreateArea(244, 315, 677, 354, 721);
	Overworld_CreateArea(245, 357, 626, 507, 728);
	Overworld_CreateArea(246, 349, 728, 354, 743);
	Overworld_CreateArea(247, 334, 735, 342, 744);
	Overworld_CreateArea(248, 360, 735, 379, 742);
	Overworld_CreateArea(249, 369, 746, 379, 753);
	Overworld_CreateArea(250, 240, 726, 265, 737);
	// Illusion - Memory Hell
	Overworld_CreateArea(251, 11, 662, 23, 743);
	Overworld_CreateArea(252, 60, 649, 79, 663);
	Overworld_CreateArea(253, 87, 643, 110, 694);
	Overworld_CreateArea(254, 157, 716, 161, 791);
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		overworld.map.doors[i].enabled = false;
	}
	
	
	
	// Village
	Overworld_CreateDoor(0, 544, 2656, 1, 3272, 5328, 0, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(1, 6480, 3376, 0, 1232, 9344, 2, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	Overworld_CreateDoor(2, 1480, 9296, 2, 1480, 9392, 3, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(3, 2064, 9808, 3, 2064, 9344, 4, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(4, 2264, 9728, 3, 2272, 9248, 4, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(5, 2064, 9600, 3, 2064, 9120, 4, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	Overworld_CreateDoor(6, 7248, 3360, 0, 2576, 9696, 3, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village - Forest
	Overworld_CreateDoor(7, 3704, 4128, 0, 3768, 3936, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(8, 3032, 2048, 0, 3032, 1920, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(9, 3032, 1696, 0, 3032, 1536, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(10, 2936, 1696, 0, 2600, 1552, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(11, 3128, 1696, 0, 3528, 1872, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(12, 3048, 688, 0, 3048, 592, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(13, 3056, 400, 0, 600, 1408, 5, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	Overworld_CreateDoor(14, 17048, 8368, 6, 10160, 8448, 7, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(15, 10480, 8096, 7, 10480, 7952, 8, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(16, 10288, 8064, 7, 10288, 7920, 8, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	Overworld_CreateDoor(17, 16384, 7664, 6, 9600, 8448, 9, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(18, 9440, 8384, 9, 9408, 8384, 10, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	Overworld_CreateDoor(19, 9760, 8240, 9, 8848, 8384, 11, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(20, 9680, 8320, 9, 9408, 8672, 12, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(21, 9504, 8784, 13, 9504, 8672, 12, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	Overworld_CreateDoor(22, 14600, 4656, 6, 14600, 4464, 6, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(23, 15568, 3536, 6, 8048, 8112, 14, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(24, 8048, 7984, 14, 8048, 7840, 15, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(25, 7984, 7648, 15, 7984, 7424, 16, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(26, 8048, 7392, 16, 7184, 7968, 17, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(27, 7392, 7888, 17, 7392, 7712, 18, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(28, 7392, 7504, 18, 7392, 7344, 19, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(29, 8048, 7728, 15, 7552, 8416, 20, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(30, 7552, 8336, 20, 7664, 9984, 24, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(31, 7664, 8928, 21, 8928, 10320, 22, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(32, 8928, 9360, 22, 8656, 9312, 23, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(33, 9664, 9808, 22, 9664, 9648, 22, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(34, 7664, 9392, 24, 7664, 9280, 21, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Town - Mansion
	Overworld_CreateDoor(35, 8144, 7984, 14, 8528, 7840, 25, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(36, 7952, 7984, 14, 7776, 8096, 26, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(37, 8112, 7456, 16, 8496, 7968, 27, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(38, 8368, 7984, 27, 8256, 8624, 28, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village - Shop
	Overworld_CreateDoor(39, 8824, 3568, 0, 576, 1152, 29, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village - Ruby's House
	Overworld_CreateDoor(40, 432, 2800, 1, 432, 2944, 30, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	
	// Village - Forest
	Overworld_CreateDoor(41, 2600, 1328, 0, 2600, 1200, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village - Secret Passage
	Overworld_CreateDoor(42, 10288, 4032, 0, 10216, 4272, 0, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(43, 10272, 4480, 0, 10432, 4528, 0, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	
	// Village - Noah's House
	Overworld_CreateDoor(44, 5024, 5280, 0, 1056, 2832, 31, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(45, 1008, 2704, 31, 1008, 2576, 32, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village - Emmet's House
	Overworld_CreateDoor(46, 5888, 5120, 0, 240, 2528, 33, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(47, 272, 2416, 33, 704, 2400, 34, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(48, 272, 2288, 33, 704, 2064, 35, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village - Bus Station
	Overworld_CreateDoor(49, 8464, 5184, 0, 6752, 7168, 36, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(50, 6640, 7032, 36, 8384, 5064, 0, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	
	// Town - Mansion
	Overworld_CreateDoor(51, 8240, 8072, 27, 8512, 8312, 37, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	Overworld_CreateDoor(52, 8544, 8072, 27, 8624, 8136, 38, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	
	// Town - Shop
	Overworld_CreateDoor(53, 17208, 6512, 6, 10320, 9104, 39, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(54, 10040, 8704, 39, 10040, 9312, 40, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village - Left End
	Overworld_CreateDoor(55, 2232, 4592, 0, 2232, 4784, 0, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	
	// Lapis City - Sanji Club
	Overworld_CreateDoor(56, 22712, 4544, 80, 19912, 10304, 81, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(57, 19960, 10192, 81, 20136, 10192, 82, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(58, 20096, 10048, 82, 20096, 9920, 83, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(59, 20192, 10144, 82, 20272, 10144, 84, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(60, 20688, 10336, 84, 19024, 10336, 85, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(61, 19360, 10304, 85, 19360, 10512, 86, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(62, 20352, 9968, 84, 19952, 10784, 87, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(63, 20976, 10528, 87, 20976, 11056, 88, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(64, 20456, 10576, 87, 20456, 11280, 89, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(65, 20456, 11040, 89, 20008, 11184, 90, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Lapis City - Hotel
	Overworld_CreateDoor(66, 24936, 4832, 80, 18392, 11904, 91, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(67, 25016, 4832, 80, 18472, 11904, 91, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(68, 18552, 11600, 91, 18448, 12176, 92, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(69, 18552, 11232, 93, 18448, 12176, 92, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(70, 18552, 10928, 94, 18448, 12176, 92, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(71, 18176, 11248, 93, 17728, 11344, 95, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(72, 18128, 11616, 91, 17552, 11824, 96, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Lapis City - Lapis Peaks
	Overworld_CreateDoor(73, 27040, 4768, 80, 16560, 12512, 97, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(74, 27200, 4768, 80, 16720, 12512, 97, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(75, 16560, 11376, 97, 22448, 14016, 98, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(76, 16720, 11376, 97, 22608, 14016, 98, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(77, 22208, 13328, 98, 19440, 13904, 99, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(78, 22592, 13232, 98, 19824, 13808, 99, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(79, 22064, 13088, 98, 19296, 13664, 99, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(80, 21952, 13472, 98, 18912, 14016, 100, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(81, 18992, 13728, 100, 22016, 13184, 98, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(82, 18456, 13424, 100, 18456, 13296, 101, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(83, 21968, 12464, 98, 18736, 12848, 101, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(84, 21760, 13648, 98, 19600, 13296, 116, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(85, 22864, 10960, 98, 19952, 12128, 102, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(86, 19952, 11616, 102, 12112, 14320, 103, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(87, 12112, 13312, 103, 6160, 13824, 104, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(88, 12112, 13168, 103, 6160, 13632, 105, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(89, 11616, 13232, 103, 5648, 13664, 106, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(90, 11360, 13072, 103, 5280, 14224, 106, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(91, 6304, 13664, 104, 6304, 13536, 105, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(92, 5648, 13328, 106, 5520, 14000, 106, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(93, 5152, 13392, 106, 4960, 13264, 107, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(94, 4768, 13328, 106, 10720, 12256, 103, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(95, 11456, 11648, 103, 5552, 12672, 107, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Lapis City - Shop
	Overworld_CreateDoor(96, 25544, 5776, 80, 17848, 10320, 108, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(97, 17848, 9792, 108, 19160, 10944, 109, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Town - Hotel
	Overworld_CreateDoor(98, 16128, 8368, 6, 10320, 9968, 41, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(99, 10400, 9728, 41, 10400, 10048, 42, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(100, 10288, 10016, 42, 10288, 10400, 43, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Lapis City - Ninja Area
	Overworld_CreateDoor(101, 13920, 9552, 103, 8000, 14800, 110, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(102, 8000, 13536, 110, 6336, 13072, 111, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(103, 6144, 12976, 111, 6048, 12528, 112, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(104, 6336, 12688, 111, 8000, 13040, 110, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Lapis City - Lapis Peaks
	Overworld_CreateDoor(105, 23920, 10944, 98, 20064, 12128, 113, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(106, 20048, 11616, 113, 12720, 14288, 103, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(107, 24832, 11328, 98, 17552, 12672, 114, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(108, 17552, 12384, 114, 17552, 13296, 115, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(109, 26304, 11952, 98, 19456, 13216, 117, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	Overworld_CreateDoor(110, 26672, 11408, 98, 17632, 15008, 118, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Lapis City - Weird Dungeon
	Overworld_CreateDoor(111, 17888, 14720, 118, 18016, 14288, 119, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(112, 18016, 14976, 119, 18208, 14416, 120, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(113, 18368, 14944, 120, 18416, 14944, 121, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(114, 18800, 14912, 121, 19112, 14544, 122, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(115, 18800, 14624, 121, 18872, 14544, 123, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(116, 18416, 14656, 121, 19536, 14688, 124, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	
	// Lapis City - Lapis Peaks
	Overworld_CreateDoor(117, 12464, 13776, 103, 6800, 13856, 125, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(118, 12608, 13520, 103, 12608, 13584, 103, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	
	// Lapis City
	Overworld_CreateDoor(119, 23880, 5856, 80, 18920, 11856, 126, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(120, 26136, 4928, 80, 19096, 12272, 127, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Town - Hospital
	Overworld_CreateDoor(121, 17752, 8352, 6, 10904, 9248, 44, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Sapphirepolis
	Overworld_CreateDoor(122, 26800, 976, 150, 26984, 9904, 151, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(123, 27512, 3504, 150, 27816, 9888, 152, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Sapphirepolis - Ampercorp
	Overworld_CreateDoor(124, 27816, 9616, 152, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(125, 28824, 9472, 154, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(126, 28824, 10272, 155, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(127, 28824, 11344, 158, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(128, 29096, 12208, 159, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(129, 29096, 12752, 160, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(130, 30728, 12032, 161, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(131, 30536, 12784, 164, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Sapphirepolis - Ampercorp - Floor #3 rooms
	Overworld_CreateDoor(132, 28320, 10288, 155, 29584, 10304, 156, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(133, 28448, 10288, 155, 29744, 10304, 156, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(134, 28576, 10288, 155, 29904, 10304, 156, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(135, 28704, 10288, 155, 30064, 10304, 156, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(136, 28944, 10288, 155, 30224, 10304, 157, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(137, 29072, 10288, 155, 30384, 10304, 157, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(138, 29200, 10288, 155, 30544, 10304, 157, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(139, 29328, 10288, 155, 30704, 10304, 157, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(140, 28448, 10576, 155, 29744, 10656, 156, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(141, 28576, 10576, 155, 29904, 10656, 156, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(142, 28704, 10576, 155, 30064, 10656, 156, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(143, 28944, 10576, 155, 30224, 10656, 157, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(144, 29072, 10576, 155, 30384, 10656, 157, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(145, 29200, 10576, 155, 30544, 10656, 157, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Sapphirepolis - Ampercorp
	Overworld_CreateDoor(146, 30944, 12216, 161, 32080, 12232, 162, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	Overworld_CreateDoor(147, 32056, 12672, 162, 32552, 12032, 163, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(148, 32664, 11680, 163, 31032, 12272, 161, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(149, 30536, 13472, 164, 30944, 13160, 165, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_UP);
	
	// Sapphirepolis - Brilliant Connection
	Overworld_CreateDoor_Advanced(150, 26984, 9584, 151, 512, 7272, 166, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_DOWN, 176, 16, 16, 176);
	Overworld_CreateDoor(151, 2632, 7632, 166, 2776, 7424, 166, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(152, 4600, 7280, 166, 4600, 7136, 166, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(153, 6320, 7384, 166, 5696, 9048, 167, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(154, 6352, 9048, 167, 29904, 7480, 168, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(155, 30336, 6656, 168, 29408, 7840, 169, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(156, 29408, 7584, 169, 30336, 6352, 168, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Brilliant Mountains
	Overworld_CreateDoor(157, 28688, 5344, 168, 29872, 8960, 170, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(158, 29872, 8960, 170, 29248, 9008, 171, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(159, 29184, 8400, 171, 28752, 5232, 168, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor_Advanced(160, 31904, 4496, 168, 30384, 8960, 172, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN, 48, 16, 16, 16);
	Overworld_CreateDoor(161, 31744, 9840, 172, 30336, 9152, 172, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(162, 30720, 9216, 172, 31744, 9968, 173, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(163, 31744, 11776, 173, 32224, 13296, 174, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	
	// Sapphirepolis - Restaurant
	Overworld_CreateDoor(164, 26168, 1024, 150, 20648, 15296, 186, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(165, 20312, 14880, 186, 20312, 15632, 187, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Sapphirepolis - Whitelight
	Overworld_CreateDoor(166, 29864, 2208, 150, 19752, 15552, 188, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(167, 19616, 15496, 188, 19616, 15976, 189, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	Overworld_CreateDoor(168, 19888, 15496, 188, 19888, 15976, 190, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(169, 19616, 15432, 189, 19616, 15704, 191, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(170, 19888, 15432, 190, 19888, 15704, 191, OBJECT_DIRECTION_LEFT, OBJECT_DIRECTION_RIGHT);
	Overworld_CreateDoor(171, 19752, 15440, 188, 19760, 16112, 192, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(172, 18856, 16016, 193, 19760, 16112, 192, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(173, 18088, 16016, 195, 19760, 16112, 192, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(174, 18776, 16000, 193, 18776, 15824, 194, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(175, 18936, 16000, 193, 18936, 15824, 194, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(176, 18008, 16000, 195, 18008, 15824, 196, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(177, 18168, 16000, 195, 18168, 15824, 196, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Sapphirepolis - Hotel
	Overworld_CreateDoor(178, 25880, 3504, 150, 16760, 16272, 197, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(179, 16760, 15872, 197, 15952, 16432, 198, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(180, 16760, 15216, 197, 15952, 16432, 198, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(181, 16760, 14768, 197, 15952, 16432, 198, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(182, 16584, 14864, 197, 15736, 16304, 199, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Sapphirepolis - Ampercorp
	Overworld_CreateDoor(183, 29600, 9616, 154, 30064, 9728, 175, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(184, 29608, 11088, 158, 29944, 11200, 158, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(185, 29240, 11776, 159, 28328, 12320, 159, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(186, 29144, 14432, 176, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(187, 29000, 16208, 177, 29288, 15520, 177, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(188, 29288, 16208, 177, 29000, 15520, 177, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(189, 29144, 16208, 177, 27816, 9440, 153, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Brilliant Mountains
	Overworld_CreateDoor(190, 30368, 4992, 168, 30368, 4848, 168, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(191, 32168, 14160, 174, 32168, 14432, 174, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(192, 31704, 14736, 174, 31704, 14960, 174, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor_Advanced(193, 32448, 15016, 174, 30064, 15016, 200, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_LEFT, 16, 32, 16, 32);
	Overworld_CreateDoor(194, 30480, 15072, 200, 30240, 15792, 200, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(195, 31016, 15872, 200, 10856, 14976, 201, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(196, 12584, 14992, 201, 12920, 15104, 201, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(197, 14168, 15296, 201, 4600, 14864, 202, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(198, 6280, 15616, 202, 6680, 16416, 202, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(199, 6696, 15936, 202, 6696, 15264, 202, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Village
	Overworld_CreateDoor_Advanced(200, 8984, 5552, 0, 8600, 5376, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN, 80, 16, 80, 16);
	
	// Metro
	Overworld_CreateDoor_Advanced(201, 22432, 10144, 203, 21888, 3712, 150, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN, 112, 16, 80, 16);
	
	// Village
	Overworld_CreateDoor(202, 4888, 1408, 0, 4888, 1248, 0, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	
	
	// Illusion - Lapis Hotel
	Overworld_CreateDoor(231, 1952, 14352, 239, 2464, 14448, 230, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(232, 1328, 14976, 232, 1048, 14224, 238, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(233, 2816, 12576, 234, 2432, 12688, 233, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(234, 2800, 12976, 235, 2816, 12448, 234, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(235, 1952, 13920, 239, 1952, 13424, 235, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(236, 2768, 14112, 237, 912, 13952, 236, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(237, 344, 14352, 238, 880, 12672, 236, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_UP);
	Overworld_CreateDoor(238, 2320, 14288, 239, 2464, 14208, 237, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_LEFT);
	Overworld_CreateDoor(239, 1584, 14288, 239, 1360, 14208, 238, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_RIGHT);
	
	// Illusion - Sapphireton Island
	Overworld_CreateDoor(240, 4960, 9888, 241, 4944, 9408, 242, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	// Illusion - Time Waterflows
	Overworld_CreateDoor(241, 4848, 11376, 243, 5024, 11424, 244, OBJECT_DIRECTION_RIGHT, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(242, 5616, 10880, 244, 6784, 11664, 245, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(243, 6424, 10384, 245, 5624, 11904, 246, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(244, 7552, 11392, 245, 5440, 11920, 247, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(245, 7768, 10352, 245, 5784, 11824, 248, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(246, 7936, 10352, 245, 5952, 11824, 248, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(247, 6064, 11744, 248, 6064, 12016, 249, OBJECT_DIRECTION_DOWN, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(248, 7056, 10400, 245, 3888, 11808, 250, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	Overworld_CreateDoor(249, 4208, 11696, 250, 897, 11249, 231, OBJECT_DIRECTION_UP, OBJECT_DIRECTION_DOWN);
	
	
	
	Player_TeleportToTile(42, 169);
	overworld.areaId = 1;
	overworld.transition.id = 0;
}



void Init() {
	game.forceGameQuit = false;
	game.windowWidth = 640;
	game.windowHeight = 480;
	game.rendererSize = 1;
	game.rendererX = 0;
	game.rendererY = 0;
	
	game.settings.textSkip = false;
	game.settings.autoRun = true;
	game.settings.fullscreen = false;
	game.settings.showStatSymbolLabels = false;
	
	game.debug = 1;
	game.saveFileNumber = 0;
	game.frameskip = 0;
	game.frameskipCounter = 0;
	Drawer_SetProjection(640, 360, 1);
	Drawer_SetDrawColor(255, 255, 255);
	Drawer_SetDrawAlpha(255);
	Drawer_SetDrawBlend(BLENDMODE_BLEND);
	Drawer_SetFontSprite(SPR_font_main);
	
	DevConsole_Init();
	
	LoadSprites();
	LoadAudio();
	LoadDialogData();
	LoadFighterData();
	LoadBattleBodyData();
	LoadActionData();
	LoadArmorData();
	LoadPassiveData();
	LoadItemData();
	LoadStatusEffectData();
	for (int i = 0; i < 3; i++) {
		game.mouseHeld[i] = 0;
		game.mouseHeldPrev[i] = 0;
		game.mousePressed[i] = 0;
	}
	game.timer = 0;
	
	game.mouseX = 0;
	game.mouseY = 0;
	game.mouseXPrev = game.mouseX;
	game.mouseYPrev = game.mouseY;
	game.mouseScrollY = 0;
	
	for (int i = 0; i < 256; i++) {
		game.keyStates[i] = 0;
	}
	for (int i = 0; i < 32; i++) {
		game.playerKeyStates[i] = 0;
		game.playerKeyStatesPrev[i] = 0;
		game.playerKeyPressed[i] = 0;
		game.playerKeyReleased[i] = 0;
	}
	
	Setup();
	
	for (int i = 0; i < 4; i++) {
		profile.saveFiles[i].exists = false;
	}
	
	profile.gameBeaten = false;
	LoadSaveData();
	
	ChangeScene(SCENE_MENU);
	
	game.internal.keyStates = SDL_GetKeyboardState(NULL);
}

void UpdateInput() {
	game.mouseXPrev = game.mouseX;
	game.mouseYPrev = game.mouseY;
	SDL_GetMouseState(&game.mouseX, &game.mouseY);
	game.mouseX = (game.mouseX - game.rendererX) / game.rendererSize;
	game.mouseY = (game.mouseY - game.rendererY) / game.rendererSize;
	
	if (devConsole.enabled) {
		for (int i = 0; i < 256; i++) {
			game.keyStates[i] = false;
		}
	}
	else {
		for (int i = 0; i < 256; i++) {
			game.keyStates[i] = game.internal.keyStates[i];
		}
	}
	
	for (int i = 0; i < 3; i++) {
		game.mousePressed[i] = game.mouseHeld[i] && !game.mouseHeldPrev[i];
		game.mouseReleased[i] = !game.mouseHeld[i] && game.mouseHeldPrev[i];
		
		game.mouseHeldPrev[i] = game.mouseHeld[i];
	}
	if (game.mouseScrollY > 0) game.mouseScrollY--;
	if (game.mouseScrollY < 0) game.mouseScrollY++;
	
	for (int i = 0; i < 256; i++) {
		game.keyPressed[i] = game.keyStates[i] && !game.keyStatesPrev[i];
		game.keyReleased[i] = !game.keyStates[i] && game.keyStatesPrev[i];
		
		game.keyStatesPrev[i] = game.keyStates[i];
	}
	
	
	
	game.playerKeyStates[PLAYER_BUTTON_Z] = game.keyStates[SDL_SCANCODE_Z] || game.keyStates[SDL_SCANCODE_SPACE] || game.keyStates[SDL_SCANCODE_W];
	game.playerKeyStates[PLAYER_BUTTON_X] = game.keyStates[SDL_SCANCODE_X] || game.keyStates[SDL_SCANCODE_LSHIFT];
	game.playerKeyStates[PLAYER_BUTTON_C] = game.keyStates[SDL_SCANCODE_C] || game.keyStates[SDL_SCANCODE_RETURN];
	game.playerKeyStates[PLAYER_BUTTON_A] = game.keyStates[SDL_SCANCODE_A] || game.keyStates[SDL_SCANCODE_Q];
	game.playerKeyStates[PLAYER_BUTTON_S] = game.keyStates[SDL_SCANCODE_S];
	game.playerKeyStates[PLAYER_BUTTON_D] = game.keyStates[SDL_SCANCODE_D];
	
	game.playerKeyStates[PLAYER_BUTTON_LEFT] = game.keyStates[SDL_SCANCODE_LEFT];
	game.playerKeyStates[PLAYER_BUTTON_RIGHT] = game.keyStates[SDL_SCANCODE_RIGHT];
	game.playerKeyStates[PLAYER_BUTTON_UP] = game.keyStates[SDL_SCANCODE_UP];
	game.playerKeyStates[PLAYER_BUTTON_DOWN] = game.keyStates[SDL_SCANCODE_DOWN];
	
	for (int i = 0; i < 32; i++) {
		game.playerKeyPressed[i] = game.playerKeyStates[i] && !game.playerKeyStatesPrev[i];
		game.playerKeyReleased[i] = !game.playerKeyStates[i] && game.playerKeyStatesPrev[i];
		
		game.playerKeyStatesPrev[i] = game.playerKeyStates[i];
	}
}

void Update() {
	UpdateInput();
	
	if (game.keyStates[SDL_SCANCODE_BACKSLASH]) return;
	
	if (game.popup.enabled) {
		if (PlayerButtonPressed(PLAYER_BUTTON_Z)) {
			game.popup.enabled = false;
		}
		return;
	}
	
	game.timer++;
	
	switch (game.scene) {
		case SCENE_MENU:
			MainMenu_Update();
			break;
		case SCENE_CINEMA:
			Cinema_Update();
			break;
		case SCENE_OVERWORLD:
			Overworld_Update();
			break;
		case SCENE_BATTLE:
			Battle_Update();
			break;
		case SCENE_GAMEOVER:
			GameOver_Update();
			break;
		case SCENE_ENDING:
			Ending_Update();
			break;
		case SCENE_MAPEDITOR:
			MapEditor_Update();
			break;
		case SCENE_CHESS:
			Chess_Update();
			break;
	}
	
	Event_Update();
	Dialog_Update();
	
	for (int i = 0; i < audioSystem.soundInterruptCount; i++) {
		Audio_PlaySound(audioSystem.soundInterrupts[i]);
	}
	audioSystem.soundInterruptCount = 0;
	
	if (audioSystem.currentMusicId >= 0 && audioSystem.currentMusicCanLoop)
	if (audioSystem.musicTracks[audioSystem.currentMusicId].loopMusicId >= 0 && !Mix_PlayingMusic()) {
		Audio_PlayMusic(audioSystem.musicTracks[audioSystem.currentMusicId].loopMusicId);
	}
}

void Draw() {
	Drawer_SetProjection(320, 240, 1);
	Drawer_SetDrawColor(255, 255, 255);
	Drawer_SetDrawAlpha(255);
	Drawer_SetFontSprite(SPR_font_main);
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	switch (game.scene) {
		case SCENE_MENU:
			MainMenu_Draw();
			break;
		case SCENE_CINEMA:
			Cinema_Draw();
			break;
		case SCENE_OVERWORLD:
			Overworld_Draw();
			break;
		case SCENE_BATTLE:
			Battle_Draw();
			break;
		case SCENE_GAMEOVER:
			GameOver_Draw();
			break;
		case SCENE_ENDING:
			Ending_Draw();
			break;
		case SCENE_MAPEDITOR:
			MapEditor_Draw();
			break;
		case SCENE_CHESS:
			Chess_Draw();
			break;
	}
	
	if (game.popup.enabled) {
		Drawer_SetProjection(320, 240, 1);
		Drawer_SetDrawAlpha(127);
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		Drawer_SetDrawAlpha(255);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
		
		DrawDialogBox(0, 176, 640, 128);
		Drawer_DrawText(game.popup.message, 256, 8, 180, 2, 2);
	}
	
	if (devConsole.enabled) {
		DevConsole_Draw();
	}
}

void ChangeScene(int scene) {
	game.scene = scene;
	game.timer = 0;
	
	switch (game.scene) {
		case SCENE_MENU:
			MainMenu_Init();
			break;
		case SCENE_CINEMA:
			Cinema_Init();
			break;
		case SCENE_OVERWORLD:
			Overworld_Init();
			break;
		case SCENE_BATTLE:
			Battle_Init();
			break;
		case SCENE_GAMEOVER:
			GameOver_Init();
			break;
		case SCENE_ENDING:
			Ending_Init();
			break;
		case SCENE_MAPEDITOR:
			MapEditor_Init();
			break;
		case SCENE_CHESS:
			Chess_Init();
			break;
	}
}



void MainMenu_Init() {
	overworld.transition.id = 0;
	overworld.fadeAlpha = 1;
	Audio_PlayMusic(MUS_menu);
	
	MainMenu_ChangeMenu(0);
}

void MainMenu_Update() {
	if (game.timer < 30) {
		overworld.fadeAlpha = 1 - (float)game.timer / 30;
		return;
	}
	else if (game.timer == 30) {
		overworld.fadeAlpha = 0;
	}
	
	if (overworld.transition.id == 0) {
		Menu_Update(&overworld.menu);
		
		if (overworld.menu.id == 0) {
			if (overworld.menu.optionPressed == 0) {
				Audio_PlaySound(SND_mana);
				overworld.transition.id = 1;
				overworld.transition.timer = 0;
			}
			else if (overworld.menu.optionPressed == 1) {
				MainMenu_ChangeMenu(1);
				Menu_ResetCursor(&overworld.menu);
			}
			else if (overworld.menu.optionPressed == 2) {
				MainMenu_ChangeMenu(4);
				Menu_ResetCursor(&overworld.menu);
			}
			else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
				
			}
		}
		else if (overworld.menu.id == 1) {
			if (overworld.menu.optionPressed >= 0) {
				if (profile.saveFiles[overworld.menu.optionPressed].exists) {
					overworld.menuBuffer[0] = overworld.menu;
					MainMenu_ChangeMenu(2);
					Menu_ResetCursor(&overworld.menu);
				}
			}
			else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
				MainMenu_ChangeMenu(0);
			}
		}
		else if (overworld.menu.id == 2) {
			if (overworld.menu.optionPressed == 0) {
				int ret = Profile_LoadGameSlot(overworld.menu.cursors[1]);
				if (ret == 1) {
					Audio_PlaySound(SND_mana);
					Audio_StopMusic();
					overworld.transition.id = 2;
					overworld.transition.timer = 0;
					game.saveFileNumber = overworld.menu.cursors[1];
				}
				else {
					Audio_PlaySound(SND_no);
					if (ret == -2) {
						CreatePopup("File is not a Rubindeavor save.");
					}
					else if (ret == -3)
						CreatePopup("This file is from an older version\nof Rubindeavor and cannot be loaded.");
					else
						CreatePopup("Failed to load the file.");
				}
			}
			else if (overworld.menu.optionPressed == 1) {
				MainMenu_ChangeMenu(3);
				Menu_ResetCursor(&overworld.menu);
			}
			else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
				MainMenu_ChangeMenu(1);
			}
		}
		else if (overworld.menu.id == 3) {
			if (overworld.menu.optionPressed == 1) {
				int ret = Profile_DeleteGameSlot(overworld.menu.cursors[1]);
				if (ret == 1) {
					Audio_PlaySound(SND_explode);
				}
				else {
					Audio_PlaySound(SND_no);
					CreatePopup("Could not delete the file.");
				}
				MainMenu_ChangeMenu(1);
			}
			else if (overworld.menu.optionPressed == 0 || overworld.menu.optionPressed == MENUOPTION_BACK) {
				MainMenu_ChangeMenu(1);
			}
		}
		else if (overworld.menu.id == 4) {
			if (overworld.menu.optionPressed == 0) {
				Audio_StopMusic();
				MainMenu_ChangeMenu(5);
				Menu_ResetCursor(&overworld.menu);
			}
			else if (overworld.menu.optionPressed == 1) {
				game.settings.textSkip = overworld.menu.optionPressedValue;
			}
			else if (overworld.menu.optionPressed == 9999) {
				game.settings.autoRun = overworld.menu.optionPressedValue;
			}
			else if (overworld.menu.optionPressed == 2) {
				game.settings.fullscreen = overworld.menu.optionPressedValue;
				UpdateFullscreenMode();
			}
			else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
				MainMenu_ChangeMenu(0);
			}
		}
		else if (overworld.menu.id == 5) {
			if (overworld.menu.optionPressed == 0) {
				int musicId = audioSystem.soundtracks[overworld.menu.optionPressedValue].musicId;
				if (audioSystem.currentMusicId == musicId)
					Audio_StopMusic();
				else
					Audio_PlayMusic(musicId);
			}
			else if (overworld.menu.optionPressed == MENUOPTION_BACK) {
				Audio_PlayMusic(MUS_menu);
				MainMenu_ChangeMenu(4);
			}
		}
	}
	
	switch (overworld.transition.id) {
		case 1:
			overworld.transition.timer++;
			if (overworld.transition.timer < 60) {
				overworld.fadeAlpha = fmin(1, (float)overworld.transition.timer / 50);
			}
			else {
				Setup();
				overworld.fadeAlpha = 1;
				overworld.transition.id = 1;
				overworld.transition.timer = 24;
				overworld.state = OVERWORLD_STATE_IDLE;
				ShowCinemaCutscene(0);
			}
			break;
		case 2:
			overworld.transition.timer++;
			if (overworld.transition.timer < 60) {
				overworld.fadeAlpha = fmin(1, (float)overworld.transition.timer / 50);
			}
			else {
				overworld.fadeAlpha = 1;
				overworld.transition.id = 1;
				overworld.transition.timer = 24;
				overworld.state = OVERWORLD_STATE_IDLE;
				ChangeScene(SCENE_OVERWORLD);
				Overworld_ChangeArea(overworld.areaId);
			}
			break;
	}
}

void MainMenu_Draw() {
	Drawer_SetProjection(320, 240, 1);
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	float x = (game.timer / 2) % 128;
	float y = (game.timer / 3) % 128;
	
	Drawer_SetDrawColor(0, 0, 0);
	
	Drawer_SetDrawColor(31, 0, 0);
	for (int j = -4; j < 14; j++)
	for (int i = -4; i < 14; i++) {
		Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i, y + 64*j / 2, 0, 1, 1);
	}
	
	Drawer_SetDrawBlend(BLENDMODE_ADD);
	for (int j = -4; j < 14; j++)
	for (int i = -4; i < 14; i++) {
		Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i, y + 64*j, 0, 1, 1);
	}
	Drawer_SetDrawBlend(BLENDMODE_BLEND);
	Drawer_SetDrawColor(255, 255, 255);
	
	switch (overworld.menu.id) {
		case 0:
			Drawer_DrawSprite(SPR_gui_rubindeavor, SCREEN_WIDTH / 2, 64, 0, 8, 8);
			
			Drawer_SetFontSprite(SPR_font_small);
			Drawer_DrawText("---Controls---\n\nArrows - move, navigate\nZ / Space - interact, confirm\nX / Shift - run, cancel\nC / Enter - open menu", 128, 320, 320, 2, 2);
			Drawer_SetFontSprite(SPR_font_main);
			
			Menu_DrawOptions(&overworld.menu, 0, 320, 632);
			break;
		case 1:
			{
				DrawDialogBox(24, 0, 592, SCREEN_HEIGHT);
				Drawer_DrawText("Load Game", 128, 32, 4, 2, 2);
				Menu* menu = &overworld.menu;
				int c = 0;
				for (int i = menu->pageColumns * menu->pageRows * menu->page; i < menu->pageColumns * menu->pageRows * (menu->page + 1) && i < menu->optionCount; i++) {
					int x = 32;
					int y = 40 + (c / menu->pageColumns) * 100;
					DrawSaveFile(i, x, y, 0, menu->cursors[1] == i);
					c++;
				}
				
				Drawer_SetDrawColor(255, 255, 255);
				if (menu->page + 1 < menu->pageCount)
					Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 4, 456, 0, 2, 2);
				if (menu->page - 1 >= 0)
					Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 32, 456, 0, -2, 2);
			}
			break;
		case 2:
			{
				DrawDialogBox(24, 0, 592, SCREEN_HEIGHT);
				Drawer_DrawText("Load Game", 128, 32, 4, 2, 2);
				Menu* menu = &overworld.menuBuffer[0];
				int c = 0;
				for (int i = menu->pageColumns * menu->pageRows * menu->page; i < menu->pageColumns * menu->pageRows * (menu->page + 1) && i < menu->optionCount; i++) {
					int x = 32;
					int y = 40 + (c / menu->pageColumns) * 100;
					DrawSaveFile(i, x, y, menu->cursors[1] == i, menu->cursors[1] == i);
					if (menu->cursors[1] == i) {
						Menu_DrawOptions(&overworld.menu, x, y + 28, 632);
					}
					c++;
				}
				
				Drawer_SetDrawColor(255, 255, 255);
				if (menu->page + 1 < menu->pageCount)
					Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 4, 456, 0, 2, 2);
				if (menu->page - 1 >= 0)
					Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 32, 456, 0, -2, 2);
			}
			break;
		case 3:
			{
				DrawDialogBox(24, 0, 592, SCREEN_HEIGHT);
				Drawer_DrawText("Load", 128, 32, 4, 2, 2);
				Menu* menu = &overworld.menuBuffer[0];
				int c = 0;
				for (int i = menu->pageColumns * menu->pageRows * menu->page; i < menu->pageColumns * menu->pageRows * (menu->page + 1) && i < menu->optionCount; i++) {
					int x = 32;
					int y = 40 + (c / menu->pageColumns) * 100;
					DrawSaveFile(i, x, y, 2 * (menu->cursors[1] == i), menu->cursors[1] == i);
					if (menu->cursors[1] == i) {
						Menu_DrawOptions(&overworld.menu, x, y + 28, 632);
					}
					c++;
				}
				
				Drawer_SetDrawColor(255, 255, 255);
				if (menu->page + 1 < menu->pageCount)
					Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 4, 456, 0, 2, 2);
				if (menu->page - 1 >= 0)
					Drawer_DrawSprite(SPR_gui_valuearrow, 608 - 32, 456, 0, -2, 2);
			}
			break;
		case 4:
			DrawDialogBox(0, 148, SCREEN_WIDTH, 184);
			DrawDialogBox(0, 332, SCREEN_WIDTH, 128);
			
			Menu_DrawOptions(&overworld.menu, 0, 148, 632);
			
			const int x = 8;
			const int y = 336;
			
			switch (overworld.menu.cursors[1]) {
				case 0: Drawer_DrawText("Listen to the game's soundtracks.", 128, x, y, 2, 2); break;
				case 1: Drawer_DrawText("Hold C/Enter to skip dialog text.", 128, x, y, 2, 2); break;
				//case 2: Drawer_DrawText("If enabled, you automatically run\nwithout holding X/Shift (holding it\nmakes you walk instead).", 128, x, y, 2, 2); break;
				case 2: Drawer_DrawText("Choose fullscreen mode or windowed\nmode. You can also press F4.", 128, x, y, 2, 2); break;
				default: Drawer_DrawText("Invalid Option", 128, x, y, 2, 2); break;
			}
			break;
		case 5:
			DrawDialogBox(0, 204, SCREEN_WIDTH, 72);
			DrawDialogBox(0, 276, SCREEN_WIDTH, 44);
			Drawer_DrawText("Sound Test", 128, 8, 208, 2, 2);
			Drawer_DrawText(audioSystem.soundtracks[overworld.menu.options[0].value].title, 128, 8, 280, 2, 2);
			
			Menu_DrawOptions(&overworld.menu, 0, 232, 632);
			break;
	}
	
	if (overworld.fadeAlpha > 0) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_SetDrawAlpha(overworld.fadeAlpha * 255);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
}

void MainMenu_ChangeMenu(int id) {
	switch (id) {
		case 0:
			Menu_New(&overworld.menu, 0, 1, 4, 0);
			Menu_AddOption(&overworld.menu, true, 0, "New Game");
			Menu_AddOption(&overworld.menu, true, 1, "Continue");
			Menu_AddOption(&overworld.menu, true, 2, "Settings");
			break;
		case 1:
			Menu_New(&overworld.menu, 1, 1, 4, 1);
			for (int i = 0; i < 32; i++) {
				Menu_AddOption(&overworld.menu, profile.saveFiles[i].exists, i, "");
			}
			break;
		case 2:
			Menu_New(&overworld.menu, 2, 1, 2, 2);
			Menu_AddOption(&overworld.menu, true, 0, "Load");
			Menu_AddOption(&overworld.menu, true, 1, "Delete");
			break;
		case 3:
			Menu_New(&overworld.menu, 3, 1, 2, 3);
			Menu_AddOption(&overworld.menu, true, 0, "No");
			Menu_AddOption(&overworld.menu, true, 1, "Yes");
			break;
		case 4:
			Menu_New(&overworld.menu, 4, 1, 8, 1);
			Menu_AddOption(&overworld.menu, true, 0, "Sound Test");
			Menu_AddOption_Boolean(&overworld.menu, true, game.settings.textSkip, "Text Skip");
			Menu_AddOption_Boolean(&overworld.menu, true, game.settings.fullscreen, "Fullscreen");
			break;
		case 5:
			Menu_New(&overworld.menu, 5, 1, 8, 2);
			Menu_AddOption_Number(&overworld.menu, true, 0, "", 0, (profile.gameBeaten) ? audioSystem.soundtrackCount - 1 : 1);
			break;
	}
}



void Cinema_Init() {
	
}

void Cinema_Update() {
	if (game.cinema.transitionTimer == 0 && Dialog_IsFinished()) {
		game.cinema.timer++;
		
		switch (game.cinema.id) {
			case 0:
				if (game.cinema.timer == 1) {
					Audio_PlayMusic(MUS_menu);
					Cinema_SlideImage(SPR_misc_gemia_map2);
					Dialog_RunVoiced(10, 1);
				}
				if (game.cinema.timer == 2) {
					Dialog_RunVoiced(11, 1);
				}
				if (game.cinema.timer == 3) {
					Cinema_SlideImage(SPR_misc_cinema_gems);
					Dialog_RunVoiced(12, 1);
				}
				if (game.cinema.timer == 4) {
					Dialog_RunVoiced(13, 1);
				}
				if (game.cinema.timer == 5) {
					Dialog_RunVoiced(14, 1);
				}
				if (game.cinema.timer == 6) {
					Cinema_SlideImage(SPR_misc_gemia_map1);
					Dialog_RunVoiced(15, 1);
				}
				if (game.cinema.timer == 7) {
					Cinema_SlideImage(SPR_misc_cinema_rubyhouse);
					Dialog_RunVoiced(16, 1);
				}
				if (game.cinema.timer == 8) {
					Cinema_SlideImage(SPR_misc_cinema_ruby);
					Dialog_RunVoiced(17, 1);
				}
				if (game.cinema.timer == 9) {
					Dialog_RunVoiced(18, 1);
				}
				if (game.cinema.timer == 10) {
					Dialog_RunVoiced(19, 1);
				}
				if (game.cinema.timer == 11) {
					Dialog_RunVoiced(20, 1);
				}
				if (game.cinema.timer == 12) {
					Cinema_SlideImage(-1);
					Dialog_RunVoiced(21, 1);
				}
				if (game.cinema.timer == 13) {
					Cinema_SlideImage(SPR_misc_cinema_rubyawakening);
					Audio_StopMusic();
					Dialog_RunVoiced(22, 1);
				}
				if (game.cinema.timer == 14) {
					Audio_PlaySound(SND_introwakeup);
				}
				
				if (game.cinema.timer == 378) {
					Overworld_ChangeArea(1);
					ChangeScene(SCENE_OVERWORLD);
				}
				break;
		}
	}
	
	if (game.cinema.transitionTimer > 0) {
		game.cinema.transitionTimer++;
		if (game.cinema.transitionTimer == 30) {
			game.cinema.spriteId = game.cinema.transitionSpriteId;
		}
		if (game.cinema.transitionTimer >= 60) {
			game.cinema.transitionTimer = 0;
		}
	}
}

void Cinema_Draw() {
	Drawer_SetProjection(320, 240, 1);
	
	if (game.cinema.spriteId >= 0) Drawer_DrawSprite(game.cinema.spriteId, 320, 180, 0, 2, 2);
	
	if (game.cinema.transitionTimer > 0) {
		Drawer_SetDrawColor(0, 0, 0);
		if (game.cinema.transitionTimer <= 30)
			Drawer_SetDrawAlpha(game.cinema.transitionTimer * 255 / 30);
		else
			Drawer_SetDrawAlpha(255 - (game.cinema.transitionTimer - 30) * 255 / 30);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
	
	if (dialogSystem.state != DIALOG_STATE_IDLE) {
		Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
		
		Drawer_DrawText(dialogSystem.text, dialogSystem.textLength, 8, SCREEN_HEIGHT - 124, 2, 2);
	}
	
	if (game.cinema.id == 0 && game.cinema.timer > 13) {
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(Min(255, (game.cinema.timer - 13) * 255 / 300));
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
}

void Cinema_SlideImage(int spriteId) {
	game.cinema.transitionSpriteId = spriteId;
	game.cinema.transitionTimer = 1;
}



void GameOver_Init() {
	
}

void GameOver_Update() {
	if (game.timer < 60) {
		overworld.fadeAlpha = 1 - (float)game.timer / 60;
	}
	else if (game.timer == 60) {
		overworld.fadeAlpha = 0;
	}
	else if (game.timer == 100) {
		Menu_New(&overworld.menu, 0, 1, 2, 0);
		Menu_AddOption(&overworld.menu, true, 0, "Retry Fight");
		Menu_AddOption(&overworld.menu, true, 1, "Load Last Save");
		Menu_ResetCursor(&overworld.menu);
		
		if (profile.flags[FLAG_OMEGALULU_GAMEOVER])
			Dialog_Run(4034);
		else if (profile.flags[FLAG_SAVECOUNT] == -1)
			Dialog_Run(4033);
		else
			Dialog_Run(Random_IRange(4010, 4021));
	}
	else if (game.timer == 101 && !Dialog_IsWaiting()) {
		game.timer--;
		if (profile.flags[FLAG_OMEGALULU_GAMEOVER] && Dialog_IsFinished()) {
			profile.gameBeaten = true;
			SaveSaveData();
			game.forceGameQuit = true;
			return;
		}
	}
	else if (game.timer == 102) {
		Menu_Update(&overworld.menu);
		
		if (overworld.menu.optionPressed == 0) {
			Dialog_Continue();
			battle.retry = true;
		}
		else if (overworld.menu.optionPressed == 1) {
			Dialog_Continue();
			battle.loadLastSave = true;
			
			if (profile.flags[FLAG_SAVECOUNT] != 0) {
				int ret = Profile_LoadGameSlot(game.saveFileNumber);
				if (ret == 1) {
					Audio_StopMusic();
					overworld.transition.id = 2;
					overworld.transition.timer = 0;
					overworld.fadeAlpha = 0;
					return;
				}
				else {
					profile.flags[FLAG_SAVECOUNT] = 0;
					Dialog_Run(Random_IRange(4030, 4033));
					Audio_PlaySound(SND_no);
					if (ret == -2) {
						CreatePopup("File is not a Rubindeavor save.");
					}
					else if (ret == -3)
						CreatePopup("This file is from an older version\nof Rubindeavor and cannot be loaded.");
					else
						CreatePopup("Failed to load the file.");
				}
			}
			overworld.fadeAlpha = 0;
		}
		else {
			game.timer--;
		}
	}
	else if (game.timer == 104 && !Dialog_IsFinished()) {
		game.timer--;
	}
	else if (game.timer > 105 && game.timer <= 165) {
		overworld.fadeAlpha = (float)(game.timer - 105) / 60;
	}
	else if (game.timer > 165 && game.timer < 190) {
		overworld.fadeAlpha = 1;
	}
	else if (game.timer >= 190) {
		if (battle.retry) {
			profile = profileBuffer;
			ChangeScene(SCENE_BATTLE);
		}
		else {
			if (profile.flags[FLAG_SAVECOUNT] != 0) {
				int ret = Profile_LoadGameSlot(game.saveFileNumber);
				if (ret == 1) {
					overworld.fadeAlpha = 1;
					overworld.transition.id = 1;
					overworld.transition.timer = 24;
					overworld.state = OVERWORLD_STATE_IDLE;
					ChangeScene(SCENE_OVERWORLD);
					Overworld_ChangeArea(overworld.areaId);
					return;
				}
				else {
					Audio_PlaySound(SND_no);
					if (ret == -2) {
						CreatePopup("File is not a Rubindeavor save.");
					}
					else if (ret == -3)
						CreatePopup("This file is from an older version\nof Rubindeavor and cannot be loaded.");
					else
						CreatePopup("Failed to load the file.");
				}
			}
			else {
				ChangeScene(SCENE_MENU);
			}
		}
	}
}

void GameOver_Draw() {
	Drawer_SetProjection(320, 240, 1);
	
	Drawer_SetFontAlignment(FONT_ALIGN_MIDDLE | FONT_ALIGN_TOP);
	Drawer_DrawText("GAME OVER", 32, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 4, 4);
	
	if (dialogSystem.state != DIALOG_STATE_IDLE) {
		Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
		
		Drawer_DrawText(dialogSystem.text, dialogSystem.textLength, 8, SCREEN_HEIGHT - 152, 2, 2);
	}
	
	if (game.timer == 101) {
		Menu_DrawOptions(&overworld.menu, 184, SCREEN_HEIGHT - 80, 632);
	}
	
	if (overworld.fadeAlpha > 0) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_SetDrawAlpha(overworld.fadeAlpha * 255);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
}



void Ending_Init() {
	game.ending.timer = 0;
	game.ending.stage = -1;
	for (int i = 0; i < 6; i++) game.ending.gems[i] = -1;
	game.ending.actionCount = 0;
	game.ending.armorCount = 0;
	game.ending.passiveCount = 0;
	game.ending.totalActionCount = 0;
	game.ending.totalArmorCount = 0;
	game.ending.totalPassiveCount = 0;
	
	if (game.ending.id == 1)
		Audio_StopMusic();
	else
		Audio_PlayMusic(MUS_tally);
	
	overworld.fadeAlpha = 0;
	
	for (int i = 2; i < OBJECT_COUNT_MAX; i++) {
		if (profile.actions[i] <= 0) continue;
		
		game.ending.actionCount++;
		game.ending.totalActionCount += profile.actions[i];
	}
	
	for (int i = 1; i < OBJECT_COUNT_MAX; i++) {
		if (profile.armors[i] <= 0) continue;
		
		game.ending.armorCount++;
		game.ending.totalArmorCount += profile.armors[i];
	}
	
	for (int i = 1; i < OBJECT_COUNT_MAX; i++) {
		if (profile.passives[i] <= 0) continue;
		
		game.ending.passiveCount++;
		game.ending.totalPassiveCount += profile.passives[i];
	}
}

void Ending_Update() {
	game.ending.timer++;
	bool skipping = PlayerButtonHeld(PLAYER_BUTTON_X) || PlayerButtonHeld(PLAYER_BUTTON_C);
	
	if (game.ending.stage < 0) {
		if (game.ending.timer >= 30) {
			game.ending.stage = 0;
			game.ending.timer = 0;
		}
	}
	else if (game.ending.stage == 0) {
		if (game.ending.timer >= 30 || (game.ending.timer >= 15 && skipping)) {
			bool gemShown = false;
			for (int i = 0; i < 5; i++) {
				if (!Profile_KeyItemExists(250 + i)) continue;
				
				for (int j = 0; j < 6; j++) {
					if (game.ending.gems[j] == i) break;
					
					if (game.ending.gems[j] == -1) {
						game.ending.gems[j] = i;
						Audio_PlaySound(SND_tallyancientgem);
						game.ending.timer = 0;
						gemShown = true;
						break;
					}
				}
				if (gemShown) break;
			}
			if (!gemShown) {
				game.ending.stage = 1;
				game.ending.timer = 0;
			}
		}
	}
	else if (game.ending.stage < 9) {
		if (game.ending.timer >= 16 || (game.ending.timer >= 8 && skipping)) {
			game.ending.stage++;
			game.ending.timer = 0;
			Audio_PlaySound(SND_chess_move);
		}
	}
	else if (game.ending.stage == 9) {
		if (game.ending.timer >= 60) {
			game.ending.stage = 32;
			game.ending.timer = 0;
			
			Menu_New(&overworld.menu, 0, 1, 1, 0);
			Menu_AddOption(&overworld.menu, true, 0, "Continue");
			Menu_ResetCursor(&overworld.menu);
		}
	}
	else if (game.ending.stage == 32) {
		Menu_Update(&overworld.menu);
		
		if (overworld.menu.optionPressed == 0) {
			game.ending.stage = 33;
			game.ending.timer = 0;
			Audio_FadeOutMusic(1000);
		}
	}
	else if (game.ending.stage == 33) {
		if (game.ending.timer < 60) {
			overworld.fadeAlpha = (float)game.ending.timer / 60;
		}
		else if (game.ending.timer < 90) {
			overworld.fadeAlpha = 1;
		}
		else {
			Setup();
			ChangeScene(SCENE_MENU);
		}
	}
}

void Ending_Draw() {
	Drawer_SetProjection(320, 240, 1);
	
	Drawer_DrawSprite(SPR_misc_backdrop_brilliant, 0, 0, 0, 2, 2);
	
	Drawer_SetDrawBlend(BLENDMODE_MUL);
	Drawer_SetDrawColor(0, 127, 255);
	Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Drawer_SetDrawBlend(BLENDMODE_BLEND);
	Drawer_SetDrawColor(255, 255, 255);
	
	Drawer_SetFontAlignment(FONT_ALIGN_MIDDLE | FONT_ALIGN_TOP);
	
	switch (game.ending.id) {
		case 0:
			SetString(game.textBuffer, "NORMAL ENDING (End #1)");
			break;
		case 1:
			SetString(game.textBuffer, "LONE SUPERNATURAL (End #2)");
			break;
		default:
			SetString(game.textBuffer, "UNKNOWN ENDING (End #unknown)");
			break;
	}
	Drawer_DrawText(game.textBuffer, 40, SCREEN_WIDTH / 2, 4, 2, 2);
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	for (int i = 0; i < 6; i++) {
		if (game.ending.gems[i] == -1) break;
		
		Drawer_DrawSprite(SPR_misc_gems, 320 - 64 + i * 32, 80, game.ending.gems[i], 2, 2);
	}
	
	for (int i = 0; i < game.ending.stage - 1 && i < 8; i++) {
		switch (i) {
			case 0:
				snprintf(game.textBuffer, 40, "Level %d", partyMembers[0].level);
				break;
			case 1:
				snprintf(game.textBuffer, 40, "EXP: %d", partyMembers[0].exp);
				break;
			case 2:
				snprintf(game.textBuffer, 40, "Total Skills: %d", game.ending.totalActionCount);
				break;
			case 3:
				snprintf(game.textBuffer, 40, "Total Armors: %d", game.ending.totalArmorCount);
				break;
			case 4:
				snprintf(game.textBuffer, 40, "Total Badges: %d", game.ending.totalPassiveCount);
				break;
			case 5:
				snprintf(game.textBuffer, 40, "Unique Skills: %d", game.ending.actionCount);
				break;
			case 6:
				snprintf(game.textBuffer, 40, "Unique Armors: %d", game.ending.armorCount);
				break;
			case 7:
				snprintf(game.textBuffer, 40, "Unique Badges: %d", game.ending.passiveCount);
				break;
		}
		Drawer_DrawText(game.textBuffer, 40, 8, 96 + i * 28, 2, 2);
	}
	
	if (game.ending.stage == 32) {
		Menu_DrawOptions(&overworld.menu, 0, 432, 632);
	}
	
	if (overworld.fadeAlpha > 0) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_SetDrawAlpha(overworld.fadeAlpha * 255);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
}
