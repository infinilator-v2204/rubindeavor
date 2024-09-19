#include "generic.h"
#include "armor.h"

Armor armorData[OBJECT_COUNT_MAX];

void LoadArmorData() {
	Armor* armor;
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		armorData[i].specialAbility = 0;
		armorData[i].ranged = false;
	}
	
	
	
	armor = &armorData[0];
	SetString(armor->name, "None");
	armor->cost = 0;
	
	armor->headId = 0;
	armor->bodyId = 0;
	armor->actionAnimId = 0;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[1];
	SetString(armor->name, "Ruby");
	armor->cost = 0;
	
	armor->headId = 1;
	armor->bodyId = 1;
	armor->actionAnimId = 1;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[2];
	SetString(armor->name, "Noah");
	armor->cost = 0;
	
	armor->headId = 2;
	armor->bodyId = 3;
	armor->actionAnimId = 1;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[3];
	SetString(armor->name, "Emmet");
	armor->cost = 0;
	
	armor->headId = 3;
	armor->bodyId = 4;
	armor->actionAnimId = 1;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[4];
	SetString(armor->name, "Sally");
	armor->cost = 0;
	
	armor->headId = 4;
	armor->bodyId = 5;
	armor->actionAnimId = 1;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[5];
	SetString(armor->name, "Diego");
	armor->cost = 0;
	
	armor->headId = 1;
	armor->bodyId = 1;
	armor->actionAnimId = 1;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[6];
	SetString(armor->name, "Tony");
	armor->cost = 0;
	
	armor->headId = 1;
	armor->bodyId = 1;
	armor->actionAnimId = 1;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[7];
	SetString(armor->name, "Perry");
	armor->cost = 0;
	
	armor->headId = 7;
	armor->bodyId = 8;
	armor->actionAnimId = 1;
	
	armor->hp = 0;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	
	
	
	armor = &armorData[11];
	SetString(armor->name, "Hobo");
	armor->cost = 0;
	
	armor->headId = 11;
	armor->bodyId = 11;
	armor->actionAnimId = 1;
	
	armor->hp = 1;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[12];
	SetString(armor->name, "Navy Gang");
	armor->cost = 0;
	
	armor->headId = 11;
	armor->bodyId = 12;
	armor->actionAnimId = 1;
	
	armor->hp = 1;
	armor->mp = 0;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 1;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[13];
	SetString(armor->name, "Sally");
	armor->cost = 1;
	
	armor->headId = 4;
	armor->bodyId = 5;
	armor->actionAnimId = 2;
	
	armor->hp = 4;
	armor->mp = 1;
	armor->attack = 2;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 1;
	armor->passives[0] = 2;
	
	
	
	armor = &armorData[14];
	SetString(armor->name, "Leaf Crew");
	armor->cost = 1;
	
	armor->headId = 12;
	armor->bodyId = 13;
	armor->actionAnimId = 2;
	
	armor->hp = 3;
	armor->mp = 2;
	armor->attack = 1;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 1;
	armor->passives[0] = 3;
	
	
	
	armor = &armorData[15];
	SetString(armor->name, "Lisao");
	armor->cost = 4;
	
	armor->headId = 15;
	armor->bodyId = 14;
	armor->actionAnimId = 4;
	
	armor->hp = 15;
	armor->mp = 8;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 2;
	armor->passives[0] = 4;
	armor->passives[1] = 3;
	
	
	
	armor = &armorData[16];
	SetString(armor->name, "Lulu");
	armor->cost = 2;
	
	armor->headId = 16;
	armor->bodyId = 15;
	armor->actionAnimId = 1;
	
	armor->hp = 2;
	armor->mp = 1;
	armor->attack = 2;
	armor->defense = 0;
	armor->speed = 6;
	
	armor->passiveCount = 1;
	armor->passives[0] = 5;
	
	
	
	armor = &armorData[17];
	SetString(armor->name, "Blazin' Lulu");
	armor->cost = 4;
	
	armor->headId = 16;
	armor->bodyId = 16;
	armor->actionAnimId = 19;
	
	armor->hp = 2;
	armor->mp = 1;
	armor->attack = 8;
	armor->defense = 0;
	armor->speed = 6;
	
	armor->passiveCount = 2;
	armor->passives[0] = 5;
	armor->passives[1] = 7;
	
	
	
	armor = &armorData[18];
	SetString(armor->name, "Police");
	armor->cost = 2;
	
	armor->headId = 17;
	armor->bodyId = 17;
	armor->actionAnimId = 2;
	
	armor->hp = 7;
	armor->mp = 4;
	armor->attack = 3;
	armor->defense = 0;
	armor->speed = 3;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[19];
	SetString(armor->name, "Farmer");
	armor->cost = 1;
	
	armor->headId = 19;
	armor->bodyId = 18;
	armor->actionAnimId = 2;
	
	armor->hp = 4;
	armor->mp = 0;
	armor->attack = 2;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[20];
	SetString(armor->name, "Knife Thug");
	armor->cost = 1;
	
	armor->headId = 11;
	armor->bodyId = 19;
	armor->actionAnimId = 2;
	
	armor->hp = 3;
	armor->mp = 1;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 1;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[21];
	SetString(armor->name, "Vandal B");
	armor->cost = 2;
	
	armor->headId = 20;
	armor->bodyId = 20;
	armor->actionAnimId = 2;
	
	armor->hp = 5;
	armor->mp = 3;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 3;
	
	armor->passiveCount = 1;
	armor->passives[0] = 6;
	
	
	
	armor = &armorData[22];
	SetString(armor->name, "Vandal F");
	armor->cost = 2;
	
	armor->headId = 21;
	armor->bodyId = 21;
	armor->actionAnimId = 3;
	
	armor->hp = 8;
	armor->mp = 1;
	armor->attack = 6;
	armor->defense = 0;
	armor->speed = 1;
	
	armor->passiveCount = 1;
	armor->passives[0] = 6;
	
	
	
	armor = &armorData[23];
	SetString(armor->name, "Nurse");
	armor->cost = 1;
	
	armor->headId = 22;
	armor->bodyId = 22;
	armor->actionAnimId = 1;
	
	armor->hp = 1;
	armor->mp = 5;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 1;
	
	armor->passiveCount = 1;
	armor->passives[0] = 8;
	
	
	
	armor = &armorData[24];
	SetString(armor->name, "Jackie");
	armor->cost = 3;
	
	armor->headId = 23;
	armor->bodyId = 23;
	armor->actionAnimId = 1;
	
	armor->hp = 8;
	armor->mp = 4;
	armor->attack = 2;
	armor->defense = 0;
	armor->speed = 7;
	
	armor->passiveCount = 1;
	armor->passives[0] = 9;
	
	
	
	armor = &armorData[25];
	SetString(armor->name, "Electra");
	armor->cost = 3;
	
	armor->headId = 24;
	armor->bodyId = 24;
	armor->actionAnimId = 3;
	
	armor->hp = 5;
	armor->mp = 5;
	armor->attack = 6;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 1;
	armor->passives[0] = 10;
	
	
	
	armor = &armorData[26];
	SetString(armor->name, "Ray");
	armor->cost = 3;
	
	armor->headId = 25;
	armor->bodyId = 25;
	armor->actionAnimId = 2;
	
	armor->hp = 7;
	armor->mp = 3;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 5;
	
	armor->passiveCount = 1;
	armor->passives[0] = 11;
	
	
	
	armor = &armorData[27];
	SetString(armor->name, "Omega Lulu");
	armor->cost = 13;
	
	armor->headId = 16;
	armor->bodyId = 26;
	armor->actionAnimId = 19;
	
	armor->hp = 16;
	armor->mp = 8;
	armor->attack = 12;
	armor->defense = 0;
	armor->speed = 16;
	
	armor->passiveCount = 2;
	armor->passives[0] = 5;
	armor->passives[1] = 7;
	
	
	
	armor = &armorData[28];
	SetString(armor->name, "Dia");
	armor->cost = 7;
	
	armor->headId = 29;
	armor->bodyId = 29;
	armor->actionAnimId = 18;
	
	armor->hp = 20;
	armor->mp = 25;
	armor->attack = 5;
	armor->defense = 0;
	armor->speed = 4;
	
	armor->passiveCount = 2;
	armor->passives[0] = 13;
	armor->passives[1] = 14;
	
	
	
	armor = &armorData[29];
	SetString(armor->name, "Police Captain");
	armor->cost = 3;
	
	armor->headId = 30;
	armor->bodyId = 32;
	armor->actionAnimId = 2;
	
	armor->hp = 10;
	armor->mp = 5;
	armor->attack = 3;
	armor->defense = 0;
	armor->speed = 3;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[30];
	SetString(armor->name, "SYNC Office");
	armor->cost = 3;
	
	armor->headId = 31;
	armor->bodyId = 33;
	armor->actionAnimId = 1;
	
	armor->hp = 6;
	armor->mp = 5;
	armor->attack = 3;
	armor->defense = 0;
	armor->speed = 5;
	
	armor->passiveCount = 1;
	armor->passives[0] = 17;
	
	
	
	armor = &armorData[31];
	SetString(armor->name, "Josh");
	armor->cost = 5;
	
	armor->headId = 32;
	armor->bodyId = 34;
	armor->actionAnimId = 1;
	
	armor->hp = 12;
	armor->mp = 9;
	armor->attack = 5;
	armor->defense = 0;
	armor->speed = 7;
	
	armor->passiveCount = 1;
	armor->passives[0] = 17;
	
	
	
	armor = &armorData[32];
	SetString(armor->name, "Pirate");
	armor->cost = 3;
	
	armor->headId = 33;
	armor->bodyId = 35;
	armor->actionAnimId = 2;
	
	armor->hp = 8;
	armor->mp = 4;
	armor->attack = 6;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 1;
	armor->passives[0] = 19;
	
	
	
	armor = &armorData[33];
	SetString(armor->name, "Pirate Cap'n");
	armor->cost = 5;
	
	armor->headId = 34;
	armor->bodyId = 36;
	armor->actionAnimId = 2;
	
	armor->hp = 11;
	armor->mp = 6;
	armor->attack = 8;
	armor->defense = 0;
	armor->speed = 3;
	
	armor->passiveCount = 2;
	armor->passives[0] = 19;
	armor->passives[1] = 20;
	
	
	
	armor = &armorData[34];
	SetString(armor->name, "Sanji");
	armor->cost = 7;
	
	armor->headId = 35;
	armor->bodyId = 37;
	armor->actionAnimId = 29;
	
	armor->hp = 30;
	armor->mp = 22;
	armor->attack = 10;
	armor->defense = 0;
	armor->speed = 5;
	
	armor->passiveCount = 3;
	armor->passives[0] = 16;
	armor->passives[1] = 19;
	armor->passives[2] = 20;
	
	
	
	armor = &armorData[35];
	SetString(armor->name, "Ninja");
	armor->cost = 6;
	
	armor->headId = 36;
	armor->bodyId = 38;
	armor->actionAnimId = 1;
	
	armor->hp = 7;
	armor->mp = 6;
	armor->attack = 3;
	armor->defense = 0;
	armor->speed = 12;
	
	armor->passiveCount = 1;
	armor->passives[0] = 11;
	
	
	
	armor = &armorData[36];
	SetString(armor->name, "Secret Agent");
	armor->cost = 10;
	
	armor->headId = 39;
	armor->bodyId = 39;
	armor->actionAnimId = 1;
	
	armor->hp = 16;
	armor->mp = 15;
	armor->attack = 7;
	armor->defense = 2;
	armor->speed = 11;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[37];
	SetString(armor->name, "B Police");
	armor->cost = 4;
	
	armor->headId = 37;
	armor->bodyId = 40;
	armor->actionAnimId = 2;
	
	armor->hp = 10;
	armor->mp = 6;
	armor->attack = 4;
	armor->defense = 1;
	armor->speed = 4;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[38];
	SetString(armor->name, "G Police");
	armor->cost = 10;
	
	armor->headId = 38;
	armor->bodyId = 41;
	armor->actionAnimId = 2;
	
	armor->hp = 18;
	armor->mp = 22;
	armor->attack = 9;
	armor->defense = 1;
	armor->speed = 10;
	
	armor->passiveCount = 0;
	armor->ranged = true;
	
	
	
	armor = &armorData[39];
	SetString(armor->name, "Amp");
	armor->cost = 20;
	
	armor->headId = 40;
	armor->bodyId = 42;
	armor->actionAnimId = 2;
	
	armor->hp = 40;
	armor->mp = 60;
	armor->attack = 20;
	armor->defense = 2;
	armor->speed = 16;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[40];
	SetString(armor->name, "River");
	armor->cost = 1;
	
	armor->headId = 41;
	armor->bodyId = 43;
	armor->actionAnimId = 1;
	
	armor->hp = 2;
	armor->mp = 1;
	armor->attack = 0;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[41];
	SetString(armor->name, "Frank");
	armor->cost = 1;
	
	armor->headId = 42;
	armor->bodyId = 44;
	armor->actionAnimId = 2;
	
	armor->hp = 1;
	armor->mp = 1;
	armor->attack = 1;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[42];
	SetString(armor->name, "Wax Knight");
	armor->cost = 3;
	
	armor->headId = 43;
	armor->bodyId = 45;
	armor->actionAnimId = 2;
	
	armor->hp = 6;
	armor->mp = 3;
	armor->attack = 8;
	armor->defense = 4;
	armor->speed = 0;
	
	armor->passiveCount = 1;
	armor->passives[0] = 18;
	
	
	
	armor = &armorData[43];
	SetString(armor->name, "Flora");
	armor->cost = 17;
	
	armor->headId = 44;
	armor->bodyId = 46;
	armor->actionAnimId = 18;
	
	armor->hp = 27;
	armor->mp = 25;
	armor->attack = 12;
	armor->defense = 0;
	armor->speed = 15;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[44];
	SetString(armor->name, "Kelly");
	armor->cost = 4;
	
	armor->headId = 46;
	armor->bodyId = 51;
	armor->actionAnimId = 3;
	
	armor->hp = 8;
	armor->mp = 6;
	armor->attack = 6;
	armor->defense = 0;
	armor->speed = 6;
	
	armor->passiveCount = 1;
	armor->passives[0] = 21;
	
	
	
	armor = &armorData[45];
	SetString(armor->name, "Neveah");
	armor->cost = 4;
	
	armor->headId = 47;
	armor->bodyId = 52;
	armor->actionAnimId = 3;
	
	armor->hp = 10;
	armor->mp = 8;
	armor->attack = 7;
	armor->defense = 0;
	armor->speed = 4;
	
	armor->passiveCount = 2;
	armor->passives[0] = 21;
	armor->passives[1] = 22;
	
	
	
	armor = &armorData[46];
	SetString(armor->name, "Brook");
	armor->cost = 6;
	
	armor->headId = 48;
	armor->bodyId = 53;
	armor->actionAnimId = 1;
	
	armor->hp = 27;
	armor->mp = 4;
	armor->attack = 7;
	armor->defense = 1;
	armor->speed = 1;
	
	armor->passiveCount = 1;
	armor->passives[0] = 25;
	
	
	
	armor = &armorData[47];
	SetString(armor->name, "Tom");
	armor->cost = 6;
	
	armor->headId = 49;
	armor->bodyId = 54;
	armor->actionAnimId = 2;
	
	armor->hp = 12;
	armor->mp = 12;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 9;
	
	armor->passiveCount = 2;
	armor->passives[0] = 23;
	armor->passives[1] = 24;
	
	
	
	armor = &armorData[48];
	SetString(armor->name, "Cindy");
	armor->cost = 6;
	
	armor->headId = 50;
	armor->bodyId = 55;
	armor->actionAnimId = 1;
	
	armor->hp = 2;
	armor->mp = 40;
	armor->attack = 1;
	armor->defense = 0;
	armor->speed = 3;
	
	armor->passiveCount = 1;
	armor->passives[0] = 26;
	
	
	
	armor = &armorData[49];
	SetString(armor->name, "Slime");
	armor->cost = 2;
	
	armor->headId = 51;
	armor->bodyId = 56;
	armor->actionAnimId = 3;
	
	armor->hp = 6;
	armor->mp = 2;
	armor->attack = 1;
	armor->defense = 0;
	armor->speed = 3;
	
	armor->passiveCount = 1;
	armor->passives[0] = 12;
	
	
	
	armor = &armorData[50];
	SetString(armor->name, "Spider");
	armor->cost = 4;
	
	armor->headId = 51;
	armor->bodyId = 57;
	armor->actionAnimId = 3;
	
	armor->hp = 10;
	armor->mp = 10;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[51];
	SetString(armor->name, "Ozone Mafia");
	armor->cost = 5;
	
	armor->headId = 52;
	armor->bodyId = 58;
	armor->actionAnimId = 2;
	
	armor->hp = 7;
	armor->mp = 10;
	armor->attack = 5;
	armor->defense = 0;
	armor->speed = 2;
	
	armor->passiveCount = 1;
	armor->passives[0] = 31;
	armor->ranged = true;
	
	
	
	armor = &armorData[52];
	SetString(armor->name, "Don");
	armor->cost = 8;
	
	armor->headId = 53;
	armor->bodyId = 59;
	armor->actionAnimId = 2;
	
	armor->hp = 11;
	armor->mp = 14;
	armor->attack = 7;
	armor->defense = 0;
	armor->speed = 7;
	
	armor->passiveCount = 2;
	armor->passives[0] = 31;
	armor->passives[1] = 32;
	armor->ranged = true;
	
	
	
	armor = &armorData[53];
	SetString(armor->name, "Nate");
	armor->cost = 8;
	
	armor->headId = 54;
	armor->bodyId = 60;
	armor->actionAnimId = 3;
	
	armor->hp = 20;
	armor->mp = 10;
	armor->attack = 9;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 2;
	armor->passives[0] = 31;
	armor->passives[1] = 33;
	armor->ranged = true;
	
	
	
	armor = &armorData[54];
	SetString(armor->name, "Vulkan");
	armor->cost = 15;
	
	armor->headId = 55;
	armor->bodyId = 61;
	armor->actionAnimId = 26;
	
	armor->hp = 32;
	armor->mp = 30;
	armor->attack = 11;
	armor->defense = 0;
	armor->speed = 14;
	
	armor->passiveCount = 3;
	armor->passives[0] = 28;
	armor->passives[1] = 29;
	armor->passives[2] = 30;
	
	
	
	armor = &armorData[55];
	SetString(armor->name, "Hellgoner");
	armor->cost = 10;
	
	armor->headId = 51;
	armor->bodyId = 65;
	armor->actionAnimId = 28;
	
	armor->hp = 33;
	armor->mp = 33;
	armor->attack = 36;
	armor->defense = 0;
	armor->speed = 38;
	
	armor->passiveCount = 0;
	armor->specialAbility = 1;
	armor->ranged = true;
	
	
	
	armor = &armorData[56];
	SetString(armor->name, "Luna");
	armor->cost = 10;
	
	armor->headId = 56;
	armor->bodyId = 62;
	armor->actionAnimId = 1;
	
	armor->hp = 25;
	armor->mp = 25;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 5;
	
	armor->passiveCount = 2;
	armor->passives[0] = 31;
	armor->passives[1] = 27;
	
	
	
	armor = &armorData[57];
	SetString(armor->name, "Perry");
	armor->cost = 1;
	
	armor->headId = 7;
	armor->bodyId = 67;
	armor->actionAnimId = 2;
	
	armor->hp = 1;
	armor->mp = 1;
	armor->attack = 4;
	armor->defense = 0;
	armor->speed = 0;
	
	armor->passiveCount = 0;
	
	
	
	armor = &armorData[58];
	SetString(armor->name, "Brian");
	armor->cost = 1;
	
	armor->headId = 58;
	armor->bodyId = 68;
	armor->actionAnimId = 3;
	
	armor->hp = 1;
	armor->mp = 1;
	armor->attack = 10;
	armor->defense = 0;
	armor->speed = 3;
	
	armor->passiveCount = 1;
	armor->passives[0] = 34;
	armor->specialAbility = 2;
	
	
	
	armor = &armorData[59];
	SetString(armor->name, "Nekin");
	armor->cost = 12;
	
	armor->headId = 59;
	armor->bodyId = 69;
	armor->actionAnimId = 30;
	
	armor->hp = 19;
	armor->mp = 20;
	armor->attack = 12;
	armor->defense = 0;
	armor->speed = 8;
	
	armor->passiveCount = 3;
	armor->passives[0] = 35;
	armor->passives[1] = 36;
	armor->passives[2] = 37;
	
	
	
	armor = &armorData[60];
	SetString(armor->name, "Adios");
	armor->cost = 12;
	
	armor->headId = 61;
	armor->bodyId = 71;
	armor->actionAnimId = 1;
	
	armor->hp = 20;
	armor->mp = 16;
	armor->attack = 7;
	armor->defense = 2;
	armor->speed = 13;
	
	armor->passiveCount = 2;
	armor->passives[0] = 39;
	armor->passives[1] = 38;
	armor->ranged = true;
	
	
	
	armor = &armorData[61];
	SetString(armor->name, "Bulldog");
	armor->cost = 10;
	
	armor->headId = 62;
	armor->bodyId = 72;
	armor->actionAnimId = 1;
	
	armor->hp = 28;
	armor->mp = 3;
	armor->attack = 10;
	armor->defense = 4;
	armor->speed = 2;
	
	armor->passiveCount = 2;
	armor->passives[0] = 40;
	armor->passives[1] = 33;
}
