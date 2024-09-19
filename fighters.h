#pragma once

typedef struct {
	char name[32];
	int exp;
	int cash;
	int rewardCount;
	struct {
		int type;
		int id;
		int rarity;
	} rewards[16];
	
	int headId;
	int bodyId;
	int charId;
	int collapseSpriteId;
	int actionAnimId;
	int ai;
	
	int hpMax;
	int mpMax;
	
	int attack;
	int defense;
	int speed;
	
	int movesetCount;
	int moveset[16];
	
	int passiveCount;
	int passives[32];
} FighterData;

extern FighterData fighterData[OBJECT_COUNT_MAX];

void LoadFighterData();

void FighterData_AddReward(FighterData* fighter, int type, int id, int rarity);
