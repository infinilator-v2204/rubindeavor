#include "generic.h"
#include "profile.h"
#include "overworld.h"
#include "action.h"
#include "armor.h"
#include "passives.h"
#include "sprites.h"

Profile profile;
Profile profileBuffer;

const int saveVersion = 1;

void fputc_short(int ch, FILE* stream) {
	fputc((uint8_t)(ch & 0xff), stream);
	fputc((uint8_t)((ch >> 8) & 0xff), stream);
}
void fputc_int(int ch, FILE* stream) {
	fputc((uint8_t)(ch & 0xff), stream);
	fputc((uint8_t)((ch >> 8) & 0xff), stream);
	fputc((uint8_t)((ch >> 16) & 0xff), stream);
	fputc((uint8_t)((ch >> 24) & 0xff), stream);
}
int fgetc_short(FILE* stream) {
	int ret = fgetc(stream);
	ret |= fgetc(stream) << 8;
	return ret;
}
int fgetc_int(FILE* stream) {
	int ret = fgetc(stream);
	ret |= fgetc(stream) << 8;
	ret |= fgetc(stream) << 16;
	ret |= fgetc(stream) << 24;
	return ret;
}

int SaveGame(const char* filename) {
	FILE* file = fopen(filename, "wb");
	
	if (file == NULL) return -1;
	
	fputc('R', file);
	fputc('X', file);
	fputc(0x55, file);
	fputc(0xaa, file);
	fputc_int(saveVersion, file);
	
	fputc_int(overworld.areaId, file);
	fputc_int((int)overworld.player.x, file);
	fputc_int((int)overworld.player.y, file);
	
	for (int i = 0; i < 5; i++) {
		fputc(profile.party[i], file);
	}
	for (int i = 0; i < 5; i++) {
		fputc(profile.partyOrder[i], file);
	}
	for (int i = 0; i < 5; i++) {
		fputc(partyMembers[i].inventoryUnlocked, file);
	}
	
	for (int i = 0; i < 10; i++) {
		PartyMember* partyMember = &partyMembers[i];
		
		fputc_int(partyMember->exp, file);
		fputc_int(partyMember->headId, file);
		fputc_int(partyMember->bodyId, file);
		fputc_int(partyMember->defaultArmorId, file);
		fputc_int(partyMember->armorId, file);
		fputc_int(partyMember->hpDamage, file);
		fputc_int(partyMember->tiredness, file);
		fputc_int(partyMember->tiredLevel, file);
		
		fputc_int(partyMember->movesetCount, file);
		for (int j = 0; j < partyMember->movesetCount; j++) {
			fputc_int(partyMember->moveset[j], file);
		}
		
		fputc_int(partyMember->uniqueActionCount, file);
		for (int j = 0; j < partyMember->uniqueActionCount; j++) {
			fputc_int(partyMember->uniqueActions[j], file);
		}
		
		fputc_int(partyMember->extraPassiveCount, file);
		for (int j = 0; j < partyMember->extraPassiveCount; j++) {
			fputc_int(partyMember->extraPassives[j], file);
		}
	}
	
	for (int i = 0; i < 1000; i++) {
		fputc_short(profile.actions[i], file);
		fputc_short(profile.actionsEquipped[i], file);
	}
	for (int i = 0; i < 1000; i++) {
		fputc_short(profile.armors[i], file);
		fputc_short(profile.armorsEquipped[i], file);
	}
	for (int i = 0; i < 1000; i++) {
		fputc_int(profile.flags[i], file);
	}
	
	fputc_int(profile.cash, file);
	
	for (int i = 0; i < 16; i++) {
		fputc_int(profile.itemInventory[i], file);
	}
	for (int i = 0; i < 64; i++) {
		fputc_int(profile.keyItemInventory[i], file);
	}
	
	fputc_int(overworld.map.tilesetSpriteId - firstTilesetSpriteId, file);
	
	fclose(file);
	return 1;
}

int LoadGame(const char* filename) {
	FILE* file = fopen(filename, "rb");
	
	if (file == NULL) return -1;
	
	if (fgetc(file) != 'R') return -2;
	if (fgetc(file) != 'X') return -2;
	if (fgetc(file) != 0x55) return -2;
	if (fgetc(file) != 0xaa) return -2;
	if (fgetc_int(file) != saveVersion) return -3;
	
	Setup();
	
	int areaId = fgetc_int(file);
	int playerX = fgetc_int(file);
	int playerY = fgetc_int(file);
	
	for (int i = 0; i < 5; i++) {
		profile.party[i] = fgetc(file);
	}
	for (int i = 0; i < 5; i++) {
		profile.partyOrder[i] = fgetc(file);
	}
	for (int i = 0; i < 5; i++) {
		partyMembers[i].inventoryUnlocked = fgetc(file);
	}
	
	for (int i = 0; i < 10; i++) {
		PartyMember* partyMember = &partyMembers[i];
		
		Party_SetExp(i, fgetc_int(file));
		partyMember->headId = fgetc_int(file);
		partyMember->bodyId = fgetc_int(file);
		partyMember->defaultArmorId = fgetc_int(file);
		partyMember->armorId = fgetc_int(file);
		partyMember->hpDamage = fgetc_int(file);
		partyMember->tiredness = fgetc_int(file);
		partyMember->tiredLevel = fgetc_int(file);
		
		partyMember->movesetCount = fgetc_int(file);
		for (int j = 0; j < partyMember->movesetCount; j++) {
			partyMember->moveset[j] = fgetc_int(file);
		}
		
		partyMember->uniqueActionCount = fgetc_int(file);
		for (int j = 0; j < partyMember->uniqueActionCount; j++) {
			partyMember->uniqueActions[j] = fgetc_int(file);
		}
		
		partyMember->extraPassiveCount = fgetc_int(file);
		for (int j = 0; j < partyMember->extraPassiveCount; j++) {
			partyMember->extraPassives[j] = fgetc_int(file);
		}
		Party_Refresh(i);
	}
	
	for (int i = 0; i < 1000; i++) {
		profile.actions[i] = fgetc_short(file);
		profile.actionsEquipped[i] = fgetc_short(file);
	}
	for (int i = 0; i < 1000; i++) {
		profile.armors[i] = fgetc_short(file);
		profile.armorsEquipped[i] = fgetc_short(file);
	}
	for (int i = 0; i < 1000; i++) {
		profile.flags[i] = fgetc_int(file);
	}
	
	profile.cash = fgetc_int(file);
	
	for (int i = 0; i < 16; i++) {
		profile.itemInventory[i] = fgetc_int(file);
	}
	for (int i = 0; i < 64; i++) {
		profile.keyItemInventory[i] = fgetc_int(file);
	}
	
	overworld.map.tilesetSpriteId = fgetc_int(file) + firstTilesetSpriteId;
	
	fclose(file);
	
	for (int i = 1; i < OBJECT_COUNT_MAX; i++) {
		if (profile.armors[i] == 0) continue;
		
		for (int j = 0; j < armorData[i].passiveCount; j++) {
			profile.passives[armorData[i].passives[j]] += profile.armors[i];
		}
	}
	for (int i = 0; i < 10; i++) {
		PartyMember* partyMember = &partyMembers[i];
		
		for (int j = 0; j < partyMember->extraPassiveCount; j++) {
			profile.passivesEquipped[partyMember->extraPassives[j]]++;
		}
	}
	
	for (int i = 0; i < 10; i++) {
		Party_Refresh(i);
	}
	
	Overworld_ChangeArea(areaId);
	Player_TeleportTo(playerX, playerY);
	Party_UpdateCaterpillar();
	Player_UpdateObject();
	
	overworld.transition.id = 1;
	overworld.transition.timer = 25;
	overworld.fadeAlpha = 1;
	return 1;
}

int SaveFileExists() {
	FILE* file = fopen("save.bin", "rb");
	
	if (file == NULL) return 0;
	
	fclose(file);
	return 1;
}

int SaveSaveData() {
	FILE* file = fopen("save/save.bin", "wb");
	
	if (file == NULL) return -1;
	
	fputc('R', file);
	fputc('X', file);
	fputc(0x55, file);
	fputc(0xaa, file);
	fputc_int(saveVersion, file);
	
	fputc(game.settings.textSkip | (game.settings.autoRun << 1), file);
	fputc_int(0, file); // reserved
	fputc_int(0, file); // reserved
	fputc_int(0, file); // reserved
	fputc_int(profile.gameBeaten, file);
	
	for (int i = 0; i < 16; i++) {
		fputc(profile.saveFiles[i].exists, file);
		if (!profile.saveFiles[i].exists) continue;
		
		for (int j = 0; j < 5; j++) {
			fputc(profile.saveFiles[i].party[j], file);
		}
		fputc_int(profile.saveFiles[i].level, file);
	}
	
	fclose(file);
	
	return 1;
}

int LoadSaveData() {
	FILE* file = fopen("save/save.bin", "rb");
	
	if (file == NULL) return -1;
	
	if (fgetc(file) != 'R') return -2;
	if (fgetc(file) != 'X') return -2;
	if (fgetc(file) != 0x55) return -2;
	if (fgetc(file) != 0xaa) return -2;
	if (fgetc_int(file) != saveVersion) return -3;
	
	int settingsFlags = fgetc(file);
	game.settings.textSkip = settingsFlags & 1;
	game.settings.autoRun = (settingsFlags >> 1) & 1;
	fgetc_int(file);
	fgetc_int(file);
	fgetc_int(file);
	profile.gameBeaten = fgetc_int(file);
	
	for (int i = 0; i < 16; i++) {
		profile.saveFiles[i].exists = fgetc(file);
		if (!profile.saveFiles[i].exists) continue;
		
		for (int j = 0; j < 5; j++) {
			profile.saveFiles[i].party[j] = fgetc(file);
		}
		profile.saveFiles[i].level = fgetc_int(file);
	}
	
	fclose(file);
	
	return 1;
}



int Profile_SaveGameSlot(int id) {
	snprintf(game.textBuffer, 32, "save/%d.bin", id);
	if (SaveGame(game.textBuffer) < 0) return -1;
	
	profile.saveFiles[id].exists = true;
	for (int i = 0; i < 5; i++) {
		profile.saveFiles[id].party[i] = profile.party[i];
	}
	profile.saveFiles[id].level = partyMembers[0].level;
	
	SaveSaveData();
	return 1;
}

int Profile_LoadGameSlot(int id) {
	snprintf(game.textBuffer, 32, "save/%d.bin", id);
	return LoadGame(game.textBuffer);
}

int Profile_DeleteGameSlot(int id) {
	if (!profile.saveFiles[id].exists) return -1;
	
	snprintf(game.textBuffer, 32, "save/%d.bin", id);
	if (remove(game.textBuffer)) return -1;
	
	profile.saveFiles[id].exists = false;
	
	SaveSaveData();
	return 1;
}



void Profile_AddAction(int id, int count) {
	profile.actions[id] += count;
}

void Profile_AddArmor(int id, int count) {
	profile.armors[id] += count;
	
	for (int i = 0; i < armorData[id].passiveCount; i++) {
		profile.passives[armorData[id].passives[i]] += count;
	}
}

void Profile_EquipAction(int partyId, int actionId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (profile.actionsEquipped[actionId] >= profile.actions[actionId] || partyMember->movesetCount >= 6) return;
	
	for (int i = 0; i < partyMember->movesetCount; i++) {
		if (partyMember->moveset[i] == actionId) return;
	}
	
	if (actionData[actionId].armorOnlyId > 0 && actionData[actionId].armorOnlyId != partyMember->armorId) return;
	
	partyMember->moveset[partyMember->movesetCount++] = actionId;
	profile.actionsEquipped[actionId]++;
}

void Profile_UnequipAction(int partyId, int movesetId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (movesetId >= partyMember->movesetCount) return;
	
	profile.actionsEquipped[partyMember->moveset[movesetId]]--;
	
	partyMember->movesetCount--;
	for (int i = movesetId; i < partyMember->movesetCount; i++) {
		partyMember->moveset[i] = partyMember->moveset[i + 1];
	}
}

void Profile_SwapAction(int partyId, int movesetId, int actionId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (profile.actionsEquipped[actionId] >= profile.actions[actionId]) return;
	
	if (movesetId >= partyMember->movesetCount) return;
	
	for (int i = 0; i < partyMember->movesetCount; i++) {
		if (partyMember->moveset[i] == actionId) return;
	}
	
	if (actionData[actionId].armorOnlyId > 0 && actionData[actionId].armorOnlyId != partyMember->armorId) return;
	
	profile.actionsEquipped[partyMember->moveset[movesetId]]--;
	
	partyMember->moveset[movesetId] = actionId;
	profile.actionsEquipped[actionId]++;
}

void Profile_EquipArmor(int partyId, int armorId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (partyMember->armorId == armorId) {
		profile.armorsEquipped[armorId]--;
		partyMember->armorId = 0;
		
		for (int i = 0; i < partyMember->extraPassiveCount; i++) {
			profile.passivesEquipped[partyMember->extraPassives[i]]--;
		}
		partyMember->extraPassiveCount = 0;
	}
	else {
		if (profile.armorsEquipped[armorId] >= profile.armors[armorId]) return;
		
		int gpNew = profile.gp;
		if (partyMember->armorId > 0) gpNew += Party_CalculateArmorCost(partyMember->armorId);
		gpNew -= Party_CalculateArmorCost(armorId);
		if (gpNew < 0) return;
		
		
		if (partyMember->armorId > 0) {
			profile.armorsEquipped[partyMember->armorId]--;
		}
		partyMember->armorId = armorId;
		profile.armorsEquipped[armorId]++;
		
		/*if (armorData[armorId].passiveCount + partyMember->extraPassiveCount > 4) {
			for (int i = 4 - armorData[armorId].passiveCount; i < partyMember->extraPassiveCount; i++) {
				profile.passivesEquipped[partyMember->extraPassives[i]]--;
			}
			partyMember->extraPassiveCount = 4 - armorData[armorId].passiveCount;
		}*/
		for (int i = 0; i < partyMember->extraPassiveCount; i++) {
			profile.passivesEquipped[partyMember->extraPassives[i]]--;
		}
		partyMember->extraPassiveCount = 0;
	}
	
	for (int i = 0; i < partyMember->movesetCount; i++) {
		Action* action = &actionData[partyMember->moveset[i]];
		if (action->armorOnlyId > 0 || (action->ranged && !armorData[partyMember->armorId].ranged)) {
			Profile_UnequipAction(partyId, i--);
		}
	}
	
	Party_Refresh(partyId);
}

void Profile_UnequipArmor(int partyId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (partyMember->armorId == 0) return;
	
	profile.armorsEquipped[partyMember->armorId]--;
	partyMember->armorId = 0;
	
	for (int i = 0; i < partyMember->movesetCount; i++) {
		Action* action = &actionData[partyMember->moveset[i]];
		if (action->armorOnlyId > 0 || action->ranged) {
			Profile_UnequipAction(partyId, i--);
		}
	}
	for (int i = 0; i < partyMember->extraPassiveCount; i++) {
		profile.passivesEquipped[partyMember->extraPassives[i]]--;
	}
	partyMember->extraPassiveCount = 0;
	
	Party_Refresh(partyId);
}

void Profile_EquipPassive(int partyId, int passiveId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (profile.passivesEquipped[passiveId] >= profile.passives[passiveId] || partyMember->extraPassiveCount >= 4 || partyMember->passiveCount >= 4) return;
	
	if (profile.gp - passiveData[passiveId].cost < 0) return;
	
	for (int i = 0; i < partyMember->passiveCount; i++) {
		if (partyMember->passives[i] == passiveId) return;
	}
	
	partyMember->extraPassives[partyMember->extraPassiveCount++] = passiveId;
	profile.passivesEquipped[passiveId]++;
	Party_Refresh(partyId);
}

void Profile_UnequipPassive(int partyId, int extraPassiveId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (extraPassiveId >= partyMember->extraPassiveCount) return;
	
	profile.passivesEquipped[partyMember->extraPassives[extraPassiveId]]--;
	
	partyMember->extraPassiveCount--;
	for (int i = extraPassiveId; i < partyMember->extraPassiveCount; i++) {
		partyMember->extraPassives[i] = partyMember->extraPassives[i + 1];
	}
	Party_Refresh(partyId);
}

void Profile_SwapPassive(int partyId, int extraPassiveId, int passiveId) {
	PartyMember* partyMember = &partyMembers[partyId];
	
	if (profile.passivesEquipped[passiveId] >= profile.passives[passiveId]) return;
	
	if (extraPassiveId >= partyMember->extraPassiveCount) return;
	
	int gpNew = profile.gp;
	gpNew += passiveData[partyMember->extraPassives[extraPassiveId]].cost;
	gpNew -= passiveData[passiveId].cost;
	if (gpNew < 0) return;
	
	for (int i = 0; i < partyMember->passiveCount; i++) {
		if (partyMember->passives[i] == passiveId) return;
	}
	
	profile.passivesEquipped[partyMember->extraPassives[extraPassiveId]]--;
	
	partyMember->extraPassives[extraPassiveId] = passiveId;
	profile.passivesEquipped[passiveId]++;
	Party_Refresh(partyId);
}



void Profile_InventoryPartyOrderAdd(int id) {
	for (int i = 0; i < 5; i++) {
		if (profile.partyOrder[i] < 0) {
			profile.partyOrder[i] = id;
			break;
		}
	}
}

void Profile_InventoryPartyOrderRemove(int id) {
	for (int i = 0; i < 5; i++) {
		if (profile.partyOrder[i] == id) {
			for (int j = i; j < 4; j++) {
				profile.partyOrder[j] = profile.partyOrder[j + 1];
			}
			profile.partyOrder[4] = -1;
			break;
		}
	}
}



void Profile_ItemAdd(int id) {
	profile.lastGotItemId = id;
	for (int i = 0; i < 16; i++) {
		if (profile.itemInventory[i] == 0) {
			profile.itemInventory[i] = id;
			break;
		}
	}
}

void Profile_ItemRemove(int inventoryId) {
	for (int i = inventoryId; i < 15; i++) {
		profile.itemInventory[i] = profile.itemInventory[i + 1];
	}
	profile.itemInventory[15] = 0;
}

void Profile_ClearItemInventory() {
	for (int i = 0; i < 16; i++) {
		profile.itemInventory[i] = 0;
	}
	for (int i = 0; i < 64; i++) {
		profile.keyItemInventory[i] = 0;
	}
}

bool Profile_ItemInventoryIsFull() {
	for (int i = 0; i < 16; i++) {
		if (profile.itemInventory[i] == 0)
			return false;
	}
	return true;
}

void Profile_KeyItemAdd(int id) {
	int i = 0;
	while (1) {
		if (profile.keyItemInventory[i] == 0) {
			profile.keyItemInventory[i] = id;
			profile.lastGotItemId = id;
			break;
		}
		i++;
	}
}

void Profile_KeyItemRemove(int id) {
	int inventoryId = -1;
	
	for (int i = 0; i < 64; i++) {
		if (profile.keyItemInventory[i] == id) {
			inventoryId = i;
			break;
		}
	}
	
	if (inventoryId < 0) return;
	
	for (int i = inventoryId; i < 63; i++) {
		profile.keyItemInventory[i] = profile.keyItemInventory[i + 1];
	}
	profile.keyItemInventory[63] = 0;
}

bool Profile_KeyItemExists(int id) {
	for (int i = 0; i < 64; i++) {
		if (profile.keyItemInventory[i] == id) {
			return true;
		}
	}
	return false;
}
