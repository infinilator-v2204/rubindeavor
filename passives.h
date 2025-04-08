#pragma once

#include "battlesystem.h"

typedef struct {
	char name[32];
	char desc[128];
	int cost;
	bool stackable;
	bool immortal;
} Passive;

extern Passive passiveData[OBJECT_COUNT_MAX];

void LoadPassiveData();

void Passive_OnTurnStart(int passiveId, Fighter* fighter);
void Passive_OnSkillUse(int passiveId, Fighter* fighter);
void Passive_OnSkillEnd(int passiveId, Fighter* fighter);
void Passive_OnDealDamage(int passiveId, Fighter* fighter, Fighter* target, int* damagePointer, unsigned int* flagsPointer);
void Passive_OnTakeDamage(int passiveId, Fighter* fighter, Fighter* attacker, int* damagePointer, unsigned int* flagsPointer);
void Passive_OnTakeStatus(int passiveId, Fighter* fighter, Fighter* attacker, int* statusIdPointer, int* countPointer, int damageFlags);
void Passive_OnFighterDefeat(int passiveId, Fighter* fighter, Fighter* target);
