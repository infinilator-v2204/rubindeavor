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
		case 32:
			if (profile.flags[FLAG_BASHURA_PLOT] < 1) {
				profile.flags[FLAG_BASHURA_PLOT] = 1;
			}
			break;
		case 55:
			battle.gameOverDisabled = true;
			if (battle.fighters[0].hp <= 0) {
				battle.battleEventVars[0]++;
				Battle_TriggerBattleEvent(5, fighter);
			}
			if (fighter->hp <= 0 && battle.battleEventVars[1] < 999) {
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
		case 88:
			fighter->aiVars[1].f = (float)(fighter->aiVars[0].i - fighter->hp) / (float)fighter->hpMax;
			fighter->aiVars[0].i = fighter->hp;
			break;
		case 90:
			battle.gameOverDisabled = true;
			if (battle.fighters[0].hp <= 0) {
				Battle_TriggerBattleEvent(17, fighter);
			}
			break;
		case 91:
			battle.gameOverDisabled = true;
			if (battle.fighters[0].hp <= 0 && battle.fighters[1].hp <= 0 && battle.fighters[2].hp <= 0 && battle.fighters[3].hp <= 0) {
				Battle_TriggerBattleEvent(18, fighter);
			}
			break;
		case 101:
			if (fighter->hp <= 0 && battle.battleEventVars[0] == 0) {
				Battle_TriggerBattleEvent(21, fighter);
				interrupt = true;
			}
			break;
		case 102:
			if (profile.flags[FLAG_ALONE] && battle.battleEventVars[0] < 2) {
				battle.battleEventVars[0] = 2;
			}
			
			if (profile.flags[FLAG_RUBY_GODMODE] > 0) {
				battle.gameOverDisabled = false;
				
				if (fighter->hp <= 0) {
					Battle_TriggerBattleEvent(51, fighter);
					interrupt = true;
				}
			}
			else {
				battle.gameOverDisabled = true;
				if (profile.flags[FLAG_ALONE]) {
					if (battle.fighters[0].hp <= 0) {
						Battle_TriggerBattleEvent(50, fighter);
						interrupt = true;
					}
				}
				else if (battle.fighters[0].hp <= 0 && battle.fighters[1].hp <= 0 && battle.fighters[2].hp <= 0 && battle.fighters[3].hp <= 0) {
					Battle_TriggerBattleEvent(24, fighter);
				}
			}
			break;
		case 103:
			if (battle.turnCount >= 2) {
				Fighter_TakeDamage(fighter, NULL, 48295153, 0);
			}
			if (fighter->hp <= 0) {
				if (profile.flags[FLAG_RUBY_GODMODE]) {
					Battle_TriggerBattleEvent(56, fighter);
				}
				else {
					Battle_TriggerBattleEvent(25, fighter);
				}
				interrupt = true;
			}
			break;
		case 104:
			if (!fighter->alive) break;
			
			Fighter_DisableAction(fighter, 211);
			Fighter_DisableAction(fighter, 212);
			if (fighter->hp <= 300 + fighter->aiVars[0].i * 8 && fighter->aiVars[0].i < 5) {
				Fighter_EnableAction(fighter, 211);
				if (battle.battleEventVars[2] < 1) {
					battle.battleEventVars[2] = 1;
					Battle_TriggerBattleEvent(32, fighter);
					interrupt = true;
				}
			}
			if (fighter->aiVars[0].i >= 3 && fighter->aiVars[1].i < fighter->aiVars[0].i - 2) {
				Fighter_EnableAction(fighter, 212);
				if (battle.battleEventVars[2] < 2) {
					battle.battleEventVars[2] = 2;
					battle.battleEventVars[1] = 10;
					Battle_TriggerBattleEvent(33, fighter);
					interrupt = true;
				}
				if (battle.battleEventVars[2] < 3 && fighter->aiVars[0].i == 5) {
					battle.battleEventVars[2] = 3;
					Battle_TriggerBattleEvent(37, fighter);
					interrupt = true;
				}
			}
			break;
		case 105:
			if (fighter->hp <= 0) break;
			if (!battle.fighters[9].alive && battle.battleEventVars[0] < 4) {
				Battle_TriggerBattleEvent(44, fighter);
				battle.battleEventVars[0] = 4;
				interrupt = true;
			}
			else if (fighter->hp < 225 && fighter->mp >= 120 && battle.battleEventVars[0] < 3) {
				Battle_TriggerBattleEvent(43, fighter);
				battle.battleEventVars[0] = 3;
				interrupt = true;
			}
			else if (battle.turnCount == 5 && battle.battleEventVars[0] < 2) {
				Battle_TriggerBattleEvent(42, fighter);
				battle.battleEventVars[0] = 2;
				interrupt = true;
			}
			else if (battle.turnCount == 3 && battle.battleEventVars[0] < 1) {
				Battle_TriggerBattleEvent(41, fighter);
				battle.battleEventVars[0] = 1;
				interrupt = true;
			}
			break;
		case 106:
			if (fighter->hp <= 0) break;
			if (fighter->hp < 100 && battle.battleEventVars[1] < 4) {
				Battle_TriggerBattleEvent(48, fighter);
				battle.battleEventVars[1] = 4;
				interrupt = true;
			}
			else if (!battle.fighters[8].alive && battle.battleEventVars[1] < 3) {
				Battle_TriggerBattleEvent(47, fighter);
				battle.battleEventVars[1] = 3;
				interrupt = true;
			}
			else if (fighter->hp < 350 && fighter->mp >= 216 - fighter->manaCostReduction && battle.battleEventVars[1] < 2) {
				Battle_TriggerBattleEvent(46, fighter);
				battle.battleEventVars[1] = 2;
				interrupt = true;
			}
			else if (fighter->hp < 655 && battle.battleEventVars[1] < 1) {
				Battle_TriggerBattleEvent(45, fighter);
				battle.battleEventVars[1] = 1;
				interrupt = true;
			}
			break;
		case 107:
			if (fighter->hp <= 0) {
				Battle_TriggerBattleEvent(55, fighter);
				interrupt = true;
			}
			else if (fighter->mp >= 837 && fighter->aiVars[0].i == 0 && (fighter->hp < fighter->hpMax / 6 || (fighter->hp < 5000 && battle.fighters[0].status[FIGHTER_STATUS_CHARGE] >= 6)) && battle.battleEventVars[0] < 2) {
				Battle_TriggerBattleEvent(54, fighter);
				battle.battleEventVars[0] = 2;
				interrupt = true;
			}
			else if (battle.fighters[0].hp <= battle.fighters[0].hpMax / 2 && battle.battleEventVars[0] < 1) {
				Battle_TriggerBattleEvent(53, fighter);
				battle.battleEventVars[0] = 1;
				interrupt = true;
			}
			break;
		case 108:
			battle.gameOverDisabled = true;
			if (battle.fighters[0].hp <= 0) {
				Battle_TriggerBattleEvent(57, fighter);
				interrupt = true;
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
		case 4: case 5: case 28: case 191:
			if (battle.battleEventVars[3] == 0) {
				for (int i = 0; i < 8; i++) {
					if (battle.fighters[i].actionId == 32) {
						if (profile.flags[FLAG_LULU_HANDSHAKES] == 0) {
							Battle_TriggerBattleEvent(3, fighter);
						}
						else if (profile.flags[FLAG_LULU_HANDSHAKES] == 1) {
							Battle_TriggerBattleEvent(4, fighter);
						}
						else if (profile.flags[FLAG_LULU_HANDSHAKES] == 2) {
							Battle_TriggerBattleEvent(39, fighter);
						}
						profile.flags[FLAG_LULU_HANDSHAKES]++;
						battle.battleEventVars[3] = 1;
						break;
					}
				}
			}
			break;
		case 92:
			if (!fighter->alive) break;
			
			if (battle.battleEventVars[3] == 0) {
				for (int i = 0; i < 8; i++) {
					if (battle.fighters[i].actionId == 32) {
						if (profile.flags[FLAG_LULU_HANDSHAKES] == 0) {
							Battle_TriggerBattleEvent(3, fighter);
						}
						else if (profile.flags[FLAG_LULU_HANDSHAKES] == 1) {
							Battle_TriggerBattleEvent(4, fighter);
						}
						else if (profile.flags[FLAG_LULU_HANDSHAKES] == 2) {
							Battle_TriggerBattleEvent(39, fighter);
						}
						profile.flags[FLAG_LULU_HANDSHAKES]++;
						battle.battleEventVars[3] = 1;
						battle.battleEventVars[0] = 2;
						break;
					}
				}
			}
			
			if (battle.battleEventVars[0] < 2 && fighter->hp < fighter->hpMax) {
				Battle_TriggerBattleEvent(20, fighter);
				battle.battleEventVars[0] = 2;
			}
			else if (battle.battleEventVars[0] == 0 && actionData[battle.fighters[0].actionId].category == ACTIONCATEGORY_ATTACK) {
				Battle_TriggerBattleEvent(19, fighter);
				battle.battleEventVars[0] = 1;
			}
			break;
		case 102:
			if (!fighter->alive) break;
			
			if (battle.battleEventVars[3] == 0) {
				for (int i = 0; i < 8; i++) {
					if (battle.fighters[i].actionId == 32) {
						Battle_TriggerBattleEvent(40, fighter);
						profile.flags[FLAG_LULU_HANDSHAKES]++;
						battle.battleEventVars[3] = 1;
						battle.battleEventVars[0] = 2;
						break;
					}
				}
			}
			
			fighter->aiVars[0].i = Random_IRange(0, 7);
			
			if (profile.flags[FLAG_RUBY_GODMODE] > 0) {
				if (battle.fighters[0].actionId > 0 && battle.battleEventVars[0] < 3) {
					Battle_TriggerBattleEvent(52, fighter);
					battle.battleEventVars[0] = 3;
				}
			}
			
			if (battle.battleEventVars[0] < 2 && fighter->hp <= fighter->hpMax * 2 / 3) {
				Battle_TriggerBattleEvent(22, fighter);
				battle.battleEventVars[0] = 2;
			}
			else if (battle.battleEventVars[0] == 0 && battle.turnCount == 3) {
				if (battle.fighters[3].enabled && battle.fighters[3].alive) {
					Battle_TriggerBattleEvent(23, fighter);
				}
				battle.battleEventVars[0] = 1;
			}
			break;
		case 104:
			if (!fighter->alive) break;
			
			if (battle.battleEventVars[1] == 0) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(26, fighter);
			}
			else if (battle.battleEventVars[1] == 1) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(27, fighter);
			}
			else if (battle.battleEventVars[1] == 2) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(28, fighter);
			}
			else if (battle.battleEventVars[1] == 3 && fighter->aiVars[0].i >= 1) {
				battle.battleEventVars[1]++;
			}
			else if (battle.battleEventVars[1] == 4) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(29, fighter);
			}
			else if (battle.battleEventVars[1] == 5) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(30, fighter);
			}
			else if (battle.battleEventVars[1] == 6) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(31, fighter);
			}
			else if (battle.battleEventVars[1] == 7 && fighter->aiVars[0].i >= 2) {
				battle.battleEventVars[1]++;
			}
			else if (battle.battleEventVars[1] == 8) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(34, fighter);
			}
			else if (battle.battleEventVars[1] == 9 && fighter->aiVars[0].i < 3) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(35, fighter);
			}
			else if (battle.battleEventVars[1] == 10 && fighter->aiVars[0].i >= 3) {
				battle.battleEventVars[1]++;
			}
			else if (battle.battleEventVars[1] == 11) {
				battle.battleEventVars[1]++;
			}
			else if (battle.battleEventVars[1] == 12) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(36, fighter);
			}
			else if (battle.battleEventVars[1] == 13 && fighter->aiVars[1].i >= 3) {
				battle.battleEventVars[1]++;
				Battle_TriggerBattleEvent(38, fighter);
			}
			break;
		case 105:
			if (!fighter->alive && !battle.fighters[9].alive && battle.battleEventVars[2] == 0) {
				Battle_TriggerBattleEvent(49, fighter);
				battle.battleEventVars[2] = 1;
			}
			break;
		case 109:
			if (battle.fighters[0].actionId == 180) {
				fighter->aiVars[0].i++;
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
		
		case 46: {
			if (battle.turnCount == 1) {
				preferAction = 6;
				break;
			}
			else if (battle.turnCount == 2) {
				preferAction = 53;
				break;
			}
			
			if (fighter->aiVars[1].i > 0) fighter->aiVars[1].i--;
			if (fighter->hp < fighter->hpMax / 4 && fighter->mp >= 84 && fighter->aiVars[1].i == 0) {
				preferAction = 146;
				fighter->aiVars[1].i = 3;
				break;
			}
			
			if (fighter->mp < 99 && fighter->hp > fighter->hpMax / 5 && fighter->hp < fighter->hpMax / 2) {
				preferAction = 55;
				break;
			}
			
			if (fighter->status[FIGHTER_STATUS_CHARGE]) {
				if (fighter->mp < 99)
					preferAction = 55;
				else
					preferAction = 54;
				break;
			}
			
			if (fighter->hp < fighter->hpMax / 2 && fighter->aiVars[0].i == 0) {
				fighter->aiVars[0].i++;
				if (fighter->status[FIGHTER_STATUS_CHARGE]) {
					preferAction = 54;
				}
				else {
					preferAction = 55;
				}
				break;
			}
			if (battle.turnCount % 4 == 1 && fighter->hp < fighter->hpMax * 3 / 4) {
				preferAction = 146;
				break;
			}
			
			for (int i = 0; i < 8; i++) {
				if (!battle.fighters[i].enabled || !battle.fighters[i].alive) continue;
				
				if (battle.fighters[i].status[FIGHTER_STATUS_PARALYSIS] >= 10 || (battle.fighters[i].status[FIGHTER_STATUS_PARALYSIS] >= 4 && fighter->mp < fighter->mpMax / 2)) {
					preferTarget = i;
					preferAction = 143;
					break;
				}
			}
		} break;
		
		case 51: {
			if (fighter->mp >= 14 && fighter->hp < 100 + 150 * (fighter->mp < 42)) {
				preferAction = 57;
				break;
			}
			if (fighter->mp < 60) {
				preferAction = 58;
				break;
			}
			
			if (battle.turnCount <= 2 || (battle.battleEventVars[1] > 0 && fighter->hp >= fighter->hpMax / 2)) {
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
				if (count > 1 && (count >= 3 || count >= countTotal || battle.battleEventVars[0] >= 1)) {
					battle.battleEventVars[0] = 0;
					preferAction = 60;
					break;
				}
				battle.battleEventVars[0]++;
				battle.battleEventVars[1] = 3 - count;
				break;
			}
			else if (fighter->hp < fighter->hpMax / 2) {
				preferAction = 60;
			}
			else {
				preferAction = 56;
				battle.battleEventVars[1] = 1;
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
					
					if (fighter2->hp < 45) {
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
		
		case 76: {
			if (battle.turnCount == 1)
				preferAction = 110;
			else if (fighter->status[FIGHTER_STATUS_STRENGTH] >= 10) {
				int most = 0;
				preferAction = 115;
				
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->hp > most) {
						most = fighter2->hp;
						preferTarget = i;
					}
				}
			}
			else if (fighter->hp > fighter->hpMax / 2 && !fighter->status[FIGHTER_STATUS_MANADISCOUNT])
				preferAction = 107;
			else if (fighter->mp >= 5 && fighter->mp < 25 && fighter->hp > fighter->hpMax / 2)
				preferAction = 108;
			else if (fighter->mp >= 16 - fighter->manaCostReduction)
				preferAction = 113;
			else
				preferAction = 108;
		} break;
		
		case 78: {
			if (battle.turnCount == 1) {
				preferAction = 116;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					preferTarget = i;
					break;
				}
			}
			else if (fighter->mp < 33) {
				preferAction = 72;
			}
			else if (fighter->hp < fighter->hpMax / 2 && fighter->battleEventVars[0] == 0) {
				preferAction = 109;
				fighter->battleEventVars[0] = 1;
			}
			else {
				int least = 9999;
				preferAction = 65;
				
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->hp <= 14) {
						preferAction = 4;
						preferTarget = i;
						break;
					}
					else if (fighter2->hp < least) {
						least = fighter2->hp;
						preferTarget = i;
					}
				}
			}
			
			if (battle.turnCount % 3 <= 1) {
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->hp < 30 + (fighter == fighter2) * 30) {
						preferTarget = i;
						preferAction = 117;
						break;
					}
				}
			}
		} break;
		
		case 86: {
			for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				if (fighter2->status[FIGHTER_STATUS_ANTIGUARD]) {
					preferTarget = i;
					preferAction = 125;
					break;
				}
			}
			
			if (preferTarget >= 0) break;
			
			if (battle.turnCount % 2 == 0) {
				int leastDefense = 0;
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					int defense = fighter2->defense + fighter2->status[FIGHTER_STATUS_ENDURANCE] - fighter2->status[FIGHTER_STATUS_DISARM];
					if (defense < leastDefense) {
						preferTarget = i;
						preferAction = 129;
						leastDefense = defense;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (battle.turnCount == 1)
				preferAction = 128;
			else if (fighter->mp < 45 || (battle.turnCount % 4 >= 2 && fighter->mp < 60))
				preferAction = 50;
			else if (battle.turnCount % 4 == 0)
				preferAction = 125;
			else if (battle.turnCount % 4 == 3)
				preferAction = 126;
			else {
				preferAction = 128;
				
				int mostDefense = 0;
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					int defense = fighter2->defense + fighter2->status[FIGHTER_STATUS_ENDURANCE] - fighter2->status[FIGHTER_STATUS_DISARM];
					if (defense > mostDefense) {
						preferTarget = i;
						preferAction = 127;
						mostDefense = defense;
					}
				}
			}
		} break;
		
		case 87: {
			if (battle.turnCount % 4 == 3) {
				preferAction = 131;
				break;
			}
			
			if (battle.turnCount % 5 < 4) {
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					if (battle.turnCount % 9 == 3 || (Random(1) < 0.25 && fighter2->hp >= 100)) {
						preferTarget = i;
						preferAction = 68;
						break;
					}
					if (fighter2->hp < fighter2->hpMax - 10) {
						preferTarget = i;
						preferAction = 27;
						break;
					}
				}
			}
		} break;
		
		case 88: {
			if (battle.turnCount % 4 != 3) {
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					if ((fighter2->hp < 50 && battle.turnCount % 5 >= 3) || (fighter2->hp < 100 && battle.turnCount <= 2 && fighter->hp >= fighter->hpMax * 2 / 3)) {
						preferTarget = i;
						preferAction = 121;
						break;
					}
				}
			}
			
			if (preferTarget >= 0) break;
			
			if (fighter->mp >= 10 && (fighter->aiVars[1].f >= 0.5 || fighter->hp < 50 || (fighter->hp < 100 && fighter->aiVars[1].f >= 0.3) || battle.turnCount >= 22))
				preferAction = 105;
			else if (fighter->hp >= fighter->hpMax * 3 / 4 && battle.turnCount <= 4)
				preferAction = 132;
			else if (fighter->mp < 52)
				preferAction = 134;
			else if (fighter->status[FIGHTER_STATUS_CHARGE])
				preferAction = 133;
			else if (fighter->mp < 80)
				preferAction = 134;
			else
				preferAction = 76;
		} break;
		
		case 89: {
			if (battle.turnCount % 3 >= 1) {
				int leastMP = 10 - (battle.turnCount % 3 == 1) * 3;
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->mp < leastMP) {
						preferTarget = i;
						preferAction = 136;
						leastMP = fighter2->mp;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (fighter->hp <= fighter->hpMax / 2) {
				int leastMP = 999999;
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->mp < leastMP) {
						preferTarget = i;
						leastMP = fighter2->mp;
					}
				}
				preferAction = 137;
			}
			else if (battle.turnCount == 1 || fighter->mp >= 33 || battle.turnCount % 3 == 0) {
				int leastMP = 999999;
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->mp < leastMP) {
						preferTarget = i;
						leastMP = fighter2->mp;
					}
				}
				preferAction = 135;
			}
			else if (battle.turnCount % 4 != 2 && (fighter->mp < 18 || (fighter->mp < 33 && fighter->hp > fighter->hpMax / 2)))
				preferAction = 36;
			else {
				int leastHP = 999999;
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->hp < leastHP) {
						preferTarget = i;
						leastHP = fighter2->hp;
					}
				}
				
				preferAction = 5;
			}
		} break;
		
		case 90: {
			if (battle.turnCount == 1 || (battle.turnCount <= Min(4, 6 - fighter->mpMax / 10) && fighter->hp >= fighter->hpMax / 2))
				preferAction = 142;
			else if (fighter->mp >= 15 - fighter->manaCostReduction)
				preferAction = 139;
			else if (fighter->mp >= 5 - fighter->manaCostReduction)
				preferAction = 138;
			else
				preferAction = 142;
		} break;
		
		case 91: {
			if (fighter->mp < 120)
				preferAction = 72;
			else if (battle.turnCount % 2 == 1)
				preferAction = 144;
			else
				preferAction = -1;
		} break;
		
		case 92: {
			if (battle.battleEventVars[0] >= 2 || battle.turnCount >= 13) {
				if (fighter->mp < 45) {
					int leastHP = 36;
					for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
						Fighter* fighter2 = &battle.fighters[i];
						if (!fighter2->enabled || !fighter2->alive) continue;
						
						if (fighter2->hp < leastHP) {
							preferTarget = i;
							if (fighter2->hp < 25 || fighter->mp < 18)
								preferAction = 18;
							else
								preferAction = 19;
							leastHP = fighter2->hp;
						}
					}
					
					if (preferAction == 0)
						preferAction = -1;
				}
				else if (fighter->mp >= 115 && (fighter->mp <= 160 || battle.battleEventVars[0] >= 3))
					preferAction = 147;
				else {
					preferAction = 28;
					battle.battleEventVars[0] = 3;
				}
			}
			else if (fighter->mp <= 255)
				preferAction = -1;
			else if (battle.turnCount % 2 == 1)
				preferAction = 18;
			else
				preferAction = 19;
		} break;
		
		case 93: {
			int alliesAlive = 0;
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive) continue;
				
				alliesAlive++;
			}
			
			if (alliesAlive == 1) {
				if (fighter->mp >= 97)
					preferAction = 99;
				else
					preferAction = 93;
				break;
			}
			
			int leastHP = 60;
			for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
				
				if (fighter2->hp < leastHP) {
					preferTarget = i;
					preferAction = 97;
					leastHP = fighter2->hp;
				}
			}
			if (preferAction > 0) break;
			
			if (fighter->mp >= 97 && fighter->hp < fighter->hpMax / 3)
				preferAction = 99;
			else if (fighter->mp >= fighter->mpMax / 2)
				preferAction = 98;
			else
				preferAction = 93;
		} break;
		
		case 101: {
			fighter->aiVars[0].i++;
			
			switch (fighter->passiveVars[71].i) {
				case 1:
					if (fighter->mp < 260 && fighter->aiVars[0].i >= 4)
						preferAction = -1;
					else if (battle.turnCount % 4 == 2)
						preferAction = 98;
					else
						preferAction = 99;
					break;
				case 2:
					if (fighter->mp < 250 || fighter->aiVars[0].i == 2) {
						if (fighter->status[FIGHTER_STATUS_STRENGTH] >= 8)
							preferAction = 93;
						else
							preferAction = 134;
					}
					else if (fighter->status[FIGHTER_STATUS_STRENGTH] >= 8 || fighter->aiVars[0].i == 1)
						preferAction = 148;
					else
						preferAction = 116;
					break;
				case 3:
					if (fighter->mp < 120 || fighter->aiVars[0].i == 2) {
						if (fighter->status[FIGHTER_STATUS_STRENGTH] >= 8)
							preferAction = 114;
						else
							preferAction = 134;
						break;
					}
					
					if (fighter->aiVars[0].i % 2 == 1) {
						int mostAtk = 0;
						for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
							Fighter* fighter2 = &battle.fighters[i];
							if (!fighter2->enabled || !fighter2->alive) continue;
							
							if (fighter2->attack > mostAtk) {
								preferTarget = i;
								mostAtk = fighter2->attack;
							}
						}
						
						preferAction = 61;
					}
					else {
						int mostMP = 0;
						for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
							Fighter* fighter2 = &battle.fighters[i];
							if (!fighter2->enabled || !fighter2->alive) continue;
							
							if (fighter2->mp > mostMP) {
								preferTarget = i;
								mostMP = fighter2->mp;
							}
						}
						
						preferAction = 158;
					}
					break;
				case 4:
					if (fighter->mp < 160 || fighter->aiVars[0].i >= 2 && fighter->aiVars[0].i % 3 >= 1)
						preferAction = 157;
					else {
						int mostMP = 0;
						for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
							Fighter* fighter2 = &battle.fighters[i];
							if (!fighter2->enabled || !fighter2->alive) continue;
							
							if (fighter2->mp > mostMP) {
								preferTarget = i;
								mostMP = fighter2->mp;
							}
						}
						
						if (fighter->mp < 112 + (fighter->aiVars[0].i % 2) * 30)
							preferAction = 71;
						else
							preferAction = 149;
					}
					break;
				case 5:
					if (fighter->mp < 100)
						preferAction = 72;
					else
						preferAction = 159;
					break;
				case 6:
					if (fighter->mp < 150 + (fighter->aiVars[0].i == 1) * 150) {
						preferAction = 152;
						break;
					}
					
					int mostRoll = 0;
					for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
						Fighter* fighter2 = &battle.fighters[i];
						if (!fighter2->enabled || !fighter2->alive) continue;
						
						if (fighter2->speedRoll > mostRoll) {
							preferTarget = i;
							mostRoll = fighter2->speedRoll;
						}
						if (fighter2->status[FIGHTER_STATUS_HASTE] >= 15 && fighter->mp >= 64) {
							preferAction = 150;
						}
					}
					if (preferAction > 0) break;
					
					if (fighter->mp >= 64 && (fighter->aiVars[0].i == 3 || Random(1) < 0.375))
						preferAction = 150;
					else
						preferAction = 151;
					break;
				case 7:
					if (fighter->aiVars[0].i % 2 == 1 && fighter->mp >= 75)
						preferAction = 153;
					else if (fighter->mp >= 48)
						preferAction = 145;
					else
						preferAction = 45;
					break;
				case 8:
					if (fighter->mp < 244) {
						if (fighter->hp <= 10)
							preferAction = (fighter->status[FIGHTER_STATUS_CHARGE] < 3) ? 161 : -1;
						else
							preferAction = 163;
					}
					else if (fighter->status[FIGHTER_STATUS_CHARGE] < 3)
						preferAction = 161;
					else
						preferAction = 162;
					break;
			}
		} break;
		
		case 102: {
			if (battle.battleEventVars[0] >= 2) {
				if (fighter->hp < fighter->hpMax / 3 && battle.turnCount % 2 == 1)
					preferAction = 165;
				else if (fighter->mp < 195)
					preferAction = 166;
				else if (battle.turnCount % 3 == 0)
					preferAction = 147;
				else if (battle.turnCount % 3 == 1)
					preferAction = 148;
				else
					preferAction = 164;
			}
			else {
				if (battle.turnCount % 4 == 2 && fighter->mp < fighter->mpMax * 3 / 4)
					preferAction = 166;
				else if (fighter->mp < 240)
					preferAction = 18;
				else if (battle.turnCount % 3 == 0)
					preferAction = 164;
				else
					preferAction = 18;
			}
		} break;
		
		case 104: {
			if (fighter->aiVars[0].i < 5 && fighter->hp <= 300 + fighter->aiVars[0].i * 8) {
				preferAction = 211;
				fighter->aiVars[0].i++;
				battle.battleEventVars[0]++;
				break;
			}
			if (fighter->aiVars[0].i >= 3 && fighter->aiVars[1].i < fighter->aiVars[0].i - 2) {
				preferAction = 212;
				fighter->aiVars[1].i++;
				break;
			}
			
			if (fighter->mp >= 22 + fighter->mpMax * (5 - fighter->aiVars[0].i) / 5)
				preferAction = 37;
			else if (fighter->mp >= -1 + fighter->mpMax * (5 - fighter->aiVars[0].i) / 5)
				preferAction = 49;
			else
				preferAction = 5;
		} break;
		
		case 105: {
			if ((fighter->hp < 225 || !battle.fighters[9].alive) && fighter->mp >= 120 && fighter->aiVars[0].i == 0) {
				preferAction = 172;
				fighter->aiVars[0].i = 1;
			}
			else if (fighter->mp < 150 || ((battle.turnCount == 4 || battle.turnCount == 10) && fighter->mp < fighter->mpMax - 24))
				preferAction = 72;
			else if (battle.turnCount == 3 || battle.turnCount % 5 == 4)
				preferAction = 169;
			else if (battle.turnCount % 5 == 2 && battle.turnCount > 5)
				preferAction = 171;
			else if (battle.turnCount == 2 || (battle.turnCount % 5 == 1 && battle.turnCount > 5))
				preferAction = 170;
			else {
				preferAction = 168;
				fighter->aiVars[1].i++;
			}
		} break;
		
		case 106: {
			if (fighter->hp >= 655) {
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->hp < fighter2->hpMax / 4) {
						preferAction = 175;
						preferTarget = i;
						break;
					}
				}
				
				if (preferAction > 0) break;
			}
			
			if ((fighter->hp < 350 || !battle.fighters[8].alive) && fighter->mp >= 216 - fighter->manaCostReduction && fighter->aiVars[0].i == 0) {
				preferAction = 174;
				fighter->aiVars[0].i = 1;
			}
			else if (fighter->mp < 216 - fighter->manaCostReduction && fighter->hp >= 40)
				preferAction = 163;
			else if (fighter->hp < 655)
				preferAction = 173;
			else if (fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] <= 8)
				preferAction = 142;
			else
				preferAction = 93;
		} break;
		
		case 107: {
			if (fighter->mp >= 837 && fighter->aiVars[0].i == 0 && (fighter->hp < fighter->hpMax / 6 || (fighter->hp < 5000 && battle.fighters[0].status[FIGHTER_STATUS_CHARGE] >= 6))) {
				preferAction = 186;
				fighter->aiVars[0].i = 1;
			}
			else if (fighter->mp >= 400 && fighter->aiVars[0].i == 1) {
				preferAction = 185;
				fighter->aiVars[0].i = 2;
			}
			else if (battle.turnCount == 1)
				preferAction = 19;
			else if (fighter->mp < 900) {
				if (battle.fighters[0].hp < 100 && battle.turnCount % 5 < 4)
					preferAction = 19;
				else
					preferAction = 187;
			}
			else if (battle.turnCount % 5 == 3 || battle.turnCount % 5 == 0 || fighter->status[FIGHTER_STATUS_STRENGTH] >= 100)
				preferAction = 184;
			else if (battle.turnCount % 5 == 2)
				preferAction = 183;
			else if (fighter->mp >= 400 && battle.turnCount % 4 == 3)
				preferAction = 185;
			else
				preferAction = 19;
		} break;
		
		case 108: {
			if (!fighter->movesetDisabled[7]) {
				int averageMP = 0;
				int aliveCount = 0;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					aliveCount++;
					averageMP += fighter2->mp;
				}
				averageMP /= aliveCount;
				
				if (averageMP < 200) {
					preferAction = 197;
					break;
				}
			}
			
			if (fighter->mp >= 140 - fighter->manaCostReduction) {
				int averageHP = 0;
				int aliveCount = 0;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					averageHP += fighter2->hp;
					aliveCount++;
				}
				averageHP /= aliveCount;
				
				if (averageHP < 600 && battle.fighters[10].mp < 349 - battle.fighters[10].manaCostReduction) {
					preferTarget = 10;
					preferAction = 194;
					break;
				}
			}
			
			if (fighter->mp >= 190 - fighter->manaCostReduction && fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] >= 50) {
				int leastMP = 300;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2) continue;
					
					if (fighter2->mp < leastMP && fighter2->hp >= fighter2->hpMax / 4) {
						preferTarget = i;
						preferAction = 194;
						leastMP = fighter2->mp;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (fighter->mp >= 90 - fighter->manaCostReduction) {
				int leastHP = 999999;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->hp < leastHP && fighter2->hp >= fighter2->hpMax / 4 && fighter2->hp < fighter2->hpMax / 2) {
						preferTarget = i;
						preferAction = 165;
						leastHP = fighter2->hp;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (fighter->mp < 51 - fighter->manaCostReduction)
				preferAction = -1;
			else if (fighter->mp < 130 + fighter->manaCostReduction)
				preferAction = 166;
			else if (fighter->status[FIGHTER_STATUS_CHARGE]) {
				if (fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] < 50)
					preferAction = 188;
				else if (fighter->mp >= 298 - fighter->manaCostReduction && fighter->status[FIGHTER_STATUS_STRENGTH] >= 50)
					preferAction = 195;
				else if (fighter->mp < fighter->mpMax / 2)
					preferAction = 166;
				else
					preferAction = 190;
			}
			else if (fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] < 50 || battle.turnCount % 2 == 0)
				preferAction = 188;
			else
				preferAction = 160;
		} break;
		
		case 109: {
			if (fighter->mp >= 90 - fighter->manaCostReduction) {
				int leastHP = 999999;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->hp < leastHP && fighter2->hp >= fighter2->hpMax / 8 && fighter2->hp < fighter2->hpMax / 2) {
						preferTarget = i;
						preferAction = 165;
						leastHP = fighter2->hp;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (fighter->aiVars[0].i >= 2) {
				if (fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] < 50)
					preferAction = 188;
				else
					preferAction = 196;
			}
			else if (fighter->mp < 51 - fighter->manaCostReduction)
				preferAction = -1;
			else if (fighter->mp < 169 + fighter->manaCostReduction)
				preferAction = 166;
			else if (fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] < 50 || (battle.turnCount % 2 == 0 && battle.fighters[11].alive))
				preferAction = 188;
			else if (fighter->mp < 265 - fighter->manaCostReduction || battle.fighters[0].mp > battle.fighters[0].mpMax / 2)
				preferAction = 126;
			else
				preferAction = 193;
		} break;
		
		case 110: {
			if (fighter->mp >= 140 - fighter->manaCostReduction && fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] >= 50) {
				int leastMP = 335;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive || fighter == fighter2 || i == 8) continue;
					
					if (fighter2->mp < leastMP) {
						preferTarget = i;
						preferAction = 194;
						leastMP = fighter2->mp;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (fighter->mp >= 249 - fighter->manaCostReduction) {
				int averageHP = 0;
				int aliveCount = 0;
				for (int i = fighter->side * 8; i < fighter->side * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					averageHP += fighter2->hp;
					aliveCount++;
				}
				averageHP /= aliveCount;
				
				if (averageHP < 600) {
					preferAction = 189;
					break;
				}
			}
			
			if (fighter->mp >= 5 - fighter->manaCostReduction) {
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->status[FIGHTER_STATUS_CHARGE] >= 2) {
						preferTarget = i;
						preferAction = 82;
						break;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (fighter->mp < 51 - fighter->manaCostReduction)
				preferAction = -1;
			else if (fighter->mp < 169 + fighter->manaCostReduction)
				preferAction = 166;
			else if (fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] < 50 || fighter->mp < 150 - fighter->manaCostReduction)
				preferAction = 188;
			else
				preferAction = 198;
		} break;
		
		case 111: {
			if (fighter->mp >= 5 - fighter->manaCostReduction) {
				for (int i = (1 - fighter->side) * 8; i < (1 - fighter->side) * 8 + 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					if (fighter2->status[FIGHTER_STATUS_CHARGE] >= 6) {
						preferTarget = i;
						preferAction = 82;
						break;
					}
				}
				
				if (preferTarget >= 0) break;
			}
			
			if (fighter->mp < 51 - fighter->manaCostReduction)
				preferAction = -1;
			else if (fighter->mp < 130 + fighter->manaCostReduction)
				preferAction = 166;
			else if (fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] < 50)
				preferAction = 188;
			else if (fighter->mp < 265 - fighter->manaCostReduction || battle.fighters[0].mp > battle.fighters[0].mpMax / 2 || (battle.turnCount % 2 == 1 && battle.fighters[9].alive && battle.fighters[9].aiVars[0].i < 2)) {
				if (battle.fighters[0].hp >= 1000)
					preferAction = 188;
				else if (fighter->status[FIGHTER_STATUS_CHARGE])
					preferAction = 195;
				else
					preferAction = 76;
			}
			else
				preferAction = 193;
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
		if (fighter->mp < actionData[fighter->moveset[i]].cost - fighter->manaCostReduction) continue;
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
		
		case 93: case 94: case 95: case 96: case 97: case 98: case 99: case 100: case 101: {
			if (fighter->readyTimer >= 8) {
				attack = 1;
			}
		} break;
		
		case 102: {
			if (battle.battleEventVars[0] < 2) {
				if (fighter->aiVars[0].i < 7 && Random(1) < 0.1) {
					attack = 1;
				}
				break;
			}
			if (Random(1) < 0.25 || fighter->readyTimer >= 5) {
				attack = 1;
			}
		} break;
		
		case 104: {
			if (fighter->actionId == 212) {
				if (fighter->readyTimer >= 120 || (fighter->aiVars[0].i >= 5 && fighter->readyTimer >= 11)) {
					attack = 1;
				}
				break;
			}
			if (Random(1) < 0.1) {
				attack = 1;
			}
		} break;
		
		case 105: {
			if (fighter->actionId == 168) {
				if (fighter->aiVars[1].i == 1) {
					if (fighter->actionAttacks < 3) {
						if (fighter->totalAttackTimer / 2 % 4 == 1 && (fighter->actionAttacks >= 1 || fighter->readyTimer >= 15)) {
							attack = 1;
						}
					}
					else if (fighter->actionAttacks < 6) {
						if (fighter->totalAttackTimer / 2 % 4 == 3 && (fighter->actionAttacks >= 4 || fighter->readyTimer >= 30)) {
							attack = 1;
						}
					}
					else if (fighter->actionAttacks < 9) {
						if (fighter->totalAttackTimer / 2 % 4 == 1 && (fighter->actionAttacks >= 7 || fighter->readyTimer >= 25)) {
							attack = 1;
						}
					}
					else if (fighter->actionAttacks < 12) {
						if (fighter->totalAttackTimer / 2 % 4 == 3 && (fighter->actionAttacks >= 10 || fighter->readyTimer >= 10)) {
							attack = 1;
						}
					}
					else {
						if (fighter->totalAttackTimer / 2 % 4 == 0 && (fighter->actionAttacks >= 13 || fighter->readyTimer >= 20)) {
							attack = 1;
						}
					}
					break;
				}
				else if (fighter->aiVars[1].i == 2) {
					if (fighter->totalAttackTimer % 22 == 0) {
						attack = 1;
					}
					break;
				}
				else if (fighter->aiVars[1].i == 3) {
					if (fighter->totalAttackTimer / 2 % 4 == 0) {
						attack = 1;
					}
					break;
				}
			}
			if (Random(1) < 0.1) {
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
			if (attacker->totalAttackTimer == 9 && Fighter_AI_Random(fighter) < 0.1) {
				blocked = 1;
			}
			else if (attacker->totalAttackTimer % 60 == 19 && Fighter_AI_Random(fighter) < 0.25) {
				blocked = 1;
			}
		} break;
		
		case 3: {
			if ((attacker->readyTimer >= 4 || attacker->attackTimer >= 0) && Fighter_AI_Random(fighter) < 0.25) {
				blocked = 1;
			}
		} break;
		
		case 4: {
			if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 15 && Fighter_AI_Random(fighter) < 0.1) {
				blocked = 1;
			}
		} break;
		
		case 5: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Fighter_AI_Random(fighter) < 0.75))) {
				blocked = 1;
			}
		} break;
		
		case 6: {
			if (attacker->actionId == 92) {
				if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Fighter_AI_Random(fighter) < 0.99) {
					blocked = 1;
				}
				break;
			}
			if (battle.turnCount % 2 == 1 && fighter->hp >= fighter->hpMax / 2) {
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Fighter_AI_Random(fighter) < 0.15) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Fighter_AI_Random(fighter) < 0.5))) {
					blocked = 1;
				}
				break;
			}
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 2 && Fighter_AI_Random(fighter) < 0.5) || (attacker->attackAnimTimer > attacker->attackAnimTime && Fighter_AI_Random(fighter) < 0.92))) {
				blocked = 1;
			}
		} break;
		
		case 9: {
			if (attacker->readyTimer >= 18 && Fighter_AI_Random(fighter) < 0.15) {
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
				if (attacker->totalAttackTimer % 60 == 50 && Fighter_AI_Random(fighter) < 0.3) {
					blocked = 1;
				}
			}
			else if (attacker->headId == 4) {
				if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 18 && Fighter_AI_Random(fighter) < 0.5) {
					blocked = 1;
				}
			}
			else {
				if ((attacker->totalAttackTimer == 40 && Fighter_AI_Random(fighter) < 0.2) || (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 16 && Fighter_AI_Random(fighter) < 0.15)) {
					blocked = 1;
				}
			}
		} break;
		
		case 38: {
			if (fighter->hp < fighter->hpMax / 4) {
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Fighter_AI_Random(fighter) < 0.5))) {
					blocked = 1;
				}
			}
			else {
				if (Fighter_AI_Random(fighter) < 0.05) {
					blocked = 1;
				}
			}
		} break;
		
		case 46: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Fighter_AI_Random(fighter) < 0.4))) {
				blocked = 1;
			}
		} break;
		
		case 51: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Fighter_AI_Random(fighter) < 0.4))) {
				blocked = 1;
			}
		} break;
		
		case 55: {
			
		} break;
		
		case 64: {
			if (attacker->hp < attacker->hpMax / 6) {
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && (Fighter_AI_Random(fighter) < 0.1 || battle.turnCount % 5 == 2)) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Fighter_AI_Random(fighter) < 0.75))) {
					blocked = 1;
				}
			}
			else if (attacker->hp < attacker->hpMax * 3 / 4) {
				if (attacker->totalAttackTimer == 12 && battle.turnCount % 3 < 2) {
					blocked = 1;
				}
				else if (attacker->hp < attacker->hpMax / 3) {
					if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Fighter_AI_Random(fighter) < 0.75))) {
						blocked = 1;
					}
				}
				else if (attacker->totalAttackTimer % 40 == 14 && Fighter_AI_Random(fighter) < 0.5) {
					blocked = 1;
				}
			}
		} break;
		
		case 72: {
			
		} break;
		
		case 73: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Fighter_AI_Random(fighter) < 0.5))) {
				blocked = 1;
			}
		} break;
		
		case 86: {
			if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 8 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Fighter_AI_Random(fighter) < 0.9))) {
				blocked = 1;
			}
		} break;
		
		case 87: {
			if (battle.turnCount <= 2 || attacker->hp >= attacker->hpMax) break;
			if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime && Fighter_AI_Random(fighter) < 0.28) {
				blocked = 1;
			}
		} break;
		
		case 89: {
			if (battle.turnCount == 1) {
				if (attacker->readyTimer == 1 || (attacker->attackAnimTimer == 1 && Fighter_AI_Random(fighter) < 0.5)) {
					blocked = 1;
				}
				break;
			}
			if (fighter->hp <= fighter->hpMax * 3 / 4) {
				if (fighter->aiTakeAttackPredictTime >= 0 && (fighter->aiTakeAttackPredictTime < 30 || attacker->readyTimer >= 0) && (fighter->aiTakeAttackCount - fighter->aiBlockCount <= 4 || fighter->aiBlockCount % 4 == 0)) {
					if ((attacker->readyTimer >= fighter->aiTakeAttackPredictTime - 5 && Fighter_AI_Random(fighter) < 0.05) || attacker->readyTimer == fighter->aiTakeAttackPredictTime + 15 || attacker->attackAnimTimer == fighter->aiTakeAttackPredictTime) {
						blocked = 1;
					}
					break;
				}
				if (attacker->attackTimer >= 0 && attacker->attackAnimTimer > attacker->attackAnimTime - 6 && Fighter_AI_Random(fighter) < 0.17) {
					blocked = 1;
				}
				break;
			}
			if (Fighter_AI_Random(fighter) < 0.05) {
				blocked = 1;
			}
		} break;
		
		case 90: {
			if (attacker->attackAnimTime >= 9 - attacker->aiDefenseScore / 8) {
				if (attacker->aiDefenseScore <= -6) {
					if (attacker->readyTimer == 1) {
						blocked = 1;
					}
					break;
				}
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer >= attacker->attackAnimTime - 6 && attacker->attackAnimTimer <= attacker->attackAnimTime - 5 && Fighter_AI_Random(fighter) < 0.5) || (attacker->attackAnimTimer == attacker->attackAnimTime - 4 && fighter->aiDefenseScore > 0) || (attacker->attackAnimTimer == attacker->attackAnimTime - 1 && Fighter_AI_Random(fighter) < 0.75))) {
					blocked = 1;
				}
				break;
			}
			if (Fighter_AI_Random(fighter) < 0.1 || attacker->readyTimer == 1) {
				blocked = 1;
			}
		} break;
		
		case 91: {
			
		} break;
		
		case 92: case 105: case 108: case 109: case 110: case 111: {
			if (attacker->attackTimer >= 0 && (attacker->attackAnimTimer > attacker->attackAnimTime + 1 || attacker->attackTimer >= 3)) {
				blocked = 1;
			}
		} break;
		
		case 93: case 94: case 95: case 96: case 97: case 98: case 99: case 100: case 101: {
			
		} break;
		
		case 102: {
			if (battle.battleEventVars[0] >= 2) {
				if (attacker->attackTimer >= 0 && (attacker->attackAnimTimer > attacker->attackAnimTime + 1 || attacker->attackTimer >= 3)) {
					blocked = 1;
				}
			}
		} break;
		
		case 103: {
			
		} break;
		
		case 104: {
			if (attacker->totalAttackTimer == 5 && Fighter_AI_Random(fighter) < 0.75) {
				blocked = 1;
			}
			else if (attacker->totalAttackTimer % 10 == 6 && Fighter_AI_Random(fighter) < 0.75) {
				blocked = 1;
			}
			else if (attacker->totalAttackTimer == 7) {
				blocked = 1;
			}
		} break;
		
		case 106: {
			if (fighter->hp < fighter->hpMax / 2) {
				if (attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 9 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 3 && Fighter_AI_Random(fighter) < 0.4))) {
					blocked = 1;
				}
				break;
			}
			
			if (fighter->aiTakeAttackPredictTime >= 0 && (fighter->aiTakeAttackPredictTime < 30 || attacker->readyTimer >= 0)) {
				if ((attacker->readyTimer >= fighter->aiTakeAttackPredictTime - 15 && Fighter_AI_Random(fighter) < 0.05) || attacker->readyTimer == fighter->aiTakeAttackPredictTime + 15 || attacker->attackAnimTimer == fighter->aiTakeAttackPredictTime) {
					blocked = 1;
				}
				break;
			}
			if (Fighter_AI_Random(fighter) < 0.05) {
				blocked = 1;
			}
		} break;
		
		case 107: {
			if (attacker->attackTimer >= 0 && (attacker->attackAnimTimer > attacker->attackAnimTime + 1 || attacker->attackTimer >= 3)) {
				blocked = 1;
			}
		} break;
		
		case 191: case 192: {
			if (battle.battleEventVars[0] == 0 && attacker->attackTimer >= 0 && ((attacker->attackAnimTimer > attacker->attackAnimTime - 7 && Fighter_AI_Random(fighter) < 0.1) || (attacker->attackAnimTimer > attacker->attackAnimTime - 1 && Fighter_AI_Random(fighter) < 0.9))) {
				blocked = 1;
			}
		} break;
		
		default: {
			if (fighter->aiTakeAttackPredictTime >= 0 && (fighter->aiTakeAttackPredictTime < 30 || attacker->readyTimer >= 0)) {
				if ((attacker->readyTimer >= fighter->aiTakeAttackPredictTime - 15 && Fighter_AI_Random(fighter) < 0.05) || attacker->readyTimer == fighter->aiTakeAttackPredictTime + 15 || attacker->attackAnimTimer == fighter->aiTakeAttackPredictTime) {
					blocked = 1;
				}
				break;
			}
			if (Fighter_AI_Random(fighter) < 0.05) {
				blocked = 1;
			}
		} break;
	}
	
	return blocked;
}

float Fighter_AI_Random(Fighter* fighter) {
	float xMin = 0;
	float xMax = 1.f + (float)Max(-100, Min(100, fighter->aiDefenseScore)) / 100.f;
	if (fighter->aiDefenseScore > 50) {
		xMin = (float)(fighter->aiDefenseScore - 50) / 100.f;
	}
	return Random_Range(xMin, xMax);
}
