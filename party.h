#pragma once

typedef struct {
	char name[32];
	int id;
	bool inventoryUnlocked;
	int level;
	int exp;
	int expNext;
	
	int headId;
	int bodyId;
	int charId;
	
	int hp;
	int mp;
	int tiredThreshold;
	
	int hpDamage;
	int tiredness;
	int tiredLevel;
	
	int hpMax;
	int mpMax;
	int attack;
	int defense;
	int speed;
	
	struct {
		int hpMax;
		int mpMax;
		int attack;
		int defense;
		int speed;
	} starter;
	
	struct {
		int hpMax;
		int mpMax;
		int attack;
		int defense;
		int speed;
	} base;
	
	struct {
		int hpMax;
		int mpMax;
		int attack;
		int defense;
		int speed;
	} growth;
	
	int movesetCount;
	int moveset[16];
	
	int passiveCount;
	int passives[16];
	
	int extraPassiveCount;
	int extraPassives[16];
	
	int uniqueActionCount;
	int uniqueActions[32];
	int uniqueActionsEquipped[32];
	
	int armorId;
	int defaultArmorId;
} PartyMember;

extern PartyMember partyMembers[10];

void LoadPartyData();
void Party_UpdateCaterpillar();
void Party_Join(int id);
void Party_Leave(int id);
void Party_Refresh(int id);
bool Party_Exists(int id);
void Party_RefreshGemPoints();
int Party_CalculateArmorCost(int armorId);

void Party_InventoryLock(int id);
void Party_InventoryUnlock(int id);
void Party_SetExp(int id, int exp);
void Party_GainExp(int id, int exp);
void Party_SetLevel(int id, int level);
void Party_LevelUp(int id);
void Party_LearnAction(int id, int actionId);
void Party_UnlearnAction(int id, int actionId);
