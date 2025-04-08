#include "generic.h"
#include "battlesystem.h"
#include "overworld.h"
#include "sprites.h"
#include "audio.h"
#include "battlebody.h"
#include "fighters.h"
#include "action.h"
#include "passives.h"
#include "armor.h"
#include "dialog.h"
#include "party.h"
#include "profile.h"
#include "items.h"
#include "ai.h"

Battle battle;

StatusEffect statusEffectData[32];



void Fighter_TakeDamage(Fighter* fighter, Fighter* attacker, int damage, unsigned int flags) {
	if (attacker == NULL) {
		for (int i = 0; i < fighter->passiveCount; i++) Passive_OnTakeDamage(fighter->passives[i], fighter, NULL, &damage, &flags);
	}
	if (damage < 0) return;
	
	if (!fighter->statusOverride[FIGHTER_STATUS_ABSORPTION] && fighter->status[FIGHTER_STATUS_ABSORPTION] > 0) {
		fighter->status[FIGHTER_STATUS_ABSORPTION] -= damage;
		if (fighter->status[FIGHTER_STATUS_ABSORPTION] < 0) {
			damage = -fighter->status[FIGHTER_STATUS_ABSORPTION];
			fighter->status[FIGHTER_STATUS_ABSORPTION] = 0;
		}
		else {
			damage = 0;
		}
	}
	
	fighter->hp -= damage;
	if (fighter->hp < 0) fighter->hp = 0;
	
	fighter->blockTimer = -1;
	fighter->blockCooldownTimer = -1;
	
	Fighter_CheckDefeat(fighter, flags);
}

void Fighter_CheckDefeat(Fighter* fighter, unsigned int flags) {
	if (fighter->hp <= 0) {
		if ((flags & DAMAGE_FLAG_LETHAL) || fighter->status[FIGHTER_STATUS_SERIOUS]) {
			fighter->fatalInjury = true;
		}
		fighter->alive = 0;
		Fighter_ClearAllStatus(fighter);
		
		if (fighter->x != fighter->xStart || fighter->y != fighter->yStart) {
			Fighter_MoveToStart(fighter);
		}
	}
}

void Fighter_DealDamage(Fighter* fighter, Fighter* target, int damage, unsigned int flags) {
	int damageOriginal = damage;
	fighter->actionInflictedDamage = 0;
	if (damage > -99999) {
		if (target->status[FIGHTER_STATUS_GUARD]) damage -= target->status[FIGHTER_STATUS_GUARD] - 1;
		
		for (int i = 0; i < fighter->passiveCount; i++) Passive_OnDealDamage(fighter->passives[i], fighter, target, &damage, &flags);
		for (int i = 0; i < target->passiveCount; i++) Passive_OnTakeDamage(target->passives[i], target, fighter, &damage, &flags);
		
		if (damage > -99999 && damage < 0) damage = 0;
	}
	
	if (damage > damageOriginal && (flags & DAMAGE_FLAG_CAPPED)) {
		damage = damageOriginal;
	}
	
	if (target->status[FIGHTER_STATUS_COUNTER] && fighter->counterTargetId < 0) {
		target->counterTargetId = fighter->id;
	}
	if (target->status[FIGHTER_STATUS_DEFLECT]) {
		int points = target->status[FIGHTER_STATUS_DEFLECT] + target->defense + target->status[FIGHTER_STATUS_ENDURANCE] - target->status[FIGHTER_STATUS_DISARM];
		if (points > 0) {
			fighter->mp -= points;
			if (fighter->mp < 0) fighter->mp = 0;
			Audio_PlaySoundInterrupt(SND_deflect);
			snprintf(game.textBuffer, 16, "%d", points);
			Battle_CreateLabel(6, game.textBuffer, fighter->x, fighter->y - 32);
			Battle_CreateLabel(6, "DEFLECT", fighter->x, fighter->y - 56);
			target->status[FIGHTER_STATUS_DEFLECT]--;
		}
	}
	
	if (((target->blockTimer >= 0 && target->blockTimer < target->dodgeTime) || target->status[FIGHTER_STATUS_EVADE]) && (flags & DAMAGE_FLAG_DODGABLE) && !target->status[FIGHTER_STATUS_ANTIGUARD]) {
		damage = 0;
		target->state = FIGHTER_STATE_ATTACK1;
		Audio_PlaySoundInterrupt(SND_dodge);
		
		if (!target->status[FIGHTER_STATUS_EVADE]) {
			Battle_CreateLabel(1, "DODGE", target->x, target->y - 32);
		}
		target->aiDodgeCount++;
		if (target->aiDefenseScore <= -80)
			target->aiDefenseScore = -40;
		target->aiDefenseScore += 25;
	}
	else if (damage < 0) {
		
	}
	else if (damage == 0) {
		Battle_CreateLabel(0, "0", target->x, target->y - 32);
	}
	else if (((target->blockTimer >= 0 && target->blockTimer < target->blockTime) || target->status[FIGHTER_STATUS_GUARD]) && (flags & DAMAGE_FLAG_BLOCKABLE) && !target->status[FIGHTER_STATUS_ANTIGUARD]) {
		damage /= 2;
		target->state = FIGHTER_STATE_BLOCK;
		target->flinchTicks = 18;
		Audio_PlaySoundInterrupt(SND_hit1);
		
		snprintf(game.textBuffer, 16, "%d", damage);
		Battle_CreateLabel(0, game.textBuffer, target->x, target->y - 32);
		if (!target->status[FIGHTER_STATUS_GUARD]) {
			Battle_CreateLabel(2, "BLOCK", target->x, target->y - 56);
		}
		target->aiBlockCount++;
		if (target->aiDefenseScore <= -80)
			target->aiDefenseScore = -40;
		target->aiDefenseScore += 12;
	}
	else if ((flags & DAMAGE_FLAG_CRITICAL) || (target->blockTimer >= 0 && (flags & DAMAGE_FLAG_BLOCKABLE))) {
		damage *= 3;
		damage += 1;
		damage /= 2;
		target->state = FIGHTER_STATE_HURT;
		target->flinchTicks = 24;
		Audio_PlaySoundInterrupt(SND_hit3);
		
		snprintf(game.textBuffer, 16, "%d", damage);
		Battle_CreateLabel(0, game.textBuffer, target->x, target->y - 32);
		Battle_CreateLabel(3, "CRITICAL", target->x, target->y - 56);
		target->aiBlockCritCount++;
		if (target->aiDefenseScore >= 80)
			target->aiDefenseScore = 40;
		target->aiDefenseScore -= 27;
	}
	else if (damage > 0) {
		target->state = FIGHTER_STATE_HURT;
		target->flinchTicks = 21;
		Audio_PlaySoundInterrupt(SND_hit2);
		
		snprintf(game.textBuffer, 16, "%d", damage);
		Battle_CreateLabel(0, game.textBuffer, target->x, target->y - 32);
		if (target->aiDefenseScore >= 80)
			target->aiDefenseScore = 40;
		target->aiDefenseScore -= 12;
	}
	
	target->aiTakeAttackCount++;
	
	if (damage < 0) return;
	
	Fighter_TakeDamage(target, fighter, damage, flags);
	fighter->actionInflictedDamage = damage;
	if (fighter->status[FIGHTER_STATUS_HYPERENERGIZER]) {
		Audio_PlaySoundInterrupt(SND_explode);
		Battle_ShakeScreen(20);
	}
}

void Fighter_InflictStatus(Fighter* fighter, Fighter* target, int statusId, int count, bool instant) {
	for (int i = 0; i < target->passiveCount; i++) Passive_OnTakeStatus(target->passives[i], target, fighter, &statusId, &count, 0);
	Fighter_GainStatus(target, statusId, count, instant);
}

void Fighter_InflictStatusNextTurn(Fighter* fighter, Fighter* target, int statusId, int count) {
	for (int i = 0; i < target->passiveCount; i++) Passive_OnTakeStatus(target->passives[i], target, fighter, &statusId, &count, 0);
	Fighter_GainStatusNextTurn(target, statusId, count);
}

void Fighter_InflictStatusDodgable(Fighter* fighter, Fighter* target, int statusId, int count, bool instant) {
	if ((target->blockTimer >= 0 && target->blockTimer < target->dodgeTime) || target->status[FIGHTER_STATUS_EVADE]) {
		return;
	}
	
	for (int i = 0; i < target->passiveCount; i++) Passive_OnTakeStatus(target->passives[i], target, fighter, &statusId, &count, DAMAGE_FLAG_DODGABLE | DAMAGE_FLAG_BLOCKABLE);
	Fighter_GainStatus(target, statusId, count, instant);
}



void Fighter_OnAttackSwing(Fighter* fighter) {
	if (fighter->status[FIGHTER_STATUS_BLEED] > 0) {
		if (fighter->hp <= fighter->status[FIGHTER_STATUS_BLEED])
			Fighter_TakeDamage(fighter, NULL, fighter->hp - 1, 0);
		else
			Fighter_TakeDamage(fighter, NULL, fighter->status[FIGHTER_STATUS_BLEED], 0);
		fighter->status[FIGHTER_STATUS_BLEED] = fighter->status[FIGHTER_STATUS_BLEED] * 2 / 3;
		Battle_CreateSpark(3, fighter->x, fighter->y - 24, 0);
		Audio_PlaySoundInterrupt(SND_poison);
	}
	
	if (battle.target) {
		if (battle.target->aiTakeAttackCount == 1) {
			battle.target->aiTakeAttackPredictTime = battle.target->readyTimer;
		}
		else if (battle.target->aiTakeAttackCount > 1) {
			if (battle.target->aiDefenseScore > 40) {
				battle.target->aiTakeAttackPredictTime += (battle.target->readyTimer - battle.target->aiTakeAttackPredictTime) / 4;
			}
			else if (battle.target->aiDefenseScore > 0) {
				battle.target->aiTakeAttackPredictTime += (battle.target->readyTimer - battle.target->aiTakeAttackPredictTime) / 2;
			}
			else if (battle.target->aiDefenseScore > -40) {
				battle.target->aiTakeAttackPredictTime += (battle.target->readyTimer - battle.target->aiTakeAttackPredictTime) * 2 / 3;
			}
			else {
				battle.target->aiTakeAttackPredictTime += Max(0, (battle.target->readyTimer - battle.target->aiTakeAttackPredictTime) + Random_IRange(-60, 60));
			}
		}
	}
}

void Fighter_PrepareToBlock(Fighter* fighter) {
	Fighter_SwitchToDefaultState(fighter);
	fighter->blockTimer = -1;
	fighter->blockCooldownTimer = -1;
	
	int speedDifference = fighter->speedRoll - battle.attacker->speedRoll;
	
	fighter->criticalTime = 20;
	if (speedDifference >= 40) {
		fighter->blockTime = 24;
		fighter->dodgeTime = 6;
	}
	else if (speedDifference >= 30) {
		fighter->blockTime = 22;
		fighter->dodgeTime = 5;
	}
	else if (speedDifference >= 20) {
		fighter->blockTime = 20;
		fighter->dodgeTime = 4;
	}
	else if (speedDifference >= 10) {
		fighter->blockTime = 18;
		fighter->dodgeTime = 3;
	}
	else if (speedDifference > -10) {
		fighter->blockTime = 16;
		fighter->dodgeTime = 2;
	}
	else if (speedDifference > -20) {
		fighter->blockTime = 14;
		fighter->dodgeTime = 2;
	}
	else if (speedDifference > -30) {
		fighter->blockTime = 12;
		fighter->dodgeTime = 0;
	}
	else if (speedDifference > -40) {
		fighter->blockTime = 10;
		fighter->dodgeTime = 0;
	}
	else {
		fighter->blockTime = 8;
		fighter->dodgeTime = 0;
	}
	
	if (fighter->criticalTime < fighter->blockTime)
		fighter->criticalTime = fighter->blockTime;
}

void Fighter_UpdateBlock(Fighter* fighter) {
	if (fighter->blockTimer >= 0) {
		fighter->blockTimer++;
		
		if (fighter->blockTimer == fighter->blockTime) {
			Fighter_SwitchToDefaultState(fighter);
		}
		if (fighter->blockTimer >= fighter->criticalTime) {
			fighter->blockTimer = -1;
		}
	}
	if (fighter->blockCooldownTimer >= 0) {
		fighter->blockCooldownTimer++;
		
		if (fighter->blockCooldownTimer >= 60) {
			fighter->blockCooldownTimer = -1;
		}
	}
}

void Fighter_MoveTo(Fighter* fighter, float x, float y, float speed, int facing) {
	fighter->moveTarget.enabled = true;
	fighter->moveTarget.x = x;
	fighter->moveTarget.y = y;
	fighter->moveTarget.speed = speed;
	fighter->moveTarget.facing = facing;
}

void Fighter_MoveToStart(Fighter* fighter) {
	fighter->moveTarget.enabled = true;
	fighter->moveTarget.x = fighter->xStart;
	fighter->moveTarget.y = fighter->yStart;
	fighter->moveTarget.speed = 8;
	fighter->moveTarget.facing = 1 - fighter->side * 2;
}

void Fighter_SwitchToDefaultState(Fighter* fighter) {
	if (!fighter->alive)
		fighter->state = FIGHTER_STATE_DOWN;
	else if (fighter->status[FIGHTER_STATUS_WEAPONSEARCH] > 0)
		fighter->state = FIGHTER_STATE_SPECIAL1;
	else if (fighter->status[FIGHTER_STATUS_COUNTER] > 0)
		fighter->state = FIGHTER_STATE_ATTACK1;
	else if (fighter->status[FIGHTER_STATUS_GUARD] > 0)
		fighter->state = FIGHTER_STATE_BLOCK;
	else
		fighter->state = FIGHTER_STATE_IDLE;
}



void Fighter_HealHP(Fighter* fighter, int amount) {
	if (amount == 0) return;
	
	if (!fighter->status[FIGHTER_STATUS_ANTIREGEN]) {
		fighter->hp += amount;
		if (fighter->hp >= fighter->hpMax) fighter->hp = fighter->hpMax;
		
		Audio_PlaySoundInterrupt(SND_heal);
	}
	
	fighter->storeHealedHP += amount;
}

void Fighter_HealMP(Fighter* fighter, int amount) {
	if (amount == 0) return;
	
	fighter->mp += amount;
	if (fighter->mp >= fighter->mpMax) fighter->mp = fighter->mpMax;
	
	Audio_PlaySoundInterrupt(SND_mana);
	
	fighter->storeHealedMP += amount;
}

void Fighter_GainStatus(Fighter* fighter, int statusId, int count, bool instant) {
	if (statusId == FIGHTER_STATUS_FLOWER) {
		Audio_PlaySoundInterrupt(SND_flower2);
	}
	
	if (statusId == FIGHTER_STATUS_MANADISCOUNT)
		fighter->status[statusId] = count;
	else if (instant || statusEffectData[statusId].instantByDefault)
		fighter->status[statusId] += count;
	else
		fighter->statusNext[statusId] += count;
}

void Fighter_GainStatusNextTurn(Fighter* fighter, int statusId, int count) {
	if (statusId == FIGHTER_STATUS_MANADISCOUNT)
		fighter->status[statusId] = count;
	else
		fighter->statusNext[statusId] += count;
}

void Fighter_ClearAllStatus(Fighter* fighter) {
	for (int i = 0; i < 32; i++) {
		if (i == FIGHTER_STATUS_SERIOUS) continue;
		fighter->status[i] = 0;
		fighter->statusNext[i] = 0;
	}
}

void Fighter_EnableAction(Fighter* fighter, int actionId) {
	for (int i = 0; i < fighter->movesetCount; i++) {
		if (fighter->moveset[i] == actionId) {
			fighter->movesetDisabled[i] = 0;
		}
	}
}

void Fighter_DisableAction(Fighter* fighter, int actionId) {
	for (int i = 0; i < fighter->movesetCount; i++) {
		if (fighter->moveset[i] == actionId) {
			fighter->movesetDisabled[i] = 1;
		}
	}
}

void Fighter_DisableActionPermamently(Fighter* fighter, int actionId) {
	for (int i = 0; i < fighter->movesetCount; i++) {
		if (fighter->moveset[i] == actionId) {
			fighter->movesetDisabled[i] = 2;
		}
	}
}



void LoadStatusEffectData() {
	StatusEffect* effect;
	
	for (int i = 0; i < 32; i++) {
		statusEffectData[i].type = STATUS_TYPE_NEUTRAL;
	}
	
	
	
	effect = &statusEffectData[0];
	SetString(effect->name, "Strength");
	SetString(effect->desc, "More ATK");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_POSITIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[1];
	SetString(effect->name, "Feeble");
	SetString(effect->desc, "Less ATK");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[2];
	SetString(effect->name, "Endurance");
	SetString(effect->desc, "More DEF");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_POSITIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[3];
	SetString(effect->name, "Disarm");
	SetString(effect->desc, "Less DEF");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[4];
	SetString(effect->name, "Haste");
	SetString(effect->desc, "More SPD");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_POSITIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[5];
	SetString(effect->name, "Bind");
	SetString(effect->desc, "Less SPD");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[6];
	SetString(effect->name, "Burn");
	SetString(effect->desc, "DMG every turn");
	effect->visible = true;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[7];
	SetString(effect->name, "Bleed");
	SetString(effect->desc, "DMG on attack");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[8];
	SetString(effect->name, "Guard");
	SetString(effect->desc, "Block damage");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = true;
	
	effect = &statusEffectData[9];
	SetString(effect->name, "Counter");
	SetString(effect->desc, "Counter attacks");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = true;
	
	effect = &statusEffectData[10];
	SetString(effect->name, "Paralysis");
	SetString(effect->desc, "Less ATK & SPD");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[11];
	SetString(effect->name, "Poison");
	SetString(effect->desc, "Drains HP & MP");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[12];
	SetString(effect->name, "Timed Bomb");
	SetString(effect->desc, "Explodes");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[13];
	SetString(effect->name, "Anti-Guard");
	SetString(effect->desc, "No blocking");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = false;
	
	effect = &statusEffectData[14];
	SetString(effect->name, "Immobile");
	SetString(effect->desc, "Can't act");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = false;
	
	effect = &statusEffectData[15];
	SetString(effect->name, "Chill");
	SetString(effect->desc, "Drains MP & SPD");
	effect->visible = true;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[16];
	SetString(effect->name, "Flower");
	SetString(effect->desc, "Drains MP");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEGATIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[17];
	SetString(effect->name, "Charge");
	SetString(effect->desc, "Used by skills");
	effect->visible = true;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_POSITIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[18];
	SetString(effect->name, "Serious");
	SetString(effect->desc, "Die on defeat");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = false;
	
	effect = &statusEffectData[19];
	SetString(effect->name, "Hyperenergizer");
	SetString(effect->desc, "");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = false;
	
	effect = &statusEffectData[20];
	SetString(effect->name, "Searching");
	SetString(effect->desc, "");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = false;
	
	effect = &statusEffectData[21];
	SetString(effect->name, "Mana Discount");
	SetString(effect->desc, "");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = true;
	
	effect = &statusEffectData[22];
	SetString(effect->name, "ATK Multiplier");
	SetString(effect->desc, "");
	effect->visible = false;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = true;
	
	effect = &statusEffectData[23];
	SetString(effect->name, "Evade");
	SetString(effect->desc, "Dodge attacks");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = true;
	
	effect = &statusEffectData[24];
	SetString(effect->name, "Deflect");
	SetString(effect->desc, "Deflect DMG");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = true;
	
	effect = &statusEffectData[25];
	SetString(effect->name, "Absorption");
	SetString(effect->desc, "Extra HP");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_POSITIVE;
	effect->stackable = true;
	
	effect = &statusEffectData[26];
	SetString(effect->name, "Mana Perma Discount");
	SetString(effect->desc, "");
	effect->visible = false;
	effect->instantByDefault = true;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = true;
	
	effect = &statusEffectData[27];
	SetString(effect->name, "Anti-Regen");
	SetString(effect->desc, "No HP recover");
	effect->visible = true;
	effect->instantByDefault = false;
	effect->type = STATUS_TYPE_NEUTRAL;
	effect->stackable = false;
}



void Battle_Init() {
	profileBuffer = profile;
	for (int i = 0; i < 16; i++) {
		battle.fighters[i].enabled = 0;
		battle.fighters[i].id = i;
	}
	
	battle.gameover = false;
	battle.retry = false;
	battle.loadLastSave = false;
	battle.fleeing = false;
	battle.everythingButSkillsDisabled = false;
	battle.state = BATTLE_STATE_START;
	battle.timer = 0;
	battle.globalTimer = 0;
	battle.shakeTimer = 0;
	battle.turnCount = 0;
	battle.turn = 0;
	battle.attacker = NULL;
	battle.target = NULL;
	battle.gameOverDisabled = false;
	battle.turnStartFatalInjury = false;
	
	battle.camera.x = 320;
	battle.camera.y = 240;
	battle.camera.zoom = 1;
	
	battle.labelCounter = 0;
	for (int i = 0; i < 16; i++) {
		battle.label[i].timer = -1;
	}
	battle.sparkCounter = 0;
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		battle.sparks[i].id = 0;
	}
	
	for (int i = 0; i < 5; i++) {
		if (profile.party[i] < 0) continue;
		
		Battle_CreateFighter(profile.party[i] + 1, 0);
	}
	
	for (int i = 0; i < 4; i++) {
		battle.battleEventVars[i] = 0;
	}
	
	BattleEncounter* encounter = &battleEncounterData[battle.encounter];
	for (int i = 0; i < 8; i++) {
		if (encounter->fighterIds[i] == 0) continue;
		Battle_CreateFighter(encounter->fighterIds[i], 1);
	}
	
	battle.musicId = encounter->musicId;
	if (battle.musicId == MUS_lbpre && profile.flags[FLAG_ALONE_PLOT] >= 20) {
		battle.musicId = MUS_unnamed28;
	}
	
	if (encounter->backgroundId == 0)
		battle.backgroundId = profile.flags[FLAG_DEFAULT_BATTLE_BG];
	else
		battle.backgroundId = encounter->backgroundId;
	
	if (battle.canFlee) {
		for (int i = 8; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			if ((i == 8 && battle.encounterVars[0].i == 1) || (i != 8 && Random(1) < 0.5)) {
				switch (fighter->headId) {
					case 11: fighter->headId = 26; break;
					case 17: fighter->headId = 18; break;
					case 27: fighter->headId = 28; break;
					case 33: fighter->headId = 45; break;
					case 37: fighter->headId = 63; break;
					case 72: fighter->headId = 73; break;
				}
			}
			
			if (i != 8 && Random(1) < 0.0001) {
				fighter->headId = 1;
			}
		}
	}
	
	if (battle.encounter == 69) {
		Fighter* fighter = &battle.fighters[8];
		
		PartyMember* partyMember = &partyMembers[6];
		
		fighter->exp += partyMember->exp / 2;
		fighter->hpMax += partyMember->hpMax;
		fighter->mpMax += partyMember->mpMax;
		fighter->attack += partyMember->attack;
		fighter->defense += partyMember->defense;
		fighter->speed += partyMember->speed;
		
		fighter->hp = fighter->hpMax;
		fighter->mp = fighter->mpMax;
		
		fighter->status[FIGHTER_STATUS_SERIOUS] = 1;
	}
	if (battle.encounter == 72 && profile.flags[FLAG_ALONE]) {
		Fighter* fighter = &battle.fighters[8];
		
		fighter->hpMax += 70;
		fighter->mpMax += 10;
		fighter->attack += 2;
		fighter->speed += 5;
		
		fighter->hp = fighter->hpMax;
		fighter->mp = fighter->mpMax;
		
		fighter->status[FIGHTER_STATUS_SERIOUS] = 1;
	}
	if (battle.encounter == 84) {
		Fighter* fighter = &battle.fighters[8];
		
		PartyMember* partyMember = &partyMembers[3];
		
		fighter->exp += partyMember->exp / 128;
		fighter->hpMax = partyMember->hpMax;
		fighter->mpMax = partyMember->mpMax;
		fighter->attack = partyMember->attack;
		fighter->defense = partyMember->defense;
		fighter->speed = partyMember->speed;
		
		fighter->hp = fighter->hpMax;
		fighter->mp = fighter->mpMax;
	}
	if (battle.encounter == 102) {
		if (profile.flags[FLAG_RUBY_GODMODE]) {
			battle.everythingButSkillsDisabled = true;
			
			battle.musicId = MUS_trance;
			
			Fighter* fighter = &battle.fighters[8];
			
			fighter->defense -= -1015821984;
		}
		else {
			battle.everythingButSkillsDisabled = true;
			
			Fighter* fighter = &battle.fighters[0];
			
			fighter->ai = 0;
			fighter->bodyId = 10;
			fighter->actionAnimId = 62;
			fighter->movesetCount = 1;
			fighter->moveset[0] = 5;
			fighter->passiveCount = 0;
		}
	}
	if (battle.encounter == 103) {
		Fighter* fighter = &battle.fighters[8];
		
		fighter->status[FIGHTER_STATUS_SERIOUS] = 1;
	}
	if (battle.encounter == 104) {
		Fighter* fighter = &battle.fighters[8];
		
		fighter->status[FIGHTER_STATUS_SERIOUS] = 1;
		
		fighter = &battle.fighters[9];
		
		fighter->status[FIGHTER_STATUS_SERIOUS] = 1;
	}
}



void Battle_Update() {
	battle.timer++;
	battle.globalTimer++;
	
	if (battle.shakeTimer > 0) battle.shakeTimer--;
	
	if (battle.camera.moveTarget.enabled) {
		float distance = PointDistance(battle.camera.x, battle.camera.y, battle.camera.moveTarget.x, battle.camera.moveTarget.y);
		
		if (distance <= battle.camera.moveTarget.speed) {
			battle.camera.x = battle.camera.moveTarget.x;
			battle.camera.y = battle.camera.moveTarget.y;
			battle.camera.zoom = battle.camera.moveTarget.zoom;
			battle.camera.moveTarget.enabled = false;
		}
		else {
			float direction = PointDirection(battle.camera.x, battle.camera.y, battle.camera.moveTarget.x, battle.camera.moveTarget.y);
			
			battle.camera.x += cos(direction) * battle.camera.moveTarget.speed;
			battle.camera.y += sin(direction) * battle.camera.moveTarget.speed;
			battle.camera.zoom += battle.camera.moveTarget.zoomSpeed;
		}
	}
	
	for (int i = 0; i < 16; i++) {
		Fighter* fighter = &battle.fighters[i];
		if (!fighter->enabled) continue;
		
		if (fighter->moveTarget.enabled) {
			float distance = PointDistance(fighter->x, fighter->y, fighter->moveTarget.x, fighter->moveTarget.y);
			
			if (distance <= fighter->moveTarget.speed) {
				fighter->x = fighter->moveTarget.x;
				fighter->y = fighter->moveTarget.y;
				if (fighter->moveTarget.facing != 0) fighter->facing = fighter->moveTarget.facing;
				fighter->moveTarget.enabled = false;
			}
			else {
				float direction = PointDirection(fighter->x, fighter->y, fighter->moveTarget.x, fighter->moveTarget.y);
				
				fighter->x += cos(direction) * fighter->moveTarget.speed;
				fighter->y += sin(direction) * fighter->moveTarget.speed;
			}
		}
		else {
			if (fighter->bodyId == 54 && !fighter->alive && fighter->state == FIGHTER_STATE_DOWN && fighter->x < SCREEN_WIDTH + 16 && fighter->x > -16) {
				fighter->x -= fighter->facing;
			}
		}
		
		if (fighter->flinchTicks > 0) {
			fighter->flinchTicks--;
			if (fighter->flinchTicks == 0 && fighter->hp > 0) {
				Fighter_SwitchToDefaultState(fighter);
			}
		}
		
		if (fighter->storeHealedHP != 0) {
			if (fighter->status[FIGHTER_STATUS_ANTIREGEN]) {
				Audio_PlaySoundInterrupt(SND_closeskill);
			}
			else {
				float y = fighter->y;
				if (fighter->storeHealedMP != 0) y -= 16;
				snprintf(game.textBuffer, 16, "%d", fighter->storeHealedHP);
				Battle_CreateLabel(4, game.textBuffer, fighter->x, y - 32);
			}
			
			Battle_CreateSpark(4, fighter->x, fighter->y - 24, 0);
			
			fighter->storeHealedHP = 0;
		}
		if (fighter->storeHealedMP != 0) {
			float y = fighter->y;
			snprintf(game.textBuffer, 16, "%d", fighter->storeHealedMP);
			Battle_CreateLabel(5, game.textBuffer, fighter->x, y - 32);
			
			Battle_CreateSpark(5, fighter->x, fighter->y - 24, 0);
			
			fighter->storeHealedMP = 0;
		}
	}
	
	switch (battle.state) {
		case BATTLE_STATE_START:
			Battle_Update_Start();
			break;
		case BATTLE_STATE_IDLE:
			Battle_Update_Idle();
			break;
		case BATTLE_STATE_ACTION:
			Battle_Update_Action();
			break;
		case BATTLE_STATE_END:
			Battle_Update_End();
			break;
		case BATTLE_STATE_EVENT:
			Battle_Update_Event();
			break;
	}
	
	for (int i = 0; i < 16; i++) {
		if (battle.label[i].timer < 0) continue;
		
		battle.label[i].timer++;
		
		if (battle.label[i].timer < 40) {
			battle.label[i].y += -4 + battle.label[i].timer / 5;
		}
		
		if (battle.label[i].timer >= 75) battle.label[i].timer = -1;
	}
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		if (battle.sparks[i].id <= 0) continue;
		
		battle.sparks[i].timer++;
		battle.sparks[i].x += battle.sparks[i].xVel;
		battle.sparks[i].y += battle.sparks[i].yVel;
		
		switch (battle.sparks[i].id) {
			case 1:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 2:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 3:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 4:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 5:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 6:
				if (battle.sparks[i].timer >= 12) {
					battle.sparks[i].id = 0;
				}
				break;
			case 7:
				if (battle.sparks[i].timer >= 16) {
					battle.sparks[i].id = 0;
				}
				break;
			case 8:
				if (battle.sparks[i].timer >= 16) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9:
				battle.sparks[i].yVel = -16;
				if (battle.sparks[i].timer >= 160 || battle.sparks[i].y < 0) {
					battle.sparks[i].id = 0;
				}
				break;
			case 10:
				if (battle.sparks[i].timer >= 16) {
					battle.sparks[i].id = 0;
				}
				break;
			case 11:
				if (battle.sparks[i].timer >= 300 || battle.attacker == NULL || battle.target == NULL || battle.state != BATTLE_STATE_ACTION) {
					battle.sparks[i].id = 0;
					break;
				}
				if (battle.sparks[i].x < -16 || battle.sparks[i].x > 656) {
					battle.sparks[i].id = 0;
					break;
				}
				if (battle.attacker->actionVars[0].i == 0) {
					if (battle.sparks[i].y < 136) {
						Audio_PlaySound(SND_birchhit1);
						battle.sparks[i].y = 136;
						
						float velocity = PointDistance(0, 0, battle.sparks[i].xVel, battle.sparks[i].yVel);
						float angle = PointDirection(battle.sparks[i].x, battle.sparks[i].y, battle.target->x, battle.target->y - 24);
						battle.sparks[i].xVel = cos(angle) * velocity;
						battle.sparks[i].yVel = sin(angle) * velocity;
					}
					if (battle.sparks[i].y > 352) {
						Audio_PlaySound(SND_birchhit1);
						battle.sparks[i].y = 352;
						
						float velocity = PointDistance(0, 0, battle.sparks[i].xVel, battle.sparks[i].yVel);
						float angle = PointDirection(battle.sparks[i].x, battle.sparks[i].y, battle.target->x, battle.target->y - 24);
						battle.sparks[i].xVel = cos(angle) * velocity;
						battle.sparks[i].yVel = sin(angle) * velocity;
					}
				}
				else if (battle.attacker->actionVars[0].i == 3) {
					if (battle.sparks[i].y < 136) {
						Audio_PlaySound(SND_birchhit1);
						battle.sparks[i].y = 136;
						battle.sparks[i].yVel = -battle.sparks[i].yVel;
					}
					if (battle.sparks[i].y > 352) {
						Audio_PlaySound(SND_birchhit1);
						battle.sparks[i].y = 352;
						battle.sparks[i].yVel = -battle.sparks[i].yVel;
					}
				}
				if (battle.attacker->attackTimer < 1 && battle.sparks[i].x > battle.target->x - 24 && battle.sparks[i].x < battle.target->x + 24 && battle.sparks[i].y > battle.target->y - 48 && battle.sparks[i].y < battle.target->y) {
					battle.attacker->attackTimer = 1;
					Audio_PlaySound(SND_birchhit2);
					Battle_ShakeScreen(4);
					battle.sparks[i].id = 0;
					Battle_CreateSpark(12, battle.target->x, battle.target->y - 24, 0);
					break;
				}
				break;
			case 12:
				if (battle.sparks[i].timer >= 8) {
					battle.sparks[i].id = 0;
				}
				break;
			case 13:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 14:
				if (battle.sparks[i].timer >= 6) {
					battle.sparks[i].id = 0;
				}
				break;
			case 15:
				if (battle.sparks[i].timer >= 6) {
					battle.sparks[i].id = 0;
				}
				break;
			case 16:
				if (battle.sparks[i].timer >= 6) {
					battle.sparks[i].id = 0;
				}
				break;
			case 17:
				if (battle.sparks[i].timer >= 11) {
					battle.sparks[i].id = 0;
					Battle_CreateSpark(18, battle.sparks[i].x, battle.sparks[i].y + 32, 0);
					Audio_PlaySound(SND_gunfire2);
					Audio_PlaySound(SND_explode);
					Battle_ShakeScreen(48);
				}
				break;
			case 18:
				if (battle.sparks[i].timer >= 16) {
					battle.sparks[i].id = 0;
				}
				break;
			case 19:
				if (battle.sparks[i].timer >= 24) {
					battle.sparks[i].id = 0;
				}
				break;
			case 20:
				if (battle.sparks[i].timer >= 6) {
					battle.sparks[i].id = 0;
				}
				break;
			case 21:
				if (battle.sparks[i].timer >= 20) {
					battle.sparks[i].id = 0;
				}
				break;
			
			case 9900:
				if (battle.sparks[i].timer >= 8) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9901:
				if (battle.sparks[i].timer >= 5) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9902:
				if (battle.sparks[i].timer == 1) {
					battle.sparks[i].xVel = Random_Range(-24, 24);
					battle.sparks[i].yVel = Random_Range(-24, 24);
				}
				battle.sparks[i].xVel += Random_Range(-1, 1);
				battle.sparks[i].yVel += Random_Range(-1, 1);
				if (battle.sparks[i].timer >= 120) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9903:
				if (battle.sparks[i].timer == 1) {
					battle.sparks[i].xVel = Random_Range(-24, 24);
					battle.sparks[i].yVel = Random_Range(-24, 24);
				}
				if (battle.sparks[i].timer >= 120) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9904:
				if (battle.sparks[i].timer == 1) {
					battle.sparks[i].xVel = Random_Range(-24, 24);
					battle.sparks[i].yVel = Random_Range(-24, 24);
				}
				battle.sparks[i].xVel += Random_Range(-1, 1);
				battle.sparks[i].yVel += Random_Range(-1, 1);
				if (battle.sparks[i].timer >= 120) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9905:
				if (battle.sparks[i].timer >= 5) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9906:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9907:
				if (battle.sparks[i].timer >= 10) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9908:
				if (battle.sparks[i].timer >= 39) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9909:
				if (battle.sparks[i].timer >= 39) {
					battle.sparks[i].id = 0;
				}
				break;
			case 9910:
				if (battle.sparks[i].timer >= 40) {
					battle.sparks[i].id = 0;
				}
				break;
		}
	}
}

void Battle_Update_Start() {
	if (battle.timer == 1) {
		Audio_PlaySound(SND_encounter);
		for (int i = 0; i < 5; i++) {
			if (profile.party[i] < 0) continue;
			
			PartyMember* partyMember = &partyMembers[profile.party[i]];
			
			if (partyMember->armorId != 0) {
				Audio_PlaySound(SND_encountermg);
				break;
			}
		}
	}
	if (battle.timer >= 45) {
		battle.state = BATTLE_STATE_IDLE;
		battle.timer = 0;
		if (!profile.tempFlags[TEMPFLAG_DISABLEBATTLEMUSIC]) {
			Audio_PlayMusic(battle.musicId);
		}
	}
}

void Battle_Update_Idle() {
	if (battle.timer == 0) {
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Fighter_MoveToStart(fighter);
		}
	}
	else if (battle.timer == 1) {
		battle.turnCount++;
		
		for (int i = 0; i < 16; i++) {
			battle.turnOrder[i] = -1;
		}
		
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			fighter->bodyguardId = -1;
			fighter->targetId = 0;
			fighter->actionId = 0;
			fighter->usedItemId = 0;
			fighter->manaCostReduction = 0;
			
			fighter->mp += 1 + fighter->mpMax / 20;
			
			if (!fighter->statusOverride[FIGHTER_STATUS_BURN] && fighter->status[FIGHTER_STATUS_BURN] > 0) {
				Fighter_TakeDamage(fighter, NULL, fighter->status[FIGHTER_STATUS_BURN], 0);
				fighter->status[FIGHTER_STATUS_BURN] = fighter->status[FIGHTER_STATUS_BURN] * 2 / 3;
				Audio_PlaySoundInterrupt(SND_burn);
				Battle_CreateSpark(2, fighter->x, fighter->y - 24, 0);
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_BLEED] && fighter->status[FIGHTER_STATUS_BLEED] > 0) {
				Fighter_TakeDamage(fighter, NULL, fighter->status[FIGHTER_STATUS_BLEED], 0);
				Battle_CreateSpark(3, fighter->x, fighter->y - 24, 0);
				Audio_PlaySoundInterrupt(SND_poison);
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_POISON] && fighter->status[FIGHTER_STATUS_POISON] > 0) {
				fighter->mp -= (fighter->status[FIGHTER_STATUS_POISON] + 1) / 2;
				Fighter_TakeDamage(fighter, NULL, fighter->status[FIGHTER_STATUS_POISON], 0);
				fighter->status[FIGHTER_STATUS_POISON] = fighter->status[FIGHTER_STATUS_POISON] * 2 / 3;
				Audio_PlaySoundInterrupt(SND_poison);
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_TIMEDBOMB] && fighter->status[FIGHTER_STATUS_TIMEDBOMB] > 0) {
				Fighter_TakeDamage(fighter, NULL, fighter->status[FIGHTER_STATUS_TIMEDBOMB], 0);
				fighter->status[FIGHTER_STATUS_TIMEDBOMB] = 0;
				Audio_PlaySoundInterrupt(SND_explode);
				Battle_ShakeScreen(6);
				Battle_CreateSpark(2, fighter->x, fighter->y - 24, 0);
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_CHILL] && fighter->status[FIGHTER_STATUS_CHILL] > 0) {
				fighter->mp -= fighter->status[FIGHTER_STATUS_CHILL];
				fighter->status[FIGHTER_STATUS_CHILL] = fighter->status[FIGHTER_STATUS_CHILL] * 2 / 3;
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_FLOWER] && fighter->status[FIGHTER_STATUS_FLOWER] > 0) {
				fighter->mp -= fighter->status[FIGHTER_STATUS_FLOWER];
				fighter->status[FIGHTER_STATUS_FLOWER] = fighter->status[FIGHTER_STATUS_FLOWER] * 2 / 3;
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_MANADISCOUNT] && fighter->status[FIGHTER_STATUS_MANADISCOUNT] > 0) {
				fighter->manaCostReduction += fighter->status[FIGHTER_STATUS_MANADISCOUNT] & 0xffff;
				fighter->status[FIGHTER_STATUS_MANADISCOUNT] -= 1 << 16;
				if (fighter->status[FIGHTER_STATUS_MANADISCOUNT] < 0) fighter->status[FIGHTER_STATUS_MANADISCOUNT] = 0;
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_MANAPERMADISCOUNT] && fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT] != 0) {
				fighter->manaCostReduction += fighter->status[FIGHTER_STATUS_MANAPERMADISCOUNT];
			}
			
			if (!fighter->statusOverride[FIGHTER_STATUS_STRENGTH]) fighter->status[FIGHTER_STATUS_STRENGTH] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_FEEBLE]) fighter->status[FIGHTER_STATUS_FEEBLE] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_ENDURANCE]) fighter->status[FIGHTER_STATUS_ENDURANCE] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_DISARM]) fighter->status[FIGHTER_STATUS_DISARM] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_HASTE]) fighter->status[FIGHTER_STATUS_HASTE] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_BIND]) fighter->status[FIGHTER_STATUS_BIND] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_BLEED]) fighter->status[FIGHTER_STATUS_BLEED] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_GUARD]) fighter->status[FIGHTER_STATUS_GUARD] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_COUNTER]) fighter->status[FIGHTER_STATUS_COUNTER] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_PARALYSIS]) fighter->status[FIGHTER_STATUS_PARALYSIS] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_ANTIGUARD]) fighter->status[FIGHTER_STATUS_ANTIGUARD] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_IMMOBILE]) fighter->status[FIGHTER_STATUS_IMMOBILE] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_ATTACKMULT]) fighter->status[FIGHTER_STATUS_ATTACKMULT] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_EVADE]) fighter->status[FIGHTER_STATUS_EVADE] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_DEFLECT]) fighter->status[FIGHTER_STATUS_DEFLECT] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_ABSORPTION]) fighter->status[FIGHTER_STATUS_ABSORPTION] = 0;
			if (!fighter->statusOverride[FIGHTER_STATUS_ANTIREGEN]) fighter->status[FIGHTER_STATUS_ANTIREGEN] = 0;
			
			for (int i = 0; i < 32; i++) {
				fighter->status[i] += fighter->statusNext[i];
				fighter->statusNext[i] = 0;
			}
			
			if (fighter->mp < 0) fighter->mp = 0;
			if (fighter->mp > fighter->mpMax) fighter->mp = fighter->mpMax;
			
			
			
			if (!fighter->alive && fighter->fatalInjury) {
				fighter->state = FIGHTER_STATE_HURT;
				if (battle.timer == 1) {
					battle.turnStartFatalInjury = true;
					battle.state = BATTLE_STATE_ACTION;
					battle.attacker = fighter;
					battle.timer = 6;
				}
				continue;
			}
			
			fighter->speedRoll = fighter->speed + fighter->status[FIGHTER_STATUS_HASTE] - fighter->status[FIGHTER_STATUS_BIND] - fighter->status[FIGHTER_STATUS_PARALYSIS] - fighter->status[FIGHTER_STATUS_CHILL];
			fighter->speedRollMin = fighter->speedRoll - 3;
			fighter->speedRollMax = fighter->speedRoll + 3;
			
			if (fighter->speedRollMin < 1) fighter->speedRollMin = 1;
			if (fighter->speedRollMax < 1) fighter->speedRollMax = 1;
			
			if (fighter->status[FIGHTER_STATUS_PARALYSIS])
				fighter->speedRollMax = fighter->speedRollMin;
			
			fighter->speedRoll = Random_IRange(fighter->speedRollMin, fighter->speedRollMax);
			
			Fighter_SwitchToDefaultState(fighter);
		}
		
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			for (int j = 0; j < fighter->passiveCount; j++) Passive_OnTurnStart(fighter->passives[j], fighter);
		}
	}
	else if (battle.timer == 2) {
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			if (Fighter_AI_TurnStart(fighter)) {
				return;
			}
		}
		
		if (profile.flags[FLAG_PLOT] >= 5 && !profile.flags[FLAG_TUTORIAL_DEFENSE]) {
			Battle_TriggerBattleEvent(16, &battle.fighters[0]);
			profile.flags[FLAG_TUTORIAL_DEFENSE] = 1;
			return;
		}
		if (profile.flags[FLAG_PLOT] >= 10 && !profile.flags[FLAG_TUTORIAL_FLEE]) {
			Battle_TriggerBattleEvent(15, &battle.fighters[0]);
			profile.flags[FLAG_TUTORIAL_FLEE] = 1;
			return;
		}
		
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			for (int j = 0; j < fighter->movesetCount; j++) {
				Action* action = &actionData[fighter->moveset[j]];
				
				if (fighter->movesetDisabled[j] == 1) {
					Fighter_EnableAction(fighter, fighter->moveset[j]);
				}
				else if (fighter->movesetDisabled[j] == 2) {
					continue;
				}
				
				if (action->targetType == TARGETTYPE_DOWNALLY) {
					bool downAlly = false;
					for (int k = fighter->side * 8; k < fighter->side * 8 + 8; k++) {
						Fighter* fighter2 = &battle.fighters[k];
						if (!fighter2->enabled || fighter2->alive) continue;
						
						downAlly = true;
						break;
					}
					if (!downAlly) {
						Fighter_DisableAction(fighter, fighter->moveset[j]);
					}
				}
				
				if (action->condition == ACTIONCONDITION_HPHALF || action->condition == ACTIONCONDITION_EXHAUST_HPHALF) {
					if (fighter->hp > (fighter->hpMax + 1) / 2) {
						Fighter_DisableAction(fighter, fighter->moveset[j]);
					}
				}
				else if (action->condition == ACTIONCONDITION_STATUSCOST) {
					if (fighter->status[action->conditionVars[0].i] < action->conditionVars[1].i) {
						Fighter_DisableAction(fighter, fighter->moveset[j]);
					}
				}
				else if (action->condition == ACTIONCONDITION_AZTEC_1) {
					if (fighter->status[FIGHTER_STATUS_PARALYSIS] != 3 || fighter->movesetCount != 5 || fighter->mp % 8 != 0) {
						Fighter_DisableAction(fighter, fighter->moveset[j]);
					}
				}
			}
			
			fighter->canAct = true;
			if (fighter->status[FIGHTER_STATUS_IMMOBILE] || fighter->status[FIGHTER_STATUS_WEAPONSEARCH]) fighter->canAct = false;
			
			fighter->actionId = 0;
			fighter->targetId = 0;
			if (fighter->side == 1 && fighter->movesetCount > 0) {
				Fighter_AI_ChooseAction(fighter);
			}
			
			Fighter_SwitchToDefaultState(fighter);
		}
		
		battle.turn = -1;
		while (++battle.turn < 8 && (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive));
		Battle_ChangeMenu(0);
		Menu_ResetCursor(&battle.menu);
		
		int sidesAlive[2] = {0, 0};
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive || fighter->side < 0 || fighter->side > 1) continue;
			
			sidesAlive[fighter->side]++;
		}
		
		if (sidesAlive[0] <= 0 && !battle.gameOverDisabled) {
			battle.state = BATTLE_STATE_END;
			battle.timer = 2;
			battle.gameover = true;
		}
		else if (sidesAlive[1] <= 0) {
			battle.state = BATTLE_STATE_END;
			battle.timer = 0;
		}
	}
	
	if (battle.timer >= 3) {
		Menu_Update(&battle.menu);
		
		switch (battle.menu.id) {
			case 0:
				if (PlayerButtonPressed(PLAYER_BUTTON_C) && !battle.everythingButSkillsDisabled) {
					Audio_PlaySoundInterrupt(SND_menu6);
					Battle_ChangeMenu(5);
					Menu_ResetCursor(&battle.menu);
				}
				else if (battle.menu.optionPressed == 0) {
					if (battle.fighters[battle.turn].movesetCount >= 1) {
						Battle_ChangeMenu(1);
						Menu_ResetCursor(&battle.menu);
					}
				}
				else if (battle.menu.optionPressed == 1 && !battle.everythingButSkillsDisabled) {
					Battle_ChangeMenu(4);
					Menu_ResetCursor(&battle.menu);
				}
				else if (battle.menu.optionPressed == 2 && !battle.everythingButSkillsDisabled) {
					for (int i = 0; i < 16; i++) {
						if (profile.itemInventory[i] > 0) {
							Battle_ChangeMenu(3);
							Menu_ResetCursor(&battle.menu);
							break;
						}
					}
				}
				else if (battle.menu.optionPressed == 3 && !battle.everythingButSkillsDisabled) {
					while (++battle.turn < 8 && (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive));
					
					Battle_ChangeMenu(0);
					Menu_ResetCursor(&battle.menu);
					
					if (battle.turn >= 8) {
						battle.state = BATTLE_STATE_ACTION;
						battle.timer = -1;
						battle.turn = 0;
						battle.priority = 5;
					}
				}
				else if (battle.menu.optionPressed == MENUOPTION_BACK) {
					if (battle.turn <= 0) battle.turn = 1;
					while (--battle.turn > 0 && (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive));
					
					if (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive) {
						while (++battle.turn < 8 && (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive));
					}
					
					battle.fighters[battle.turn].actionId = 0;
					battle.fighters[battle.turn].usedItemId = 0;
					
					Battle_ChangeMenu(0);
					Menu_ResetCursor(&battle.menu);
				}
				break;
			case 1:
				if (battle.menu.optionPressed >= 0) {
					int actionId = battle.menu.optionPressedValue;
					if (battle.fighters[battle.turn].mp >= Max(0, actionData[actionId].cost - battle.fighters[battle.turn].manaCostReduction) && !battle.fighters[battle.turn].movesetDisabled[battle.menu.optionPressed]) {
						battle.fighters[battle.turn].actionId = actionId;
						
						if (actionData[actionId].targetType == TARGETTYPE_ENEMY || actionData[actionId].targetType == TARGETTYPE_ALLY || actionData[actionId].targetType == TARGETTYPE_ANY || actionData[actionId].targetType == TARGETTYPE_DOWNALLY) {
							battle.fighters[battle.turn].targetId = battle.turn;
							Battle_ChangeMenu(2);
							Menu_ResetCursor(&battle.menu);
						}
						else {
							if (actionData[actionId].targetType == TARGETTYPE_ENEMYPARTY)
								battle.fighters[battle.turn].targetId = TARGET_ENEMYPARTY;
							else if (actionData[actionId].targetType == TARGETTYPE_ALLYPARTY)
								battle.fighters[battle.turn].targetId = TARGET_ALLYPARTY;
							
							while (++battle.turn < 8 && (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive));
							
							Battle_ChangeMenu(0);
							Menu_ResetCursor(&battle.menu);
							
							if (battle.turn >= 8) {
								battle.state = BATTLE_STATE_ACTION;
								battle.timer = -1;
								battle.turn = 0;
								battle.priority = 5;
							}
						}
					}
				}
				else if (battle.menu.optionPressed == MENUOPTION_BACK) {
					Battle_ChangeMenu(0);
				}
				break;
			case 2:
				if (battle.menu.optionPressed >= 0) {
					battle.fighters[battle.turn].targetId = battle.menu.optionPressedValue;
					
					while (++battle.turn < 8 && (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive));
					
					Battle_ChangeMenu(0);
					Menu_ResetCursor(&battle.menu);
					
					if (battle.turn >= 8) {
						battle.state = BATTLE_STATE_ACTION;
						battle.timer = -1;
						battle.turn = 0;
						battle.priority = 5;
					}
				}
				else if (battle.menu.optionPressed == MENUOPTION_BACK) {
					battle.fighters[battle.turn].actionId = 0;
					if (battle.fighters[battle.turn].usedItemId > 0) {
						battle.fighters[battle.turn].usedItemId = 0;
						Battle_ChangeMenu(3);
					}
					else
						Battle_ChangeMenu(1);
				}
				break;
			case 3:
				if (battle.menu.optionPressed >= 0) {
					int itemId = profile.itemInventory[battle.menu.optionPressedValue];
					if (itemData[itemId].actionId > 0) {
						int actionId = itemData[itemId].actionId;
						battle.fighters[battle.turn].actionId = actionId;
						battle.fighters[battle.turn].usedItemId = itemId;
						battle.fighters[battle.turn].usedItemSlot = battle.menu.optionPressedValue;
						
						if (actionData[actionId].targetType == TARGETTYPE_ENEMY || actionData[actionId].targetType == TARGETTYPE_ALLY || actionData[actionId].targetType == TARGETTYPE_ANY) {
							battle.fighters[battle.turn].targetId = battle.turn;
							Battle_ChangeMenu(2);
							Menu_ResetCursor(&battle.menu);
						}
						else {
							if (actionData[actionId].targetType == TARGETTYPE_ENEMYPARTY)
								battle.fighters[battle.turn].targetId = TARGET_ENEMYPARTY;
							else if (actionData[actionId].targetType == TARGETTYPE_ALLYPARTY)
								battle.fighters[battle.turn].targetId = TARGET_ALLYPARTY;
							
							while (++battle.turn < 8 && (!battle.fighters[battle.turn].enabled || !battle.fighters[battle.turn].alive));
							
							Battle_ChangeMenu(0);
							Menu_ResetCursor(&battle.menu);
							
							if (battle.turn >= 8) {
								battle.state = BATTLE_STATE_ACTION;
								battle.timer = -1;
								battle.turn = 0;
								battle.priority = 5;
							}
						}
					}
				}
				else if (battle.menu.optionPressed == MENUOPTION_BACK) {
					Battle_ChangeMenu(0);
				}
				break;
			case 4:
				if (battle.menu.optionPressed >= 0) {
					
				}
				else if (battle.menu.optionPressed == MENUOPTION_BACK) {
					Battle_ChangeMenu(0);
				}
				break;
			case 5:
				if (battle.menu.optionPressed == 0 && battle.canFlee) {
					battle.state = BATTLE_STATE_END;
					battle.timer = 100;
					battle.fleeing = true;
				}
				else if (battle.menu.optionPressed == 1) {
					battle.state = BATTLE_STATE_END;
					battle.timer = 4;
					battle.retry = true;
				}
				else if (battle.menu.optionPressed == 2) {
					battle.state = BATTLE_STATE_END;
					battle.timer = 4;
					battle.loadLastSave = true;
				}
				else if (battle.menu.optionPressed == MENUOPTION_BACK || PlayerButtonPressed(PLAYER_BUTTON_C)) {
					Audio_PlaySoundInterrupt(SND_menu3);
					Battle_ChangeMenu(0);
				}
				break;
		}
	}
}

void Battle_Update_Action() {
	if (battle.timer == 0) {
		int turnOrderLength = 0;
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			battle.turnOrder[turnOrderLength++] = i;
			
			fighter->priority = 0;
			if (fighter->actionId >= 1) {
				fighter->priority = actionData[fighter->actionId].priority;
			}
		}
		
		for (int i = 0; i < turnOrderLength; i++) {
			for (int j = 0; j < turnOrderLength - 1; j++) {
				Fighter* fighter1 = &battle.fighters[battle.turnOrder[j]];
				Fighter* fighter2 = &battle.fighters[battle.turnOrder[j+1]];
				if (fighter1->speedRoll + fighter1->priority * 1000000 < fighter2->speedRoll + fighter2->priority * 1000000) {
					int temp = battle.turnOrder[j];
					battle.turnOrder[j] = battle.turnOrder[j+1];
					battle.turnOrder[j+1] = temp;
				}
			}
		}
	}
	
	if (battle.timer == 1) {
		battle.attacker = NULL;
		battle.target = NULL;
		
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			if (fighter->targetId >= 0 && fighter->targetId < 16) {
				Fighter* target = &battle.fighters[fighter->targetId];
				
				if (target->bodyguardId >= 0 && fighter->side != target->side) {
					fighter->targetId = target->bodyguardId;
				}
			}
			if (fighter->counterTargetId >= 0) {
				battle.attacker = fighter;
				
				if (battle.fighters[fighter->counterTargetId].alive) {
					battle.target = &battle.fighters[fighter->counterTargetId];
					
					battle.attacker->blockTimer = -1;
					battle.attacker->blockCooldownTimer = -1;
					battle.attacker->attackTimer = -1;
					battle.attacker->attackAnimTimer = -1;
					battle.attacker->attackAnimTime = -1;
					battle.attacker->readyTimer = 0;
					battle.attacker->totalAttackTimer = 0;
					for (int i = 0; i < 4; i++) {
						battle.attacker->actionPower[i] = actionData[COUNTER_DEFAULT_ACTION].power[i];
						battle.attacker->actionVars[i].i = actionData[COUNTER_DEFAULT_ACTION].vars[i].i;
					}
					battle.attacker->actionPower[0] = battle.attacker->status[FIGHTER_STATUS_COUNTER];
					battle.attacker->actionVars[1].i = 1;
					for (int i = 0; i < 8; i++) {
						battle.attacker->tempVars[i].i = 0;
					}
					battle.attacker->actionPowerRepeat = actionData[COUNTER_DEFAULT_ACTION].powerRepeat;
					battle.attacker->actionAttackMultiplier = actionData[COUNTER_DEFAULT_ACTION].attackMultiplier;
					battle.attacker->actionAttacks = 0;
					battle.attacker->actionTempAnimId = battle.attacker->actionAnimId;
					
					Fighter_PrepareToBlock(battle.target);
					
					Dialog_Run(4006);
					break;
				}
			}
		}
		
		if (battle.target == NULL) {
			while (battle.turn < 16) {
				int id = battle.turnOrder[battle.turn++];
				
				if (id >= 0 && id < 16) {
					battle.attacker = &battle.fighters[id];
					if (battle.attacker->targetId >= 0 && battle.attacker->targetId < 16) {
						battle.target = &battle.fighters[battle.attacker->targetId];
					}
					else {
						battle.target = battle.attacker;
					}
					
					if (battle.attacker && battle.attacker->alive && battle.attacker->actionId > 0 && battle.target && ((battle.target->enabled && (battle.target->alive || actionData[battle.attacker->actionId].targetType == TARGETTYPE_DOWNALLY)) || actionData[battle.attacker->actionId].targetType == TARGETTYPE_NONE)) {
						if (battle.attacker->mp < Max(0, actionData[battle.attacker->actionId].cost - battle.attacker->manaCostReduction)) {
							battle.attacker->readyTimer = -404;
							Dialog_Run(4009);
							break;
						}
						battle.attacker->blockTimer = -1;
						battle.attacker->blockCooldownTimer = -1;
						battle.attacker->attackTimer = -1;
						battle.attacker->attackAnimTimer = -1;
						battle.attacker->attackAnimTime = -1;
						battle.attacker->readyTimer = 0;
						battle.attacker->totalAttackTimer = 0;
						for (int i = 0; i < 4; i++) {
							battle.attacker->actionPower[i] = actionData[battle.attacker->actionId].power[i];
							battle.attacker->actionVars[i].i = actionData[battle.attacker->actionId].vars[i].i;
						}
						for (int i = 0; i < 8; i++) {
							battle.attacker->tempVars[i].i = 0;
						}
						battle.attacker->actionPowerRepeat = actionData[battle.attacker->actionId].powerRepeat;
						battle.attacker->actionAttackMultiplier = actionData[battle.attacker->actionId].attackMultiplier;
						battle.attacker->actionAttacks = 0;
						battle.attacker->actionTempAnimId = battle.attacker->actionAnimId;
						if (actionData[battle.attacker->actionId].animationId >= 0)
							battle.attacker->actionTempAnimId = actionData[battle.attacker->actionId].animationId;
						
						battle.attacker->attackAnimTime = actionAnimData[battle.attacker->actionTempAnimId].time;
						if (battle.attacker->targetId == TARGET_ALLYPARTY) {
							for (int i = 0; i < 8; i++) {
								Fighter* fighter = &battle.fighters[i];
								if (!fighter->enabled || !fighter->alive) continue;
								
								Fighter_PrepareToBlock(fighter);
								
								if (battle.target == battle.attacker) {
									battle.target = fighter;
								}
							}
						}
						else if (battle.attacker->targetId == TARGET_ENEMYPARTY) {
							for (int i = 8; i < 16; i++) {
								Fighter* fighter = &battle.fighters[i];
								if (!fighter->enabled || !fighter->alive) continue;
								
								Fighter_PrepareToBlock(fighter);
								
								if (battle.target == battle.attacker) {
									battle.target = fighter;
								}
							}
						}
						else if (actionData[battle.attacker->actionId].targetType != TARGETTYPE_NONE) {
							Fighter_PrepareToBlock(battle.target);
						}
						
						Dialog_Run(4000);
						break;
					}
				}
				else {
					battle.state = BATTLE_STATE_IDLE;
					battle.timer = -1;
					
					for (int i = 0; i < 15; i++) {
						if (profile.itemInventory[i] == 0) {
							for (int j = i + 1; j < 16; j++) {
								if (profile.itemInventory[j] > 0) {
									Profile_ItemRemove(i--);
									break;
								}
							}
						}
					}
					
					for (int i = 0; i < 16; i++) {
						Fighter* fighter = &battle.fighters[i];
						if (!fighter->enabled) continue;
						
						Fighter_AI_TurnEnd(fighter);
					}
					if (battle.state != BATTLE_STATE_EVENT && profile.flags[FLAG_PLOT] >= 70) {
						if (Random(1) < 0.07) {
							profile.flags[FLAG_FAKE_UNKNOWNHARDERROR]++;
							if (profile.flags[FLAG_FAKE_UNKNOWNHARDERROR] == 5) {
								Battle_TriggerBattleEvent(999, &battle.fighters[0]);
							}
						}
					}
					break;
				}
			}
		}
	}
	
	if (battle.timer == 2) {
		if (!Dialog_IsWaiting()) {
			battle.timer--;
		}
		else {
			if (battle.attacker->readyTimer == -404) {
				battle.timer--;
			}
			else if (battle.attacker->counterTargetId < 0) {
				Action* action = &actionData[battle.attacker->actionId];
				battle.attacker->mp -= Max(0, action->cost - battle.attacker->manaCostReduction);
				if (action->condition == ACTIONCONDITION_STATUSCOST) {
					battle.attacker->status[action->conditionVars[0].i] -= action->conditionVars[1].i;
					if (battle.attacker->status[action->conditionVars[0].i] < 0) {
						battle.attacker->status[action->conditionVars[0].i] = 0;
					}
				}
				if (action->condition == ACTIONCONDITION_EXHAUST || action->condition == ACTIONCONDITION_EXHAUST_HPHALF) {
					Fighter_DisableActionPermamently(battle.attacker, battle.attacker->actionId);
				}
				for (int i = 0; i < battle.attacker->passiveCount; i++) Passive_OnSkillUse(battle.attacker->passives[i], battle.attacker);
			}
		}
		
		if (Dialog_IsFinished()) {
			battle.timer = 5;
		}
	}
	
	if (battle.timer == 3) {
		if (battle.attacker->attackTimer >= 0) battle.attacker->attackTimer++;
		if (battle.attacker->attackAnimTimer >= 0) battle.attacker->attackAnimTimer++;
		if (battle.attacker->readyTimer >= 0) battle.attacker->readyTimer++;
		battle.attacker->totalAttackTimer++;
		
		if (battle.attacker->targetId == TARGET_ALLYPARTY) {
			for (int i = 0; i < 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Fighter_UpdateBlock(fighter);
			}
		}
		else if (battle.attacker->targetId == TARGET_ENEMYPARTY) {
			for (int i = 8; i < 16; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Fighter_UpdateBlock(fighter);
			}
		}
		else {
			Fighter_UpdateBlock(battle.target);
		}
		
		actionAnimUpdateCode[battle.attacker->actionTempAnimId](battle.attacker, battle.target);
		
		if (battle.attacker->status[FIGHTER_STATUS_HYPERENERGIZER]) {
			if (battle.attacker->attackTimer >= 0 && battle.attacker->attackAnimTimer >= 1) {
				battle.attacker->attackAnimTimer++;
			}
		}
		
		int runActionCodeId = actionData[battle.attacker->actionId].codeId;
		if (battle.attacker->counterTargetId >= 0)
			runActionCodeId = actionData[1].codeId;
		
		if (!actionUpdateCode[runActionCodeId](battle.attacker, battle.target)) {
			battle.timer--;
		}
	}
	
	
	if (battle.timer == 4) {
		Dialog_Continue();
	}
	
	if (battle.timer == 5) {
		battle.target->aiTakeAttackCount++;
		
		if (battle.target->hp <= 0 && actionData[battle.attacker->actionId].targetType == TARGETTYPE_ENEMY) {
			for (int i = 0; i < 16; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled) continue;
				
				for (int j = 0; j < fighter->passiveCount; j++) Passive_OnFighterDefeat(fighter->passives[j], fighter, battle.target);
			}
		}
		
		if (battle.attacker->readyTimer == -404) {
			
		}
		else if (battle.attacker->counterTargetId >= 0) {
			battle.attacker->counterTargetId = -1;
		}
		else {
			for (int i = 0; i < battle.attacker->passiveCount; i++) Passive_OnSkillEnd(battle.attacker->passives[i], battle.attacker);
			
			if (battle.attacker->usedItemId > 0) {
				profile.itemInventory[battle.attacker->usedItemSlot] = 0;
			}
		}
		
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || fighter->trulyDead) continue;
			
			if (!fighter->alive && fighter->fatalInjury) {
				fighter->state = FIGHTER_STATE_HURT;
				if (battle.timer == 5) {
					battle.attacker = fighter;
					battle.timer = 6;
					battle.turnStartFatalInjury = false;
				}
				continue;
			}
			
			Fighter_SwitchToDefaultState(fighter);
		}
		if (battle.timer == 5) battle.timer = 0;
	}
	
	if (battle.timer == 7) {
		Dialog_Run(4007);
		if (battle.attacker->collapseSpriteId >= 0) {
			battle.attacker->spriteId = battle.attacker->collapseSpriteId;
			battle.attacker->spriteFrame = 0;
		}
	}
	if (battle.timer == 8) {
		if (!Dialog_IsWaiting()) {
			battle.timer--;
		}
	}
	if (battle.timer >= 69 && battle.timer < 154 && battle.timer % 8 == 0) {
		battle.attacker->flinchTicks = 12;
	}
	if (battle.timer == 154) {
		Audio_PlaySound(SND_poison);
		battle.attacker->flinchTicks = 18;
		if (battle.attacker->collapseSpriteId >= 0) {
			battle.attacker->spriteFrame = 1;
		}
		else {
			battle.attacker->state = FIGHTER_STATE_DOWN;
		}
	}
	if (battle.timer == 220) {
		Dialog_Continue();
		battle.attacker->trulyDead = true;
		if (battle.attacker->side == 0) {
			battle.state = BATTLE_STATE_END;
			battle.timer = 4;
			battle.gameover = true;
		}
		else {
			for (int i = 0; i < 16; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || fighter->trulyDead) continue;
				
				if (!fighter->alive && fighter->fatalInjury) {
					battle.attacker = fighter;
					battle.timer = 6;
					break;
				}
			}
			if (battle.timer == 220) {
				if (battle.turnStartFatalInjury) {
					battle.state = BATTLE_STATE_IDLE;
					battle.timer = 1;
				}
				else
					battle.timer = 0;
			}
		}
	}
}

void Battle_Update_End() {
	if (battle.timer == 1) {
		int partySize = 0;
		battle.turn = 0;
		battle.expEarned = 0;
		battle.cashEarned = 0;
		battle.rewardCount = 0;
		for (int i = 0; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			if (fighter->side == 1) {
				battle.expEarned += fighter->exp * (1 + fighter->trulyDead);
				battle.cashEarned += fighter->cash;
				for (int j = 0; j < fighter->rewardCount; j++) {
					uint16_t progress = (uint16_t)profile.armorsProgress[fighter->rewards[j].id] + (uint16_t)(256 >> fighter->rewards[j].rarity);
					
					if (progress >= 256) {
						progress &= 0xff;
						profile.armorsProgress[fighter->rewards[j].id] = (uint8_t)progress;
						
						if (fighter->rewards[j].type != 0)
						if (armorData[fighter->rewards[j].id].specialAbility == 1 && profile.armors[fighter->rewards[j].id] > 0) {
							continue;
						}
						
						if (fighter->rewards[j].type == 0)
							Profile_AddAction(fighter->rewards[j].id, 1);
						else
							Profile_AddArmor(fighter->rewards[j].id, 1);
						
						bool isDuplicate = false;
						for (int k = 0; k < battle.rewardCount; k++) {
							if (battle.rewards[k].type == fighter->rewards[j].type && battle.rewards[k].id == fighter->rewards[j].id) {
								isDuplicate = true;
								battle.rewards[k].count++;
								break;
							}
						}
						if (!isDuplicate) {
							battle.rewards[battle.rewardCount].type = fighter->rewards[j].type;
							battle.rewards[battle.rewardCount].id = fighter->rewards[j].id;
							battle.rewards[battle.rewardCount].count = 1;
							battle.rewardCount++;
						}
					}
					else {
						profile.armorsProgress[fighter->rewards[j].id] = (uint8_t)progress;
					}
				}
			}
			else if (fighter->side == 0) {
				partySize++;
				
				if (i < 5)
				if (profile.party[i] >= 0) {
					PartyMember* partyMember = &partyMembers[profile.party[i]];
					
					if (fighter->hp > 1 || fighter->hpMax - fighter->hp > partyMember->hpDamage) {
						partyMember->hpDamage = fighter->hpMax - fighter->hp;
					}
					
					partyMember->tiredness += 5 + (20 - fighter->mp * 20 / fighter->mpMax) + (10 - fighter->hp * 10 / fighter->hpMax);
					if (!fighter->alive) partyMember->tiredness += 30;
					
					if (partyMember->tiredness >= partyMember->tiredThreshold * 2) {
						partyMember->tiredness = partyMember->tiredThreshold * 2;
						partyMember->tiredLevel = 2;
					}
					else if (partyMember->tiredness >= partyMember->tiredThreshold) {
						partyMember->tiredLevel = 1;
					}
					else {
						partyMember->tiredLevel = 0;
					}
				}
			}
		}
		battle.expEarned = (battle.expEarned + partySize - 1) / partySize;
		profile.cash += battle.cashEarned;
		
		Dialog_Run(4001);
	}
	if (battle.timer == 2) {
		battle.timer--;
		if (Dialog_IsWaiting()) {
			Dialog_Continue();
			while (battle.turn < 5) {
				int partyId = profile.party[battle.turn++];
				if (partyId < 0) continue;
				
				PartyMember* partyMember = &partyMembers[partyId];
				
				int levelPrev = partyMember->level;
				int hpPrev = partyMember->base.hpMax;
				int mpPrev = partyMember->base.mpMax;
				int attackPrev = partyMember->base.attack;
				int defensePrev = partyMember->base.defense;
				int speedPrev = partyMember->base.speed;
				
				Party_GainExp(partyId, battle.expEarned);
				
				if (partyMember->level > levelPrev) {
					battle.levelUp.partyId = partyId;
					battle.levelUp.hpGain = partyMember->base.hpMax - hpPrev;
					battle.levelUp.mpGain = partyMember->base.mpMax - mpPrev;
					battle.levelUp.attackGain = partyMember->base.attack - attackPrev;
					battle.levelUp.defenseGain = partyMember->base.defense - defensePrev;
					battle.levelUp.speedGain = partyMember->base.speed - speedPrev;
					battle.levelUp.actionId = 0;
					
					Dialog_Jump(4002);
					break;
				}
			}
		}
		if (Dialog_IsFinished()) {
			battle.timer = 5;
		}
	}
	
	if (battle.timer == 3) {
		Dialog_Run(4003);
	}
	if (battle.timer == 4) {
		if (!Dialog_IsFinished()) {
			battle.timer--;
		}
	}
	if (battle.timer == 5) {
		if (!profile.tempFlags[TEMPFLAG_DISABLEBATTLEMUSIC]) {
			Audio_FadeOutMusic(500);
		}
	}
	if (battle.timer == 35) {
		if (!profile.tempFlags[TEMPFLAG_DISABLEBATTLEMUSIC]) {
			Audio_StopMusic();
		}
		Audio_RemoveSoundFilter();
		game.frameskip = 0;
		if (battle.retry) {
			profile = profileBuffer;
			ChangeScene(SCENE_BATTLE);
		}
		else if (battle.loadLastSave) {
			if (profile.flags[FLAG_SAVECOUNT] != 0) {
				int ret = Profile_LoadGameSlot(game.saveFileNumber);
				if (ret == 1) {
					overworld.fadeAlpha = 1;
					overworld.transition.id = 1;
					overworld.transition.timer = 24;
					overworld.state = OVERWORLD_STATE_IDLE;
					ChangeScene(SCENE_OVERWORLD);
					Overworld_ChangeArea(overworld.areaId);
					return;
				}
				else {
					Audio_PlaySound(SND_no);
					if (ret == -2) {
						CreatePopup("File is not a Rubindeavor save.");
					}
					else if (ret == -3)
						CreatePopup("This file is from an older version\nof Rubindeavor and cannot be loaded.");
					else
						CreatePopup("Failed to load the file.");
				}
			}
			else {
				ChangeScene(SCENE_MENU);
			}
		}
		else if (battle.gameover) {
			ChangeScene(SCENE_GAMEOVER);
		}
		else {
			ChangeScene(SCENE_OVERWORLD);
			Audio_PlayMusic(overworld.lastMusicId);
			overworld.transition.timer++;
		}
	}
	if (battle.timer == 101) {
		for (int i = 0; i < 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			fighter->facing = FACING_LEFT;
			Fighter_MoveTo(fighter, fighter->x - 320, fighter->y, 12, FACING_LEFT);
			fighter->state = FIGHTER_STATE_RUN;
		}
		Dialog_Run(4008);
	}
	if (battle.timer >= 101 && battle.timer <= 120 && battle.timer % 8 == 5) {
		Audio_PlaySound(SND_chess_move);
	}
	if (battle.timer == 132) {
		Dialog_Continue();
		
		for (int i = 0; i < 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			if (fighter->side == 0) {
				if (i < 5)
				if (profile.party[i] >= 0) {
					PartyMember* partyMember = &partyMembers[profile.party[i]];
					
					if (fighter->hp > 1 || fighter->hpMax - fighter->hp > partyMember->hpDamage) {
						partyMember->hpDamage = fighter->hpMax - fighter->hp;
					}
					
					partyMember->tiredness += 10;
					partyMember->tiredness += 5 + (20 - fighter->mp * 20 / fighter->mpMax) + (10 - fighter->hp * 10 / fighter->hpMax);
					if (!fighter->alive) partyMember->tiredness += 30;
					
					if (partyMember->tiredness >= partyMember->tiredThreshold * 2) {
						partyMember->tiredness = partyMember->tiredThreshold * 2;
						partyMember->tiredLevel = 2;
					}
					else if (partyMember->tiredness >= partyMember->tiredThreshold) {
						partyMember->tiredLevel = 1;
					}
					else {
						partyMember->tiredLevel = 0;
					}
				}
			}
		}
		
		battle.timer = 4;
	}
}

void Battle_Update_Event() {
	bool finished = false;
	
	if (!Dialog_IsFinished() && battle.battleEventDialogWait) {
		battle.timer--;
		return;
	}
	
	switch (battle.battleEventId) {
		case 1:
			if (battle.timer == 1) {
				Dialog_Run(50);
			}
			if (battle.timer == 2) {
				Dialog_Run(51);
			}
			if (battle.timer == 3) {
				battle.state = BATTLE_STATE_END;
				battle.timer = 0;
			}
			break;
		case 2:
			if (battle.timer == 1) {
				Dialog_Run(49);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 3:
			if (battle.timer == 1) {
				Dialog_Run(2073);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 4:
			if (battle.timer == 1) {
				Dialog_Run(2074);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 5:
			if (battle.timer == 1) {
				Dialog_Run(3105);
				battle.battleEventDialogWait = false;
			}
			if (battle.timer == 360) {
				if (battle.battleEventVars[0] == 1 || battle.battleEventVars[0] == 3 || battle.battleEventVars[0] == 6)
					Audio_FadeOutMusic(2000);
			}
			if (battle.timer == 420) {
				battle.backgroundId = 8;
				battle.fighters[0].hp = battle.fighters[0].hpMax;
				battle.fighters[0].mp = battle.fighters[0].mpMax;
				battle.fighters[0].alive = true;
				battle.fighters[0].state = FIGHTER_STATE_HURT;
				for (int i = 0; i < 32; i++) {
					battle.fighters[0].status[i] = 0;
					battle.fighters[0].statusNext[i] = 0;
				}
				if (battle.battleEventVars[0] == 10) {
					battle.timer = 1000;
					Audio_FadeOutMusic(5000);
				}
			}
			if (battle.timer == 480) {
				battle.battleEventVars[1]++;
			}
			if (battle.timer == 500) {
				if (battle.battleEventVars[0] == 1) {
					Audio_PlayMusic(MUS_battlegate2);
				}
				else if (battle.battleEventVars[0] == 2) {
					Audio_ApplySoundFilter(0);
				}
				else if (battle.battleEventVars[0] == 3) {
					Audio_PlayMusic(MUS_battlegate3);
					game.frameskip = 1;
				}
				else if (battle.battleEventVars[0] == 6) {
					Audio_PlayMusic(MUS_battlegate4);
					game.frameskip = 4;
				}
				else if (battle.battleEventVars[0] == 7) {
					Audio_ApplySoundFilter(1);
				}
				else if (battle.battleEventVars[0] == 9) {
					Audio_ApplySoundFilter(2);
					game.frameskip = 18;
				}
			}
			if (battle.timer == 600) {
				Dialog_Continue();
				finished = true;
			}
			
			if (battle.timer == 1450) {
				Audio_RemoveSoundFilter();
				game.frameskip = 0;
				Dialog_Continue();
				ChangeScene(SCENE_OVERWORLD);
				overworld.transition.timer++;
			}
			break;
		case 6:
			if (battle.timer >= 70 && battle.timer <= 140 && battle.timer % 8 == 0) {
				battle.battleEventFighter->alive = false;
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				battle.battleEventFighter->flinchTicks = 18;
			}
			else if (battle.timer == 160) {
				battle.battleEventFighter->state = FIGHTER_STATE_SPECIAL3;
			}
			else if (battle.timer == 180) {
				Audio_PlaySound(SND_unknown3);
				battle.battleEventFighter->state = FIGHTER_STATE_SPECIAL4;
			}
			else if (battle.timer == 200) {
				Audio_PlaySound(SND_unknown2);
				battle.battleEventFighter->state = FIGHTER_STATE_SPECIAL5;
			}
			else if (battle.timer == 220) {
				battle.battleEventFighter->state = FIGHTER_STATE_SPECIAL6;
			}
			else if (battle.timer == 330) {
				battle.attacker = battle.battleEventFighter;
				Dialog_Run(3106);
			}
			else if (battle.timer == 331) {
				battle.state = BATTLE_STATE_END;
				battle.timer = 4;
				battle.gameover = true;
			}
			break;
		case 7:
			if (battle.timer == 1) {
				bool rubyHere = battle.fighters[0].headId == 1 && battle.fighters[0].enabled && battle.fighters[0].alive;
				battle.timer = 2;
				if (rubyHere) {
					switch (battle.battleEventFighter->headId) {
						case 1: battle.timer = 11; break;
						case 2: battle.timer = 21; break;
						case 3: battle.timer = 31; break;
						case 4: battle.timer = 41; break;
					}
				}
			}
			
			if (battle.timer == 2) {
				battle.attacker = battle.battleEventFighter;
				Dialog_Run(3122);
			}
			else if (battle.timer == 3) {
				finished = true;
			}
			
			if (battle.timer == 11) {
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Dialog_Run(3107);
			}
			else if (battle.timer == 12) {
				finished = true;
			}
			
			if (battle.timer == 21) {
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Dialog_Run(3108);
			}
			else if (battle.timer == 22) {
				battle.fighters[0].facing = FACING_LEFT;
				Dialog_Run(3109);
			}
			else if (battle.timer == 23) {
				Dialog_Run(3110);
			}
			else if (battle.timer == 24) {
				Dialog_Run(3111);
			}
			else if (battle.timer == 25) {
				Dialog_Run(3112);
			}
			else if (battle.timer == 26) {
				battle.fighters[0].facing = FACING_RIGHT;
				finished = true;
			}
			
			if (battle.timer == 31) {
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Dialog_Run(3113);
			}
			else if (battle.timer == 32) {
				battle.fighters[0].facing = FACING_LEFT;
				Dialog_Run(3114);
			}
			else if (battle.timer == 33) {
				Dialog_Run(3115);
			}
			else if (battle.timer == 34) {
				Dialog_Run(3116);
			}
			else if (battle.timer == 35) {
				battle.fighters[0].facing = FACING_RIGHT;
				finished = true;
			}
			
			if (battle.timer == 41) {
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Dialog_Run(3117);
			}
			else if (battle.timer == 42) {
				battle.fighters[0].facing = FACING_LEFT;
				Dialog_Run(3118);
			}
			else if (battle.timer == 43) {
				Dialog_Run(3119);
			}
			else if (battle.timer == 44) {
				Dialog_Run(3120);
			}
			else if (battle.timer == 45) {
				Dialog_Run(3121);
			}
			else if (battle.timer == 46) {
				battle.fighters[0].facing = FACING_RIGHT;
				finished = true;
			}
			break;
		case 8:
			if (battle.timer == 1) {
				Dialog_Run(2155);
			}
			else if (battle.timer == 2) {
				Dialog_Run(2154);
				battle.battleEventDialogWait = false;
			}
			else if (battle.timer == 75) {
				battle.battleEventFighter->state = FIGHTER_STATE_BLOCK;
				Audio_PlaySound(SND_boost);
			}
			else if (battle.timer == 135) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				Battle_ShakeScreen(20);
				Audio_PlaySound(SND_reset);
				Audio_PlayMusic(MUS_lastresort_pitchup);
				battle.battleEventVars[1] = 1;
				battle.battleEventVars[2] = battle.backgroundId;
				battle.backgroundId = 10;
				battle.battleEventFighter->hp = battle.battleEventFighter->hpMax;
				battle.battleEventFighter->mp = battle.battleEventFighter->mpMax;
				battle.battleEventFighter->status[FIGHTER_STATUS_HYPERENERGIZER] = 1;
				battle.battleEventFighter->status[FIGHTER_STATUS_STRENGTH] = 50;
				battle.battleEventFighter->status[FIGHTER_STATUS_ENDURANCE] = 50;
				battle.battleEventFighter->status[FIGHTER_STATUS_HASTE] = 50;
				battle.battleEventFighter->status[FIGHTER_STATUS_COUNTER] = 10;
			}
			else if (battle.timer == 279) {
				Dialog_Continue();
				battle.battleEventDialogWait = true;
			}
			else if (battle.timer == 280) {
				Dialog_Run(2156);
			}
			else if (battle.timer == 281) {
				finished = true;
			}
			break;
		case 9:
			if (battle.timer == 1) {
				Audio_PlayMusic(MUS_battle);
				battle.backgroundId = battle.battleEventVars[2];
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				battle.battleEventFighter->status[FIGHTER_STATUS_HYPERENERGIZER] = 0;
				battle.battleEventFighter->status[FIGHTER_STATUS_IMMOBILE] = 1;
				battle.battleEventFighter->status[FIGHTER_STATUS_DISARM] = 10;
			}
			if (battle.timer == 140 && profile.flags[FLAG_SALLY_JOINED]) {
				Dialog_Run(2157);
			}
			if (battle.timer == 141) {
				finished = true;
			}
			break;
		case 10:
			if (battle.timer == 1) {
				Dialog_Run(779);
			}
			if (battle.timer == 65) {
				int damage = 256;
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Audio_PlaySoundInterrupt(SND_hit2);
				
				snprintf(game.textBuffer, 16, "%d", damage);
				Battle_CreateLabel(0, game.textBuffer, battle.battleEventFighter->x, battle.battleEventFighter->y - 32);
				
				Fighter_TakeDamage(battle.battleEventFighter, NULL, damage, 0);
			}
			if (battle.timer == 135) {
				battle.battleEventFighter->state = FIGHTER_STATE_DOWN;
				finished = true;
			}
			break;
		case 11:
			if (battle.timer == 1) {
				battle.backgroundId = 8;
				Audio_RemoveSoundFilter();
				game.frameskip = 0;
				Audio_StopMusic();
				battle.battleEventVars[1] = 999;
				battle.battleEventFighter->facing = FACING_RIGHT;
			}
			if (battle.timer == 60) {
				Audio_PlaySound(SND_gatedefeat);
			}
			if (battle.timer >= 61 && battle.timer < 360) {
				Battle_ShakeScreen(2 + (battle.timer - 61) / 155 * 3);
				if (battle.timer % 36 == 1) {
					battle.battleEventFighter->spriteId = SPR_misc_hellgateboss_off;
				}
				else if (battle.timer % 43 == 7) {
					battle.battleEventFighter->spriteId = -1;
				}
			}
			if (battle.timer == 360) {
				battle.battleEventFighter->spriteId = SPR_misc_hellgateboss_off;
			}
			if (battle.timer == 460) {
				Dialog_Run(3131);
				battle.battleEventDialogWait = false;
			}
			if (battle.timer == 640) {
				Dialog_Continue();
				Audio_PlayMusic(MUS_brilliant3);
				battle.battleEventDialogWait = true;
			}
			if (battle.timer == 641) {
				profile.flags[FLAG_ILLUSION_GATE_DEFEATED] = 1;
				finished = true;
			}
			break;
		case 12:
			if (battle.timer == 1) {
				Dialog_Run(2181);
				battle.battleEventFighter->state = FIGHTER_STATE_SPECIAL1;
				battle.battleEventFighter->canAct = false;
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 13:
			if (battle.timer == 1) {
				Dialog_Run(2182);
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
			}
			if (battle.timer == 2) {
				battle.battleEventFighter->state = FIGHTER_STATE_IDLE;
				finished = true;
			}
			break;
		case 14:
			if (battle.timer == 1) {
				battle.battleEventFighter->state = FIGHTER_STATE_SPECIAL1;
				battle.battleEventFighter->canAct = false;
				battle.timer = 2;
				switch (battle.battleEventFighter->headId) {
					case 1: battle.timer = 11; break;
					case 2: battle.timer = 21; break;
					case 3: battle.timer = 31; break;
					case 4: battle.timer = 41; break;
				}
			}
			
			if (battle.timer == 2) {
				finished = true;
			}
			
			if (battle.timer == 11) {
				Dialog_Run(2217);
			}
			else if (battle.timer == 12) {
				finished = true;
			}
			
			if (battle.timer == 21) {
				Dialog_Run(2218 + (profile.flags[FLAG_ARMOR_BRIAN_BATTLES] % 2));
			}
			else if (battle.timer == 22) {
				finished = true;
			}
			
			if (battle.timer == 31) {
				Dialog_Run(2220 + (profile.flags[FLAG_ARMOR_BRIAN_BATTLES] % 2));
			}
			else if (battle.timer == 32) {
				finished = true;
			}
			
			if (battle.timer == 41) {
				Dialog_Run(2222 + (profile.flags[FLAG_ARMOR_BRIAN_BATTLES] % 2));
			}
			else if (battle.timer == 42) {
				finished = true;
			}
			break;
		case 15:
			if (battle.timer == 1) {
				Dialog_Run(37);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 16:
			if (battle.timer == 1) {
				Dialog_Run(38);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 17:
			if (battle.timer == 1) {
				battle.state = BATTLE_STATE_END;
				battle.timer = 4;
			}
			break;
		case 18:
			if (battle.timer == 1) {
				Dialog_Run(2570);
			}
			if (battle.timer == 2) {
				profile.flags[FLAG_AMPERCORP_PBSUPERHERO_DIALOG] = 8;
				battle.state = BATTLE_STATE_END;
				battle.timer = 4;
			}
			break;
		case 19:
			if (battle.timer == 1) {
				Dialog_Run(2644);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 20:
			if (battle.timer == 1) {
				Dialog_Run(2645);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 21:
			if (battle.timer == 1) {
				battle.battleEventVars[0] = 1;
			}
			if (battle.timer == 4) {
				Audio_PlaySound(SND_explode);
				battle.battleEventFighter->flinchTicks = 18;
				Battle_ShakeScreen(10);
			}
			if (battle.timer == 75 || battle.timer == 185 || battle.timer == 210 || battle.timer == 317) {
				Audio_PlaySound(SND_explode);
				Battle_ShakeScreen(4);
			}
			if (battle.timer >= 75 && battle.timer < 471 && battle.timer % 4 == 0) {
				battle.battleEventFighter->flinchTicks = 6;
			}
			if (battle.timer == 491) {
				Audio_PlaySound(SND_firemassattack);
			}
			if (battle.timer == 515) {
				Audio_PlaySound(SND_nerf);
				Audio_FadeOutMusic(4000);
				battle.battleEventFighter->y -= 10000;
				battle.battleEventFighter->yStart -= 10000;
			}
			
			if (battle.timer == 816) {
				finished = true;
			}
			break;
		case 22:
			if (battle.timer == 1) {
				Dialog_Run(2648);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 23:
			if (battle.timer == 1) {
				Dialog_Run(2646);
			}
			if (battle.timer == 2) {
				Dialog_Run(2647);
			}
			if (battle.timer == 3) {
				finished = true;
			}
			break;
		case 24:
			if (battle.timer == 1) {
				Audio_FadeOutMusic(3000);
			}
			if (battle.timer == 181) {
				Dialog_Run(2649);
			}
			if (battle.timer == 182) {
				battle.state = BATTLE_STATE_END;
				battle.timer = 4;
			}
			break;
		case 25:
			if (battle.timer == 1) {
				Audio_StopMusic();
				battle.battleEventFighter->spriteId = SPR_misc_helltree_collapsed;
			}
			if (battle.timer >= 146 && battle.timer <= 289 && battle.timer % 13 == 0) {
				Battle_CreateSpark(7, battle.battleEventFighter->x + Random_IRange(-80, 80), battle.battleEventFighter->y + Random_IRange(-120, 40), 0);
				Audio_PlaySound(SND_explode);
				Battle_ShakeScreen(10);
			}
			if (battle.timer == 290) {
				Battle_CreateSpark(7, battle.battleEventFighter->x - 72, battle.battleEventFighter->y, 0);
				Battle_CreateSpark(7, battle.battleEventFighter->x, battle.battleEventFighter->y, 0);
				Battle_CreateSpark(7, battle.battleEventFighter->x + 72, battle.battleEventFighter->y, 0);
				Audio_PlaySound(SND_firemassattack);
				Battle_ShakeScreen(20);
				battle.battleEventFighter->y -= 10000;
				battle.battleEventFighter->spriteId = -1;
			}
			if (battle.timer == 485) {
				battle.state = BATTLE_STATE_END;
				battle.timer = 4;
			}
			break;
		case 26:
			if (battle.timer == 1) {
				Dialog_Run(1536);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 27:
			if (battle.timer == 1) {
				Dialog_Run(1537);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 28:
			if (battle.timer == 1) {
				Dialog_Run(1538);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 29:
			if (battle.timer == 1) {
				Dialog_Run(1541);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 30:
			if (battle.timer == 1) {
				Dialog_Run(1542);
			}
			if (battle.timer == 2) {
				Dialog_Run(1543);
			}
			if (battle.timer == 3) {
				finished = true;
			}
			break;
		case 31:
			if (battle.timer == 1) {
				Dialog_Run(1544);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 32:
			if (battle.timer == 1) {
				Dialog_Run(1539);
			}
			if (battle.timer == 2) {
				Dialog_Run(1540);
			}
			if (battle.timer == 3) {
				finished = true;
			}
			break;
		case 33:
			if (battle.timer == 1) {
				Dialog_Run(1545);
			}
			if (battle.timer == 2) {
				Dialog_Run(1546);
			}
			if (battle.timer == 3) {
				finished = true;
			}
			break;
		case 34:
			if (battle.timer == 1) {
				Dialog_Run(1547);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 35:
			if (battle.timer == 1) {
				Dialog_Run(1548);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 36:
			if (battle.timer == 1) {
				Dialog_Run(1549);
			}
			if (battle.timer == 2) {
				battle.fighters[0].state = FIGHTER_STATE_ATTACK1;
				Dialog_Run(1550);
			}
			if (battle.timer == 3) {
				Dialog_Run(1551);
			}
			if (battle.timer == 4) {
				finished = true;
			}
			break;
		case 37:
			if (battle.timer == 1) {
				Dialog_Run(1552);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 38:
			if (battle.timer == 1) {
				Dialog_Run(1553);
			}
			if (battle.timer == 2) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
			}
			if (battle.timer == 14) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK3;
				Audio_PlaySound(SND_menu1);
			}
			if (battle.timer == 115) {
				battle.battleEventFighter->state = FIGHTER_STATE_IDLE;
				Dialog_Run(1554);
			}
			if (battle.timer == 116) {
				finished = true;
			}
			break;
		case 39:
			if (battle.timer == 1) {
				Dialog_Run(2663);
			}
			if (profile.flags[FLAG_ALONE]) {
				if (battle.timer == 2) {
					finished = true;
				}
			}
			else {
				if (battle.timer == 2) {
					Dialog_Run(2664);
				}
				if (battle.timer == 3) {
					Dialog_Run(2665);
				}
				if (battle.timer == 4) {
					finished = true;
				}
			}
			break;
		case 40:
			if (battle.timer == 1) {
				Dialog_Run(2666);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 41:
			if (battle.timer == 1) {
				Dialog_Run(1651);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 42:
			if (battle.timer == 1) {
				Dialog_Run(1652);
			}
			if (battle.timer == 2) {
				Dialog_Run(1655);
			}
			if (battle.timer == 3) {
				finished = true;
			}
			break;
		case 43:
			if (battle.timer == 1) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				Dialog_Run(1653);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 44:
			if (battle.timer == 1) {
				Dialog_Run(1654);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 45:
			if (battle.timer == 1) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				Dialog_Run(1656);
			}
			if (battle.timer == 2) {
				Dialog_Run(1657);
			}
			if (battle.timer == 3) {
				Dialog_Run(1658);
			}
			if (battle.timer == 4) {
				finished = true;
			}
			break;
		case 46:
			if (battle.timer == 1) {
				Dialog_Run(1659);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 47:
			if (battle.timer == 1) {
				Dialog_Run(1660);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 48:
			if (battle.timer == 1) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				Dialog_Run(1661);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 49:
			if (battle.timer == 1) {
				Audio_FadeOutMusic(2000);
			}
			if (battle.timer == 300) {
				finished = true;
			}
			break;
		case 50:
			if (battle.timer == 1) {
				Audio_FadeOutMusic(3000);
				battle.battleEventVars[1] = 0;
			}
			if (battle.timer == 251) {
				Audio_StopMusic();
			}
			if (battle.timer >= 251 && battle.timer < 394) {
				if (PlayerButtonPressed(PLAYER_BUTTON_Z) || PlayerButtonPressed(PLAYER_BUTTON_X)) {
					battle.battleEventVars[1] = 1;
				}
				if (battle.timer >= 320 && battle.battleEventVars[1] == 1) {
					battle.battleEventVars[1] = 0;
					battle.timer = 394;
				}
			}
			if (battle.timer == 395) {
				Audio_PlayMusic(MUS_bin);
			}
			if (battle.timer >= 785 && battle.timer < 1239) {
				if (PlayerButtonPressed(PLAYER_BUTTON_Z) || PlayerButtonPressed(PLAYER_BUTTON_X)) {
					battle.battleEventVars[1]++;
				}
				if (battle.timer >= Max(890, 1240 - battle.battleEventVars[1] * 15) && battle.battleEventVars[1] >= 1) {
					battle.battleEventVars[1] = 0;
					battle.timer = 1239;
				}
			}
			if (battle.timer == 1240) {
				Audio_PlaySound(SND_introwakeup);
			}
			if (battle.timer >= 1240 && battle.timer < 1490 && battle.timer % 4 == 0) {
				Audio_PlaySound(SND_explode);
				Battle_CreateSpark(13, Random_Range(16, SCREEN_WIDTH / 3), SCREEN_HEIGHT, 0);
				Battle_CreateSpark(13, Random_Range(SCREEN_WIDTH / 2, SCREEN_WIDTH * 2 / 3), SCREEN_HEIGHT, 0);
				Battle_CreateSpark(13, Random_Range(SCREEN_WIDTH * 2 / 3, SCREEN_WIDTH - 16), SCREEN_HEIGHT, 0);
			}
			if (battle.timer == 1540) {
				Audio_StopMusic();
				Audio_PlaySound(SND_subspace_transform);
				
				PartyMember* partyMember = &partyMembers[0];
				
				partyMember->headId = 86;
				partyMember->defaultArmorId = 10;
				partyMember->tiredThreshold = 0x1fff1fff;
				partyMember->hpDamage = 0;
				partyMember->tiredness = 0;
				partyMember->tiredLevel = 0;
				
				partyMember->starter.hpMax = 5700;
				partyMember->starter.mpMax = 850;
				partyMember->starter.attack = 65;
				partyMember->starter.defense = 8;
				partyMember->starter.speed = 95;
				
				partyMember->growth.hpMax = 551;
				partyMember->growth.mpMax = 112;
				partyMember->growth.attack = 66;
				partyMember->growth.defense = 8;
				partyMember->growth.speed = 68;
				
				Profile_UnequipAll(0);
				
				Profile_AddAction(176, 1);
				Profile_AddAction(177, 1);
				Profile_AddAction(179, 1);
				Profile_AddAction(180, 1);
				Profile_AddAction(181, 1);
				Profile_AddAction(182, 1);
				
				Profile_EquipAction(0, 176);
				Profile_EquipAction(0, 177);
				Profile_EquipAction(0, 179);
				Profile_EquipAction(0, 180);
				Profile_EquipAction(0, 181);
				Profile_EquipAction(0, 182);
				
				battle.fighters[0].enabled = false;
				Battle_CreateFighter(1, 0);
				{
					Fighter* fighter = &battle.fighters[0];
					fighter->speedRoll = fighter->speed;
					fighter->speedRollMin = fighter->speedRoll - 3;
					fighter->speedRollMax = fighter->speedRoll + 3;
					
					if (fighter->speedRollMin < 1) fighter->speedRollMin = 1;
					if (fighter->speedRollMax < 1) fighter->speedRollMax = 1;
					
					fighter->speedRoll = Random_IRange(fighter->speedRollMin, fighter->speedRollMax);
				}
				
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				
				profile.flags[FLAG_RUBY_GODMODE] = 1;
			}
			if (battle.timer >= 1540 && battle.timer < 1679) {
				if (PlayerButtonPressed(PLAYER_BUTTON_Z) || PlayerButtonPressed(PLAYER_BUTTON_X)) {
					battle.battleEventVars[1] = 1;
				}
				if (battle.timer >= 1570 && battle.battleEventVars[1] == 1) {
					battle.battleEventVars[1] = 0;
					battle.timer = 1679;
				}
			}
			if (battle.timer == 1740) {
				Audio_PlayMusic(MUS_lastresort);
			}
			if (battle.timer == 2220) {
				battle.battleEventFighter->state = FIGHTER_STATE_IDLE;
				Dialog_Run(1676);
			}
			if (battle.timer == 2221) {
				Dialog_Run(1677);
			}
			if (battle.timer == 2222) {
				finished = true;
			}
			break;
		case 51:
			if (battle.timer == 1) {
				Audio_FadeOutMusic(1000);
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Dialog_Run(1679);
			}
			if (battle.timer == 55) {
				Dialog_Run(1680);
			}
			if (battle.timer == 56) {
				Dialog_Run(1681);
			}
			if (battle.timer == 107) {
				Audio_PlayMusic(MUS_risk);
				battle.battleEventFighter->spriteId = SPR_misc_lulu_god_rage;
				battle.battleEventFighter->spriteFrame = 0;
			}
			if (battle.timer == 118) {
				Dialog_Run(1683);
			}
			if (battle.timer == 119) {
				Dialog_Run(1682);
			}
			if (battle.timer >= 120 && battle.timer < 180) {
				if (battle.timer % 12 == 0) {
					battle.battleEventFighter->x = battle.battleEventFighter->xStart - 2;
				}
				else if (battle.timer % 12 == 6) {
					battle.battleEventFighter->x = battle.battleEventFighter->xStart + 2;
				}
			}
			if (battle.timer == 180) {
				Audio_PlaySound(SND_introwakeup);
				battle.battleEventFighter->x = battle.battleEventFighter->xStart;
				battle.battleEventFighter->spriteFrame = 1;
			}
			if (battle.timer >= 180 && battle.timer <= 540) {
				if (battle.timer % 20 == 0) {
					Audio_PlaySound(SND_burn);
				}
				if (battle.timer >= 330 && battle.timer % 8 == 0) {
					Audio_PlaySound(SND_explode);
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				if (battle.timer >= 420 && battle.timer % 8 == 4) {
					Audio_PlaySound(SND_explode);
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				if (battle.timer % 10 == 0) {
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				Battle_ShakeScreen(1 + (battle.timer - 180) / 30);
			}
			if (battle.timer == 570) {
				Audio_StopMusic();
				Audio_PlaySound(SND_firemassattack);
				
				battle.fighters[8].enabled = false;
				Battle_CreateFighter(107, 1);
				{
					Fighter* fighter = &battle.fighters[8];
					fighter->speedRoll = fighter->speed;
					fighter->speedRollMin = fighter->speedRoll - 3;
					fighter->speedRollMax = fighter->speedRoll + 3;
					
					if (fighter->speedRollMin < 1) fighter->speedRollMin = 1;
					if (fighter->speedRollMax < 1) fighter->speedRollMax = 1;
					
					fighter->speedRoll = Random_IRange(fighter->speedRollMin, fighter->speedRollMax);
				}
				Fighter_ClearAllStatus(&battle.fighters[0]);
			}
			if (battle.timer == 900) {
				Audio_PlayMusic(MUS_ultboss);
				battle.battleEventVars[0] = 0;
				battle.turnCount = 1;
				battle.backgroundId = 20;
			}
			if (battle.timer == 1305) {
				Dialog_Run(1684);
			}
			if (battle.timer == 1306) {
				finished = true;
			}
			break;
		case 52:
			if (battle.timer == 1) {
				Dialog_Run(1678);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 53:
			if (battle.timer == 1) {
				Dialog_Run(1685);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 54:
			if (battle.timer == 1) {
				Dialog_Run(1686);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 55:
			if (battle.timer == 1) {
				Audio_FadeOutMusic(2000);
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
			}
			if (battle.timer == 111) {
				Audio_PlaySound(SND_poison);
				battle.battleEventFighter->spriteId = SPR_misc_lulu_ultimate_stagger;
				battle.battleEventFighter->spriteFrame = 0;
			}
			if (battle.timer == 160) {
				Dialog_Run(1687);
			}
			if (battle.timer == 161) {
				Dialog_Run(1688);
			}
			if (battle.timer == 225) {
				battle.battleEventFighter->state = FIGHTER_STATE_IDLE;
				battle.battleEventFighter->spriteId = -1;
				Dialog_Run(1689);
			}
			if (battle.timer == 226) {
				Audio_PlayMusic(MUS_ultboss_shortpre);
				battle.battleEventFighter->spriteId = SPR_misc_lulu_ultimate_rage;
				battle.battleEventFighter->spriteFrame = 0;
			}
			if (battle.timer == 334) {
				Dialog_Run(1690);
			}
			if (battle.timer == 335) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				battle.battleEventFighter->spriteId = -1;
				Dialog_Run(1691);
			}
			if (battle.timer == 336) {
				Audio_PlaySound(SND_swing);
				Audio_PlaySound(SND_beamsword);
				Audio_PlaySound(SND_thunder);
				battle.fighters[0].state = FIGHTER_STATE_ATTACK3;
			}
			if (battle.timer == 346) {
				Audio_StopMusic();
				Audio_PlaySound(SND_hit1);
				battle.battleEventFighter->spriteId = SPR_misc_lulu_ultimate_rage;
				battle.battleEventFighter->spriteFrame = 0;
				Fighter_MoveTo(battle.battleEventFighter, battle.battleEventFighter->x + 56, battle.battleEventFighter->y, 4, 0);
			}
			if (battle.timer == 348) {
				Battle_ShakeScreen(18);
				Audio_PlaySound(SND_crusherhit2);
			}
			if (battle.timer == 404) {
				battle.battleEventFighter->spriteId = SPR_misc_lulu_ultimate_stagger;
				battle.battleEventFighter->spriteFrame = 0;
			}
			if (battle.timer == 455) {
				battle.fighters[0].state = FIGHTER_STATE_IDLE;
				Dialog_Run(1692);
			}
			if (battle.timer == 456) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				battle.battleEventFighter->spriteId = -1;
				Dialog_Run(1693);
			}
			if (battle.timer == 457) {
				battle.fighters[0].state = FIGHTER_STATE_HURT;
				Dialog_Run(1694);
			}
			if (battle.timer == 458) {
				Audio_PlayMusic(MUS_ultboss_short);
				battle.battleEventFighter->spriteId = SPR_misc_lulu_ultimate_rage;
				battle.battleEventFighter->spriteFrame = 1;
				Battle_ShakeScreen(20);
				Dialog_Run(1695);
			}
			if (battle.timer == 459) {
				battle.fighters[0].state = FIGHTER_STATE_IDLE;
				Dialog_Run(1696);
				battle.battleEventDialogWait = false;
			}
			if (battle.timer == 494) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				battle.battleEventFighter->spriteId = -1;
			}
			if (battle.timer == 503) {
				Battle_CreateSpark(20, battle.battleEventFighter->x, battle.battleEventFighter->y - 40, 0);
				Audio_PlaySound(SND_ultimateskill);
				battle.battleEventFighter->state = FIGHTER_STATE_BLOCK;
			}
			if (battle.timer == 568) {
				Fighter_MoveTo(battle.battleEventFighter, battle.fighters[0].x - battle.battleEventFighter->facing * 32, battle.fighters[0].y, 12, 0);
				battle.battleEventFighter->state = FIGHTER_STATE_SPECIAL1;
			}
			if (battle.timer == 569 && battle.battleEventFighter->moveTarget.enabled) battle.timer--;
			
			if (battle.timer == 578) {
				battle.battleEventDialogWait = true;
				dialogSystem.state = DIALOG_STATE_IDLE;
				dialogSystem.textLength = 0;
				
				Audio_StopAllSounds();
				Audio_StopMusic();
				Audio_PlaySound(SND_firemassattack);
				Audio_PlaySound(SND_hit3);
				Audio_PlaySound(SND_crusherhit2);
				Battle_CreateSpark(16, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0);
				Battle_CreateSpark(21, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0);
				
				battle.fighters[0].state = FIGHTER_STATE_BLOCK;
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
			}
			if (battle.timer == 685) {
				Audio_PlaySound(SND_hit2);
				
				Battle_CreateSpark(14, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0);
				Battle_CreateSpark(21, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0);
				battle.fighters[0].state = FIGHTER_STATE_ATTACK3;
				Fighter_MoveTo(battle.battleEventFighter, 616, battle.battleEventFighter->yStart, 56, 0);
			}
			if (battle.timer == 686 && battle.battleEventFighter->moveTarget.enabled) battle.timer--;
			if (battle.timer == 687) {
				Audio_PlaySound(SND_hit3);
				
				battle.battleEventFighter->spriteId = SPR_misc_lulu_ultimate_stagger;
				battle.battleEventFighter->spriteFrame = 0;
				Fighter_MoveTo(battle.battleEventFighter, battle.battleEventFighter->xStart, battle.battleEventFighter->yStart, 18, 0);
				
				battle.battleEventVars[1] = 0;
			}
			
			if (battle.timer >= 768 && battle.timer < 1128) {
				if ((battle.timer - 768) % 18 < 13) {
					if (PlayerButtonPressed(PLAYER_BUTTON_Z) || PlayerButtonPressed(PLAYER_BUTTON_X)) {
						battle.battleEventVars[1] = 1;
					}
				}
				
				if ((battle.timer - 768) % 18 == 0) {
					Audio_PlaySound(SND_swing);
					Audio_PlaySound(SND_beamsword);
					Audio_PlaySound(SND_thunder);
					battle.fighters[0].state = ((battle.timer - 768) % 36 == 0) ? FIGHTER_STATE_ATTACK2 : FIGHTER_STATE_ATTACK3;
				}
				else if ((battle.timer - 768) % 18 == 10) {
					Audio_PlaySound(SND_hit3);
					battle.battleEventFighter->flinchTicks = 24;
					Battle_CreateSpark(21, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0);
				}
				else if ((battle.timer - 768) % 18 == 12) {
					Battle_ShakeScreen(18);
					Audio_PlaySound(SND_crusherhit2);
				}
				else if ((battle.timer - 768) % 18 >= 13 && (battle.timer - 768) % 18 < 17 && battle.battleEventVars[1] == 1) {
					battle.battleEventVars[1] = 0;
					battle.timer += 17 - (battle.timer - 768) % 18;
				}
			}
			if (battle.timer == 1140) {
				Audio_PlaySound(SND_swing);
				Audio_PlaySound(SND_beamsword);
				Battle_CreateSpark(16, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0);
			}
			if (battle.timer == 1250) {
				Audio_PlaySound(SND_firemassattack);
				Audio_PlaySound(SND_gunfire2);
				Audio_PlaySound(SND_gunfire2);
				Battle_CreateSpark(21, battle.battleEventFighter->x + 8, battle.battleEventFighter->y - 24, 0);
				Battle_CreateSpark(21, battle.battleEventFighter->x - 32, battle.battleEventFighter->y - 64, 0);
				Battle_CreateSpark(21, battle.battleEventFighter->x - 32, battle.battleEventFighter->y + 16, 0);
			}
			
			if (battle.timer == 1600) {
				battle.timer = 1;
				Battle_Update_End();
				dialogSystem.state = DIALOG_STATE_IDLE;
				dialogSystem.textLength = 0;
				
				Party_GainExp(0, battle.expEarned);
				
				battle.state = BATTLE_STATE_END;
				battle.timer = 34;
			}
			break;
		case 56:
			if (battle.timer == 1) {
				Audio_StopMusic();
				battle.battleEventFighter->spriteId = SPR_misc_helltree_collapsed;
			}
			if (battle.timer == 2) {
				Battle_CreateSpark(7, battle.battleEventFighter->x - 72, battle.battleEventFighter->y, 0);
				Battle_CreateSpark(7, battle.battleEventFighter->x, battle.battleEventFighter->y, 0);
				Battle_CreateSpark(7, battle.battleEventFighter->x + 72, battle.battleEventFighter->y, 0);
				Audio_PlaySound(SND_explode);
				Audio_PlaySound(SND_firemassattack);
				Audio_PlaySound(SND_subspace_transform);
				Battle_ShakeScreen(90);
				battle.battleEventFighter->y -= 10000;
				battle.battleEventFighter->spriteId = -1;
			}
			if (battle.timer == 287) {
				battle.state = BATTLE_STATE_END;
				battle.timer = 34;
			}
			break;
		case 57:
			if (battle.timer == 1) {
				Audio_FadeOutMusic(4000);
			}
			if (battle.timer == 720) {
				battle.state = BATTLE_STATE_END;
				battle.timer = 34;
			}
			break;
		
		case 191:
			if (battle.timer == 1) {
				Audio_FadeOutMusic(2000);
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Dialog_Run(578);
			}
			if (battle.timer == 2) {
				Audio_PlayMusic(MUS_bin);
				battle.battleEventFighter->spriteId = SPR_misc_lulu_omega_rage;
				battle.battleEventFighter->spriteFrame = 0;
				Dialog_Run(579);
			}
			if (battle.timer == 118) {
				Dialog_Run(580);
			}
			if (battle.timer == 119) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				Dialog_Run(581);
			}
			if (battle.timer >= 120 && battle.timer < 180) {
				if (battle.timer % 12 == 0) {
					battle.battleEventFighter->x = battle.battleEventFighter->xStart - 2;
				}
				else if (battle.timer % 12 == 6) {
					battle.battleEventFighter->x = battle.battleEventFighter->xStart + 2;
				}
			}
			if (battle.timer == 180) {
				Audio_PlaySound(SND_introwakeup);
				battle.battleEventFighter->x = battle.battleEventFighter->xStart;
				battle.battleEventFighter->spriteFrame = 1;
			}
			if (battle.timer >= 180 && battle.timer <= 540) {
				if (battle.timer % 20 == 0) {
					Audio_PlaySound(SND_burn);
				}
				if (battle.timer >= 330 && battle.timer % 8 == 0) {
					Audio_PlaySound(SND_explode);
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				if (battle.timer >= 420 && battle.timer % 8 == 4) {
					Audio_PlaySound(SND_explode);
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				if (battle.timer % 10 == 0) {
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				Battle_ShakeScreen(1 + (battle.timer - 180) / 30);
			}
			if (battle.timer == 570) {
				Audio_StopMusic();
				Audio_PlaySound(SND_firemassattack);
				
				battle.battleEventFighter->hp = 1500;
				battle.battleEventFighter->hpMax = 1500;
				battle.battleEventFighter->mp = 1000;
				battle.battleEventFighter->mpMax = 1000;
				battle.battleEventFighter->attack = 70;
				battle.battleEventFighter->defense = 80;
				battle.battleEventFighter->speed = 120;
				
				for (int i = 0; i < 32; i++) {
					battle.battleEventFighter->status[i] = 0;
					battle.battleEventFighter->statusNext[i] = 0;
				}
			}
			if (battle.timer == 720) {
				battle.battleEventFighter->spriteId = -1;
				
				Audio_PlayMusic(MUS_lastresort);
				battle.battleEventVars[0] = 1;
			}
			if (battle.timer == 1200) {
				finished = true;
			}
			break;
		case 192:
			if (battle.timer == 1) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				Dialog_Run(577);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 193:
			if (battle.timer == 1) {
				Dialog_Run(582);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 194:
			if (battle.timer == 1) {
				Dialog_Run(583);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		case 195:
			if (battle.timer == 1) {
				Dialog_Run(585);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		
		case 196:
			if (battle.timer == 1) {
				Audio_StopMusic();
				battle.battleEventFighter->state = FIGHTER_STATE_HURT;
				Dialog_Run(578);
			}
			if (battle.timer == 2) {
				Audio_PlayMusic(MUS_bin);
				battle.battleEventFighter->spriteId = SPR_misc_lulu_omega_rage;
				battle.battleEventFighter->spriteFrame = 0;
				Dialog_Run(579);
			}
			if (battle.timer == 118) {
				Dialog_Run(580);
			}
			if (battle.timer == 119) {
				battle.battleEventFighter->state = FIGHTER_STATE_ATTACK1;
				Dialog_Run(581);
			}
			if (battle.timer >= 120 && battle.timer < 180) {
				if (battle.timer % 12 == 0) {
					battle.battleEventFighter->x = battle.battleEventFighter->xStart - 2;
				}
				else if (battle.timer % 12 == 6) {
					battle.battleEventFighter->x = battle.battleEventFighter->xStart + 2;
				}
			}
			if (battle.timer == 180) {
				Audio_PlaySound(SND_introwakeup);
				battle.battleEventFighter->x = battle.battleEventFighter->xStart;
				battle.battleEventFighter->spriteFrame = 1;
			}
			if (battle.timer >= 180 && battle.timer <= 240) {
				if (battle.timer % 10 == 0) {
					Audio_PlaySound(SND_burn);
				}
				if (battle.timer % 10 == 0) {
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				Battle_ShakeScreen(1);
			}
			if (battle.timer == 244) {
				Audio_PlayMusic(MUS_lastresort2);
			}
			if (battle.timer >= 260 && battle.timer <= 940) {
				if (battle.timer % 20 == 0 && battle.timer <= 320) {
					Audio_PlaySound(SND_burn);
				}
				if (battle.timer >= 330 && battle.timer % 180 == 150) {
					Audio_PlaySound(SND_subspace_transform);
				}
				if (battle.timer >= 330 && battle.timer % 32 == 0) {
					Audio_PlaySound(SND_explode);
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
					for (int i = 0; i < 5; i++) {
						Battle_CreateSpark(9906, Random_Range(0, 640), 480, 0);
					}
				}
				if (battle.timer >= 600 && battle.timer % 8 == 4) {
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
					for (int i = 0; i < 5; i++) {
						Battle_CreateSpark(9907, 20 + i * 150, 480, 0);
					}
					for (int i = 0; i < 3; i++) {
						Battle_CreateSpark(9907, battle.battleEventFighter->x - 48 + i * 32, 480, 0);
					}
				}
				if (battle.timer % 10 == 0) {
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				if (battle.timer >= 350 && battle.timer % 50 == 0) {
					Battle_CreateSpark(9908, battle.battleEventFighter->x, battle.battleEventFighter->y + 32, 0);
				}
				Battle_ShakeScreen(1 + (battle.timer - 180) / 60);
			}
			if (battle.timer == 950) {
				battle.backgroundId = 15;
				Audio_StopMusic();
				Audio_PlaySound(SND_firemassattack);
				Audio_PlaySound(SND_subspace_transform);
				
				SetString(battle.battleEventFighter->name, "SD Lulu");
				battle.battleEventFighter->hp = 50000;
				battle.battleEventFighter->hpMax = 50000;
				battle.battleEventFighter->mp = 8000;
				battle.battleEventFighter->mpMax = 8000;
				battle.battleEventFighter->attack = 200;
				battle.battleEventFighter->defense = 220;
				battle.battleEventFighter->speed = 350;
				
				battle.battleEventFighter->headId = 60;
				battle.battleEventFighter->bodyId = 70;
				battle.battleEventFighter->state = FIGHTER_STATE_IDLE;
				battle.battleEventFighter->spriteId = SPR_misc_lulu_subspace_rage;
				battle.battleEventFighter->spriteFrame = 0;
				
				for (int i = 0; i < 32; i++) {
					battle.battleEventFighter->status[i] = 0;
					battle.battleEventFighter->statusNext[i] = 0;
				}
			}
			if (battle.timer >= 960 && battle.timer <= 1290) {
				if (battle.timer % 20 == 0) {
					Audio_PlaySound(SND_burn);
				}
				if (battle.timer == 960) {
					Audio_PlaySound(SND_subspace_transform2);
				}
				if (battle.timer % 90 == 80) {
					Audio_PlaySound(SND_subspace_transform);
				}
				if (battle.timer % 6 == 0) {
					Audio_PlaySound(SND_explode);
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
					for (int i = 0; i < 10; i++) {
						Battle_CreateSpark(9906, Random_Range(0, 640), 480, 0);
					}
				}
				if (battle.timer % 6 == 3) {
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
					for (int i = 0; i < 10; i++) {
						Battle_CreateSpark(9907, Random_Range(0, 10) + i * 70, 480, 0);
						Battle_CreateSpark(9907, battle.battleEventFighter->x - 72 + i * 16, 480, 0);
					}
				}
				if (battle.timer % 10 == 0) {
					Battle_CreateSpark(9905, battle.battleEventFighter->x + Random_Range(-48, 48), battle.battleEventFighter->y + Random_Range(-64, 32), 0);
				}
				Battle_ShakeScreen(1 + (battle.timer - 180) / 60);
				if (battle.timer % 90 == 0 || battle.timer % 90 == 36) {
					Audio_PlaySound(SND_firemassattack);
					for (int i = 0; i < 5; i++) {
						Battle_CreateSpark(9908, 40 + i * 140, 480, 0);
					}
				}
			}
			if (battle.timer == 1300) {
				Audio_StopMusic();
				battle.battleEventFighter->spriteFrame = 1;
				
				Audio_PlaySound(SND_subspace_transform);
				Audio_PlaySound(SND_subspace_transform);
				battle.battleEventVars[0] = 1;
				Battle_ShakeScreen(90);
			}
			if (battle.timer >= 1301 && battle.timer <= 1970) {
				if (battle.timer % 8 == 0) {
					Audio_PlaySound(SND_explode);
					for (int i = 0; i < 4; i++) {
						Battle_CreateSpark(9907, Random_Range(0, 640), 480, 0);
					}
				}
				if (battle.timer >= 1480 && battle.timer % 16 == 1 && battle.timer <= 1800) {
					Audio_PlaySound(SND_explode);
					for (int i = 0; i < 32; i++) {
						Battle_CreateSpark(9907, Random_Range(0, 640), 480, 0);
					}
				}
				if (battle.timer == 1301) {
					Audio_PlaySound(SND_firemassattack);
					for (int i = 0; i < 5; i++) {
						Battle_CreateSpark(9908, 40 + i * 140, 480, 0);
					}
				}
				if (battle.timer == 1400 || battle.timer == 1432) {
					Audio_PlaySound(SND_firemassattack);
					for (int i = 0; i < 4; i++) {
						Battle_CreateSpark(9908, 50 + i * 180, 480, 0);
					}
					Battle_ShakeScreen(30);
				}
				if (battle.timer == 1416) {
					Audio_PlaySound(SND_firemassattack);
					for (int i = 0; i < 3; i++) {
						Battle_CreateSpark(9908, 120 + i * 200, 480, 0);
					}
					Battle_ShakeScreen(30);
				}
				if (battle.timer >= 1480 && battle.timer % 48 == 0 && battle.timer <= 1800) {
					Audio_PlaySound(SND_firemassattack);
					for (int i = 0; i < 5; i++) {
						Battle_CreateSpark(9908, 40 + i * 140, 480, 0);
					}
				}
			}
			if (battle.timer == 2100) {
				Audio_PlayMusic(MUS_battlepower);
				battle.battleEventFighter->spriteId = -1;
			}
			if (battle.timer == 2101) {
				Dialog_Run(2309);
			}
			if (battle.timer == 2102) {
				finished = true;
			}
			break;
		case 197:
			if (battle.timer == 1) {
				battle.backgroundId = 15;
				SetString(battle.battleEventFighter->name, "SD Lulu");
				battle.battleEventFighter->hp = 50000;
				battle.battleEventFighter->hpMax = 50000;
				battle.battleEventFighter->mp = 8000;
				battle.battleEventFighter->mpMax = 8000;
				battle.battleEventFighter->attack = 200;
				battle.battleEventFighter->defense = 220;
				battle.battleEventFighter->speed = 350;
				
				battle.battleEventFighter->headId = 60;
				battle.battleEventFighter->bodyId = 70;
				battle.battleEventFighter->state = FIGHTER_STATE_IDLE;
				battle.battleEventFighter->spriteId = SPR_misc_lulu_subspace_rage;
				battle.battleEventFighter->spriteFrame = 0;
				
				Audio_PlayMusic(MUS_battlepower);
				battle.battleEventFighter->spriteId = -1;
				finished = true;
				battle.battleEventVars[0] = 1;
			}
			break;
		
		case 999:
			if (battle.timer == 1) {
				Dialog_Run(3158);
			}
			if (battle.timer == 2) {
				finished = true;
			}
			break;
		default:
			finished = true;
			break;
	}
	
	if (finished) {
		if (battle.battleEventType == BATTLE_EVENT_TYPE_TURNEND) {
			battle.state = BATTLE_STATE_IDLE;
			battle.timer = -1;
		}
		else {
			battle.state = BATTLE_STATE_IDLE;
			battle.timer = 1;
		}
	}
}

void Battle_Draw_Event() {
	switch (battle.battleEventId) {
		case 5:
			if (battle.timer >= 240 && battle.timer < 420) {
				Fighter* fighter = &battle.fighters[8];
				DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, fighter->x - (float)(battle.timer - 240), fighter->y + (float)(battle.timer - 240) * 2, 2 + (float)(battle.timer - 240) / 4, 2 + (float)(battle.timer - 240) / 4, fighter->facing);
			}
			
			if (battle.timer >= 360 && battle.timer < 420) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_SetDrawAlpha((battle.timer - 360) * 255 / 60);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
				Drawer_SetDrawColor(255, 255, 255);
			}
			else if ((battle.timer >= 420 && battle.timer < 480) || battle.timer >= 1000) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
			}
			else if (battle.timer >= 480 && battle.timer < 540) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_SetDrawAlpha(255 - (battle.timer - 480) * 255 / 60);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
				Drawer_SetDrawColor(255, 255, 255);
			}
			break;
		case 10:
			if (battle.timer >= 5 && battle.timer < 65) {
				Drawer_DrawSprite_Angle(SPR_misc_sign_3, battle.battleEventFighter->x, battle.battleEventFighter->y - 32 - (65 - battle.timer) * 24, 0, 2, 2, -15);
			}
			else if (battle.timer >= 65 && battle.timer < 125) {
				Drawer_DrawSprite_Angle(SPR_misc_sign_3, battle.battleEventFighter->x - (battle.timer - 65) * 6, battle.battleEventFighter->y - 32 + (battle.timer - 75) * (battle.timer - 75) / 2 - 100, 0, 2, 2, -30 - (battle.timer - 65) * 10);
			}
			break;
		case 11:
			if (battle.timer >= 61 && battle.timer < 448) {
				Drawer_SetDrawBlend(BLENDMODE_MUL);
				Drawer_SetDrawColor(255 * (battle.timer % 126 < 42), 255 * (battle.timer % 126 >= 42 && battle.timer % 132 < 84), 255 * (battle.timer % 138 >= 84));
				Drawer_SetDrawAlpha(127);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
			}
			break;
		case 21:
			if (battle.timer == 4 || battle.timer == 5
			|| battle.timer == 75 || battle.timer == 76
			|| battle.timer == 185 || battle.timer == 186
			|| battle.timer == 210 || battle.timer == 211
			|| battle.timer == 317 || battle.timer == 318) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			
			if (battle.timer >= 451 && battle.timer < 652) {
				if (battle.timer >= 450 && battle.timer < 471)
					Drawer_SetDrawAlpha((battle.timer - 449) * 12);
				else if (battle.timer >= 621)
					Drawer_SetDrawAlpha(255 - (battle.timer - 620) * 8);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
			}
			break;
		case 50:
			if (battle.timer < 251) {
				
			}
			else if (battle.timer < 785) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
				if (battle.timer < 395) {
					Drawer_DrawSprite(SPR_owchar_collapse_ruby, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 8, 1, 2, 2);
				}
				else if (battle.timer < 625) {
					Drawer_DrawSprite(SPR_misc_ruby_suppressed, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 24, 1, 2, 2);
				}
				else if (battle.timer < 725) {
					Drawer_DrawSprite(SPR_misc_ruby_suppressed, SCREEN_WIDTH / 2 + ((battle.timer % 8 < 4) ? -1 : 1), SCREEN_HEIGHT / 2 + 24, 1, 2, 2);
				}
				else {
					Drawer_SetDrawAlpha(255 - (battle.timer - 725) * 255 / 60);
					Drawer_DrawSprite(SPR_misc_ruby_suppressed, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 24, 1, 2, 2);
					Drawer_SetDrawAlpha(255);
				}
			}
			else if (battle.timer < 1240) {
				Drawer_SetDrawColor(128 + (int)(sin((float)(battle.timer - 785) / 12) * 127), 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(0, 0, 0);
				if (battle.timer < 890) {
					Drawer_DrawSprite(SPR_misc_ruby_rage, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 24, 0, 2, 2);
				}
				else if (battle.timer < 1070) {
					Drawer_DrawSprite(SPR_misc_ruby_rage, SCREEN_WIDTH / 2 + ((battle.timer % 8 < 4) ? -2 : 2), SCREEN_HEIGHT / 2 + 24, 0, 2, 2);
				}
				else {
					Drawer_DrawSprite(SPR_misc_ruby_rage, SCREEN_WIDTH / 2 + ((battle.timer % 6 < 3) ? -4 : 4), SCREEN_HEIGHT / 2 + 24, 0, 2, 2);
				}
				Drawer_SetDrawColor(255, 255, 255);
			}
			else if (battle.timer < 1510) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_DrawSprite(SPR_misc_ruby_rage, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 24 + ((battle.timer % 4 < 2) ? -16 : 16), 1, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				if (battle.timer > 1360) {
					Drawer_SetDrawAlpha((battle.timer - 1360) * 255 / 150);
					Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
					Drawer_SetDrawAlpha(255);
				}
			}
			else if (battle.timer < 1680) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			else if (battle.timer < 1830) {
				Drawer_SetDrawAlpha(255 - (battle.timer - 1680) * 255 / 150);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
			}
			break;
		case 51:
			if (battle.timer < 540) {
				
			}
			else if (battle.timer < 720) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			else if (battle.timer < 840) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_SetDrawAlpha(255 - (battle.timer - 720) * 255 / 120);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
			}
			else if (battle.timer < 900) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
			}
			else if (battle.timer < 1030) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_SetDrawAlpha((battle.timer - 900) * 255 / 130);
				Drawer_DrawSprite(SPR_owchar_lulu_ultimate, battle.battleEventFighter->x, battle.battleEventFighter->y, 1, 2, 2);
				Drawer_SetDrawAlpha(255);
			}
			else if (battle.timer < 1267) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_DrawSprite(SPR_owchar_lulu_ultimate, battle.battleEventFighter->x, battle.battleEventFighter->y, 1, 2, 2);
			}
			else if (battle.timer < 1273) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_DrawSprite(SPR_owchar_lulu_ultimate, battle.battleEventFighter->x, battle.battleEventFighter->y, 2, -2, 2);
			}
			else if (battle.timer < 1303) {
				Drawer_SetDrawAlpha(255 - (battle.timer - 1273) * 255 / 30);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
				DrawFighterChar(battle.battleEventFighter->headId, battle.battleEventFighter->bodyId, battle.battleEventFighter->state, battle.battleEventFighter->x, battle.battleEventFighter->y, 2, 2, battle.battleEventFighter->facing);
			}
			break;
		case 55:
			if (battle.timer < 336) {
				
			}
			else if (battle.timer < 354) {
				Drawer_SetDrawColor(255, 0, 0);
				if (battle.timer < 340) {
					int x = battle.battleEventFighter->x;
					for (int y = battle.battleEventFighter->y; y > 128; y -= 2) {
						Drawer_SetDrawColor(159, 0, 0);
						Drawer_FillRect(x - 9, y - 1, 18, 2);
						Drawer_SetDrawColor(255, 0, 0);
						Drawer_FillRect(x - 5, y - 1, 10, 2);
						Drawer_SetDrawColor(255, 255, 255);
						Drawer_FillRect(x - 1, y - 1, 2, 2);
						x += Random_IRange(-1, 1) * 2;
					}
				}
				else if (battle.timer < 342) {
					Drawer_SetDrawAlpha(63);
					Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
					Drawer_SetDrawAlpha(255);
				}
				else if (battle.timer < 346) {
					Drawer_DrawSprite(SPR_spark_slashultra, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0, 2, 2);
				}
				else if (battle.timer < 350) {
					Drawer_DrawSprite(SPR_spark_slashultra, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 1, 2, 2);
				}
				else {
					Drawer_DrawSprite(SPR_spark_slashultra, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 2, 2, 2);
				}
				Drawer_SetDrawColor(255, 255, 255);
			}
			else if (battle.timer < 570) {
				
			}
			else if (battle.timer < 633) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-64, -64, SCREEN_WIDTH + 128, SCREEN_HEIGHT + 128);
				Drawer_SetDrawColor(255, 255, 255);
			}
			else if (battle.timer < 768) {
				
			}
			else if (battle.timer < 1128) {
				Drawer_SetDrawColor(255, 0, 0);
				if ((battle.timer - 768) % 18 < 6) {
					int x = battle.battleEventFighter->x;
					for (int y = battle.battleEventFighter->y; y > 128; y -= 2) {
						Drawer_SetDrawColor(159, 0, 0);
						Drawer_FillRect(x - 9, y - 1, 18, 2);
						Drawer_SetDrawColor(255, 0, 0);
						Drawer_FillRect(x - 5, y - 1, 10, 2);
						Drawer_SetDrawColor(255, 255, 255);
						Drawer_FillRect(x - 1, y - 1, 2, 2);
						x += Random_IRange(-1, 1) * 2;
					}
				}
				else if ((battle.timer - 768) % 18 < 9) {
					Drawer_SetDrawAlpha(63);
					Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
					Drawer_SetDrawAlpha(255);
				}
				else if ((battle.timer - 768) % 18 < 12) {
					Drawer_DrawSprite(SPR_spark_slashultra, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 0, 2, 2);
				}
				else if ((battle.timer - 768) % 18 < 15) {
					Drawer_DrawSprite(SPR_spark_slashultra, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 1, 2, 2);
				}
				else {
					Drawer_DrawSprite(SPR_spark_slashultra, battle.battleEventFighter->x, battle.battleEventFighter->y - 24, 2, 2, 2);
				}
				Drawer_SetDrawColor(255, 255, 255);
			}
			else {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-64, -64, SCREEN_WIDTH + 128, SCREEN_HEIGHT + 128);
				Drawer_SetDrawColor(255, 255, 255);
			}
			break;
		case 56:
			if (battle.timer < 2) {
				
			}
			else if (battle.timer < 17) {
				Drawer_SetDrawAlpha((battle.timer - 2) * 255 / 15);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			else if (battle.timer < 77) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			else if (battle.timer < 137) {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_SetDrawAlpha(255 - (battle.timer - 77) * 255 / 60);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
			}
			else {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
			}
			break;
		case 57:
			if (battle.timer < 2) {
				
			}
			else if (battle.timer < 302) {
				Drawer_SetDrawAlpha((battle.timer - 2) * 255 / 300);
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
			}
			else {
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawColor(255, 255, 255);
			}
			break;
		
		case 191:
			if (battle.timer >= 540 && battle.timer <= 720) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			else if (battle.timer > 720 && battle.timer <= 840) {
				Drawer_SetDrawAlpha(255 - (battle.timer - 720) * 255 / 120);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
			}
			break;
		
		case 196:
			if (battle.timer >= 950 && battle.timer <= 960) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			else if (battle.timer >= 960 && battle.timer <= 1300) {
				Drawer_SetDrawBlend(BLENDMODE_MUL);
				Drawer_SetDrawColor(191, 0, 63);
				Drawer_SetDrawAlpha(191 + (battle.timer % 16 < 8) * 32);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
			}
			else if (battle.timer >= 1300 && battle.timer <= 1304) {
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
			}
			else if (battle.timer >= 1305 && battle.timer <= 1940) {
				Drawer_SetDrawBlend(BLENDMODE_MUL);
				Drawer_SetDrawColor(191, 0, 0);
				Drawer_SetDrawAlpha((battle.timer % 56 < 28) * 223);
				Drawer_FillRect(-100, -100, SCREEN_WIDTH + 200, SCREEN_HEIGHT + 200);
				Drawer_SetDrawAlpha(255);
				Drawer_SetDrawColor(255, 255, 255);
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
			}
			break;
	}
}



void Battle_CreateFighter(int fighterId, int side) {
	int id = -1;
	if (side == 0) {
		for (int i = 0; i < 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) {
				id = i;
				break;
			}
		}
	}
	else {
		for (int i = 8; i < 16; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) {
				id = i;
				break;
			}
		}
	}
	
	if (id < 0) return;
	
	Fighter* fighter = &battle.fighters[id];
	FighterData* fd = &fighterData[fighterId];
	
	fighter->enabled = 1;
	fighter->alive = 1;
	fighter->fatalInjury = false;
	fighter->trulyDead = false;
	fighter->side = side;
	
	for (int i = 0; i < 32; i++) fighter->name[i] = fd->name[i];
	fighter->exp = fd->exp;
	fighter->cash = fd->cash;
	fighter->rewardCount = fd->rewardCount;
	for (int i = 0; i < fighter->rewardCount; i++) {
		fighter->rewards[i].type = fd->rewards[i].type;
		fighter->rewards[i].id = fd->rewards[i].id;
		fighter->rewards[i].rarity = fd->rewards[i].rarity;
	}
	
	fighter->headId = fd->headId;
	fighter->bodyId = fd->bodyId;
	fighter->collapseSpriteId = fd->collapseSpriteId;
	fighter->spriteId = -1;
	fighter->spriteFrame = 0;
	fighter->actionAnimId = fd->actionAnimId;
	fighter->ai = fd->ai;
	fighter->gender = fd->gender;
	
	switch (id) {
		case 0:
			fighter->xStart = 224;
			fighter->yStart = SCREEN_HEIGHT / 2 + 48;
			break;
		case 1:
			fighter->xStart = 168;
			fighter->yStart = SCREEN_HEIGHT / 2 - 8;
			break;
		case 2:
			fighter->xStart = 128;
			fighter->yStart = SCREEN_HEIGHT / 2 + 104;
			break;
		case 3:
			fighter->xStart = 72;
			fighter->yStart = SCREEN_HEIGHT / 2 + 48;
			break;
		case 8:
			fighter->xStart = SCREEN_WIDTH - 224;
			fighter->yStart = SCREEN_HEIGHT / 2 + 48;
			break;
		case 9:
			fighter->xStart = SCREEN_WIDTH - 168;
			fighter->yStart = SCREEN_HEIGHT / 2 - 8;
			break;
		case 10:
			fighter->xStart = SCREEN_WIDTH - 128;
			fighter->yStart = SCREEN_HEIGHT / 2 + 104;
			break;
		case 11:
			fighter->xStart = SCREEN_WIDTH - 72;
			fighter->yStart = SCREEN_HEIGHT / 2 + 48;
			break;
		default:
			fighter->xStart = SCREEN_WIDTH / 2;
			fighter->yStart = SCREEN_HEIGHT / 3 * 2;
			break;
	}
	
	fighter->x = fighter->xStart;
	fighter->y = fighter->yStart;
	fighter->moveTarget.enabled = false;
	fighter->facing = 1 - side * 2;
	fighter->state = FIGHTER_STATE_IDLE;
	fighter->flinchTicks = 0;
	
	fighter->hpMax = fd->hpMax;
	fighter->mpMax = fd->mpMax;
	fighter->attack = fd->attack;
	fighter->defense = fd->defense;
	fighter->speed = fd->speed;
	
	fighter->movesetCount = fd->movesetCount;
	for (int i = 0; i < 16; i++) {
		fighter->moveset[i] = fd->moveset[i] & 0xff;
		fighter->movesetDisabled[i] = false;
	}
	
	fighter->passiveCount = fd->passiveCount;
	for (int i = 0; i < 32; i++) fighter->passives[i] = fd->passives[i];
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) fighter->passiveVars[i].i = 0;
	
	fighter->hp = fighter->hpMax;
	fighter->mp = fighter->mpMax;
	
	if (fighter->hpMax == 0) fighter->hpMax = 1;
	if (fighter->mpMax == 0) fighter->mpMax = 1;
	
	if (fighterId >= 1 && fighterId <= 10) {
		PartyMember* partyMember = &partyMembers[fighterId - 1];
		
		fighter->headId = partyMember->headId;
		fighter->bodyId = partyMember->bodyId;
		Armor* armor;
		if (partyMember->armorId == 0)
			armor = &armorData[partyMember->defaultArmorId];
		else
			armor = &armorData[partyMember->armorId];
		
		fighter->actionAnimId = armor->actionAnimId;
		
		fighter->hpMax = partyMember->hpMax;
		fighter->mpMax = partyMember->mpMax;
		fighter->attack = partyMember->attack;
		fighter->defense = partyMember->defense;
		fighter->speed = partyMember->speed;
		
		fighter->movesetCount = partyMember->movesetCount;
		for (int i = 0; i < fighter->movesetCount; i++) {
			fighter->moveset[i] = partyMember->moveset[i];
			fighter->movesetDisabled[i] = false;
		}
		
		fighter->passiveCount = partyMember->passiveCount;
		for (int i = 0; i < fighter->passiveCount; i++) fighter->passives[i] = partyMember->passives[i];
		
		fighter->hp = fighter->hpMax - partyMember->hpDamage;
		fighter->mp = fighter->mpMax;
		if (partyMember->tiredLevel >= 2) {
			fighter->mp = 0;
		}
		else if (partyMember->tiredLevel == 1) {
			fighter->mp = fighter->mpMax / 2;
		}
		
		if (fighter->hp < 1) fighter->hp = 1;
		
		if (armorData[partyMember->armorId].specialAbility) {
			fighter->ai = 10000 + armorData[partyMember->armorId].specialAbility;
		}
	}
	
	fighter->canAct = true;
	fighter->speedRoll = 0;
	for (int i = 0; i < 32; i++) {
		fighter->status[i] = 0;
		fighter->statusNext[i] = 0;
		fighter->statusOverride[i] = false;
	}
	for (int i = 0; i < 4; i++) fighter->battleEventVars[i] = 0;
	for (int i = 0; i < 8; i++) fighter->aiVars[i].i = 0;
	
	fighter->bodyguardId = -1;
	fighter->counterTargetId = -1;
	fighter->manaCostReduction = 0;
	
	fighter->blockTimer = -1;
	fighter->blockCooldownTimer = -1;
	fighter->attackTimer = -1;
	fighter->attackAnimTimer = -1;
	fighter->attackAnimTime = -1;
	fighter->readyTimer = -1;
	
	fighter->aiTakeAttackCount = 0;
	fighter->aiTakeAttackPredictTime = -1;
	fighter->aiBlockCount = 0;
	fighter->aiDodgeCount = 0;
	fighter->aiDefenseScore = 0;
}

void Battle_CreateLabel(int color, const char* string, float x, float y) {
	int id = battle.labelCounter;
	
	battle.label[id].color = color;
	for (int i = 0; i < 16; i++) {
		battle.label[id].string[i] = string[i];
		if (string[i] == 0) break;
	}
	battle.label[id].x = x;
	battle.label[id].y = y;
	battle.label[id].timer = 0;
	
	battle.labelCounter++;
	if (battle.labelCounter >= 16) battle.labelCounter = 0;
}

void Battle_CreateSpark(int id, float x, float y, int depth) {
	int sparkId = battle.sparkCounter;
	
	battle.sparks[sparkId].id = id;
	battle.sparks[sparkId].x = x;
	battle.sparks[sparkId].y = y;
	battle.sparks[sparkId].depth = depth;
	battle.sparks[sparkId].timer = 0;
	battle.sparks[sparkId].xVel = 0;
	battle.sparks[sparkId].yVel = 0;
	
	battle.sparkCounter++;
	if (battle.sparkCounter >= OBJECT_COUNT_MAX) battle.sparkCounter = 0;
}

void Battle_ShakeScreen(int timer) {
	battle.shakeTimer = timer;
}

void Battle_TriggerBattleEvent(int battleEventId, Fighter* fighter) {
	battle.battleEventId = battleEventId;
	battle.battleEventFighter = fighter;
	if (battle.state == BATTLE_STATE_IDLE && battle.timer <= -1) {
		battle.battleEventType = BATTLE_EVENT_TYPE_TURNEND;
	}
	else {
		battle.battleEventType = BATTLE_EVENT_TYPE_TURNSTART;
	}
	battle.state = BATTLE_STATE_EVENT;
	battle.timer = 0;
	battle.battleEventDialogWait = true;
}



void Battle_Camera_MoveTo(float x, float y, float zoom, float speed) {
	battle.camera.moveTarget.enabled = true;
	battle.camera.moveTarget.x = x;
	battle.camera.moveTarget.y = y;
	battle.camera.moveTarget.zoom = zoom;
	battle.camera.moveTarget.speed = speed;
	
	float distance = PointDistance(battle.camera.x, battle.camera.y, battle.camera.moveTarget.x, battle.camera.moveTarget.y);
	battle.camera.moveTarget.zoomSpeed = (battle.camera.moveTarget.zoom - battle.camera.zoom) / distance * speed;
}

void Battle_Camera_MoveToStart(float speed) {
	battle.camera.moveTarget.enabled = true;
	battle.camera.moveTarget.x = 320;
	battle.camera.moveTarget.y = 240;
	battle.camera.moveTarget.zoom = 1;
	battle.camera.moveTarget.speed = speed;
	
	float distance = PointDistance(battle.camera.x, battle.camera.y, battle.camera.moveTarget.x, battle.camera.moveTarget.y);
	battle.camera.moveTarget.zoomSpeed = (battle.camera.moveTarget.zoom - battle.camera.zoom) / distance * speed;
}



void Battle_Draw() {
	if (battle.shakeTimer == 0)
		Drawer_SetProjection(battle.camera.x, battle.camera.y, battle.camera.zoom);
	else
		Drawer_SetProjection(battle.camera.x + Random_Range(-battle.shakeTimer, battle.shakeTimer), battle.camera.y + Random_Range(-battle.shakeTimer, battle.shakeTimer), battle.camera.zoom);
	
	if (battle.backgroundId == 0) {
		Drawer_SetDrawColor(15, 23, 15);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawColor(0, 63, 0);
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(32*i - 0.5 - (battle.globalTimer % 256) / 4, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(0, 32*i - 0.5, SCREEN_WIDTH, 1);
		}
		
		Drawer_SetDrawColor(79, 0, 79);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 1) {
		float x = sin((float)(battle.globalTimer % 1024) / 96) * 128;
		float y = cos((float)(battle.globalTimer % 1024) / 128) * 128;
		float scale = 2;
		if ((battle.globalTimer % 72) / 24 == 2)
			scale = 12;
		else if ((battle.globalTimer % 72) / 24 == 1)
			scale = 4;
		
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		
		Drawer_SetDrawColor(16 - (int)(cos((float)battle.globalTimer / 128) * 16), 12 + (int)(cos((float)battle.globalTimer / 128) * 11), 0);
		for (int j = -9; j < 16; j++)
		for (int i = -9; i < 14; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		Drawer_SetDrawColor(16 - (int)(cos((float)battle.globalTimer / 128) * 16), 6 + (int)(cos((float)battle.globalTimer / 128) * 5), 0);
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		for (int j = -9; j < 20; j++)
		for (int i = -9; i < 17; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		
		Drawer_SetDrawColor(0, 31, 0);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 2) {
		float speed = 0.25;
		if (audioSystem.currentMusicId == MUS_boss2 || audioSystem.currentMusicId == MUS_battlestrong) speed = 3.5;
		float x = sin((float)(battle.globalTimer % 2048) / 160) * 512 * speed;
		float y = cos((float)(battle.globalTimer % 2048) / 96) * 48 * speed;
		float scale = 2;
		if ((battle.globalTimer % 72) / 24 == 2)
			scale = 12;
		else if ((battle.globalTimer % 72) / 24 == 1)
			scale = 4;
		
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		
		Drawer_SetDrawColor(16 - (int)(cos((float)battle.globalTimer / 128) * 16), 12 + (int)(cos((float)battle.globalTimer / 128) * 11), 24 + (int)(cos((float)battle.globalTimer / 128) * 23));
		for (int j = -9; j < 16; j++)
		for (int i = -14; i < 19; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		for (int j = -9; j < 20; j++)
		for (int i = -14; i < 22; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, -y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		
		Drawer_SetDrawColor(0, 15, 31);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 3) {
		float x = (battle.globalTimer * 4) % 2048;
		float y = battle.globalTimer % 1024;
		float scaleX = 1;
		float scaleY = 1 - (float)(battle.globalTimer % 1024) / 800;
		if (battle.globalTimer % 1024 >= 512) {
			y -= 2 * ((battle.globalTimer - 511) % 1024);
			scaleY += (float)((battle.globalTimer - 511) % 1024) / 400;
		}
		
		Drawer_SetDrawColor(11 + (int)(cos((float)battle.globalTimer / 32) * 12), 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(0, 0, 63);
		for (int j = -18; j < 18; j++)
		for (int i = -22; i < 22; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_2, x / 8 + 32*i*scaleX*8, y / 8 + 32*j*scaleY*8, 0, scaleX * 4, scaleY * 4);
		}
		
		Drawer_SetDrawColor(0, 127 + (int)(cos((float)battle.globalTimer / 64) * 128), 255);
		for (int j = -38; j < 28; j++)
		for (int i = -32; i < 32; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_2, x / 2 + 32*i*scaleX*2, y + 32*j*scaleY, 0, scaleX, scaleY);
		}
		
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(0, 0, 255);
		for (int j = -28; j < 28; j++)
		for (int i = -32; i < 32; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_2, x / 2 + 32*i*scaleX*4, y / 2 + 32*j*scaleY*4, 0, scaleX * 4, scaleY * 4);
		}
		
		Drawer_SetDrawColor(63, 0, 0);
		for (int j = -18; j < 18; j++)
		for (int i = -22; i < 22; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_2, x / 8 + 32*i*scaleX*4, y / 16 + 32*j*scaleY*4, 0, scaleX * 6, scaleY * 6);
		}
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(0, 0, 31);
		for (int j = -18; j < 18; j++)
		for (int i = -22; i < 22; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_2, x / 8 + 32*i*scaleX*4, y / 16 + 32*j*scaleY*4, 0, scaleX * 6, scaleY * 6);
		}
		
		Drawer_SetDrawColor(127, 0, 127);
		/*
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
		*/
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (battle.backgroundId == 4) {
		float speed = 0.25;
		if (audioSystem.currentMusicId == MUS_lastresort || audioSystem.currentMusicId == MUS_lastresort2) speed = 3.5;
		float x = sin((float)(battle.globalTimer % 2048) / 140) * 512 * speed;
		float y = cos((float)(battle.globalTimer % 2048) / 84) * 64 * speed;
		float scale = 2;
		if ((battle.globalTimer % 72) / 24 == 2)
			scale = 12;
		else if ((battle.globalTimer % 72) / 24 == 1)
			scale = 4;
		
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(32 - (int)(cos((float)battle.globalTimer / 128) * 8), 32 + (int)(cos((float)battle.globalTimer / 128) * 32), 32 + (int)(cos((float)battle.globalTimer / 128) * 32));
		for (int j = -9; j < 16; j++)
		for (int i = -14; i < 19; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		for (int j = -9; j < 20; j++)
		for (int i = -14; i < 22; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, -y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		
		Drawer_SetDrawColor(31, 0, 0);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 5) {
		Drawer_SetDrawColor(15, 15, 23);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawColor(0, 15, 63);
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(32*i - 0.5 - (battle.globalTimer % 256) / 4, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(0, 32*i - 0.5, SCREEN_WIDTH, 1);
		}
		
		Drawer_SetDrawColor(0, 31, 127);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 6) {
		float x = -(battle.globalTimer % 512) / 4;
		float y = -(battle.globalTimer % 512) / 4;
		float scale = 2;
		if ((battle.globalTimer % 120) / 40 == 2)
			scale = 12;
		else if ((battle.globalTimer % 120) / 40 == 1)
			scale = 4;
		
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		
		Drawer_SetDrawColor(12, 12, 12);
		for (int j = -9; j < 16; j++)
		for (int i = -9; i < 14; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		Drawer_SetDrawColor(16, 16, 16);
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		for (int j = -9; j < 20; j++)
		for (int i = -9; i < 17; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (battle.backgroundId == 7) {
		float x = sin((float)(battle.globalTimer % 1024) / 96) * 128;
		float y = cos((float)(battle.globalTimer % 1024) / 128) * 128;
		float scale = 2;
		if ((battle.globalTimer % 72) / 24 == 2)
			scale = 12;
		else if ((battle.globalTimer % 72) / 24 == 1)
			scale = 4;
		
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		
		Drawer_SetDrawColor(12 + (int)(cos((float)battle.globalTimer / 512) * 11), 0, 0);
		for (int j = -9; j < 16; j++)
		for (int i = -9; i < 14; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		Drawer_SetDrawColor(6 + (int)(cos((float)battle.globalTimer / 512) * 5), 0, 0);
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		for (int j = -9; j < 20; j++)
		for (int i = -9; i < 17; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		
		Drawer_SetDrawColor(31, 0, 0);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 8) {
		if (battle.battleEventVars[1] >= 999)
			Drawer_SetDrawColor(0, 0, 128);
		else
			Drawer_SetDrawColor(255 - 24 * battle.battleEventVars[1], 32, 32);
		Drawer_DrawSprite(SPR_misc_backdrop_hell, 0, 0, 0, 2, 2);
	}
	else if (battle.backgroundId == 9) {
		for (int y = 0; y < 256; y += 128)
		for (int x = 0; x < 640; x += 128) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x, y, 0, 2, 2);
		}
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(336, 240, 304, 16);
	}
	else if (battle.backgroundId == 10) {
		Drawer_SetDrawColor(240, 240, 232);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		float x = cos((float)battle.globalTimer / 4) * 128 + sin((float)battle.globalTimer / 5) * 128 + cos((float)battle.globalTimer / 9) * 128;
		float y = sin((float)battle.globalTimer / 4) * 128 + cos((float)battle.globalTimer / 5) * 128 + sin((float)battle.globalTimer / 9) * 128;
		
		Drawer_SetDrawColor(255, 240, 192);
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(32*i - 0.5 + x - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(0, 32*i - 0.5 + y, SCREEN_WIDTH, 1);
		}
		
		Drawer_SetDrawColor(255, 224, 128);
		for (int i = -34; i < 90; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 + x - (battle.globalTimer % 64), 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -34; i < 90; i++) {
			Drawer_FillRect(0, 32*i - 0.5 + y - (battle.globalTimer % 64), SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 11) {
		Drawer_SetDrawColor(15, 23, 31);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawColor(0, 47, 63);
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(32*i - 0.5 - (battle.globalTimer % 256) / 4, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(0, 32*i - 0.5, SCREEN_WIDTH, 1);
		}
		
		Drawer_SetDrawColor(0, 95, 111);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 12) {
		float speed = 3.5;
		float x = sin((float)(battle.globalTimer % 2048) / 160) * 512 * speed;
		float y = cos((float)(battle.globalTimer % 2048) / 96) * 48 * speed;
		float scale = 2;
		if ((battle.globalTimer % 72) / 24 == 2)
			scale = 12;
		else if ((battle.globalTimer % 72) / 24 == 1)
			scale = 4;
		
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, 1280, 720);
		
		Drawer_SetDrawColor(16 - (int)(cos((float)battle.globalTimer / 128) * 16), 0, 24 + (int)(cos((float)battle.globalTimer / 128) * 23));
		for (int j = -9; j < 16; j++)
		for (int i = -14; i < 19; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		for (int j = -9; j < 20; j++)
		for (int i = -14; i < 22; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, -y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		
		Drawer_SetDrawColor(0, 0, 31);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 13) {
		bool redMode = battle.fighters[8].battleEventVars[0] == 1;
		float x = sin((float)battle.globalTimer / 25) * 4;
		float y = 0;
		float angle = 0;
		if (redMode)
			angle = (battle.globalTimer % 90) * 4;
		else if (battle.globalTimer % 650 < 120)
			angle = (battle.globalTimer % 650) * 90 / 120;
		else if (battle.globalTimer % 650 >= 120 && battle.globalTimer % 650 < 210)
			angle = 90 + ((battle.globalTimer % 650) - 120);
		else if (battle.globalTimer % 650 >= 210 && battle.globalTimer % 650 < 550)
			angle = 180 - ((battle.globalTimer % 650) - 210) * 90 / 340;
		else if (battle.globalTimer % 650 >= 550 && battle.globalTimer % 650 < 640)
			angle = 90 - ((battle.globalTimer % 650) - 550);
		
		if (battle.globalTimer % 1500 < 300)
			y = 0;
		else if (battle.globalTimer % 1500 < 400)
			y = -((battle.globalTimer % 1500) - 300) / 8;
		else if (battle.globalTimer % 1500 < 1100)
			y = -12;
		else if (battle.globalTimer % 1500 < 1300)
			y = -12 + ((battle.globalTimer % 1500) - 1100) / 16;
		else
			y = 0;
		
		if (redMode)
			Drawer_SetDrawColor(31, 0, 0);
		else
			Drawer_SetDrawColor(27, 0, 27);
		for (int i = 0; i < 24; i++) {
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_3, x + 32*i, y + 160, 0, 1, 1, angle);
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_3, x + 32*i, -y + SCREEN_HEIGHT - 160, 0, 1, 1, angle);
		}
		if (redMode)
			Drawer_SetDrawColor(95, 0, 0);
		else
			Drawer_SetDrawColor(71, 0, 71);
		for (int i = 0; i < 12; i++) {
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_3, x * 2 + 64*i, y + 120, 0, 2, 2, angle);
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_3, x * 2 + 64*i, -y + SCREEN_HEIGHT - 120, 0, 2, 2, angle);
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_4, x * 2 + 64*i, y + 120, 0, 1.75, 1.75, angle);
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_4, x * 2 + 64*i, -y + SCREEN_HEIGHT - 120, 0, 1.75, 1.75, angle);
		}
		if (redMode)
			Drawer_SetDrawColor(223, 0, 0);
		else
			Drawer_SetDrawColor(191, 0, 191);
		for (int i = 0; i < 6; i++) {
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_3, x * 4 + 128*i, y * 2 + 46, 0, 4, 4, angle);
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_3, x * 4 + 128*i, -y * 2 + SCREEN_HEIGHT - 46, 0, 4, 4, angle);
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_4, x * 4 + 128*i, y * 2 + 46, 0, 3.5, 3.5, angle);
			Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_4, x * 4 + 128*i, -y * 2 + SCREEN_HEIGHT - 46, 0, 3.5, 3.5, angle);
		}
		
		if (redMode)
			Drawer_SetDrawColor(31, 0, 0);
		else
			Drawer_SetDrawColor(15, 0, 15);
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		for (int j = -9; j < 16; j++)
		for (int i = -15; i < 12; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, 64*i*2 + (battle.globalTimer % 512) / 4 * (1 + redMode * 11), 64*j*2 - (battle.globalTimer % 512) / 4, 0, 2, 2);
		}
		for (int j = -9; j < 16; j++)
		for (int i = -15; i < 12; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, 64*i*2 + (battle.globalTimer % 256) / 2 * (1 + redMode * 11), 64*j*2 - (battle.globalTimer % 256) / 2, 0, 2, 2);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (battle.backgroundId == 14) {
		int a = battle.globalTimer / 4 * 16;
		float scale = 2;
		if (game.settings.softwareRendering) {
			for (int i = 0; i < 100; i++) {
				float b = (float)(a + i) / 2;
				float colorScale = 2.0 - (float)i / 50;
				Drawer_SetDrawColor((6 + sin(b) * 6) * colorScale, 0, (16 - sin(b) * 16) * colorScale);
				Drawer_FillRect(320 - SCREEN_WIDTH / 2, 240 - SCREEN_HEIGHT * scale / 2 + sin((float)(a + i) / 384) * 48 - 56, SCREEN_WIDTH, 16 * scale);
				Drawer_FillRect(320 - SCREEN_WIDTH / 2, 240 + SCREEN_HEIGHT * scale / 2 - 16 * scale + sin((float)(a + i) / 384) * 48 - 56, SCREEN_WIDTH, 16 * scale);
				scale *= 0.96;
			}
		}
		else {
			for (int i = 0; i < 100; i++) {
				float b = (float)(a + i) / 2;
				float colorScale = 2.0 - (float)i / 50;
				Drawer_SetDrawColor((6 + sin(b) * 6) * colorScale, 0, (16 - sin(b) * 16) * colorScale);
				Drawer_FillRect(320 - SCREEN_WIDTH / 2, 240 - SCREEN_HEIGHT * scale / 2 + sin((float)(a + i) / 384) * 48 - 56, SCREEN_WIDTH, SCREEN_HEIGHT * scale);
				scale *= 0.96;
			}
		}
		
		Drawer_SetDrawColor(0, 63, 159);
		for (int i = -4; i < 36; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_6, 32*i - (battle.globalTimer % 8) * 4, 140, 0, 2, 2);
			Drawer_DrawSprite(SPR_misc_bossbattlebg_6, 32*i + (battle.globalTimer % 8) * 4, 360, 0, 2, -2);
		}
	}
	else if (battle.backgroundId == 15) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		int a = battle.globalTimer / 2 * 16;
		float scale = 2;
		for (int i = 0; i < 100; i++) {
			float b = (float)(a + i) / 2;
			float colorScale = 2.0 - (float)i / 50;
			Drawer_SetDrawColor((20 + sin(b) * 20) * colorScale * (2 + sin((float)battle.globalTimer / 48)), 0, 0);
			Drawer_FillRect(320 - SCREEN_WIDTH * scale / 2, 240 - SCREEN_HEIGHT * scale / 2, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale);
			scale *= 0.96;
		}
	}
	else if (battle.backgroundId == 16) {
		Drawer_SetDrawColor(15, 15, 15);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawColor(47, 23, 47);
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(32*i - 0.5 - (battle.globalTimer % 256) / 4, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(0, 32*i - 0.5, SCREEN_WIDTH, 1);
		}
		
		Drawer_SetDrawColor(127, 0, 79);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 17) {
		Drawer_SetDrawColor(23, 15, 15);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawColor(63, 0, 0);
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(32*i - 0.5 - (battle.globalTimer % 256) / 4, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(0, 32*i - 0.5, SCREEN_WIDTH, 1);
		}
		
		Drawer_SetDrawColor(127, 0, 0);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}
	}
	else if (battle.backgroundId == 18) {
		Drawer_SetDrawColor(167 - (int)(cos((float)battle.globalTimer / 128) * 32), 0, 0);
		Drawer_DrawSprite(SPR_misc_backdrop_redmountains, 0, 0, 0, 2, 2);
		
		Drawer_SetDrawColor(0, 0, 0);
		for (int y = -64 + ((game.timer / 8) % 6); y < SCREEN_HEIGHT + 128; y += 6) {
			Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 1);
		}
		
		/*Drawer_SetDrawColor(127, 0, 0);
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(32*i - 0.5 - (battle.globalTimer % 256) / 4, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -100; i < 100; i++) {
			Drawer_FillRect(0, 32*i - 0.5, SCREEN_WIDTH, 1);
		}
		
		Drawer_SetDrawColor(63, 0, 0);
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(32*i - 0.5 + 4 - (battle.globalTimer % 128) / 2, 0, 1, SCREEN_HEIGHT);
		}
		for (int i = -4; i < 60; i++) {
			Drawer_FillRect(0, 32*i - 0.5 - (battle.globalTimer % 128) / 2, SCREEN_WIDTH, 1);
		}*/
	}
	else if (battle.backgroundId == 19) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(63 + (int)(cos((float)battle.globalTimer / 256) * 32), 0, 0);
		Drawer_DrawSprite(SPR_misc_bossbattlebg_10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, battle.globalTimer / 2 % 4, 1, 1);
		
		for (int i = 1; i <= 8; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, (battle.globalTimer / 2 - 1 - i / 2) % 4, 1 + i * 0.5, 1 + i * 0.5);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (battle.backgroundId == 20) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(0, 0, 63 + (int)(cos((float)battle.globalTimer / 256) * 32));
		Drawer_DrawSprite(SPR_misc_bossbattlebg_10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, battle.globalTimer / 2 % 4, 1, 1);
		
		for (int i = 1; i <= 8; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, (battle.globalTimer / 2 - 1 - i / 2) % 4, 1 + i * 0.5, 1 + i * 0.5);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (battle.backgroundId == 21) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(23, 23, 23);
		Drawer_DrawSprite(SPR_misc_bossbattlebg_10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, battle.globalTimer / 2 % 4, 1, 1);
		
		for (int i = 1; i <= 8; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, (battle.globalTimer / 2 - 1 - i / 2) % 4, 1 + i * 0.5, 1 + i * 0.5);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	
	Drawer_SetDrawColor(63, 63, 63);
	Drawer_FillRect(-64, SCREEN_HEIGHT - 106, SCREEN_WIDTH + 128, 256);
	Drawer_SetDrawColor(0, 0, 0);
	Drawer_FillRect(-64, SCREEN_HEIGHT - 104, SCREEN_WIDTH + 128, 252);
	Drawer_SetDrawColor(255, 255, 255);
	
	Drawer_SetFontAlignment(FONT_ALIGN_MIDDLE | FONT_ALIGN_CENTER);
	
	for (int i = 0; i < 16; i++) {
		Fighter* fighter = &battle.fighters[i];
		if (!fighter->enabled) continue;
		
		if (fighter->ai == 192 && battle.battleEventVars[0] == 1) {
			Drawer_SetDrawAlpha(223);
			Drawer_DrawSprite(SPR_misc_subspace_redaura, fighter->x, fighter->y - 24, (battle.globalTimer / 2) % 4, 2, 2);
			Drawer_SetDrawAlpha(255);
		}
		
		float x = fighter->x;
		float y = fighter->y;
		if (fighter->flinchTicks > 6) {
			x += (1 - 2 * (((fighter->flinchTicks - 6) / 3) % 2)) * ((fighter->flinchTicks - 6) / 6 + 1);
		}
		if (fighter->ai == 101) {
			y += -12 + cos((float)battle.globalTimer / 32) * 10;
		}
		
		if (fighter->spriteId >= 0)
			Drawer_DrawSprite(fighter->spriteId, x, y, fighter->spriteFrame, 2 * fighter->facing, 2);
		else
			DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, x, y, 2, 2, fighter->facing);
		
		if (fighter->ai == 57 && battle.battleEventVars[1] >= 1) {
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			if (battle.globalTimer % 8 < 4) {
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_SetDrawAlpha(127);
			}
			if (fighter->spriteId >= 0)
				Drawer_DrawSprite(fighter->spriteId, x, y, fighter->spriteFrame, 2 * fighter->facing, 2);
			else
				DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, x, y, 2, 2, fighter->facing);
			
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_SetDrawAlpha(127);
			
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 3, 3, (float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 4, 4, -(float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 5, 5, (float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 6, 6, -(float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 7, 7, (float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 8, 8, -(float)battle.globalTimer * 18);
			
			Drawer_SetDrawAlpha(255);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		if (fighter->ai == 192 && battle.battleEventVars[0] == 1) {
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			if (battle.globalTimer % 8 < 4) {
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_SetDrawAlpha(127);
			}
			if (fighter->spriteId >= 0)
				Drawer_DrawSprite(fighter->spriteId, x, y, fighter->spriteFrame, 2 * fighter->facing, 2);
			else
				DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, x, y, 2, 2, fighter->facing);
			
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			Drawer_SetDrawColor(127, 0, 127);
			Drawer_SetDrawAlpha(127);
			
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 4, 4, (float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 6, 6, -(float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 8, 8, (float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 10, 10, -(float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 12, 12, (float)battle.globalTimer * 18);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 14, 14, -(float)battle.globalTimer * 18);
			
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_SetDrawAlpha(255);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		if (fighter->ai == 191 && battle.battleEventVars[0] == 1) {
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			if (battle.globalTimer % 8 < 4) {
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_SetDrawAlpha(127);
			}
			if (fighter->spriteId >= 0)
				Drawer_DrawSprite(fighter->spriteId, x, y, fighter->spriteFrame, 2 * fighter->facing, 2);
			else
				DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, x, y, 2, 2, fighter->facing);
			
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_SetDrawAlpha(127);
			
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 3, 3, (float)battle.globalTimer * 9);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 4, 4, -(float)battle.globalTimer * 9);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 5, 5, (float)battle.globalTimer * 9);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 6, 6, -(float)battle.globalTimer * 9);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 2, 7, 7, (float)battle.globalTimer * 9);
			Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 3, 8, 8, -(float)battle.globalTimer * 9);
			
			Drawer_SetDrawAlpha(255);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		
		if (battle.state == BATTLE_STATE_IDLE && fighter->alive) {
			if (i == battle.turn)
				Drawer_SetDrawColor(255, 255, 255);
			else if (fighter->actionId > 0)
				Drawer_SetDrawColor(255, 127, 255);
			else
				Drawer_SetDrawColor(63, 63, 63);
			
			Drawer_DrawSprite(SPR_gui_speedgem, fighter->x, fighter->y - 86 - (fighter->ai == 101) * 46, 0, 2, 2);
			
			Drawer_SetDrawColor(255, 255, 255);
			
			if ((battle.menu.id == 2 && battle.menu.options[battle.menu.cursors[2]].value == i) || (battle.menu.id == 4 && battle.menu.options[battle.menu.cursors[1]].value == i)) {
				Drawer_SetDrawBlend(BLENDMODE_ADD);
				Drawer_DrawSprite(SPR_gui_speedgem, fighter->x, fighter->y - 86 - (fighter->ai == 101) * 46, 0, 2, 2);
				Drawer_SetDrawBlend(BLENDMODE_BLEND);
			}
			
			Drawer_SetFontSprite(SPR_font_small);
			snprintf(game.textBuffer, 32, "%d", fighter->speedRoll);
			Drawer_DrawText(game.textBuffer, 32, fighter->x, fighter->y - 82 - (fighter->ai == 101) * 46, 2, 2);
			Drawer_SetFontSprite(SPR_font_main);
		}
	}
	
	for (int i = 0; i < 16; i++) {
		Fighter* fighter = &battle.fighters[i];
		if (!fighter->enabled) continue;
		
		if (fighter->alive) {
			int statusCount[10] = {0};
			int statusCountRows = 0;
			for (int j = 0; j < 32; j++) {
				if (!statusEffectData[j].visible) continue;
				if (fighter->status[j] > 0) statusCount[statusCountRows]++;
				if (statusCount[statusCountRows] >= 4) statusCountRows++;
				if (fighter->statusNext[j] > 0) statusCount[statusCountRows]++;
				if (statusCount[statusCountRows] >= 4) statusCountRows++;
			}
			
			Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
			Drawer_SetFontSprite(SPR_font_small);
			
			int c = 0;
			int row = 0;
			for (int j = 0; j < 32; j++) {
				if (fighter->status[j] <= 0) continue;
				if (!statusEffectData[j].visible) continue;
				
				Drawer_DrawSprite(SPR_gui_status, fighter->x - (statusCount[row] - 1) * 12 + c * 24, fighter->y + 16 + 24 * row, j, 2, 2);
				
				if (statusEffectData[j].stackable) {
					snprintf(game.textBuffer, 4, "%d", fighter->status[j]);
					Drawer_DrawText(game.textBuffer, 4, fighter->x - (statusCount[row] - 1) * 12 + c * 24 + 2, fighter->y + 16 + 24 * row + 2, 2, 2);
				}
				c++;
				if (c >= 4) {
					c = 0;
					row++;
				}
			}
			for (int j = 0; j < 32; j++) {
				if (fighter->statusNext[j] <= 0) continue;
				if (!statusEffectData[j].visible) continue;
				
				Drawer_SetDrawAlpha(127);
				Drawer_DrawSprite(SPR_gui_status, fighter->x - (statusCount[row] - 1) * 12 + c * 24, fighter->y + 16 + 24 * row, j, 2, 2);
				Drawer_SetDrawAlpha(255);
				
				if (statusEffectData[j].stackable) {
					snprintf(game.textBuffer, 4, "%d", fighter->statusNext[j]);
					Drawer_DrawText(game.textBuffer, 4, fighter->x - (statusCount[row] - 1) * 12 + c * 24 + 2, fighter->y + 16 + 24 * row + 2, 2, 2);
				}
				c++;
				if (c >= 4) {
					c = 0;
					row++;
				}
			}
			
			Drawer_SetFontAlignment(FONT_ALIGN_MIDDLE | FONT_ALIGN_CENTER);
			Drawer_SetFontSprite(SPR_font_main);
		}
	}
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	Drawer_SetFontSprite(SPR_font_small);
	
	for (int i = 0; i < 16; i++) {
		Fighter* fighter = &battle.fighters[i];
		if (!fighter->enabled) continue;
		
		int x;
		if (i < 8)
			x = 25 + i * 54;
		else
			x = SCREEN_WIDTH - 25 - (i - 8) * 54;
		
		Drawer_SetDrawColor(127, 127, 127);
		if (fighter->blockTimer >= 0 && fighter->blockTimer <= 1)
			Drawer_SetDrawColor(255, 255, 0);
		else if (fighter->blockTimer >= 0)
			Drawer_SetDrawColor(159, 159, 159);
		
		Drawer_DrawSprite(SPR_gui_charbar, x, SCREEN_HEIGHT - 102, 0, 2, 2);
		
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_FillRect(x - 18, SCREEN_HEIGHT - 102 + 52 - fighter->hp * 46 / fighter->hpMax, 6, fighter->hp * 46 / fighter->hpMax);
		
		Drawer_SetDrawColor(0, 255, 255);
		Drawer_FillRect(x - 6, SCREEN_HEIGHT - 102 + 52 - fighter->mp * 46 / fighter->mpMax, 6, fighter->mp * 46 / fighter->mpMax);
		
		Drawer_SetDrawColor(255, 255, 255);
		
		Battle_DrawFighterPortrait(fighter, x + 2, SCREEN_HEIGHT - 102 + 90);
		
		/*if (fighter->headId > 0) {
			int subImage = fighter->alive ? 0 : 2;
			if (battleHeadData[fighter->headId].backSpriteId >= 0) Drawer_DrawSprite(battleHeadData[fighter->headId].backSpriteId, x + 2, SCREEN_HEIGHT - 102 + 90, subImage, 2, 2);
			Drawer_DrawSprite(battleHeadData[fighter->headId].spriteId, x + 2, SCREEN_HEIGHT - 102 + 90, subImage, 2, 2);
		}
		else if (fighter->bodyId > 0) {
			int subImage = fighter->alive ? FIGHTER_STATE_IDLE : FIGHTER_STATE_HURT;
			Drawer_DrawSprite(battleBodyData[fighter->bodyId].spriteId, x + 2, SCREEN_HEIGHT - 102 + 92, subImage, 2, 2);
		}*/
	}
	
	Drawer_SetFontSprite(SPR_font_main);
	
	
	
	DrawDialogBox(0, 0, 640, 128);
	
	if (dialogSystem.state != DIALOG_STATE_IDLE) {
		Drawer_DrawText(dialogSystem.text, dialogSystem.textLength, 8, 4, 2, 2);
		
		if (dialogSystem.name[0] != 0) {
			Drawer_SetFontAlignment(FONT_ALIGN_RIGHT | FONT_ALIGN_TOP);
			DrawDialogBox(SCREEN_WIDTH - 16 - StringLength(dialogSystem.name) * 16, 128, 16 + StringLength(dialogSystem.name) * 16, 44);
			Drawer_DrawText(dialogSystem.name, 32, SCREEN_WIDTH - 8, 132, 2, 2);
			Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
		}
	}
	else if (battle.state == BATTLE_STATE_IDLE && battle.timer >= 3) {
		if (battle.menu.id == 0) {
			Fighter* fighter = &battle.fighters[battle.turn];
			
			if (fighter->enabled) {
				Battle_DrawFighterProfile(fighter);
				Menu_DrawOptions(&battle.menu, 0, 0, 360);
			}
		}
		else if (battle.menu.id == 1) {
			Fighter* fighter = &battle.fighters[battle.turn];
			
			Menu_DrawOptions(&battle.menu, 0, 0, 632);
			
			if (fighter->movesetCount > 0) {
				DrawActionDetailBox(battle.menu.options[battle.menu.cursors[battle.menu.cursorId]].value, 0, SCREEN_HEIGHT - 128, fighter->manaCostReduction, false, false);
			}
		}
		else if (battle.menu.id == 2) {
			Fighter* fighter = &battle.fighters[battle.menu.options[battle.menu.cursors[2]].value];
			
			Drawer_SetFontAlignment(FONT_ALIGN_MIDDLE | FONT_ALIGN_BOTTOM);
			Drawer_DrawText("v", 10, fighter->x, fighter->y - 104, 2, 2);
			Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
			
			Battle_DrawFighterProfile(fighter);
			Battle_DrawFighterProfileAction(fighter);
		}
		else if (battle.menu.id == 3) {
			Fighter* fighter = &battle.fighters[battle.turn];
			
			Menu_DrawOptions(&battle.menu, 0, 0, 632);
			
			if (profile.itemInventory[battle.menu.options[battle.menu.cursors[battle.menu.cursorId]].value] > 0) {
				DrawDialogBox(0, SCREEN_HEIGHT - 128, 640, 128);
				Drawer_DrawText(GetDialogString(4500 + profile.itemInventory[battle.menu.options[battle.menu.cursors[battle.menu.cursorId]].value]), 128, 8, SCREEN_HEIGHT - 128 + 4, 2, 2);
			}
		}
		else if (battle.menu.id == 4) {
			Fighter* fighter = &battle.fighters[battle.menu.options[battle.menu.cursors[1]].value];
			
			Drawer_SetFontAlignment(FONT_ALIGN_MIDDLE | FONT_ALIGN_BOTTOM);
			Drawer_DrawText("v", 10, fighter->x, fighter->y - 104, 2, 2);
			Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
			
			Battle_DrawFighterProfile(fighter);
			Battle_DrawFighterProfileAction(fighter);
		}
		else if (battle.menu.id == 5) {
			Menu_DrawOptions(&battle.menu, 0, 0, 360);
		}
	}
	
	
	
	if (battle.state == BATTLE_STATE_ACTION && battle.timer == 2) {
		int runActionCodeId = actionData[battle.attacker->actionId].codeId;
		if (battle.attacker->counterTargetId >= 0)
			runActionCodeId = actionData[1].codeId;
		
		actionDrawCode[runActionCodeId](battle.attacker, battle.target);
	}
	
	
	
	if (battle.state == BATTLE_STATE_START) {
		if (battle.timer < 44) {
			Drawer_SetDrawColor(0, 0, 0);
			Drawer_SetDrawAlpha(255 - battle.timer * 255 / 44);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_SetDrawAlpha(255);
		}
		if (battle.timer <= 33) {
			for (int i = 0; i < 5; i++) {
				if (profile.party[i] < 0) continue;
				
				Fighter* fighter = &battle.fighters[i];
				OverworldObject* object = &overworld.objects[i];
				
				Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
				
				fighter->x = GetScreenX(object->x) + (fighter->xStart - GetScreenX(object->x)) * battle.timer / 33;
				fighter->y = GetScreenY(object->y) + (fighter->yStart - GetScreenY(object->y)) * battle.timer / 33;
				
				Drawer_SetProjection(battle.camera.x, battle.camera.y, battle.camera.zoom);
				
				float x = fighter->x;
				float y = fighter->y;
				
				DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, x, y, 2, 2, fighter->facing);
				
				if (battle.timer < 24 && partyMembers[profile.party[i]].armorId != 0) {
					Drawer_SetDrawBlend(BLENDMODE_ADD);
					Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 1 + Min(3, battle.timer / 3), 2, 2, (float)battle.globalTimer * 15);
					Drawer_DrawSprite_Angle(SPR_spark_star, fighter->x, fighter->y - 24, 1 + Min(3, battle.timer / 3), 4, 4, -(float)battle.globalTimer * 15);
					Drawer_SetDrawBlend(BLENDMODE_BLEND);
				}
			}
			if (overworld.transition.vars[0] >= 0) {
				Fighter* fighter = &battle.fighters[8];
				OverworldObject* object = &overworld.objects[(int)overworld.transition.vars[0]];
				
				Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
				
				fighter->x = GetScreenX(object->x) + (fighter->xStart - GetScreenX(object->x)) * battle.timer / 33;
				fighter->y = GetScreenY(object->y) + (fighter->yStart - GetScreenY(object->y)) * battle.timer / 33;
				
				Drawer_SetProjection(battle.camera.x, battle.camera.y, battle.camera.zoom);
				
				float x = fighter->x;
				float y = fighter->y;
				
				DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, x, y, 2, 2, fighter->facing);
			}
		}
	}
	
	if (battle.state == BATTLE_STATE_END) {
		if (battle.timer > 5 && battle.timer < 100) {
			Drawer_SetDrawColor(0, 0, 0);
			Drawer_SetDrawAlpha((battle.timer - 5) * 255 / 30);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_SetDrawAlpha(255);
		}
	}
	
	if (battle.state == BATTLE_STATE_EVENT) {
		Battle_Draw_Event();
	}
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		if (battle.sparks[i].id <= 0) continue;
		
		float x = battle.sparks[i].x;
		float y = battle.sparks[i].y;
		
		switch (battle.sparks[i].id) {
			case 1:
				Drawer_DrawSprite(SPR_spark_spark, x, y, battle.sparks[i].timer / 2, 2, 2);
				break;
			case 2:
				Drawer_SetDrawColor(255, 191, 0);
				Drawer_DrawSprite(SPR_spark_spark, x, y, battle.sparks[i].timer / 2, 4, 4);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 3:
				Drawer_SetDrawColor(255, 0, 0);
				Drawer_DrawSprite(SPR_spark_spark, x, y, battle.sparks[i].timer / 2, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 4:
				Drawer_SetDrawColor(0, 255, 0);
				Drawer_DrawSprite(SPR_spark_spark, x, y, battle.sparks[i].timer / 2, 4, 4);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 5:
				Drawer_SetDrawColor(0, 127, 255);
				Drawer_DrawSprite(SPR_spark_spark, x, y, battle.sparks[i].timer / 2, 4, 4);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 6:
				Drawer_SetDrawColor(255, 191, 0);
				Drawer_DrawSprite(SPR_spark_star, x, y, battle.sparks[i].timer / 3, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 7:
				Drawer_DrawSprite(SPR_spark_blazeimpact, x, y, battle.sparks[i].timer / 4, 2, 2);
				break;
			case 8:
				Drawer_SetDrawColor(0, 255, 255);
				Drawer_DrawSprite(SPR_spark_ring, x, y, battle.sparks[i].timer / 4, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 9:
				Drawer_SetDrawColor(0, 0, 255);
				Drawer_DrawSprite(SPR_spark_spark, x, y, 0, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 10:
				Drawer_SetDrawColor(0, 0, 0);
				Drawer_DrawSprite(SPR_spark_blazeimpact, x, y, battle.sparks[i].timer / 4, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 11:
				{
					float angle = PointDirection(0, 0, battle.sparks[i].xVel, battle.sparks[i].yVel);
					if (angle > PI)
						angle -= 2 * PI;
					int frame = 2;
					if ((angle >= PI / 16 && angle <= PI * 7 / 16) || (angle >= PI * 9 / 16 && angle <= PI * 15 / 16))
						frame = 3;
					else if ((angle <= -PI / 16 && angle >= -PI * 7 / 16) || (angle <= -PI * 9 / 16 && angle >= -PI * 15 / 16))
						frame = 1;
					else if (angle >= PI / 4 && angle <= PI * 3 / 4)
						frame = 4;
					else if (angle <= -PI / 4 && angle >= -PI * 3 / 4)
						frame = 0;
					
					Drawer_DrawSprite(SPR_misc_malinewave, x, y, frame, 2 - 4 * (battle.sparks[i].xVel < 0), 2);
				}
				break;
			case 12:
				Drawer_SetDrawColor(40, 40, 40);
				Drawer_DrawSprite(SPR_spark_spark, x, y, 1 + battle.sparks[i].timer / 2, 2, 2);
				Drawer_DrawSprite(SPR_spark_ring, x, y, battle.sparks[i].timer / 2, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 13:
				for (; y > 0; y -= 4) {
					Drawer_SetDrawColor(127, 0, 0);
					Drawer_FillRect(x - 16, y - 1, 32, 4);
					Drawer_SetDrawColor(255, 0, 0);
					Drawer_FillRect(x - 6, y - 1, 12, 4);
					Drawer_SetDrawColor(0, 0, 0);
					Drawer_FillRect(x - 3, y - 1, 6, 4);
					x += Random_IRange(-1, 1) * 2;
				}
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 14:
				Drawer_SetDrawColor(255, 0, 0);
				Drawer_DrawSprite(SPR_spark_slashultra, x, y, battle.sparks[i].timer / 2, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 15:
				Drawer_SetDrawColor(255, 0, 255);
				Drawer_DrawSprite(SPR_spark_slashultra, x, y, battle.sparks[i].timer / 2, 2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 16:
				Drawer_SetDrawColor(255, 0, 0);
				Drawer_DrawSprite(SPR_spark_slashultra, x, y, battle.sparks[i].timer / 2, 2, 2);
				Drawer_DrawSprite(SPR_spark_slashultra, x, y, battle.sparks[i].timer / 2, -2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 17:
				Drawer_DrawSprite(SPR_misc_ultluluorb, x, y, battle.sparks[i].timer / 2 % 4, 2, 2);
				break;
			case 18:
				Drawer_DrawSprite(SPR_spark_ultluluimpact, x, y, battle.sparks[i].timer / 4, 2, 2);
				break;
			case 19:
				Drawer_DrawSprite(SPR_spark_ultlulubolt, x, y, battle.sparks[i].timer / 4, 2, 2);
				break;
			case 20:
				Drawer_SetDrawColor(255, 0, 255);
				Drawer_DrawSprite(SPR_spark_slashultra, x, y, battle.sparks[i].timer / 2, 2, 2);
				Drawer_DrawSprite(SPR_spark_slashultra, x, y, battle.sparks[i].timer / 2, -2, 2);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 21:
				Drawer_DrawSprite(SPR_spark_blood, x, y, battle.sparks[i].timer / 4, 2, 2);
				break;
			
			case 9900:
				Drawer_DrawSprite(SPR_spark_star, x, y, battle.sparks[i].timer / 2, 4, 4);
				break;
			case 9901:
				Drawer_SetDrawColor(255, 0, 0);
				Drawer_DrawSprite(SPR_spark_spark, x, y, battle.sparks[i].timer, 16, 16);
				Drawer_SetDrawColor(255, 255, 255);
				break;
			case 9902:
				Drawer_DrawSprite(SPR_misc_omegalulu, x, y, 0, 10, 10);
				break;
			case 9903:
				Drawer_DrawSprite_Angle(SPR_misc_omegalulukatana, x, y, 0, 4, 4, (float)battle.sparks[i].timer * 8);
				break;
			case 9904:
				Drawer_DrawSprite_Angle(SPR_misc_omegalulu, x, y, 0, 4, 4, (float)battle.sparks[i].timer * 5);
				break;
			case 9905:
				Drawer_DrawSprite(SPR_spark_spark, x, y, battle.sparks[i].timer, 4, 4);
				break;
			case 9906:
				for (; y > 0; y -= 2) {
					Drawer_SetDrawColor(255, 31, 255);
					Drawer_FillRect(x - 4, y - 1, 8, 2);
					Drawer_SetDrawColor(255, 255, 255);
					Drawer_FillRect(x - 1, y - 1, 2, 2);
					x += Random_IRange(-1, 1) * 2;
				}
				break;
			case 9907:
				for (; y > 0; y -= 4) {
					Drawer_SetDrawColor(127, 0, 127);
					Drawer_FillRect(x - 16, y - 1, 32, 4);
					Drawer_SetDrawColor(255, 0, 255);
					Drawer_FillRect(x - 6, y - 1, 12, 4);
					Drawer_SetDrawColor(255, 255, 255);
					Drawer_FillRect(x - 3, y - 1, 6, 4);
					x += Random_IRange(-1, 1) * 2;
				}
				break;
			case 9908:
				Drawer_SetDrawColor(255, 0, 255);
				Drawer_DrawSprite(SPR_misc_subspace_beam, x, y, (battle.sparks[i].timer / 2) % 5, 2 - Max(0, battle.sparks[i].timer - 30) * 0.2, 2);
				break;
			case 9909:
				Drawer_SetDrawColor(255, 0, 0);
				Drawer_DrawSprite(SPR_misc_subspace_beam, x, y, (battle.sparks[i].timer / 2) % 5, 0.8 - Max(0, battle.sparks[i].timer - 30) * 0.08, 2);
				break;
			case 9910:
				Drawer_DrawSprite(SPR_spark_ring, x, y, 3, battle.sparks[i].timer, battle.sparks[i].timer);
				break;
		}
	}
	
	Drawer_SetFontAlignment(FONT_ALIGN_MIDDLE | FONT_ALIGN_BOTTOM);
	
	for (int i = 0; i < 16; i++) {
		if (battle.label[i].timer < 0) continue;
		
		switch (battle.label[i].color) {
			case 1: Drawer_SetDrawColor(255, 255, 0); break;
			case 2: Drawer_SetDrawColor(127, 127, 127); break;
			case 3: Drawer_SetDrawColor(255, 127, 0); break;
			case 4: Drawer_SetDrawColor(0, 255, 0); break;
			case 5: Drawer_SetDrawColor(0, 127, 255); break;
			case 6: Drawer_SetDrawColor(0, 255, 255); break;
		}
		
		Drawer_DrawText(battle.label[i].string, 16, battle.label[i].x, battle.label[i].y, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	
	
	
	if (battle.encounter == 55 && battle.battleEventVars[1] >= 2 && battle.battleEventVars[1] < 999) {
		Drawer_SetProjection(battle.camera.x, battle.camera.y, battle.camera.zoom);
		Drawer_SetDrawColor(0, 0, 0);
		
		Battle_ShakeScreen(2);
		for (int y = -64 + 2 * ((game.timer / 32) % 2); y < SCREEN_HEIGHT + 128; y += 4) {
			Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 2);
		}
		
		if (battle.battleEventVars[1] >= 8) {
			Battle_ShakeScreen(3);
			for (int y = -64 + 4 * ((game.timer / 25) % 2); y < SCREEN_HEIGHT + 128; y += 8) {
				Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 4);
			}
		}
		
		if (battle.battleEventVars[1] >= 19) {
			Battle_ShakeScreen(5);
			for (int y = -64 + 6 * ((game.timer / 17) % 2); y < SCREEN_HEIGHT + 128; y += 12) {
				Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 6);
			}
		}
		
		if (battle.battleEventVars[1] >= 19) {
			Battle_ShakeScreen(7);
			for (int y = -64 + 8 * ((game.timer / 16) % 2); y < SCREEN_HEIGHT + 128; y += 16) {
				Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 8);
			}
		}
		
		if (battle.battleEventVars[1] >= 19) {
			Battle_ShakeScreen(9);
			for (int y = -64 + 10 * ((game.timer / 15) % 2); y < SCREEN_HEIGHT + 128; y += 20) {
				Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 10);
			}
		}
		
		if (battle.battleEventVars[1] >= 19) {
			Battle_ShakeScreen(11);
			for (int y = -64 + 12 * ((game.timer / 14) % 2); y < SCREEN_HEIGHT + 128; y += 24) {
				Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 12);
			}
		}
		
		if (battle.battleEventVars[1] >= 19) {
			Battle_ShakeScreen(15);
			for (int y = -64 + 14 * ((game.timer / 13) % 2); y < SCREEN_HEIGHT + 128; y += 28) {
				Drawer_FillRect(-200, y, SCREEN_WIDTH + 400, 14);
			}
		}
		
		Drawer_SetDrawColor(255, 255, 255);
		
		if (battle.battleEventVars[1] >= 9) {
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			Drawer_SetDrawColor(255, 0, 0);
			Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		
		if (battle.battleEventVars[1] >= 10) {
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			int size = 4;
			for (int y = 0; y < SCREEN_HEIGHT; y += size)
			for (int x = 0; x < SCREEN_WIDTH; x += size) {
				int level = Random_IRange(36, 144);
				Drawer_SetDrawColor(level, 0, 0);
				Drawer_FillRect(x, y, size, size);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		else if (battle.battleEventVars[1] >= 9) {
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			int size = 4;
			for (int y = 0; y < SCREEN_HEIGHT; y += size)
			for (int x = 0; x < SCREEN_WIDTH; x += size) {
				int level = Random_IRange(32, 128);
				Drawer_SetDrawColor(level, 0, 0);
				Drawer_FillRect(x, y, size, size);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		else if (battle.battleEventVars[1] >= 8) {
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			int size = 4;
			for (int y = 0; y < SCREEN_HEIGHT; y += size)
			for (int x = 0; x < SCREEN_WIDTH; x += size) {
				int level = Random_IRange(8, 80);
				Drawer_SetDrawColor(level, 0, 0);
				Drawer_FillRect(x, y, size, size);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		else if (battle.battleEventVars[1] >= 7) {
			Drawer_SetDrawBlend(BLENDMODE_ADD);
			int size = 4;
			for (int y = 0; y < SCREEN_HEIGHT; y += size)
			for (int x = 0; x < SCREEN_WIDTH; x += size) {
				int level = Random_IRange(0, 48);
				Drawer_SetDrawColor(level, 0, 0);
				Drawer_FillRect(x, y, size, size);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		
		if (battle.battleEventVars[1] >= 6) {
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			int size = 4;
			for (int y = 0; y < SCREEN_HEIGHT; y += size)
			for (int x = 0; x < SCREEN_WIDTH; x += size) {
				int level = Random_IRange(32, 160);
				Drawer_SetDrawColor(level, level, level);
				Drawer_FillRect(x, y, size, size);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		else if (battle.battleEventVars[1] >= 3) {
			Drawer_SetDrawBlend(BLENDMODE_MUL);
			int size = 4;
			for (int y = 0; y < SCREEN_HEIGHT; y += size)
			for (int x = 0; x < SCREEN_WIDTH; x += size) {
				int level = Random_IRange(160, 255);
				Drawer_SetDrawColor(level, level, level);
				Drawer_FillRect(x, y, size, size);
			}
			Drawer_SetDrawBlend(BLENDMODE_BLEND);
		}
		Drawer_SetDrawColor(255, 255, 255);
	}
}

void Battle_DrawFighterPortrait(Fighter* fighter, int x, int y) {
	if (fighter->bodyId > 0) {
		if (battleBodyData[fighter->bodyId].spriteId == SPR_misc_gemini) {
			Drawer_DrawSprite(SPR_misc_gemini, x, y, fighter->headId, 2, 2);
			return;
		}
		if (battleBodyData[fighter->bodyId].spriteId == SPR_misc_dystal) {
			Drawer_DrawSprite(SPR_misc_dystal, x, y, fighter->headId, 2, 2);
			return;
		}
		if (battleBodyData[fighter->bodyId].spriteId == SPR_misc_dystal_final) {
			Drawer_DrawSprite(SPR_misc_dystal_final, x, y, 0, 2, 2);
			return;
		}
		if (battleBodyData[fighter->bodyId].spriteId == SPR_misc_helltree) {
			return;
		}
	}
	
	if (fighter->headId > 0) {
		int subImage = fighter->alive ? 0 : 2;
		if (battleHeadData[fighter->headId].backSpriteId >= 0) Drawer_DrawSprite(battleHeadData[fighter->headId].backSpriteId, x, y, subImage, 2, 2);
		Drawer_DrawSprite(battleHeadData[fighter->headId].spriteId, x, y, subImage, 2, 2);
	}
	else if (fighter->bodyId > 0) {
		int subImage = fighter->alive ? FIGHTER_STATE_IDLE : FIGHTER_STATE_HURT;
		Drawer_DrawSprite(battleBodyData[fighter->bodyId].spriteId, x, y + 2, subImage, 2, 2);
	}
}

void Battle_DrawFighterProfile(Fighter* fighter) {
	Battle_DrawFighterPortrait(fighter, SCREEN_WIDTH - 28, 52);
	
	Drawer_SetFontAlignment(FONT_ALIGN_RIGHT | FONT_ALIGN_TOP);
	Drawer_DrawText(fighter->name, 32, SCREEN_WIDTH - 64, 4, 2, 2);
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	Drawer_SetDrawColor(63, 63, 63);
	Drawer_FillRect(460, 66, 128, 16);
	Drawer_FillRect(460, 90, 128, 16);
	Drawer_SetDrawColor(0, 0, 0);
	Drawer_FillRect(462, 68, 124, 12);
	Drawer_FillRect(462, 92, 124, 12);
	
	Drawer_SetDrawColor(255, 0, 0);
	Drawer_FillRect(462, 68, fighter->hp * 124 / fighter->hpMax, 12);
	Drawer_SetDrawColor(0, 255, 255);
	Drawer_FillRect(462, 92, fighter->mp * 124 / fighter->mpMax, 12);
	
	Drawer_SetDrawColor(255, 255, 255);
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_CENTER);
	
	Drawer_DrawText("HP", 32, 592, 72, 2, 2);
	Drawer_DrawText("MP", 32, 592, 96, 2, 2);
	
	Drawer_SetFontAlignment(FONT_ALIGN_RIGHT | FONT_ALIGN_CENTER);
	
	snprintf(game.textBuffer, 32, "%d", fighter->hp);
	Drawer_DrawText(game.textBuffer, 32, 456, 72, 2, 2);
	snprintf(game.textBuffer, 32, "%d", fighter->mp);
	Drawer_DrawText(game.textBuffer, 32, 456, 96, 2, 2);
	
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
}

void Battle_DrawFighterProfileAction(Fighter* fighter) {
	int statusCount = 0;
	for (int j = 0; j < 32; j++) {
		if (!statusEffectData[j].visible) continue;
		if (fighter->status[j] > 0) statusCount++;
	}
	
	if (statusCount > 0) {
		DrawDialogBox(320 - fighter->side * 320, 128, 320, 16 + statusCount * 24);
		
		Drawer_SetFontSprite(SPR_font_small);
		int c = 0;
		for (int i = 0; i < 32; i++) {
			if (fighter->status[i] <= 0) continue;
			if (!statusEffectData[i].visible) continue;
			
			if (statusEffectData[i].stackable) {
				snprintf(game.textBuffer, 128, "%d", fighter->status[i]);
				Drawer_DrawText(game.textBuffer, 4, 330 - fighter->side * 320, 140 + c * 24, 2, 2);
			}
			Drawer_DrawSprite(SPR_gui_status, 364 - fighter->side * 320, 146 + c * 24, i, 2, 2);
			snprintf(game.textBuffer, 128, "%s: %s", statusEffectData[i].name, statusEffectData[i].desc);
			Drawer_DrawText(game.textBuffer, 32, 376 - fighter->side * 320, 140 + c * 24, 2, 2);
			c++;
		}
		Drawer_SetFontSprite(SPR_font_main);
	}
	
	if (fighter->actionId > 0) {
		snprintf(game.textBuffer, 128, "%s", actionData[fighter->actionId].name);
		Drawer_DrawText(game.textBuffer, 128, 8, 4, 2, 2);
		
		if (actionData[fighter->actionId].targetType != TARGETTYPE_NONE) {
			Drawer_DrawText("Target:", 128, 8, 60, 2, 2);
			if (fighter->targetId == TARGET_ALLYPARTY) {
				int c = 0;
				for (int i = 0; i < 8; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					Battle_DrawFighterPortrait(fighter2, 152 + c * 32, 92);
					c++;
				}
			}
			else if (fighter->targetId == TARGET_ENEMYPARTY) {
				int c = 0;
				for (int i = 8; i < 16; i++) {
					Fighter* fighter2 = &battle.fighters[i];
					if (!fighter2->enabled || !fighter2->alive) continue;
					
					Battle_DrawFighterPortrait(fighter2, 152 + c * 32, 92);
					c++;
				}
			}
			else if (fighter->targetId >= 0) {
				Battle_DrawFighterPortrait(&battle.fighters[fighter->targetId], 152, 92);
			}
		}
		
		DrawActionDetailBox(fighter->actionId, 0, SCREEN_HEIGHT - 128, fighter->manaCostReduction, false, false);
	}
	else {
		Drawer_DrawText("No action", 128, 8, 4, 2, 2);
	}
}



void Battle_ChangeMenu(int id) {
	switch (id) {
		case 0:
			{
				bool hasItems = false;
				for (int i = 0; i < 16; i++) {
					if (profile.itemInventory[i] == 0) continue;
					
					bool skip = false;
					
					for (int j = 0; j < 8; j++) {
						Fighter* fighter = &battle.fighters[j];
						if (!fighter->enabled || !fighter->alive) continue;
						
						if (fighter->usedItemId > 0 && fighter->usedItemSlot == i) {
							skip = true;
							break;
						}
					}
					
					if (skip) continue;
					
					hasItems = true;
					break;
				}
				
				Menu_New(&battle.menu, 0, 1, 4, 0);
				Menu_AddOption(&battle.menu, battle.fighters[battle.turn].canAct && battle.fighters[battle.turn].movesetCount > 0, 0, "Fight");
				Menu_AddOption(&battle.menu, !battle.everythingButSkillsDisabled, 1, "Check");
				Menu_AddOption(&battle.menu, !battle.everythingButSkillsDisabled && battle.fighters[battle.turn].canAct && profile.itemInventory[0] > 0 && hasItems, 2, "Goods");
				Menu_AddOption(&battle.menu, !battle.everythingButSkillsDisabled, 3, "Do Nothing");
			}
			break;
		case 1:
			Menu_New(&battle.menu, 1, 2, 4, 1);
			for (int i = 0; i < battle.fighters[battle.turn].movesetCount; i++) {
				Menu_AddOption(&battle.menu, battle.fighters[battle.turn].mp >= Max(0, actionData[battle.fighters[battle.turn].moveset[i]].cost - battle.fighters[battle.turn].manaCostReduction) && !battle.fighters[battle.turn].movesetDisabled[i], battle.fighters[battle.turn].moveset[i], actionData[battle.fighters[battle.turn].moveset[i]].name);
			}
			break;
		case 2:
			Menu_New(&battle.menu, 2, 16, 1, 2);
			if (actionData[battle.fighters[battle.turn].actionId].targetType == TARGETTYPE_ENEMY) {
				for (int i = 8; i < 16; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled || !fighter->alive) continue;
					
					Menu_AddOption(&battle.menu, true, i, fighter->name);
				}
			}
			else if (actionData[battle.fighters[battle.turn].actionId].targetType == TARGETTYPE_ALLY) {
				for (int i = 0; i < 8; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled || !fighter->alive) continue;
					
					Menu_AddOption(&battle.menu, true, i, fighter->name);
				}
			}
			else if (actionData[battle.fighters[battle.turn].actionId].targetType == TARGETTYPE_ANY) {
				for (int i = 0; i < 16; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled || !fighter->alive) continue;
					
					Menu_AddOption(&battle.menu, true, i, fighter->name);
				}
			}
			else if (actionData[battle.fighters[battle.turn].actionId].targetType == TARGETTYPE_DOWNALLY) {
				for (int i = 0; i < 8; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled || fighter->alive) continue;
					
					Menu_AddOption(&battle.menu, true, i, fighter->name);
				}
			}
			break;
		case 3:
			Menu_New(&battle.menu, 3, 2, 4, 1);
			for (int i = 0; i < 16; i++) {
				if (profile.itemInventory[i] == 0) continue;
				
				bool skip = false;
				
				for (int j = 0; j < 8; j++) {
					Fighter* fighter = &battle.fighters[j];
					if (!fighter->enabled || !fighter->alive) continue;
					
					if (fighter->usedItemId > 0 && fighter->usedItemSlot == i) {
						skip = true;
						break;
					}
				}
				
				if (skip) continue;
				
				Item* item = &itemData[profile.itemInventory[i]];
				
				Menu_AddOption(&battle.menu, item->actionId > 0, i, item->name);
			}
			break;
		case 4:
			Menu_New(&battle.menu, 4, 16, 1, 1);
			for (int i = 0; i < 16; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Menu_AddOption(&battle.menu, true, i, fighter->name);
			}
			break;
		case 5:
			Menu_New(&battle.menu, 5, 1, 4, 1);
			Menu_AddOption(&battle.menu, battle.canFlee, 0, "Flee");
			Menu_AddOption(&battle.menu, true, 1, "Retry Fight");
			Menu_AddOption(&battle.menu, true, 2, "Load Last Save");
			break;
	}
}



void DrawFighterChar(int headId, int bodyId, int state, float x, float y, float xScale, float yScale, int facing) {
	if (headId < 0 || headId >= OBJECT_COUNT_MAX || bodyId < 0 || bodyId >= OBJECT_COUNT_MAX) return;
	BattleHead* battleHead = &battleHeadData[headId];
	BattleBody* battleBody = &battleBodyData[bodyId];
	
	int headFrame = battleBody->headFrame[state] & 0xffff;
	int headFlags = battleBody->headFrame[state] & (~0xffff);
	float headOffsetX = battleBody->headOffsetX[state];
	float headOffsetY = battleBody->headOffsetY[state];
	
	float headXScale = 1;
	float headYScale = 1;
	
	if (headFlags & BATTLEBODY_HEAD_MIRROR) headXScale = -headXScale;
	if (headFlags & BATTLEBODY_HEAD_FLIP) headYScale = -headYScale;
	
	if (battleBody->spriteId == SPR_misc_pbsuperhero) {
		Drawer_DrawSprite(SPR_misc_pbsuperhero, x, y, (game.timer / 8) % 3, xScale, yScale);
		return;
	}
	if (battleBody->spriteId == SPR_misc_hellgateboss) {
		Drawer_DrawSprite(SPR_misc_hellgateboss, x, y, (game.timer / 16) % 3, xScale, yScale);
		return;
	}
	if (battleBody->spriteId == SPR_misc_gemini) {
		if (state == FIGHTER_STATE_DOWN) {
			Drawer_DrawSprite(SPR_misc_gemini_collapsed, x, y, headId, xScale, yScale);
			return;
		}
		Drawer_DrawSprite(SPR_misc_gemini, x, y, headId, xScale, yScale);
		return;
	}
	if (battleBody->spriteId == SPR_misc_dystal) {
		Drawer_DrawSprite(SPR_misc_dystal, x, y, headId, xScale, yScale);
		return;
	}
	if (battleBody->spriteId == SPR_misc_dystal_final) {
		Drawer_DrawSprite(SPR_misc_dystal_final, x, y, (game.timer / 2) % 6, xScale, yScale);
		return;
	}
	if (battleBody->spriteId == SPR_misc_helltree) {
		Drawer_DrawSprite(SPR_misc_helltree, x, y, (game.timer / 48) % 2, xScale, yScale);
		return;
	}
	
	if (battleHead->backSpriteId >= 0) Drawer_DrawSprite(battleHead->backSpriteId, x + headOffsetX * facing * xScale, y + headOffsetY * yScale, headFrame, facing * xScale * headXScale, yScale * headYScale);
	if (state != FIGHTER_STATE_BLOCK && battleBody->spriteId >= 0) Drawer_DrawSprite(battleBody->spriteId, x, y, state, facing * xScale, yScale);
	if (battleHead->spriteId >= 0) Drawer_DrawSprite(battleHead->spriteId, x + headOffsetX * facing * xScale, y + headOffsetY * yScale, headFrame, facing * xScale * headXScale, yScale * headYScale);
	if (state == FIGHTER_STATE_BLOCK && battleBody->spriteId >= 0) Drawer_DrawSprite(battleBody->spriteId, x, y, state, facing * xScale, yScale);
}
