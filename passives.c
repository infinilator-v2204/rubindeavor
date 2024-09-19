#include "generic.h"
#include "passives.h"
#include "battlesystem.h"
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
	SetString(passive->desc, "On ally defeat, gain 10 Strength next\nturn.");
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
	SetString(passive->desc, "Deal +2 damage on first hit.");
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
	SetString(passive->desc, "On turn start, random ally gains 2\nStrength.");
	passive->cost = 1;
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
	SetString(passive->desc,  "Dodge the first dodgable attack.");
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
	SetString(passive->desc, "On enemy defeat, gain 15 Strength next\nturn.");
	passive->cost = 1;
	passive->stackable = true;
	passive->immortal = false;
	
	passive = &passiveData[18];
	SetString(passive->name, "Wack Wax");
	SetString(passive->desc, "Deal +8 damage on first hit.");
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
	SetString(passive->desc, "Deal +4 damage with the skill that\nis used 2 or more times in a row.");
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
	SetString(passive->desc, "Deal +2 damage to slower enemies.");
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
	SetString(passive->desc, "When HP reaches 1, recover to 1 HP,\nrestore 20 MP and gain 20 Endurance\nthe same turn. Activates once.");
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
				
				if (target != NULL) target->status[FIGHTER_STATUS_STRENGTH] += 2;
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
					
					PlaySound(SND_reset);
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
	}
}

void Passive_OnSkillEnd(int passiveId, Fighter* fighter) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	switch (passiveId) {
		case 22: {
			fighter->passiveVars[22].i = fighter->actionId;
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
			if (fighter->passiveVars[6].i == 0 && blocked != 2) {
				fighter->passiveVars[6].i = 1;
				*damagePointer += 2;
			}
		} break;
		
		case 7: {
			if (blocked != 2) {
				Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_BURN, 1, false);
			}
		} break;
		
		case 12: {
			if (blocked != 2) {
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
			if (fighter->passiveVars[18].i == 0 && blocked != 2) {
				fighter->passiveVars[18].i = 1;
				*damagePointer += 8;
			}
		} break;
		
		case 19: {
			if (blocked != 2) {
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
				Fighter_InflictStatus(fighter, target, FIGHTER_STATUS_PARALYSIS, 1, false);
			}
		} break;
		
		case 22: {
			if (fighter->passiveVars[22].i == fighter->actionId) {
				*damagePointer += 4;
			}
		} break;
		
		case 24: {
			if (fighter->speedRoll > target->speedRoll) {
				*damagePointer += 2;
			}
		} break;
		
		case 28: {
			if (blocked != 2) {
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
					PlaySound(SND_dodge);
				}
			}
		} break;
		
		case 27: {
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
	}
}

void Passive_OnTakeStatus(int passiveId, Fighter* fighter, Fighter* attacker, int* statusIdPointer, int* countPointer) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	int blocked = 0;
	if (fighter->blockTimer >= 0 && fighter->blockTimer < fighter->dodgeTime) {
		blocked = 2;
	}
	else if (fighter->blockTimer >= 0 && fighter->blockTimer < fighter->blockTime) {
		blocked = 1;
	}
	
	switch (passiveId) {
		case 11: {
			if (attacker == NULL) break;
			if (attacker->side == fighter->side) return;
			if (blocked != 2) {
				if (fighter->passiveVars[11].i == 0) {
					*countPointer = 0;
				}
			}
		} break;
	}
}

void Passive_OnFighterDefeat(int passiveId, Fighter* fighter, Fighter* target) {
	if (!passiveData[passiveId].immortal && !fighter->alive) return;
	
	switch (passiveId) {
		case 2: {
			if (target->side == fighter->side) {
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 10;
			}
		} break;
		
		case 17: {
			if (target->side != fighter->side) {
				fighter->statusNext[FIGHTER_STATUS_STRENGTH] += 15;
			}
		} break;
	}
}
