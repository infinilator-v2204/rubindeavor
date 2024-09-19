#include "generic.h"
#include "party.h"
#include "overworld.h"
#include "sprites.h"
#include "profile.h"
#include "armor.h"
#include "passives.h"

PartyMember partyMembers[10];

void LoadPartyData() {
	for (int i = 0; i < 10; i++) {
		PartyMember* partyMember = &partyMembers[i];
		
		partyMember->hpDamage = 0;
		partyMember->tiredness = 0;
		partyMember->tiredLevel = 0;
	}
	
	PartyMember* partyMember;
	
	
	
	partyMember = &partyMembers[0];
	SetString(partyMember->name, "Ruby");
	partyMember->id = 0;
	partyMember->inventoryUnlocked = 0;
	partyMember->level = 0;
	partyMember->exp = 0;
	partyMember->expNext = 0;
	partyMember->headId = 1;
	partyMember->bodyId = 1;
	partyMember->charId = 1;
	partyMember->tiredThreshold = 280;
	partyMember->hp = 0;
	partyMember->mp = 0;
	partyMember->hpMax = 0;
	partyMember->mpMax = 0;
	partyMember->attack = 0;
	partyMember->defense = 0;
	partyMember->speed = 0;
	partyMember->base.hpMax = 0;
	partyMember->base.mpMax = 0;
	partyMember->base.attack = 0;
	partyMember->base.defense = 0;
	partyMember->base.speed = 0;
	
	partyMember->starter.hpMax = 10;
	partyMember->starter.mpMax = 5;
	partyMember->starter.attack = 4;
	partyMember->starter.defense = 0;
	partyMember->starter.speed = 5;
	
	partyMember->growth.hpMax = 96;
	partyMember->growth.mpMax = 48;
	partyMember->growth.attack = 27;
	partyMember->growth.defense = 4;
	partyMember->growth.speed = 28;
	
	partyMember->movesetCount = 0;
	partyMember->passiveCount = 0;
	partyMember->extraPassiveCount = 0;
	partyMember->armorId = 0;
	partyMember->defaultArmorId = 1;
	partyMember->uniqueActionCount = 0;
	
	
	
	partyMember = &partyMembers[1];
	SetString(partyMember->name, "Noah");
	partyMember->id = 0;
	partyMember->inventoryUnlocked = 0;
	partyMember->level = 0;
	partyMember->exp = 0;
	partyMember->expNext = 0;
	partyMember->headId = 2;
	partyMember->bodyId = 3;
	partyMember->charId = 2;
	partyMember->tiredThreshold = 140;
	partyMember->hp = 0;
	partyMember->mp = 0;
	partyMember->hpMax = 0;
	partyMember->mpMax = 0;
	partyMember->attack = 0;
	partyMember->defense = 0;
	partyMember->speed = 0;
	partyMember->base.hpMax = 0;
	partyMember->base.mpMax = 0;
	partyMember->base.attack = 0;
	partyMember->base.defense = 0;
	partyMember->base.speed = 0;
	
	partyMember->starter.hpMax = 10;
	partyMember->starter.mpMax = 5;
	partyMember->starter.attack = 3;
	partyMember->starter.defense = 0;
	partyMember->starter.speed = 3;
	
	partyMember->growth.hpMax = 64;
	partyMember->growth.mpMax = 32;
	partyMember->growth.attack = 16;
	partyMember->growth.defense = 2;
	partyMember->growth.speed = 17;
	
	partyMember->movesetCount = 0;
	partyMember->passiveCount = 0;
	partyMember->extraPassiveCount = 0;
	partyMember->armorId = 0;
	partyMember->defaultArmorId = 2;
	partyMember->uniqueActionCount = 0;
	
	
	
	partyMember = &partyMembers[2];
	SetString(partyMember->name, "Emmet");
	partyMember->id = 0;
	partyMember->inventoryUnlocked = 0;
	partyMember->level = 0;
	partyMember->exp = 0;
	partyMember->expNext = 0;
	partyMember->headId = 3;
	partyMember->bodyId = 4;
	partyMember->charId = 3;
	partyMember->tiredThreshold = 230;
	partyMember->hp = 0;
	partyMember->mp = 0;
	partyMember->hpMax = 0;
	partyMember->mpMax = 0;
	partyMember->attack = 0;
	partyMember->defense = 0;
	partyMember->speed = 0;
	partyMember->base.hpMax = 0;
	partyMember->base.mpMax = 0;
	partyMember->base.attack = 0;
	partyMember->base.defense = 0;
	partyMember->base.speed = 0;
	
	partyMember->starter.hpMax = 10;
	partyMember->starter.mpMax = 5;
	partyMember->starter.attack = 3;
	partyMember->starter.defense = 0;
	partyMember->starter.speed = 8;
	
	partyMember->growth.hpMax = 61;
	partyMember->growth.mpMax = 52;
	partyMember->growth.attack = 20;
	partyMember->growth.defense = 0;
	partyMember->growth.speed = 22;
	
	partyMember->movesetCount = 0;
	partyMember->passiveCount = 0;
	partyMember->extraPassiveCount = 0;
	partyMember->armorId = 0;
	partyMember->defaultArmorId = 3;
	partyMember->uniqueActionCount = 0;
	
	
	
	partyMember = &partyMembers[3];
	SetString(partyMember->name, "Sally");
	partyMember->id = 0;
	partyMember->inventoryUnlocked = 0;
	partyMember->level = 0;
	partyMember->exp = 0;
	partyMember->expNext = 0;
	partyMember->headId = 4;
	partyMember->bodyId = 5;
	partyMember->charId = 4;
	partyMember->tiredThreshold = 180;
	partyMember->hp = 0;
	partyMember->mp = 0;
	partyMember->hpMax = 0;
	partyMember->mpMax = 0;
	partyMember->attack = 0;
	partyMember->defense = 0;
	partyMember->speed = 0;
	partyMember->base.hpMax = 0;
	partyMember->base.mpMax = 0;
	partyMember->base.attack = 0;
	partyMember->base.defense = 0;
	partyMember->base.speed = 0;
	
	partyMember->starter.hpMax = 10;
	partyMember->starter.mpMax = 5;
	partyMember->starter.attack = 5;
	partyMember->starter.defense = 0;
	partyMember->starter.speed = 4;
	
	partyMember->growth.hpMax = 106;
	partyMember->growth.mpMax = 22;
	partyMember->growth.attack = 26;
	partyMember->growth.defense = 0;
	partyMember->growth.speed = 12;
	
	partyMember->movesetCount = 0;
	partyMember->passiveCount = 0;
	partyMember->extraPassiveCount = 0;
	partyMember->armorId = 0;
	partyMember->defaultArmorId = 13;
	partyMember->uniqueActionCount = 0;
	
	
	
	partyMember = &partyMembers[4];
	SetString(partyMember->name, "Diego");
	partyMember->id = 0;
	partyMember->inventoryUnlocked = 0;
	partyMember->level = 0;
	partyMember->exp = 0;
	partyMember->expNext = 0;
	partyMember->headId = 1;
	partyMember->bodyId = 1;
	partyMember->charId = 1;
	partyMember->tiredThreshold = 260;
	partyMember->hp = 0;
	partyMember->mp = 0;
	partyMember->hpMax = 0;
	partyMember->mpMax = 0;
	partyMember->attack = 0;
	partyMember->defense = 0;
	partyMember->speed = 0;
	partyMember->base.hpMax = 0;
	partyMember->base.mpMax = 0;
	partyMember->base.attack = 0;
	partyMember->base.defense = 0;
	partyMember->base.speed = 0;
	
	partyMember->starter.hpMax = 12;
	partyMember->starter.mpMax = 6;
	partyMember->starter.attack = 7;
	partyMember->starter.defense = 0;
	partyMember->starter.speed = 7;
	
	partyMember->growth.hpMax = 92;
	partyMember->growth.mpMax = 48;
	partyMember->growth.attack = 24;
	partyMember->growth.defense = 4;
	partyMember->growth.speed = 25;
	
	partyMember->movesetCount = 0;
	partyMember->passiveCount = 0;
	partyMember->extraPassiveCount = 0;
	partyMember->armorId = 0;
	partyMember->defaultArmorId = 5;
	partyMember->uniqueActionCount = 0;
	
	
	
	partyMember = &partyMembers[5];
	SetString(partyMember->name, "Tony");
	partyMember->id = 0;
	partyMember->inventoryUnlocked = 0;
	partyMember->level = 0;
	partyMember->exp = 0;
	partyMember->expNext = 0;
	partyMember->headId = 1;
	partyMember->bodyId = 1;
	partyMember->charId = 1;
	partyMember->tiredThreshold = 200;
	partyMember->hp = 0;
	partyMember->mp = 0;
	partyMember->hpMax = 0;
	partyMember->mpMax = 0;
	partyMember->attack = 0;
	partyMember->defense = 0;
	partyMember->speed = 0;
	partyMember->base.hpMax = 0;
	partyMember->base.mpMax = 0;
	partyMember->base.attack = 0;
	partyMember->base.defense = 0;
	partyMember->base.speed = 0;
	
	partyMember->starter.hpMax = 10;
	partyMember->starter.mpMax = 5;
	partyMember->starter.attack = 3;
	partyMember->starter.defense = 0;
	partyMember->starter.speed = 4;
	
	partyMember->growth.hpMax = 75;
	partyMember->growth.mpMax = 25;
	partyMember->growth.attack = 18;
	partyMember->growth.defense = 1;
	partyMember->growth.speed = 20;
	
	partyMember->movesetCount = 0;
	partyMember->passiveCount = 0;
	partyMember->extraPassiveCount = 0;
	partyMember->armorId = 0;
	partyMember->defaultArmorId = 6;
	partyMember->uniqueActionCount = 0;
	
	
	
	partyMember = &partyMembers[6];
	SetString(partyMember->name, "Perry");
	partyMember->id = 0;
	partyMember->inventoryUnlocked = 0;
	partyMember->level = 0;
	partyMember->exp = 0;
	partyMember->expNext = 0;
	partyMember->headId = 7;
	partyMember->bodyId = 8;
	partyMember->charId = 7;
	partyMember->tiredThreshold = 150;
	partyMember->hp = 0;
	partyMember->mp = 0;
	partyMember->hpMax = 0;
	partyMember->mpMax = 0;
	partyMember->attack = 0;
	partyMember->defense = 0;
	partyMember->speed = 0;
	partyMember->base.hpMax = 0;
	partyMember->base.mpMax = 0;
	partyMember->base.attack = 0;
	partyMember->base.defense = 0;
	partyMember->base.speed = 0;
	
	partyMember->starter.hpMax = 10;
	partyMember->starter.mpMax = 4;
	partyMember->starter.attack = 2;
	partyMember->starter.defense = 0;
	partyMember->starter.speed = 2;
	
	partyMember->growth.hpMax = 35;
	partyMember->growth.mpMax = 20;
	partyMember->growth.attack = 11;
	partyMember->growth.defense = 0;
	partyMember->growth.speed = 10;
	
	partyMember->movesetCount = 0;
	partyMember->passiveCount = 0;
	partyMember->extraPassiveCount = 0;
	partyMember->armorId = 0;
	partyMember->defaultArmorId = 7;
	partyMember->uniqueActionCount = 0;
	
	
	
	for (int i = 0; i < 7; i++) {
		Party_SetLevel(i, 0);
		Party_Refresh(i);
	}
}

void Party_UpdateCaterpillar() {
	for (int i = 0; i < 5; i++) {
		OverworldObject* object = &overworld.objects[i];
		
		if (profile.party[i] < 0) {
			object->spriteId = -1;
			object->climbSpriteId = -1;
			continue;
		}
		
		switch (profile.party[i]) {
			case 0:
				if (overworld.overlayId == 2) break;
				object->spriteId = (profile.flags[FLAG_RUBY_LABCOAT]) ? SPR_owchar_ruby : SPR_owchar_ruby_zero;
				object->climbSpriteId = SPR_owchar_climb_ruby;
				break;
			case 1:
				object->spriteId = SPR_owchar_noah;
				object->climbSpriteId = SPR_owchar_climb_noah;
				break;
			case 2:
				object->spriteId = SPR_owchar_emmet;
				object->climbSpriteId = SPR_owchar_climb_emmet;
				break;
			case 3:
				object->spriteId = SPR_owchar_sally;
				object->climbSpriteId = SPR_owchar_climb_sally;
				break;
			
			case 6:
				object->spriteId = SPR_owchar_perry;
				object->climbSpriteId = SPR_owchar_climb_perry;
				break;
		}
		
		if (overworld.player.dashChargeTimer >= 50 && profile.party[i] == 0) {
			object->spriteId += 2;
		}
		else if (overworld.player.dashChargeTimer >= 1 && profile.party[i] == 0) {
			object->spriteId++;
		}
		else if (overworld.player.dashing || overworld.player.dashChargeTimer >= 50) {
			object->spriteId++;
		}
		
		OverworldObject_ChangeSpriteId(i, object->spriteId);
	}
}

void Party_Join(int id) {
	for (int i = 0; i < 5; i++) {
		if (profile.party[i] >= 0) continue;
		
		profile.party[i] = id;
		break;
	}
	Party_UpdateCaterpillar();
}

void Party_Leave(int id) {
	for (int i = 0; i < 5; i++) {
		if (profile.party[i] != id) continue;
		
		for (int j = i; j < 4; j++) {
			profile.party[j] = profile.party[j + 1];
		}
		profile.party[4] = -1;
		break;
	}
	Party_UpdateCaterpillar();
}

void Party_Refresh(int id) {
	PartyMember* partyMember = &partyMembers[id];
	Armor* armor;
	if (partyMember->armorId == 0)
		armor = &armorData[partyMember->defaultArmorId];
	else
		armor = &armorData[partyMember->armorId];
	
	partyMember->bodyId = armor->bodyId;
	partyMember->base.hpMax = partyMember->starter.hpMax + (int)(partyMember->level * partyMember->growth.hpMax / 48);
	partyMember->base.mpMax = partyMember->starter.mpMax + (int)(partyMember->level * partyMember->growth.mpMax / 48);
	partyMember->base.attack = partyMember->starter.attack + (int)(partyMember->level * partyMember->growth.attack / 112);
	partyMember->base.defense = partyMember->starter.defense + (int)(partyMember->level * partyMember->growth.defense / 192);
	partyMember->base.speed = partyMember->starter.speed + (int)(partyMember->level * partyMember->growth.speed / 56);
	
	if (id == 0) {
		if (profile.flags[FLAG_RUBY_ALONE_STATBOOST]) {
			profile.flags[FLAG_RUBY_ALONE_STATBOOST_LEVEL] = partyMember->level;
		}
		
		if (profile.flags[FLAG_RUBY_ALONE_STATBOOST_LEVEL] >= 1) {
			partyMember->base.hpMax += (int)(profile.flags[FLAG_RUBY_ALONE_STATBOOST_LEVEL] * partyMember->growth.hpMax / 48) / 2;
			partyMember->base.mpMax += (int)(profile.flags[FLAG_RUBY_ALONE_STATBOOST_LEVEL] * partyMember->growth.mpMax / 48) / 2;
			partyMember->base.attack += (int)(profile.flags[FLAG_RUBY_ALONE_STATBOOST_LEVEL] * partyMember->growth.attack / 112) / 2;
			partyMember->base.defense += (int)(profile.flags[FLAG_RUBY_ALONE_STATBOOST_LEVEL] * partyMember->growth.defense / 192) / 2;
			partyMember->base.speed += (int)(profile.flags[FLAG_RUBY_ALONE_STATBOOST_LEVEL] * partyMember->growth.speed / 56) / 2;
		}
	}
	
	partyMember->hpMax = partyMember->base.hpMax + armor->hp;
	partyMember->mpMax = partyMember->base.mpMax + armor->mp;
	partyMember->attack = partyMember->base.attack + armor->attack;
	partyMember->defense = partyMember->base.defense + armor->defense;
	partyMember->speed = partyMember->base.speed + armor->speed;
	
	partyMember->passiveCount = armor->passiveCount;
	for (int i = 0; i < partyMember->passiveCount; i++) {
		partyMember->passives[i] = armor->passives[i];
	}
	
	for (int i = 0; i < partyMember->extraPassiveCount; i++) {
		partyMember->passives[partyMember->passiveCount++] = partyMember->extraPassives[i];
	}
	Party_RefreshGemPoints();
}

bool Party_Exists(int id) {
	for (int i = 0; i < 5; i++) {
		if (profile.party[i] == id) {
			return true;
		}
	}
	return false;
}

void Party_RefreshGemPoints() {
	profile.gpMax = 10;
	if (Profile_KeyItemExists(251)) profile.gpMax += 15;
	if (Profile_KeyItemExists(252)) profile.gpMax += 20;
	if (Profile_KeyItemExists(253)) profile.gpMax += 25;
	if (Profile_KeyItemExists(254)) profile.gpMax += 30;
	if (Profile_KeyItemExists(250)) profile.gpMax += 40;
	profile.gp = profile.gpMax;
	
	for (int i = 0; i < 10; i++) {
		PartyMember* partyMember = &partyMembers[i];
		if (partyMember->armorId != 0) {
			profile.gp -= armorData[partyMember->armorId].cost;
		}
		for (int j = 0; j < partyMember->passiveCount; j++) {
			if (partyMember->armorId == 0 && j < armorData[partyMember->defaultArmorId].passiveCount) continue;
			profile.gp -= passiveData[partyMember->passives[j]].cost;
		}
	}
}

int Party_CalculateArmorCost(int armorId) {
	Armor* armor = &armorData[armorId];
	
	int cost = armor->cost;
	for (int i = 0; i < armor->passiveCount; i++) {
		cost += passiveData[armor->passives[i]].cost;
	}
	return cost;
}



void Party_InventoryLock(int id) {
	PartyMember* partyMember = &partyMembers[id];
	
	partyMember->inventoryUnlocked = false;
}

void Party_InventoryUnlock(int id) {
	PartyMember* partyMember = &partyMembers[id];
	
	partyMember->inventoryUnlocked = true;
}

void Party_SetExp(int id, int exp) {
	PartyMember* partyMember = &partyMembers[id];
	
	Party_SetLevel(id, 0);
	partyMember->exp = exp;
	
	int c = 0;
	while (partyMember->exp >= partyMember->expNext && c++ < 500) {
		Party_LevelUp(id);
	}
}

void Party_GainExp(int id, int exp) {
	PartyMember* partyMember = &partyMembers[id];
	
	partyMember->exp += exp;
	
	int c = 0;
	while (partyMember->exp >= partyMember->expNext && c++ < 500) {
		Party_LevelUp(id);
	}
}

void Party_SetLevel(int id, int level) {
	PartyMember* partyMember = &partyMembers[id];
	
	partyMember->level = level;
	partyMember->expNext = 1;
	for (int i = 1; i <= level; i++) {
		partyMember->expNext += (int)pow(5, 0.6 + ((float)i / 18)) + i * 3;
		//partyMember->expNext += (int)pow(5, 0.6 + ((float)i / 15)) + i * 2;
	}
	
	Party_Refresh(id);
}

void Party_LevelUp(int id) {
	PartyMember* partyMember = &partyMembers[id];
	
	Party_SetLevel(id, partyMember->level + 1);
}

void Party_LearnAction(int id, int actionId) {
	PartyMember* partyMember = &partyMembers[id];
	
	partyMember->uniqueActions[partyMember->uniqueActionCount] = actionId;
	partyMember->uniqueActionsEquipped[partyMember->uniqueActionCount] = 0;
	partyMember->uniqueActionCount++;
}

void Party_UnlearnAction(int id, int actionId) {
	PartyMember* partyMember = &partyMembers[id];
	
	for (int i = 0; i < partyMember->uniqueActionCount; i++) {
		if (partyMember->uniqueActions[i] != actionId) continue;
		
		for (int j = i; j < --partyMember->uniqueActionCount; j++) {
			partyMember->uniqueActions[j] = partyMember->uniqueActions[j + 1];
			partyMember->uniqueActionsEquipped[j] = partyMember->uniqueActionsEquipped[j + 1];
		}
		break;
	}
}
