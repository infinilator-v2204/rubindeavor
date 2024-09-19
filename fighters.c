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
	
	fighter->hpMax = 8;
	fighter->mpMax = 2;
	
	fighter->attack = 2;
	fighter->defense = 0;
	fighter->speed = 3;
	
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
	
	fighter->hpMax = 10;
	fighter->mpMax = 2;
	
	fighter->attack = 2;
	fighter->defense = 0;
	fighter->speed = 5;
	
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
	
	fighter->hpMax = 17;
	fighter->mpMax = 6;
	
	fighter->attack = 6;
	fighter->defense = 0;
	fighter->speed = 4;
	
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
	
	fighter->hpMax = 24;
	fighter->mpMax = 8;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 8;
	
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
	
	fighter->hpMax = 140;
	fighter->mpMax = 50;
	
	fighter->attack = 11;
	fighter->defense = 0;
	fighter->speed = 7;
	
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
	
	fighter->hpMax = 24;
	fighter->mpMax = 10;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 12;
	
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
	
	fighter->hpMax = 60;
	fighter->mpMax = 30;
	
	fighter->attack = 17;
	fighter->defense = 0;
	fighter->speed = 15;
	
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
	
	fighter->hpMax = 45;
	fighter->mpMax = 15;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 9;
	
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
	
	fighter->hpMax = 18;
	fighter->mpMax = 5;
	
	fighter->attack = 6;
	fighter->defense = 0;
	fighter->speed = 3;
	
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
	
	fighter->hpMax = 22;
	fighter->mpMax = 6;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 6;
	
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
	
	fighter->hpMax = 30;
	fighter->mpMax = 11;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 10;
	
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
	
	fighter->hpMax = 32;
	fighter->mpMax = 10;
	
	fighter->attack = 14;
	fighter->defense = 0;
	fighter->speed = 7;
	
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
	
	fighter->hpMax = 25;
	fighter->mpMax = 12;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 6;
	
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
	
	fighter->hpMax = 60;
	fighter->mpMax = 20;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 20;
	
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
	
	fighter->hpMax = 45;
	fighter->mpMax = 24;
	
	fighter->attack = 12;
	fighter->defense = 0;
	fighter->speed = 8;
	
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
	
	fighter->hpMax = 48;
	fighter->mpMax = 20;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 15;
	
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
	
	fighter->hpMax = 120;
	fighter->mpMax = 55;
	
	fighter->attack = 27;
	fighter->defense = 0;
	fighter->speed = 28;
	
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
	
	fighter->hpMax = 200;
	fighter->mpMax = 180;
	
	fighter->attack = 38;
	fighter->defense = 0;
	fighter->speed = 40;
	
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
	
	fighter->hpMax = 26;
	fighter->mpMax = 11;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 8;
	
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
	
	fighter->hpMax = 15;
	fighter->mpMax = 6;
	
	fighter->attack = 4;
	fighter->defense = 0;
	fighter->speed = 9;
	
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
	
	fighter->hpMax = 60;
	fighter->mpMax = 16;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 6;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 12;
	fighter->moveset[2] = 13;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 12;
	
	
	
	fighter = &fighterData[32];
	SetString(fighter->name, "Leaf Crew");
	fighter->exp = 90;
	fighter->cash = 8;
	FighterData_AddReward(fighter, 1, 14, 1);
	FighterData_AddReward(fighter, 0, 5, 1);
	FighterData_AddReward(fighter, 0, 6, 1);
	FighterData_AddReward(fighter, 0, 7, 1);
	
	fighter->headId = 14;
	fighter->bodyId = 13;
	fighter->charId = 13;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	
	fighter->hpMax = 24;
	fighter->mpMax = 8;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 8;
	
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
	
	fighter->hpMax = 400;
	fighter->mpMax = 150;
	
	fighter->attack = 20;
	fighter->defense = 0;
	fighter->speed = 19;
	
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
	
	fighter->hpMax = 20;
	fighter->mpMax = 20;
	
	fighter->attack = 8;
	fighter->defense = 0;
	fighter->speed = 14;
	
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
	
	fighter->hpMax = 220;
	fighter->mpMax = 80;
	
	fighter->attack = 30;
	fighter->defense = 0;
	fighter->speed = 10;
	
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
	
	fighter->hpMax = 56;
	fighter->mpMax = 18;
	
	fighter->attack = 12;
	fighter->defense = 0;
	fighter->speed = 9;
	
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
	
	fighter->hpMax = 46;
	fighter->mpMax = 23;
	
	fighter->attack = 10;
	fighter->defense = 0;
	fighter->speed = 18;
	
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
	
	fighter->hpMax = 85;
	fighter->mpMax = 38;
	
	fighter->attack = 18;
	fighter->defense = 0;
	fighter->speed = 26;
	
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
	
	fighter->hpMax = 48;
	fighter->mpMax = 20;
	
	fighter->attack = 18;
	fighter->defense = 0;
	fighter->speed = 14;
	
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
	
	fighter->hpMax = 82;
	fighter->mpMax = 32;
	
	fighter->attack = 23;
	fighter->defense = 0;
	fighter->speed = 17;
	
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
	
	fighter->hpMax = 360;
	fighter->mpMax = 50;
	
	fighter->attack = 32;
	fighter->defense = 0;
	fighter->speed = 22;
	
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
	
	fighter->hpMax = 54;
	fighter->mpMax = 30;
	
	fighter->attack = 13;
	fighter->defense = 0;
	fighter->speed = 35;
	
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
	fighter->exp = 200;
	fighter->cash = 70;
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
	
	fighter->hpMax = 105;
	fighter->mpMax = 60;
	
	fighter->attack = 26;
	fighter->defense = 2;
	fighter->speed = 36;
	
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
	
	fighter->hpMax = 60;
	fighter->mpMax = 27;
	
	fighter->attack = 18;
	fighter->defense = 1;
	fighter->speed = 12;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 5;
	fighter->moveset[1] = 6;
	fighter->moveset[2] = 48;
	fighter->moveset[3] = 49;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[45];
	SetString(fighter->name, "G Police");
	fighter->exp = 275;
	fighter->cash = 80;
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
	
	fighter->hpMax = 110;
	fighter->mpMax = 75;
	
	fighter->attack = 28;
	fighter->defense = 1;
	fighter->speed = 32;
	
	fighter->movesetCount = 4;
	fighter->moveset[0] = 49;
	fighter->moveset[1] = 50;
	fighter->moveset[2] = 51;
	fighter->moveset[3] = 52;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[46];
	SetString(fighter->name, "Amp");
	fighter->exp = 10000;
	fighter->cash = 5000;
	FighterData_AddReward(fighter, 1, 39, 0);
	FighterData_AddReward(fighter, 0, 5, 0);
	FighterData_AddReward(fighter, 0, 6, 0);
	FighterData_AddReward(fighter, 0, 53, 0);
	FighterData_AddReward(fighter, 0, 54, 0);
	FighterData_AddReward(fighter, 0, 55, 0);
	
	fighter->headId = 40;
	fighter->bodyId = 42;
	fighter->charId = 42;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	
	fighter->hpMax = 500;
	fighter->mpMax = 250;
	
	fighter->attack = 45;
	fighter->defense = 2;
	fighter->speed = 45;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 54;
	fighter->moveset[1] = 54;
	fighter->moveset[2] = 53;
	fighter->moveset[3] = 54;
	fighter->moveset[4] = 55;
	
	fighter->passiveCount = 0;
	
	
	
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
	
	fighter->hpMax = 16;
	fighter->mpMax = 8;
	
	fighter->attack = 1;
	fighter->defense = 0;
	fighter->speed = 5;
	
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
	
	fighter->hpMax = 16;
	fighter->mpMax = 8;
	
	fighter->attack = 1;
	fighter->defense = 0;
	fighter->speed = 8;
	
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
	
	fighter->hpMax = 11;
	fighter->mpMax = 3;
	
	fighter->attack = 3;
	fighter->defense = 0;
	fighter->speed = 6;
	
	fighter->movesetCount = 3;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 2;
	fighter->moveset[2] = 25;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[50];
	SetString(fighter->name, "Wax Knight");
	fighter->exp = 60;
	fighter->cash = 4;
	FighterData_AddReward(fighter, 1, 42, 5);
	
	fighter->headId = 43;
	fighter->bodyId = 45;
	fighter->charId = 45;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	
	fighter->hpMax = 60;
	fighter->mpMax = 40;
	
	fighter->attack = 32;
	fighter->defense = 4;
	fighter->speed = 10;
	
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
	
	fighter->hpMax = 500;
	fighter->mpMax = 160;
	
	fighter->attack = 30;
	fighter->defense = 0;
	fighter->speed = 44;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 56;
	fighter->moveset[1] = 57;
	fighter->moveset[2] = 58;
	fighter->moveset[3] = 59;
	fighter->moveset[4] = 60;
	
	fighter->passiveCount = 0;
	
	
	
	fighter = &fighterData[52];
	SetString(fighter->name, "Death Knife");
	fighter->exp = 55;
	fighter->cash = 0;
	
	fighter->headId = 0;
	fighter->bodyId = 47;
	fighter->charId = 47;
	fighter->actionAnimId = 2;
	fighter->ai = 0;
	
	fighter->hpMax = 40;
	fighter->mpMax = 22;
	
	fighter->attack = 25;
	fighter->defense = 0;
	fighter->speed = 15;
	
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
	
	fighter->hpMax = 1;
	fighter->mpMax = 93;
	
	fighter->attack = 20;
	fighter->defense = 0;
	fighter->speed = 33;
	
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
	
	fighter->hpMax = 80;
	fighter->mpMax = 13;
	
	fighter->attack = 18;
	fighter->defense = 12;
	fighter->speed = 1;
	
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
	
	fighter->hpMax = 1500; //99000
	fighter->mpMax = 750; //3758
	
	fighter->attack = 30;
	fighter->defense = 9;
	fighter->speed = 75;
	
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
	
	fighter->hpMax = 60;
	fighter->mpMax = 35;
	
	fighter->attack = 21;
	fighter->defense = 0;
	fighter->speed = 20;
	
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
	
	fighter->hpMax = 82;
	fighter->mpMax = 40;
	
	fighter->attack = 24;
	fighter->defense = 0;
	fighter->speed = 15;
	
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
	
	fighter->hpMax = 137;
	fighter->mpMax = 50;
	
	fighter->attack = 24;
	fighter->defense = 1;
	fighter->speed = 14;
	
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
	FighterData_AddReward(fighter, 0, 2, 0);
	FighterData_AddReward(fighter, 0, 3, 0);
	FighterData_AddReward(fighter, 0, 67, 0);
	FighterData_AddReward(fighter, 0, 68, 0);
	FighterData_AddReward(fighter, 0, 74, 0);
	
	fighter->headId = 49;
	fighter->bodyId = 54;
	fighter->charId = 54;
	fighter->actionAnimId = 2;
	fighter->ai = 59;
	
	fighter->hpMax = 110;
	fighter->mpMax = 78;
	
	fighter->attack = 22;
	fighter->defense = 0;
	fighter->speed = 29;
	
	fighter->movesetCount = 5;
	fighter->moveset[0] = 2;
	fighter->moveset[1] = 3;
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
	
	fighter->hpMax = 94;
	fighter->mpMax = 155;
	
	fighter->attack = 16;
	fighter->defense = 0;
	fighter->speed = 20;
	
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
	
	fighter->hpMax = 50;
	fighter->mpMax = 28;
	
	fighter->attack = 16;
	fighter->defense = 0;
	fighter->speed = 16;
	
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
	
	fighter->hpMax = 100;
	fighter->mpMax = 64;
	
	fighter->attack = 22;
	fighter->defense = 0;
	fighter->speed = 28;
	
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
	
	fighter->hpMax = 140;
	fighter->mpMax = 40;
	
	fighter->attack = 24;
	fighter->defense = 0;
	fighter->speed = 5;
	
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
	
	fighter->hpMax = 440;
	fighter->mpMax = 160;
	
	fighter->attack = 40;
	fighter->defense = 0;
	fighter->speed = 40;
	
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
	
	fighter->hpMax = 337;
	fighter->mpMax = 180;
	
	fighter->attack = 21;
	fighter->defense = 0;
	fighter->speed = 20;
	
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
	
	fighter->hpMax = 149;
	fighter->mpMax = 84;
	
	fighter->attack = 33;
	fighter->defense = -21;
	fighter->speed = 4;
	
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
	
	fighter->hpMax = 149;
	fighter->mpMax = 84;
	
	fighter->attack = 33;
	fighter->defense = -21;
	fighter->speed = 4;
	
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
	
	fighter->hpMax = 13;
	fighter->mpMax = 13;
	
	fighter->attack = 13;
	fighter->defense = 6;
	fighter->speed = 22;
	
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
	
	fighter->hpMax = 40;
	fighter->mpMax = 5;
	
	fighter->attack = 5;
	fighter->defense = 0;
	fighter->speed = 1;
	
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
	
	fighter->hpMax = 60;
	fighter->mpMax = 35;
	
	fighter->attack = 21;
	fighter->defense = 0;
	fighter->speed = 20;
	
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
	
	fighter->hpMax = 84;
	fighter->mpMax = 41;
	
	fighter->attack = 24;
	fighter->defense = 0;
	fighter->speed = 16;
	
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
	
	fighter->hpMax = 15;
	fighter->mpMax = 10;
	
	fighter->attack = 37;
	fighter->defense = 0;
	fighter->speed = 13;
	
	fighter->movesetCount = 2;
	fighter->moveset[0] = 1;
	fighter->moveset[1] = 84;
	
	fighter->passiveCount = 1;
	fighter->passives[0] = 34;
	
	
	
	fighter = &fighterData[73];
	SetString(fighter->name, "Nekin");
	fighter->exp = 1200;
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
	
	fighter->hpMax = 316;
	fighter->mpMax = 125;
	
	fighter->attack = 41;
	fighter->defense = 0;
	fighter->speed = 31;
	
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
	
	fighter->hpMax = 122;
	fighter->mpMax = 70;
	
	fighter->attack = 27;
	fighter->defense = 2;
	fighter->speed = 38;
	
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
	
	fighter->hpMax = 142;
	fighter->mpMax = 56;
	
	fighter->attack = 32;
	fighter->defense = 4;
	fighter->speed = 15;
	
	fighter->movesetCount = 6;
	fighter->moveset[0] = 36;
	fighter->moveset[1] = 94;
	fighter->moveset[2] = 93;
	fighter->moveset[3] = 92;
	fighter->moveset[4] = 26;
	
	fighter->passiveCount = 2;
	fighter->passives[0] = 40;
	fighter->passives[1] = 33;
	
	
	
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
	
	fighter->hpMax = 300;
	fighter->mpMax = 125;
	
	fighter->attack = 36;
	fighter->defense = 1;
	fighter->speed = 38;
	
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
	
	fighter->hpMax = 300;
	fighter->mpMax = 125;
	
	fighter->attack = 36;
	fighter->defense = 1;
	fighter->speed = 38;
	
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
