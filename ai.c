#include "generic.h"
#include "ai.h"
#include "action.h"
#include "profile.h"



bool Fighter_AI_TurnStart(Fighter* fighter) {
	bool interrupt = false;
	
	switch (fighter->ai) {
		case 5:
			if (battle.encounter == 70) {
				if (battle.battleEventVars[0] == 0) {
					Battle_TriggerBattleEvent(10, fighter);
					battle.battleEventVars[0] = 1;
				}
			}
			else {
				if (fighter->hp < 120 && battle.battleEventVars[2] == 0) {
					Battle_TriggerBattleEvent(192, fighter);
					battle.battleEventVars[2]++;
				}
			}
			break;
		case 8:
			if (battle.encounter == 49) {
				if (battle.turnCount == 1 && battle.battleEventVars[0] == 0) {
					Battle_TriggerBattleEvent(2, fighter);
					battle.battleEventVars[0] = 1;
				}
				else if (battle.turnCount >= 3 && battle.fighters[0].hp * 100 / battle.fighters[0].hpMax > fighter->hp * 100 / fighter->hpMax) {
					Battle_TriggerBattleEvent(1, fighter);
				}
			}
			break;
		case 55:
			battle.gameOverDisabled = true;
			if (battle.fighters[0].hp <= 0) {
				battle.battleEventVars[0]++;
				Battle_TriggerBattleEvent(5, fighter);
			}
			if (fighter->hp - fighter->status[FIGHTER_STATUS_POISON] - fighter->status[FIGHTER_STATUS_BURN] - fighter->status[FIGHTER_STATUS_BLEED] - fighter->status[FIGHTER_STATUS_TIMEDBOMB] <= 0 && battle.battleEventVars[1] < 999) {
				Battle_TriggerBattleEvent(11, fighter);
				interrupt = true;
			}
			break;
		case 57:
			if (battle.encounter != 40) break;
			int alliesAlive = 0;
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				alliesAlive++;
			}
			
			if ((fighter->hp < fighter->hpMax || alliesAlive == 1) && battle.battleEventVars[0] == 0) {
				battle.battleEventVars[0] = 1;
				Battle_TriggerBattleEvent(8, fighter);
			}
			else if (battle.battleEventVars[1] >= 2) {
				battle.battleEventVars[1] = 0;
				Battle_TriggerBattleEvent(9, fighter);
			}
			else if (battle.battleEventVars[1] >= 1) {
				battle.battleEventVars[1]++;
				fighter->status[FIGHTER_STATUS_HYPERENERGIZER] = 1;
				fighter->status[FIGHTER_STATUS_STRENGTH] = 50;
				fighter->status[FIGHTER_STATUS_ENDURANCE] = 50;
				fighter->status[FIGHTER_STATUS_HASTE] = 50;
				fighter->status[FIGHTER_STATUS_COUNTER] = 10;
			}
			break;
		case 72:
			if (fighter->battleEventVars[0] == 0) {
				Battle_TriggerBattleEvent(12, fighter);
				fighter->status[FIGHTER_STATUS_WEAPONSEARCH] = 1;
			}
			else if (fighter->battleEventVars[0] == 2) {
				Battle_TriggerBattleEvent(13, fighter);
				fighter->status[FIGHTER_STATUS_WEAPONSEARCH] = 0;
			}
			fighter->battleEventVars[0]++;
			break;
		case 73:
			if (fighter->battleEventVars[0] == 0 && fighter->hp <= fighter->hpMax / 2) {
				fighter->battleEventVars[0] = 1;
			}
			break;
		
		case 191:
			if (fighter->hp <= 150 && battle.battleEventVars[2] == 0) {
				Battle_TriggerBattleEvent(192, fighter);
				battle.battleEventVars[2]++;
			}
			else if (fighter->hp - fighter->status[FIGHTER_STATUS_POISON] - fighter->status[FIGHTER_STATUS_BURN] - fighter->status[FIGHTER_STATUS_BLEED] - fighter->status[FIGHTER_STATUS_TIMEDBOMB] <= 0 && battle.battleEventVars[0] == 0) {
				Battle_TriggerBattleEvent(191, fighter);
				interrupt = true;
				fighter->alive = true;
			}
			
			if (battle.battleEventVars[1] == 1 && battle.battleEventVars[2] == 1) {
				Battle_TriggerBattleEvent(193, fighter);
				battle.battleEventVars[2]++;
				interrupt = true;
			}
			if (battle.battleEventVars[1] == 2 && battle.battleEventVars[2] == 2) {
				Battle_TriggerBattleEvent(195, fighter);
				battle.battleEventVars[2]++;
				interrupt = true;
			}
			if (battle.battleEventVars[1] == 3 && battle.battleEventVars[2] == 3) {
				Battle_TriggerBattleEvent(194, fighter);
				battle.battleEventVars[2]++;
				interrupt = true;
			}
			break;
		
		case 192:
			/*if (battle.battleEventVars[0] == 0) {
				if (battle.battleEventVars[2] == 0) battle.battleEventVars[2]++;
				Battle_TriggerBattleEvent(197, fighter);
				interrupt = true;
			}*/
			
			if (fighter->hp - fighter->status[FIGHTER_STATUS_POISON] - fighter->status[FIGHTER_STATUS_BURN] - fighter->status[FIGHTER_STATUS_BLEED] - fighter->status[FIGHTER_STATUS_TIMEDBOMB] <= 0 && battle.battleEventVars[0] == 0) {
				if (battle.battleEventVars[2] == 0) battle.battleEventVars[2]++;
				Battle_TriggerBattleEvent(196, fighter);
				interrupt = true;
				fighter->alive = true;
			}
			else if (fighter->hp <= 150 && battle.battleEventVars[2] == 0) {
				Battle_TriggerBattleEvent(192, fighter);
				battle.battleEventVars[2]++;
			}
			
			if (battle.battleEventVars[1] == 1 && battle.battleEventVars[2] == 1) {
				Battle_TriggerBattleEvent(193, fighter);
				battle.battleEventVars[2]++;
				interrupt = true;
			}
			if (battle.battleEventVars[1] == 2 && battle.battleEventVars[2] == 2) {
				Battle_TriggerBattleEvent(195, fighter);
				battle.battleEventVars[2]++;
				interrupt = true;
			}
			if (battle.battleEventVars[1] == 3 && battle.battleEventVars[2] == 3) {
				Battle_TriggerBattleEvent(194, fighter);
				battle.battleEventVars[2]++;
				interrupt = true;
			}
			break;
		
		// Armor special ability
		case 10002:
			if (fighter->battleEventVars[0] == 0) {
				profile.flags[FLAG_ARMOR_BRIAN_BATTLES]++;
				Battle_TriggerBattleEvent(14, fighter);
				fighter->status[FIGHTER_STATUS_WEAPONSEARCH] = 1;
			}
			else if (fighter->battleEventVars[0] == 2) {
				fighter->status[FIGHTER_STATUS_WEAPONSEARCH] = 0;
			}
			fighter->battleEventVars[0]++;
			break;
	}
	
	return interrupt;
}

void Fighter_AI_TurnEnd(Fighter* fighter) {
	switch (fighter->ai) {
		case 4: case 5: case 191:
			if (battle.battleEventVars[3] == 0) {
				for (int i = 0; i < 8; i++) {
					if (battle.fighters[i].actionId == 32) {
						if (profile.flags[FLAG_LULU_HANDSHAKES] == 0) {
							Battle_TriggerBattleEvent(3, fighter);
						}
						else {
							Battle_TriggerBattleEvent(4, fighter);
						}
						profile.flags[FLAG_LULU_HANDSHAKES]++;
						battle.battleEventVars[3] = 1;
						break;
					}
				}
			}
			break;
		
		// Armor special ability
		case 10001:
			if (battle.encounter == 55) break;
			profile.flags[FLAG_ARMOR_HELLGONER_TURNCOUNT]++;
			if (profile.flags[FLAG_ARMOR_HELLGONER_TURNCOUNT] == 11 && profile.flags[FLAG_ARMOR_HELLGONER_COMPLAINT] == 0) {
				Battle_TriggerBattleEvent(7, fighter);
				profile.flags[FLAG_ARMOR_HELLGONER_COMPLAINT] = 1;
			}
			if (profile.flags[FLAG_ARMOR_HELLGONER_TURNCOUNT] >= 18) {
				Battle_TriggerBattleEvent(6, fighter);
			}
			break;
	}
}

void Fighter_AI_ChooseAction(Fighter* fighter) {
	int preferAction = 0;
	int preferTarget = -1;
	
	switch (fighter->ai) {
		case 2: {
			if (battle.turnCount % 3 <= 1 && battle.fighters[8].headId == 4 && battle.fighters[8].alive)
				preferAction = 25;
		} break;
		
		case 5: {
			if (fighter->hp < 120)
				preferAction = 17;
			else if (battle.turnCount == 1 || fighter->mp < 100)
				preferAction = 18;
			else if (battle.turnCount == 2)
				preferAction = 19;
			else if (Random(1) < 0.25)
				preferAction = 20;
			else
				preferAction = 19;
		} break;
		
		case 6: {
			if (battle.turnCount == 1)
				preferAction = 40;
			else if (battle.turnCount == 2)
				preferAction = 39;
			else if (Random(1) < 0.5)
				preferAction = 40;
			else
				preferAction = 39;
			
			if (fighter->status[FIGHTER_STATUS_STRENGTH] >= 8)
				preferAction = 41;
			
			if (fighter->hp <= fighter->hpMax / 2)
				preferAction = 42;
		} break;
		
		case 7: {
			if (battle.turnCount == 1)
				preferAction = 5;
			else
				preferAction = 3;
			
			for (int i = 0; i < 8; i++) {
				if (battle.fighters[i].enabled && battle.fighters[i].headId == 3) {
					preferTarget = i;
					break;
				}
			}
		} break;
		
		case 8: {
			if (battle.turnCount == 1 && battle.fighters[8].headId == 4)
				preferAction = 25;
			else
				preferAction = 1;
		} break;
		
		case 9: {
			if (battle.turnCount <= 4)
				preferTarget = Random_IRange(1, 2);
			
			if (battle.turnCount == 1) {
				preferAction = 11;
				preferTarget = 0;
			}
			else if (battle.turnCount % 6 == 3 && fighter->hp >= fighter->hpMax / 2)
				preferAction = 7;
			else if (battle.turnCount % 2 == 0 || (battle.turnCount % 6 < 5 && fighter->hp >= fighter->hpMax / 2))
				preferAction = 9;
			else if (Random(1) < 0.5)
				preferAction = 10;
			else
				preferAction = 11;
		} break;
		
		case 14: {
			if (battle.turnCount == 1) {
				if (Random(1) < 0.5)
					preferAction = 5;
				else
					preferAction = 6;
			}
		} break;
		
		case 24: {
			if (battle.turnCount == 1)
				preferAction = 32;
		} break;
		
		case 29: {
			if (battle.turnCount == 1) {
				preferAction = 8;
			}
		} break;
		
		case 33: {
			if (battle.turnCount == 1) {
				preferAction = 14;
			}
			else if (battle.turnCount == 2) {
				preferAction = 16;
				preferTarget = 3;
			}
			else if (battle.turnCount == 3) {
				preferAction = 16;
				preferTarget = 0;
			}
			else if (battle.turnCount == 4) {
				preferAction = 15;
				preferTarget = 0;
			}
			else if (Random(1) < 0.75 && fighter->mp >= 50) {
				preferAction = 16;
			}
			else if (Random(1) < 0.75) {
				preferAction = 15;
			}
		} break;
		
		case 37: {
			if (battle.turnCount == 1) {
				preferAction = 29;
			}
			for (int i = 0; i < 8; i++) {
				if (!battle.fighters[i].enabled || !battle.fighters[i].alive) continue;
				
				if (battle.fighters[i].status[FIGHTER_STATUS_DISARM]) {
					preferTarget = i;
					preferAction = 37;
					break;
				}
			}
		} break;
		
		case 38: {
			if (battle.turnCount == 1) {
				preferAction = 29;
			}
			for (int i = 0; i < 8; i++) {
				if (!battle.fighters[i].enabled || !battle.fighters[i].alive) continue;
				
				if (battle.fighters[i].status[FIGHTER_STATUS_DISARM]) {
					preferTarget = i;
					preferAction = 37;
					break;
				}
			}
		} break;
		
		case 51: {
			if (fighter->mp >= 14 && fighter->hp < 100 + 150 * (fighter->mp < 42)) {
				preferAction = 57;
				break;
			}
			if (fighter->mp < 64) {
				preferAction = 58;
				break;
			}
			
			if (battle.turnCount <= 2 || battle.battleEventVars[1] > 0) {
				preferAction = 56;
				battle.battleEventVars[1]--;
				break;
			}
			
			int s = 0;
			int count = 0;
			int countTotal = 0;
			for (int i = 0; i < 8; i++) {
				if (!battle.fighters[i].enabled || !battle.fighters[i].alive) continue;
				
				if (battle.fighters[i].status[FIGHTER_STATUS_FLOWER] > s) {
					preferTarget = i;
					preferAction = 59;
					s = battle.fighters[i].status[FIGHTER_STATUS_FLOWER];
					count++;
				}
				countTotal++;
			}
			if (count >= 1) {
				if (count >= 3 || count >= countTotal || battle.battleEventVars[0] >= 1) {
					battle.battleEventVars[0] = 0;
					preferAction = 60;
					break;
				}
				battle.battleEventVars[0]++;
				battle.battleEventVars[1] = 3 - count;
				break;
			}
			else {
				preferAction = 56;
				battle.battleEventVars[1] = 2;
			}
		} break;
		
		case 56: {
			int alliesAlive = 0;
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				alliesAlive++;
			}
			
			preferTarget = 3;
			
			if (alliesAlive == 1) {
				preferAction = 64;
			}
			else {
				if (battle.turnCount % 2 == 1)
					preferAction = 63;
				else
					preferAction = 5;
			}
		} break;
		
		case 57: {
			int alliesAlive = 0;
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				alliesAlive++;
			}
			
			preferTarget = 3;
			
			if (alliesAlive == 1) {
				preferAction = 64;
			}
			else {
				if (battle.turnCount % 4 < 2)
					preferAction = 63;
				else
					preferAction = 5;
			}
		} break;
		
		case 58: {
			if (fighter->status[FIGHTER_STATUS_STRENGTH] > 0) {
				preferAction = 66;
			}
			else if (!battle.fighters[9].alive || fighter->hp < fighter->hpMax / 4) {
				preferAction = 65;
			}
			else {
				if (Random(1) < 0.5)
					preferAction = 66;
				else
					preferAction = 2;
			}
		} break;
		
		case 59: {
			Fighter* fighter2 = NULL;
			for (int i = 8; i < 16; i++) {
				if (i == fighter->id) continue;
				if (!battle.fighters[i].enabled || !battle.fighters[i].alive) continue;
				
				fighter2 = &battle.fighters[i];
				break;
			}
			
			if (fighter->status[FIGHTER_STATUS_STRENGTH] > 0) {
				preferAction = 3;
			}
			else if (fighter2 != NULL) {
				if (fighter->mp >= 25 && fighter->hp <= fighter->hpMax / 2) {
					preferAction = 74;
					preferTarget = fighter->id;
				}
				else if (fighter->mp >= 25 && fighter2->hp <= fighter2->hpMax / 2) {
					preferAction = 74;
					preferTarget = fighter2->id;
				}
				else if (battle.turnCount % 3 <= 1) {
					preferAction = 67;
					preferTarget = 9;
				}
				else if (Random(1) < 0.5)
					preferAction = 67;
				else
					preferAction = 68;
			}
		} break;
		
		case 60: {
			int enemyCount = 0;
			int enemyWeakCount = 0;
			int enemySuperWeakCount = 0;
			for (int i = 0; i < 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				enemyCount++;
				if (fighter2->hp <= 40) {
					enemyWeakCount++;
				}
				if (fighter2->hp <= 4) {
					enemySuperWeakCount++;
				}
			}
			
			if (enemyCount == 1 && enemySuperWeakCount == 1) {
				preferAction = 73;
			}
			else if (battle.turnCount == 1 || enemyWeakCount >= 2 || enemyWeakCount == enemyCount) {
				if (fighter->hp >= fighter->hpMax / 3 && enemyCount == 1 && battle.turnCount <= 20 && Random(1) < 0.98) {
					if (battle.turnCount >= 17 && (Random(1) < 0.25 || battle.turnCount >= 19))
						preferAction = 71;
					else
						preferAction = 73;
				}
				else
					preferAction = 70;
			}
			else if (fighter->mp < 28) {
				preferAction = 72;
			}
			else if (battle.turnCount % 3 == 1) {
				preferAction = 61;
			}
			else {
				preferAction = 71;
			}
		} break;
		
		case 62: {
			if (fighter->mp < 48) {
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					if (fighter2->hp >= 15 && fighter2->hp < 50 - fighter->mp / 2) {
						preferAction = 85;
						preferTarget = i;
						break;
					}
				}
				if (preferAction == 85) {
					for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
						Fighter* fighter2 = &battle.fighters[i];
						if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
						
						if (fighter2->actionId == 85) {
							preferAction = 0;
							preferTarget = -1;
							break;
						}
					}
				}
				if (preferAction == 85) break;
			}
			
			int leastHP = 999999;
			for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->hp < leastHP) {
					preferTarget = i;
					leastHP = fighter2->hp;
				}
			}
			
			if (fighter->mp < 30) {
				if (battle.turnCount % 3 < 2)
					preferAction = 50;
				else
					preferAction = 3;
			}
			else {
				if (leastHP <= 7)
					preferAction = 3;
				else
					preferAction = 51;
			}
		} break;
		
		case 63: {
			if (fighter->status[FIGHTER_STATUS_CHARGE] == 0 || fighter->mp < 25) {
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					if (fighter2->hp >= 15 && fighter2->hp < 50 - fighter->mp / 2) {
						preferAction = 85;
						preferTarget = i;
						break;
					}
				}
				if (preferAction == 85) {
					for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
						Fighter* fighter2 = &battle.fighters[i];
						if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
						
						if (fighter2->actionId == 85) {
							preferAction = 0;
							preferTarget = -1;
							break;
						}
					}
				}
				if (preferAction == 85) break;
			}
			
			int mostHP = 0;
			for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->hp > mostHP) {
					preferTarget = i;
					mostHP = fighter2->hp;
				}
			}
			
			if (fighter->status[FIGHTER_STATUS_CHARGE] >= 1) {
				if (fighter->mp < 25)
					preferAction = 50;
				else
					preferAction = 77;
			}
			else if (fighter->mp < 25 && battle.turnCount % 4 == 0) {
				preferAction = 50;
			}
			else if (battle.turnCount == 1 || fighter->mp >= 25) {
				preferAction = 76;
			}
		} break;
		
		case 64: {
			if (fighter->hp > 11 && (fighter->mp < 40 || (fighter->mp < 90 && fighter->hp >= fighter->hpMax / 2)))
				preferAction = 36;
			else if ((battle.turnCount % 3 == 0 && fighter->hp < fighter->hpMax / 2 && fighter->mp >= 80) || fighter->hp <= 11)
				preferAction = 81;
			else if (battle.turnCount % 5 == 2)
				preferAction = 79;
			else if (battle.turnCount % 4 == 3)
				preferAction = 80;
			else if (battle.turnCount % 5 == 1)
				preferAction = 6;
			else if (battle.turnCount % 5 == 4)
				preferAction = 43;
			else if (fighter->hp < fighter->hpMax / 4)
				preferAction = 6;
			else
				preferAction = 36;
		} break;
		
		case 65: {
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || fighter2->alive) continue;
				
				preferAction = 83;
				preferTarget = i;
				break;
			}
			if (preferAction == 83) break;
			
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->hp < fighter2->hpMax / 3 && fighter2->hp >= 15) {
					preferAction = 74;
					preferTarget = i;
					break;
				}
			}
			if (preferAction == 74) break;
			
			for (int i = 0; i < 16; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->side != fighter->side) {
					int sum = 0;
					for (int j = 0; j < 32; j++) {
						if (statusEffectData[j].type == STATUS_TYPE_POSITIVE) {
							sum += fighter2->status[j];
						}
					}
					if (sum >= 60 - fighter->mp * 30 / fighter->mpMax) {
						preferAction = 82;
						preferTarget = i;
					}
					continue;
				}
				
				int sum = 0;
				for (int j = 0; j < 32; j++) {
					if (statusEffectData[j].type == STATUS_TYPE_NEGATIVE) {
						sum += fighter2->status[j];
					}
				}
				sum -= fighter2->status[FIGHTER_STATUS_CHARGE] * 10;
				if (sum >= 40 - fighter->mp * 20 / fighter->mpMax) {
					preferAction = 82;
					preferTarget = i;
					break;
				}
			}
			if (preferAction == 82) break;
			
			if (fighter->mp <= 60 || (fighter->mp <= 100 && Random(1) < 0.25)) {
				preferAction = 72;
			}
			else if (fighter->mp <= 80) {
				preferAction = 1;
			}
			else {
				preferAction = 61;
			}
		} break;
		
		case 72: {
			preferAction = 84;
		} break;
		
		case 73: {
			int most = 0;
			for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->status[FIGHTER_STATUS_BLEED] > most) {
					preferTarget = i;
					most = fighter2->status[FIGHTER_STATUS_BLEED];
				}
			}
			
			if (battle.turnCount % 3 == 0)
				preferAction = 90;
			else if (fighter->hp > fighter->hpMax / 2) {
				if (battle.turnCount % 4 == 1)
					preferAction = 87;
				else
					preferAction = 89;
			}
			else
				preferAction = 86;
		} break;
		
		case 74: {
			int alliesAlive = 0;
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				alliesAlive++;
			}
			
			if (fighter->status[FIGHTER_STATUS_CHARGE] >= 1) {
				if (fighter->mp < 35)
					preferAction = 50;
				else
					preferAction = 91;
			}
			else if (fighter->mp >= 25) {
				if (battle.turnCount % 3 == 2 || (battle.turnCount % 3 == 0 && alliesAlive >= 2))
					preferAction = 76;
				else if (fighter->hp < fighter->hpMax / 2)
					preferAction = 47;
				else
					preferAction = 46;
			}
			else {
				if (fighter->hp < fighter->hpMax / 2 && alliesAlive == 1)
					preferAction = 4;
				else
					preferAction = 50;
			}
		} break;
		
		case 75: {
			if (fighter->hp >= 5) {
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					if (fighter2->hp < 45 || fighter->hp < 60) {
						preferAction = 26;
						preferTarget = i;
						break;
					}
				}
				if (preferAction == 26) break;
			}
			
			if (fighter->status[FIGHTER_STATUS_STRENGTH] >= 15) {
				preferAction = 92;
			}
			else if (battle.turnCount % 4 == 1 && fighter->mp >= 23) {
				preferAction = 94;
			}
			else if (battle.turnCount % 4 == 0 || fighter->mp >= fighter->mpMax - 16) {
				preferAction = 93;
			}
			else {
				preferAction = 36;
			}
		} break;
		
		
		
		case 191: {
			if (battle.battleEventVars[0] == 1) {
				battle.battleEventVars[1]++;
				if (battle.battleEventVars[1] >= 4)
					preferAction = 191;
				else
					preferAction = 18;
			}
			else {
				if (fighter->hp > 150) {
					preferAction = Random_IRange(18, 20);
				}
				else {
					preferAction = 17;
				}
			}
		} break;
		
		case 192: {
			preferAction = 192;
		} break;
	}
	
	int poolSize = 0;
	int pool[16];
	
	for (int i = 0; i < fighter->movesetCount; i++) {
		if (fighter->mp < actionData[fighter->moveset[i]].cost) continue;
		if (fighter->movesetDisabled[i]) continue;
		if (!fighter->canAct) break;
		
		pool[poolSize++] = fighter->moveset[i];
	}
	
	if (poolSize > 0) {
		if (preferAction == -1)
			fighter->actionId = 0;
		else
			fighter->actionId = pool[Random_IRange(0, poolSize - 1)];
		if (preferAction > 0) {
			for (int i = 0; i < poolSize; i++) {
				if (pool[i] == preferAction) {
					fighter->actionId = preferAction;
					break;
				}
			}
		}
	}
	
	poolSize = 0;
	
	for (int i = 0; i < 16; i++) {
		Fighter* fighter2 = &battle.fighters[i];
		if (!fighter2->enabled) continue;
		
		if (fighter2->alive) {
			if (fighter2->side != fighter->side && (actionData[fighter->actionId].targetType == TARGETTYPE_ENEMY || actionData[fighter->actionId].targetType == TARGETTYPE_ANY)) {
				pool[poolSize++] = i;
			}
			else if (fighter2->side == fighter->side && (actionData[fighter->actionId].targetType == TARGETTYPE_ALLY || actionData[fighter->actionId].targetType == TARGETTYPE_ANY)) {
				pool[poolSize++] = i;
			}
		}
		else {
			if (fighter2->side == fighter->side && actionData[fighter->actionId].targetType == TARGETTYPE_DOWNALLY) {
				pool[poolSize++] = i;
			}
		}
	}
	
	if (poolSize > 0) {
		fighter->targetId = pool[Random_IRange(0, poolSize - 1)];
		
		if (preferTarget >= 0) {
			Fighter* fighter2 = &battle.fighters[preferTarget];
			if (fighter2->enabled && (fighter2->alive || actionData[fighter->actionId].targetType == TARGETTYPE_DOWNALLY))
			if (actionData[fighter->actionId].targetType == TARGETTYPE_ANY || (fighter2->side != fighter->side && actionData[fighter->actionId].targetType == TARGETTYPE_ENEMY) || (fighter2->side == fighter->side && actionData[fighter->actionId].targetType == TARGETTYPE_ALLY))
				fighter->targetId = preferTarget;
		}
	}
	
	if (actionData[fighter->actionId].targetType == TARGETTYPE_ENEMYPARTY)
		fighter->targetId = TARGET_ALLYPARTY;
	else if (actionData[fighter->actionId].targetType == TARGETTYPE_ALLYPARTY)
		fighter->targetId = TARGET_ENEMYPARTY;
}

int Fighter_AI_Attack(Fighter* fighter, Fighter* target) {
	int attack = 0;
	
	switch (fighter->ai) {
		case 1: {
			if (fighter->readyTimer >= 15) {
				attack = 1;
			}
		} break;
		
		case 2: {
			if (fighter->readyTimer == 9 && Random(1) < 0.25) {
				attack = 1;
			}
			else if (fighter->readyTimer % 30 == 19 && Random(1) < 0.75) {
				attack = 1;
			}
		} break;
		
		case 7: {
			if (fighter->hp <= fighter->hpMax / 2 && fighter->readyTimer >= 3) {
				attack = 1;
			}
			else if (fighter->readyTimer >= 12) {
				attack = 1;
			}
		} break;
		
		case 8: {
			if ((fighter->readyTimer == 18 && battle.turnCount > 1) || fighter->readyTimer >= 30) {
				attack = 1;
			}
		} break;
		
		case 9: {
			if (battle.turnCount % 2 == 0) {
				if ((battle.turnCount % 6 < 4 && fighter->readyTimer == 4) || (fighter->readyTimer > 16 && Random(1) < 0.05)) {
					attack = 1;
				}
			}
			else {
				if (Random(1) < 0.1 || fighter->readyTimer >= 40) {
					attack = 1;
				}
			}
		} break;
		
		case 24: {
			if (game.timer % 87 == 0) {
				attack = 1;
			}
		} break;
		
		case 33: {
			if (target->headId == 4) {
				attack = 1;
			}
			else if (target->headId == 1) {
				if (fighter->readyTimer >= 60) {
					attack = 1;
				}
			}
			else {
				if ((fighter->readyTimer % 10 == 0 && Random(1) < 0.3) || fighter->readyTimer >= 40) {
					attack = 1;
				}
			}
		} break;
		
		case 55: {
			if (fighter->readyTimer >= 8) {
				attack = 1;
			}
		} break;
		
		case 57:
			if (battle.battleEventVars[1] >= 1) {
				attack = 1;
			}
			else if (Random(1) < 0.1) {
				attack = 1;
			}
			break;
			
		case 64:
			if (battle.turnCount % 7 == 0) {
				if (fighter->actionAttacks == 1) {
					if ((fighter->readyTimer >= 140 || target->blockTimer + 8 >= target->blockTime) && Random(1) < 0.5) attack = 1;
				}
				else
					attack = 1;
			}
			else if (battle.turnCount % 7 == 5) {
				if (fighter->actionAttacks == 0) {
					if ((fighter->readyTimer >= 140 || target->blockTimer + 8 >= target->blockTime) && Random(1) < 0.5) attack = 1;
				}
				else
					attack = 1;
			}
			else if (target->blockTimer + 6 < target->blockTime) {
				
			}
			else if (target->blockTimer + 6 >= target->blockTime) {
				if (Random(1) < 0.5)
					attack = 1;
			}
			else if (battle.turnCount % 3 == 2) {
				if (Random(1) < 0.08)
					attack = 1;
			}
			else {
				if (Random(1) < 0.15)
					attack = 1;
			}
			break;
		
		case 72: {
			if (fighter->readyTimer >= 22) {
				attack = 1;
			}
		} break;
		
		default: {
			if (Random(1) < 0.1) {
				attack = 1;
			}
		} break;
	}
	
	return attack;
}

int Fighter_AI_Block(Fighter* fighter, Fighter* attacker) {
	int blocked = 0;
	
	switch (fighter->ai) {
		case 1: case 8: {
			
		} break;
		
		case 2: case 7: {
			if (attacker->totalAttackTimer == 9 && Random(1) < 0.1) {
				blocked = 1;
			}
			else if (attacker->totalAttackTimer % 60 == 19 && Random(1) < 0.25) {
				blocked = 1;
			}
		} break;
		
		case 3: {
			if ((attacker->readyTimer >= 4 || attacker->attackTimer >= 0) && Random(1) < 0.25) {
				blocked = 1;
			}
		} break;
		
		case 4: {
			if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 15 && Random(1) < 0.1) {
				blocked = 1;
			}
		} break;
		
		case 5: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Random(1) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Random(1) < 0.75))) {
				blocked = 1;
			}
		} break;
		
		case 6: {
			if (attacker->actionId == 92) {
				if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Random(1) < 0.99) {
					blocked = 1;
				}
				break;
			}
			if (battle.turnCount % 2 == 1 && fighter->hp >= fighter->hpMax / 2) {
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Random(1) < 0.15) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Random(1) < 0.5))) {
					blocked = 1;
				}
				break;
			}
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 2 && Random(1) < 0.5) || (attacker->attackAnimTimer > attacker->attackAnimTime && Random(1) < 0.92))) {
				blocked = 1;
			}
		} break;
		
		case 9: {
			if (attacker->readyTimer >= 18 && Random(1) < 0.15) {
				blocked = 1;
			}
		} break;
		
		case 24: {
			if (game.timer % 87 == 0) {
				blocked = 1;
			}
		} break;
		
		case 33: {
			if (attacker->headId == 1) {
				if (attacker->totalAttackTimer % 60 == 50 && Random(1) < 0.3) {
					blocked = 1;
				}
			}
			else if (attacker->headId == 4) {
				if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 18 && Random(1) < 0.5) {
					blocked = 1;
				}
			}
			else {
				if ((attacker->totalAttackTimer == 40 && Random(1) < 0.2) || (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 16 && Random(1) < 0.15)) {
					blocked = 1;
				}
			}
		} break;
		
		case 38: {
			if (fighter->hp < fighter->hpMax / 4) {
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Random(1) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Random(1) < 0.5))) {
					blocked = 1;
				}
			}
			else {
				if (Random(1) < 0.05) {
					blocked = 1;
				}
			}
		} break;
		
		case 51: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Random(1) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Random(1) < 0.4))) {
				blocked = 1;
			}
		} break;
		
		case 55: {
			
		} break;
		
		case 64: {
			if (attacker->hp < attacker->hpMax / 6) {
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && (Random(1) < 0.1 || battle.turnCount % 5 == 2)) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Random(1) < 0.75))) {
					blocked = 1;
				}
			}
			else if (attacker->hp < attacker->hpMax * 3 / 4) {
				if (attacker->totalAttackTimer == 12 && battle.turnCount % 3 < 2) {
					blocked = 1;
				}
				else if (attacker->hp < attacker->hpMax / 3) {
					if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Random(1) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Random(1) < 0.75))) {
						blocked = 1;
					}
				}
				else if (attacker->totalAttackTimer % 40 == 14 && Random(1) < 0.5) {
					blocked = 1;
				}
			}
		} break;
		
		case 72: {
			
		} break;
		
		case 73: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Random(1) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Random(1) < 0.5))) {
				blocked = 1;
			}
		} break;
		
		case 191: case 192: {
			if (battle.battleEventVars[0] == 0 && attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Random(1) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Random(1) < 0.9))) {
				blocked = 1;
			}
		} break;
		
		default: {
			if (Random(1) < 0.05) {
				blocked = 1;
			}
		} break;
	}
	
	return blocked;
}
