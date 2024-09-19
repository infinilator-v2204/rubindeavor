#pragma once

#include "party.h"

typedef struct {
	short actions[1000];
	short actionsEquipped[1000];
	short armors[1000];
	short armorsEquipped[1000];
	short passives[1000];
	short passivesEquipped[1000];
	
	int flags[1000];
	int tempFlags[1000];
	
	char party[5];
	char partyOrder[5];
	
	int cash;
	int itemInventory[16];
	int keyItemInventory[64];
	int gp;
	int gpMax;
	
	int lastGotItemId;
	
	bool gameBeaten;
	
	struct {
		bool exists;
		char party[5];
		int level;
	} saveFiles[16];
} Profile;

extern Profile profile;
extern Profile profileBuffer;

#include "profile_flags.h"

void fputc_short(int ch, FILE* stream);
void fputc_int(int ch, FILE* stream);
int fgetc_short(FILE* stream);
int fgetc_int(FILE* stream);
int SaveGame(const char* filename);
int LoadGame(const char* filename);
int SaveFileExists();
int SaveSaveData();
int LoadSaveData();

int Profile_SaveGameSlot(int id);
int Profile_LoadGameSlot(int id);
int Profile_DeleteGameSlot(int id);

void Profile_AddAction(int id, int count);
void Profile_AddArmor(int id, int count);
void Profile_EquipAction(int partyId, int actionId);
void Profile_UnequipAction(int partyId, int movesetId);
void Profile_SwapAction(int partyId, int movesetId, int actionId);
void Profile_EquipArmor(int partyId, int armorId);
void Profile_UnequipArmor(int partyId);
void Profile_EquipPassive(int partyId, int passiveId);
void Profile_UnequipPassive(int partyId, int extraPassiveId);
void Profile_SwapPassive(int partyId, int extraPassiveId, int passiveId);

void Profile_InventoryPartyOrderAdd(int id);
void Profile_InventoryPartyOrderRemove(int id);

void Profile_ItemAdd(int id);
void Profile_ItemRemove(int inventoryId);
void Profile_ClearItemInventory();
bool Profile_ItemInventoryIsFull();

void Profile_KeyItemAdd(int id);
void Profile_KeyItemRemove(int id);
bool Profile_KeyItemExists(int id);
