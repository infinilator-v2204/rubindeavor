#include "generic.h"
#include "fighters.h"
#include "sprites.h"

FighterData fighterData[OBJECT_COUNT_MAX];

void LoadFighterData() {
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		fighterData[i].collapseSpriteId = -1;
		fighterData[i].rewardCount = 0;
	}
	
	FighterData* fighter;
	
	
	
	fighter = &fighterData[0];
	SetString(fighter->name, "Nobody");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 0;
	fighter->bodyId = 0;
	fighter->charId = 0;
	fighter->actionAnimId = 0;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 0;
	fighter->mpMax = 0;
	
	fighter->attack = 0;
	fighter->defense = 0;
	fighter->speed = 0;
	
	fighter->movesetCount = 0;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[1];
	SetString(fighter->name, "Ruby");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 1;
	fighter->bodyId = 1;
	fighter->charId = 1;
	fighter->collapseSpriteId = SPR_owchar_collapse_ruby;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 10;
	fighter->mpMax = 5;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 5;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[2];
	SetString(fighter->name, "Noah");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 1;
	fighter->bodyId = 1;
	fighter->charId = 1;
	fighter->collapseSpriteId = SPR_owchar_collapse_noah;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 10;
	fighter->mpMax = 5;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 5;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[3];
	SetString(fighter->name, "Emmet");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 1;
	fighter->bodyId = 1;
	fighter->charId = 1;
	fighter->collapseSpriteId = SPR_owchar_collapse_emmet;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 10;
	fighter->mpMax = 5;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 5;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[4];
	SetString(fighter->name, "Sally");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 1;
	fighter->bodyId = 1;
	fighter->charId = 1;
	fighter->collapseSpriteId = SPR_owchar_collapse_sally;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 10;
	fighter->mpMax = 5;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 5;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[7];
	SetString(fighter->name, "Perry");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 1;
	fighter->bodyId = 1;
	fighter->charId = 1;
	fighter->collapseSpriteId = SPR_owchar_collapse_perry;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 10;
	fighter->mpMax = 5;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 5;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[10];
	SetString(fighter->name, "Rubin");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 1;
	fighter->bodyId = 1;
	fighter->charId = 1;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 66666;
	fighter->mpMax = 66666;
	
	fighter->attack = 6666;
	fighter->defense = 0;
	fighter->speed = 6666;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	
	
	
	fighter = &fighterData[11];
	SetString(fighter->name, "Hobo");
	fighter->exp = 2;
	fighter->cash = 1;
	FighterData_AddReward(fighter, 1, 11, 0);
	
	fighter->headId = 11;
	fighter->bodyId = 11;
	fighter->charId = 11;
	fighter->actionAnimId = 1;
	fighter->ai = 1;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 8;
	fighter->mpMax = 2;
	
	fighter->attack = 2;
	fighter->defense = 0;
	fighter->speed = 8;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[12];
	SetString(fighter->name, "Navy Gang");
	fighter->exp = 3;
	fighter->cash = 2;
	FighterData_AddReward(fighter, 1, 12, 0);
	FighterData_AddReward(fighter, 0, 2, 0);
	
	fighter->headId = 27;
	fighter->bodyId = 12;
	fighter->charId = 12;
	fighter->actionAnimId = 1;
	fighter->ai = 2;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 10;
	fighter->mpMax = 2;
	
	fighter->attack = 2;
	fighter->defense = 0;
	fighter->speed = 10;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 2;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[13];
	SetString(fighter->name, "Sally");
	fighter->exp = 10;
	fighter->cash = 8;
	FighterData_AddReward(fighter, 1, 13, 0);
	FighterData_AddReward(fighter, 0, 3, 0);
	
	fighter->headId = 4;
	fighter->bodyId = 5;
	fighter->charId = 4;
	fighter->actionAnimId = 2;
	fighter->ai = 7;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 17;
	fighter->mpMax = 6;
	
	fighter->attack = 6;
	fighter->defense = 0;
	fighter->speed = 9;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 2;
	fighter->moveset[2] = 3;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 2;
	
	
	
	fighter = &fighterData[14];
	SetString(fighter->name, "Leaf Crew");
	fighter->exp = 18;
	fighter->cash = 8;
	FighterData_AddReward(fighter, 1, 14, 1);
	FighterData_AddReward(fighter, 0, 5, 1);
	FighterData_AddReward(fighter, 0, 6, 1);
	FighterData_AddReward(fighter, 0, 7, 1);
	
	fighter->headId = 12;
	fighter->bodyId = 13;
	fighter->charId = 13;
	fighter->actionAnimId = 2;
	fighter->ai = 14;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 24;
	fighter->mpMax = 8;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 13;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 7;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 3;
	
	
	
	fighter = &fighterData[15];
	SetString(fighter->name, "Lisao");
	fighter->exp = 180;
	fighter->cash = 50;
	FighterData_AddReward(fighter, 1, 15, 0);
	FighterData_AddReward(fighter, 0, 9, 0);
	FighterData_AddReward(fighter, 0, 10, 0);
	FighterData_AddReward(fighter, 0, 11, 0);
	
	fighter->headId = 15;
	fighter->bodyId = 14;
	fighter->charId = 14;
	fighter->actionAnimId = 4;
	fighter->ai = 9;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 140;
	fighter->mpMax = 50;
	
	fighter->attack = 11;
	fighter->defense = 0;
	fighter->speed = 12;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 9;
	fighter->moveset[1] = 10;
	fighter->moveset[2] = 11;
	fighter->moveset[3] = 7;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 4;
	fighter->passives[1] = 3;
	
	
	
	fighter = &fighterData[16];
	SetString(fighter->name, "Lulu");
	fighter->exp = 24;
	fighter->cash = 15;
	FighterData_AddReward(fighter, 1, 16, 0);
	FighterData_AddReward(fighter, 0, 4, 0);
	
	fighter->headId = 16;
	fighter->bodyId = 15;
	fighter->charId = 15;
	fighter->actionAnimId = 1;
	fighter->ai = 3;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 24;
	fighter->mpMax = 10;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 17;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 4;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 5;
	
	
	
	fighter = &fighterData[17];
	SetString(fighter->name, "Blazin' Lulu");
	fighter->exp = 80;
	fighter->cash = 30;
	FighterData_AddReward(fighter, 1, 17, 0);
	FighterData_AddReward(fighter, 0, 18, 0);
	FighterData_AddReward(fighter, 0, 6, 0);
	FighterData_AddReward(fighter, 0, 20, 0);
	
	fighter->headId = 16;
	fighter->bodyId = 16;
	fighter->charId = 16;
	fighter->actionAnimId = 19;
	fighter->ai = 4;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 60;
	fighter->mpMax = 30;
	
	fighter->attack = 17;
	fighter->defense = 0;
	fighter->speed = 20;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 18;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 20;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
	
	
	
	fighter = &fighterData[18];
	SetString(fighter->name, "Police");
	fighter->exp = 35;
	fighter->cash = 10;
	FighterData_AddReward(fighter, 1, 18, 1);
	FighterData_AddReward(fighter, 0, 5, 2);
	FighterData_AddReward(fighter, 0, 6, 2);
	FighterData_AddReward(fighter, 0, 26, 0);
	FighterData_AddReward(fighter, 0, 49, 1);
	
	fighter->headId = 17;
	fighter->bodyId = 17;
	fighter->charId = 17;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 45;
	fighter->mpMax = 15;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 14;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 26;
	fighter->moveset[3] = 49;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[19];
	SetString(fighter->name, "Farmer");
	FighterData_AddReward(fighter, 1, 19, 1);
	FighterData_AddReward(fighter, 0, 5, 1);
	fighter->exp = 8;
	fighter->cash = 3;
	
	fighter->headId = 19;
	fighter->bodyId = 18;
	fighter->charId = 18;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 18;
	fighter->mpMax = 5;
	
	fighter->attack = 6;
	fighter->defense = 0;
	fighter->speed = 8;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 5;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[20];
	SetString(fighter->name, "Knife Thug");
	FighterData_AddReward(fighter, 1, 20, 1);
	FighterData_AddReward(fighter, 0, 5, 1);
	FighterData_AddReward(fighter, 0, 6, 1);
	fighter->exp = 16;
	fighter->cash = 4;
	
	fighter->headId = 11;
	fighter->bodyId = 19;
	fighter->charId = 19;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 22;
	fighter->mpMax = 6;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 11;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[21];
	SetString(fighter->name, "Vandal B");
	FighterData_AddReward(fighter, 1, 21, 1);
	FighterData_AddReward(fighter, 0, 26, 1);
	fighter->exp = 28;
	fighter->cash = 10;
	
	fighter->headId = 20;
	fighter->bodyId = 20;
	fighter->charId = 20;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 30;
	fighter->mpMax = 11;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 15;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 2;
	fighter->moveset[2] = 3;
	fighter->moveset[3] = 201;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 6;
	
	
	
	fighter = &fighterData[22];
	SetString(fighter->name, "Vandal F");
	FighterData_AddReward(fighter, 1, 22, 1);
	fighter->exp = 28;
	fighter->cash = 10;
	
	fighter->headId = 21;
	fighter->bodyId = 21;
	fighter->charId = 21;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 32;
	fighter->mpMax = 10;
	
	fighter->attack = 14;
	fighter->defense = 0;
	fighter->speed = 12;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 2;
	fighter->moveset[2] = 26;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 6;
	
	
	
	fighter = &fighterData[23];
	SetString(fighter->name, "Nurse");
	FighterData_AddReward(fighter, 1, 23, 1);
	FighterData_AddReward(fighter, 0, 27, 1);
	fighter->exp = 20;
	fighter->cash = 12;
	
	fighter->headId = 22;
	fighter->bodyId = 22;
	fighter->charId = 22;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 25;
	fighter->mpMax = 12;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 11;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 27;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 8;
	
	
	
	fighter = &fighterData[24];
	SetString(fighter->name, "Jackie");
	FighterData_AddReward(fighter, 1, 24, 0);
	FighterData_AddReward(fighter, 0, 30, 0);
	FighterData_AddReward(fighter, 0, 31, 0);
	FighterData_AddReward(fighter, 0, 32, 0);
	fighter->exp = 64;
	fighter->cash = 30;
	
	fighter->headId = 23;
	fighter->bodyId = 23;
	fighter->charId = 23;
	fighter->actionAnimId = 1;
	fighter->ai = 24;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 60;
	fighter->mpMax = 20;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 25;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 30;
	fighter->moveset[2] = 31;
	fighter->moveset[3] = 32;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 9;
	
	
	
	fighter = &fighterData[25];
	SetString(fighter->name, "Electra");
	FighterData_AddReward(fighter, 1, 25, 0);
	FighterData_AddReward(fighter, 0, 33, 0);
	FighterData_AddReward(fighter, 0, 34, 0);
	fighter->exp = 55;
	fighter->cash = 22;
	
	fighter->headId = 24;
	fighter->bodyId = 24;
	fighter->charId = 24;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 45;
	fighter->mpMax = 24;
	
	fighter->attack = 14;
	fighter->defense = 0;
	fighter->speed = 13;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 33;
	fighter->moveset[2] = 34;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 10;
	
	
	
	fighter = &fighterData[26];
	SetString(fighter->name, "Ray");
	FighterData_AddReward(fighter, 1, 26, 0);
	FighterData_AddReward(fighter, 0, 35, 0);
	fighter->exp = 55;
	fighter->cash = 15;
	
	fighter->headId = 25;
	fighter->bodyId = 25;
	fighter->charId = 25;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 48;
	fighter->mpMax = 20;
	
	fighter->attack = 12;
	fighter->defense = 0;
	fighter->speed = 20;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 6;
	fighter->moveset[1] = 35;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 11;
	
	
	
	fighter = &fighterData[27];
	SetString(fighter->name, "Blazin' Lulu");
	FighterData_AddReward(fighter, 0, 19, 0);
	fighter->exp = 250;
	fighter->cash = 70;
	
	fighter->headId = 16;
	fighter->bodyId = 16;
	fighter->charId = 16;
	fighter->actionAnimId = 19;
	fighter->ai = 4;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 120;
	fighter->mpMax = 55;
	
	fighter->attack = 27;
	fighter->defense = 0;
	fighter->speed = 33;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 18;
	fighter->moveset[1] = 19;
	fighter->moveset[2] = 20;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
	
	
	
	fighter = &fighterData[28];
	SetString(fighter->name, "Omega Lulu");
	FighterData_AddReward(fighter, 1, 27, 0);
	FighterData_AddReward(fighter, 0, 18, 0);
	FighterData_AddReward(fighter, 0, 19, 0);
	FighterData_AddReward(fighter, 0, 17, 0);
	FighterData_AddReward(fighter, 0, 20, 0);
	fighter->exp = 1500;
	fighter->cash = 700;
	
	fighter->headId = 16;
	fighter->bodyId = 26;
	fighter->charId = 26;
	fighter->collapseSpriteId = SPR_owchar_collapse_lulu_omega;
	fighter->actionAnimId = 19;
	fighter->ai = 5;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 200;
	fighter->mpMax = 180;
	
	fighter->attack = 38;
	fighter->defense = 0;
	fighter->speed = 45;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 18;
	fighter->moveset[1] = 19;
	fighter->moveset[2] = 17;
	fighter->moveset[3] = 20;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
	
	
	
	fighter = &fighterData[29];
	SetString(fighter->name, "Leaf Crew");
	fighter->exp = 22;
	fighter->cash = 8;
	FighterData_AddReward(fighter, 1, 14, 0);
	FighterData_AddReward(fighter, 0, 5, 1);
	FighterData_AddReward(fighter, 0, 7, 1);
	FighterData_AddReward(fighter, 0, 8, 0);
	
	fighter->headId = 13;
	fighter->bodyId = 13;
	fighter->charId = 13;
	fighter->actionAnimId = 2;
	fighter->ai = 29;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 26;
	fighter->mpMax = 11;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 13;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 7;
	fighter->moveset[2] = 8;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 3;
	
	
	
	fighter = &fighterData[30];
	SetString(fighter->name, "Slime");
	fighter->exp = 8;
	fighter->cash = 1;
	FighterData_AddReward(fighter, 1, 49, 4);
	FighterData_AddReward(fighter, 0, 12, 1);
	
	fighter->headId = 0;
	fighter->bodyId = 27;
	fighter->charId = 27;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 15;
	fighter->mpMax = 6;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 14;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 12;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[31];
	SetString(fighter->name, "Huge Slime");
	fighter->exp = 50;
	fighter->cash = 4;
	FighterData_AddReward(fighter, 1, 49, 3);
	FighterData_AddReward(fighter, 0, 12, 0);
	FighterData_AddReward(fighter, 0, 13, 0);
	
	fighter->headId = 0;
	fighter->bodyId = 28;
	fighter->charId = 28;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 60;
	fighter->mpMax = 16;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 11;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 12;
	fighter->moveset[2] = 13;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 12;
	
	
	
	fighter = &fighterData[32];
	SetString(fighter->name, "Leaf Crew");
	fighter->exp = 72;
	fighter->cash = 8;
	FighterData_AddReward(fighter, 1, 14, 1);
	FighterData_AddReward(fighter, 0, 5, 1);
	FighterData_AddReward(fighter, 0, 6, 1);
	FighterData_AddReward(fighter, 0, 7, 1);
	
	fighter->headId = 14;
	fighter->bodyId = 13;
	fighter->charId = 13;
	fighter->actionAnimId = 2;
	fighter->ai = 32;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 24;
	fighter->mpMax = 8;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 13;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 7;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 3;
	
	
	
	fighter = &fighterData[33];
	SetString(fighter->name, "Dia");
	fighter->exp = 800;
	fighter->cash = 100;
	FighterData_AddReward(fighter, 1, 28, 0);
	FighterData_AddReward(fighter, 0, 14, 0);
	FighterData_AddReward(fighter, 0, 15, 0);
	FighterData_AddReward(fighter, 0, 16, 0);
	
	fighter->headId = 29;
	fighter->bodyId = 29;
	fighter->charId = 29;
	fighter->collapseSpriteId = SPR_owchar_collapse_dia;
	fighter->actionAnimId = 18;
	fighter->ai = 33;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 400;
	fighter->mpMax = 150;
	
	fighter->attack = 20;
	fighter->defense = 0;
	fighter->speed = 24;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 14;
	fighter->moveset[1] = 15;
	fighter->moveset[2] = 16;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 13;
	fighter->passives[1] = 14;
	
	
	
	fighter = &fighterData[34];
	SetString(fighter->name, "Spider");
	fighter->exp = 25;
	fighter->cash = 1;
	FighterData_AddReward(fighter, 1, 50, 4);
	FighterData_AddReward(fighter, 0, 21, 1);
	FighterData_AddReward(fighter, 0, 22, 2);
	
	fighter->headId = 0;
	fighter->bodyId = 30;
	fighter->charId = 30;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 20;
	fighter->mpMax = 20;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 19;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 21;
	fighter->moveset[1] = 22;
	fighter->moveset[2] = 24;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[35];
	SetString(fighter->name, "Spider Titan");
	fighter->exp = 300;
	fighter->cash = 15;
	FighterData_AddReward(fighter, 1, 50, 3);
	FighterData_AddReward(fighter, 0, 21, 0);
	FighterData_AddReward(fighter, 0, 22, 0);
	FighterData_AddReward(fighter, 0, 23, 0);
	
	fighter->headId = 0;
	fighter->bodyId = 31;
	fighter->charId = 31;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 220;
	fighter->mpMax = 80;
	
	fighter->attack = 30;
	fighter->defense = 0;
	fighter->speed = 15;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 21;
	fighter->moveset[1] = 22;
	fighter->moveset[2] = 24;
	fighter->moveset[3] = 23;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 15;
	
	
	
	fighter = &fighterData[36];
	SetString(fighter->name, "Police Captain");
	fighter->exp = 50;
	fighter->cash = 15;
	FighterData_AddReward(fighter, 1, 29, 1);
	FighterData_AddReward(fighter, 0, 5, 2);
	FighterData_AddReward(fighter, 0, 6, 2);
	FighterData_AddReward(fighter, 0, 26, 0);
	FighterData_AddReward(fighter, 0, 49, 1);
	
	fighter->headId = 30;
	fighter->bodyId = 32;
	fighter->charId = 32;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 56;
	fighter->mpMax = 18;
	
	fighter->attack = 12;
	fighter->defense = 0;
	fighter->speed = 14;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 26;
	fighter->moveset[3] = 49;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[37];
	SetString(fighter->name, "SYNC Office");
	fighter->exp = 40;
	fighter->cash = 15;
	FighterData_AddReward(fighter, 1, 30, 0);
	FighterData_AddReward(fighter, 0, 4, 1);
	FighterData_AddReward(fighter, 0, 36, 0);
	FighterData_AddReward(fighter, 0, 29, 0);
	
	fighter->headId = 31;
	fighter->bodyId = 33;
	fighter->charId = 33;
	fighter->actionAnimId = 1;
	fighter->ai = 37;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 46;
	fighter->mpMax = 23;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 23;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 36;
	fighter->moveset[2] = 29;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 17;
	
	
	
	fighter = &fighterData[38];
	SetString(fighter->name, "Josh");
	fighter->exp = 120;
	fighter->cash = 30;
	FighterData_AddReward(fighter, 1, 31, 0);
	FighterData_AddReward(fighter, 0, 4, 0);
	FighterData_AddReward(fighter, 0, 36, 0);
	FighterData_AddReward(fighter, 0, 29, 0);
	FighterData_AddReward(fighter, 0, 37, 0);
	
	fighter->headId = 32;
	fighter->bodyId = 34;
	fighter->charId = 34;
	fighter->actionAnimId = 1;
	fighter->ai = 38;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 85;
	fighter->mpMax = 38;
	
	fighter->attack = 18;
	fighter->defense = 0;
	fighter->speed = 31;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 36;
	fighter->moveset[2] = 29;
	fighter->moveset[3] = 37;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 17;
	
	
	
	fighter = &fighterData[39];
	SetString(fighter->name, "Pirate");
	fighter->exp = 46;
	fighter->cash = 20;
	FighterData_AddReward(fighter, 1, 32, 1);
	FighterData_AddReward(fighter, 0, 5, 2);
	FighterData_AddReward(fighter, 0, 6, 2);
	FighterData_AddReward(fighter, 0, 38, 1);
	
	fighter->headId = 33;
	fighter->bodyId = 35;
	fighter->charId = 35;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 48;
	fighter->mpMax = 20;
	
	fighter->attack = 18;
	fighter->defense = 0;
	fighter->speed = 19;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 38;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 19;
	
	
	
	fighter = &fighterData[40];
	SetString(fighter->name, "Pirate Cap'n");
	fighter->exp = 100;
	fighter->cash = 69;
	FighterData_AddReward(fighter, 1, 33, 0);
	FighterData_AddReward(fighter, 0, 5, 2);
	FighterData_AddReward(fighter, 0, 6, 2);
	FighterData_AddReward(fighter, 0, 38, 0);
	FighterData_AddReward(fighter, 0, 39, 0);
	
	fighter->headId = 34;
	fighter->bodyId = 36;
	fighter->charId = 36;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 82;
	fighter->mpMax = 32;
	
	fighter->attack = 23;
	fighter->defense = 0;
	fighter->speed = 22;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 38;
	fighter->moveset[3] = 39;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 19;
	fighter->passives[1] = 20;
	
	
	
	fighter = &fighterData[41];
	SetString(fighter->name, "Sanji");
	fighter->exp = 1000;
	fighter->cash = 300;
	FighterData_AddReward(fighter, 1, 34, 0);
	FighterData_AddReward(fighter, 0, 39, 0);
	FighterData_AddReward(fighter, 0, 40, 0);
	FighterData_AddReward(fighter, 0, 41, 0);
	FighterData_AddReward(fighter, 0, 42, 0);
	
	fighter->headId = 35;
	fighter->bodyId = 37;
	fighter->charId = 37;
	fighter->actionAnimId = 29;
	fighter->ai = 6;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 360;
	fighter->mpMax = 118;
	
	fighter->attack = 40;
	fighter->defense = 0;
	fighter->speed = 37;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 39;
	fighter->moveset[1] = 40;
	fighter->moveset[2] = 41;
	fighter->moveset[3] = 42;
	
	fighter->passiveCount = 3;
	fighter->passives[0] = 16;
	fighter->passives[1] = 19;
	fighter->passives[2] = 20;
	
	
	
	fighter = &fighterData[42];
	SetString(fighter->name, "Ninja");
	fighter->exp = 80;
	fighter->cash = 20;
	FighterData_AddReward(fighter, 1, 35, 1);
	FighterData_AddReward(fighter, 0, 35, 1);
	FighterData_AddReward(fighter, 0, 43, 1);
	FighterData_AddReward(fighter, 0, 44, 2);
	FighterData_AddReward(fighter, 0, 45, 1);
	
	fighter->headId = 36;
	fighter->bodyId = 38;
	fighter->charId = 38;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 54;
	fighter->mpMax = 30;
	
	fighter->attack = 13;
	fighter->defense = 0;
	fighter->speed = 40;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 35;
	fighter->moveset[2] = 43;
	fighter->moveset[3] = 44;
	fighter->moveset[4] = 45;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 11;
	
	
	
	fighter = &fighterData[43];
	SetString(fighter->name, "Secret Agent");
	fighter->exp = 300;
	fighter->cash = 140;
	FighterData_AddReward(fighter, 1, 36, 1);
	FighterData_AddReward(fighter, 0, 36, 1);
	FighterData_AddReward(fighter, 0, 29, 1);
	FighterData_AddReward(fighter, 0, 46, 1);
	FighterData_AddReward(fighter, 0, 47, 2);
	
	fighter->headId = 39;
	fighter->bodyId = 39;
	fighter->charId = 39;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 125;
	fighter->mpMax = 75;
	
	fighter->attack = 26;
	fighter->defense = 2;
	fighter->speed = 48;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 36;
	fighter->moveset[2] = 29;
	fighter->moveset[3] = 46;
	fighter->moveset[4] = 47;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[44];
	SetString(fighter->name, "B Police");
	fighter->exp = 74;
	fighter->cash = 20;
	FighterData_AddReward(fighter, 1, 37, 1);
	FighterData_AddReward(fighter, 0, 5, 2);
	FighterData_AddReward(fighter, 0, 6, 2);
	FighterData_AddReward(fighter, 0, 48, 1);
	FighterData_AddReward(fighter, 0, 49, 1);
	
	fighter->headId = 37;
	fighter->bodyId = 40;
	fighter->charId = 40;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 60;
	fighter->mpMax = 27;
	
	fighter->attack = 18;
	fighter->defense = 1;
	fighter->speed = 17;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 48;
	fighter->moveset[3] = 49;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 81;
	
	
	
	fighter = &fighterData[45];
	SetString(fighter->name, "G Police");
	fighter->exp = 275;
	fighter->cash = 160;
	FighterData_AddReward(fighter, 1, 38, 1);
	FighterData_AddReward(fighter, 0, 49, 1);
	FighterData_AddReward(fighter, 0, 50, 1);
	FighterData_AddReward(fighter, 0, 51, 1);
	FighterData_AddReward(fighter, 0, 52, 1);
	
	fighter->headId = 38;
	fighter->bodyId = 41;
	fighter->charId = 41;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 110;
	fighter->mpMax = 75;
	
	fighter->attack = 28;
	fighter->defense = 1;
	fighter->speed = 37;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 49;
	fighter->moveset[1] = 50;
	fighter->moveset[2] = 51;
	fighter->moveset[3] = 52;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 82;
	
	
	
	fighter = &fighterData[46];
	SetString(fighter->name, "Amp");
	fighter->exp = 10000;
	fighter->cash = 5000;
	FighterData_AddReward(fighter, 1, 39, 0);
	FighterData_AddReward(fighter, 0, 6, 0);
	FighterData_AddReward(fighter, 0, 143, 0);
	FighterData_AddReward(fighter, 0, 53, 0);
	FighterData_AddReward(fighter, 0, 55, 0);
	FighterData_AddReward(fighter, 0, 146, 0);
	FighterData_AddReward(fighter, 0, 54, 0);
	
	fighter->headId = 40;
	fighter->bodyId = 42;
	fighter->charId = 42;
	fighter->actionAnimId = 49;
	fighter->ai = 46;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 831;
	fighter->mpMax = 255;
	
	fighter->attack = 45;
	fighter->defense = 2;
	fighter->speed = 50;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 6;
	fighter->moveset[1] = 143;
	fighter->moveset[2] = 53;
	fighter->moveset[3] = 55;
	fighter->moveset[4] = 146;
	fighter->moveset[5] = 54;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 68;
	fighter->passives[1] = 69;
	
	
	
	fighter = &fighterData[47];
	SetString(fighter->name, "River");
	fighter->exp = 3;
	fighter->cash = 0;
	FighterData_AddReward(fighter, 1, 40, 0);
	
	fighter->headId = 41;
	fighter->bodyId = 43;
	fighter->charId = 43;
	fighter->actionAnimId = 1;
	fighter->ai = 8;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 16;
	fighter->mpMax = 8;
	
	fighter->attack = 1;
	fighter->defense = 0;
	fighter->speed = 10;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[48];
	SetString(fighter->name, "River");
	fighter->exp = 6;
	fighter->cash = 4;
	FighterData_AddReward(fighter, 0, 25, 0);
	
	fighter->headId = 41;
	fighter->bodyId = 43;
	fighter->charId = 43;
	fighter->actionAnimId = 1;
	fighter->ai = 2;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 16;
	fighter->mpMax = 8;
	
	fighter->attack = 1;
	fighter->defense = 0;
	fighter->speed = 13;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 25;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[49];
	SetString(fighter->name, "Frank");
	fighter->exp = 5;
	fighter->cash = 3;
	FighterData_AddReward(fighter, 1, 41, 0);
	FighterData_AddReward(fighter, 0, 2, 0);
	FighterData_AddReward(fighter, 0, 25, 0);
	
	fighter->headId = 42;
	fighter->bodyId = 44;
	fighter->charId = 44;
	fighter->actionAnimId = 2;
	fighter->ai = 2;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 11;
	fighter->mpMax = 3;
	
	fighter->attack = 3;
	fighter->defense = 0;
	fighter->speed = 11;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 2;
	fighter->moveset[2] = 25;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[50];
	SetString(fighter->name, "Wax Knight");
	fighter->exp = 60;
	fighter->cash = 4;
	FighterData_AddReward(fighter, 1, 42, 4);
	
	fighter->headId = 43;
	fighter->bodyId = 45;
	fighter->charId = 45;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 60;
	fighter->mpMax = 40;
	
	fighter->attack = 32;
	fighter->defense = 5;
	fighter->speed = 15;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 38;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 18;
	
	
	
	fighter = &fighterData[51];
	SetString(fighter->name, "Flora");
	fighter->exp = 8000;
	fighter->cash = 2500;
	FighterData_AddReward(fighter, 1, 43, 0);
	FighterData_AddReward(fighter, 0, 56, 0);
	FighterData_AddReward(fighter, 0, 57, 0);
	FighterData_AddReward(fighter, 0, 58, 0);
	FighterData_AddReward(fighter, 0, 59, 0);
	FighterData_AddReward(fighter, 0, 60, 0);
	
	fighter->headId = 44;
	fighter->bodyId = 46;
	fighter->charId = 46;
	fighter->actionAnimId = 18;
	fighter->ai = 51;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 500;
	fighter->mpMax = 160;
	
	fighter->attack = 30;
	fighter->defense = 0;
	fighter->speed = 59;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 56;
	fighter->moveset[1] = 57;
	fighter->moveset[2] = 58;
	fighter->moveset[3] = 59;
	fighter->moveset[4] = 60;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 70;
	
	
	
	fighter = &fighterData[52];
	SetString(fighter->name, "Death Knife");
	fighter->exp = 55;
	fighter->cash = 0;
	
	fighter->headId = 0;
	fighter->bodyId = 47;
	fighter->charId = 47;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 40;
	fighter->mpMax = 22;
	
	fighter->attack = 25;
	fighter->defense = 0;
	fighter->speed = 20;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 49;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[53];
	SetString(fighter->name, "Energy Entity");
	fighter->exp = 48;
	fighter->cash = 0;
	
	fighter->headId = 0;
	fighter->bodyId = 48;
	fighter->charId = 48;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 1;
	fighter->mpMax = 93;
	
	fighter->attack = 20;
	fighter->defense = 0;
	fighter->speed = 38;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 61;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[54];
	SetString(fighter->name, "Death Weight");
	fighter->exp = 67;
	fighter->cash = 0;
	
	fighter->headId = 0;
	fighter->bodyId = 49;
	fighter->charId = 49;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 80;
	fighter->mpMax = 13;
	
	fighter->attack = 18;
	fighter->defense = 12;
	fighter->speed = 3;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 62;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[55];
	SetString(fighter->name, "The Gate");
	fighter->exp = 6666;
	fighter->cash = 0;
	
	fighter->headId = 0;
	fighter->bodyId = 50;
	fighter->charId = 50;
	fighter->actionAnimId = 0;
	fighter->ai = 55;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 1500; //99000
	fighter->mpMax = 750; //3758
	
	fighter->attack = 30;
	fighter->defense = 9;
	fighter->speed = 80;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 61;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[56];
	SetString(fighter->name, "Kelly");
	fighter->exp = 68;
	fighter->cash = 25;
	FighterData_AddReward(fighter, 1, 44, 0);
	FighterData_AddReward(fighter, 0, 63, 0);
	FighterData_AddReward(fighter, 0, 64, 0);
	
	fighter->headId = 46;
	fighter->bodyId = 51;
	fighter->charId = 51;
	fighter->actionAnimId = 3;
	fighter->ai = 56;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 60;
	fighter->mpMax = 35;
	
	fighter->attack = 21;
	fighter->defense = 0;
	fighter->speed = 25;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 63;
	fighter->moveset[2] = 64;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 21;
	
	
	
	fighter = &fighterData[57];
	SetString(fighter->name, "Neveah");
	fighter->exp = 77;
	fighter->cash = 36;
	FighterData_AddReward(fighter, 1, 45, 0);
	FighterData_AddReward(fighter, 0, 63, 0);
	FighterData_AddReward(fighter, 0, 64, 0);
	
	fighter->headId = 47;
	fighter->bodyId = 52;
	fighter->charId = 52;
	fighter->actionAnimId = 3;
	fighter->ai = 57;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 82;
	fighter->mpMax = 40;
	
	fighter->attack = 24;
	fighter->defense = 0;
	fighter->speed = 20;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 63;
	fighter->moveset[2] = 64;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 21;
	fighter->passives[1] = 22;
	
	
	
	fighter = &fighterData[58];
	SetString(fighter->name, "Brook");
	fighter->exp = 190;
	fighter->cash = 38;
	FighterData_AddReward(fighter, 1, 46, 0);
	FighterData_AddReward(fighter, 0, 65, 0);
	FighterData_AddReward(fighter, 0, 66, 0);
	
	fighter->headId = 48;
	fighter->bodyId = 53;
	fighter->charId = 53;
	fighter->actionAnimId = 1;
	fighter->ai = 58;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 137;
	fighter->mpMax = 50;
	
	fighter->attack = 24;
	fighter->defense = 1;
	fighter->speed = 19;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 2;
	fighter->moveset[2] = 65;
	fighter->moveset[3] = 66;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 25;
	
	
	
	fighter = &fighterData[59];
	SetString(fighter->name, "Tom");
	fighter->exp = 164;
	fighter->cash = 80;
	FighterData_AddReward(fighter, 1, 47, 0);
	FighterData_AddReward(fighter, 0, 3, 0);
	FighterData_AddReward(fighter, 0, 93, 0);
	FighterData_AddReward(fighter, 0, 67, 0);
	FighterData_AddReward(fighter, 0, 68, 0);
	FighterData_AddReward(fighter, 0, 74, 0);
	
	fighter->headId = 49;
	fighter->bodyId = 54;
	fighter->charId = 54;
	fighter->actionAnimId = 2;
	fighter->ai = 59;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 110;
	fighter->mpMax = 78;
	
	fighter->attack = 22;
	fighter->defense = 0;
	fighter->speed = 39;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 3;
	fighter->moveset[1] = 93;
	fighter->moveset[2] = 67;
	fighter->moveset[3] = 68;
	fighter->moveset[4] = 74;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 23;
	fighter->passives[1] = 24;
	
	
	
	fighter = &fighterData[60];
	SetString(fighter->name, "Cindy");
	fighter->exp = 224;
	fighter->cash = 100;
	FighterData_AddReward(fighter, 1, 48, 0);
	FighterData_AddReward(fighter, 0, 73, 0);
	FighterData_AddReward(fighter, 0, 61, 0);
	FighterData_AddReward(fighter, 0, 70, 0);
	FighterData_AddReward(fighter, 0, 71, 0);
	FighterData_AddReward(fighter, 0, 72, 0);
	
	fighter->headId = 50;
	fighter->bodyId = 55;
	fighter->charId = 55;
	fighter->actionAnimId = 1;
	fighter->ai = 60;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 94;
	fighter->mpMax = 155;
	
	fighter->attack = 16;
	fighter->defense = 0;
	fighter->speed = 25;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 73;
	fighter->moveset[1] = 61;
	fighter->moveset[2] = 70;
	fighter->moveset[3] = 71;
	fighter->moveset[4] = 72;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 26;
	
	
	
	fighter = &fighterData[61];
	SetString(fighter->name, "Ozone Mafia");
	fighter->exp = 84;
	fighter->cash = 30;
	FighterData_AddReward(fighter, 1, 51, 1);
	FighterData_AddReward(fighter, 0, 50, 1);
	FighterData_AddReward(fighter, 0, 75, 1);
	
	fighter->headId = 52;
	fighter->bodyId = 58;
	fighter->charId = 58;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 50;
	fighter->mpMax = 28;
	
	fighter->attack = 16;
	fighter->defense = 0;
	fighter->speed = 21;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 49;
	fighter->moveset[1] = 50;
	fighter->moveset[2] = 75;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 31;
	
	
	
	fighter = &fighterData[62];
	SetString(fighter->name, "Don");
	fighter->exp = 150;
	fighter->cash = 60;
	FighterData_AddReward(fighter, 1, 52, 0);
	FighterData_AddReward(fighter, 0, 50, 0);
	FighterData_AddReward(fighter, 0, 51, 0);
	FighterData_AddReward(fighter, 0, 85, 0);
	
	fighter->headId = 53;
	fighter->bodyId = 59;
	fighter->charId = 59;
	fighter->actionAnimId = 2;
	fighter->ai = 62;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 100;
	fighter->mpMax = 64;
	
	fighter->attack = 22;
	fighter->defense = 0;
	fighter->speed = 33;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 3;
	fighter->moveset[1] = 50;
	fighter->moveset[2] = 51;
	fighter->moveset[3] = 85;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 31;
	fighter->passives[1] = 32;
	
	
	
	fighter = &fighterData[63];
	SetString(fighter->name, "Nate");
	fighter->exp = 150;
	fighter->cash = 60;
	FighterData_AddReward(fighter, 1, 53, 0);
	FighterData_AddReward(fighter, 0, 49, 0);
	FighterData_AddReward(fighter, 0, 76, 0);
	FighterData_AddReward(fighter, 0, 77, 0);
	FighterData_AddReward(fighter, 0, 85, 0);
	
	fighter->headId = 54;
	fighter->bodyId = 60;
	fighter->charId = 60;
	fighter->actionAnimId = 3;
	fighter->ai = 63;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 140;
	fighter->mpMax = 40;
	
	fighter->attack = 24;
	fighter->defense = 0;
	fighter->speed = 10;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 49;
	fighter->moveset[1] = 50;
	fighter->moveset[2] = 76;
	fighter->moveset[3] = 77;
	fighter->moveset[4] = 85;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 31;
	fighter->passives[1] = 33;
	
	
	
	fighter = &fighterData[64];
	SetString(fighter->name, "Vulkan");
	fighter->exp = 2000;
	fighter->cash = 400;
	FighterData_AddReward(fighter, 1, 54, 0);
	FighterData_AddReward(fighter, 0, 6, 0);
	FighterData_AddReward(fighter, 0, 79, 0);
	FighterData_AddReward(fighter, 0, 80, 0);
	FighterData_AddReward(fighter, 0, 81, 0);
	FighterData_AddReward(fighter, 0, 43, 0);
	FighterData_AddReward(fighter, 0, 36, 0);
	
	fighter->headId = 55;
	fighter->bodyId = 61;
	fighter->charId = 61;
	fighter->actionAnimId = 26;
	fighter->ai = 64;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 440;
	fighter->mpMax = 160;
	
	fighter->attack = 40;
	fighter->defense = 0;
	fighter->speed = 45;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 6;
	fighter->moveset[1] = 79;
	fighter->moveset[2] = 80;
	fighter->moveset[3] = 81;
	fighter->moveset[4] = 43;
	fighter->moveset[5] = 36;
	
	fighter->passiveCount = 3;
	fighter->passives[0] = 28;
	fighter->passives[1] = 29;
	fighter->passives[2] = 30;
	
	
	
	fighter = &fighterData[65];
	SetString(fighter->name, "Luna");
	fighter->exp = 1000;
	fighter->cash = 300;
	FighterData_AddReward(fighter, 1, 56, 0);
	FighterData_AddReward(fighter, 0, 61, 0);
	FighterData_AddReward(fighter, 0, 72, 0);
	FighterData_AddReward(fighter, 0, 74, 0);
	FighterData_AddReward(fighter, 0, 82, 0);
	FighterData_AddReward(fighter, 0, 83, 0);
	
	fighter->headId = 56;
	fighter->bodyId = 62;
	fighter->charId = 62;
	fighter->collapseSpriteId = SPR_owchar_collapse_luna;
	fighter->actionAnimId = 3;
	fighter->ai = 65;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 337;
	fighter->mpMax = 180;
	
	fighter->attack = 21;
	fighter->defense = 0;
	fighter->speed = 25;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 61;
	fighter->moveset[2] = 72;
	fighter->moveset[3] = 74;
	fighter->moveset[4] = 82;
	fighter->moveset[5] = 83;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 31;
	fighter->passives[1] = 27;
	
	
	
	fighter = &fighterData[66];
	SetString(fighter->name, "Hellgoner");
	fighter->exp = 30;
	fighter->cash = 0;
	FighterData_AddReward(fighter, 1, 55, 4);
	
	fighter->headId = 0;
	fighter->bodyId = 63;
	fighter->charId = 63;
	fighter->actionAnimId = 28;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 149;
	fighter->mpMax = 84;
	
	fighter->attack = 33;
	fighter->defense = -21;
	fighter->speed = 9;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 13;
	fighter->moveset[2] = 23;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[67];
	SetString(fighter->name, "Hellgoner");
	fighter->exp = 30;
	fighter->cash = 0;
	FighterData_AddReward(fighter, 1, 55, 4);
	
	fighter->headId = 0;
	fighter->bodyId = 64;
	fighter->charId = 64;
	fighter->actionAnimId = 28;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 149;
	fighter->mpMax = 84;
	
	fighter->attack = 33;
	fighter->defense = -21;
	fighter->speed = 9;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 13;
	fighter->moveset[2] = 23;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[68];
	SetString(fighter->name, "D$`Hc");
	fighter->exp = 0;
	fighter->cash = 0;
	FighterData_AddReward(fighter, 0, 0x90, 5);
	
	fighter->headId = 0;
	fighter->bodyId = 66;
	fighter->charId = 31;
	fighter->actionAnimId = 13;
	fighter->ai = 0;
	fighter->gender = 0x90;
	
	fighter->hpMax = 13;
	fighter->mpMax = 13;
	
	fighter->attack = 13;
	fighter->defense = 6;
	fighter->speed = 27;
	
	fighter->movesetCount = 8;
	fighter->moveset[0] = 33;
	fighter->moveset[1] = 33;
	fighter->moveset[2] = 1;
	fighter->moveset[3] = 1;
	fighter->moveset[4] = 255;
	fighter->moveset[5] = 191;
	fighter->moveset[6] = 1;
	fighter->moveset[7] = 33;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[69];
	SetString(fighter->name, "Perry");
	fighter->exp = 20;
	fighter->cash = 873;
	FighterData_AddReward(fighter, 1, 57, 0);
	
	fighter->headId = 57;
	fighter->bodyId = 67;
	fighter->charId = 7;
	fighter->collapseSpriteId = SPR_owchar_collapse_perry;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 40;
	fighter->mpMax = 5;
	
	fighter->attack = 5;
	fighter->defense = 0;
	fighter->speed = 6;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[70];
	SetString(fighter->name, "Kelly");
	fighter->exp = 68;
	fighter->cash = 22;
	
	fighter->headId = 46;
	fighter->bodyId = 51;
	fighter->charId = 51;
	fighter->actionAnimId = 3;
	fighter->ai = 56;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 60;
	fighter->mpMax = 35;
	
	fighter->attack = 21;
	fighter->defense = 0;
	fighter->speed = 25;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 63;
	fighter->moveset[2] = 64;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 21;
	
	
	
	fighter = &fighterData[71];
	SetString(fighter->name, "Neveah");
	fighter->exp = 78;
	fighter->cash = 30;
	
	fighter->headId = 47;
	fighter->bodyId = 52;
	fighter->charId = 52;
	fighter->actionAnimId = 3;
	fighter->ai = 57;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 84;
	fighter->mpMax = 41;
	
	fighter->attack = 24;
	fighter->defense = 0;
	fighter->speed = 21;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 63;
	fighter->moveset[2] = 64;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 21;
	fighter->passives[1] = 22;
	
	
	
	fighter = &fighterData[72];
	SetString(fighter->name, "Brian");
	fighter->exp = 15;
	fighter->cash = 30;
	FighterData_AddReward(fighter, 1, 58, 0);
	FighterData_AddReward(fighter, 0, 84, 0);
	
	fighter->headId = 58;
	fighter->bodyId = 68;
	fighter->charId = 68;
	fighter->actionAnimId = 3;
	fighter->ai = 72;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 15;
	fighter->mpMax = 10;
	
	fighter->attack = 37;
	fighter->defense = 0;
	fighter->speed = 18;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 84;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 34;
	
	
	
	fighter = &fighterData[73];
	SetString(fighter->name, "Nekin");
	fighter->exp = 2107;
	fighter->cash = 192;
	FighterData_AddReward(fighter, 1, 59, 0);
	FighterData_AddReward(fighter, 0, 4, 0);
	FighterData_AddReward(fighter, 0, 41, 0);
	FighterData_AddReward(fighter, 0, 87, 0);
	FighterData_AddReward(fighter, 0, 89, 0);
	FighterData_AddReward(fighter, 0, 90, 0);
	FighterData_AddReward(fighter, 0, 88, 0);
	
	fighter->headId = 59;
	fighter->bodyId = 69;
	fighter->charId = 69;
	fighter->collapseSpriteId = SPR_owchar_collapse_nekin;
	fighter->actionAnimId = 30;
	fighter->ai = 73;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 316;
	fighter->mpMax = 125;
	
	fighter->attack = 41;
	fighter->defense = 0;
	fighter->speed = 36;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 41;
	fighter->moveset[2] = 87;
	fighter->moveset[3] = 89;
	fighter->moveset[4] = 90;
	fighter->moveset[5] = 86;
	
	fighter->passiveCount = 3;
	fighter->passives[0] = 35;
	fighter->passives[1] = 36;
	fighter->passives[2] = 37;
	
	
	
	fighter = &fighterData[74];
	SetString(fighter->name, "Adios");
	fighter->exp = 250;
	fighter->cash = 150;
	FighterData_AddReward(fighter, 1, 60, 0);
	FighterData_AddReward(fighter, 0, 4, 0);
	FighterData_AddReward(fighter, 0, 50, 0);
	FighterData_AddReward(fighter, 0, 46, 0);
	FighterData_AddReward(fighter, 0, 47, 0);
	FighterData_AddReward(fighter, 0, 76, 0);
	FighterData_AddReward(fighter, 0, 91, 0);
	
	fighter->headId = 61;
	fighter->bodyId = 71;
	fighter->charId = 71;
	fighter->actionAnimId = 1;
	fighter->ai = 74;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 132;
	fighter->mpMax = 80;
	
	fighter->attack = 27;
	fighter->defense = 2;
	fighter->speed = 45;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 50;
	fighter->moveset[2] = 46;
	fighter->moveset[3] = 47;
	fighter->moveset[4] = 76;
	fighter->moveset[5] = 91;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 39;
	fighter->passives[1] = 38;
	
	
	
	fighter = &fighterData[75];
	SetString(fighter->name, "Bulldog");
	fighter->exp = 223;
	fighter->cash = 100;
	FighterData_AddReward(fighter, 1, 61, 0);
	FighterData_AddReward(fighter, 0, 36, 0);
	FighterData_AddReward(fighter, 0, 94, 0);
	FighterData_AddReward(fighter, 0, 93, 0);
	FighterData_AddReward(fighter, 0, 92, 0);
	FighterData_AddReward(fighter, 0, 26, 0);
	
	fighter->headId = 62;
	fighter->bodyId = 72;
	fighter->charId = 72;
	fighter->actionAnimId = 1;
	fighter->ai = 75;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 172;
	fighter->mpMax = 56;
	
	fighter->attack = 32;
	fighter->defense = 4;
	fighter->speed = 20;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 36;
	fighter->moveset[1] = 94;
	fighter->moveset[2] = 93;
	fighter->moveset[3] = 92;
	fighter->moveset[4] = 26;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 40;
	fighter->passives[1] = 33;
	
	
	
	fighter = &fighterData[76];
	SetString(fighter->name, "Kyle");
	fighter->exp = 270;
	fighter->cash = 280;
	FighterData_AddReward(fighter, 1, 66, 0);
	FighterData_AddReward(fighter, 0, 108, 0);
	FighterData_AddReward(fighter, 0, 110, 0);
	FighterData_AddReward(fighter, 0, 113, 0);
	FighterData_AddReward(fighter, 0, 115, 0);
	FighterData_AddReward(fighter, 0, 107, 0);
	
	fighter->headId = 64;
	fighter->bodyId = 73;
	fighter->charId = 73;
	fighter->actionAnimId = 1;
	fighter->ai = 76;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 120;
	fighter->mpMax = 60;
	
	fighter->attack = 22;
	fighter->defense = 0;
	fighter->speed = 40;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 108;
	fighter->moveset[1] = 110;
	fighter->moveset[2] = 113;
	fighter->moveset[3] = 115;
	fighter->moveset[4] = 107;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 3;
	fighter->passives[1] = 46;
	
	
	
	fighter = &fighterData[77];
	SetString(fighter->name, "Builder");
	fighter->exp = 130;
	fighter->cash = 30;
	FighterData_AddReward(fighter, 1, 63, 1);
	FighterData_AddReward(fighter, 0, 5, 0);
	FighterData_AddReward(fighter, 0, 36, 1);
	FighterData_AddReward(fighter, 0, 38, 1);
	FighterData_AddReward(fighter, 0, 122, 2);
	FighterData_AddReward(fighter, 0, 123, 1);
	
	fighter->headId = 65;
	fighter->bodyId = 74;
	fighter->charId = 74;
	fighter->actionAnimId = 3;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 125;
	fighter->mpMax = 37;
	
	fighter->attack = 28;
	fighter->defense = 3;
	fighter->speed = 18;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 36;
	fighter->moveset[2] = 38;
	fighter->moveset[3] = 122;
	fighter->moveset[4] = 123;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 50;
	
	
	
	fighter = &fighterData[78];
	SetString(fighter->name, "Tia");
	fighter->exp = 400;
	fighter->cash = 300;
	FighterData_AddReward(fighter, 1, 64, 0);
	FighterData_AddReward(fighter, 0, 4, 0);
	FighterData_AddReward(fighter, 0, 117, 0);
	FighterData_AddReward(fighter, 0, 72, 0);
	FighterData_AddReward(fighter, 0, 109, 0);
	FighterData_AddReward(fighter, 0, 116, 0);
	FighterData_AddReward(fighter, 0, 65, 0);
	
	fighter->headId = 66;
	fighter->bodyId = 75;
	fighter->charId = 75;
	fighter->actionAnimId = 1;
	fighter->ai = 78;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 250;
	fighter->mpMax = 150;
	
	fighter->attack = 20;
	fighter->defense = 0;
	fighter->speed = 34;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 4;
	fighter->moveset[1] = 117;
	fighter->moveset[2] = 72;
	fighter->moveset[3] = 109;
	fighter->moveset[4] = 116;
	fighter->moveset[5] = 65;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 59;
	fighter->passives[1] = 40;
	
	
	
	fighter = &fighterData[79];
	SetString(fighter->name, "Kara");
	fighter->exp = 1256;
	fighter->cash = 375;
	FighterData_AddReward(fighter, 1, 65, 0);
	FighterData_AddReward(fighter, 0, 2, 0);
	FighterData_AddReward(fighter, 0, 35, 0);
	FighterData_AddReward(fighter, 0, 36, 0);
	FighterData_AddReward(fighter, 0, 45, 0);
	FighterData_AddReward(fighter, 0, 145, 0);
	
	fighter->headId = 67;
	fighter->bodyId = 76;
	fighter->charId = 76;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 375;
	fighter->mpMax = 164;
	
	fighter->attack = 27;
	fighter->defense = 0;
	fighter->speed = 57;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 2;
	fighter->moveset[1] = 35;
	fighter->moveset[2] = 36;
	fighter->moveset[3] = 45;
	fighter->moveset[4] = 145;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 61;
	fighter->passives[1] = 55;
	
	
	
	fighter = &fighterData[80];
	SetString(fighter->name, "Camilla");
	fighter->exp = 102;
	fighter->cash = 500;
	FighterData_AddReward(fighter, 1, 67, 0);
	FighterData_AddReward(fighter, 0, 6, 0);
	FighterData_AddReward(fighter, 0, 118, 0);
	FighterData_AddReward(fighter, 0, 121, 0);
	
	fighter->headId = 68;
	fighter->bodyId = 77;
	fighter->charId = 77;
	fighter->actionAnimId = 42;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 65;
	fighter->mpMax = 52;
	
	fighter->attack = 16;
	fighter->defense = 2;
	fighter->speed = 20;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 118;
	fighter->moveset[3] = 121;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 60;
	
	
	
	fighter = &fighterData[81];
	SetString(fighter->name, "Ayin Oying");
	fighter->exp = 69;
	fighter->cash = 3;
	FighterData_AddReward(fighter, 1, 69, 0);
	
	fighter->headId = 69;
	fighter->bodyId = 78;
	fighter->charId = 78;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 30;
	fighter->mpMax = 30;
	
	fighter->attack = 1;
	fighter->defense = 8;
	fighter->speed = 1;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 1;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[82];
	SetString(fighter->name, "Aztec");
	fighter->exp = 250;
	fighter->cash = 95;
	FighterData_AddReward(fighter, 1, 62, 0);
	FighterData_AddReward(fighter, 0, 100, 0);
	FighterData_AddReward(fighter, 0, 101, 0);
	FighterData_AddReward(fighter, 0, 102, 0);
	FighterData_AddReward(fighter, 0, 103, 0);
	FighterData_AddReward(fighter, 0, 104, 0);
	
	fighter->headId = 70;
	fighter->bodyId = 79;
	fighter->charId = 79;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 140;
	fighter->mpMax = 69;
	
	fighter->attack = 12;
	fighter->defense = 0;
	fighter->speed = 21;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 100;
	fighter->moveset[1] = 101;
	fighter->moveset[2] = 102;
	fighter->moveset[3] = 103;
	fighter->moveset[4] = 104;
	
	fighter->passiveCount = 4;
	fighter->passives[0] = 41;
	fighter->passives[1] = 42;
	fighter->passives[2] = 43;
	fighter->passives[3] = 44;
	
	
	
	fighter = &fighterData[83];
	SetString(fighter->name, "Gemini");
	fighter->exp = 400;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 97, 1);
	FighterData_AddReward(fighter, 0, 98, 1);
	FighterData_AddReward(fighter, 0, 99, 1);
	
	fighter->headId = 0;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 1;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 180;
	fighter->mpMax = 160;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 97;
	fighter->moveset[2] = 98;
	fighter->moveset[3] = 99;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[84];
	SetString(fighter->name, "Dirk");
	fighter->exp = 350;
	fighter->cash = 38;
	FighterData_AddReward(fighter, 1, 68, 0);
	FighterData_AddReward(fighter, 0, 2, 0);
	FighterData_AddReward(fighter, 0, 65, 0);
	FighterData_AddReward(fighter, 0, 124, 0);
	
	fighter->headId = 71;
	fighter->bodyId = 81;
	fighter->charId = 81;
	fighter->actionAnimId = 1;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 336;
	fighter->mpMax = 74;
	
	fighter->attack = 32;
	fighter->defense = 2;
	fighter->speed = 30;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 2;
	fighter->moveset[1] = 65;
	fighter->moveset[2] = 124;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 57;
	
	
	
	fighter = &fighterData[85];
	SetString(fighter->name, "Whitelight");
	fighter->exp = 188;
	fighter->cash = 32;
	FighterData_AddReward(fighter, 1, 70, 1);
	FighterData_AddReward(fighter, 0, 121, 1);
	FighterData_AddReward(fighter, 0, 127, 2);
	FighterData_AddReward(fighter, 0, 128, 3);
	
	fighter->headId = 72;
	fighter->bodyId = 82;
	fighter->charId = 82;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 101;
	fighter->mpMax = 52;
	
	fighter->attack = 31;
	fighter->defense = 2;
	fighter->speed = 33;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 121;
	fighter->moveset[2] = 127;
	fighter->moveset[3] = 128;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 54;
	
	
	
	fighter = &fighterData[86];
	SetString(fighter->name, "Rob");
	fighter->exp = 3892;
	fighter->cash = 1500;
	FighterData_AddReward(fighter, 1, 71, 0);
	FighterData_AddReward(fighter, 0, 50, 0);
	FighterData_AddReward(fighter, 0, 126, 0);
	FighterData_AddReward(fighter, 0, 127, 0);
	FighterData_AddReward(fighter, 0, 128, 0);
	FighterData_AddReward(fighter, 0, 125, 0);
	FighterData_AddReward(fighter, 0, 129, 0);
	
	fighter->headId = 74;
	fighter->bodyId = 83;
	fighter->charId = 83;
	fighter->actionAnimId = 2;
	fighter->ai = 86;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 375;
	fighter->mpMax = 160;
	
	fighter->attack = 38;
	fighter->defense = 3;
	fighter->speed = 60;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 50;
	fighter->moveset[1] = 126;
	fighter->moveset[2] = 127;
	fighter->moveset[3] = 128;
	fighter->moveset[4] = 125;
	fighter->moveset[5] = 129;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 54;
	fighter->passives[1] = 62;
	
	
	
	fighter = &fighterData[87];
	SetString(fighter->name, "Mani");
	fighter->exp = 97;
	fighter->cash = 100;
	FighterData_AddReward(fighter, 1, 72, 0);
	FighterData_AddReward(fighter, 0, 73, 0);
	FighterData_AddReward(fighter, 0, 6, 0);
	FighterData_AddReward(fighter, 0, 27, 0);
	FighterData_AddReward(fighter, 0, 68, 0);
	FighterData_AddReward(fighter, 0, 131, 0);
	
	fighter->headId = 75;
	fighter->bodyId = 84;
	fighter->charId = 84;
	fighter->actionAnimId = 2;
	fighter->ai = 87;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 57;
	fighter->mpMax = 63;
	
	fighter->attack = 15;
	fighter->defense = 2;
	fighter->speed = 22;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 73;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 27;
	fighter->moveset[3] = 68;
	fighter->moveset[4] = 131;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 54;
	fighter->passives[1] = 63;
	
	
	
	fighter = &fighterData[88];
	SetString(fighter->name, "Timon");
	fighter->exp = 983;
	fighter->cash = 250;
	FighterData_AddReward(fighter, 1, 73, 0);
	FighterData_AddReward(fighter, 0, 132, 0);
	FighterData_AddReward(fighter, 0, 121, 0);
	FighterData_AddReward(fighter, 0, 134, 0);
	FighterData_AddReward(fighter, 0, 76, 0);
	FighterData_AddReward(fighter, 0, 133, 0);
	FighterData_AddReward(fighter, 0, 105, 0);
	
	fighter->headId = 76;
	fighter->bodyId = 85;
	fighter->charId = 85;
	fighter->actionAnimId = 2;
	fighter->ai = 88;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 242;
	fighter->mpMax = 114;
	
	fighter->attack = 24;
	fighter->defense = 2;
	fighter->speed = 32;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 132;
	fighter->moveset[1] = 121;
	fighter->moveset[2] = 134;
	fighter->moveset[3] = 76;
	fighter->moveset[4] = 133;
	fighter->moveset[5] = 105;
	
	fighter->passiveCount = 3;
	fighter->passives[0] = 54;
	fighter->passives[1] = 64;
	fighter->passives[2] = 65;
	
	
	
	fighter = &fighterData[89];
	SetString(fighter->name, "Gregory");
	fighter->exp = 257;
	fighter->cash = 150;
	FighterData_AddReward(fighter, 1, 75, 0);
	FighterData_AddReward(fighter, 0, 5, 0);
	FighterData_AddReward(fighter, 0, 135, 0);
	FighterData_AddReward(fighter, 0, 136, 0);
	FighterData_AddReward(fighter, 0, 36, 0);
	FighterData_AddReward(fighter, 0, 137, 0);
	
	fighter->headId = 77;
	fighter->bodyId = 86;
	fighter->charId = 86;
	fighter->actionAnimId = 2;
	fighter->ai = 89;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 185;
	fighter->mpMax = 52;
	
	fighter->attack = 15;
	fighter->defense = 0;
	fighter->speed = 15;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 135;
	fighter->moveset[2] = 136;
	fighter->moveset[3] = 36;
	fighter->moveset[4] = 137;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 67;
	
	
	
	fighter = &fighterData[90];
	SetString(fighter->name, "Sally");
	fighter->exp = 30;
	fighter->cash = 0;
	FighterData_AddReward(fighter, 1, 74, 0);
	FighterData_AddReward(fighter, 0, 138, 0);
	FighterData_AddReward(fighter, 0, 139, 0);
	FighterData_AddReward(fighter, 0, 140, 0);
	FighterData_AddReward(fighter, 0, 142, 0);
	
	fighter->headId = 79;
	fighter->bodyId = 88;
	fighter->charId = 88;
	fighter->actionAnimId = 48;
	fighter->ai = 90;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 10;
	fighter->mpMax = 5;
	
	fighter->attack = 5;
	fighter->defense = 0;
	fighter->speed = 5;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 138;
	fighter->moveset[1] = 139;
	fighter->moveset[2] = 140;
	fighter->moveset[3] = 142;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 47;
	fighter->passives[1] = 66;
	
	
	
	fighter = &fighterData[91];
	SetString(fighter->name, "The Path Blocker");
	fighter->exp = 19772;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 144, 0);
	FighterData_AddReward(fighter, 0, 72, 0);
	
	fighter->headId = 0;
	fighter->bodyId = 90;
	fighter->charId = 90;
	fighter->actionAnimId = 3;
	fighter->ai = 91;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 1095;
	fighter->mpMax = 348;
	
	fighter->attack = 50;
	fighter->defense = 4;
	fighter->speed = 74;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 144;
	fighter->moveset[1] = 72;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[92];
	SetString(fighter->name, "Master Lulu");
	FighterData_AddReward(fighter, 1, 76, 0);
	FighterData_AddReward(fighter, 0, 28, 0);
	FighterData_AddReward(fighter, 0, 147, 0);
	fighter->exp = 10246;
	fighter->cash = 4000;
	
	fighter->headId = 81;
	fighter->bodyId = 91;
	fighter->charId = 91;
	fighter->actionAnimId = 19;
	fighter->ai = 92;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 400;
	fighter->mpMax = 282;
	
	fighter->attack = 48;
	fighter->defense = 0;
	fighter->speed = 65;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 18;
	fighter->moveset[1] = 19;
	fighter->moveset[2] = 17;
	fighter->moveset[3] = 28;
	fighter->moveset[4] = 147;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
	
	
	
	fighter = &fighterData[93];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 97, 1);
	FighterData_AddReward(fighter, 0, 98, 1);
	FighterData_AddReward(fighter, 0, 99, 2);
	
	fighter->headId = 0;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 93;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 97;
	fighter->moveset[2] = 98;
	fighter->moveset[3] = 99;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[94];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 116, 1);
	FighterData_AddReward(fighter, 0, 134, 1);
	FighterData_AddReward(fighter, 0, 148, 2);
	
	fighter->headId = 1;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 94;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 116;
	fighter->moveset[2] = 134;
	fighter->moveset[3] = 148;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[95];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 152, 1);
	FighterData_AddReward(fighter, 0, 150, 2);
	FighterData_AddReward(fighter, 0, 151, 2);
	
	fighter->headId = 2;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 95;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 152;
	fighter->moveset[2] = 150;
	fighter->moveset[3] = 151;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[96];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 114, 1);
	FighterData_AddReward(fighter, 0, 134, 1);
	FighterData_AddReward(fighter, 0, 158, 1);
	FighterData_AddReward(fighter, 0, 61, 2);
	
	fighter->headId = 3;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 96;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 114;
	fighter->moveset[2] = 134;
	fighter->moveset[3] = 158;
	fighter->moveset[4] = 61;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[97];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 82, 1);
	FighterData_AddReward(fighter, 0, 45, 1);
	FighterData_AddReward(fighter, 0, 153, 2);
	
	fighter->headId = 4;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 97;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 82;
	fighter->moveset[2] = 45;
	fighter->moveset[3] = 153;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[98];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 157, 1);
	FighterData_AddReward(fighter, 0, 71, 1);
	FighterData_AddReward(fighter, 0, 149, 2);
	
	fighter->headId = 5;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 98;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 157;
	fighter->moveset[2] = 71;
	fighter->moveset[3] = 149;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[99];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 70, 2);
	FighterData_AddReward(fighter, 0, 154, 2);
	
	fighter->headId = 6;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 99;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 70;
	fighter->moveset[2] = 154;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[100];
	SetString(fighter->name, "Gemini");
	fighter->exp = 815;
	fighter->cash = 1000;
	FighterData_AddReward(fighter, 0, 93, 1);
	FighterData_AddReward(fighter, 0, 82, 1);
	FighterData_AddReward(fighter, 0, 74, 1);
	FighterData_AddReward(fighter, 0, 83, 2);
	FighterData_AddReward(fighter, 0, 155, 2);
	
	fighter->headId = 7;
	fighter->bodyId = 80;
	fighter->charId = 80;
	fighter->actionAnimId = 3;
	fighter->ai = 100;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 182;
	fighter->mpMax = 235;
	
	fighter->attack = 35;
	fighter->defense = 6;
	fighter->speed = 43;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 82;
	fighter->moveset[2] = 74;
	fighter->moveset[3] = 83;
	fighter->moveset[4] = 155;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[101];
	SetString(fighter->name, "Dystal");
	fighter->exp = 64226;
	fighter->cash = 75996;
	
	fighter->headId = 0;
	fighter->bodyId = 92;
	fighter->charId = 92;
	fighter->actionAnimId = 3;
	fighter->ai = 101;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 1600;
	fighter->mpMax = 360;
	
	fighter->attack = 41;
	fighter->defense = 6;
	fighter->speed = 55;
	
	fighter->movesetCount = 0;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 71;
	
	
	
	fighter = &fighterData[102];
	SetString(fighter->name, "God Lulu");
	FighterData_AddReward(fighter, 1, 77, 0);
	FighterData_AddReward(fighter, 0, 18, 0);
	FighterData_AddReward(fighter, 0, 164, 0);
	FighterData_AddReward(fighter, 0, 148, 0);
	FighterData_AddReward(fighter, 0, 147, 0);
	FighterData_AddReward(fighter, 0, 165, 0);
	FighterData_AddReward(fighter, 0, 166, 0);
	fighter->exp = 105718;
	fighter->cash = 1500;
	
	fighter->headId = 82;
	fighter->bodyId = 94;
	fighter->charId = 94;
	fighter->actionAnimId = 19;
	fighter->ai = 102;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 3000;
	fighter->mpMax = 519;
	
	fighter->attack = 64;
	fighter->defense = 2;
	fighter->speed = 96;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 18;
	fighter->moveset[1] = 164;
	fighter->moveset[2] = 148;
	fighter->moveset[3] = 147;
	fighter->moveset[4] = 165;
	fighter->moveset[5] = 166;
	
	fighter->passiveCount = 3;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
	fighter->passives[2] = 85;
	
	
	
	fighter = &fighterData[103];
	SetString(fighter->name, "Tree of Evil");
	fighter->exp = 0;
	fighter->cash = 0;
	
	fighter->headId = 0;
	fighter->bodyId = 95;
	fighter->charId = 95;
	fighter->actionAnimId = 3;
	fighter->ai = 103;
	fighter->gender = FIGHTER_GENDER_OTHER;
	
	fighter->hpMax = 1444;
	fighter->mpMax = 444;
	
	fighter->attack = -9999;
	fighter->defense = -48295153;
	fighter->speed = -5;
	
	fighter->movesetCount = 1;
	fighter->moveset[0] = 167;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[104];
	SetString(fighter->name, "Panda");
	fighter->exp = 950;
	fighter->cash = 680;
	FighterData_AddReward(fighter, 1, 78, 0);
	FighterData_AddReward(fighter, 0, 5, 0);
	FighterData_AddReward(fighter, 0, 49, 0);
	FighterData_AddReward(fighter, 0, 37, 0);
	
	fighter->headId = 83;
	fighter->bodyId = 96;
	fighter->charId = 96;
	fighter->collapseSpriteId = SPR_owchar_collapse_panda;
	fighter->actionAnimId = 63;
	fighter->ai = 104;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 550;
	fighter->mpMax = 132;
	
	fighter->attack = 44;
	fighter->defense = 10;
	fighter->speed = 31;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 49;
	fighter->moveset[2] = 37;
	fighter->moveset[3] = 211;
	fighter->moveset[4] = 212;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 72;
	fighter->passives[1] = 73;
	
	
	
	fighter = &fighterData[105];
	SetString(fighter->name, "Maline");
	fighter->exp = 28518;
	fighter->cash = 50000;
	FighterData_AddReward(fighter, 1, 79, 0);
	FighterData_AddReward(fighter, 0, 168, 0);
	FighterData_AddReward(fighter, 0, 169, 0);
	FighterData_AddReward(fighter, 0, 170, 0);
	FighterData_AddReward(fighter, 0, 171, 0);
	FighterData_AddReward(fighter, 0, 72, 0);
	FighterData_AddReward(fighter, 0, 172, 0);
	
	fighter->headId = 84;
	fighter->bodyId = 97;
	fighter->charId = 97;
	fighter->collapseSpriteId = SPR_owchar_collapse_maline;
	fighter->actionAnimId = 64;
	fighter->ai = 105;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 550;
	fighter->mpMax = 395;
	
	fighter->attack = 36;
	fighter->defense = 0;
	fighter->speed = 105;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 168;
	fighter->moveset[1] = 169;
	fighter->moveset[2] = 170;
	fighter->moveset[3] = 171;
	fighter->moveset[4] = 72;
	fighter->moveset[5] = 172;
	
	fighter->passiveCount = 3;
	fighter->passives[0] = 74;
	fighter->passives[1] = 75;
	fighter->passives[2] = 79;
	
	
	
	fighter = &fighterData[106];
	SetString(fighter->name, "Cory");
	fighter->exp = 40612;
	fighter->cash = 75000;
	FighterData_AddReward(fighter, 1, 80, 0);
	FighterData_AddReward(fighter, 0, 93, 0);
	FighterData_AddReward(fighter, 0, 142, 0);
	FighterData_AddReward(fighter, 0, 173, 0);
	FighterData_AddReward(fighter, 0, 174, 0);
	FighterData_AddReward(fighter, 0, 163, 0);
	FighterData_AddReward(fighter, 0, 175, 0);
	
	fighter->headId = 85;
	fighter->bodyId = 98;
	fighter->charId = 98;
	fighter->collapseSpriteId = SPR_owchar_collapse_cory;
	fighter->actionAnimId = 65;
	fighter->ai = 106;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 1000;
	fighter->mpMax = 280;
	
	fighter->attack = 66;
	fighter->defense = 5;
	fighter->speed = 77;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 93;
	fighter->moveset[1] = 142;
	fighter->moveset[2] = 173;
	fighter->moveset[3] = 174;
	fighter->moveset[4] = 163;
	fighter->moveset[5] = 175;
	
	fighter->passiveCount = 3;
	fighter->passives[0] = 76;
	fighter->passives[1] = 77;
	fighter->passives[2] = 78;
	
	
	
	fighter = &fighterData[107];
	SetString(fighter->name, "Ultimate Lulu");
	FighterData_AddReward(fighter, 1, 77, 0);
	FighterData_AddReward(fighter, 0, 18, 0);
	FighterData_AddReward(fighter, 0, 164, 0);
	FighterData_AddReward(fighter, 0, 148, 0);
	FighterData_AddReward(fighter, 0, 147, 0);
	FighterData_AddReward(fighter, 0, 165, 0);
	FighterData_AddReward(fighter, 0, 166, 0);
	fighter->exp = 845288;
	fighter->cash = 1500;
	
	fighter->headId = 91;
	fighter->bodyId = 101;
	fighter->charId = 101;
	fighter->actionAnimId = 69;
	fighter->ai = 107;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 8754;
	fighter->mpMax = 1557;
	
	fighter->attack = 245;
	fighter->defense = 22;
	fighter->speed = 318;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 19;
	fighter->moveset[1] = 183;
	fighter->moveset[2] = 184;
	fighter->moveset[3] = 185;
	fighter->moveset[4] = 186;
	fighter->moveset[5] = 187;
	
	fighter->passiveCount = 4;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
	fighter->passives[2] = 84;
	fighter->passives[3] = 85;
	
	
	
	fighter = &fighterData[108];
	SetString(fighter->name, "Vincent");
	fighter->exp = 101794;
	fighter->cash = 250000;
	FighterData_AddReward(fighter, 1, 81, 2);
	FighterData_AddReward(fighter, 0, 188, 0);
	FighterData_AddReward(fighter, 0, 165, 0);
	FighterData_AddReward(fighter, 0, 166, 0);
	FighterData_AddReward(fighter, 0, 194, 0);
	FighterData_AddReward(fighter, 0, 190, 0);
	FighterData_AddReward(fighter, 0, 195, 0);
	FighterData_AddReward(fighter, 0, 160, 0);
	
	fighter->headId = 87;
	fighter->bodyId = 100;
	fighter->charId = 100;
	fighter->actionAnimId = 67;
	fighter->ai = 108;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 1608;
	fighter->mpMax = 505;
	
	fighter->attack = 78;
	fighter->defense = 11;
	fighter->speed = 118;
	
	fighter->movesetCount = 8;
	fighter->moveset[0] = 188;
	fighter->moveset[1] = 165;
	fighter->moveset[2] = 166;
	fighter->moveset[3] = 194;
	fighter->moveset[4] = 190;
	fighter->moveset[5] = 195;
	fighter->moveset[6] = 160;
	fighter->moveset[7] = 197;
	
	fighter->passiveCount = 4;
	fighter->passives[0] = 80;
	fighter->passives[1] = 83;
	fighter->passives[2] = 86;
	fighter->passives[3] = 87;
	
	
	
	fighter = &fighterData[109];
	SetString(fighter->name, "Jerry");
	fighter->exp = 92520;
	fighter->cash = 250000;
	FighterData_AddReward(fighter, 1, 81, 2);
	FighterData_AddReward(fighter, 0, 188, 0);
	FighterData_AddReward(fighter, 0, 165, 0);
	FighterData_AddReward(fighter, 0, 166, 0);
	FighterData_AddReward(fighter, 0, 193, 1);
	FighterData_AddReward(fighter, 0, 196, 0);
	FighterData_AddReward(fighter, 0, 126, 0);
	
	fighter->headId = 88;
	fighter->bodyId = 100;
	fighter->charId = 100;
	fighter->actionAnimId = 67;
	fighter->ai = 109;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 1680;
	fighter->mpMax = 412;
	
	fighter->attack = 72;
	fighter->defense = 8;
	fighter->speed = 130;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 188;
	fighter->moveset[1] = 165;
	fighter->moveset[2] = 166;
	fighter->moveset[3] = 193;
	fighter->moveset[4] = 196;
	fighter->moveset[5] = 126;
	
	fighter->passiveCount = 4;
	fighter->passives[0] = 80;
	fighter->passives[1] = 83;
	fighter->passives[2] = 86;
	fighter->passives[3] = 87;
	
	
	
	fighter = &fighterData[110];
	SetString(fighter->name, "Ohio");
	fighter->exp = 92520;
	fighter->cash = 250000;
	FighterData_AddReward(fighter, 1, 81, 2);
	FighterData_AddReward(fighter, 0, 188, 0);
	FighterData_AddReward(fighter, 0, 82, 0);
	FighterData_AddReward(fighter, 0, 166, 0);
	FighterData_AddReward(fighter, 0, 194, 0);
	FighterData_AddReward(fighter, 0, 189, 0);
	FighterData_AddReward(fighter, 0, 149, 0);
	
	fighter->headId = 89;
	fighter->bodyId = 100;
	fighter->charId = 100;
	fighter->actionAnimId = 67;
	fighter->ai = 110;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 1425;
	fighter->mpMax = 500;
	
	fighter->attack = 70;
	fighter->defense = 12;
	fighter->speed = 112;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 188;
	fighter->moveset[1] = 82;
	fighter->moveset[2] = 166;
	fighter->moveset[3] = 194;
	fighter->moveset[4] = 189;
	fighter->moveset[5] = 198;
	
	fighter->passiveCount = 4;
	fighter->passives[0] = 80;
	fighter->passives[1] = 83;
	fighter->passives[2] = 86;
	fighter->passives[3] = 87;
	
	
	
	fighter = &fighterData[111];
	SetString(fighter->name, "Kaiser");
	fighter->exp = 92520;
	fighter->cash = 250000;
	FighterData_AddReward(fighter, 1, 81, 2);
	FighterData_AddReward(fighter, 0, 188, 0);
	FighterData_AddReward(fighter, 0, 166, 0);
	FighterData_AddReward(fighter, 0, 76, 0);
	FighterData_AddReward(fighter, 0, 82, 0);
	FighterData_AddReward(fighter, 0, 193, 1);
	FighterData_AddReward(fighter, 0, 195, 0);
	
	fighter->headId = 90;
	fighter->bodyId = 100;
	fighter->charId = 100;
	fighter->actionAnimId = 67;
	fighter->ai = 111;
	fighter->gender = FIGHTER_GENDER_MALE;
	
	fighter->hpMax = 1508;
	fighter->mpMax = 485;
	
	fighter->attack = 89;
	fighter->defense = 8;
	fighter->speed = 109;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 188;
	fighter->moveset[1] = 166;
	fighter->moveset[2] = 76;
	fighter->moveset[3] = 82;
	fighter->moveset[4] = 193;
	fighter->moveset[5] = 195;
	
	fighter->passiveCount = 4;
	fighter->passives[0] = 80;
	fighter->passives[1] = 83;
	fighter->passives[2] = 86;
	fighter->passives[3] = 87;
	
	
	
	// Demo-exclusive
	
	fighter = &fighterData[191];
	SetString(fighter->name, "Omega Lulu");
	fighter->exp = 9001;
	fighter->cash = 8999;
	FighterData_AddReward(fighter, 1, 27, 0);
	FighterData_AddReward(fighter, 0, 17, 0);
	FighterData_AddReward(fighter, 0, 28, 0);
	FighterData_AddReward(fighter, 0, 191, 0);
	
	fighter->headId = 16;
	fighter->bodyId = 26;
	fighter->charId = 26;
	fighter->actionAnimId = 19;
	fighter->ai = 191;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 300;
	fighter->mpMax = 125;
	
	fighter->attack = 36;
	fighter->defense = 1;
	fighter->speed = 43;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 18;
	fighter->moveset[1] = 19;
	fighter->moveset[2] = 20;
	fighter->moveset[3] = 17;
	fighter->moveset[4] = 191;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
	
	
	
	fighter = &fighterData[192];
	SetString(fighter->name, "Omega Lulu");
	fighter->exp = 9001;
	fighter->cash = 8999;
	FighterData_AddReward(fighter, 1, 27, 0);
	FighterData_AddReward(fighter, 0, 17, 0);
	FighterData_AddReward(fighter, 0, 28, 0);
	FighterData_AddReward(fighter, 0, 191, 0);
	
	fighter->headId = 16;
	fighter->bodyId = 26;
	fighter->charId = 26;
	fighter->actionAnimId = 19;
	fighter->ai = 192;
	fighter->gender = FIGHTER_GENDER_FEMALE;
	
	fighter->hpMax = 300;
	fighter->mpMax = 125;
	
	fighter->attack = 36;
	fighter->defense = 1;
	fighter->speed = 43;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 192;
	fighter->moveset[1] = 18;
	fighter->moveset[2] = 19;
	fighter->moveset[3] = 17;
	fighter->moveset[4] = 20;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 5;
	fighter->passives[1] = 7;
}

void FighterData_AddReward(FighterData* fighter, int type, int id, int rarity) {
	fighter->rewards[fighter->rewardCount].type = type;
	fighter->rewards[fighter->rewardCount].id = id;
	fighter->rewards[fighter->rewardCount].rarity = rarity;
	fighter->rewardCount++;
}
