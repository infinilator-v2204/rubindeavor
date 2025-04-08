#include "generic.h"
#include "passives.h"
#include "battlesystem.h"
#include "fighters.h"
#include "action.h"
#include "audio.h"

Passive passiveData[OBJECT_COUNT_MAX];

void LoadPassiveData() {
	Passive* passive;
	
	
	
	passive = &passiveData[0];
	SetString(passive->name, "");
	SetString(passive->desc, "");
	passive->cost = 0;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[1];
	SetString(passive->name, "Test");
	SetString(passive->desc, "On turn start, gain 7 Strength.");
	passive->cost = 10;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[2];
	SetString(passive->name, "Vengeance");
	SetString(passive->desc, "On ally defeat, gain 15 Strength next\nturn.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[3];
	SetString(passive->name, "Cool Head");
	SetString(passive->desc, "Restore +1 MP every turn.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[4];
	SetString(passive->name, "Vine Amateur");
	SetString(passive->desc, "On turn start, inflict 3 Bind to random\nenemy.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[5];
	SetString(passive->name, "Fury");
	SetString(passive->desc, "Every time this character's attack is\nblocked, gain 3 Strength next turn.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[6];
	SetString(passive->name, "First Strike");
	SetString(passive->desc, "Deal +3 damage in first turn.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[7];
	SetString(passive->name, "Fire Sword");
	SetString(passive->desc, "Inflict 1 Burn on hit.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[8];
	SetString(passive->name, "Injury Treat");
	SetString(passive->desc, "On turn start, heal 2 HP to ally with\nleast HP.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[9];
	SetString(passive->name, "Club Master");
	SetString(passive->desc, "On turn start, random ally gains 6\nStrength.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[10];
	SetString(passive->name, "Stagger Resist");
	SetString(passive->desc, "Take 2 less damage for all attacks\nexcept first in a turn.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[11];
	SetString(passive->name, "Ninja Dodge");
	SetString(passive->desc, "Dodge the first dodgable attack.");
	passive->cost = 2;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[12];
	SetString(passive->name, "Lots Of Slime");
	SetString(passive->desc, "Inflict 1 Bind on hit.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[13];
	SetString(passive->name, "Witch");
	SetString(passive->desc, "Skills cost 10 less MP in first 2\nturns.");
	passive->cost = 3;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[14];
	SetString(passive->name, "Wound of Magic");
	SetString(passive->desc, "Deal +2 damage to enemies with a status\nailment.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[15];
	SetString(passive->name, "Spider Titan");
	SetString(passive->desc, "On turn start, summon a Spider if there\nis a defeated Spider.");
	passive->cost = 0;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[16];
	SetString(passive->name, "Pirate Leader");
	SetString(passive->desc, "Give back 75% of used MP by converting\nHP to MP.");
	passive->cost = 2;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[17];
	SetString(passive->name, "SYNC Beat");
	SetString(passive->desc, "On enemy defeat, gain 25 Strength next\nturn.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[18];
	SetString(passive->name, "Wack Wax");
	SetString(passive->desc, "Deal +8 damage in first turn.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[19];
	SetString(passive->name, "Sharp Cutter");
	SetString(passive->desc, "Inflict 1 Bleed on hit.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[20];
	SetString(passive->name, "Pirate Bounty");
	SetString(passive->desc, "On unblocked hit, restore 1 MP.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[21];
	SetString(passive->name, "Electro Weapon");
	SetString(passive->desc, "Inflict 1 Paralysis on hit.");
	passive->cost = 3;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[22];
	SetString(passive->name, "Cheap Shot");
	SetString(passive->desc, "Deal +5 damage with the skill that\nis used 2 or more times in a row.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[23];
	SetString(passive->name, "Upper Hand");
	SetString(passive->desc, "On turn start, roll the maximum speed\npossible.");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[24];
	SetString(passive->name, "Swift Strike");
	SetString(passive->desc, "Deal +3 damage to slower enemies.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[25];
	SetString(passive->name, "Flexible Flex");
	SetString(passive->desc, "On skill use, gain Strength equal to\n50% of original MP cost next turn.");
	passive->cost = 3;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[26];
	SetString(passive->name, "Psychic");
	SetString(passive->desc, "On turn start, gain 5 Strength and\nEndurance if MP is at 50% or higher.");
	passive->cost = 3;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[27];
	SetString(passive->name, "Undead");
	SetString(passive->desc, "Recover back to 10% of max HP 4 turns\nafter defeat. Immune to Lethal\ndamage effect.");
	passive->cost = 5;
	passive->stackable = false;
	passive->immortal = true;
	
	passive = &passiveData[28];
	SetString(passive->name, "Detonato-blade");
	SetString(passive->desc, "Inflict 2 Timed Bomb on hit.");
	passive->cost = 4;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[29];
	SetString(passive->name, "Adrenaline");
	SetString(passive->desc, "Restore +4 MP every turn if HP is\nat 50% or less.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[30];
	SetString(passive->name, "Last Chance");
	SetString(passive->desc, "When HP reaches 1, recover to 1 HP,\nrestore 20 MP and gain 50 Endurance\nthe same turn. Activates once.");
	passive->cost = 5;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[31];
	SetString(passive->name, "Ozone Danger");
	SetString(passive->desc, "Deal +4 damage if HP is at 25% or\nless.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[32];
	SetString(passive->name, "Close Call");
	SetString(passive->desc, "Gain 25 Haste every turn if HP\nis at 25% or less.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[33];
	SetString(passive->name, "Bodyguard");
	SetString(passive->desc, "Recover 6 MP when using a defensive\nskill (Guard, Protect etc.).");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[34];
	SetString(passive->name, "Pre-charged Up");
	SetString(passive->desc, "Start with 1 Charge.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[35];
	SetString(passive->name, "Wound of Blade");
	SetString(passive->desc, "Deal +3 damage to enemies with Bleed.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[36];
	SetString(passive->name, "Unstoppable");
	SetString(passive->desc, "On turn start, if there is a defeated\nenemy, gain 20 Strength and 4 Disarm.\nRestore +2 MP otherwise.");
	passive->cost = 4;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[37];
	SetString(passive->name, "Royal Reject");
	SetString(passive->desc, "Attacks against enemies with 5+ Bleed\nbecome unblockable and always land\ncritical hits.");
	passive->cost = 10;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[38];
	SetString(passive->name, "Chargeload");
	SetString(passive->desc, "Recover 4 MP when gaining Charge via\na skill.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[39];
	SetString(passive->name, "Detective");
	SetString(passive->desc, "Gain Haste equal to half of taken\ndamage negated by defense, blocking\nand dodging next turn.");
	passive->cost = 3;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[40];
	SetString(passive->name, "Mixed Offense");
	SetString(passive->desc, "Gain 1 Endurance on hit.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[41];
	SetString(passive->name, "Unnamed Badge");
	SetString(passive->desc, "On turn start, gain 1 random status\nout of: Strength, Endurance, Paralysis,\nCharge or Counter.");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[42];
	SetString(passive->name, "Mercury Dryer");
	SetString(passive->desc, "Deal +36 damage every 3rd turn starting\nfrom 2nd if MP is greater than total\nsum of everyone's HP divided by 2.");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[43];
	SetString(passive->name, "Img.No Bison");
	SetString(passive->desc, "On skill use, at 90% chance, spend all\nBurn to deal +2*Paralysis damage to\na female or enraged Nathan.");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[44];
	SetString(passive->name, "Ib Xiu");
	SetString(passive->desc, "Upon taking damage equal to your MP,\ngain 5*Roll Strength & 8*MP Haste next\nturn. Ineffective against meditators.");
	//SetString(passive->desc, "I don't even know what this badge does.");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[45];
	SetString(passive->name, "Peanut Butter Jelly Time: Deltapsymechoffruinikkiamadoribeshotgekher Edition");
	SetString(passive->desc, "");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[46];
	SetString(passive->name, "Bandwagon");
	SetString(passive->desc, "Deal extra damage equal to number of\nalive allies excluding self.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[47];
	SetString(passive->name, "Frostbite");
	SetString(passive->desc, "Inflict 1 Chill on hit.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[48];
	SetString(passive->name, "Burn Resist");
	SetString(passive->desc, "Immune to Burn.");
	passive->cost = 3;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[49];
	SetString(passive->name, "Bleed Resist");
	SetString(passive->desc, "Immune to Bleed.");
	passive->cost = 3;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[50];
	SetString(passive->name, "Electro Resist");
	SetString(passive->desc, "Immune to Paralysis.");
	passive->cost = 3;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[51];
	SetString(passive->name, "Venom Resist");
	SetString(passive->desc, "Immune to Poison.");
	passive->cost = 3;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[52];
	SetString(passive->name, "Chill Resist");
	SetString(passive->desc, "Immune to Chill.");
	passive->cost = 3;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[53];
	SetString(passive->name, "Minesweeper");
	SetString(passive->desc, "Immune to Timed Bomb.");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[54];
	SetString(passive->name, "Defender");
	SetString(passive->desc, "Restore 1 MP on block or dodge.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[55];
	SetString(passive->name, "Economist");
	SetString(passive->desc, "Skills cost 2 less MP.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[56];
	SetString(passive->name, "No To War");
	SetString(passive->desc, "When attacked while doing nothing,\nboost ATK +20 and SPD +15 once\nper battle.");
	passive->cost = 1;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[57];
	SetString(passive->name, "Gate Keeper");
	SetString(passive->desc, "Protects an ally (except self) with\nthe lowest HP after using a skill.");
	passive->cost = 5;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[58];
	SetString(passive->name, "Double Wreck");
	SetString(passive->desc, "Right after using an attack skill,\nuse it again on the same enemy\nwith +4 MP cost if possible.");
	passive->cost = 10;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[59];
	SetString(passive->name, "Snake");
	SetString(passive->desc, "Poison heals and restores HP and MP\ninstead of dealing damage.");
	passive->cost = 5;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[60];
	SetString(passive->name, "Emotional");
	SetString(passive->desc, "On ally or enemy defeat, gain 20\nStrength next turn.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[61];
	SetString(passive->name, "Cunning");
	SetString(passive->desc, "Restore 3 MP when using a free skill.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[62];
	SetString(passive->name, "True Color");
	SetString(passive->desc, "Reduce each incoming negative status\neffect by 3.");
	passive->cost = 4;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[63];
	SetString(passive->name, "Biased Treat");
	SetString(passive->desc, "On turn start, heal 6 HP to ally with\nhighest max HP.");
	passive->cost = 4;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[64];
	SetString(passive->name, "Hot Head");
	SetString(passive->desc, "Lose 1 MP every turn, but deal +4\ndamage.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[65];
	SetString(passive->name, "Justice At Home");
	SetString(passive->desc, "On ally defeat, boost ATK +10, DEF +1\nand SPD +5 (up to 3 times).");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[66];
	SetString(passive->name, "Unbroken Bond");
	SetString(passive->desc, "On ally defeat, gain 20 Strength and\n6 Endurance next 2 turns.");
	passive->cost = 2;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[67];
	SetString(passive->name, "Bad Morals");
	SetString(passive->desc, "Deal +9 damage to enemies with 9 or\nless MP, or +4 damage to enemies with\n49 or less MP.");
	passive->cost = 3;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[68];
	SetString(passive->name, "Laser Weapon");
	SetString(passive->desc, "Attacks become unblockable. Inflict 2\nParalysis on hit.");
	passive->cost = 10;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[69];
	SetString(passive->name, "Recycled Energy");
	SetString(passive->desc, "Immune to Paralysis' effect. On turn\nstart, convert each point of\nParalysis into 2 MP.");
	passive->cost = 4;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[70];
	SetString(passive->name, "Gardener");
	SetString(passive->desc, "Inflict 1 Flower next turn on hit,\nexcept if the damage is boosted due to\ntarget's Flower.");
	passive->cost = 6;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[71];
	SetString(passive->name, "Dystal Forms");
	SetString(passive->desc, "");
	passive->cost = 0;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[72];
	SetString(passive->name, "Naive Persist X");
	SetString(passive->desc, "When HP reaches 1, recover to half of\nmax HP. Activates once.");
	passive->cost = 43;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[73];
	SetString(passive->name, "Last Stand");
	SetString(passive->desc, "Take 50% of damage if HP is at 25% or\nless.");
	passive->cost = 2;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[74];
	SetString(passive->name, "Riggedcoaster");
	SetString(passive->desc, "On turn start, roll the maximum speed\npossible. Enemies roll the minimum\nspeed possible.");
	passive->cost = 2;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[75];
	SetString(passive->name, "Lightspeed");
	SetString(passive->desc, "When using an offensive skill against\na slower enemy, restore MP equal to 50%\nof roll difference (rounded down).");
	passive->cost = 5;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[76];
	SetString(passive->name, "Headcut");
	SetString(passive->desc, "Inflict 2 Bleed and 1 Paralysis on hit.");
	passive->cost = 5;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[77];
	SetString(passive->name, "Massive Damage");
	SetString(passive->desc, "Deal +12 damage.");
	passive->cost = 9;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[78];
	SetString(passive->name, "Extreme Fury");
	SetString(passive->desc, "Every time this character's attack is\nblocked, gain 25 Strength next turn.");
	passive->cost = 5;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[79];
	SetString(passive->name, "Thought Waves");
	SetString(passive->desc, "Restore +7 MP every turn.");
	passive->cost = 14;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[80];
	SetString(passive->name, "Onyx Immortal");
	SetString(passive->desc, "Recover back to 25% of max HP 2 turns\nafter defeat. Immune to Lethal\ndamage effect.");
	passive->cost = 15;
	passive->stackable = false;
	passive->immortal = true;
	
	passive = &passiveData[81];
	SetString(passive->name, "Heavy Armor");
	SetString(passive->desc, "Every turn, nullify first 3 points of\ndamage and 1 of status ailments.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[82];
	SetString(passive->name, "Super Armor");
	SetString(passive->desc, "Every turn, nullify first 9 points of\ndamage and 3 of status ailments.");
	passive->cost = 3;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[83];
	SetString(passive->name, "Hyper Armor");
	SetString(passive->desc, "Every turn, nullify first 30 points of\ndamage and 15 of status ailments.");
	passive->cost = 10;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[84];
	SetString(passive->name, "Superflow State");
	SetString(passive->desc, "Restore +25 MP every turn.");
	passive->cost = 36;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[85];
	SetString(passive->name, "Godly Powers");
	SetString(passive->desc, "Immune to Lethal damage effect. Deal\nextra damage and take reduced damage\nequal to 1% of remaining MP.");
	passive->cost = 10;
	passive->stackable = false;
	passive->immortal = true;
	
	passive = &passiveData[86];
	SetString(passive->name, "Ministry Power");
	SetString(passive->desc, "Restore +5% MP every turn. Deal +20\ndamage. Take 25% less damage. Immune to\nBurn, Bleed, Paralysis, Poison, Chill.");
	passive->cost = 25;
	passive->stackable = false;
	passive->immortal = false;
	
	passive = &passiveData[87];
	SetString(passive->name, "Emerald-gency");
	SetString(passive->desc, "Gain 30 Endurance every turn if HP is\nat 25% or less. On turn start, heal 20\nHP to ally with least HP.");
	passive->cost = 18;
	passive->stackable = true;
	passive->immortal = false;
}

void Passive_OnTurnStart(int passiveId, Fighter* fighter) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	switch (passiveId) {
		case 1: {
			fighter->status[FIGHTER_STATUS_STRENGTH] += 7;
		} break;
		
		case 3: {
			fighter->mp += 1;
			if (fighter->mp > fighter->mpMax) fighter->mp = fighter->mpMax;
		} break;
		
		case 4: {
			Fighter* target = NULL;
			Fighter* pool[8];
			int poolSize = 0;
			
			for (int i = 8 - fighter->side * 8; i < 8 - fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				pool[poolSize++] = fighter2;
			}
			
			if (poolSize > 0) {
				int r = Random_IRange(0, poolSize - 1);
				target = pool[r];
				
				if (target != NULL) target->status[FIGHTER_STATUS_BIND] += 3;
			}
		} break;
		
		case 8: {
			Fighter* target = NULL;
			int leastHP = 0x7fffffff;
			
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->hp < leastHP && fighter2->hp < fighter2->hpMax) {
					target = fighter2;
					leastHP = fighter2->hp;
				}
			}
			
			if (target != NULL) Fighter_HealHP(target, 2);
		} break;
		
		case 9: {
			Fighter* target = NULL;
			Fighter* pool[8];
			int poolSize = 0;
			
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				pool[poolSize++] = fighter2;
			}
			
			if (poolSize > 0) {
				int r = Random_IRange(0, poolSize - 1);
				target = pool[r];
				
				if (target != NULL) target->status[FIGHTER_STATUS_STRENGTH] += 6;
			}
		} break;
		
		case 10: {
			fighter->passiveVars[10].i = 0;
		} break;
		
		case 13: {
			if (battle.turnCount <= 2) {
				fighter->manaCostReduction += 10;
			}
		} break;
		
		case 15: {
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled) continue;
				
				if (!fighter2->alive) {
					fighter2->alive = true;
					fighter2->state = FIGHTER_STATE_IDLE;
					fighter2->hp = fighter2->hpMax;
					fighter2->mp = fighter2->mpMax;
					break;
				}
			}
		} break;
		
		case 16: {
			int amount = (fighter->mpMax - fighter->mp) * 3 / 4;
			if (amount < fighter->hp) {
				fighter->hp -= amount;
				Fighter_HealMP(fighter, amount);
			}
		} break;
		
		case 23: {
			fighter->speedRoll = fighter->speedRollMax;
			fighter->speedRollMin = fighter->speedRollMax;
		} break;
		
		case 26: {
			if (fighter->mp >= fighter->mpMax / 2) {
				fighter->status[FIGHTER_STATUS_STRENGTH] += 5;
				fighter->status[FIGHTER_STATUS_ENDURANCE] += 5;
			}
		} break;
		
		case 27: {
			if (!fighter->alive) {
				fighter->passiveVars[27].i++;
				if (fighter->passiveVars[27].i >= 4) {
					fighter->passiveVars[27].i = 0;
					
					Audio_PlaySound(SND_reset);
					fighter->alive = true;
					fighter->state = FIGHTER_STATE_IDLE;
					Fighter_HealHP(fighter, 1 + fighter->hpMax / 10);
				}
			}
		} break;
		
		case 29: {
			if (fighter->hp <= fighter->hpMax / 2) {
				fighter->mp += 4;
				if (fighter->mp > fighter->mpMax) fighter->mp = fighter->mpMax;
			}
		} break;
		
		case 30: {
			if (fighter->passiveVars[30].i == 1) {
				fighter->passiveVars[30].i = 2;
			}
		} break;
		
		case 32: {
			if (fighter->hp <= fighter->hpMax / 4) {
				Fighter_GainStatus(fighter, FIGHTER_STATUS_HASTE, 25, true);
			}
		} break;
		
		case 34: {
			if (fighter->passiveVars[34].i == 0) {
				fighter->passiveVars[34].i = 1;
				fighter->status[FIGHTER_STATUS_CHARGE] += 1;
			}
		} break;
		
		case 36: {
			bool condition = false;
			for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled) continue;
				if (!fighter2->alive) {
					condition = true;
					break;
				}
			}
			if (condition) {
				Fighter_GainStatus(fighter, FIGHTER_STATUS_STRENGTH, 20, true);
				Fighter_GainStatus(fighter, FIGHTER_STATUS_DISARM, 4, true);
			}
			else {
				fighter->mp += 2;
				if (fighter->mp > fighter->mpMax) fighter->mp = fighter->mpMax;
			}
		} break;
		
		case 41: {
			fighter->status[(int[]){ FIGHTER_STATUS_STRENGTH, FIGHTER_STATUS_ENDURANCE, FIGHTER_STATUS_PARALYSIS, FIGHTER_STATUS_CHARGE, FIGHTER_STATUS_COUNTER }[Random_IRange(0, 4)]] += 1;
		} break;
		
		case 42: {
			fighter->passiveVars[42].i = 0;
			int sum = 0;
			for (int i = 0; i < 16; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				sum += fighter2->hp;
			}
			if (battle.turnCount % 3 == 2 && fighter->mp * 2 > sum) {
				fighter->passiveVars[42].i = 1;
			}
		} break;
		
		case 55: {
			fighter->manaCostReduction += 2;
		} break;
		
		case 57: {
			fighter->passiveVars[57].i = 0;
		} break;
		
		case 58: {
			fighter->passiveVars[58].i = 0;
		} break;
		
		case 59: {
			fighter->statusOverride[FIGHTER_STATUS_POISON] = true;
			if (fighter->status[FIGHTER_STATUS_POISON] > 0) {
				Fighter_HealHP(fighter, fighter->status[FIGHTER_STATUS_POISON]);
				Fighter_HealMP(fighter, fighter->status[FIGHTER_STATUS_POISON]);
				fighter->status[FIGHTER_STATUS_POISON] = fighter->status[FIGHTER_STATUS_POISON] * 2 / 3;
			}
		} break;
		
		case 63: {
			Fighter* target = NULL;
			int mostHP = -1;
			
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->hpMax > mostHP) {
					target = fighter2;
					mostHP = fighter2->hpMax;
				}
			}
			
			if (target != NULL) Fighter_HealHP(target, 6);
		} break;
		
		case 64: {
			fighter->mp -= 1;
			if (fighter->mp < 0) fighter->mp = 0;
		} break;
		
		case 66: {
			if (fighter->passiveVars[66].i >= 1) {
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 20 * fighter->passiveVars[66].i;
				fighter->statusNext[FIGHTER_STATUS_ENDURANCE] += 6 * fighter->passiveVars[66].i;
				fighter->passiveVars[66].i = 0;
			}
		} break;
		
		case 69: {
			fighter->statusOverride[FIGHTER_STATUS_PARALYSIS] = true;
			if (fighter->status[FIGHTER_STATUS_PARALYSIS] > 0) {
				Fighter_HealMP(fighter, fighter->status[FIGHTER_STATUS_PARALYSIS] * 2);
				fighter->status[FIGHTER_STATUS_PARALYSIS] = 0;
			}
		} break;
		
		case 71: {
			int hpStage = 8 - (fighter->hp - 1) / 200;
			if (fighter->passiveVars[71].i < hpStage) {
				Audio_PlaySoundInterrupt(SND_shards);
				Battle_CreateSpark(10, fighter->x, fighter->y, 0);
				Battle_ShakeScreen(8);
				
				fighter->passiveVars[71].i++;
				fighter->hp = (9 - fighter->passiveVars[71].i) * 200;
				Fighter_ClearAllStatus(fighter);
				Fighter_HealMP(fighter, 84);
				fighter->aiVars[0].i = 0;
				
				switch (fighter->passiveVars[71].i) {
					case 1:
						fighter->headId = 1;
						battle.backgroundId = 12;
						
						fighter->movesetCount = 3;
						fighter->moveset[0] = 93;
						fighter->moveset[1] = 98;
						fighter->moveset[2] = 99;
						break;
					case 2:
						fighter->headId = 2;
						battle.backgroundId = 7;
						
						fighter->movesetCount = 4;
						fighter->moveset[0] = 93;
						fighter->moveset[1] = 116;
						fighter->moveset[2] = 134;
						fighter->moveset[3] = 148;
						break;
					case 3:
						fighter->headId = 4;
						battle.backgroundId = 18;
						
						fighter->movesetCount = 5;
						fighter->moveset[0] = 93;
						fighter->moveset[1] = 114;
						fighter->moveset[2] = 134;
						fighter->moveset[3] = 158;
						fighter->moveset[4] = 61;
						break;
					case 4:
						fighter->headId = 7;
						battle.backgroundId = 2;
						
						fighter->movesetCount = 4;
						fighter->moveset[0] = 93;
						fighter->moveset[1] = 157;
						fighter->moveset[2] = 71;
						fighter->moveset[3] = 149;
						break;
					case 5:
						fighter->headId = 6;
						battle.backgroundId = 8;
						
						fighter->movesetCount = 2;
						fighter->moveset[0] = 159;
						fighter->moveset[1] = 72;
						break;
					case 6:
						fighter->headId = 3;
						battle.backgroundId = 1;
						
						fighter->movesetCount = 4;
						fighter->moveset[0] = 93;
						fighter->moveset[1] = 152;
						fighter->moveset[2] = 150;
						fighter->moveset[3] = 151;
						break;
					case 7:
						fighter->headId = 5;
						battle.backgroundId = 18;
						
						fighter->movesetCount = 3;
						fighter->moveset[0] = 45;
						fighter->moveset[1] = 145;
						fighter->moveset[2] = 153;
						break;
					case 8:
						fighter->headId = 0;
						fighter->bodyId = 93;
						battle.backgroundId = 7;
						
						fighter->attack += 85;
						fighter->defense -= 8;
						Fighter_HealMP(fighter, fighter->mpMax - 84);
						Fighter_GainStatus(fighter, FIGHTER_STATUS_ENDURANCE, 60, true);
						
						fighter->movesetCount = 3;
						fighter->moveset[0] = 162;
						fighter->moveset[1] = 161;
						fighter->moveset[2] = 163;
						
						Audio_PlayMusic(MUS_superboss); // placeholder music, could use a new one
						break;
				}
				break;
			}
		} break;
		
		case 74: {
			fighter->speedRoll = fighter->speedRollMax;
			fighter->speedRollMin = fighter->speedRollMax;
			for (int i = 8 - fighter->side * 8; i < 8 - fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				fighter2->speedRoll = fighter2->speedRollMin;
			}
		} break;
		
		case 79: {
			fighter->mp += 7;
			if (fighter->mp > fighter->mpMax) fighter->mp = fighter->mpMax;
		} break;
		
		case 80: {
			if (!fighter->alive) {
				fighter->passiveVars[80].i++;
				if (fighter->passiveVars[80].i >= 2) {
					fighter->passiveVars[80].i = 0;
					
					Audio_PlaySound(SND_reset);
					fighter->alive = true;
					fighter->state = FIGHTER_STATE_IDLE;
					Fighter_HealHP(fighter, 1 + fighter->hpMax / 4);
				}
			}
		} break;
		
		case 81: {
			fighter->passiveVars[81].i = 0;
		} break;
		
		case 82: {
			fighter->passiveVars[82].i = 0;
		} break;
		
		case 83: {
			fighter->passiveVars[83].i = 0;
		} break;
		
		case 84: {
			fighter->mp += 25;
			if (fighter->mp > fighter->mpMax) fighter->mp = fighter->mpMax;
		} break;
		
		case 86: {
			fighter->mp += fighter->mpMax / 20;
			if (fighter->mp > fighter->mpMax) fighter->mp = fighter->mpMax;
		} break;
		
		case 87: {
			if (fighter->hp <= fighter->hpMax / 4) {
				Fighter_GainStatus(fighter, FIGHTER_STATUS_ENDURANCE, 30, true);
			}
			
			Fighter* target = NULL;
			int leastHP = 0x7fffffff;
			
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->hp < leastHP && fighter2->hp < fighter2->hpMax) {
					target = fighter2;
					leastHP = fighter2->hp;
				}
			}
			
			if (target != NULL) Fighter_HealHP(target, 20);
		} break;
	}
}

void Passive_OnSkillUse(int passiveId, Fighter* fighter) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	switch (passiveId) {
		case 25: {
			fighter->statusNext[FIGHTER_STATUS_STRENGTH] += actionData[fighter->actionId].cost / 2;
		} break;
		
		case 33: {
			if (actionData[fighter->actionId].category == ACTIONCATEGORY_DEFENSIVE) {
				Fighter_HealMP(fighter, 6);
			}
		} break;
		
		case 38: {
			if (fighter->actionId == 76) {
				Fighter_HealMP(fighter, 4);
			}
		} break;
		
		case 43: {
			fighter->passiveVars[43].i = 0;
			if (fighter->status[FIGHTER_STATUS_BURN] && Random(1) < 0.9) {
				fighter->passiveVars[43].i = 1;
				fighter->status[FIGHTER_STATUS_BURN] = 0;
			}
		} break;
		
		case 61: {
			if (actionData[fighter->actionId].cost - fighter->manaCostReduction <= 0) {
				Fighter_HealMP(fighter, 3);
			}
		} break;
		
		case 75: {
			if (actionData[fighter->actionId].category == ACTIONCATEGORY_ATTACK && actionData[fighter->actionId].targetType == TARGETTYPE_ENEMY) {
				if (fighter->speedRoll >= battle.target->speedRoll + 2) {
					Fighter_HealMP(fighter, (fighter->speedRoll - battle.target->speedRoll) / 2);
				}
			}
		} break;
	}
}

void Passive_OnSkillEnd(int passiveId, Fighter* fighter) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	switch (passiveId) {
		case 22: {
			fighter->passiveVars[22].i = fighter->actionId;
		} break;
		
		case 43: {
			fighter->passiveVars[43].i = 0;
		} break;
		
		case 57: {
			if (fighter->passiveVars[57].i == 0) {
				fighter->passiveVars[57].i = 1;
				
				int targetId = -1;
				int leastHP = 0x7fffffff;
				
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					if (fighter2->hp < leastHP) {
						targetId = i;
						leastHP = fighter2->hp;
					}
				}
				
				if (targetId >= 0) {
					fighter->actionId = 26;
					fighter->targetId = targetId;
					battle.turn--;
				}
			}
		} break;
		
		case 58: {
			if (battle.target == NULL) break;
			if (fighter->passiveVars[58].i == 0) {
				fighter->passiveVars[58].i = 1;
				
				if (actionData[fighter->actionId].category == ACTIONCATEGORY_ATTACK && actionData[fighter->actionId].targetType == TARGETTYPE_ENEMY && battle.target->hp > 0) {
					fighter->manaCostReduction -= 4;
					battle.turn--;
				}
			}
		} break;
	}
}

void Passive_OnDealDamage(int passiveId, Fighter* fighter, Fighter* target, int* damagePointer, unsigned int* flagsPointer) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	int blocked = 0;
	if (target->blockTimer >= 0 && target->blockTimer < target->dodgeTime && (*flagsPointer & DAMAGE_FLAG_DODGABLE)) {
		blocked = 2;
	}
	else if (*damagePointer >= 0 && ((target->blockTimer >= 0 && target->blockTimer < target->blockTime) || target->status[FIGHTER_STATUS_GUARD]) && (*flagsPointer & DAMAGE_FLAG_BLOCKABLE)) {
		blocked = 1;
	}
	
	switch (passiveId) {
		case 5: {
			if (blocked == 1 || blocked == 2) {
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 3;
			}
		} break;
		
		case 6: {
			/*if (fighter->passiveVars[6].i == 0 && blocked != 2) {
				fighter->passiveVars[6].i = 1;
				*damagePointer += 2;
			}*/
			if (battle.turnCount <= 1 && blocked != 2) {
				*damagePointer += 3;
			}
		} break;
		
		case 7: {
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_BURN, 1, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_BURN, 1, false);
			}
		} break;
		
		case 12: {
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_BIND, 1, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_BIND, 1, false);
			}
		} break;
		
		case 14: {
			if (blocked != 2) {
				for (int i = 0; i < 32; i++) {
					if (!target->status[i]) continue;
					if (statusEffectData[i].type == STATUS_TYPE_NEGATIVE) {
						*damagePointer += 2;
						break;
					}
				}
			}
		} break;
		
		case 18: {
			if (battle.turnCount <= 1 && blocked != 2) {
				*damagePointer += 8;
			}
		} break;
		
		case 19: {
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_BLEED, 1, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_BLEED, 1, false);
			}
		} break;
		
		case 20: {
			if (blocked == 0) {
				Fighter_HealMP(fighter, 1);
			}
		} break;
		
		case 21: {
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_PARALYSIS, 1, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_PARALYSIS, 1, false);
			}
		} break;
		
		case 22: {
			if (fighter->passiveVars[22].i == fighter->actionId) {
				*damagePointer += 5;
			}
		} break;
		
		case 24: {
			if (fighter->speedRoll > target->speedRoll) {
				*damagePointer += 3;
			}
		} break;
		
		case 28: {
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_TIMEDBOMB, 2, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_TIMEDBOMB, 2, false);
			}
		} break;
		
		case 31: {
			if (fighter->hp <= fighter->hpMax / 4 && blocked != 2) {
				*damagePointer += 4;
			}
		} break;
		
		case 35: {
			if (blocked != 2) {
				if (target->status[FIGHTER_STATUS_BLEED]) {
					*damagePointer += 3;
				}
			}
		} break;
		
		case 37: {
			if (blocked != 2) {
				if (target->status[FIGHTER_STATUS_BLEED] >= 5) {
					*flagsPointer |= DAMAGE_FLAG_CRITICAL;
					*flagsPointer &= ~DAMAGE_FLAG_BLOCKABLE;
				}
			}
		} break;
		
		case 40: {
			if (blocked != 2) {
				Fighter_GainStatus(fighter, FIGHTER_STATUS_ENDURANCE, 1, false);
			}
		} break;
		
		case 42: {
			if (fighter->passiveVars[42].i) {
				*damagePointer += 36;
			}
		} break;
		
		case 43: {
			if (fighter->passiveVars[43].i && target->gender == FIGHTER_GENDER_FEMALE) {
				*damagePointer += 2 * fighter->status[FIGHTER_STATUS_PARALYSIS];
			}
		} break;
		
		case 46: {
			int count = 0;
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				*damagePointer += 1;
			}
		} break;
		
		case 47: {
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_CHILL, 1, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_CHILL, 1, false);
			}
		} break;
		
		case 64: {
			if (blocked != 2) {
				*damagePointer += 4;
			}
		} break;
		
		case 67: {
			if (blocked != 2) {
				if (target->mp <= 9)
					*damagePointer += 9;
				else if (target->mp <= 49)
					*damagePointer += 4;
			}
		} break;
		
		case 68: {
			if (blocked != 2) {
				*flagsPointer &= ~DAMAGE_FLAG_BLOCKABLE;
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_PARALYSIS, 2, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_PARALYSIS, 2, false);
			}
		} break;
		
		case 70: {
			if ((fighter->actionId == 59 || fighter->actionId == 60) && target->status[FIGHTER_STATUS_FLOWER]) {
				break;
			}
			
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE)
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_FLOWER, 1, false);
				else
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_FLOWER, 1, false);
			}
		} break;
		
		case 76: {
			if (blocked != 2) {
				if (*flagsPointer & DAMAGE_FLAG_DODGABLE) {
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_BLEED, 2, false);
					Fighter_InflictStatusDodgable(fighter, target, FIGHTER_STATUS_PARALYSIS, 1, false);
				}
				else {
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_BLEED, 2, false);
					Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_PARALYSIS, 1, false);
				}
			}
		} break;
		
		case 77: {
			if (blocked != 2) {
				*damagePointer += 12;
			}
		} break;
		
		case 78: {
			if (blocked == 1 || blocked == 2) {
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 25;
			}
		} break;
		
		case 85: {
			if (blocked != 2) {
				*damagePointer += fighter->mp / 100;
			}
		} break;
		
		case 86: {
			if (blocked != 2) {
				*damagePointer += 20;
			}
		} break;
	}
}

void Passive_OnTakeDamage(int passiveId, Fighter* fighter, Fighter* attacker, int* damagePointer, unsigned int* flagsPointer) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	int blocked = 0;
	if (fighter->blockTimer >= 0 && fighter->blockTimer < fighter->dodgeTime && (*flagsPointer & DAMAGE_FLAG_DODGABLE)) {
		blocked = 2;
	}
	else if (*damagePointer >= 0 && ((fighter->blockTimer >= 0 && fighter->blockTimer < fighter->blockTime) || fighter->status[FIGHTER_STATUS_GUARD]) && (*flagsPointer & DAMAGE_FLAG_BLOCKABLE)) {
		blocked = 1;
	}
	
	switch (passiveId) {
		case 10: {
			if (attacker == NULL) break;
			if (blocked != 2) {
				if (fighter->passiveVars[10].i == 0) {
					fighter->passiveVars[10].i = 1;
				}
				else {
					*damagePointer -= 2;
					if (*damagePointer < 0) *damagePointer = 0;
				}
			}
		} break;
		
		case 11: {
			if (*damagePointer >= 1000) break;
			if (attacker == NULL) break;
			if (blocked != 2 && (*flagsPointer & DAMAGE_FLAG_DODGABLE)) {
				if (fighter->passiveVars[11].i == 0) {
					fighter->passiveVars[11].i = 1;
					
					*damagePointer = -999999;
					fighter->state = FIGHTER_STATE_ATTACK1;
					Audio_PlaySound(SND_dodge);
				}
			}
		} break;
		
		case 27: case 80: {
			*flagsPointer &= ~DAMAGE_FLAG_LETHAL;
		} break;
		
		case 30: {
			if (*damagePointer >= 1000) break;
			if (attacker == NULL && fighter->passiveVars[30].i == 1) {
				*damagePointer = -999999;
				break;
			}
			if (fighter->hp - *damagePointer <= 1 && fighter->passiveVars[30].i == 0) {
				fighter->passiveVars[30].i = 1;
				
				if (*damagePointer >= fighter->hp) *damagePointer = fighter->hp - 1;
				Fighter_HealMP(fighter, 20);
				Fighter_GainStatus(fighter, FIGHTER_STATUS_ENDURANCE, 50, true);
				Fighter_GainStatus(fighter, FIGHTER_STATUS_STRENGTH, 20, false);
			}
		} break;
		
		case 39: {
			if (attacker == NULL) break;
			int damageNegated = Max(0, fighter->defense + fighter->status[FIGHTER_STATUS_ENDURANCE] - fighter->status[FIGHTER_STATUS_DISARM]);
			if (blocked == 2)
				damageNegated += *damagePointer;
			else if (blocked == 1)
				damageNegated += (*damagePointer + 1) / 2;
			
			fighter->statusNext[FIGHTER_STATUS_HASTE] += damageNegated / 2;
		} break;
		
		case 44: {
			if (attacker == NULL) break;
			if (*damagePointer == fighter->mp) {
				bool condition = true;
				for (int i = 0; i < attacker->movesetCount; i++) {
					if (attacker->moveset[i] == 44) {
						condition = false;
						break;
					}
				}
				if (condition) {
					fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 5 * fighter->speedRoll;
					fighter->statusNext[FIGHTER_STATUS_HASTE] += 8 * fighter->mp;
				}
			}
		} break;
		
		case 54: {
			if (blocked == 1 || blocked == 2) {
				Fighter_HealMP(fighter, 1);
			}
		} break;
		
		case 56: {
			if (fighter->actionId == 0 && fighter->passiveVars[56].i == 0) {
				fighter->passiveVars[56].i = 1;
				fighter->attack += 20;
				fighter->speed += 15;
			}
		} break;
		
		case 71: {
			int hpStage = 8 - fighter->passiveVars[71].i;
			if (fighter->hp - *damagePointer < hpStage * 200 && hpStage > 0) {
				*damagePointer = fighter->hp - hpStage * 200;
				break;
			}
		} break;
		
		case 72: {
			if (*damagePointer >= 1000 || blocked == 2) break;
			if (fighter->hp - *damagePointer <= 1 && fighter->passiveVars[72].i == 0) {
				fighter->passiveVars[72].i = 1;
				
				if (*damagePointer >= fighter->hp) *damagePointer = fighter->hp - 1;
				Fighter_HealHP(fighter, fighter->hpMax / 2);
			}
		} break;
		
		case 73: {
			if (fighter->hp - *damagePointer <= (fighter->hpMax + 3) / 4) {
				*damagePointer /= 2;
			}
		} break;
		
		case 81: {
			if (blocked == 2) break;
			int maxArmor = 3;
			if ((fighter->passiveVars[81].i & 0xffff) < maxArmor) {
				int armorLeft = maxArmor - (fighter->passiveVars[81].i & 0xffff);
				if (*damagePointer >= armorLeft) {
					*damagePointer -= armorLeft;
					fighter->passiveVars[81].i = (fighter->passiveVars[81].i & ~0xffff) | maxArmor;
				}
				else if (*damagePointer > 0) {
					fighter->passiveVars[81].i += *damagePointer;
					*damagePointer = 0;
				}
			}
		} break;
		
		case 82: {
			if (blocked == 2) break;
			int maxArmor = 9;
			if ((fighter->passiveVars[82].i & 0xffff) < maxArmor) {
				int armorLeft = maxArmor - (fighter->passiveVars[82].i & 0xffff);
				if (*damagePointer >= armorLeft) {
					*damagePointer -= armorLeft;
					fighter->passiveVars[82].i = (fighter->passiveVars[82].i & ~0xffff) | maxArmor;
				}
				else if (*damagePointer > 0) {
					fighter->passiveVars[82].i += *damagePointer;
					*damagePointer = 0;
				}
			}
		} break;
		
		case 83: {
			if (blocked == 2) break;
			int maxArmor = 30;
			if ((fighter->passiveVars[83].i & 0xffff) < maxArmor) {
				int armorLeft = maxArmor - (fighter->passiveVars[83].i & 0xffff);
				if (*damagePointer >= armorLeft) {
					*damagePointer -= armorLeft;
					fighter->passiveVars[83].i = (fighter->passiveVars[83].i & ~0xffff) | maxArmor;
				}
				else if (*damagePointer > 0) {
					fighter->passiveVars[83].i += *damagePointer;
					*damagePointer = 0;
				}
			}
		} break;
		
		case 85: {
			*flagsPointer &= ~DAMAGE_FLAG_LETHAL;
			
			if (blocked != 2) {
				*damagePointer -= fighter->mp / 100;
				if (*damagePointer < 0) *damagePointer = 0;
			}
		} break;
		
		case 86: {
			if (blocked != 2) {
				*damagePointer -= (*damagePointer + 3) / 4;
			}
		} break;
	}
}

void Passive_OnTakeStatus(int passiveId, Fighter* fighter, Fighter* attacker, int* statusIdPointer, int* countPointer, int damageFlags) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	int blocked = 0;
	if (fighter->blockTimer >= 0 && fighter->blockTimer < fighter->dodgeTime && (damageFlags & DAMAGE_FLAG_DODGABLE)) {
		blocked = 2;
	}
	else if (((fighter->blockTimer >= 0 && fighter->blockTimer < fighter->blockTime) || fighter->status[FIGHTER_STATUS_GUARD]) && (damageFlags & DAMAGE_FLAG_BLOCKABLE)) {
		blocked = 1;
	}
	
	switch (passiveId) {
		case 11: {
			if (attacker == NULL) break;
			if (attacker->side == fighter->side) return;
			if (blocked != 2 && (damageFlags & DAMAGE_FLAG_DODGABLE)) {
				if (fighter->passiveVars[11].i == 0) {
					*countPointer = 0;
				}
			}
		} break;
		
		case 48: {
			if (*statusIdPointer == FIGHTER_STATUS_BURN) {
				*countPointer = 0;
			}
		} break;
		
		case 49: {
			if (*statusIdPointer == FIGHTER_STATUS_BLEED) {
				*countPointer = 0;
			}
		} break;
		
		case 50: {
			if (*statusIdPointer == FIGHTER_STATUS_PARALYSIS) {
				*countPointer = 0;
			}
		} break;
		
		case 51: {
			if (*statusIdPointer == FIGHTER_STATUS_POISON) {
				*countPointer = 0;
			}
		} break;
		
		case 52: {
			if (*statusIdPointer == FIGHTER_STATUS_CHILL) {
				*countPointer = 0;
			}
		} break;
		
		case 53: {
			if (*statusIdPointer == FIGHTER_STATUS_TIMEDBOMB) {
				*countPointer = 0;
			}
		} break;
		
		case 62: {
			if (statusEffectData[*statusIdPointer].type == STATUS_TYPE_NEGATIVE) {
				*countPointer -= 3;
				if (*countPointer < 0)
					*countPointer = 0;
			}
		} break;
		
		case 81: {
			if (statusEffectData[*statusIdPointer].type == STATUS_TYPE_NEGATIVE) {
				int maxArmor = 1;
				if ((fighter->passiveVars[81].i >> 16) < maxArmor) {
					int armorLeft = maxArmor - (fighter->passiveVars[81].i >> 16);
					if (*countPointer >= armorLeft) {
						*countPointer -= armorLeft;
						fighter->passiveVars[81].i = (fighter->passiveVars[81].i & 0xffff) | (maxArmor << 16);
					}
					else if (*countPointer > 0) {
						fighter->passiveVars[81].i += *countPointer << 16;
						*countPointer = 0;
					}
				}
			}
		} break;
		
		case 82: {
			if (statusEffectData[*statusIdPointer].type == STATUS_TYPE_NEGATIVE) {
				int maxArmor = 3;
				if ((fighter->passiveVars[82].i >> 16) < maxArmor) {
					int armorLeft = maxArmor - (fighter->passiveVars[82].i >> 16);
					if (*countPointer >= armorLeft) {
						*countPointer -= armorLeft;
						fighter->passiveVars[82].i = (fighter->passiveVars[82].i & 0xffff) | (maxArmor << 16);
					}
					else if (*countPointer > 0) {
						fighter->passiveVars[82].i += *countPointer << 16;
						*countPointer = 0;
					}
				}
			}
		} break;
		
		case 83: {
			if (statusEffectData[*statusIdPointer].type == STATUS_TYPE_NEGATIVE) {
				int maxArmor = 15;
				if ((fighter->passiveVars[83].i >> 16) < maxArmor) {
					int armorLeft = maxArmor - (fighter->passiveVars[83].i >> 16);
					if (*countPointer >= armorLeft) {
						*countPointer -= armorLeft;
						fighter->passiveVars[83].i = (fighter->passiveVars[83].i & 0xffff) | (maxArmor << 16);
					}
					else if (*countPointer > 0) {
						fighter->passiveVars[83].i += *countPointer << 16;
						*countPointer = 0;
					}
				}
			}
		} break;
		
		case 86: {
			if (*statusIdPointer == FIGHTER_STATUS_BURN || *statusIdPointer == FIGHTER_STATUS_BLEED || *statusIdPointer == FIGHTER_STATUS_PARALYSIS || *statusIdPointer == FIGHTER_STATUS_POISON || *statusIdPointer == FIGHTER_STATUS_CHILL) {
				*countPointer = 0;
			}
		} break;
	}
}

void Passive_OnFighterDefeat(int passiveId, Fighter* fighter, Fighter* target) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	switch (passiveId) {
		case 2: {
			if (target->side == fighter->side) {
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 15;
			}
		} break;
		
		case 17: {
			if (target->side != fighter->side) {
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 25;
			}
		} break;
		
		case 60: {
			fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 20;
		} break;
		
		case 65: {
			if (target->side == fighter->side && fighter->passiveVars[65].i < 3) {
				fighter->passiveVars[65].i++;
				fighter->attack += 10;
				fighter->defense += 1;
				fighter->speed += 5;
			}
		} break;
		
		case 66: {
			if (target->side == fighter->side) {
				fighter->passiveVars[66].i++;
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 20;
				fighter->statusNext[FIGHTER_STATUS_ENDURANCE] += 6;
			}
		} break;
	}
}
