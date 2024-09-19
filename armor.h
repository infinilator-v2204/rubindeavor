#pragma once

typedef struct {
	char name[32];
	int cost;
	
	int headId;
	int bodyId;
	int actionAnimId;
	
	int hp;
	int mp;
	int attack;
	int defense;
	int speed;
	
	int passiveCount;
	int passives[32];
	
	int specialAbility;
	bool ranged;
} Armor;

extern Armor armorData[OBJECT_COUNT_MAX];

void LoadArmorData();
