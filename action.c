#include "generic.h"
#include "action.h"
#include "battlesystem.h"
#include "sprites.h"
#include "audio.h"
#include "dialog.h"
#include "items.h"
#include "ai.h"
#include "profile.h"

const int ACTION_DELAYTIME_MAX = 180;

Action actionData[OBJECT_COUNT_MAX];
ActionAnim actionAnimData[OBJECT_COUNT_MAX];
ActionUpdateFunction actionUpdateCode[OBJECT_COUNT_MAX];
ActionDrawFunction actionDrawCode[OBJECT_COUNT_MAX];
ActionAnimFunction actionAnimUpdateCode[OBJECT_COUNT_MAX];
ActionAnimFunction actionAnimDrawCode[OBJECT_COUNT_MAX];

void LoadActionData() {
	Action* action;
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		actionData[i].armorOnlyId = 0;
		actionData[i].ranged = false;
		actionData[i].condition = ACTIONCONDITION_NONE;
		actionData[i].conditionVars[0].i = 0; actionData[i].conditionVars[1].i = 0; actionData[i].conditionVars[2].i = 0; actionData[i].conditionVars[3].i = 0;
		actionData[i].power[0] = -1; actionData[i].power[1] = -1; actionData[i].power[2] = -1; actionData[i].power[3] = -1;
		actionData[i].powerRepeat = 1;
	}
	
	action = &actionData[0];
	SetString(action->name, "nothing");
	action->descriptionDialogId = 5000;
	action->cost = 0;
	action->priority = 0;
	action->codeId = 0;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->power[0] = 0;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	
	action = &actionData[1];
	SetString(action->name, "Poke");
	action->descriptionDialogId = 5001;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 1;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	
	action = &actionData[2];
	SetString(action->name, "Cut In");
	action->descriptionDialogId = 5002;
	action->cost = 2;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 333;
	action->vars[1].i = 0;
	
	action = &actionData[3];
	SetString(action->name, "Ruthless Swing");
	action->descriptionDialogId = 5003;
	action->cost = 5;
	action->priority = 1;
	action->codeId = 2;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5; action->power[1] = 1;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 5;
	action->vars[1].i = 1;
	
	action = &actionData[4];
	SetString(action->name, "Chop");
	action->descriptionDialogId = 5004;
	action->cost = 4;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 5;
	action->vars[1].i = 1;
	
	action = &actionData[5];
	SetString(action->name, "Swing");
	action->descriptionDialogId = 5005;
	action->cost = 1;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 1;
	
	action = &actionData[6];
	SetString(action->name, "Swing 'n Stab");
	action->descriptionDialogId = 5006;
	action->cost = 3;
	action->priority = 1;
	action->codeId = 2;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2; action->power[1] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 2;
	
	action = &actionData[7];
	SetString(action->name, "Fresh Air");
	action->descriptionDialogId = 5007;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 6;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[8];
	SetString(action->name, "Final Leaves");
	action->descriptionDialogId = 5008;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 4;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6; action->power[1] = 3; action->power[2] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 6;
	action->vars[1].i = 3;
	action->vars[2].i = 2;
	
	action = &actionData[9];
	SetString(action->name, "Vine Impale");
	action->descriptionDialogId = 5009;
	action->cost = 3;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = 4;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 4;
	action->vars[1].i = 0;
	
	action = &actionData[10];
	SetString(action->name, "Vine Slow");
	action->descriptionDialogId = 5010;
	action->cost = 12;
	action->armorOnlyId = 15;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 5;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 9;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 8;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 10;
	
	action = &actionData[11];
	SetString(action->name, "Vine Dragdown");
	action->descriptionDialogId = 5011;
	action->cost = 17;
	action->armorOnlyId = 15;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 5;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 10;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 9;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 16;
	
	action = &actionData[12];
	SetString(action->name, "Blob Slow");
	action->descriptionDialogId = 5012;
	action->cost = 3;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 4;
	
	action = &actionData[13];
	SetString(action->name, "Slime Crash");
	action->descriptionDialogId = 5013;
	action->cost = 8;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 7;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 7;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 6;
	
	action = &actionData[14];
	SetString(action->name, "Magic Slash");
	action->descriptionDialogId = 5014;
	action->cost = 7;
	action->priority = 1;
	action->codeId = 7;
	action->animationId = 18;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3; action->power[1] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 4;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 2;
	
	action = &actionData[15];
	SetString(action->name, "Water Blasts");
	action->descriptionDialogId = 5015;
	action->cost = 25;
	action->armorOnlyId = 28;
	action->priority = 2;
	action->codeId = 6;
	action->animationId = 13;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3; action->power[1] = 3; action->power[2] = 3; action->power[3] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 3;
	action->vars[1].i = 15;
	
	action = &actionData[16];
	SetString(action->name, "Flame Orb");
	action->descriptionDialogId = 5016;
	action->cost = 25;
	action->armorOnlyId = 28;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 12;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 15;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_BURN;
	action->vars[3].i = 8;
	
	action = &actionData[17];
	SetString(action->name, "Omega Slash");
	action->descriptionDialogId = 5017;
	action->cost = 50;
	action->armorOnlyId = 27;
	action->priority = 1;
	action->codeId = 8;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 9;
	action->powerRepeat = 6;
	action->attackMultiplier = 1;
	action->vars[0].i = 6;
	action->vars[1].i = 0;
	
	action = &actionData[18];
	SetString(action->name, "Fire Chop");
	action->descriptionDialogId = 5018;
	action->cost = 8;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 5;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BURN;
	action->vars[3].i = 3;
	
	action = &actionData[19];
	SetString(action->name, "Dual Blaze");
	action->descriptionDialogId = 5019;
	action->cost = 18;
	action->priority = 1;
	action->codeId = 7;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5; action->power[1] = 5;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 5;
	action->vars[1].i = 5;
	action->vars[2].i = FIGHTER_STATUS_BURN;
	action->vars[3].i = 4;
	
	action = &actionData[20];
	SetString(action->name, "Rage Swing");
	action->descriptionDialogId = 5020;
	action->cost = 17;
	action->priority = 1;
	action->codeId = 9;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 17;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 16;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_STRENGTH;
	action->vars[3].i = 15;
	
	action = &actionData[21];
	SetString(action->name, "Bite");
	action->descriptionDialogId = 5021;
	action->cost = 2;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 1;
	
	action = &actionData[22];
	SetString(action->name, "Venom Bite");
	action->descriptionDialogId = 5022;
	action->cost = 6;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 3;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_POISON;
	action->vars[3].i = 3;
	
	action = &actionData[23];
	SetString(action->name, "Tear Apart");
	action->descriptionDialogId = 5023;
	action->cost = 18;
	action->priority = 1;
	action->codeId = 7;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8; action->power[1] = 9;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 8;
	action->vars[1].i = 9;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 2;
	
	action = &actionData[24];
	SetString(action->name, "Web Shot");
	action->descriptionDialogId = 5024;
	action->cost = 8;
	action->priority = 2;
	action->codeId = 10;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 0;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = FIGHTER_STATUS_BIND;
	action->vars[2].i = 20;
	
	action = &actionData[25];
	SetString(action->name, "Guard");
	action->descriptionDialogId = 5025;
	action->cost = 0;
	action->priority = 2;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 2;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[26];
	SetString(action->name, "Protect");
	action->descriptionDialogId = 5026;
	action->cost = 1;
	action->priority = 2;
	action->codeId = 12;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 3;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[27];
	SetString(action->name, "Wound Heal");
	action->descriptionDialogId = 5027;
	action->cost = 5;
	action->priority = 1;
	action->codeId = 13;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 10;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[28];
	SetString(action->name, "Blaze Oblivion");
	action->descriptionDialogId = 5028;
	action->cost = 45;
	action->priority = 1;
	action->codeId = 14;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 25;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 15;
	action->vars[1].i = FIGHTER_STATUS_BURN;
	action->vars[2].i = 8;
	
	action = &actionData[29];
	SetString(action->name, "Takedown");
	action->descriptionDialogId = 5029;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 9;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 9;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_DISARM;
	action->vars[3].i = 2;
	
	action = &actionData[30];
	SetString(action->name, "A Load of This");
	action->descriptionDialogId = 5030;
	action->cost = 5;
	action->priority = 1;
	action->codeId = 15;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 4;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_HASTE;
	action->vars[3].i = 12;
	
	action = &actionData[31];
	SetString(action->name, "Just Dancing");
	action->descriptionDialogId = 5031;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 16;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3; action->power[1] = 1;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 4;
	action->vars[1].i = 1;
	
	action = &actionData[32];
	SetString(action->name, "Handshake");
	action->descriptionDialogId = 5032;
	action->cost = 3;
	action->armorOnlyId = 24;
	action->priority = 1;
	action->codeId = 17;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_EXHAUST;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 7;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 7;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 3;
	
	action = &actionData[33];
	SetString(action->name, "Disassembly");
	action->descriptionDialogId = 5033;
	action->cost = 9;
	action->armorOnlyId = 25;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 3;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_DISARM;
	action->vars[3].i = 4;
	
	action = &actionData[34];
	SetString(action->name, "Undercharge");
	action->descriptionDialogId = 5034;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 18;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 9; action->power[1] = 6; action->power[2] = 6;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 9;
	action->vars[1].i = 6;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 12;
	
	action = &actionData[35];
	SetString(action->name, "Shuriken Throw");
	action->descriptionDialogId = 5035;
	action->cost = 4;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 6;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 3;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 2;
	
	action = &actionData[36];
	SetString(action->name, "Calm Down");
	action->descriptionDialogId = 5036;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 8;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[37];
	SetString(action->name, "Beatdown");
	action->descriptionDialogId = 5037;
	action->cost = 22;
	action->priority = 1;
	action->codeId = 4;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 7; action->power[1] = 8; action->power[2] = 11;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 7;
	action->vars[1].i = 8;
	action->vars[2].i = 11;
	
	action = &actionData[38];
	SetString(action->name, "Blunt Strike");
	action->descriptionDialogId = 5038;
	action->cost = 11;
	action->priority = 1;
	action->codeId = 19;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 6;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 4;
	
	action = &actionData[39];
	SetString(action->name, "Hook Pin");
	action->descriptionDialogId = 5039;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 15;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_STRENGTH;
	action->vars[3].i = 15;
	
	action = &actionData[40];
	SetString(action->name, "X-Slash");
	action->descriptionDialogId = 5040;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 7;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4; action->power[1] = 4;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 4;
	action->vars[1].i = 4;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 3;
	
	action = &actionData[41];
	SetString(action->name, "Counter");
	action->descriptionDialogId = 5041;
	action->cost = 8;
	action->priority = 2;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_COUNTER;
	action->vars[1].i = 2;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[42];
	SetString(action->name, "Razor Chaos");
	action->descriptionDialogId = 5042;
	action->cost = 25;
	action->armorOnlyId = 34;
	action->priority = 1;
	action->codeId = 20;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 8;
	action->vars[1].i = FIGHTER_STATUS_BLEED;
	action->vars[2].i = 4;
	
	action = &actionData[43];
	SetString(action->name, "Kunai");
	action->descriptionDialogId = 5043;
	action->cost = 13;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 11;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 1;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 1;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_TIMEDBOMB;
	action->vars[3].i = 15;
	
	action = &actionData[44];
	SetString(action->name, "Meditation");
	action->descriptionDialogId = 5044;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_HASTE;
	action->vars[1].i = 18;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[45];
	SetString(action->name, "Blink Speed");
	action->descriptionDialogId = 5045;
	action->cost = 15;
	action->priority = 2;
	action->codeId = 21;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 0;
	
	action = &actionData[46];
	SetString(action->name, "Stun Shot");
	action->descriptionDialogId = 5046;
	action->cost = 16;
	action->ranged = true;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 7;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 12;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 8;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 6;
	
	action = &actionData[47];
	SetString(action->name, "Secret Technique");
	action->descriptionDialogId = 5047;
	action->cost = 25;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = 8;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_HPHALF;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 33;
	action->attackMultiplier = 1;
	action->vars[0].i = 33;
	action->vars[1].i = 0;
	
	action = &actionData[48];
	SetString(action->name, "Shield Protect");
	action->descriptionDialogId = 5048;
	action->cost = 6;
	action->priority = 2;
	action->codeId = 12;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 6;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[49];
	SetString(action->name, "Heavy Strike");
	action->descriptionDialogId = 5049;
	action->cost = 8;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 7;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 1;
	
	action = &actionData[50];
	SetString(action->name, "Reload");
	action->descriptionDialogId = 5050;
	action->cost = 4;
	action->ranged = true;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 16;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[51];
	SetString(action->name, "Rapid Fire");
	action->descriptionDialogId = 5051;
	action->cost = 30;
	action->ranged = true;
	action->priority = 2;
	action->codeId = 22;
	action->animationId = 7;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8; action->power[1] = 8; action->power[2] = 8; action->power[3] = 8;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 8;
	action->vars[1].i = 4;
	
	action = &actionData[52];
	SetString(action->name, "Rocket Launch");
	action->descriptionDialogId = 5052;
	action->cost = 55;
	action->armorOnlyId = 38;
	action->priority = 2;
	action->codeId = 23;
	action->animationId = 9;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 26;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 26;
	action->vars[1].i = 10;
	action->vars[2].i = FIGHTER_STATUS_BURN;
	action->vars[3].i = 2;
	
	action = &actionData[53];
	SetString(action->name, "Pulse Laser");
	action->descriptionDialogId = 5053;
	action->cost = 27;
	action->ranged = true;
	action->armorOnlyId = 39;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 14;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 21;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 14;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 10;
	
	action = &actionData[54];
	SetString(action->name, "Breaking Beam");
	action->descriptionDialogId = 5054;
	action->cost = 99;
	action->ranged = true;
	action->armorOnlyId = 39;
	action->priority = 2;
	action->codeId = 26;
	action->animationId = 15;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 1;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->powerRepeat = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 60;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 8;
	
	action = &actionData[55];
	SetString(action->name, "Amp Charge");
	action->descriptionDialogId = 5055;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 69;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 55;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_IMMOBILE;
	action->vars[3].i = 1;
	
	action = &actionData[56];
	SetString(action->name, "Lawnstrike");
	action->descriptionDialogId = 5056;
	action->cost = 6;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 3;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_FLOWER;
	action->vars[3].i = 3;
	
	action = &actionData[57];
	SetString(action->name, "Flower Recover");
	action->descriptionDialogId = 5057;
	action->cost = 14;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 70;
	action->vars[2].i = FIGHTER_STATUS_FLOWER;
	action->vars[3].i = 12;
	
	action = &actionData[58];
	SetString(action->name, "Flower Relax");
	action->descriptionDialogId = 5058;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 40;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_FLOWER;
	action->vars[3].i = 9;
	
	action = &actionData[59];
	SetString(action->name, "Petal Blast");
	action->descriptionDialogId = 5059;
	action->cost = 42;
	action->armorOnlyId = 43;
	action->priority = 2;
	action->codeId = 28;
	action->animationId = 17;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 24;
	action->attackMultiplier = 1;
	action->vars[0].i = 24;
	action->vars[1].i = 0;
	
	action = &actionData[60];
	SetString(action->name, "Spring Funeral");
	action->descriptionDialogId = 5060;
	action->cost = 64;
	action->armorOnlyId = 43;
	action->priority = 2;
	action->codeId = 29;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4;
	action->powerRepeat = 8;
	action->attackMultiplier = 0;
	action->vars[0].i = 2;
	
	action = &actionData[61];
	SetString(action->name, "Lightning");
	action->descriptionDialogId = 5061;
	action->cost = 40;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 23;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 1.5;
	action->vars[0].i = 8;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 10;
	
	action = &actionData[62];
	SetString(action->name, "Stomp");
	action->descriptionDialogId = 5062;
	action->cost = 8;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 37;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 1;
	action->vars[0].i = 2;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 3;
	
	action = &actionData[63];
	SetString(action->name, "Electroshock");
	action->descriptionDialogId = 5063;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 10;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 9;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 4;
	
	action = &actionData[64];
	SetString(action->name, "Killer Whip");
	action->descriptionDialogId = 5064;
	action->cost = 23;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->attackMultiplier = 1;
	action->vars[0].i = 15;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 7;
	
	action = &actionData[65];
	SetString(action->name, "Brutal Beatdown");
	action->descriptionDialogId = 5065;
	action->cost = 33;
	action->priority = 1;
	action->codeId = 30;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3; action->power[1] = 7; action->power[2] = 8; action->power[3] = 11;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[66];
	SetString(action->name, "Pancake Recipe");
	action->descriptionDialogId = 5066;
	action->cost = 16;
	action->armorOnlyId = 46;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->attackMultiplier = 1.5;
	action->vars[0].i = 5;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 4;
	
	action = &actionData[67];
	SetString(action->name, "Red Boost");
	action->descriptionDialogId = 5067;
	action->cost = 7;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 20;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_STRENGTH;
	action->vars[1].i = 20;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[68];
	SetString(action->name, "Blue Boost");
	action->descriptionDialogId = 5068;
	action->cost = 7;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 21;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_ENDURANCE;
	action->vars[1].i = 10;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[69];
	SetString(action->name, "Setup Jab");
	action->descriptionDialogId = 5069;
	action->cost = 9;
	action->priority = 1;
	action->codeId = 15;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_HASTE;
	action->vars[3].i = 25;
	
	action = &actionData[70];
	SetString(action->name, "Nature's Pref");
	action->descriptionDialogId = 5070;
	action->cost = 29;
	action->priority = 2;
	action->codeId = 32;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 12;
	action->attackMultiplier = 0;
	action->vars[0].i = 12;
	action->vars[1].i = 40;
	
	action = &actionData[71];
	SetString(action->name, "Ice Freeze");
	action->descriptionDialogId = 5071;
	action->cost = 28;
	action->priority = 2;
	action->codeId = 33;
	action->animationId = 22;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 16;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 16;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_CHILL;
	action->vars[3].i = 10;
	
	action = &actionData[72];
	SetString(action->name, "Mana Regen");
	action->descriptionDialogId = 5072;
	action->cost = 7;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 20;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[73];
	SetString(action->name, "Slap");
	action->descriptionDialogId = 5073;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 24;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 1;
	action->attackMultiplier = 0.25;
	action->vars[0].i = 1;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 2;
	
	action = &actionData[74];
	SetString(action->name, "Power Heal");
	action->descriptionDialogId = 5074;
	action->cost = 25;
	action->priority = 1;
	action->codeId = 13;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 40;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[75];
	SetString(action->name, "Double Shot");
	action->descriptionDialogId = 5075;
	action->cost = 18;
	action->ranged = true;
	action->priority = 2;
	action->codeId = 22;
	action->animationId = 7;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 9; action->power[1] = 9;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 2;
	
	action = &actionData[76];
	SetString(action->name, "Charge Up");
	action->descriptionDialogId = 5076;
	action->cost = 1;
	action->priority = 1;
	action->codeId = 41;
	action->animationId = 35;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_CHARGE;
	action->vars[1].i = 1;
	
	action = &actionData[77];
	SetString(action->name, "Bullet Barrage");
	action->descriptionDialogId = 5077;
	action->cost = 24;
	action->ranged = true;
	action->armorOnlyId = 53;
	action->priority = 2;
	action->codeId = 34;
	action->animationId = 25;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 1;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->powerRepeat = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 8;
	
	action = &actionData[78];
	SetString(action->name, "Dual Ignite");
	action->descriptionDialogId = 5078;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 7;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6; action->power[1] = 6;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 5;
	action->vars[1].i = 5;
	action->vars[2].i = FIGHTER_STATUS_BURN;
	action->vars[3].i = 1;
	
	action = &actionData[79];
	SetString(action->name, "De Ignito");
	action->descriptionDialogId = 5079;
	action->cost = 30;
	action->armorOnlyId = 54;
	action->priority = 1;
	action->codeId = 35;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 10;
	action->vars[1].i = FIGHTER_STATUS_BURN;
	action->vars[2].i = FIGHTER_STATUS_TIMEDBOMB;
	
	action = &actionData[80];
	SetString(action->name, "Air Smite");
	action->descriptionDialogId = 5080;
	action->cost = 36;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 27;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 12;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 18;
	
	action = &actionData[81];
	SetString(action->name, "Eruption Blitz");
	action->descriptionDialogId = 5081;
	action->cost = 60;
	action->armorOnlyId = 54;
	action->priority = 1;
	action->codeId = 36;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->condition = ACTIONCONDITION_HPHALF;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 12;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_TIMEDBOMB;
	action->vars[1].i = 15;
	
	action = &actionData[82];
	SetString(action->name, "Neutralizer");
	action->descriptionDialogId = 5082;
	action->cost = 5;
	action->priority = 1;
	action->codeId = 37;
	action->animationId = 34;
	action->targetType = TARGETTYPE_ANY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 1;
	
	action = &actionData[83];
	SetString(action->name, "Revive");
	action->descriptionDialogId = 5083;
	action->cost = 40;
	action->priority = 1;
	action->codeId = 38;
	action->animationId = -1;
	action->targetType = TARGETTYPE_DOWNALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 20;
	action->vars[1].i = 0;
	
	action = &actionData[84];
	SetString(action->name, "500kV Discharge");
	action->descriptionDialogId = 5084;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 1;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6;
	action->attackMultiplier = 1;
	action->vars[0].i = 6;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 12;
	
	action = &actionData[85];
	SetString(action->name, "Quick Protect");
	action->descriptionDialogId = 5085;
	action->cost = 4;
	action->priority = 3;
	action->codeId = 12;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 3;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[86];
	SetString(action->name, "Saw Massacre");
	action->descriptionDialogId = 5086;
	action->cost = 36;
	action->armorOnlyId = 59;
	action->priority = 1;
	action->codeId = 39;
	action->animationId = 31;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_HPHALF;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 20;
	
	action = &actionData[87];
	SetString(action->name, "Cutter");
	action->descriptionDialogId = 5087;
	action->cost = 8;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 6;
	
	action = &actionData[88];
	SetString(action->name, "Saw Massacre");
	action->descriptionDialogId = 5088;
	action->cost = 36;
	action->armorOnlyId = 59;
	action->priority = 1;
	action->codeId = 19;
	action->animationId = 31;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_HPHALF;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 20;
	
	action = &actionData[89];
	SetString(action->name, "Tri-Knife");
	action->descriptionDialogId = 5089;
	action->cost = 13;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 32;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 9;
	
	action = &actionData[90];
	SetString(action->name, "Knife Rain");
	action->descriptionDialogId = 5090;
	action->cost = 20;
	action->priority = 2;
	action->codeId = 40;
	action->animationId = 33;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3;
	action->attackMultiplier = 0.25;
	action->vars[0].i = FIGHTER_STATUS_BLEED;
	action->vars[1].i = 2;
	
	action = &actionData[91];
	SetString(action->name, "Silver Bullet");
	action->descriptionDialogId = 5091;
	action->cost = 35;
	action->ranged = true;
	action->armorOnlyId = 60;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 36;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 1;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 77;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 24;
	
	action = &actionData[92];
	SetString(action->name, "Bear Rush");
	action->descriptionDialogId = 5092;
	action->cost = 25;
	action->armorOnlyId = 61;
	action->priority = 1;
	action->codeId = 42;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 10;
	action->attackMultiplier = 1.5;
	action->vars[0].i = 10;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 12;
	
	action = &actionData[93];
	SetString(action->name, "Smash");
	action->descriptionDialogId = 5093;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 43;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 11;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 9;
	action->vars[1].i = 1;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[94];
	SetString(action->name, "Enrage");
	action->descriptionDialogId = 5094;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_STRENGTH;
	action->vars[1].i = 20;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[95];
	SetString(action->name, "Resist");
	action->descriptionDialogId = 5095;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_ENDURANCE;
	action->vars[1].i = 10;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[96];
	SetString(action->name, "Gun Shot");
	action->descriptionDialogId = 5096;
	action->cost = 35;
	action->ranged = true;
	action->armorOnlyId = 60;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 36;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 999;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 24;
	
	action = &actionData[97];
	SetString(action->name, "Ultra Protect");
	action->descriptionDialogId = 5097;
	action->cost = 22;
	action->priority = 3;
	action->codeId = 12;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 13;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[98];
	SetString(action->name, "Solidification");
	action->descriptionDialogId = 5098;
	action->cost = 45;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 21;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_ENDURANCE;
	action->vars[1].i = 60;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[99];
	SetString(action->name, "Tsunami");
	action->descriptionDialogId = 5099;
	action->cost = 97;
	action->priority = 2;
	action->codeId = 46;
	action->animationId = 38;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 55;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_DISARM;
	action->vars[1].i = 12;
	
	action = &actionData[100];
	SetString(action->name, "Fox-bidden Trout");
	action->descriptionDialogId = 5100;
	action->cost = 51;
	action->priority = 1;
	action->codeId = 47;
	action->animationId = 39;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_AZTEC_1;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 47;
	action->powerRepeat = 8;
	action->attackMultiplier = 4;
	action->vars[0].i = 8;
	
	action = &actionData[101];
	SetString(action->name, "Tyrannical Claw");
	action->descriptionDialogId = 5101;
	action->cost = 9;
	action->priority = 1;
	action->codeId = 48;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 9;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 20;
	action->vars[1].i = 0;
	
	action = &actionData[102];
	SetString(action->name, "Harsh Readier");
	action->descriptionDialogId = 5102;
	action->cost = 4;
	action->priority = 1;
	action->codeId = 51;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 20;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 1;
	
	action = &actionData[103];
	SetString(action->name, "Osmosis");
	action->descriptionDialogId = 5103;
	action->cost = 15;
	action->priority = 1;
	action->codeId = 49;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 7;
	action->vars[2].i = FIGHTER_STATUS_STRENGTH;
	action->vars[3].i = 2;
	
	action = &actionData[104];
	SetString(action->name, "Cobra Punch");
	action->descriptionDialogId = 5104;
	action->cost = 48;
	action->priority = 1;
	action->codeId = 50;
	action->animationId = 39;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 12;
	action->attackMultiplier = 1;
	
	action = &actionData[105];
	SetString(action->name, "Last Resort");
	action->descriptionDialogId = 5105;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 52;
	action->animationId = 8;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_EXHAUST;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->powerRepeat = 8;
	action->attackMultiplier = 2;
	
	action = &actionData[106];
	SetString(action->name, "Trance");
	action->descriptionDialogId = 5106;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 41;
	action->animationId = 35;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_MANADISCOUNT;
	action->vars[1].i = 20;
	
	action = &actionData[107];
	SetString(action->name, "Long Tension");
	action->descriptionDialogId = 5107;
	action->cost = 5;
	action->priority = 1;
	action->codeId = 41;
	action->animationId = 35;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_MANADISCOUNT;
	action->vars[1].i = 10 | (2 << 16);
	
	action = &actionData[108];
	SetString(action->name, "Wring Out");
	action->descriptionDialogId = 5108;
	action->cost = 7;
	action->priority = 1;
	action->codeId = 53;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].f = 0.75;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[109];
	SetString(action->name, "Brawler Stance");
	action->descriptionDialogId = 5109;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 54;
	action->animationId = 20;
	action->targetType = TARGETTYPE_NONE;
	action->condition = ACTIONCONDITION_EXHAUST_HPHALF;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 15;
	action->vars[1].i = 5;
	action->vars[2].i = 15;
	action->vars[3].i = 40;
	
	action = &actionData[110];
	SetString(action->name, "Wind Up");
	action->descriptionDialogId = 5110;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 41;
	action->animationId = 35;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_ATTACKMULT;
	action->vars[1].i = 100;
	
	action = &actionData[111];
	SetString(action->name, "Evade");
	action->descriptionDialogId = 5111;
	action->cost = 18;
	action->priority = 2;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_EVADE;
	action->vars[1].i = 1;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[112];
	SetString(action->name, "Violent Punish");
	action->descriptionDialogId = 5112;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 55;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 15;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_STRENGTH;
	action->vars[3].i = 10;
	
	action = &actionData[113];
	SetString(action->name, "Boom Mix");
	action->descriptionDialogId = 5113;
	action->cost = 16;
	action->priority = 1;
	action->codeId = 56;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8; action->power[1] = 7; action->power[2] = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 9;
	action->vars[1].i = 1;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[114];
	SetString(action->name, "Shock of Fury");
	action->descriptionDialogId = 5114;
	action->cost = 22;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 26;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_STRENGTH;
	action->vars[3].i = 30;
	
	action = &actionData[115];
	SetString(action->name, "Hyper Punch");
	action->descriptionDialogId = 5115;
	action->cost = 31;
	action->priority = 1;
	action->codeId = 8;
	action->animationId = 1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->powerRepeat = 8;
	action->attackMultiplier = 1.5;
	action->vars[0].i = 8;
	action->vars[1].i = 1;
	
	action = &actionData[116];
	SetString(action->name, "Extreminator");
	action->descriptionDialogId = 5116;
	action->cost = 50;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 20;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_STRENGTH;
	action->vars[1].i = 80;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[117];
	SetString(action->name, "Dark Heal");
	action->descriptionDialogId = 5117;
	action->cost = 20;
	action->priority = 1;
	action->codeId = 13;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 50;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_POISON;
	action->vars[3].i = 12;
	
	action = &actionData[118];
	SetString(action->name, "\x8f\x08""Ca\x8f\x09""m\x8f\x0a""il\x8f\x0b""la\x8f\x0c""bo\x8f\x0d""os\x8f\x0e""t\x8f\xff");
	action->descriptionDialogId = 5118;
	action->cost = 50;
	action->priority = 3;
	action->codeId = 31;
	action->animationId = 40;
	action->targetType = TARGETTYPE_ANY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_CHARGE;
	action->vars[1].i = 1;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[119];
	SetString(action->name, "Trivial Strike");
	action->descriptionDialogId = 5119;
	action->cost = 9;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 25;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	
	action = &actionData[120];
	SetString(action->name, "Indomitable Will");
	action->descriptionDialogId = 5120;
	action->cost = 10;
	action->priority = 2;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 13;
	action->vars[2].i = FIGHTER_STATUS_ENDURANCE;
	action->vars[3].i = 8;
	
	action = &actionData[121];
	SetString(action->name, "Deflect");
	action->descriptionDialogId = 5121;
	action->cost = 9;
	action->priority = 2;
	action->codeId = 12;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 3;
	action->vars[2].i = FIGHTER_STATUS_DEFLECT;
	action->vars[3].i = 3;
	
	action = &actionData[122];
	SetString(action->name, "Demolish");
	action->descriptionDialogId = 5122;
	action->cost = 29;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 41;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 8;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_DISARM;
	action->vars[3].i = 9;
	
	action = &actionData[123];
	SetString(action->name, "Construct Wall");
	action->descriptionDialogId = 5123;
	action->cost = 25;
	action->armorOnlyId = 63;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 43;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_ABSORPTION;
	action->vars[1].i = 80;
	action->vars[2].i = 2;
	action->vars[3].i = 0;
	
	action = &actionData[124];
	SetString(action->name, "Paperplane Fold");
	action->descriptionDialogId = 5124;
	action->cost = 44;
	action->armorOnlyId = 68;
	action->priority = 1;
	action->codeId = 57;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 14; action->power[1] = 40;
	action->attackMultiplier = 1;
	action->vars[0].i = FIGHTER_STATUS_FEEBLE;
	action->vars[1].i = 15;
	action->vars[2].i = 24;
	
	action = &actionData[125];
	SetString(action->name, "Slick Robber");
	action->descriptionDialogId = 5125;
	action->cost = 45;
	action->armorOnlyId = 71;
	action->priority = 1;
	action->codeId = 58;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 1;
	action->powerRepeat = 16;
	action->attackMultiplier = 4;
	action->vars[0].i = 2;
	action->vars[1].i = 0;
	
	action = &actionData[126];
	SetString(action->name, "Mass Deflect");
	action->descriptionDialogId = 5126;
	action->cost = 20;
	action->priority = 2;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->vars[0].i = FIGHTER_STATUS_DEFLECT;
	action->vars[1].i = 6;
	action->vars[2].i = FIGHTER_STATUS_GUARD;
	action->vars[3].i = 5;
	
	action = &actionData[127];
	SetString(action->name, "Dismantler");
	action->descriptionDialogId = 5127;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 59;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15; action->power[1] = 17;
	action->attackMultiplier = 1;
	action->vars[0].i = 10;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_DISARM;
	action->vars[3].i = 1;
	
	action = &actionData[128];
	SetString(action->name, "Exposer");
	action->descriptionDialogId = 5128;
	action->cost = 28;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 12;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_ANTIGUARD;
	action->vars[3].i = 1;
	
	action = &actionData[129];
	SetString(action->name, "LaserRob");
	action->descriptionDialogId = 5129;
	action->cost = 36;
	action->ranged = true;
	action->armorOnlyId = 71;
	action->priority = 2;
	action->codeId = 60;
	action->animationId = 44;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->powerRepeat = 8;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_BURN;
	action->vars[1].i = 1;
	
	action = &actionData[130];
	SetString(action->name, "Red Nerf");
	action->descriptionDialogId = 5130;
	action->cost = 9;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 45;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_FEEBLE;
	action->vars[1].i = 20;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[131];
	SetString(action->name, "Blue Nerf");
	action->descriptionDialogId = 5131;
	action->cost = 9;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 46;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_DISARM;
	action->vars[1].i = 10;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[132];
	SetString(action->name, "Headbutt");
	action->descriptionDialogId = 5132;
	action->cost = 7;
	action->priority = 1;
	action->codeId = 61;
	action->animationId = 3;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 19;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 6;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 2;
	
	action = &actionData[133];
	SetString(action->name, "Teatime Beam");
	action->descriptionDialogId = 5133;
	action->cost = 52;
	action->ranged = true;
	action->armorOnlyId = 73;
	action->priority = 2;
	action->codeId = 62;
	action->animationId = 47;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 1;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 40;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_ANTIGUARD;
	action->vars[3].i = 1;
	
	action = &actionData[134];
	SetString(action->name, "Heat Up");
	action->descriptionDialogId = 5134;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 12;
	action->vars[1].i = -3;
	action->vars[2].i = FIGHTER_STATUS_STRENGTH;
	action->vars[3].i = 8;
	
	action = &actionData[135];
	SetString(action->name, "Harvest");
	action->descriptionDialogId = 5135;
	action->cost = 7;
	action->priority = 1;
	action->codeId = 63;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 3;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 1;
	
	action = &actionData[136];
	SetString(action->name, "Reap");
	action->descriptionDialogId = 5136;
	action->cost = 18;
	action->priority = 1;
	action->codeId = 64;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 12; action->power[1] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 15;
	action->vars[1].i = 6;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 2;
	
	action = &actionData[137];
	SetString(action->name, "Nettle Shot");
	action->descriptionDialogId = 5137;
	action->cost = 15;
	action->ranged = true;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 7;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 10;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_POISON;
	action->vars[3].i = 4;
	
	action = &actionData[138];
	SetString(action->name, "Ice Swing");
	action->descriptionDialogId = 5138;
	action->cost = 5;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 1;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_CHILL;
	action->vars[3].i = 3;
	
	action = &actionData[139];
	SetString(action->name, "Dual Frost");
	action->descriptionDialogId = 5139;
	action->cost = 15;
	action->priority = 1;
	action->codeId = 7;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4; action->power[1] = 4;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 5;
	action->vars[1].i = 5;
	action->vars[2].i = FIGHTER_STATUS_CHILL;
	action->vars[3].i = 3;
	
	action = &actionData[140];
	SetString(action->name, "Mad Protect");
	action->descriptionDialogId = 5140;
	action->cost = 12;
	action->priority = 3;
	action->codeId = 12;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 3;
	action->vars[2].i = FIGHTER_STATUS_COUNTER;
	action->vars[3].i = 5;
	
	action = &actionData[141];
	SetString(action->name, "Mighty Swing");
	action->descriptionDialogId = 5141;
	action->cost = 20;
	action->priority = 1;
	action->codeId = 15;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 22;
	action->attackMultiplier = 1;
	action->vars[0].i = 2;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_IMMOBILE;
	action->vars[3].i = 1;
	
	action = &actionData[142];
	SetString(action->name, "Guerrilla Combo");
	action->descriptionDialogId = 5142;
	action->cost = 8;
	action->priority = 1;
	action->codeId = 65;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3; action->power[1] = 3;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 2;
	action->vars[1].i = 10;
	
	action = &actionData[143];
	SetString(action->name, "Ternary Op");
	action->descriptionDialogId = 5143;
	action->cost = 15;
	action->priority = 1;
	action->codeId = 66;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5; action->power[1] = 5; action->power[2] = 7;
	action->attackMultiplier = 0.5;
	
	action = &actionData[144];
	SetString(action->name, "Noob Destroyer");
	action->descriptionDialogId = 5144;
	action->cost = 120;
	action->priority = 2;
	action->codeId = 67;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 96;
	action->attackMultiplier = 0.5;
	
	action = &actionData[145];
	SetString(action->name, "Shadow Crash");
	action->descriptionDialogId = 5145;
	action->cost = 48;
	action->priority = 2;
	action->codeId = 21;
	action->animationId = 50;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 28;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	
	action = &actionData[146];
	SetString(action->name, "EMP Shutdown");
	action->descriptionDialogId = 5146;
	action->cost = 84;
	action->armorOnlyId = 39;
	action->priority = 2;
	action->codeId = 68;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 75;
	action->powerRepeat = 4;
	action->attackMultiplier = 1;
	action->vars[0].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[1].i = 6;
	action->vars[2].i = 9;
	
	action = &actionData[147];
	SetString(action->name, "Inferno Wave");
	action->descriptionDialogId = 5147;
	action->cost = 115;
	action->priority = 1;
	action->codeId = 70;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 25;
	action->powerRepeat = 4;
	action->attackMultiplier = 1.5;
	action->vars[0].i = FIGHTER_STATUS_BURN;
	action->vars[1].i = 7;
	
	action = &actionData[148];
	SetString(action->name, "Meteor Storm");
	action->descriptionDialogId = 5148;
	action->cost = 120;
	action->priority = 2;
	action->codeId = 71;
	action->animationId = 51;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 30;
	action->attackMultiplier = 1;
	action->vars[0].i = FIGHTER_STATUS_BURN;
	action->vars[1].i = 36;
	
	action = &actionData[149];
	SetString(action->name, "Ice Freeze II");
	action->descriptionDialogId = 5149;
	action->cost = 82;
	action->priority = 2;
	action->codeId = 33;
	action->animationId = 56;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 40;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 40;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_CHILL;
	action->vars[3].i = 26;
	
	action = &actionData[150];
	SetString(action->name, "Stumper");
	action->descriptionDialogId = 5150;
	action->cost = 64;
	action->priority = 1;
	action->codeId = 72;
	action->animationId = 5;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 30;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 8;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 70;
	
	action = &actionData[151];
	SetString(action->name, "Tree Impale");
	action->descriptionDialogId = 5151;
	action->cost = 31;
	action->priority = 1;
	action->codeId = 73;
	action->animationId = 52;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6; action->power[1] = 6; action->power[2] = 6;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_FEEBLE;
	action->vars[1].i = 6;
	
	action = &actionData[152];
	SetString(action->name, "Refresh");
	action->descriptionDialogId = 5152;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 20;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_MANADISCOUNT;
	action->vars[3].i = 10;
	
	action = &actionData[153];
	SetString(action->name, "Earthquake");
	action->descriptionDialogId = 5153;
	action->cost = 75;
	action->priority = 3;
	action->codeId = 74;
	action->animationId = 53;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 35;
	action->attackMultiplier = 2;
	action->vars[0].i = FIGHTER_STATUS_FEEBLE;
	action->vars[1].i = 35;
	action->vars[2].i = 47;
	
	action = &actionData[154];
	SetString(action->name, "Judgment Strike");
	action->descriptionDialogId = 5154;
	action->cost = 77;
	action->priority = 1;
	action->codeId = 75;
	action->animationId = 54;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 50;
	action->attackMultiplier = 1;
	action->vars[0].i = 140;
	action->vars[1].i = 0;
	
	action = &actionData[155];
	SetString(action->name, "Spread Heal");
	action->descriptionDialogId = 5155;
	action->cost = 75;
	action->priority = 1;
	action->codeId = 76;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLYPARTY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 40;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[156];
	SetString(action->name, "Energy Share");
	action->descriptionDialogId = 5156;
	action->cost = 10;
	action->priority = 1;
	action->codeId = 13;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 12;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[157];
	SetString(action->name, "Power Restore");
	action->descriptionDialogId = 5157;
	action->cost = 25;
	action->priority = 1;
	action->codeId = 13;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 30;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[158];
	SetString(action->name, "Energy Drain");
	action->descriptionDialogId = 5158;
	action->cost = 21;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 55;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	action->vars[2].i = 1;
	action->vars[3].i = -20;
	
	action = &actionData[159];
	SetString(action->name, "Spikes from Hell");
	action->descriptionDialogId = 5159;
	action->cost = 100;
	action->priority = 2;
	action->codeId = 77;
	action->animationId = 57;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 45;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_BLEED;
	action->vars[1].i = 29;
	
	action = &actionData[160];
	SetString(action->name, "Double Charge");
	action->descriptionDialogId = 5160;
	action->cost = 20;
	action->priority = 1;
	action->codeId = 41;
	action->animationId = 35;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_CHARGE;
	action->vars[1].i = 2;
	
	action = &actionData[161];
	SetString(action->name, "Triple Charge");
	action->descriptionDialogId = 5161;
	action->cost = 45;
	action->priority = 1;
	action->codeId = 41;
	action->animationId = 35;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_CHARGE;
	action->vars[1].i = 3;
	
	action = &actionData[162];
	SetString(action->name, "BlackHoleRampage");
	action->descriptionDialogId = 5162;
	action->cost = 244;
	action->priority = 3;
	action->codeId = 78;
	action->animationId = 58;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 3;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 35;
	action->powerRepeat = 20;
	action->attackMultiplier = 6;
	action->vars[0].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[1].i = 11;
	action->vars[2].i = FIGHTER_STATUS_DISARM;
	action->vars[3].i = 18;
	
	action = &actionData[163];
	SetString(action->name, "Extreme Replenish");
	action->descriptionDialogId = 5163;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 60;
	action->vars[1].i = -15;
	action->vars[2].i = FIGHTER_STATUS_DISARM;
	action->vars[3].i = 10;
	
	action = &actionData[164];
	SetString(action->name, "Flamestar");
	action->descriptionDialogId = 5164;
	action->cost = 71;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 59;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 35;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BURN;
	action->vars[3].i = 34;
	
	action = &actionData[165];
	SetString(action->name, "Ultra Heal");
	action->descriptionDialogId = 5165;
	action->cost = 90;
	action->priority = 1;
	action->codeId = 13;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 300;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[166];
	SetString(action->name, "Elite Relax");
	action->descriptionDialogId = 5166;
	action->cost = 70;
	action->priority = 1;
	action->codeId = 3;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 120;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[167];
	SetString(action->name, "??????");
	action->descriptionDialogId = 5001;
	action->cost = 99;
	action->priority = 1;
	action->codeId = 1;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 116;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	
	action = &actionData[168];
	SetString(action->name, "Malwave Stream");
	action->descriptionDialogId = 5168;
	action->cost = 60;
	action->armorOnlyId = 79;
	action->priority = 2;
	action->codeId = 80;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->powerRepeat = 16;
	action->attackMultiplier = 1;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	
	action = &actionData[169];
	SetString(action->name, "Tempest Tempo");
	action->descriptionDialogId = 5169;
	action->cost = 96;
	action->priority = 1;
	action->codeId = 81;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 2;
	action->powerRepeat = 32;
	action->attackMultiplier = 4;
	action->vars[0].i = 0;
	
	action = &actionData[170];
	SetString(action->name, "Malwave Spread");
	action->descriptionDialogId = 5170;
	action->cost = 52;
	action->armorOnlyId = 79;
	action->priority = 2;
	action->codeId = 80;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 7;
	action->powerRepeat = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 1;
	action->vars[1].i = 0;
	
	action = &actionData[171];
	SetString(action->name, "Malwave Flash");
	action->descriptionDialogId = 5171;
	action->cost = 81;
	action->armorOnlyId = 79;
	action->priority = 3;
	action->codeId = 80;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 7;
	action->powerRepeat = 16;
	action->attackMultiplier = 1;
	action->vars[0].i = 2;
	action->vars[1].i = 0;
	
	action = &actionData[172];
	SetString(action->name, "Malwave Finale");
	action->descriptionDialogId = 5172;
	action->cost = 120;
	action->armorOnlyId = 79;
	action->priority = 3;
	action->codeId = 80;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_EXHAUST;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 5;
	action->powerRepeat = 58;
	action->attackMultiplier = 4;
	action->vars[0].i = 3;
	action->vars[1].i = 0;
	
	action = &actionData[173];
	SetString(action->name, "Deadly Court");
	action->descriptionDialogId = 5173;
	action->cost = 121;
	action->armorOnlyId = 80;
	action->priority = 1;
	action->codeId = 82;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 10; action->power[1] = 204;
	action->attackMultiplier = 1;
	action->vars[0].i = FIGHTER_STATUS_BLEED;
	action->vars[1].i = 66;
	action->vars[2].i = 16;
	
	action = &actionData[174];
	SetString(action->name, "Cory Overdrive");
	action->descriptionDialogId = 5174;
	action->cost = 216;
	action->armorOnlyId = 80;
	action->priority = 3;
	action->codeId = 83;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_EXHAUST;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6;
	action->powerRepeat = 32;
	action->attackMultiplier = 6;
	action->vars[0].i = 0;
	
	action = &actionData[175];
	SetString(action->name, "Ultra Counter");
	action->descriptionDialogId = 5175;
	action->cost = 25;
	action->priority = 3;
	action->codeId = 11;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 30;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_COUNTER;
	action->vars[1].i = 30;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[176];
	SetString(action->name, "DM Slice");
	action->descriptionDialogId = 5176;
	action->cost = 28;
	action->priority = 1;
	action->codeId = 84;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 14;
	action->attackMultiplier = 1;
	action->vars[0].i = 8;
	action->vars[1].i = 0;
	action->vars[2].i = FIGHTER_STATUS_BLEED;
	action->vars[3].i = 25;
	
	action = &actionData[177];
	SetString(action->name, "0 to Death");
	action->descriptionDialogId = 5177;
	action->cost = 175;
	action->priority = 2;
	action->codeId = 85;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->powerRepeat = 12;
	action->attackMultiplier = 3;
	action->vars[0].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[1].i = 7;
	
	action = &actionData[178];
	SetString(action->name, "Brainteaser");
	action->descriptionDialogId = 5178;
	action->cost = 168;
	action->priority = 1;
	action->codeId = 86;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 22;
	action->attackMultiplier = 1;
	action->vars[0].i = FIGHTER_STATUS_POISON;
	action->vars[1].i = 40;
	action->vars[2].i = 50;
	
	action = &actionData[179];
	SetString(action->name, "Omni-Defend");
	action->descriptionDialogId = 5179;
	action->cost = 96;
	action->priority = 3;
	action->codeId = 87;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 93;
	action->attackMultiplier = 0.5;
	action->vars[0].i = FIGHTER_STATUS_FEEBLE;
	action->vars[1].i = 153;
	action->vars[2].i = FIGHTER_STATUS_DISARM;
	action->vars[3].i = 51;
	
	action = &actionData[180];
	SetString(action->name, "AM Regen");
	action->descriptionDialogId = 5180;
	action->cost = 450;
	action->priority = 1;
	action->codeId = 88;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 2667;
	action->vars[1].i = 104;
	action->vars[2].i = FIGHTER_STATUS_CHARGE;
	action->vars[3].i = 3;
	
	action = &actionData[181];
	SetString(action->name, "Hellchain");
	action->descriptionDialogId = 5181;
	action->cost = 425;
	action->priority = 2;
	action->codeId = 89;
	action->animationId = 68;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 66;
	action->attackMultiplier = 1;
	action->vars[0].i = FIGHTER_STATUS_BLEED;
	action->vars[1].i = 151;
	action->vars[2].i = FIGHTER_STATUS_POISON;
	action->vars[3].i = 55;
	
	action = &actionData[182];
	SetString(action->name, "Rubin's Finale");
	action->descriptionDialogId = 5182;
	action->cost = 750;
	action->priority = 3;
	action->codeId = 90;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 9;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 19;
	action->powerRepeat = 80;
	action->attackMultiplier = 8;
	
	action = &actionData[183];
	SetString(action->name, "UltL Meteors");
	action->descriptionDialogId = 5183;
	action->cost = 360;
	action->priority = 2;
	action->codeId = 71;
	action->animationId = 70;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 220;
	action->attackMultiplier = 2;
	action->vars[0].i = FIGHTER_STATUS_BURN;
	action->vars[1].i = 184;
	
	action = &actionData[184];
	SetString(action->name, "UltL Thunder");
	action->descriptionDialogId = 5184;
	action->cost = 120;
	action->priority = 2;
	action->codeId = 91;
	action->animationId = 71;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 20;
	action->powerRepeat = 6;
	action->attackMultiplier = 3;
	action->vars[0].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[1].i = 13;
	
	action = &actionData[185];
	SetString(action->name, "UltL Beam");
	action->descriptionDialogId = 5185;
	action->cost = 400;
	action->priority = 2;
	action->codeId = 92;
	action->animationId = 72;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 46;
	action->powerRepeat = 24;
	action->attackMultiplier = 3;
	action->vars[0].i = 6;
	action->vars[1].i = 0;
	
	action = &actionData[186];
	SetString(action->name, "UltL Overdrive");
	action->descriptionDialogId = 5186;
	action->cost = 838;
	action->priority = 3;
	action->codeId = 93;
	action->animationId = 0;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_EXHAUST;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->powerRepeat = 98;
	action->attackMultiplier = 8;
	
	action = &actionData[187];
	SetString(action->name, "UltL Regen");
	action->descriptionDialogId = 5187;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 94;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 505;
	action->vars[1].i = -505;
	action->vars[2].i = 150;
	action->vars[3].i = 50;
	
	action = &actionData[188];
	SetString(action->name, "Ruby Combo");
	action->descriptionDialogId = 5188;
	action->cost = 51;
	action->priority = 1;
	action->codeId = 65;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 20; action->power[1] = 20;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 10;
	action->vars[1].i = 50;
	
	action = &actionData[189];
	SetString(action->name, "Emerald Heal");
	action->descriptionDialogId = 5189;
	action->cost = 249;
	action->priority = 1;
	action->codeId = 76;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLYPARTY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 300;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[190];
	SetString(action->name, "Onyx Offensive");
	action->descriptionDialogId = 5190;
	action->cost = 150;
	action->priority = 1;
	action->codeId = 95;
	action->animationId = 73;
	action->targetType = TARGETTYPE_ALLYPARTY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 150;
	action->vars[1].i = 50;
	action->vars[2].i = 80;
	
	action = &actionData[191];
	SetString(action->name, "Raging L Overdrive");
	action->descriptionDialogId = 5191;
	action->cost = 666;
	action->priority = 2;
	action->codeId = 191;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 666;
	action->attackMultiplier = 4;
	action->vars[0].i = 10;
	
	action = &actionData[192];
	SetString(action->name, "Subspace Demon\nL Overdrive");
	action->descriptionDialogId = 5191;
	action->cost = 6666;
	action->priority = 2;
	action->codeId = 192;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 6666;
	action->attackMultiplier = 8;
	action->vars[0].i = 10;
	
	action = &actionData[193];
	SetString(action->name, "Sapphire Lock");
	action->descriptionDialogId = 5193;
	action->cost = 265;
	action->priority = 1;
	action->codeId = 96;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 60;
	action->attackMultiplier = 1;
	action->vars[0].f = 0.5;
	
	action = &actionData[194];
	SetString(action->name, "Elite Share");
	action->descriptionDialogId = 5194;
	action->cost = 140;
	action->priority = 1;
	action->codeId = 13;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 150;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[195];
	SetString(action->name, "Ruby Megarush");
	action->descriptionDialogId = 5195;
	action->cost = 298;
	action->priority = 1;
	action->codeId = 97;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->condition = ACTIONCONDITION_STATUSCOST;
	action->conditionVars[0].i = FIGHTER_STATUS_CHARGE;
	action->conditionVars[1].i = 1;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 50;
	action->powerRepeat = 8;
	action->attackMultiplier = 4;
	
	action = &actionData[196];
	SetString(action->name, "Regenblock");
	action->descriptionDialogId = 5196;
	action->cost = 50;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 74;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_ANTIREGEN;
	action->vars[1].i = 1;
	action->vars[2].i = 1;
	action->vars[3].i = 0;
	
	action = &actionData[197];
	SetString(action->name, "Amethyst Reset");
	action->descriptionDialogId = 5197;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 76;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLYPARTY;
	action->condition = ACTIONCONDITION_EXHAUST;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 500;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[198];
	SetString(action->name, "Elite Drain");
	action->descriptionDialogId = 5198;
	action->cost = 150;
	action->priority = 1;
	action->codeId = 31;
	action->animationId = 55;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 0;
	action->vars[2].i = 1;
	action->vars[3].i = -160;
	
	
	
	action = &actionData[255];
	SetString(action->name, "t>f");
	action->descriptionDialogId = 0x90;
	action->cost = 0x90909090;
	action->priority = 0x90909090;
	action->codeId = 0x90;
	action->animationId = -1;
	action->targetType = 0x90;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 0x90; action->power[1] = 0x90; action->power[2] = 0x90; action->power[3] = 0x90;
	action->powerRepeat = 0x90;
	action->attackMultiplier = 0x90;
	action->vars[0].i = 0x90;
	action->vars[1].i = 0x90;
	action->vars[2].i = 0x90;
	action->vars[3].i = 0x90;
	
	
	
	// Item actions
	
	action = &actionData[200];
	SetString(action->name, "Heal Capsule");
	action->descriptionDialogId = 5200;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 24;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 15;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[201];
	SetString(action->name, "Bomb");
	action->descriptionDialogId = 5201;
	action->cost = 0;
	action->priority = 2;
	action->codeId = 25;
	action->animationId = 10;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 1;
	
	action = &actionData[202];
	SetString(action->name, "Semi-Nuke");
	action->descriptionDialogId = 5202;
	action->cost = 0;
	action->priority = 2;
	action->codeId = 27;
	action->animationId = 16;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 666;
	action->attackMultiplier = 0;
	
	action = &actionData[203];
	SetString(action->name, "Heal B Capsule");
	action->descriptionDialogId = 5203;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 24;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 25;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[204];
	SetString(action->name, "Heal G Capsule");
	action->descriptionDialogId = 5204;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 24;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 40;
	action->vars[1].i = 0;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[205];
	SetString(action->name, "Power Capsule");
	action->descriptionDialogId = 5205;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 41;
	action->animationId = 20;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_STRENGTH;
	action->vars[1].i = 40;
	
	action = &actionData[206];
	SetString(action->name, "Dandelion Neo");
	action->descriptionDialogId = 5206;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 44;
	action->animationId = 34;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 1;
	
	action = &actionData[207];
	SetString(action->name, "Medkit");
	action->descriptionDialogId = 5207;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 45;
	action->animationId = 3;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 1;
	
	action = &actionData[208];
	SetString(action->name, "Mana Capsule");
	action->descriptionDialogId = 5208;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 24;
	action->animationId = -1;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
	action->vars[1].i = 15;
	action->vars[2].i = 0;
	action->vars[3].i = 0;
	
	action = &actionData[209];
	SetString(action->name, "Bomb B");
	action->descriptionDialogId = 5209;
	action->cost = 0;
	action->priority = 2;
	action->codeId = 25;
	action->animationId = 10;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 30;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 1;
	
	action = &actionData[210];
	SetString(action->name, "Bomb G");
	action->descriptionDialogId = 5210;
	action->cost = 0;
	action->priority = 2;
	action->codeId = 25;
	action->animationId = 10;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 60;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 0;
	action->vars[1].i = 1;
	
	action = &actionData[211];
	SetString(action->name, "XTrance7Capsule");
	action->descriptionDialogId = 5199;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 54;
	action->animationId = 60;
	action->targetType = TARGETTYPE_NONE;
	action->category = ACTIONCATEGORY_MISC;
	action->attackMultiplier = 0;
	action->vars[0].i = 24;
	action->vars[1].i = -4;
	action->vars[2].i = 5;
	action->vars[3].i = 303;
	
	action = &actionData[212];
	SetString(action->name, "Sophien Needle");
	action->descriptionDialogId = 5199;
	action->cost = 0;
	action->priority = 2;
	action->codeId = 79;
	action->animationId = 61;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->attackMultiplier = 0.25;
	action->vars[0].i = 1040;
	action->vars[1].i = 1;
	
	
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		actionAnimUpdateCode[i] = Action_AnimUpdate__0;
		actionAnimDrawCode[i] = Action_AnimDraw__0;
	}
	
	ActionAnim* actionAnim;
	
	actionAnim = &actionAnimData[0];
	actionAnim->time = 0;
	actionAnimDrawCode[0] = Action_AnimDraw__0;
	
	actionAnim = &actionAnimData[1];
	actionAnim->time = 20;
	actionAnimDrawCode[1] = Action_AnimDraw__1;
	
	actionAnim = &actionAnimData[2];
	actionAnim->time = 15;
	actionAnimDrawCode[2] = Action_AnimDraw__2;
	
	actionAnim = &actionAnimData[3];
	actionAnim->time = 20;
	actionAnimDrawCode[3] = Action_AnimDraw__3;
	
	actionAnim = &actionAnimData[4];
	actionAnim->time = 10;
	actionAnimDrawCode[4] = Action_AnimDraw__4;
	
	actionAnim = &actionAnimData[5];
	actionAnim->time = 22;
	actionAnimDrawCode[5] = Action_AnimDraw__5;
	
	actionAnim = &actionAnimData[6];
	actionAnim->time = 11;
	actionAnimDrawCode[6] = Action_AnimDraw__6;
	
	actionAnim = &actionAnimData[7];
	actionAnim->time = 7;
	actionAnimUpdateCode[7] = Action_AnimUpdate__7;
	actionAnimDrawCode[7] = Action_AnimDraw__7;
	
	actionAnim = &actionAnimData[8];
	actionAnim->time = 20;
	actionAnimUpdateCode[8] = Action_AnimUpdate__8;
	actionAnimDrawCode[8] = Action_AnimDraw__8;
	
	actionAnim = &actionAnimData[9];
	actionAnim->time = 7;
	actionAnimUpdateCode[9] = Action_AnimUpdate__9;
	actionAnimDrawCode[9] = Action_AnimDraw__9;
	
	actionAnim = &actionAnimData[10];
	actionAnim->time = 15;
	actionAnimUpdateCode[10] = Action_AnimUpdate__10;
	actionAnimDrawCode[10] = Action_AnimDraw__10;
	
	actionAnim = &actionAnimData[11];
	actionAnim->time = 11;
	actionAnimDrawCode[11] = Action_AnimDraw__11;
	
	actionAnim = &actionAnimData[12];
	actionAnim->time = 22;
	actionAnimUpdateCode[12] = Action_AnimUpdate__12;
	actionAnimDrawCode[12] = Action_AnimDraw__12;
	
	actionAnim = &actionAnimData[13];
	actionAnim->time = 12;
	actionAnimUpdateCode[13] = Action_AnimUpdate__13;
	actionAnimDrawCode[13] = Action_AnimDraw__13;
	
	actionAnim = &actionAnimData[14];
	actionAnim->time = 12;
	actionAnimUpdateCode[14] = Action_AnimUpdate__14;
	actionAnimDrawCode[14] = Action_AnimDraw__14;
	
	actionAnim = &actionAnimData[15];
	actionAnim->time = 2;
	actionAnimUpdateCode[15] = Action_AnimUpdate__15;
	actionAnimDrawCode[15] = Action_AnimDraw__15;
	
	actionAnim = &actionAnimData[16];
	actionAnim->time = 15;
	actionAnimUpdateCode[16] = Action_AnimUpdate__16;
	actionAnimDrawCode[16] = Action_AnimDraw__16;
	
	actionAnim = &actionAnimData[17];
	actionAnim->time = 68;
	actionAnimUpdateCode[17] = Action_AnimUpdate__17;
	actionAnimDrawCode[17] = Action_AnimDraw__17;
	
	actionAnim = &actionAnimData[18];
	actionAnim->time = 15;
	actionAnimDrawCode[18] = Action_AnimDraw__18;
	
	actionAnim = &actionAnimData[19];
	actionAnim->time = 15;
	actionAnimDrawCode[19] = Action_AnimDraw__19;
	
	actionAnim = &actionAnimData[20];
	actionAnim->time = 20;
	actionAnimUpdateCode[20] = Action_AnimUpdate__20;
	actionAnimDrawCode[20] = Action_AnimDraw__20;
	
	actionAnim = &actionAnimData[21];
	actionAnim->time = 20;
	actionAnimUpdateCode[21] = Action_AnimUpdate__21;
	actionAnimDrawCode[21] = Action_AnimDraw__21;
	
	actionAnim = &actionAnimData[22];
	actionAnim->time = 50;
	actionAnimUpdateCode[22] = Action_AnimUpdate__22;
	actionAnimDrawCode[22] = Action_AnimDraw__22;
	
	actionAnim = &actionAnimData[23];
	actionAnim->time = 10;
	actionAnimUpdateCode[23] = Action_AnimUpdate__23;
	actionAnimDrawCode[23] = Action_AnimDraw__23;
	
	actionAnim = &actionAnimData[24];
	actionAnim->time = 12;
	actionAnimUpdateCode[24] = Action_AnimUpdate__24;
	actionAnimDrawCode[24] = Action_AnimDraw__24;
	
	actionAnim = &actionAnimData[25];
	actionAnim->time = 7;
	actionAnimUpdateCode[25] = Action_AnimUpdate__25;
	actionAnimDrawCode[25] = Action_AnimDraw__25;
	
	actionAnim = &actionAnimData[26];
	actionAnim->time = 14;
	actionAnimUpdateCode[26] = Action_AnimUpdate__26;
	actionAnimDrawCode[26] = Action_AnimDraw__26;
	
	actionAnim = &actionAnimData[27];
	actionAnim->time = 114;
	actionAnimUpdateCode[27] = Action_AnimUpdate__27;
	actionAnimDrawCode[27] = Action_AnimDraw__27;
	
	actionAnim = &actionAnimData[28];
	actionAnim->time = 11;
	actionAnimUpdateCode[28] = Action_AnimUpdate__28;
	actionAnimDrawCode[28] = Action_AnimDraw__28;
	
	actionAnim = &actionAnimData[29];
	actionAnim->time = 10;
	actionAnimDrawCode[29] = Action_AnimDraw__29;
	
	actionAnim = &actionAnimData[30];
	actionAnim->time = 18;
	actionAnimUpdateCode[30] = Action_AnimUpdate__30;
	actionAnimDrawCode[30] = Action_AnimDraw__30;
	
	actionAnim = &actionAnimData[31];
	actionAnim->time = 32;
	actionAnimUpdateCode[31] = Action_AnimUpdate__31;
	actionAnimDrawCode[31] = Action_AnimDraw__31;
	
	actionAnim = &actionAnimData[32];
	actionAnim->time = 9;
	actionAnimUpdateCode[32] = Action_AnimUpdate__32;
	actionAnimDrawCode[32] = Action_AnimDraw__32;
	
	actionAnim = &actionAnimData[33];
	actionAnim->time = 76;
	actionAnimUpdateCode[33] = Action_AnimUpdate__33;
	actionAnimDrawCode[33] = Action_AnimDraw__33;
	
	actionAnim = &actionAnimData[34];
	actionAnim->time = 24;
	actionAnimDrawCode[34] = Action_AnimDraw__34;
	
	actionAnim = &actionAnimData[35];
	actionAnim->time = 16;
	actionAnimUpdateCode[35] = Action_AnimUpdate__35;
	actionAnimDrawCode[35] = Action_AnimDraw__35;
	
	actionAnim = &actionAnimData[36];
	actionAnim->time = 11;
	actionAnimUpdateCode[36] = Action_AnimUpdate__36;
	actionAnimDrawCode[36] = Action_AnimDraw__36;
	
	actionAnim = &actionAnimData[37];
	actionAnim->time = 59;
	actionAnimUpdateCode[37] = Action_AnimUpdate__37;
	
	actionAnim = &actionAnimData[38];
	actionAnim->time = 222;
	actionAnimUpdateCode[38] = Action_AnimUpdate__38;
	actionAnimDrawCode[38] = Action_AnimDraw__38;
	
	actionAnim = &actionAnimData[39];
	actionAnim->time = 3;
	actionAnimUpdateCode[39] = Action_AnimUpdate__39;
	actionAnimDrawCode[39] = Action_AnimDraw__39;
	
	actionAnim = &actionAnimData[40];
	actionAnim->time = 41;
	actionAnimUpdateCode[40] = Action_AnimUpdate__40;
	actionAnimDrawCode[40] = Action_AnimDraw__40;
	
	actionAnim = &actionAnimData[41];
	actionAnim->time = 20;
	actionAnimUpdateCode[41] = Action_AnimUpdate__41;
	actionAnimDrawCode[41] = Action_AnimDraw__41;
	
	actionAnim = &actionAnimData[42];
	actionAnim->time = 24;
	actionAnimUpdateCode[42] = Action_AnimUpdate__42;
	actionAnimDrawCode[42] = Action_AnimDraw__42;
	
	actionAnim = &actionAnimData[43];
	actionAnim->time = 72;
	actionAnimUpdateCode[43] = Action_AnimUpdate__43;
	actionAnimDrawCode[43] = Action_AnimDraw__43;
	
	actionAnim = &actionAnimData[44];
	actionAnim->time = 2;
	actionAnimDrawCode[44] = Action_AnimDraw__44;
	
	actionAnim = &actionAnimData[45];
	actionAnim->time = 20;
	actionAnimUpdateCode[45] = Action_AnimUpdate__45;
	actionAnimDrawCode[45] = Action_AnimDraw__45;
	
	actionAnim = &actionAnimData[46];
	actionAnim->time = 20;
	actionAnimUpdateCode[46] = Action_AnimUpdate__46;
	actionAnimDrawCode[46] = Action_AnimDraw__46;
	
	actionAnim = &actionAnimData[47];
	actionAnim->time = 70;
	actionAnimUpdateCode[47] = Action_AnimUpdate__47;
	actionAnimDrawCode[47] = Action_AnimDraw__47;
	
	actionAnim = &actionAnimData[48];
	actionAnim->time = 18;
	actionAnimUpdateCode[48] = Action_AnimUpdate__48;
	actionAnimDrawCode[48] = Action_AnimDraw__48;
	
	actionAnim = &actionAnimData[49];
	actionAnim->time = 10;
	actionAnimUpdateCode[49] = Action_AnimUpdate__49;
	actionAnimDrawCode[49] = Action_AnimDraw__49;
	
	actionAnim = &actionAnimData[50];
	actionAnim->time = 15;
	actionAnimUpdateCode[50] = Action_AnimUpdate__50;
	actionAnimDrawCode[50] = Action_AnimDraw__50;
	
	actionAnim = &actionAnimData[51];
	actionAnim->time = 120;
	actionAnimUpdateCode[51] = Action_AnimUpdate__51;
	actionAnimDrawCode[51] = Action_AnimDraw__51;
	
	actionAnim = &actionAnimData[52];
	actionAnim->time = 10;
	actionAnimDrawCode[52] = Action_AnimDraw__52;
	
	actionAnim = &actionAnimData[53];
	actionAnim->time = 55;
	actionAnimUpdateCode[53] = Action_AnimUpdate__53;
	
	actionAnim = &actionAnimData[54];
	actionAnim->time = 40;
	actionAnimUpdateCode[54] = Action_AnimUpdate__54;
	actionAnimDrawCode[54] = Action_AnimDraw__54;
	
	actionAnim = &actionAnimData[55];
	actionAnim->time = 20;
	actionAnimUpdateCode[55] = Action_AnimUpdate__55;
	actionAnimDrawCode[55] = Action_AnimDraw__55;
	
	actionAnim = &actionAnimData[56];
	actionAnim->time = 84;
	actionAnimUpdateCode[56] = Action_AnimUpdate__56;
	actionAnimDrawCode[56] = Action_AnimDraw__56;
	
	actionAnim = &actionAnimData[57];
	actionAnim->time = 56;
	actionAnimUpdateCode[57] = Action_AnimUpdate__57;
	actionAnimDrawCode[57] = Action_AnimDraw__57;
	
	actionAnim = &actionAnimData[58];
	actionAnim->time = 2;
	actionAnimUpdateCode[58] = Action_AnimUpdate__58;
	actionAnimDrawCode[58] = Action_AnimDraw__58;
	
	actionAnim = &actionAnimData[59];
	actionAnim->time = 12;
	actionAnimUpdateCode[59] = Action_AnimUpdate__59;
	actionAnimDrawCode[59] = Action_AnimDraw__59;
	
	actionAnim = &actionAnimData[60];
	actionAnim->time = 40;
	actionAnimUpdateCode[60] = Action_AnimUpdate__60;
	actionAnimDrawCode[60] = Action_AnimDraw__60;
	
	actionAnim = &actionAnimData[61];
	actionAnim->time = 11;
	actionAnimUpdateCode[61] = Action_AnimUpdate__61;
	actionAnimDrawCode[61] = Action_AnimDraw__61;
	
	actionAnim = &actionAnimData[62];
	actionAnim->time = 10;
	actionAnimUpdateCode[62] = Action_AnimUpdate__62;
	actionAnimDrawCode[62] = Action_AnimDraw__62;
	
	actionAnim = &actionAnimData[63];
	actionAnim->time = 10;
	actionAnimUpdateCode[63] = Action_AnimUpdate__63;
	actionAnimDrawCode[63] = Action_AnimDraw__63;
	
	actionAnim = &actionAnimData[64];
	actionAnim->time = 9;
	actionAnimUpdateCode[64] = Action_AnimUpdate__64;
	actionAnimDrawCode[64] = Action_AnimDraw__64;
	
	actionAnim = &actionAnimData[65];
	actionAnim->time = 18;
	actionAnimUpdateCode[65] = Action_AnimUpdate__65;
	actionAnimDrawCode[65] = Action_AnimDraw__65;
	
	actionAnim = &actionAnimData[66];
	actionAnim->time = 6;
	actionAnimUpdateCode[66] = Action_AnimUpdate__66;
	actionAnimDrawCode[66] = Action_AnimDraw__66;
	
	actionAnim = &actionAnimData[67];
	actionAnim->time = 6;
	actionAnimUpdateCode[67] = Action_AnimUpdate__67;
	actionAnimDrawCode[67] = Action_AnimDraw__67;
	
	actionAnim = &actionAnimData[68];
	actionAnim->time = 10;
	actionAnimUpdateCode[68] = Action_AnimUpdate__68;
	actionAnimDrawCode[68] = Action_AnimDraw__68;
	
	actionAnim = &actionAnimData[69];
	actionAnim->time = 4;
	actionAnimUpdateCode[69] = Action_AnimUpdate__69;
	actionAnimDrawCode[69] = Action_AnimDraw__69;
	
	actionAnim = &actionAnimData[70];
	actionAnim->time = 170;
	actionAnimUpdateCode[70] = Action_AnimUpdate__70;
	actionAnimDrawCode[70] = Action_AnimDraw__70;
	
	actionAnim = &actionAnimData[71];
	actionAnim->time = 2;
	actionAnimUpdateCode[71] = Action_AnimUpdate__71;
	
	actionAnim = &actionAnimData[72];
	actionAnim->time = 6;
	actionAnimUpdateCode[72] = Action_AnimUpdate__72;
	actionAnimDrawCode[72] = Action_AnimDraw__72;
	
	actionAnim = &actionAnimData[73];
	actionAnim->time = 20;
	actionAnimUpdateCode[73] = Action_AnimUpdate__73;
	actionAnimDrawCode[73] = Action_AnimDraw__73;
	
	actionAnim = &actionAnimData[74];
	actionAnim->time = 20;
	actionAnimUpdateCode[74] = Action_AnimUpdate__74;
	actionAnimDrawCode[74] = Action_AnimDraw__74;
	
	
	
	for (int i = 1; i < OBJECT_COUNT_MAX; i++) {
		actionUpdateCode[i] = Action_Update__0;
		actionDrawCode[i] = Action_Draw__0;
	}
	
	actionUpdateCode[1] = Action_Update__1;
	actionDrawCode[1] = Action_Draw__1;
	
	actionUpdateCode[2] = Action_Update__2;
	actionDrawCode[2] = Action_Draw__1;
	
	actionUpdateCode[3] = Action_Update__3;
	
	actionUpdateCode[4] = Action_Update__4;
	actionDrawCode[4] = Action_Draw__1;
	
	actionUpdateCode[5] = Action_Update__5;
	actionDrawCode[5] = Action_Draw__1;
	
	actionUpdateCode[6] = Action_Update__6;
	actionDrawCode[6] = Action_Draw__1;
	
	actionUpdateCode[7] = Action_Update__7;
	actionDrawCode[7] = Action_Draw__1;
	
	actionUpdateCode[8] = Action_Update__8;
	actionDrawCode[8] = Action_Draw__1;
	
	actionUpdateCode[9] = Action_Update__9;
	actionDrawCode[9] = Action_Draw__1;
	
	actionUpdateCode[10] = Action_Update__10;
	actionDrawCode[10] = Action_Draw__1;
	
	actionUpdateCode[11] = Action_Update__11;
	actionDrawCode[11] = Action_Draw__1;
	
	actionUpdateCode[12] = Action_Update__12;
	actionDrawCode[12] = Action_Draw__1;
	
	actionUpdateCode[13] = Action_Update__13;
	actionDrawCode[13] = Action_Draw__1;
	
	actionUpdateCode[14] = Action_Update__14;
	actionDrawCode[14] = Action_Draw__14;
	
	actionUpdateCode[15] = Action_Update__15;
	actionDrawCode[15] = Action_Draw__1;
	
	actionUpdateCode[16] = Action_Update__16;
	actionDrawCode[16] = Action_Draw__1;
	
	actionUpdateCode[17] = Action_Update__17;
	actionDrawCode[17] = Action_Draw__0;
	
	actionUpdateCode[18] = Action_Update__18;
	actionDrawCode[18] = Action_Draw__1;
	
	actionUpdateCode[19] = Action_Update__19;
	actionDrawCode[19] = Action_Draw__1;
	
	actionUpdateCode[20] = Action_Update__20;
	actionDrawCode[20] = Action_Draw__20;
	
	actionUpdateCode[21] = Action_Update__21;
	actionDrawCode[21] = Action_Draw__1;
	
	actionUpdateCode[22] = Action_Update__22;
	actionDrawCode[22] = Action_Draw__1;
	
	actionUpdateCode[23] = Action_Update__23;
	actionDrawCode[23] = Action_Draw__23;
	
	actionUpdateCode[24] = Action_Update__24;
	actionDrawCode[24] = Action_Draw__1;
	
	actionUpdateCode[25] = Action_Update__25;
	actionDrawCode[25] = Action_Draw__1;
	
	actionUpdateCode[26] = Action_Update__26;
	actionDrawCode[26] = Action_Draw__26;
	
	actionUpdateCode[27] = Action_Update__27;
	actionDrawCode[27] = Action_Draw__27;
	
	actionUpdateCode[28] = Action_Update__28;
	actionDrawCode[28] = Action_Draw__1;
	
	actionUpdateCode[29] = Action_Update__29;
	actionDrawCode[29] = Action_Draw__29;
	
	actionUpdateCode[30] = Action_Update__30;
	actionDrawCode[30] = Action_Draw__1;
	
	actionUpdateCode[31] = Action_Update__31;
	actionDrawCode[31] = Action_Draw__1;
	
	actionUpdateCode[32] = Action_Update__32;
	actionDrawCode[32] = Action_Draw__32;
	
	actionUpdateCode[33] = Action_Update__33;
	actionDrawCode[33] = Action_Draw__1;
	
	actionUpdateCode[34] = Action_Update__34;
	actionDrawCode[34] = Action_Draw__1;
	
	actionUpdateCode[35] = Action_Update__35;
	actionDrawCode[35] = Action_Draw__1;
	
	actionUpdateCode[36] = Action_Update__36;
	actionDrawCode[36] = Action_Draw__36;
	
	actionUpdateCode[37] = Action_Update__37;
	actionDrawCode[37] = Action_Draw__1;
	
	actionUpdateCode[38] = Action_Update__38;
	actionDrawCode[38] = Action_Draw__1;
	
	actionUpdateCode[39] = Action_Update__39;
	actionDrawCode[39] = Action_Draw__1;
	
	actionUpdateCode[40] = Action_Update__40;
	actionDrawCode[40] = Action_Draw__40;
	
	actionUpdateCode[41] = Action_Update__41;
	actionDrawCode[41] = Action_Draw__41;
	
	actionUpdateCode[42] = Action_Update__42;
	actionDrawCode[42] = Action_Draw__42;
	
	actionUpdateCode[43] = Action_Update__43;
	actionDrawCode[43] = Action_Draw__1;
	
	actionUpdateCode[44] = Action_Update__44;
	actionDrawCode[44] = Action_Draw__41;
	
	actionUpdateCode[45] = Action_Update__45;
	actionDrawCode[45] = Action_Draw__41;
	
	actionUpdateCode[46] = Action_Update__46;
	actionDrawCode[46] = Action_Draw__40;
	
	actionUpdateCode[47] = Action_Update__47;
	actionDrawCode[47] = Action_Draw__47;
	
	actionUpdateCode[48] = Action_Update__48;
	actionDrawCode[48] = Action_Draw__1;
	
	actionUpdateCode[49] = Action_Update__49;
	actionDrawCode[49] = Action_Draw__49;
	
	actionUpdateCode[50] = Action_Update__50;
	actionDrawCode[50] = Action_Draw__1;
	
	actionUpdateCode[51] = Action_Update__51;
	
	actionUpdateCode[52] = Action_Update__52;
	actionDrawCode[52] = Action_Draw__1;
	
	actionUpdateCode[53] = Action_Update__53;
	actionDrawCode[53] = Action_Draw__1;
	
	actionUpdateCode[54] = Action_Update__54;
	actionDrawCode[54] = Action_Draw__41;
	
	actionUpdateCode[55] = Action_Update__55;
	actionDrawCode[55] = Action_Draw__1;
	
	actionUpdateCode[56] = Action_Update__56;
	actionDrawCode[56] = Action_Draw__1;
	
	actionUpdateCode[57] = Action_Update__57;
	actionDrawCode[57] = Action_Draw__57;
	
	actionUpdateCode[58] = Action_Update__58;
	actionDrawCode[58] = Action_Draw__58;
	
	actionUpdateCode[59] = Action_Update__59;
	actionDrawCode[59] = Action_Draw__1;
	
	actionUpdateCode[60] = Action_Update__60;
	actionDrawCode[60] = Action_Draw__1;
	
	actionUpdateCode[61] = Action_Update__61;
	actionDrawCode[61] = Action_Draw__1;
	
	actionUpdateCode[62] = Action_Update__62;
	actionDrawCode[62] = Action_Draw__1;
	
	actionUpdateCode[63] = Action_Update__63;
	actionDrawCode[63] = Action_Draw__1;
	
	actionUpdateCode[64] = Action_Update__64;
	actionDrawCode[64] = Action_Draw__1;
	
	actionUpdateCode[65] = Action_Update__65;
	actionDrawCode[65] = Action_Draw__1;
	
	actionUpdateCode[66] = Action_Update__66;
	actionDrawCode[66] = Action_Draw__1;
	
	actionUpdateCode[67] = Action_Update__67;
	actionDrawCode[67] = Action_Draw__67;
	
	actionUpdateCode[68] = Action_Update__68;
	actionDrawCode[68] = Action_Draw__68;
	
	actionUpdateCode[69] = Action_Update__69;
	
	actionUpdateCode[70] = Action_Update__70;
	actionDrawCode[70] = Action_Draw__70;
	
	actionUpdateCode[71] = Action_Update__71;
	actionDrawCode[71] = Action_Draw__40;
	
	actionUpdateCode[72] = Action_Update__72;
	actionDrawCode[72] = Action_Draw__1;
	
	actionUpdateCode[73] = Action_Update__73;
	actionDrawCode[73] = Action_Draw__40;
	
	actionUpdateCode[74] = Action_Update__74;
	actionDrawCode[74] = Action_Draw__40;
	
	actionUpdateCode[75] = Action_Update__75;
	actionDrawCode[75] = Action_Draw__1;
	
	actionUpdateCode[76] = Action_Update__76;
	actionDrawCode[76] = Action_Draw__40;
	
	actionUpdateCode[77] = Action_Update__77;
	actionDrawCode[77] = Action_Draw__40;
	
	actionUpdateCode[78] = Action_Update__78;
	actionDrawCode[78] = Action_Draw__40;
	
	actionUpdateCode[79] = Action_Update__79;
	actionDrawCode[79] = Action_Draw__1;
	
	actionUpdateCode[80] = Action_Update__80;
	actionDrawCode[80] = Action_Draw__1;
	
	actionUpdateCode[81] = Action_Update__81;
	actionDrawCode[81] = Action_Draw__1;
	
	actionUpdateCode[82] = Action_Update__82;
	actionDrawCode[82] = Action_Draw__82;
	
	actionUpdateCode[83] = Action_Update__83;
	actionDrawCode[83] = Action_Draw__83;
	
	actionUpdateCode[84] = Action_Update__84;
	actionDrawCode[84] = Action_Draw__1;
	
	actionUpdateCode[85] = Action_Update__85;
	actionDrawCode[85] = Action_Draw__85;
	
	actionUpdateCode[86] = Action_Update__86;
	actionDrawCode[86] = Action_Draw__1;
	
	actionUpdateCode[87] = Action_Update__87;
	actionDrawCode[87] = Action_Draw__1;
	
	actionUpdateCode[88] = Action_Update__88;
	actionDrawCode[88] = Action_Draw__1;
	
	actionUpdateCode[89] = Action_Update__89;
	actionDrawCode[89] = Action_Draw__40;
	
	actionUpdateCode[90] = Action_Update__90;
	actionDrawCode[90] = Action_Draw__90;
	
	actionUpdateCode[91] = Action_Update__91;
	actionDrawCode[91] = Action_Draw__40;
	
	actionUpdateCode[92] = Action_Update__92;
	actionDrawCode[92] = Action_Draw__1;
	
	actionUpdateCode[93] = Action_Update__93;
	actionDrawCode[93] = Action_Draw__93;
	
	actionUpdateCode[94] = Action_Update__94;
	
	actionUpdateCode[95] = Action_Update__95;
	actionDrawCode[95] = Action_Draw__40;
	
	actionUpdateCode[96] = Action_Update__96;
	actionDrawCode[96] = Action_Draw__1;
	
	actionUpdateCode[97] = Action_Update__97;
	actionDrawCode[97] = Action_Draw__1;
	
	actionUpdateCode[144] = NULL;
	actionDrawCode[144] = NULL;
	
	
	actionUpdateCode[191] = Action_Update__191;
	actionDrawCode[191] = Action_Draw__191;
	
	
	actionUpdateCode[192] = Action_Update__192;
	actionDrawCode[192] = Action_Draw__192;
}



int Action_AttackUpdate(Fighter* attacker, Fighter* target) {
	if (attacker->side == 0) {
		return PlayerButtonPressed(PLAYER_BUTTON_Z);
	}
	
	return Fighter_AI_Attack(attacker, target);
}

void Action_BlockUpdate(Fighter* attacker, Fighter* target) {
	if (!target->alive || target->status[FIGHTER_STATUS_ANTIGUARD]) return;
	if (attacker->attackTimer < 0 && attacker->readyTimer < 0) return;
	
	int blocked = 0;
	
	if (target->side == 0) {
		if (PlayerButtonPressed(PLAYER_BUTTON_Z)) {
			blocked = 1;
		}
	}
	else {
		blocked = Fighter_AI_Block(target, attacker);
	}
	
	
	
	if (blocked && target->blockCooldownTimer < 0) {
		target->blockTimer = 0;
		target->blockCooldownTimer = 0;
		target->state = FIGHTER_STATE_BLOCK;
		target->flinchTicks = 0;
		
		if (attacker->targetId == TARGET_ALLYPARTY || attacker->targetId == TARGET_ENEMYPARTY) {
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				fighter->blockTimer = 0;
				fighter->blockCooldownTimer = 0;
				fighter->state = FIGHTER_STATE_BLOCK;
				fighter->flinchTicks = 0;
			}
		}
	}
}

int Action_CalculateAttackPower(Fighter* attacker, Fighter* target, int damage) {
	int speedDifference = attacker->speedRoll - target->speedRoll;
	
	if (speedDifference >= 5) {
		damage += speedDifference / 5;
	}
	
	damage -= target->defense + target->status[FIGHTER_STATUS_ENDURANCE] - target->status[FIGHTER_STATUS_DISARM];
	if (damage < 0)
		damage = 0;
	
	return damage;
}

int Action_GetDamagePower(Fighter* attacker, Fighter* target) {
	int power = 0;
	int powerCount = 0;
	for (int i = 0; i < 4; i++) {
		if (attacker->actionPower[i] < 0) break;
		powerCount++;
	}
	power = attacker->actionPower[attacker->actionAttacks % powerCount];
	return power + (float)(1 + (float)attacker->status[FIGHTER_STATUS_ATTACKMULT] / 100) * attacker->actionAttackMultiplier * (attacker->attack + attacker->status[FIGHTER_STATUS_STRENGTH] - attacker->status[FIGHTER_STATUS_FEEBLE] - attacker->status[FIGHTER_STATUS_PARALYSIS]) / powerCount / attacker->actionPowerRepeat;
}



int Action_Update__0(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__0(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	
}



int Action_Update__1(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__1(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
}



int Action_Update__2(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 1) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__3(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_HealMP(attacker, attacker->actionVars[0].i);
			if (attacker->actionVars[1].i < 0) {
				Fighter_TakeDamage(attacker, NULL, -attacker->actionVars[1].i, 0);
			}
			else {
				Fighter_HealHP(attacker, attacker->actionVars[1].i);
			}
			if (attacker->actionVars[3].i > 0) Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
		}
	}
	
	return 0;
}



int Action_Update__4(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 2) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__5(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__6(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 3) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0 && attacker->readyTimer == 1) {
			Fighter_HealMP(attacker, attacker->actionVars[1].i);
		}
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__7(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 1) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__8(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
			attacker->attackAnimTimer += 2;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= attacker->actionVars[0].i) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__9(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			if (target->state == FIGHTER_STATE_ATTACK1 || target->state == FIGHTER_STATE_BLOCK) {
				Fighter_InflictStatus(attacker, attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__10(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[1].i, attacker->actionVars[2].i, false);
			Fighter_DealDamage(attacker, target, -999999, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[0].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__11(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_GainStatus(attacker, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			if (attacker->actionVars[3].i) Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			
			if (attacker->actionVars[0].i == FIGHTER_STATUS_GUARD) {
				attacker->state = FIGHTER_STATE_BLOCK;
			}
			else if (attacker->actionVars[0].i == FIGHTER_STATUS_COUNTER || attacker->actionVars[0].i == FIGHTER_STATUS_DEFLECT) {
				for (int i = attacker->side * 8; i < attacker->side * 8 + 8; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled || !fighter->alive || fighter == attacker) continue;
					
					fighter->bodyguardId = attacker->id;
				}
			}
		}
	}
	
	return 0;
}



int Action_Update__12(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_GainStatus(attacker, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			if (attacker->actionVars[3].i) Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			target->bodyguardId = attacker->id;
			if (attacker != target) {
				Fighter_MoveTo(attacker, target->x + attacker->facing * 32, target->y, 8, 0);
				attacker->state = FIGHTER_STATE_RUN;
			}
		}
		if (attacker->readyTimer > 1 && !attacker->moveTarget.enabled) {
			attacker->state = FIGHTER_STATE_BLOCK;
		}
	}
	
	return 0;
}



int Action_Update__13(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			Fighter_HealHP(target, attacker->actionVars[0].i);
			Fighter_HealMP(target, attacker->actionVars[1].i);
			
			if (attacker->actionVars[3].i > 0) {
				Fighter_InflictStatus(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			}
		}
	}
	
	return 0;
}



int Action_Update__14(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) {
		Action_BlockUpdate(attacker, target);
	}
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 114 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 4) {
			Audio_PlaySound(SND_firemassattack);
			Battle_ShakeScreen(20);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[1].i, attacker->actionVars[2].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			}
		}
		if (attacker->attackTimer >= 12 && attacker->attackTimer < 94) {
			Battle_ShakeScreen(17 - attacker->attackTimer / 10);
		}
		
		if (attacker->attackTimer == 113) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer < 12) {
			attacker->state = FIGHTER_STATE_RUN;
			
			float xTarget = SCREEN_WIDTH / 2;
			float yTarget = 192;
			float xVel = (float)(xTarget - attacker->xStart) / 11;
			float yVel = (float)(yTarget - attacker->yStart) / 11;
			
			attacker->x += xVel;
			attacker->y += yVel;
			
			if (attacker->x >= xTarget - xVel && attacker->x <= xTarget + xVel) {
				attacker->x = xTarget;
			}
			if (attacker->y >= yTarget - yVel && attacker->y <= yTarget + yVel) {
				attacker->y = yTarget;
			}
			
			attacker->xStore = xTarget;
			attacker->yStore = yTarget;
		}
		else {
			if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK3;
			
			if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
				Fighter_OnAttackSwing(attacker);
				attacker->readyTimer = -1;
				attacker->attackTimer = 0;
				attacker->attackAnimTimer = 0;
				attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
				
				attacker->state = FIGHTER_STATE_ATTACK1;
				
				Audio_PlaySound(SND_swing);
			}
		}
	}
	
	return 0;
}
void Action_Draw__14(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	int iMin = 0;
	int iMax = 15;
	
	if (attacker->targetId == TARGET_ALLYPARTY) {
		iMax = 7;
	}
	else if (attacker->targetId == TARGET_ENEMYPARTY) {
		iMin = 8;
	}
	
	if (attacker->attackTimer < 2) {
		Drawer_SetDrawColor(255, 127, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer < 4) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 8) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
	
	if (attacker->attackTimer < 2) {
		
	}
	else if (attacker->attackTimer < 64) {
		Drawer_DrawSprite(SPR_spark_blazeoblivion, attacker->x + 4 * attacker->facing, attacker->y + 2, 0, 4 * attacker->facing, 4);
	}
	else if (attacker->attackTimer < 84) {
		Drawer_DrawSprite(SPR_spark_blazeoblivion, attacker->x + 4 * attacker->facing, attacker->y + 2, 1, 4 * attacker->facing, 4);
	}
	else if (attacker->attackTimer < 104) {
		Drawer_DrawSprite(SPR_spark_blazeoblivion, attacker->x + 4 * attacker->facing, attacker->y + 2, 2, 4 * attacker->facing, 4);
	}
}



int Action_Update__15(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__16(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 1) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
		if (attacker->attackTimer == 5) {
			for (int i = attacker->side * 8; i < attacker->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Fighter_GainStatus(fighter, FIGHTER_STATUS_STRENGTH, 4, false);
				Fighter_GainStatus(fighter, FIGHTER_STATUS_HASTE, 4, false);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__17(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 126) return 1;
		
		if (attacker->attackTimer >= 40 && attacker->attackTimer <= 43) {
			target->state = FIGHTER_STATE_RUN;
			target->x += 1 * target->facing;
		}
		if (attacker->attackTimer == 44) {
			target->state = FIGHTER_STATE_IDLE;
		}
		
		if (attacker->attackTimer == 62) {
			target->state = FIGHTER_STATE_HURT;
		}
		
		if (attacker->attackTimer == 62 || attacker->attackTimer == 72) {
			target->x += 2 * target->facing;
			Audio_PlaySound(SND_hit3);
		}
		if (attacker->attackTimer == 67 || attacker->attackTimer == 77) {
			target->x -= 2 * target->facing;
			Audio_PlaySound(SND_hit3);
		}
		
		if (attacker->attackTimer == 81) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, 0);
			target->x -= 4 * target->facing;
		}
		
		if (attacker->attackTimer >= 114) {
			attacker->state = FIGHTER_STATE_RUN;
			
			float xTarget = attacker->xStart;
			float yTarget = attacker->yStart;
			float xVel = (float)(xTarget - attacker->xStore) / 11;
			float yVel = (float)(yTarget - attacker->yStore) / 11;
			
			attacker->x += xVel;
			attacker->y += yVel;
			
			if (attacker->x >= xTarget - xVel && attacker->x <= xTarget + xVel) {
				attacker->x = xTarget;
			}
			if (attacker->y >= yTarget - yVel && attacker->y <= yTarget + yVel) {
				attacker->y = yTarget;
			}
			
			if (attacker->attackTimer == 125) {
				attacker->x = attacker->xStart;
				attacker->y = attacker->yStart;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer < 12) {
			attacker->state = FIGHTER_STATE_RUN;
			
			float xTarget = target->x + 48 * target->facing;
			float yTarget = target->y;
			float xVel = (float)(xTarget - attacker->xStart) / 11;
			float yVel = (float)(yTarget - attacker->yStart) / 11;
			
			attacker->x += xVel;
			attacker->y += yVel;
			
			if (attacker->x >= xTarget - xVel && attacker->x <= xTarget + xVel) {
				attacker->x = xTarget;
			}
			if (attacker->y >= yTarget - yVel && attacker->y <= yTarget + yVel) {
				attacker->y = yTarget;
			}
			
			attacker->xStore = xTarget;
			attacker->yStore = yTarget;
		}
		else if (attacker->readyTimer >= 60) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
	}
	
	return 0;
}



int Action_Update__18(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 2) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
		if (attacker->attackTimer == 5) {
			Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__19(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_DODGABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__20(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) {
		Action_BlockUpdate(attacker, target);
	}
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1) {
			while (++attacker->tempVars[0].i < 16 - attacker->side * 8) {
				if (!battle.fighters[attacker->tempVars[0].i].enabled || !battle.fighters[attacker->tempVars[0].i].alive) continue;
				
				target = &battle.fighters[attacker->tempVars[0].i];
				
				if (attacker->x < target->x)
					attacker->facing = 1;
				else
					attacker->facing = -1;
				Fighter_MoveTo(attacker, target->x + attacker->facing * 96, target->y, 24, 0);
				attacker->state = FIGHTER_STATE_RUN;
				
				Audio_PlaySound(SND_swing);
				attacker->attackAnimTimer = 0;
				break;
			}
			
			if (attacker->tempVars[0].i >= 16 - attacker->side * 8) {
				attacker->attackTimer = 20;
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
		}
		else if (attacker->attackTimer == 2 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		else if (attacker->attackTimer == 4) {
			target = &battle.fighters[attacker->tempVars[0].i];
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[1].i, attacker->actionVars[2].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			for (int i = target->side * 8; i < 8 + target->side * 8; i++) {
				Fighter* fighter2 = &battle.fighters[i];
				if (!fighter2->enabled) continue;
				
				fighter2->blockTimer = -1;
				fighter2->blockCooldownTimer = -1;
			}
			
			Battle_ShakeScreen(10);
			
			attacker->state = FIGHTER_STATE_ATTACK3;
		}
		else if (attacker->attackTimer == 10) {
			attacker->attackTimer = 0;
		}
		
		if (attacker->attackTimer == 63) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			attacker->tempVars[0].i = 7 - attacker->side * 8;
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
	}
	
	return 0;
}
void Action_Draw__20(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 1) return;
	
	target = &battle.fighters[attacker->tempVars[0].i];
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer < 2) {
		
	}
	else if (attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
}



int Action_Update__21(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
			attacker->attackAnimTimer += attacker->actionVars[0].i;
		}
		if (attacker->attackTimer == 4) {
			int damage = attacker->speedRoll * attacker->actionAttackMultiplier + attacker->actionPower[0];
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__22(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks < attacker->actionVars[1].i) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL1;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		}
	}
	
	return 0;
}



int Action_Update__23(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) {
		Action_BlockUpdate(attacker, target);
	}
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			Audio_PlaySound(SND_firemassattack);
			Battle_ShakeScreen(14);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			int damageLocal = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i * 2, false);
			Fighter_DealDamage(attacker, target, damageLocal, DAMAGE_FLAG_BLOCKABLE);
			
			damage = attacker->actionVars[1].i;
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive || fighter == target) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_BLOCKABLE);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL3;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		}
	}
	
	return 0;
}
void Action_Draw__23(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		Drawer_SetDrawColor(255, 127, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
	}
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
}



int Action_Update__24(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			if (attacker->actionVars[2].i == 1) {
				Fighter_HealHP(attacker, (attacker->actionVars[0].i * attacker->hpMax + 99) / 100);
				Fighter_HealMP(attacker, (attacker->actionVars[1].i * attacker->mpMax + 99) / 100);
			}
			else {
				Fighter_HealHP(attacker, attacker->actionVars[0].i);
				Fighter_HealMP(attacker, attacker->actionVars[1].i);
			}
		}
	}
	
	return 0;
}



int Action_Update__25(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__26(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 2) {
			if (attacker->actionAttacks % 2 == 0) {
				int damage = Action_GetDamagePower(attacker, target);
				
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				Fighter_DealDamage(attacker, target, damage, 0);
			}
			
			attacker->actionAttacks++;
			
			Audio_PlaySound(SND_explode);
		}
		if (attacker->attackTimer == 6 && attacker->actionAttacks <= 15) {
			attacker->attackTimer = 1;
			attacker->readyTimer = -1;
			attacker->attackAnimTimer = 2;
		}
		if (attacker->attackTimer == 9) {
			Audio_PlaySound(SND_gunfire2);
			Audio_PlaySound(SND_thunder);
		}
		if (attacker->attackTimer == 13) {
			Audio_PlaySound(SND_firemassattack);
			
			int damage = attacker->actionVars[0].i;
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
		
		if (attacker->attackTimer == 63) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer >= 180) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_SPECIAL4;
			
			Audio_PlaySound(SND_gunfire);
			Audio_PlaySound(SND_firemassattack);
		}
		
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, attacker->x + 24 * attacker->facing, target->y, 48, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		
		if (attacker->readyTimer <= 2 && attacker->moveTarget.enabled) {
			attacker->readyTimer = 1;
		}
		else if (attacker->readyTimer < 120) {
			attacker->state = FIGHTER_STATE_SPECIAL3;
			if (attacker->readyTimer % 2 == 0) {
				Battle_ShakeScreen(2);
			}
			if (attacker->readyTimer % 24 == 0) {
				Audio_PlaySound(SND_burn);
			}
		}
		else if (attacker->readyTimer == 120) {
			Audio_PlaySound(SND_mana);
		}
	}
	
	return 0;
}
void Action_Draw__26(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 0 && attacker->readyTimer < 120) {
		Drawer_DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 40, attacker->y - 22, (300 - attacker->readyTimer / 8) % 3, 4, 4);
	}
	if (attacker->readyTimer >= 120 && attacker->readyTimer <= 122) {
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	if (attacker->attackTimer >= 7 && attacker->attackTimer <= 13) {
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
}



int Action_Update__27(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) {
		Action_BlockUpdate(attacker, target);
	}
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 194) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 124) {
			Audio_PlaySound(SND_firemassattack);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[1].i, attacker->actionVars[2].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__27(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 124) {
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	if (attacker->attackTimer >= 124 && attacker->attackTimer < 126) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer >= 126 && attacker->attackTimer < 130) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
}



int Action_Update__28(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			if (target->status[FIGHTER_STATUS_FLOWER]) {
				damage += 80;
				Audio_PlaySound(SND_flower);
			}
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, 0);
		}
		
		if (attacker->attackTimer == 63) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, attacker->x + 24 * attacker->facing, target->y, 48, 0);
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
		
		if (attacker->readyTimer <= 2 && attacker->moveTarget.enabled) {
			attacker->readyTimer = 1;
		}
		
		if (attacker->readyTimer >= 10) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		}
	}
	
	return 0;
}



int Action_Update__29(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 67) return 1;
		
		if (attacker->attackTimer == 4) {
			Audio_PlaySound(SND_flower3);
			Battle_ShakeScreen(4);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				if (fighter->status[FIGHTER_STATUS_FLOWER]) {
					damageLocal += 8;
					Audio_PlaySoundInterrupt(SND_flower);
				}
				
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
		
		if (attacker->attackTimer == 17) {
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 7) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL1;
		
		if (attacker->readyTimer >= 29) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_SPECIAL2;
			
			Audio_PlaySound(SND_luxuryswing);
		}
	}
	
	return 0;
}
void Action_Draw__29(Fighter* attacker, Fighter* target) {
	int iMin = 0;
	int iMax = 15;
	
	if (attacker->targetId == TARGET_ALLYPARTY) {
		iMax = 7;
	}
	else if (attacker->targetId == TARGET_ENEMYPARTY) {
		iMin = 8;
	}
	
	if (attacker->attackTimer < 2) {
		
	}
	else if (attacker->attackTimer < 4) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
			Drawer_DrawSprite(SPR_spark_flower, fighter->x, fighter->y - 24, 0, 4, 4);
		}
	}
	else if (attacker->attackTimer < 8) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
			Drawer_DrawSprite(SPR_spark_flower, fighter->x, fighter->y - 24, 1, 4, 4);
		}
	}
	else if (attacker->attackTimer < 11) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_flower, fighter->x, fighter->y - 24, 2, 4, 4);
		}
	}
	else if (attacker->attackTimer < 14) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_flower, fighter->x, fighter->y - 24, 3, 4, 4);
		}
	}
	else if (attacker->attackTimer < 17) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_flower, fighter->x, fighter->y - 24, 4, 4, 4);
		}
	}
	
	if (attacker->actionAttacks >= 8 && attacker->attackTimer > 40) {
		return;
	}
	
	if (attacker->actionAttacks > 0 || attacker->attackTimer >= 0) {
		Drawer_SetDrawAlpha(63);
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(127);
		Drawer_SetDrawColor(255, 127, 255);
		for (int j = 0; j < 9; j++)
		for (int i = 0; i < 12; i++) {
			Drawer_DrawSprite(SPR_spark_petalbg, -64 + i * 64 + 4 * attacker->facing * (battle.globalTimer % 16), -64 + j * 64 + 4 * (battle.globalTimer % 16), (battle.globalTimer / 6) % 4, 2, 2);
		}
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
	
	/*
	if (attacker->actionAttacks == 0 && attacker->readyTimer >= 9) {
		for (int j = 0; j < 9; j++)
		for (int i = 0; i < 5; i++) {
			Drawer_DrawSprite(SPR_spark_petalbg, 464 - fighter->side * 288 - 160 + i * 64, 480 + j * 64 - 24 * (attacker->readyTimer - 8), (battle.globalTimer / 6) % 4, 2, 2);
		}
	}
	else if (attacker->actionAttacks >= 8 && attacker->attackTimer >= 18) {
		for (int j = 0; j < 9; j++)
		for (int i = 0; i < 5; i++) {
			Drawer_DrawSprite(SPR_spark_petalbg, 464 - fighter->side * 288 - 160 + i * 64, -64 + j * 64 - 24 * (attacker->attackTimer - 17), (battle.globalTimer / 6) % 4, 2, 2);
		}
	}
	else if (attacker->actionAttacks > 0 || attacker->attackTimer >= 0) {
		for (int j = 0; j < 9; j++)
		for (int i = 0; i < 5; i++) {
			Drawer_DrawSprite(SPR_spark_petalbg, 464 - fighter->side * 288 - 160 + i * 64, j * 64 - 16 * (battle.globalTimer % 4), (battle.globalTimer / 6) % 4, 2, 2);
		}
	}
	*/
}



int Action_Update__30(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 3) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__31(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 40) return 1;
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 2) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			Fighter_InflictStatus(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			
			if (attacker->actionVars[3].i < 0) {
				target->mp += attacker->actionVars[3].i;
				if (target->mp < 0) target->mp = 0;
			}
			else {
				Fighter_HealMP(target, attacker->actionVars[3].i);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->readyTimer = -1;
		attacker->attackTimer = 0;
		attacker->attackAnimTimer = 0;
		attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		if (attacker->actionVars[2].i == 2)
			attacker->state = FIGHTER_STATE_SPECIAL1;
		else if (attacker->actionVars[2].i == 1)
			attacker->state = FIGHTER_STATE_ATTACK3;
		else
			attacker->state = FIGHTER_STATE_ATTACK2;
	}
	
	return 0;
}



int Action_Update__32(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 204) return 1;
		
		if (attacker->attackTimer == 1) {
			target->actionVars[0].i = audioSystem.soundFilterId;
			Audio_ApplySoundFilter(2);
		}
		if (attacker->attackTimer >= 1 && attacker->attackTimer < 64 && attacker->attackTimer % 4 == 1) {
			Audio_PlaySound(SND_burn);
		}
		if (attacker->attackTimer == 96) {
			Audio_ApplySoundFilter(target->actionVars[0].i);
		}
		
		if (attacker->attackTimer == 144) {
			Audio_PlaySound(SND_firemassattack);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				if (fighter->hp <= attacker->actionVars[1].i) {
					Audio_PlaySoundInterrupt(SND_flower);
					fighter->hp = 0;
				}
				
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 51) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
		}
	}
	
	return 0;
}
void Action_Draw__32(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	if (attacker->attackTimer < 96) {
		for (int i = 0; i < 4; i++) {
			Drawer_FillRect(0, Random_IRange(128, SCREEN_HEIGHT), SCREEN_WIDTH, 2);
			Drawer_FillRect(0, Random_IRange(128, SCREEN_HEIGHT), SCREEN_WIDTH, 2);
			Drawer_FillRect(0, Random_IRange(128, SCREEN_HEIGHT), SCREEN_WIDTH, 4);
		}
	}
	else if (attacker->attackTimer >= 142 && attacker->attackTimer < 144) {
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}



int Action_Update__33(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, 0);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__34(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 7) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks < attacker->actionVars[1].i) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL1;
		if (attacker->readyTimer == 1 && attacker->actionAttacks == 0) {
			Audio_PlaySound(SND_minigunambience);
		}
		
		if ((attacker->actionAttacks == 0 && attacker->readyTimer >= 56) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		}
	}
	
	return 0;
}



int Action_Update__35(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) {
		Action_BlockUpdate(attacker, target);
	}
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1) {
			Battle_Camera_MoveTo(target->x + attacker->facing * 2, target->y - 24, 3, 256);
		}
		if (attacker->attackTimer == 3) {
			Fighter_MoveTo(attacker, target->x + attacker->facing * 8, target->y, 24, 0);
			attacker->state = FIGHTER_STATE_ATTACK3;
		}
		if (attacker->attackTimer == 4) {
			if (attacker->moveTarget.enabled) attacker->attackTimer--;
			if ((attacker->facing > 0 && attacker->x >= target->x) || (attacker->facing < 0 && attacker->x <= target->x)) {
				int damage = Action_GetDamagePower(attacker, target);
				
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[1].i, attacker->actionVars[0].i, false);
				Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[0].i, false);
				Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
				
				Battle_CreateSpark(6, target->x, target->y - 24, 0);
				Battle_ShakeScreen(28);
				Audio_PlaySound(SND_explode);
				
				attacker->state = FIGHTER_STATE_SPECIAL2;
				attacker->attackTimer++;
				Fighter_MoveTo(attacker, target->x + attacker->facing * 48, target->y, 1, 0);
			}
		}
		if (attacker->attackTimer == 5 && attacker->moveTarget.enabled) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 63) {
			Battle_Camera_MoveToStart(4);
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = attacker->readyTimer % 8 < 4 ? FIGHTER_STATE_ATTACK1 : FIGHTER_STATE_SPECIAL1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
	}
	
	return 0;
}



int Action_Update__36(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 234) {
		Action_BlockUpdate(attacker, target);
	}
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 294) return 1;
		
		if (attacker->attackTimer >= 40 && attacker->attackTimer <= 204 && attacker->attackTimer % 4 == 0 && attacker->attackTimer % 20 <= 15) {
			Battle_CreateSpark(6, 160 + (1 - attacker->side) * 320 + Random_IRange(-64, 64), 304 + Random_IRange(-64, 64), 0);
			Battle_CreateSpark(6, 160 + (1 - attacker->side) * 320 + 130 * cos((double)attacker->attackTimer / 2.5) + Random_IRange(-24, 24), 304 + 80 * cos((double)attacker->attackTimer / 3.5) + Random_IRange(-24, 24), 0);
			Battle_ShakeScreen(28);
			Audio_PlaySound(SND_explode);
		}
		
		if (attacker->attackTimer == 234) {
			attacker->y += 512;
			Audio_PlaySound(SND_firemassattack);
			Battle_ShakeScreen(20);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_BLOCKABLE);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			
			attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
			attacker->y -= 512;
		}
	}
	
	return 0;
}
void Action_Draw__36(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	if (attacker->attackTimer < 4) {
		for (int x = attacker->x - 7; x <= attacker->x + 6; x += 4) {
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_FillRect(x, 128, 2, attacker->y + 512 - 128);
		}
	}
	else if (attacker->attackTimer < 232) {
		
	}
	else if (attacker->attackTimer < 234) {
		Drawer_SetDrawColor(255, 127, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer < 236) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 240) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
	
	if (attacker->attackAnimTimer < 234) {
		
	}
	else if (attacker->attackAnimTimer < 238) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, 160 + (1 - attacker->side) * 320, 304, 0, 16, 16);
	}
	else if (attacker->attackAnimTimer < 242) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, 160 + (1 - attacker->side) * 320, 304, 1, 16, 16);
	}
	else if (attacker->attackAnimTimer < 246) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, 160 + (1 - attacker->side) * 320, 304, 2, 16, 16);
	}
	else if (attacker->attackAnimTimer < 250) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, 160 + (1 - attacker->side) * 320, 304, 3, 16, 16);
	}
}



int Action_Update__37(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			Fighter_ClearAllStatus(target);
			if (target->ai == 10001) {
				profile.flags[FLAG_ARMOR_HELLGONER_TURNCOUNT]--;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->readyTimer = -1;
		attacker->attackTimer = 0;
		attacker->attackAnimTimer = 0;
		attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		
		if (attacker->actionVars[1].i == 1)
			attacker->state = FIGHTER_STATE_ATTACK3;
		else
			attacker->state = FIGHTER_STATE_ATTACK2;
		
		Audio_PlaySound(SND_neutralize);
	}
	
	return 0;
}



int Action_Update__38(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			if (!target->alive) {
				Audio_PlaySound(SND_reset);
				target->alive = true;
				target->state = FIGHTER_STATE_ATTACK1;
				Fighter_HealHP(target, attacker->actionVars[0].i);
				Fighter_HealMP(target, attacker->actionVars[1].i);
			}
			else {
				Audio_PlaySound(SND_dodge);
			}
		}
	}
	
	return 0;
}



int Action_Update__39(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_DODGABLE | DAMAGE_FLAG_LETHAL);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__40(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__40(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer < 2) {
		
	}
	else if (attacker->attackTimer < 4) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 8) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
}


int Action_Update__41(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 40) return 1;
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 2) {
			Fighter_InflictStatus(attacker, attacker, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->readyTimer = -1;
		attacker->attackTimer = 0;
		attacker->attackAnimTimer = 0;
		attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		attacker->state = FIGHTER_STATE_ATTACK3;
	}
	
	return 0;
}
void Action_Draw__41(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, attacker);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, attacker->x, attacker->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, attacker->x, attacker->y - 24, 4, 2, 2);
	}
}



int Action_Update__42(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->moveTarget.enabled) {
			attacker->attackTimer--;
			
			if (attacker->attackAnimTimer % 6 == 1) {
				attacker->state = FIGHTER_STATE_SPECIAL1;
			}
			else if (attacker->attackAnimTimer % 6 == 4) {
				attacker->state = FIGHTER_STATE_IDLE;
				Audio_PlaySound(SND_chess_move);
			}
		}
		if (attacker->attackTimer == 2) {
			Audio_PlaySound(SND_explode);
			Battle_ShakeScreen(12);
			attacker->state = FIGHTER_STATE_ATTACK3;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
		}
		
		if (attacker->attackTimer == 43) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer % 8 == 1) {
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
		else if (attacker->readyTimer % 8 == 5) {
			attacker->state = FIGHTER_STATE_IDLE;
			Audio_PlaySound(SND_chess_move);
		}
		
		if ((Action_AttackUpdate(attacker, target) && attacker->readyTimer >= 16) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = PointDistance(target->x, target->y, attacker->x, attacker->y) / 12;
			Fighter_MoveTo(attacker, target->x - attacker->facing * 32, target->y, 12, 0);
		}
	}
	
	return 0;
}
void Action_Draw__42(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	if (attacker->attackTimer < 2) {
		
	}
	else if (attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackTimer < 12) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackTimer < 16) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}



int Action_Update__43(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE | DAMAGE_FLAG_CRITICAL);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__44(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			Fighter_ClearAllStatus(attacker);
			if (attacker->ai == 10001) {
				profile.flags[FLAG_ARMOR_HELLGONER_TURNCOUNT]--;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->readyTimer = -1;
		attacker->attackTimer = 0;
		attacker->attackAnimTimer = 0;
		attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		Audio_PlaySound(SND_neutralize);
	}
	
	return 0;
}



int Action_Update__45(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			attacker->status[FIGHTER_STATUS_BLEED] = 0;
			attacker->status[FIGHTER_STATUS_POISON] = 0;
			attacker->status[FIGHTER_STATUS_PARALYSIS] = 0;
			attacker->statusNext[FIGHTER_STATUS_BLEED] = 0;
			attacker->statusNext[FIGHTER_STATUS_POISON] = 0;
			attacker->statusNext[FIGHTER_STATUS_PARALYSIS] = 0;
			if (attacker->ai == 10001) {
				profile.flags[FLAG_ARMOR_HELLGONER_TURNCOUNT]--;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->readyTimer = -1;
		attacker->attackTimer = 0;
		attacker->attackAnimTimer = 0;
		attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		Audio_PlaySound(SND_flower2);
	}
	
	return 0;
}



int Action_Update__46(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_ClearAllStatus(fighter);
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__47(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, FIGHTER_STATUS_BLEED, 3, false);
			Fighter_InflictStatus(attacker, target, FIGHTER_STATUS_PARALYSIS, 3, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 7) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 2;
			}
		}
	}
	else if (attacker->readyTimer >= 2) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	else if (attacker->readyTimer == 1) {
		Audio_PlaySound(SND_firemassattack);
		Audio_PlaySound(SND_aztecrage);
	}
	
	return 0;
}
void Action_Draw__47(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 34) {
		Drawer_DrawSprite(SPR_misc_subspace_redaura, attacker->x, attacker->y - 24, (battle.globalTimer / 2) % 4, 2, 2);
		Drawer_SetDrawColor(0, 0, 0);
		DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, attacker->x, attacker->y, 2, 2, attacker->facing);
		Drawer_SetDrawColor(255, 255, 255);
	}
	
	if (attacker->readyTimer >= 0 && attacker->readyTimer < 2) {
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
}



int Action_Update__48(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			int a = target->defense;
			if (a > 3 || a < 0)
				a = 9999;
			else if (a == 0)
				a = 1;
			else if (a == 3)
				a *= 3;
			if (attacker->mp % 10 == a) {
				Fighter_HealHP(attacker, attacker->actionVars[0].i);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__49(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 78) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Audio_PlaySound(SND_absorb);
			attacker->state = FIGHTER_STATE_BLOCK;
		}
		if (attacker->readyTimer == 48) {
			int hp = 0;
			int mp = 0;
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || fighter->mp <= 0) continue;
				
				if (fighter->hp < attacker->actionVars[0].i) {
					hp += fighter->hp;
					fighter->hp = 0;
				}
				else {
					hp += attacker->actionVars[0].i;
					fighter->hp -= attacker->actionVars[0].i;
				}
				
				if (fighter->mp < attacker->actionVars[1].i) {
					mp += fighter->mp;
					fighter->mp = 0;
				}
				else {
					mp += attacker->actionVars[1].i;
					fighter->mp -= attacker->actionVars[1].i;
				}
			}
			if (attacker->actionVars[3].i > 0 && attacker->mp + mp >= attacker->mpMax) {
				Fighter_GainStatus(attacker, attacker->actionVars[2].i, (attacker->mp + mp - attacker->mpMax) / attacker->actionVars[3].i, false);
			}
			
			Fighter_HealHP(attacker, hp);
			Fighter_HealMP(attacker, mp);
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
	}
	
	return 0;
}
void Action_Draw__49(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer < 4) {
		
	}
	else if (attacker->readyTimer < 48) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || fighter->mp <= 0) continue;
			
			Drawer_SetDrawColor(0, 127, 255);
			if (attacker->readyTimer < 44)
				Drawer_DrawSprite(SPR_spark_spark, fighter->x + (attacker->x - fighter->x) * (attacker->readyTimer - 4) / 40, fighter->y - 48 + (attacker->y - fighter->y + 20) * (attacker->readyTimer - 4) * (attacker->readyTimer - 4) / 1600, (attacker->readyTimer / 4) % 3, 2, 2);
			else
				Drawer_DrawSprite(SPR_spark_spark, attacker->x, attacker->y - 28, (attacker->readyTimer / 4) % 3, 2, 2);
			Drawer_SetDrawColor(255, 255, 255);
		}
	}
}



int Action_Update__50(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, FIGHTER_STATUS_BLEED, 12, false);
			Fighter_InflictStatusDodgable(attacker, target, FIGHTER_STATUS_POISON, 12, false);
			if (target->blockTimer < 0 || target->blockTimer >= target->blockTime) {
				Fighter_GainStatus(attacker, FIGHTER_STATUS_FEEBLE, 20, false);
				Fighter_GainStatus(attacker, FIGHTER_STATUS_BIND, 20, false);
			}
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__51(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_HealMP(attacker, attacker->actionVars[0].i);
			Fighter_HealHP(attacker, attacker->actionVars[1].i);
			if (attacker->actionVars[3].i > 0) Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			bool condition = false;
			for (int i = 0; i < attacker->passiveCount; i++) {
				if (attacker->passives[i] == 41) {
					condition = true;
					break;
				}
			}
			if (!condition) {
				Fighter_TakeDamage(attacker, NULL, 5, 0);
			}
		}
	}
	
	return 0;
}



int Action_Update__52(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target) + (attacker->hp + attacker->mp) / 8;
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 7) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
			else {
				if (attacker->hp > 1) attacker->hp = 1;
				if (attacker->mp > 0) attacker->mp = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX / 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 4 == 2)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else if (attacker->actionAttacks % 4 == 0)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__53(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			if (attacker->actionVars[3].i > 0) {
				Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			}
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			Fighter_HealMP(attacker, (int)(attacker->actionVars[0].f * (float)attacker->actionInflictedDamage));
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__54(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 40) return 1;
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 2) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			attacker->attack += attacker->actionVars[0].i;
			attacker->defense += attacker->actionVars[1].i;
			attacker->speed += attacker->actionVars[2].i;
			Fighter_HealHP(attacker, attacker->actionVars[3].i);
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->readyTimer = -1;
		attacker->attackTimer = 0;
		attacker->attackAnimTimer = 0;
		attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
		attacker->state = FIGHTER_STATE_ATTACK3;
	}
	
	return 0;
}



int Action_Update__55(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			Fighter_HealMP(target, attacker->actionVars[0].i);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__56(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			if (attacker->actionVars[3].i > 0) {
				Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			}
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 2) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
			else {
				Fighter_TakeDamage(attacker, NULL, attacker->actionVars[0].i, 0);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0) {
				if (attacker->actionVars[1].i == 1)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else
					attacker->state = FIGHTER_STATE_ATTACK2;
			}
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__57(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 366 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackAnimTimer++;
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionInflictedDamage < attacker->actionVars[2].i) {
				attacker->attackTimer = 327;
				Fighter_MoveToStart(attacker);
				attacker->state = FIGHTER_STATE_RUN;
			}
		}
		
		if (attacker->attackTimer == 8 || attacker->attackTimer == 44 || attacker->attackTimer == 80) {
			attacker->state = FIGHTER_STATE_ATTACK1;
			target->state = FIGHTER_STATE_HURT;
			target->x = attacker->x + attacker->facing * 24;
			target->y = attacker->y - 6;
		}
		
		if (attacker->attackTimer == 20) {
			attacker->state = FIGHTER_STATE_SPECIAL1;
			Audio_PlaySound(SND_hit3);
			Battle_ShakeScreen(26);
			target->x = attacker->x + attacker->facing * 12;
			target->y = attacker->y - 6;
		}
		if (attacker->attackTimer == 56) {
			attacker->state = FIGHTER_STATE_SPECIAL2;
			Audio_PlaySound(SND_hit3);
			Battle_ShakeScreen(26);
			target->x = attacker->x + attacker->facing * 12;
			target->y = attacker->y - 6;
		}
		if (attacker->attackTimer == 92) {
			attacker->state = FIGHTER_STATE_SPECIAL1;
			Audio_PlaySound(SND_hit3);
			Battle_ShakeScreen(26);
			target->x = target->xStart;
			target->y = target->yStart - 10000;
		}
		
		if (attacker->attackTimer == 109) {
			Audio_PlaySound(SND_paperfold);
		}
		if (attacker->attackTimer == 110 || attacker->attackTimer == 134 || attacker->attackTimer == 158) {
			attacker->state = FIGHTER_STATE_SPECIAL2;
		}
		if (attacker->attackTimer == 122 || attacker->attackTimer == 146 || attacker->attackTimer == 170) {
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
		if (attacker->attackTimer == 180) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
		if (attacker->attackTimer == 181 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 182) {
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
		if (attacker->attackTimer == 216) {
			Audio_PlaySound(SND_swing);
			attacker->state = FIGHTER_STATE_ATTACK3;
		}
		
		if (attacker->attackTimer == 291) {
			Audio_PlaySound(SND_slap);
		}
		if (attacker->attackTimer == 326) {
			target->x = target->xStart;
			target->y = target->yStart;
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			if (attacker->actionVars[1].i > 0) {
				Fighter_InflictStatus(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			}
			Fighter_DealDamage(attacker, target, damage, 0);
			
			attacker->actionAttacks++;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, target->x - attacker->facing * 40, target->y, 12, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		if (!attacker->moveTarget.enabled) {
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
		
		if ((Action_AttackUpdate(attacker, target) && !attacker->moveTarget.enabled && attacker->readyTimer > 1) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__57(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	
	if (attacker->attackTimer < 180) {
		
	}
	else if (attacker->attackTimer < 182) {
		Drawer_DrawSprite(SPR_misc_paperplane, attacker->x - attacker->facing * 4, attacker->y - 16, 2, -2 * attacker->facing, 2);
	}
	else if (attacker->attackTimer < 216) {
		Drawer_DrawSprite(SPR_misc_paperplane, attacker->x - attacker->facing * 14, attacker->y - 24, 1, -2 * attacker->facing, 2);
	}
	else if (attacker->attackTimer < 291) {
		Drawer_DrawSprite(SPR_misc_paperplane, attacker->x + attacker->facing * 8 + (target->xStart - attacker->x - attacker->facing * 8) * (attacker->attackTimer - 216) / 75, attacker->y - 48 + (target->yStart - attacker->y + 44) * (attacker->attackTimer - 216) / 75 + (attacker->attackTimer - 253) * (attacker->attackTimer - 253) / 15 - 90, (attacker->attackTimer - 216) / 26, -2 * attacker->facing, 2);
	}
	else if (attacker->attackTimer < 326) {
		Drawer_DrawSprite(SPR_misc_paperplane, target->xStart, target->yStart - 4, 2, -2 * attacker->facing, 2);
	}
}



int Action_Update__58(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4 && attacker->actionAttacks < 15) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 54 && !attacker->moveTarget.enabled) return 1;
		
		bool skipReady = false;
		
		if (attacker->actionAttacks < 2) {
			if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
				attacker->attackAnimTimer++;
				attacker->attackTimer--;
			}
			
			if (attacker->attackTimer == 4) attacker->attackTimer = 100;
		}
		else if (attacker->actionAttacks < 3) {
			attacker->attackAnimTimer = 999;
			if (attacker->attackTimer == 1) {
				Audio_PlaySound(SND_swing);
				Fighter_MoveTo(attacker, target->x - attacker->facing * 36, target->y, 32, 0);
				attacker->state = FIGHTER_STATE_ATTACK2;
			}
			if (attacker->attackTimer == 2 && attacker->moveTarget.enabled) attacker->attackTimer--;
			
			if (attacker->attackTimer == 4) attacker->attackTimer = 100;
		}
		else if (attacker->actionAttacks < 7) {
			skipReady = true;
			if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
				attacker->attackAnimTimer++;
				attacker->attackTimer--;
				
				if (attacker->attackAnimTimer == 2) {
					if (attacker->actionAttacks >= 4) attacker->facing = -attacker->facing;
					Fighter_MoveTo(attacker, target->x + attacker->facing * 62, target->y, 26, 0);
				}
			}
			if (attacker->attackTimer == 3) {
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
			
			if (attacker->attackTimer == 5) attacker->attackTimer = 100;
		}
		else if (attacker->actionAttacks < 15) {
			skipReady = true;
			if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
				if (attacker->attackAnimTimer == 1) {
					Audio_PlaySound(SND_swing);
					if (attacker->actionAttacks == 7) attacker->facing = -attacker->facing;
				}
				
				attacker->attackAnimTimer += 4;
				attacker->attackTimer--;
				
				if (attacker->state == FIGHTER_STATE_ATTACK2)
					attacker->state = FIGHTER_STATE_SPECIAL3;
				else if (attacker->state == FIGHTER_STATE_SPECIAL3)
					attacker->state = FIGHTER_STATE_SPECIAL4;
				else
					attacker->state = FIGHTER_STATE_ATTACK2;
			}
			
			if (attacker->attackTimer == 4) attacker->attackTimer = 100;
		}
		else {
			if (attacker->attackTimer == 1 && attacker->attackAnimTimer < 44) {
				attacker->attackTimer--;
				
				if (attacker->attackAnimTimer == 1) {
					Audio_PlaySound(SND_slap);
					Audio_PlaySound(SND_luxuryswing);
					attacker->state = FIGHTER_STATE_ATTACK1;
					Fighter_MoveTo(attacker, target->x - attacker->facing * 160, target->y, 25, 0);
				}
			}
			
			if (attacker->attackTimer == 4) {
				if (attacker->actionVars[1].i > 0) {
					Battle_ShakeScreen(20);
					Audio_PlaySound(SND_gunfire2);
				}
				int damage = Action_GetDamagePower(attacker, target) + attacker->actionVars[1].i;
				
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				Fighter_DealDamage(attacker, target, damage, 0);
				
				attacker->actionAttacks++;
			}
			
			if (attacker->attackTimer == 53) {
				Fighter_MoveToStart(attacker);
				attacker->state = FIGHTER_STATE_RUN;
			}
		}
		
		if (attacker->attackTimer == 100) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Min(1, Action_CalculateAttackPower(attacker, target, damage));
			
			if (!((target->blockTimer >= 0 && target->blockTimer < target->dodgeTime) || target->status[FIGHTER_STATUS_EVADE])) {
				attacker->actionVars[1].i += attacker->actionVars[0].i;
			}
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE | DAMAGE_FLAG_CAPPED);
			
			attacker->actionAttacks++;
			
			if (skipReady) {
				attacker->attackTimer = 0;
				attacker->attackAnimTimer = 0;
				
				if (attacker->actionAttacks == 0)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else if (attacker->actionAttacks == 1)
					attacker->state = FIGHTER_STATE_ATTACK1;
				else if (attacker->actionAttacks == 3)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else if (attacker->actionAttacks == 4)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else if (attacker->actionAttacks == 5)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else if (attacker->actionAttacks == 6)
					attacker->state = FIGHTER_STATE_ATTACK3;
				
				Audio_PlaySound(SND_swing);
			}
			else {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if ((Action_AttackUpdate(attacker, target) && !attacker->moveTarget.enabled) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else if (attacker->actionAttacks == 1)
				attacker->state = FIGHTER_STATE_ATTACK1;
			else if (attacker->actionAttacks == 3)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else if (attacker->actionAttacks == 4)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else if (attacker->actionAttacks == 5)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else if (attacker->actionAttacks == 6)
				attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__58(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	if (attacker->actionAttacks == 2) {
		
	}
	else if (attacker->actionAttacks < 15) {
		actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	}
	else {
		if (attacker->attackAnimTimer < 3) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, 2, 2);
		}
		else if (attacker->attackAnimTimer < 6) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, 2, 2);
		}
		else if (attacker->attackAnimTimer < 9) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, 2);
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, -2, 2);
		}
		else if (attacker->attackAnimTimer < 12) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, -2, 2);
		}
		else if (attacker->attackAnimTimer < 15) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, -2, 2);
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, -2, -2);
		}
		else if (attacker->attackAnimTimer < 18) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, -2, -2);
		}
		else if (attacker->attackAnimTimer < 21) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, -2, -2);
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, 2, -2);
		}
		else if (attacker->attackAnimTimer < 24) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, 2, -2);
		}
		else if (attacker->attackAnimTimer < 28) {
			Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, -2);
		}
		else if (attacker->attackAnimTimer < 32) {
			Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 8, 8);
		}
		else if (attacker->attackAnimTimer < 36) {
			Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 8, 8);
		}
		else if (attacker->attackAnimTimer < 40) {
			Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 8, 8);
		}
		else if (attacker->attackAnimTimer < 44) {
			Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 8, 8);
		}
	}
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
}



int Action_Update__59(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Min(attacker->actionVars[0].i, Action_CalculateAttackPower(attacker, target, damage));
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE | DAMAGE_FLAG_CAPPED);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 1) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__60(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 2) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			Fighter_DealDamage(attacker, target, damage, 0);
			
			attacker->actionAttacks++;
		}
		if (attacker->attackTimer == 6 && attacker->actionAttacks <= 7) {
			attacker->attackTimer = 1;
			attacker->readyTimer = -1;
			attacker->attackAnimTimer = 1;
		}
		if (attacker->attackTimer == 7) {
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
		
		if (attacker->attackTimer == 63) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer >= 10) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_SPECIAL2;
			
			Audio_PlaySound(SND_gunfire);
			Audio_PlaySound(SND_heatray);
		}
		
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, attacker->x + 24 * attacker->facing, target->y, 48, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		
		if (attacker->readyTimer <= 2 && attacker->moveTarget.enabled) {
			attacker->readyTimer = 1;
		}
		
		if (attacker->readyTimer == 3) {
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
	}
	
	return 0;
}



int Action_Update__61(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			if (attacker->actionVars[3].i > 0) {
				Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			}
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			Fighter_TakeDamage(attacker, NULL, attacker->actionVars[0].i, 0);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__62(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, 0);
		}
		
		if (attacker->attackTimer == 43) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, attacker->x + 24 * attacker->facing, target->y, 48, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		
		if (attacker->readyTimer <= 2 && attacker->moveTarget.enabled) {
			attacker->readyTimer = 1;
		}
		
		if (attacker->readyTimer >= 3) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
	}
	
	return 0;
}



int Action_Update__63(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			if (attacker->actionInflictedDamage > 0) {
				if (target->mp < attacker->actionVars[0].i) {
					Fighter_HealMP(attacker, target->mp);
					target->mp = 0;
				}
				else {
					Fighter_HealMP(attacker, attacker->actionVars[0].i);
					target->mp -= attacker->actionVars[0].i;
				}
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : ((attacker->actionVars[1].i == 3) ? FIGHTER_STATE_ATTACK3 : FIGHTER_STATE_ATTACK1);
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 3)
				attacker->state = FIGHTER_STATE_ATTACK1;
			else if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__64(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			if (target->mp <= attacker->actionVars[1].i) {
				damage += attacker->actionVars[0].i;
			}
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 1) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__65(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (!attacker->moveTarget.enabled && attacker->x == target->x && attacker->y == target->y) {
			if (attacker->actionAttacks == 0)
				Fighter_MoveTo(attacker, target->x + 110 * attacker->facing, target->y, 92, 0);
			else
				Fighter_MoveTo(attacker, attacker->xStart, attacker->yStart, 92, 0);
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 1) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
		if (attacker->attackTimer == 33 && !attacker->moveTarget.enabled) {
			attacker->state = FIGHTER_STATE_IDLE;
			attacker->facing = -attacker->facing;
		}
		
		if (attacker->attackTimer == 43) {
			if (attacker->status[FIGHTER_STATUS_MANAPERMADISCOUNT] < attacker->actionVars[1].i) {
				attacker->status[FIGHTER_STATUS_MANAPERMADISCOUNT] = Min(attacker->actionVars[1].i, attacker->status[FIGHTER_STATUS_MANAPERMADISCOUNT] + attacker->actionVars[0].i);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks == 0)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
			if (attacker->actionAttacks == 1)
				attacker->facing = -attacker->facing;
			Fighter_MoveTo(attacker, target->x, target->y, 92, 0);
		}
	}
	
	return 0;
}



int Action_Update__66(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (!attacker->moveTarget.enabled && attacker->x == target->x && attacker->y == target->y) {
			if (attacker->actionAttacks <= 1)
				Fighter_MoveTo(attacker, target->x + 96 * attacker->facing, target->y, 92, 0);
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 2) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
			else {
				Fighter_GainStatus(attacker, FIGHTER_STATUS_PARALYSIS, target->status[FIGHTER_STATUS_PARALYSIS], false);
				target->status[FIGHTER_STATUS_PARALYSIS] = 0;
				Audio_PlaySound(SND_electric);
			}
		}
		if (attacker->attackTimer == 43) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveToStart(attacker);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks <= 1)
				attacker->state = FIGHTER_STATE_RUN;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
			if (attacker->actionAttacks >= 1)
				attacker->facing = -attacker->facing;
			if (attacker->actionAttacks <= 1)
				Fighter_MoveTo(attacker, target->x, target->y, 92, 0);
		}
	}
	
	return 0;
}



int Action_Update__67(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 174 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 124) {
			Fighter_MoveTo(attacker, 160 + target->side * 320, 80, 80, 0);
		}
		if (attacker->attackTimer == 134) {
			Audio_PlaySound(SND_explode);
			Audio_PlaySound(SND_crusherhit);
			Battle_ShakeScreen(30);
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
		if (attacker->attackTimer == 173) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveToStart(attacker);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_RUN;
			
			Audio_PlaySound(SND_swing);
			Fighter_MoveTo(attacker, 160 + target->side * 320, -560, 64, 0);
		}
	}
	
	return 0;
}
void Action_Draw__67(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	if (attacker->attackTimer >= 124 && attacker->attackTimer < 173) {
		Drawer_DrawSprite(SPR_misc_sapphirebus, attacker->x, attacker->y + 282, 3, 4, 4);
	}
	
	if (attacker->attackTimer < 132) {
		
	}
	else if (attacker->attackTimer < 134) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 138) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
}



int Action_Update__68(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 67) return 1;
		
		if (attacker->attackTimer == 8) {
			Audio_PlaySound(SND_saw);
			Audio_PlaySound(SND_nerf);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Min(attacker->actionVars[2].i, Action_CalculateAttackPower(attacker, fighter, damage));
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_CAPPED);
			}
		}
		
		if (attacker->attackTimer == 12) {
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 3) {
				attacker->attackTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL3;
		
		if (attacker->readyTimer >= 50) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_SPECIAL4;
			
			Audio_PlaySound(SND_swing);
			Audio_PlaySound(SND_heatray);
		}
	}
	
	return 0;
}
void Action_Draw__68(Fighter* attacker, Fighter* target) {
	int iMin = 0;
	int iMax = 15;
	
	if (attacker->targetId == TARGET_ALLYPARTY) {
		iMax = 7;
	}
	else if (attacker->targetId == TARGET_ENEMYPARTY) {
		iMin = 8;
	}
	
	if (attacker->attackTimer < 6) {
		
	}
	else if (attacker->attackTimer < 8) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 12) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
}



int Action_Update__69(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_HealMP(attacker, attacker->actionVars[0].i);
			if (attacker->actionVars[1].i < 0) {
				Fighter_TakeDamage(attacker, NULL, -attacker->actionVars[1].i, 0);
			}
			else {
				Fighter_HealHP(attacker, attacker->actionVars[1].i);
			}
			if (attacker->actionVars[3].i > 0) Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_GainStatus(attacker, FIGHTER_STATUS_CHARGE, 1, false);
		}
	}
	
	return 0;
}



int Action_Update__70(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 154 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionInflictedDamage <= 0) {
				attacker->attackTimer = 151;
			}
			else {
				Fighter_MoveTo(target, attacker->xStart + attacker->facing * 30, target->y, 18, 0);
				target->flinchTicks = 0;
				target->state = FIGHTER_STATE_HURT;
			}
			attacker->facing = -attacker->facing;
		}
		
		if (attacker->attackTimer == 10) {
			Fighter_MoveTo(attacker, attacker->xStart, target->y, 104, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		if (attacker->attackTimer == 11 && attacker->moveTarget.enabled) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 12) {
			attacker->facing = -attacker->facing;
			attacker->state = FIGHTER_STATE_BLOCK;
		}
		if (attacker->attackTimer == 13 && target->moveTarget.enabled) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 14) {
			attacker->state = FIGHTER_STATE_ATTACK3;
		}
		if (attacker->attackTimer == 16) {
			attacker->state = FIGHTER_STATE_ATTACK1;
			Audio_PlaySound(SND_swing);
		}
		
		if (attacker->attackTimer == 18 || attacker->attackTimer == 32) {
			Battle_CreateSpark(7, target->x, target->y, 0);
			Audio_PlaySound(SND_explode);
			Battle_ShakeScreen(20);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			Fighter_DealDamage(attacker, target, damage, 0);
			
			attacker->actionAttacks++;
		}
		
		if (attacker->attackTimer >= 16 && attacker->attackTimer < 46) {
			target->x = attacker->xStart + attacker->facing * 30 + (target->xStart - attacker->xStart - attacker->facing * 30) * (attacker->attackTimer - 15) / 30;
		}
		
		if (attacker->attackTimer == 46) {
			attacker->state = (attacker->bodyId == 91) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_IDLE;
			target->x = target->xStart;
			target->y = target->yStart;
			
			Audio_PlaySound(SND_firemassattack);
			Audio_PlaySound(SND_shards);
			Audio_PlaySound(SND_thunder);
			Battle_ShakeScreen(60);
			
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Battle_CreateSpark(7, fighter->x, fighter->y, 0);
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatusDodgable(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
			
			attacker->actionAttacks++;
		}
		
		if (attacker->attackTimer >= 48 && attacker->attackTimer <= 112 && attacker->attackTimer % 16 == 0) {
			Audio_PlaySound(SND_burn);
			for (int i = 0; i < 4; i++) {
				Battle_CreateSpark(7, 128 * (i + 1), 362, 0);
			}
		}
		
		if (attacker->attackTimer == 153) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveToStart(attacker);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, target->x + attacker->facing * 40, target->y, 104, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		if (!attacker->moveTarget.enabled) {
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
		
		if ((Action_AttackUpdate(attacker, target) && !attacker->moveTarget.enabled && attacker->readyTimer > 1) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__70(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer < 2) {
		
	}
	else if (attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackTimer < 16) {
		
	}
	else if (attacker->attackTimer < 18) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer < 22) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackTimer < 34) {
		
	}
	else if (attacker->attackTimer < 36) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer < 40) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackTimer < 52) {
		
	}
	else if (attacker->attackTimer < 54) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer < 58) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	
	if (attacker->attackTimer < 15) {
		
	}
	else if (attacker->attackTimer < 47) {
		Drawer_DrawSprite(SPR_spark_blazewave, target->x, target->y, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackTimer < 104) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (attacker->attackTimer < 134) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, (attacker->attackTimer - 103) * 8, (attacker->attackTimer - 103) * 8);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
}



int Action_Update__71(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__72(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__73(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatusDodgable(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			}
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 2) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__74(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Min(attacker->actionVars[2].i, Action_CalculateAttackPower(attacker, fighter, damage));
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, true);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_CAPPED);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__75(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			bool condition = target->hp <= attacker->actionVars[0].i;
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			if (attacker->actionInflictedDamage > 0 && condition) {
				Audio_PlaySoundInterrupt(SND_flower);
				target->hp = 0;
				Fighter_CheckDefeat(target, 0);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__76(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Fighter_HealHP(fighter, attacker->actionVars[0].i);
				Fighter_HealMP(fighter, attacker->actionVars[1].i);
				
				if (attacker->actionVars[3].i > 0) {
					Fighter_InflictStatus(attacker, fighter, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
				}
			}
		}
	}
	
	return 0;
}



int Action_Update__77(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_LETHAL);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__78(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatusDodgable(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			}
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 19) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 59;
			}
			else {
				Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 60) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__79(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			bool condition = target->hp <= attacker->actionVars[0].i;
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE | DAMAGE_FLAG_LETHAL);
			
			if (attacker->actionInflictedDamage > 0 && condition) {
				Audio_PlaySoundInterrupt(SND_flower);
				target->hp = 0;
				Fighter_CheckDefeat(target, DAMAGE_FLAG_LETHAL);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__80(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer == 1) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			attacker->attackTimer = -1;
		}
	}
	
	if (attacker->readyTimer >= 0) {
		if (attacker->actionVars[0].i == 0) {
			if (attacker->readyTimer >= 84) return 1;
			
			if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
			
			if (attacker->readyTimer >= 4 && attacker->actionAttacks < 16 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= 40)) {
				Fighter_OnAttackSwing(attacker);
				attacker->readyTimer = 0;
				
				if (attacker->actionAttacks % 2 == 0)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else
					attacker->state = FIGHTER_STATE_ATTACK1;
				
				Audio_PlaySound(SND_birchswing2);
				
				Battle_CreateSpark(11, attacker->x + 12 * attacker->facing, attacker->y - 24, 0);
				int sparkId = battle.sparkCounter - 1;
				if (sparkId < 0) sparkId += OBJECT_COUNT_MAX;
				switch (attacker->totalAttackTimer / 2 % 4) {
					case 1:
						battle.sparks[sparkId].xVel = 7 * attacker->facing;
						battle.sparks[sparkId].yVel = -7;
						break;
					case 3:
						battle.sparks[sparkId].xVel = 7 * attacker->facing;
						battle.sparks[sparkId].yVel = 7;
						break;
					default:
						battle.sparks[sparkId].xVel = cos(PointDirection(battle.sparks[sparkId].x, battle.sparks[sparkId].y, target->x, target->y - 24)) * 10;
						battle.sparks[sparkId].yVel = sin(PointDirection(battle.sparks[sparkId].x, battle.sparks[sparkId].y, target->x, target->y - 24)) * 10;
						break;
				}
				attacker->actionAttacks++;
			}
		}
		else if (attacker->actionVars[0].i == 1) {
			if (attacker->readyTimer >= 104 && !attacker->moveTarget.enabled) return 1;
			
			if (attacker->actionAttacks == 0) {
				if (attacker->readyTimer == 1) {
					Fighter_MoveTo(attacker, 320 - 256 * attacker->facing, target->y, 32, 0);
				}
				if (attacker->readyTimer == 2 && attacker->moveTarget.enabled) {
					attacker->readyTimer--;
				}
			}
			
			if (attacker->readyTimer == 103) {
				Fighter_MoveToStart(attacker);
				attacker->state = FIGHTER_STATE_RUN;
				Fighter_GainStatus(attacker, FIGHTER_STATUS_HASTE, 20, false);
			}
			
			if (attacker->readyTimer >= 6 + 10 * (attacker->actionAttacks % 3 == 0) && attacker->actionAttacks < 24 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= 60 || attacker->actionAttacks % 3 != 0)) {
				Fighter_OnAttackSwing(attacker);
				attacker->readyTimer = 0;
				
				if (attacker->actionAttacks % 2 == 0)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else
					attacker->state = FIGHTER_STATE_ATTACK1;
				
				Audio_PlaySound(SND_birchswing2);
				
				Battle_CreateSpark(11, attacker->x + 12 * attacker->facing, attacker->y - 24, 0);
				int sparkId = battle.sparkCounter - 1;
				if (sparkId < 0) sparkId += OBJECT_COUNT_MAX;
				
				if (attacker->actionAttacks % 3 == 0) {
					attacker->actionVars[1].i = Random_IRange(0, 2);
				}
				float angle = 0;
				if (attacker->actionVars[1].i == attacker->actionAttacks % 3) {
					angle = PointDirection(battle.sparks[sparkId].x, battle.sparks[sparkId].y, target->x - 23 * attacker->facing, target->y - 24 + Random_IRange(-20, 20));
				}
				else {
					if (Random(1) < 0.5)
						angle = PointDirection(battle.sparks[sparkId].x, battle.sparks[sparkId].y, target->x - 23 * attacker->facing, target->y + 2 + Random_IRange(0, 40));
					else
						angle = PointDirection(battle.sparks[sparkId].x, battle.sparks[sparkId].y, target->x - 23 * attacker->facing, target->y - 50 - Random_IRange(0, 40));
				}
				battle.sparks[sparkId].xVel = cos(angle) * 12;
				battle.sparks[sparkId].yVel = sin(angle) * 12;
				attacker->actionAttacks++;
			}
		}
		else if (attacker->actionVars[0].i == 2) {
			if (attacker->readyTimer >= 64) return 1;
			
			if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
			
			if (attacker->actionAttacks < 16) {
				if (attacker->readyTimer == 4 + (attacker->actionAttacks % 4 == 0) * 36) {
					Audio_PlaySound(SND_birchteleport);
					Battle_CreateSpark(12, attacker->x, attacker->y - 24, 0);
					if (attacker->actionAttacks >= 15) {
						attacker->x = attacker->xStart;
						attacker->y = attacker->yStart;
						attacker->facing = -target->facing;
						
						if (attacker->speedRoll - target->speedRoll >= 20 && actionData[target->actionId].targetType == TARGETTYPE_ENEMY && target->targetId == attacker->id) {
							target->actionId = 0;
							Audio_PlaySound(SND_closeskill);
						}
					}
					else if (target->x >= 484 || (target->x >= 160 && Random(1) < 0.5)) {
						attacker->x = Random_IRange(64, target->x - 96);
						attacker->y = Random_IRange(192, 352);
						attacker->facing = FACING_RIGHT;
					}
					else {
						attacker->x = Random_IRange(target->x + 96, 516);
						attacker->y = Random_IRange(192, 352);
						attacker->facing = FACING_LEFT;
					}
					attacker->state = FIGHTER_STATE_IDLE;
					Battle_CreateSpark(12, attacker->x, attacker->y - 24, 0);
				}
				
				if (attacker->readyTimer >= 12 + (attacker->actionAttacks % 4 == 0) * 36) {
					Fighter_OnAttackSwing(attacker);
					if (attacker->actionAttacks < 15) {
						attacker->readyTimer = 0;
					}
					
					if (attacker->actionAttacks % 2 == 0)
						attacker->state = FIGHTER_STATE_ATTACK3;
					else
						attacker->state = FIGHTER_STATE_ATTACK1;
					
					Audio_PlaySound(SND_birchswing2);
					
					Battle_CreateSpark(11, attacker->x + 12 * attacker->facing, attacker->y - 24, 0);
					int sparkId = battle.sparkCounter - 1;
					if (sparkId < 0) sparkId += OBJECT_COUNT_MAX;
					
					float velocity = PointDistance(battle.sparks[sparkId].x, battle.sparks[sparkId].y, target->x, target->y - 24) / 14;
					float angle = PointDirection(battle.sparks[sparkId].x, battle.sparks[sparkId].y, target->x, target->y - 24);
					battle.sparks[sparkId].xVel = cos(angle) * velocity;
					battle.sparks[sparkId].yVel = sin(angle) * velocity;
					
					attacker->actionAttacks++;
				}
			}
		}
		else if (attacker->actionVars[0].i == 3) {
			if (attacker->readyTimer >= 174) return 1;
			
			if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
			
			if (attacker->actionAttacks == 0 && attacker->readyTimer == 2) {
				attacker->tempVars[0].i = battle.backgroundId;
				battle.backgroundId = -1;
				Audio_PlaySound(SND_birchteleport);
				for (int i = 0; i < 16; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled) continue;
					
					fighter->y -= 65536;
				}
				attacker->x = (attacker->side == 0) ? 224 : SCREEN_WIDTH - 224;
				attacker->y = SCREEN_HEIGHT / 2 + 48;
				target->x = (attacker->side == 1) ? 224 : SCREEN_WIDTH - 224;
				target->y = SCREEN_HEIGHT / 2 + 48;
			}
			
			if (attacker->readyTimer >= 4 + (attacker->actionAttacks == 0) * 50 - (attacker->actionAttacks >= 32) - (attacker->actionAttacks >= 96) && attacker->actionAttacks < 176) {
				Fighter_OnAttackSwing(attacker);
				attacker->readyTimer = 0;
				
				if (attacker->actionAttacks % 2 == 0)
					attacker->state = FIGHTER_STATE_SPECIAL2;
				else
					attacker->state = FIGHTER_STATE_SPECIAL1;
				
				Audio_PlaySound(SND_birchswing2);
				
				Battle_CreateSpark(11, attacker->x + 12 * attacker->facing, attacker->y - 24, 0);
				int sparkId = battle.sparkCounter - 1;
				if (sparkId < 0) sparkId += OBJECT_COUNT_MAX;
				
				float angle = ((float)attacker->actionAttacks + 6.5) * PI / 12;
				battle.sparks[sparkId].xVel = -cos(angle) * 10 * attacker->facing;
				battle.sparks[sparkId].yVel = -sin(angle) * 10;
				attacker->actionAttacks++;
			}
			
			if (attacker->readyTimer == 163) {
				for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
					if (battle.sparks[i].id == 11) {
						battle.sparks[i].id = 0;
						Battle_CreateSpark(12, battle.sparks[i].x, battle.sparks[i].y, 0);
					}
				}
				battle.backgroundId = attacker->tempVars[0].i;
				Audio_PlaySound(SND_birchteleport);
				for (int i = 0; i < 16; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled) continue;
					
					fighter->y += 65536;
				}
				attacker->x = attacker->xStart;
				attacker->y = attacker->yStart;
				target->x = target->xStart;
				target->y = target->yStart;
			}
		}
	}
	
	return 0;
}



int Action_Update__81(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			if (attacker->actionAttacks >= 16) {
				attacker->attackTimer += 2;
				attacker->attackAnimTimer = attacker->attackAnimTime;
			}
			else {
				attacker->attackTimer--;
				if (attacker->actionAttacks >= 8) attacker->attackAnimTimer += 2;
			}
			attacker->state = FIGHTER_STATE_IDLE;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 31 && attacker->actionInflictedDamage > 0 && !target->status[FIGHTER_STATUS_DEFLECT]) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
		
		if (attacker->attackTimer == 43) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 24 - attacker->actionAttacks * 3)) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_RUN;
			
			Audio_PlaySound(SND_swing);
			if (attacker->actionAttacks >= 1) attacker->facing = -attacker->facing;
			Fighter_MoveTo(attacker, target->x + attacker->facing * 64, target->y, 32 + 32 * (attacker->actionAttacks >= 8), 0);
		}
	}
	
	return 0;
}



int Action_Update__82(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 343 && !attacker->moveTarget.enabled && !target->moveTarget.enabled) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackAnimTimer++;
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionInflictedDamage < attacker->actionVars[2].i) {
				attacker->attackTimer = 327;
				Fighter_MoveToStart(attacker);
				attacker->state = FIGHTER_STATE_RUN;
			}
			Battle_ShakeScreen(12);
		}
		
		if (attacker->attackTimer == 35) {
			target->flinchTicks = 0;
			attacker->state = FIGHTER_STATE_SPECIAL1;
			target->state = FIGHTER_STATE_HURT;
			target->x = attacker->x + attacker->facing * 42;
			target->y = attacker->y - 44;
		}
		if (attacker->attackTimer == 103) {
			Audio_PlaySound(SND_crusherhit2);
			Battle_ShakeScreen(12);
			Fighter_MoveTo(target, attacker->x + attacker->facing * 34, attacker->y - 10, 0.25, 0);
			Battle_CreateSpark(3, target->x, target->y - 30, 0);
		}
		if (attacker->attackTimer == 265) {
			Audio_PlaySound(SND_thunder);
			Audio_PlaySound(SND_gunfire2);
			Audio_PlaySound(SND_birchhit2);
			target->x = target->xStart;
			target->y = target->yStart;
			attacker->state = FIGHTER_STATE_ATTACK1;
			Battle_ShakeScreen(60);
		}
		if (attacker->attackTimer > 265 && attacker->attackTimer < 289 && attacker->attackTimer % 4 == 0) {
			Battle_ShakeScreen(60);
			Audio_PlaySound(SND_birchhit2);
		}
		
		if (attacker->attackTimer == 289) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_LETHAL);
			
			attacker->actionAttacks++;
			
			Fighter_MoveTo(target, 608 - attacker->side * 576, target->y, 58, 0);
		}
		
		if (attacker->attackTimer == 290 && target->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 291) {
			Audio_PlaySound(SND_birchhit1);
		}
		
		if (attacker->attackTimer == 342) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
			if (target->alive) {
				Fighter_MoveToStart(target);
				target->state = FIGHTER_STATE_RUN;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, target->x - attacker->facing * 56, target->y, 12, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		if (!attacker->moveTarget.enabled) {
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
		
		if ((Action_AttackUpdate(attacker, target) && !attacker->moveTarget.enabled && attacker->readyTimer > 1) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__82(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	
	if (attacker->attackTimer < 35) {
		
	}
	else if (attacker->attackTimer < 265) {
		DrawFighterChar(target->headId, target->bodyId, target->state, target->x, target->y, 2, 2, target->facing);
	}
	else if (attacker->attackTimer < 289) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 72, 2, 8 * target->facing, 8);
	}
	else if (attacker->attackTimer < 294) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 72, 3, 8 * target->facing, 8);
	}
	else if (attacker->attackTimer < 299) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 72, 4, 8 * target->facing, 8);
	}
	else if (attacker->attackTimer < 304) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 72, 5, 8 * target->facing, 8);
	}
}



int Action_Update__83(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer <= 240) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			if (attacker->readyTimer >= 400) {
				damage += 50;
				
				for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled || !fighter->alive) continue;
					
					int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
					
					Fighter_DealDamage(attacker, fighter, damageLocal, 0);
				}
			}
			else {
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE);
				
				if (attacker->actionAttacks == 31) {
					Battle_ShakeScreen(30);
					Audio_PlaySound(SND_firemassattack);
				}
				else {
					Battle_ShakeScreen(8);
					Audio_PlaySound(SND_birchhit2);
				}
				
				target->moveTarget.enabled = false;
			}
		}
		if (attacker->attackTimer == 20) {
			attacker->attackTimer = -1;
		}
	}
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer >= 521 && !attacker->moveTarget.enabled) return 1;
		
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
		
		if (attacker->readyTimer == 10) {
			SDL_Delay(500);
			Audio_PlaySound(SND_ultimateskill);
			attacker->state = FIGHTER_STATE_RUN;
			
			attacker->x = (attacker->side == 0) ? 224 : SCREEN_WIDTH - 224;
			attacker->y = SCREEN_HEIGHT / 2 + 48;
			target->x = (attacker->side == 1) ? 224 : SCREEN_WIDTH - 224;
			target->y = SCREEN_HEIGHT / 2 + 48;
			
			Battle_Camera_MoveTo(attacker->x - 120 * attacker->facing, attacker->y - 24, 6, 256);
		}
		
		if (attacker->readyTimer == 11) {
			Battle_Camera_MoveTo(attacker->x, attacker->y - 24, 6, 8);
		}
		
		if (attacker->readyTimer == 61) {
			Battle_Camera_MoveTo(target->x + 60 * target->facing, target->y - 24, 6, 2);
		}
		if (attacker->readyTimer == 62 && battle.camera.moveTarget.enabled) attacker->readyTimer--;
		if (attacker->readyTimer == 63) {
			Battle_Camera_MoveTo(target->x + 24 * target->facing, target->y - 24, 3, 1);
		}
		if (attacker->readyTimer == 101) {
			Fighter_MoveTo(attacker, target->x + 62 * target->facing, target->y, 16, 0);
		}
		if (attacker->readyTimer == 102 && attacker->moveTarget.enabled) attacker->readyTimer--;
		
		if (attacker->readyTimer == 106) {
			Fighter_OnAttackSwing(attacker);
			attacker->attackTimer = 0;
			
			if (attacker->actionAttacks >= 30)
				attacker->state = FIGHTER_STATE_SPECIAL3;
			else if (attacker->actionAttacks >= 24) {
				if (attacker->actionAttacks == 24) {
					attacker->x += 12 * attacker->facing;
				}
				attacker->state = FIGHTER_STATE_SPECIAL2;
				attacker->x += 2 * attacker->facing;
				attacker->y -= 4;
				target->x += 2 * attacker->facing;
				target->y -= 4;
			}
			else if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
			Audio_PlaySound(SND_birchswing2);
			
			attacker->actionAttacks++;
		}
		if (attacker->readyTimer == 124 - attacker->actionAttacks / 3 && attacker->actionAttacks < 31) {
			attacker->readyTimer = 105;
		}
		
		if (attacker->actionAttacks >= 31) {
			if (attacker->readyTimer == 146) {
				Fighter_MoveTo(target, target->x, target->y - 128, 16, 0);
				target->state = FIGHTER_STATE_HURT;
			}
			if (attacker->readyTimer == 176) {
				attacker->facing = -attacker->facing;
				attacker->state = FIGHTER_STATE_SPECIAL4;
			}
			/*if (attacker->readyTimer >= 178 && attacker->readyTimer <= 206) {
				attacker->y += (attacker->readyTimer - 178) / 10;
			}
			if (attacker->readyTimer == 206) {
				attacker->facing = -attacker->facing;
				attacker->state = FIGHTER_STATE_IDLE;
			}*/
			if (attacker->readyTimer == 198) {
				Fighter_MoveTo(target, target->x + 2, target->y + 126, 8, 0);
				target->state = FIGHTER_STATE_HURT;
			}
			if (attacker->readyTimer == 218) {
				attacker->facing = -attacker->facing;
				attacker->state = FIGHTER_STATE_ATTACK2;
				Audio_PlaySound(SND_birchswing1);
			}
			if (attacker->readyTimer >= 228 && attacker->readyTimer < 386) {
				attacker->y += 0.25;
				target->y += 0.25;
				Battle_ShakeScreen(2 + (attacker->readyTimer - 228) / 25);
			}
			if (attacker->readyTimer == 386) {
				Battle_Camera_MoveToStart(256);
			}
			if (attacker->readyTimer == 396 || attacker->readyTimer == 404 || attacker->readyTimer == 412) {
				Audio_PlaySound(SND_firemassattack);
				Audio_PlaySound(SND_thunder);
				Audio_PlaySound(SND_thunder);
			}
			if (attacker->readyTimer == 404) {
				attacker->state = FIGHTER_STATE_ATTACK1;
				attacker->attackTimer = 0;
				Battle_ShakeScreen(130);
				target->x = target->xStart;
				target->y = target->yStart;
				attacker->y = target->y;
				Battle_CreateSpark(7, target->x, target->y, 0);
			}
		}
		
		if (attacker->readyTimer == 520) {
			Fighter_MoveToStart(attacker);
			attacker->state = FIGHTER_STATE_RUN;
		}
	}
	
	return 0;
}
void Action_Draw__83(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer < 10) {
		
	}
	else if (attacker->readyTimer < 386) {
		Drawer_SetProjection(160, 120, 2);
		Drawer_SetDrawColor(127, 0, 127);
		Drawer_FillRect(0, 0, 320, 240);
		
		for (int x = 0; x < 320; x++) {
			Drawer_SetDrawColor(63, 0, 63);
			Drawer_FillRect(x, 120 - 90 + Random_IRange(-4, 4), 1, 180);
			Drawer_SetDrawColor(0, 0, 0);
			Drawer_FillRect(x, 120 - 70 + Random_IRange(-4, 4), 1, 140);
		}
		
		if (battle.shakeTimer == 0)
			Drawer_SetProjection(battle.camera.x, battle.camera.y, battle.camera.zoom);
		else
			Drawer_SetProjection(battle.camera.x + Random_Range(-battle.shakeTimer, battle.shakeTimer), battle.camera.y + Random_Range(-battle.shakeTimer, battle.shakeTimer), battle.camera.zoom);
		
		Drawer_SetDrawColor(255, 255, 255);
		
		DrawFighterChar(target->headId, target->bodyId, target->state, target->x, target->y, 2, 2, target->facing);
		DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, attacker->x, attacker->y, 2, 2, attacker->facing);
		
		if (attacker->attackTimer >= 0 && attacker->attackTimer < 20 && attacker->actionAttacks < 24) {
			Drawer_DrawSprite(SPR_spark_slashcorycombo, attacker->x, attacker->y - 48 * (attacker->state == FIGHTER_STATE_ATTACK1), attacker->attackTimer / 10, 2 * attacker->facing, 2 - 4 * (attacker->state == FIGHTER_STATE_ATTACK1));
		}
		if (attacker->readyTimer >= 106 && attacker->actionAttacks == 31) {
			if (attacker->readyTimer < 156) {
				Drawer_DrawSprite(SPR_spark_slashcorycombo, attacker->x, attacker->y, 0, 2 * attacker->facing, 2);
			}
			else if (attacker->readyTimer < 176) {
				Drawer_DrawSprite(SPR_spark_slashcorycombo, attacker->x, attacker->y, 1, 2 * attacker->facing, 2);
			}
		}
		
		
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(127, 127, 127);
		for (int x = -64; x < 640; x += 128) {
			for (int y = -64; y < 480; y += 128) {
				if (attacker->readyTimer >= 218) {
					Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_9, x, y - battle.globalTimer * 4 % 128, 0, 2, 2, 90);
					Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_9, x + 64, y - battle.globalTimer * 8 % 128, 0, 2, 2, 90);
				}
				else if (attacker->readyTimer >= 146) {
					Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_9, x, y + battle.globalTimer * 4 % 128, 0, 2, 2, 90);
					Drawer_DrawSprite_Angle(SPR_misc_bossbattlebg_9, x + 64, y + battle.globalTimer * 8 % 128, 0, 2, 2, 90);
				}
				else {
					Drawer_DrawSprite(SPR_misc_bossbattlebg_9, x - (battle.globalTimer * 4 % 128) * attacker->facing, y, 0, 2, 2);
					Drawer_DrawSprite(SPR_misc_bossbattlebg_9, x - (battle.globalTimer * 8 % 128) * attacker->facing, y + 64, 0, 2, 2);
				}
			}
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->readyTimer < 404) {
		Drawer_FillRect(-32, -32, SCREEN_WIDTH + 64, SCREEN_HEIGHT + 64);
	}
}



int Action_Update__84(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			
			Fighter_GainStatus(attacker, FIGHTER_STATUS_STRENGTH, 50, false);
			Fighter_GainStatus(attacker, FIGHTER_STATUS_HASTE, 50, false);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__85(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1) {
			if (attacker->actionAttacks >= 11) {
				attacker->x = attacker->xStart;
				attacker->y = attacker->yStart;
				attacker->facing = (attacker->x < SCREEN_WIDTH / 2) ? FACING_RIGHT : FACING_LEFT;
			}
			else {
				switch (Random_IRange(0, 1)) {
					case 0:
						attacker->facing = FACING_RIGHT;
						attacker->x = target->x - Random_IRange(32, 88);
						break;
					case 1:
						attacker->facing = FACING_LEFT;
						attacker->x = target->x + Random_IRange(32, 88);
						break;
				}
				attacker->y = target->y + Random_IRange(-40, 8);
			}
		}
		if (attacker->attackTimer == 4) {
			Audio_PlaySound(SND_crusherhit);
			int damage = attacker->speedRoll * attacker->actionAttackMultiplier / 12 + attacker->actionPower[0];
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 11) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX || attacker->actionAttacks > 0) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 2 == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
			Audio_PlaySound(SND_beamsword);
		}
	}
	
	return 0;
}
void Action_Draw__85(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	if (attacker->attackTimer >= 0 && attacker->attackTimer < 3) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer >= 3 && attacker->attackTimer < 4){
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
		
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
		
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 3, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
}



int Action_Update__86(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			Fighter_DealDamage(attacker, target, damage, 0);
			
			target->mp -= attacker->actionVars[2].i;
			if (target->mp < 0) target->mp = 0;
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__87(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_GainStatus(attacker, FIGHTER_STATUS_GUARD, 46, false);
			Fighter_GainStatus(attacker, FIGHTER_STATUS_COUNTER, 93, false);
			
			attacker->state = FIGHTER_STATE_BLOCK;
			
			for (int i = (1 - attacker->side) * 8; i < (1 - attacker->side) * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
			}
		}
	}
	
	return 0;
}



int Action_Update__88(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_HealHP(attacker, attacker->actionVars[0].i);
			Fighter_GainStatus(attacker, FIGHTER_STATUS_MANADISCOUNT, attacker->actionVars[1].i, false);
			Fighter_GainStatus(attacker, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
		}
	}
	
	return 0;
}



int Action_Update__89(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_InflictStatus(attacker, fighter, attacker->actionVars[2].i, attacker->actionVars[3].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_LETHAL);
				
				fighter->mp -= 100;
				if (fighter->mp < 0) fighter->mp = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (attacker->readyTimer >= 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__90(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			if (attacker->readyTimer >= 1587) {
				damage += 2600;
				for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled) continue;
					
					int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
					
					Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_BLEED, 4, false);
					Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_PARALYSIS, 284, false);
					Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_IMMOBILE, 1, false);
					Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_ANTIGUARD, 1, false);
					Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_LETHAL);
					fighter->flinchTicks *= 4;
				}
			}
			else {
				for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
					Fighter* fighter = &battle.fighters[i];
					if (!fighter->enabled) continue;
					
					int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
					
					int mtEnabled = fighter->moveTarget.enabled;
					int mtX = fighter->moveTarget.x;
					int mtY = fighter->moveTarget.y;
					int mtSpeed = fighter->moveTarget.speed;
					
					Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_BLEED, 4, false);
					Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_LETHAL);
					fighter->flinchTicks = 0;
					
					fighter->moveTarget.enabled = mtEnabled;
					fighter->moveTarget.x = mtX;
					fighter->moveTarget.y = mtY;
					fighter->moveTarget.speed = mtSpeed;
				}
			}
		}
		if (attacker->attackTimer == 10) {
			attacker->attackTimer = -1;
		}
	}
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer >= 1831) return 1;
		
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
		
		if (attacker->readyTimer == 10) {
			Audio_PlaySound(SND_ultimateskill);
			Audio_PlaySound(SND_firemassattack);
			attacker->state = FIGHTER_STATE_ATTACK3;
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
		}
		
		if (attacker->readyTimer == 14) {
			Battle_ShakeScreen(16);
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled) continue;
				
				Battle_CreateSpark(14, fighter->x, fighter->y - 24, 0);
				Fighter_MoveTo(fighter, fighter->x + 320 * attacker->facing, fighter->y, 32, 0);
			}
		}
		
		if (attacker->readyTimer == 61) {
			Fighter_MoveTo(attacker, attacker->x + 600 * attacker->facing, attacker->y, 32, 0);
			attacker->state = FIGHTER_STATE_RUN;
		}
		
		if (attacker->readyTimer == 75) {
			attacker->moveTarget.enabled = false;
			attacker->x = SCREEN_WIDTH / 2 - 400 * attacker->facing;
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled) continue;
				
				fighter->x = fighter->xStart;
				fighter->y = fighter->yStart;
				fighter->state = FIGHTER_STATE_HURT;
			}
			battle.camera.x = SCREEN_WIDTH / 2 + 64 * attacker->facing;
			battle.camera.y = SCREEN_HEIGHT / 2;
			battle.camera.zoom = 2;
		}
		
		if (attacker->readyTimer == 93) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, battle.fighters[target->side * 8].x - 48 * attacker->facing, battle.fighters[target->side * 8].y, 24, 0);
			Battle_Camera_MoveTo(SCREEN_WIDTH / 2 + 128 * attacker->facing, SCREEN_HEIGHT / 2, 2, 8);
		}
		if (attacker->readyTimer == 94 && attacker->moveTarget.enabled) attacker->readyTimer--;
		if (attacker->readyTimer == 96) {
			Audio_PlaySound(SND_hit3);
			attacker->state = FIGHTER_STATE_ATTACK2;
			Battle_CreateSpark(14, battle.fighters[target->side * 8].x, battle.fighters[target->side * 8].y - 24, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8], SCREEN_WIDTH - 168 - 2 * attacker->facing, SCREEN_HEIGHT / 2 - 8, 18, 0);
		}
		if (attacker->readyTimer == 108) {
			Audio_PlaySound(SND_hit3);
			attacker->state = FIGHTER_STATE_ATTACK3;
			attacker->facing = -attacker->facing;
			attacker->x = SCREEN_WIDTH - 168 - 48 * attacker->facing;
			attacker->y = SCREEN_HEIGHT / 2 - 8;
			Battle_CreateSpark(14, battle.fighters[target->side * 8].x, battle.fighters[target->side * 8].y - 24, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8], SCREEN_WIDTH - 128 - 4 * attacker->facing, SCREEN_HEIGHT / 2 + 104, 18, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 1], SCREEN_WIDTH - 128 - 2 * attacker->facing, SCREEN_HEIGHT / 2 + 104, 18, 0);
		}
		if (attacker->readyTimer == 120) {
			Audio_PlaySound(SND_hit3);
			attacker->state = FIGHTER_STATE_ATTACK2;
			attacker->facing = -attacker->facing;
			attacker->x = SCREEN_WIDTH - 128 - 48 * attacker->facing;
			attacker->y = SCREEN_HEIGHT / 2 + 104;
			Battle_CreateSpark(14, battle.fighters[target->side * 8].x, battle.fighters[target->side * 8].y - 24, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8], SCREEN_WIDTH - 72 - 6 * attacker->facing, SCREEN_HEIGHT / 2 + 48, 18, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 1], SCREEN_WIDTH - 72 - 4 * attacker->facing, SCREEN_HEIGHT / 2 + 48, 18, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 2], SCREEN_WIDTH - 72 - 2 * attacker->facing, SCREEN_HEIGHT / 2 + 48, 18, 0);
		}
		if (attacker->readyTimer == 132) {
			Audio_PlaySound(SND_hit3);
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->facing = -attacker->facing;
			attacker->x = SCREEN_WIDTH - 72 - 48 * attacker->facing;
			attacker->y = SCREEN_HEIGHT / 2 + 48;
			Battle_CreateSpark(14, battle.fighters[target->side * 8].x, battle.fighters[target->side * 8].y - 24, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8], SCREEN_WIDTH / 2 - 6 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 18, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 1], SCREEN_WIDTH / 2 - 4 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 18, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 2], SCREEN_WIDTH / 2 - 2 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 18, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 3], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 8, 18, 0);
			
			Battle_Camera_MoveTo(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 8);
		}
		
		if (attacker->readyTimer == 150) {
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->facing = -attacker->facing;
			attacker->x = SCREEN_WIDTH / 2 - 48 * attacker->facing;
			attacker->y = SCREEN_HEIGHT / 2 + 8;
		}
		
		if (attacker->readyTimer == 156) {
			Audio_PlaySound(SND_explode);
			Audio_PlaySound(SND_beamsword);
			
			if (attacker->actionAttacks >= 14) {
				attacker->state = (attacker->actionAttacks % 2 == 0) ? FIGHTER_STATE_ATTACK3 : FIGHTER_STATE_ATTACK2;
				Battle_CreateSpark(16, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, 0);
			}
			else {
				attacker->state = (attacker->actionAttacks % 2 == 0) ? FIGHTER_STATE_BLOCK : FIGHTER_STATE_ATTACK1;
				Battle_CreateSpark(14, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, 0);
			}
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
			Battle_ShakeScreen(20);
		}
		if (attacker->readyTimer == 161 && attacker->actionAttacks < 38) {
			attacker->readyTimer = 155;
		}
		
		if (attacker->readyTimer == 162) {
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->x = SCREEN_WIDTH / 2;
			attacker->y = SCREEN_HEIGHT / 2 + 8;
			Audio_PlaySound(SND_thunder);
			Audio_PlaySound(SND_beamsword);
			
			Battle_CreateSpark(16, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, 0);
			
			battle.fighters[target->side * 8].facing = -attacker->facing;
			battle.fighters[target->side * 8 + 1].facing = -attacker->facing;
			battle.fighters[target->side * 8 + 2].facing = attacker->facing;
			battle.fighters[target->side * 8 + 3].facing = attacker->facing;
			Fighter_MoveTo(&battle.fighters[target->side * 8], SCREEN_WIDTH / 2 + 140 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 16, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 1], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 72, 16, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 2], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 88, 16, 0);
			Fighter_MoveTo(&battle.fighters[target->side * 8 + 3], SCREEN_WIDTH / 2 - 140 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 16, 0);
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
			Battle_ShakeScreen(20);
		}
		
		if (attacker->readyTimer == 175) {
			Audio_PlaySound(SND_explode);
			Audio_PlaySound(SND_beamsword);
			
			attacker->state = (attacker->actionAttacks % 2 == 0) ? FIGHTER_STATE_ATTACK3 : FIGHTER_STATE_ATTACK2;
			if (attacker->actionAttacks % 2 == 0) {
				Fighter_MoveTo(&battle.fighters[target->side * 8], SCREEN_WIDTH / 2 - 88 * attacker->facing, SCREEN_HEIGHT / 2 - 40, 256, 0);
				Fighter_MoveTo(&battle.fighters[target->side * 8 + 1], SCREEN_WIDTH / 2 - 88 * attacker->facing, SCREEN_HEIGHT / 2 + 56, 256, 0);
				Fighter_MoveTo(&battle.fighters[target->side * 8 + 2], SCREEN_WIDTH / 2 + 88 * attacker->facing, SCREEN_HEIGHT / 2 - 40, 256, 0);
				Fighter_MoveTo(&battle.fighters[target->side * 8 + 3], SCREEN_WIDTH / 2 + 88 * attacker->facing, SCREEN_HEIGHT / 2 + 56, 256, 0);
			}
			else {
				Fighter_MoveTo(&battle.fighters[target->side * 8], SCREEN_WIDTH / 2 + 140 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 256, 0);
				Fighter_MoveTo(&battle.fighters[target->side * 8 + 1], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 72, 256, 0);
				Fighter_MoveTo(&battle.fighters[target->side * 8 + 2], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 88, 256, 0);
				Fighter_MoveTo(&battle.fighters[target->side * 8 + 3], SCREEN_WIDTH / 2 - 140 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 256, 0);
			}
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
			Battle_ShakeScreen(20);
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled) continue;
				
				Battle_CreateSpark(16, fighter->x, fighter->y - 24, 0);
			}
		}
		if (attacker->readyTimer == 181 && attacker->actionAttacks < 72) {
			attacker->readyTimer = 174;
		}
		
		if (attacker->readyTimer == 182) {
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->x = SCREEN_WIDTH / 2;
			attacker->y = SCREEN_HEIGHT / 2 + 8;
		}
		
		if (attacker->readyTimer == 184) {
			Audio_PlaySound(SND_thunder);
			Audio_PlaySound(SND_electric);
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
			Battle_ShakeScreen(24);
		}
		if (attacker->readyTimer >= 184 && attacker->readyTimer <= 189) {
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled) continue;
				
				Fighter_MoveTo(fighter, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(64, SCREEN_HEIGHT - 64), 80, 0);
			}
			for (int i = 0; i < 16; i++) {
				if (i % 2 == 0)
					Battle_CreateSpark(16, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(64, SCREEN_HEIGHT - 64), 0);
				else
					Battle_CreateSpark(14, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(64, SCREEN_HEIGHT - 64), 0);
			}
		}
		if (attacker->readyTimer == 189 && attacker->actionAttacks < 79) {
			attacker->readyTimer = 183;
		}
		
		if (attacker->readyTimer == 190) {
			Audio_PlaySound(SND_firemassattack);
			Battle_ShakeScreen(16);
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled) continue;
				
				Battle_CreateSpark(16, fighter->x, fighter->y - 24, 0);
				Fighter_MoveTo(fighter, fighter->x, fighter->y + 640, 49, 0);
			}
		}
		
		if (attacker->readyTimer == 208) {
			Battle_Camera_MoveToStart(256);
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->x = attacker->xStart;
			attacker->y = attacker->yStart;
			
			Audio_PlaySound(SND_explode);
			Battle_ShakeScreen(52);
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled) continue;
				
				fighter->x = fighter->xStart;
				fighter->y = fighter->yStart;
				fighter->state = FIGHTER_STATE_DOWN;
			}
		}
		
		if (attacker->readyTimer >= 264 && attacker->readyTimer <= 1164) {
			if (attacker->readyTimer % 48 == 0) {
				Audio_PlaySound(SND_charge);
			}
			if (attacker->readyTimer % 128 == 32 && attacker->readyTimer < 924) {
				Audio_PlaySound(SND_introwakeup);
			}
			Battle_ShakeScreen(1 + (attacker->readyTimer - 264) / 16);
		}
		if (attacker->readyTimer == 1230) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			Audio_PlaySound(SND_swing);
			Audio_PlaySound(SND_shards);
		}
		
		if (attacker->readyTimer >= 1527 && attacker->readyTimer <= 1587 && attacker->readyTimer % 10 == 7) {
			Audio_PlaySound(SND_firemassattack);
		}
		if (attacker->readyTimer == 1587) {
			Audio_PlaySound(SND_explode);
			Audio_PlaySound(SND_thunder);
			Audio_PlaySound(SND_gunfire2);
			Audio_PlaySound(SND_subspace_transform);
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
			Battle_ShakeScreen(199);
		}
	}
	
	return 0;
}
void Action_Draw__90(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer < 10) {
		
	}
	else if (attacker->readyTimer < 12) {
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_SetDrawAlpha(63);
		Drawer_FillRect(-64, -64, SCREEN_WIDTH + 128, SCREEN_HEIGHT + 128);
		Drawer_SetDrawAlpha(255);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->readyTimer < 75) {
		
	}
	else if (attacker->readyTimer < 208) {
		Drawer_SetProjection(160, 120, 2);
		Drawer_SetDrawColor(191, 0, 0);
		Drawer_FillRect(0, 0, 320, 240);
		
		for (int x = 0; x < 320; x++) {
			Drawer_SetDrawColor(95, 0, 0);
			Drawer_FillRect(x, 120 - 90 + Random_IRange(-4, 4), 1, 180);
			Drawer_SetDrawColor(0, 0, 0);
			Drawer_FillRect(x, 120 - 70 + Random_IRange(-4, 4), 1, 140);
		}
		
		if (battle.shakeTimer == 0)
			Drawer_SetProjection(battle.camera.x, battle.camera.y, battle.camera.zoom);
		else
			Drawer_SetProjection(battle.camera.x + Random_Range(-battle.shakeTimer, battle.shakeTimer), battle.camera.y + Random_Range(-battle.shakeTimer, battle.shakeTimer), battle.camera.zoom);
		
		Drawer_SetDrawColor(255, 255, 255);
		
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			DrawFighterChar(fighter->headId, fighter->bodyId, fighter->state, fighter->x, fighter->y, 2, 2, fighter->facing);
		}
		if (attacker->readyTimer >= 175 && attacker->readyTimer <= 181) {
			if (attacker->actionAttacks % 2 == 1) {
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 - 48 * attacker->facing, SCREEN_HEIGHT / 2 - 40, 2, 2, -attacker->facing);
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 - 48 * attacker->facing, SCREEN_HEIGHT / 2 + 56, 2, 2, -attacker->facing);
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 + 48 * attacker->facing, SCREEN_HEIGHT / 2 - 40, 2, 2, attacker->facing);
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 + 48 * attacker->facing, SCREEN_HEIGHT / 2 + 56, 2, 2, attacker->facing);
			}
			else {
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 + 100 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 2, 2, attacker->facing);
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 - 40 * attacker->facing, SCREEN_HEIGHT / 2 - 72, 2, 2, attacker->facing);
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 + 40 * attacker->facing, SCREEN_HEIGHT / 2 + 88, 2, 2, -attacker->facing);
				DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, SCREEN_WIDTH / 2 - 100 * attacker->facing, SCREEN_HEIGHT / 2 + 8, 2, 2, -attacker->facing);
			}
		}
		else {
			DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, attacker->x, attacker->y, 2, 2, attacker->facing);
		}
		
		
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(127, 127, 127);
		for (int x = -64; x < 640; x += 128) {
			for (int y = -64; y < 480; y += 128) {
				Drawer_DrawSprite(SPR_misc_bossbattlebg_9, x - (battle.globalTimer * 8 % 128) * attacker->facing, y, 0, 2, 2);
				Drawer_DrawSprite(SPR_misc_bossbattlebg_9, x - (battle.globalTimer * 16 % 128) * attacker->facing, y + 64, 0, 2, 2);
			}
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->readyTimer < 210) {
		Drawer_FillRect(-32, -32, SCREEN_WIDTH + 64, SCREEN_HEIGHT + 64);
	}
	else if (attacker->readyTimer < 265) {
		
	}
	else if (attacker->readyTimer < 1230) {
		Drawer_SetDrawColor(191, 0, 0);
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_DrawSprite(SPR_misc_dystal_final, attacker->x, attacker->y + 52, attacker->readyTimer % 6, 4, 4);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		Drawer_DrawSprite(SPR_misc_voidportal, attacker->x, attacker->y - 50, attacker->readyTimer / 2 % 3, (float)(attacker->readyTimer - 264) * 0.06, (float)(attacker->readyTimer - 264) * 0.06);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->readyTimer < 1523) {
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_DrawSprite(SPR_misc_voidportal, attacker->x + 204 * attacker->facing * (float)(attacker->readyTimer - 1230) / 293, attacker->y - 50 + 392 * (float)(attacker->readyTimer - 1230) / 293, attacker->readyTimer / 2 % 3, 965 * 0.06, 965 * 0.06);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->readyTimer < 1587) {
		Drawer_FillRect(-200, -200, SCREEN_WIDTH + 400, SCREEN_HEIGHT + 400);
	}
	else if (attacker->readyTimer < 1770) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(127, 0, 0);
		Drawer_FillRect(-200, -200, SCREEN_WIDTH + 400, SCREEN_HEIGHT + 400);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		if (attacker->readyTimer < 1647) {
			Drawer_SetDrawAlpha(255 - (attacker->readyTimer - 1587) * 255 / 60);
			Drawer_FillRect(-200, -200, SCREEN_WIDTH + 400, SCREEN_HEIGHT + 400);
			Drawer_SetDrawAlpha(255);
		}
	}
	else if (attacker->readyTimer < 1831) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(127 + (attacker->readyTimer - 1770) * 2, (attacker->readyTimer - 1770) * 4, (attacker->readyTimer - 1770) * 4);
		Drawer_FillRect(-200, -200, SCREEN_WIDTH + 400, SCREEN_HEIGHT + 400);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
}



int Action_Update__91(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_InflictStatusDodgable(attacker, fighter, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
			}
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 5) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__92(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, 0);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 23) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL1;
		
		if ((attacker->actionAttacks == 0 && (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX)) || (attacker->actionAttacks > 0 && attacker->readyTimer >= 1)) {
			if (attacker->actionAttacks == 0) Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks == 0) {
				Audio_PlaySound(SND_ultbeam);
			}
		}
	}
	
	return 0;
}



int Action_Update__93(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer == 2) {
			int damage = Action_GetDamagePower(attacker, target);
			
			if (attacker->readyTimer >= 778) {
				damage += 1800;
				
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				target->mp -= 999;
				if (target->mp < 0) target->mp = 0;
				target->status[FIGHTER_STATUS_CHARGE] = 0;
				Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_LETHAL);
				target->flinchTicks *= 4;
			}
			else {
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				int mtEnabled = target->moveTarget.enabled;
				int mtX = target->moveTarget.x;
				int mtY = target->moveTarget.y;
				int mtSpeed = target->moveTarget.speed;
				
				Fighter_InflictStatus(attacker, target, FIGHTER_STATUS_PARALYSIS, 3, false);
				Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_LETHAL);
				target->flinchTicks = 0;
				
				target->moveTarget.enabled = mtEnabled;
				target->moveTarget.x = mtX;
				target->moveTarget.y = mtY;
				target->moveTarget.speed = mtSpeed;
			}
		}
		if (attacker->attackTimer == 3) {
			attacker->attackTimer = -1;
		}
	}
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer >= 1022) return 1;
		
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK1;
		}
		
		if (attacker->readyTimer == 10) {
			Battle_CreateSpark(20, attacker->x, attacker->y - 40, 0);
			Audio_PlaySound(SND_ultimateskill);
			attacker->state = FIGHTER_STATE_BLOCK;
		}
		
		if (attacker->readyTimer == 75) {
			Fighter_MoveTo(attacker, target->x - attacker->facing * 32, target->y, 12, 0);
			attacker->state = FIGHTER_STATE_SPECIAL1;
		}
		if (attacker->readyTimer == 76 && attacker->moveTarget.enabled) attacker->readyTimer--;
		
		if (attacker->readyTimer == 86) {
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
		}
		if (attacker->readyTimer == 86 || attacker->readyTimer == 88) {
			Audio_PlaySound(SND_hit3);
			Audio_PlaySound(SND_beamsword);
			for (int i = 0; i < 2; i++) {
				Battle_CreateSpark(15 + i * 5, Random_Range(32, SCREEN_WIDTH - 32), Random_Range(32, SCREEN_HEIGHT - 32), 0);
			}
		}
		if (attacker->readyTimer == 88 && attacker->actionAttacks < 16) {
			attacker->readyTimer = 85;
		}
		
		if (attacker->readyTimer == 100) {
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
		}
		if (attacker->readyTimer == 100 || attacker->readyTimer == 101 || attacker->readyTimer == 102) {
			Audio_PlaySound(SND_hit3);
			Audio_PlaySound(SND_beamsword);
			for (int i = 0; i < 2; i++) {
				Battle_CreateSpark(20, SCREEN_WIDTH / 2 + 280 * cos((double)(attacker->totalAttackTimer * 2 + i) / 2.76), SCREEN_HEIGHT / 2 + 150 * cos((double)(attacker->attackTimer * 2 + i) / 3.7758), 0);
			}
		}
		if (attacker->readyTimer == 102 && attacker->actionAttacks < 29) {
			attacker->readyTimer = 99;
		}
		
		if (attacker->readyTimer == 115) {
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
		}
		if (attacker->readyTimer == 115 || attacker->readyTimer == 117) {
			Audio_PlaySound(SND_hit3);
			Audio_PlaySound(SND_beamsword);
			float x = Random_Range(32, SCREEN_WIDTH - 32);
			float y = Random_Range(32, SCREEN_HEIGHT - 32);
			Battle_CreateSpark(15, x, y, 0);
			Battle_CreateSpark(20, SCREEN_WIDTH - x, y, 0);
		}
		if (attacker->readyTimer == 117 && attacker->actionAttacks < 64) {
			attacker->readyTimer = 114;
		}
		
		if (attacker->readyTimer == 124) {
			Audio_PlaySound(SND_hit3);
			target->x = Random_Range(64, SCREEN_WIDTH - 64);
			target->y = Random_Range(88, SCREEN_HEIGHT - 40);
			attacker->x = target->x - attacker->facing * 32;
			attacker->y = target->y;
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else
				attacker->state = FIGHTER_STATE_SPECIAL3;
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
		}
		if (attacker->readyTimer == 128 && attacker->actionAttacks < 97) {
			attacker->readyTimer = 123;
		}
		
		if (attacker->readyTimer == 160) {
			Audio_PlaySound(SND_firemassattack);
			target->x = target->xStart;
			target->y = target->yStart;
			attacker->x = attacker->xStart;
			attacker->y = attacker->yStart;
			attacker->state = FIGHTER_STATE_SPECIAL4;
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
			Battle_ShakeScreen(40);
		}
		if (attacker->readyTimer >= 160 && attacker->attackTimer <= 224 && attacker->attackTimer % 16 == 0) {
			Audio_PlaySound(SND_burn);
			for (int i = 0; i < 4; i++) {
				Battle_CreateSpark(18, 128 * (i + 1), 362, 0);
			}
		}
		
		if (attacker->readyTimer == 238) {
			attacker->spriteId = SPR_misc_lulu_ultimate_rage;
			attacker->spriteFrame = 0;
		}
		if (attacker->readyTimer >= 260 && attacker->readyTimer < 350) {
			if (attacker->readyTimer % 4 == 0) {
				attacker->x = attacker->xStart - 2;
			}
			else if (attacker->readyTimer % 4 == 2) {
				attacker->x = attacker->xStart + 2;
			}
		}
		if (attacker->readyTimer == 350) {
			attacker->x = attacker->xStart;
			attacker->spriteFrame = 1;
			Audio_PlaySound(SND_ultbeam);
			Audio_PlaySound(SND_boost);
			Battle_ShakeScreen(24);
			
			Battle_CreateSpark(19, attacker->x, attacker->y, 0);
		}
		
		if (attacker->readyTimer >= 352 && attacker->readyTimer <= 753 && attacker->readyTimer % 3 == 0) {
			Battle_CreateSpark(17, 480 - (1 - attacker->side) * 320 + Random_IRange(-128, 128), Random_IRange(-96, -64), 0);
			int sparkId = battle.sparkCounter - 1;
			if (sparkId < 0) sparkId += OBJECT_COUNT_MAX;
			
			battle.sparks[sparkId].xVel = Random_Range(22, 26) * attacker->facing;
			battle.sparks[sparkId].yVel = 32;
			Audio_PlaySound(SND_gunfire);
			
			Battle_CreateSpark(19, 192 + (1 - attacker->side) * 256 + Random_IRange(-184, 184), 320, 0);
			Audio_PlaySound(SND_minigun);
			Audio_PlaySound(SND_electric);
			Audio_PlaySound(SND_thunder);
		}
		
		if (attacker->attackAnimTimer >= 350 && attacker->attackAnimTimer <= 775 && attacker->attackAnimTimer % 9 == 8) {
			Audio_PlaySound(SND_explode);
			Battle_ShakeScreen(28);
		}
		
		if (attacker->readyTimer == 752) {
			attacker->spriteId = SPR_misc_lulu_ultimate_rage;
			attacker->spriteFrame = 0;
		}
		
		if (attacker->readyTimer == 778) {
			attacker->spriteFrame = 1;
			Audio_PlaySound(SND_subspace_transform);
			
			Audio_PlaySound(SND_burn);
			for (int i = 0; i < 5; i++) {
				Battle_CreateSpark(19, 20 + 100 * (i + 1), 362, 0);
			}
			
			attacker->attackTimer = 0;
			attacker->actionAttacks++;
			Battle_ShakeScreen(106);
		}
		if (attacker->readyTimer >= 778 && attacker->attackTimer <= 906 && attacker->attackTimer % 12 == 0) {
			Audio_PlaySound(SND_burn);
			for (int i = 0; i < 4; i++) {
				Battle_CreateSpark(18, 128 * (i + 1), 362, 0);
			}
		}
		
		if (attacker->readyTimer == 1020) {
			attacker->spriteId = -1;
			attacker->spriteFrame = 0;
			attacker->state = FIGHTER_STATE_IDLE;
		}
	}
	
	return 0;
}
void Action_Draw__93(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer < 77) {
		
	}
	else if (attacker->readyTimer < 160) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(-64, -64, SCREEN_WIDTH + 128, SCREEN_HEIGHT + 128);
		Drawer_SetDrawColor(255, 255, 255);
		
		if (attacker->readyTimer >= 124 && attacker->readyTimer <= 127) {
			Drawer_FillRect(-64, -64, SCREEN_WIDTH + 128, SCREEN_HEIGHT + 128);
			
			Drawer_SetDrawColor(0, 0, 0);
			DrawFighterChar(target->headId, target->bodyId, target->state, target->x, target->y, 2, 2, target->facing);
			DrawFighterChar(attacker->headId, attacker->bodyId, attacker->state, attacker->x, attacker->y, 2, 2, attacker->facing);
			Drawer_SetDrawColor(255, 255, 255);
		}
	}
	else if (attacker->readyTimer < 350) {
		
	}
	else if (attacker->readyTimer < 774) {
		Drawer_SetDrawColor(191, 0, 191);
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_DrawSprite(SPR_misc_dystal_final, attacker->x, attacker->y + 52, attacker->readyTimer % 6, 4, 4);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		Drawer_SetDrawColor(255, 255, 255);
		
		if ((attacker->readyTimer - 350) % 9 < 3) {
			Drawer_DrawSprite(SPR_spark_ultlulubeam, attacker->x + attacker->facing * 28, attacker->y - 24, 0, 2 * attacker->facing, 2);
		}
		else if ((attacker->readyTimer - 350) % 9 < 6) {
			Drawer_DrawSprite(SPR_spark_ultlulubeam, attacker->x + attacker->facing * 28, attacker->y - 24, 1, 2 * attacker->facing, 2);
		}
		else {
			Drawer_DrawSprite(SPR_spark_ultlulubeam, attacker->x + attacker->facing * 28, attacker->y - 24, 2, 2 * attacker->facing, 2);
		}
	}
	else if (attacker->readyTimer < 778) {
		Drawer_FillRect(-200, -200, SCREEN_WIDTH + 400, SCREEN_HEIGHT + 400);
	}
	else if (attacker->readyTimer < 906) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(127, 0, 127);
		Drawer_FillRect(-200, -200, SCREEN_WIDTH + 400, SCREEN_HEIGHT + 400);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (attacker->readyTimer < 966) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(127 + (attacker->readyTimer - 906) * 2, (attacker->readyTimer - 906) * 4, 127 + (attacker->readyTimer - 906) * 2);
		Drawer_FillRect(-200, -200, SCREEN_WIDTH + 400, SCREEN_HEIGHT + 400);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
}



int Action_Update__94(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Battle_CreateSpark(19, attacker->x, attacker->y, 0);
			Audio_PlaySound(SND_minigun);
			Audio_PlaySound(SND_electric);
			Audio_PlaySound(SND_thunder);
			Battle_ShakeScreen(12);
			
			Fighter_HealMP(attacker, attacker->actionVars[0].i);
			if (attacker->actionVars[1].i < 0) {
				Fighter_TakeDamage(attacker, NULL, -attacker->actionVars[1].i, 0);
			}
			else {
				Fighter_HealHP(attacker, attacker->actionVars[1].i);
			}
			Fighter_GainStatus(attacker, FIGHTER_STATUS_STRENGTH, attacker->actionVars[2].i, false);
			Fighter_GainStatus(attacker, FIGHTER_STATUS_HASTE, attacker->actionVars[3].i, false);
		}
	}
	
	return 0;
}



int Action_Update__95(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			
			for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_STRENGTH, attacker->actionVars[0].i, false);
				Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_ENDURANCE, attacker->actionVars[1].i, false);
				Fighter_InflictStatus(attacker, fighter, FIGHTER_STATUS_HASTE, attacker->actionVars[2].i, false);
			}
		}
	}
	
	return 0;
}



int Action_Update__96(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_InflictStatus(attacker, target, FIGHTER_STATUS_ANTIGUARD, 1, false);
			if (target->mp <= (int)(target->mpMax * attacker->actionVars[0].f)) {
				Fighter_InflictStatus(attacker, target, FIGHTER_STATUS_IMMOBILE, 1, false);
			}
			Fighter_InflictStatus(attacker, target, FIGHTER_STATUS_DISARM, 25, false);
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = (attacker->actionVars[1].i == 2) ? FIGHTER_STATE_SPECIAL1 : FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionVars[1].i == 2)
				attacker->state = FIGHTER_STATE_SPECIAL2;
			else if (attacker->actionVars[1].i == 1)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK2;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__97(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target) + attacker->mp / 8;
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE);
			
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 7) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_ATTACK1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX / 4) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			if (attacker->actionAttacks % 4 == 2)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else if (attacker->actionAttacks % 4 == 0)
				attacker->state = FIGHTER_STATE_ATTACK2;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			Audio_PlaySound(SND_swing);
		}
	}
	
	return 0;
}






int Action_Update__191(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 1660) return 1;
		
		if (attacker->attackTimer >= 15 && attacker->attackTimer <= 70) {
			if (attacker->attackTimer % 2 == 0) Audio_PlaySound(SND_crusherhit);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, SCREEN_WIDTH / 2 + 280 * cos((double)attacker->attackTimer / 1.38), SCREEN_HEIGHT / 2 + 150 * cos((double)attacker->attackTimer / 3.8879), 0);
		}
		if (attacker->attackTimer >= 100 && attacker->attackTimer <= 350) {
			if (attacker->attackTimer % 2 == 0) Audio_PlaySound(SND_crusherhit);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, SCREEN_WIDTH / 2 + 280 * cos((double)attacker->attackTimer / 3.38), SCREEN_HEIGHT / 2 + 200 * cos((double)attacker->attackTimer / 1.1879), 0);
		}
		if (attacker->attackTimer >= 400 && attacker->attackTimer <= 430) {
			Battle_ShakeScreen(10);
			if (attacker->attackTimer % 2 == 0) Audio_PlaySound(SND_crusherhit2);
			for (int i = 0; i < 8; i++) {
				Battle_CreateSpark(9901, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			}
		}
		if (attacker->attackTimer == 451) {
			Audio_PlaySound(SND_firemassattack);
			Audio_PlaySound(SND_crusherhit2);
			Battle_ShakeScreen(100);
		}
		if (attacker->attackTimer >= 510 && attacker->attackTimer <= 690 && attacker->attackTimer % 2 == 0) {
			attacker->state = FIGHTER_STATE_BLOCK;
			attacker->spriteId = SPR_misc_lulu_omega_rage;
			attacker->spriteFrame = 1;
			Battle_ShakeScreen(27);
			Audio_PlaySound(SND_gunshot);
			Battle_CreateSpark(9900, Random_Range(32, 288), Random_Range(128, SCREEN_HEIGHT - 128), 0);
		}
		if (attacker->attackTimer == 710) {
			Audio_PlaySound(SND_firemassattack);
		}
		if (attacker->attackTimer >= 710 && attacker->attackTimer <= 840 && attacker->attackTimer % 2 == 0) {
			Battle_ShakeScreen(12);
			Audio_PlaySound(SND_explode);
		}
		if (attacker->attackTimer >= 930 && attacker->attackTimer <= 1380) {
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			battle.shakeTimer -= 20;
			if (attacker->attackTimer % 5 == 0) {
				Battle_ShakeScreen(40);
				Audio_PlaySound(SND_crusherhit);
				Battle_CreateSpark(9902, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
				Battle_CreateSpark(9903, 320, 240, 0);
				Audio_PlaySound(SND_crusherhit);
				Battle_CreateSpark(9903, 320, 240, 0);
			}
			Battle_CreateSpark(9904, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
		}
		
		if (attacker->attackTimer == 1440) {
			Audio_PlaySound(SND_firemassattack);
			Audio_PlaySound(SND_crusherhit2);
			Battle_ShakeScreen(180);
			
			int damage = Random_IRange(5555, 9999) + Action_GetDamagePower(attacker, target);
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
		if (attacker->attackTimer == 1659) {
			attacker->spriteId = -1;
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->state = FIGHTER_STATE_ATTACK3;
		if (attacker->readyTimer >= 60) {
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = 0;
			
			attacker->state = FIGHTER_STATE_IDLE;
			Audio_PlayMusic(MUS_lastresort2);
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				fighter->state = FIGHTER_STATE_HURT;
			}
		}
	}
	
	return 0;
}
void Action_Draw__191(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 255, 255);
	if (attacker->readyTimer >= 0 && attacker->readyTimer < 60) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_SetDrawAlpha(attacker->readyTimer * 255 / 60);
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawAlpha(255);
	}
	else if (attacker->attackTimer >= 0 && attacker->attackTimer < 451) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer >= 510 && attacker->attackTimer <= 690) {
		for (int i = 0; i < 9; i++) {
			float angle = ((float)attacker->attackTimer * 18 + 40 * i) / 180 * PI;
			Drawer_DrawSprite_Angle(SPR_misc_omegalulugun, attacker->x, attacker->y - 24, 0, 2, 2, angle / PI * 180);
		}
		Drawer_DrawSprite_Angle(SPR_misc_omegalulugunfire, attacker->x + Random_Range(-8, 8), attacker->y - 24 + Random_Range(-8, 8), 0, 4, 4, Random_Range(-30, 30));
	}
	else if (attacker->attackTimer >= 691 && attacker->attackTimer <= 840) {
		Drawer_DrawSprite(SPR_misc_omegalulucannon, attacker->x - 8, attacker->y - 64, 0, -2, 2);
		
		if (attacker->attackTimer >= 710) {
			Drawer_DrawSprite(SPR_misc_ampbeam, attacker->x + attacker->facing * 118, attacker->y - 64, (1 + attacker->attackTimer / 2) % 3, attacker->facing * 640, 16);
			Drawer_DrawSprite(SPR_misc_ampbeamstart, attacker->x + attacker->facing * 118, attacker->y - 64, (1 + attacker->attackTimer / 2) % 3, attacker->facing * 16, 16);
		}
	}
	else if (attacker->attackTimer >= 841 && attacker->attackTimer < 930) {
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	else if (attacker->attackTimer >= 930 && attacker->attackTimer <= 1380) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		Drawer_SetDrawColor(255, 255, 255);
		
		float x = 0;
		float y = 0;
		float scale = 2;
		if ((battle.globalTimer % 12) / 4 == 2)
			scale = 8;
		else if ((battle.globalTimer % 12) / 4 == 1)
			scale = 4;
		
		Drawer_SetDrawColor(0, 15, 31);
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		
		Drawer_SetDrawBlend(BLENDMODE_ADD);
		Drawer_SetDrawColor(0, 23, 79);
		for (int j = -9; j < 16; j++)
		for (int i = -9; i < 14; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		Drawer_SetDrawColor(0, 23, 79);
		for (int j = -9; j < 20; j++)
		for (int i = -9; i < 17; i++) {
			Drawer_DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
		Drawer_SetDrawColor(255, 255, 255);
		
		DrawFighterChar(1, 1, FIGHTER_STATE_HURT, 320, 280, 2, 2, FACING_RIGHT);
		
	}
	else if (attacker->attackTimer > 1380 && attacker->attackTimer < 1440) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
}






int Action_Update__192(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 2870) return 1;
		
		if (attacker->attackTimer >= 2 && attacker->attackTimer <= 20) {
			Audio_PlaySound(SND_crusherhit);
			for (int i = 0; i < 6; i++) {
				Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
				Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
				Battle_CreateSpark(9900, SCREEN_WIDTH / 2 + 280 * cos((double)attacker->attackTimer / 1.38), SCREEN_HEIGHT / 2 + 150 * cos((double)attacker->attackTimer / 3.8879), 0);
			}
		}
		if (attacker->attackTimer == 24 || attacker->attackTimer == 28) {
			Audio_PlaySound(SND_crusherhit2);
			Audio_PlaySound(SND_crusherhit2);
			Audio_PlaySound(SND_crusherhit2);
			Audio_PlaySound(SND_subspace_transform);
			for (int i = 0; i < 10; i++) {
				Battle_CreateSpark(9909, 5 + i * 70, 480, 0);
			}
		}
		if ((attacker->attackTimer >= 98 && attacker->attackTimer <= 160) || (attacker->attackTimer >= 179 && attacker->attackTimer <= 220)) {
			if (attacker->attackTimer % 2 == 0) Audio_PlaySound(SND_crusherhit);
			if (attacker->attackTimer % 2 == 1) Audio_PlaySound(SND_crusherhit3);
			for (int i = 0; i < 3; i++) {
				int x = SCREEN_WIDTH / 2 + 280 * cos((double)(attacker->attackTimer + i * 8) / 3.38);
				int y = SCREEN_HEIGHT / 2 + 200 * cos((double)(attacker->attackTimer + i * 16) / 1.1879);
				
				Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
				Battle_CreateSpark(9900, x, y, 0);
				Battle_CreateSpark(9900, -x + 640, y, 0);
			}
		}
		if (attacker->attackTimer >= 160 && attacker->attackTimer <= 167) {
			Battle_ShakeScreen(10);
			Audio_PlaySound(SND_crusherhit2);
			for (int i = 0; i < 16; i++) {
				Battle_CreateSpark(9901, Random_Range(32, SCREEN_WIDTH - 32), Random_Range(32, SCREEN_HEIGHT - 32), 0);
				Battle_CreateSpark(9909, Random_Range(4, SCREEN_WIDTH - 4), 480, 0);
			}
		}
		if (attacker->attackTimer == 225) {
			attacker->spriteId = SPR_misc_lulu_subspace_rage;
			attacker->spriteFrame = 1;
			Audio_PlaySound(SND_firemassattack);
			Audio_PlaySound(SND_crusherhit2);
			Battle_ShakeScreen(100);
		}
		
		if (attacker->attackTimer == 290) {
			attacker->spriteId = -1;
			Battle_Camera_MoveTo(target->x - attacker->facing * 12, target->y - 24, 3, 256);
			Fighter_MoveTo(attacker, target->x - attacker->facing * 24, target->y, 24, 0);
		}
		if (attacker->attackTimer == 291 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer >= 292 && attacker->attackTimer <= 320 && attacker->attackTimer % 2 == 0) {
			if (attacker->attackTimer % 4 < 2) {
				if (Random(1) < 0.5)
					attacker->state = FIGHTER_STATE_SPECIAL3;
				else
					attacker->state = FIGHTER_STATE_SPECIAL2;
				Audio_PlaySound(SND_crusherhit3);
				Battle_ShakeScreen(12);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
				Audio_PlaySound(SND_crusherhit3);
			}
		}
		if (attacker->attackTimer == 320) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, target->x + attacker->facing * 24, target->y, 24, 0);
		}
		if (attacker->attackTimer == 323) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_SPECIAL3;
			attacker->facing = FACING_RIGHT;
			battle.fighters[0].facing = FACING_LEFT;
			Fighter_MoveTo(&battle.fighters[0], 480, 200, 36, 0);
		}
		if (attacker->attackTimer == 340) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 504, 200, 36, 0);
			Battle_Camera_MoveTo(504, 180, 3, 36);
		}
		if (attacker->attackTimer == 341 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 342) {
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->facing = FACING_LEFT;
			battle.fighters[0].facing = FACING_RIGHT;
		}
		if (attacker->attackTimer >= 344 && attacker->attackTimer <= 440 && attacker->attackTimer % 2 == 0) {
			if (attacker->attackTimer % 4 < 2) {
				if (Random(1) < 0.5)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else
					attacker->state = FIGHTER_STATE_SPECIAL3;
				Audio_PlaySound(SND_explode);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
			Battle_ShakeScreen(16);
			Audio_PlaySound(SND_crusherhit4);
			Audio_PlaySound(SND_explode);
			Battle_CreateSpark(6, battle.fighters[0].x + Random_IRange(-4, 4), battle.fighters[0].y - 24 + Random_IRange(-4, 4), 0);
		}
		if (attacker->attackTimer == 441) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK3;
			Fighter_MoveTo(&battle.fighters[0], 180, 310, 36, 0);
			Battle_Camera_MoveTo(180, 290, 3, 36);
		}
		if (attacker->attackTimer == 448) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 156, 310, 72, 0);
		}
		if (attacker->attackTimer == 450 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 451) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->facing = FACING_RIGHT;
			Fighter_MoveTo(&battle.fighters[0], 400, 460, 36, 0);
			Battle_Camera_MoveTo(400, 440, 3, 36);
		}
		if (attacker->attackTimer == 458) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 376, 440, 72, 0);
		}
		if (attacker->attackTimer == 460 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 461) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK3;
			Fighter_MoveTo(&battle.fighters[0], 440, 200, 36, 0);
			Battle_Camera_MoveTo(440, 200, 3, 36);
		}
		if (attacker->attackTimer == 468) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 464, 200, 72, 0);
		}
		if (attacker->attackTimer == 470 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 471) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK2;
			attacker->facing = FACING_LEFT;
			Fighter_MoveTo(&battle.fighters[0], battle.fighters[0].xStart, battle.fighters[0].yStart, 36, 0);
			Battle_Camera_MoveTo(battle.fighters[0].xStart, battle.fighters[0].yStart - 20, 3, 36);
		}
		if (attacker->attackTimer == 478) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, battle.fighters[0].xStart + 24, battle.fighters[0].yStart, 72, 0);
		}
		if (attacker->attackTimer == 480 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer >= 481 && attacker->attackTimer <= 567 && attacker->attackTimer % 2 == 0) {
			if (attacker->attackTimer % 4 < 2) {
				if (Random(1) < 0.5)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else
					attacker->state = FIGHTER_STATE_SPECIAL3;
				Audio_PlaySound(SND_explode);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
			Battle_ShakeScreen(16);
			Audio_PlaySound(SND_crusherhit4);
			Audio_PlaySound(SND_explode);
			Battle_CreateSpark(6, battle.fighters[0].x + Random_IRange(-4, 4), battle.fighters[0].y - 24 + Random_IRange(-4, 4), 0);
		}
		if (attacker->attackTimer == 568) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, target->x + attacker->facing * 24, target->y, 24, 0);
		}
		if (attacker->attackTimer == 571) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_SPECIAL3;
			attacker->facing = FACING_RIGHT;
			Fighter_MoveTo(&battle.fighters[0], 480, 200, 36, 0);
		}
		if (attacker->attackTimer == 578) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 504, 200, 36, 0);
			Battle_Camera_MoveTo(504, 180, 3, 36);
		}
		if (attacker->attackTimer == 580 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 581) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK3;
			Fighter_MoveTo(&battle.fighters[0], 180, 310, 36, 0);
			Battle_Camera_MoveTo(180, 290, 3, 36);
		}
		if (attacker->attackTimer == 588) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 156, 310, 72, 0);
		}
		if (attacker->attackTimer == 590 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 591) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK1;
			attacker->facing = FACING_RIGHT;
			Fighter_MoveTo(&battle.fighters[0], 400, 460, 36, 0);
			Battle_Camera_MoveTo(400, 440, 3, 36);
		}
		if (attacker->attackTimer == 598) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 376, 440, 72, 0);
		}
		if (attacker->attackTimer == 600 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 601) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK3;
			Fighter_MoveTo(&battle.fighters[0], 440, 200, 36, 0);
			Battle_Camera_MoveTo(440, 200, 3, 36);
		}
		if (attacker->attackTimer == 608) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 464, 200, 72, 0);
		}
		if (attacker->attackTimer == 610 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer == 611) {
			Battle_ShakeScreen(8);
			Audio_PlaySound(SND_crusherhit);
			attacker->state = FIGHTER_STATE_ATTACK2;
			attacker->facing = FACING_LEFT;
			Fighter_MoveTo(&battle.fighters[0], battle.fighters[0].xStart, battle.fighters[0].yStart, 36, 0);
			Battle_Camera_MoveTo(battle.fighters[0].xStart, battle.fighters[0].yStart - 20, 3, 36);
		}
		if (attacker->attackTimer == 618) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, 296, 288, 72, 0);
			Battle_Camera_MoveTo(264, 264, 3, 36);
		}
		if (attacker->attackTimer == 620 && attacker->moveTarget.enabled) attacker->attackTimer--;
		
		if (attacker->attackTimer == 624) {
			attacker->state = FIGHTER_STATE_SPECIAL3;
		}
		
		if (attacker->attackTimer == 627) {
			Audio_PlaySound(SND_firemassattack);
			Battle_CreateSpark(9908, battle.fighters[0].x, battle.fighters[0].y + 20, 0);
		}
		if (attacker->attackTimer == 668) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, battle.fighters[0].x + 32, battle.fighters[0].y, 12, 0);
			Battle_Camera_MoveTo(battle.fighters[0].x, battle.fighters[0].y - 20, 3, 12);
		}
		if (attacker->attackTimer == 670 && attacker->moveTarget.enabled) attacker->attackTimer--;
		if (attacker->attackTimer >= 671 && attacker->attackTimer <= 767 && attacker->attackTimer % 2 == 0) {
			if (attacker->attackTimer % 4 < 2) {
				if (Random(1) < 0.5)
					attacker->state = FIGHTER_STATE_ATTACK3;
				else
					attacker->state = FIGHTER_STATE_SPECIAL3;
				Audio_PlaySound(SND_explode);
				Audio_PlaySound(SND_crusherhit4);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
			Battle_ShakeScreen(16);
			Audio_PlaySound(SND_crusherhit3);
			Battle_CreateSpark(6, battle.fighters[0].x + Random_IRange(-4, 4), battle.fighters[0].y - 24 + Random_IRange(-4, 4), 0);
		}
		
		if (attacker->attackTimer >= 770 && attacker->attackTimer < 860) {
			int timer = (attacker->attackTimer - 770) % 30;
			if (timer == 0) {
				Audio_PlaySound(SND_crusherhit);
				Fighter_MoveTo(target, 640 - 96, battle.fighters[0].yStart, 30, 0);
			}
			if (timer % 2 == 0) {
				Battle_CreateSpark(9907, battle.fighters[0].x, 480, 0);
				Battle_CreateSpark(9907, battle.fighters[0].x + 24, 480, 0);
				Battle_CreateSpark(9907, battle.fighters[0].x - 24, 480, 0);
				Audio_PlaySound(SND_thunder);
				Battle_ShakeScreen(3);
			}
			if (timer == 15) {
				Audio_PlaySound(SND_crusherhit);
				Fighter_MoveTo(target, 96, battle.fighters[0].yStart, 30, 0);
			}
			Battle_Camera_MoveTo(battle.fighters[0].x, battle.fighters[0].y - 20, 3, 29);
		}
		
		if (attacker->attackTimer == 860) {
			Audio_PlaySound(SND_firemassattack);
			Audio_PlaySound(SND_firemassattack);
			Audio_PlaySound(SND_firemassattack);
			attacker->state = FIGHTER_STATE_ATTACK2;
			attacker->facing = FACING_LEFT;
			battle.fighters[0].moveTarget.enabled = false;
			attacker->moveTarget.enabled = false;
			Battle_Camera_MoveToStart(640);
			
			attacker->spriteId = SPR_misc_lulu_subspace_rage;
			attacker->spriteFrame = 1;
			
			battle.fighters[0].state = FIGHTER_STATE_DOWN;
			battle.fighters[0].x = battle.fighters[0].xStart;
			battle.fighters[0].y = battle.fighters[0].yStart;
			attacker->x = attacker->xStart;
			attacker->y = attacker->yStart;
			
			for (int i = 0; i < 5; i++) {
				Battle_CreateSpark(9908, 40 + i * 140, 480, 0);
			}
		}
		
		if (attacker->attackTimer == 958) {
			Dialog_Continue();
		}
		if (attacker->attackTimer == 960) {
			Dialog_Run(2308);
			Audio_PlayMusic(MUS_lastresort2_pitchdown);
			attacker->spriteFrame = 0;
		}
		if (attacker->attackTimer > 960 && attacker->attackTimer < 1880) {
			if (attacker->attackTimer % 48 == 0) {
				Battle_CreateSpark(9910, attacker->x, attacker->y - 24, 0);
				Audio_PlaySound(SND_charge);
				for (int i = 0; i < 10; i++) {
					Battle_CreateSpark(9907, attacker->x - 72 + i * 16, 480, 0);
				}
			}
			if (attacker->attackTimer % 48 >= 0 && attacker->attackTimer % 48 <= 44 && attacker->attackTimer % 4 == 0) {
				Battle_CreateSpark(9906, attacker->x + Random_IRange(-80, 80), 480, 0);
			}
			Battle_ShakeScreen((attacker->attackTimer - 960) / 80);
		}
		if (attacker->attackTimer == 1899 && !Dialog_IsFinished()) attacker->attackTimer--;
		if (attacker->attackTimer == 1900) {
			Audio_PlaySound(SND_subspace_transform2);
		}
		if (attacker->attackTimer == 1930) {
			attacker->spriteFrame = 1;
		}
		if (attacker->attackTimer >= 1930 && attacker->attackTimer < 2650) {
			if (attacker->attackTimer % 32 == 0) {
				Audio_PlaySound(SND_subspace_transform);
				for (int i = 0; i < 5; i++) {
					Battle_CreateSpark(9908, battle.fighters[0].x - 80 + i * 40, 480, 0);
				}
			}
			if (attacker->attackTimer >= 2050 && attacker->attackTimer % 14 == 0) {
				Audio_PlaySound(SND_explode);
				for (int i = 0; i < 6; i++) {
					Battle_CreateSpark(9908, i * 128, 480, 0);
				}
			}
			if (attacker->attackTimer >= 2300 && attacker->attackTimer % 6 == 0) {
				Audio_PlaySound(SND_crusherhit2);
				for (int i = 0; i < 5; i++) {
					Battle_CreateSpark(9908, 20 + i * 150, 400, 0);
					Battle_CreateSpark(9908, 20 + i * 150, 280, 0);
				}
				for (int i = 0; i < 5; i++) {
					Battle_CreateSpark(9909, 40 + i * 140, 360, 0);
				}
			}
			if (attacker->attackTimer >= 2500 && attacker->attackTimer % 2 == 0) {
				Audio_PlaySound(SND_crusherhit);
				Audio_PlaySound(SND_crusherhit3);
				for (int i = 0; i < 8; i++) {
					Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
					Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
					Battle_CreateSpark(9900, SCREEN_WIDTH / 2 + 280 * cos((double)attacker->attackTimer / 1.38), SCREEN_HEIGHT / 2 + 150 * cos((double)attacker->attackTimer / 3.8879), 0);
				}
			}
			if (attacker->attackTimer >= 2300)
				Battle_ShakeScreen((attacker->attackTimer - 1630) / 10);
			else
				Battle_ShakeScreen((attacker->attackTimer - 1730) / 20);
		}
		
		
		
		
		if (attacker->attackTimer == 2690) {
			attacker->spriteId = -1;
			attacker->state = FIGHTER_STATE_SPECIAL1;
			for (int i = 0; i < 30; i++) {
				Audio_PlaySound(SND_subspace_transform);
			}
			Battle_ShakeScreen(180);
		}
		if (attacker->attackTimer == 2720) {
			int damage = 8878873 + Action_GetDamagePower(attacker, target);
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				int damageLocal = Action_CalculateAttackPower(attacker, fighter, damage);
				
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_LETHAL);
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		attacker->state = FIGHTER_STATE_SPECIAL1;
		if (attacker->readyTimer == 10) {
			Fighter_MoveTo(attacker, battle.fighters[0].x - attacker->facing * 48, attacker->y, 24, 0);
		}
		if (attacker->readyTimer >= 21) {
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = 0;
			
			attacker->state = FIGHTER_STATE_IDLE;
			
			int iMin = 0;
			int iMax = 15;
			
			if (attacker->targetId == TARGET_ALLYPARTY) {
				iMax = 7;
			}
			else if (attacker->targetId == TARGET_ENEMYPARTY) {
				iMin = 8;
			}
			
			for (int i = iMin; i <= iMax; i++) {
				Fighter* fighter = &battle.fighters[i];
				if (!fighter->enabled || !fighter->alive) continue;
				
				fighter->state = FIGHTER_STATE_HURT;
			}
		}
	}
	
	return 0;
}
void Action_Draw__192(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0 && attacker->attackTimer < 225) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		Drawer_SetDrawColor(255, 255, 255);
	}
	if (attacker->attackTimer >= 859 && attacker->attackTimer < 861) {
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	if (attacker->attackTimer >= 1930 && attacker->attackTimer < 1932) {
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	if (attacker->attackTimer >= 2660 && attacker->attackTimer < 2720) {
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
}






void Action_AnimUpdate__0(Fighter* attacker, Fighter* target) {
	
}
void Action_AnimDraw__0(Fighter* attacker, Fighter* target) {
	
}

void Action_AnimDraw__1(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_punch, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_punch, target->x, target->y - 24, 1, 2, 2);
	}
}

void Action_AnimDraw__2(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 4, 2, 2);
	}
}

void Action_AnimDraw__3(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimDraw__4(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_vinespike, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_vinespike, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_vinespike, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 13) {
		Drawer_DrawSprite(SPR_spark_vinespike, target->x, target->y, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_vinespike, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 17) {
		Drawer_DrawSprite(SPR_spark_vinespike, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 19) {
		Drawer_DrawSprite(SPR_spark_vinespike, target->x, target->y, 0, 2, 2);
	}
}

void Action_AnimDraw__5(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_vinetrap, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_vinetrap, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_vinetrap, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_vinetrap, target->x, target->y, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 22) {
		Drawer_DrawSprite(SPR_spark_vinetrap, target->x, target->y, 4, 2, 2);
	}
}

void Action_AnimDraw__6(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_misc_shuriken, attacker->x + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 10, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 10, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 27) {
		Drawer_DrawSprite(SPR_misc_shuriken, target->x + target->facing * 6, target->y - 24, 0, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__7(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_gunfire);
		attacker->state = FIGHTER_STATE_SPECIAL2;
	}
	else if (attacker->attackAnimTimer == 5) {
		attacker->state = FIGHTER_STATE_SPECIAL1;
	}
}
void Action_AnimDraw__7(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
}

void Action_AnimUpdate__8(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 20) {
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(8);
		attacker->state = FIGHTER_STATE_ATTACK3;
	}
}
void Action_AnimDraw__8(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 4, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x - 16, target->y - 34, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x + 16, target->y - 34, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 4, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 4, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 4, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 4, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 3, 2, 2);
	}
}

void Action_AnimUpdate__9(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_gunfire);
		attacker->state = FIGHTER_STATE_SPECIAL4;
	}
	else if (attacker->attackAnimTimer == 5) {
		attacker->state = FIGHTER_STATE_SPECIAL3;
	}
}
void Action_AnimDraw__9(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 7) {
		Drawer_DrawSprite(SPR_misc_rocket, attacker->x + attacker->facing * 16 + (target->x + target->facing * 6 - (attacker->x + attacker->facing * 16)) * attacker->attackAnimTimer / 6, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 6, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 8, 8);
	}
	else if (attacker->attackAnimTimer < 13) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 8, 8);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 8, 8);
	}
	else if (attacker->attackAnimTimer < 19) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 8, 8);
	}
}

void Action_AnimUpdate__10(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 15) {
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(6);
	}
}
void Action_AnimDraw__10(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_misc_bomb, attacker->x + attacker->facing * 8 + (target->x + target->facing * 6 - attacker->x + attacker->facing * 8) * attacker->attackAnimTimer / 15, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 15 + (attacker->attackAnimTimer - 7) * (attacker->attackAnimTimer - 7) - 48, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 17) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 19) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 21) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 23) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimDraw__11(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_misc_kunai, attacker->x + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 10, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 10, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 27) {
		Drawer_DrawSprite(SPR_misc_kunai, target->x + target->facing * 6, target->y - 24, 0, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__12(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_burn);
	}
	else if (attacker->attackAnimTimer == 22) {
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(6);
	}
}
void Action_AnimDraw__12(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_SetDrawColor(255, 159, 0);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_SetDrawColor(255, 159, 0);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
	if (attacker->attackAnimTimer < 22) {
		Drawer_DrawSprite(SPR_misc_flameorb, attacker->x + attacker->facing * 72 + (target->x + target->facing * 12 - (attacker->x + attacker->facing * 72)) * attacker->attackAnimTimer / 21, attacker->y - 22 + (target->y - attacker->y) * attacker->attackAnimTimer / 21, (attacker->attackAnimTimer / 3) % 3, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 26) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 30) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimUpdate__13(Fighter* attacker, Fighter* target) {
	
}
void Action_AnimDraw__13(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_SetDrawColor(0, 165, 255);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_SetDrawColor(0, 165, 255);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_SetDrawColor(0, 43, 255);
		Drawer_DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
	if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_misc_waterbullet, attacker->x + attacker->facing * 64 + (target->x + target->facing * 6 - (attacker->x + attacker->facing * 64)) * attacker->attackAnimTimer / 13, attacker->y - 22 + (target->y - attacker->y) * attacker->attackAnimTimer / 13, (attacker->attackAnimTimer / 3) % 2, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__14(Fighter* attacker, Fighter* target) {
	
}
void Action_AnimDraw__14(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 56, attacker->y - 26, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 56, attacker->y - 26, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 56, attacker->y - 26, 2, 2, 2);
	}
	
	if (attacker->attackAnimTimer >= 2) {
		if (attacker->attackAnimTimer < 4) {
			Drawer_DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 72, attacker->y - 26, 0, 2, 2);
		}
		else if (attacker->attackAnimTimer < 6) {
			Drawer_DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 72, attacker->y - 26, 1, 2, 2);
		}
		else if (attacker->attackAnimTimer < 8) {
			Drawer_DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 72, attacker->y - 26, 2, 2, 2);
		}
	}
	
	if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_misc_ampbullet, attacker->x + attacker->facing * 64 + (target->x + target->facing * 6 - (attacker->x + attacker->facing * 64)) * attacker->attackAnimTimer / 13, attacker->y - 26 + (target->y - attacker->y) * attacker->attackAnimTimer / 13, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 14) {
		Drawer_SetDrawColor(0, 255, 255);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_SetDrawColor(0, 255, 255);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_SetDrawColor(0, 255, 255);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_SetDrawColor(0, 255, 255);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimUpdate__15(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer % 2 == 0 && attacker->attackAnimTimer < 8) {
		Battle_ShakeScreen(40);
	}
}
void Action_AnimDraw__15(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_misc_ampbeam, attacker->x + attacker->facing * 38, attacker->y - 22, attacker->attackAnimTimer / 2, attacker->facing * 640, 4);
		Drawer_DrawSprite(SPR_misc_ampbeamstart, attacker->x + attacker->facing * 38, attacker->y - 22, attacker->attackAnimTimer / 2, attacker->facing * 4, 4);
	}
}

void Action_AnimUpdate__16(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 15) {
		Audio_PlaySound(SND_firemassattack);
	}
	if (attacker->attackAnimTimer >= 15 && attacker->attackAnimTimer <= 135 && attacker->attackAnimTimer % 7 == 0) {
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(76);
	}
}
void Action_AnimDraw__16(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_misc_bomb, attacker->x + attacker->facing * 8 + (target->x + target->facing * 6 - attacker->x + attacker->facing * 8) * attacker->attackAnimTimer / 15, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 15 + (attacker->attackAnimTimer - 7) * (attacker->attackAnimTimer - 7) - 48, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 142) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 16, 16);
	}
	else if (attacker->attackAnimTimer < 145) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 16, 16);
	}
	else if (attacker->attackAnimTimer < 148) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 16, 16);
	}
	else if (attacker->attackAnimTimer < 151) {
		Drawer_SetDrawColor(255, 191, 0);
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 16, 16);
	}
}

void Action_AnimUpdate__17(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		attacker->state = FIGHTER_STATE_SPECIAL2;
		Audio_PlaySound(SND_shards);
	}
	else if (attacker->attackAnimTimer == 66) {
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(64);
	}
}
void Action_AnimDraw__17(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		
	}
	else if (attacker->attackAnimTimer < 64) {
		if (attacker->facing == FACING_RIGHT)
			Drawer_FillRect(attacker->x + 26, attacker->y - 25, attacker->attackAnimTimer * 24, 2);
		else
			Drawer_FillRect(attacker->x - 26 - attacker->attackAnimTimer * 24, attacker->y - 25, attacker->attackAnimTimer * 24, 2);
	}
	else if (attacker->attackAnimTimer < 66) {
		if (attacker->facing == FACING_RIGHT)
			Drawer_FillRect(attacker->x + 26, attacker->y - 33, attacker->attackAnimTimer * 24, 18);
		else
			Drawer_FillRect(attacker->x - 26 - attacker->attackAnimTimer * 24, attacker->y - 33, attacker->attackAnimTimer * 24, 18);
	}
	else if (attacker->attackAnimTimer < 68) {
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	else if (attacker->attackAnimTimer < 70) {
		Drawer_DrawSprite(SPR_spark_flower, target->x, target->y - 24, 0, 8, 8);
	}
	else if (attacker->attackAnimTimer < 72) {
		Drawer_DrawSprite(SPR_spark_flower, target->x, target->y - 24, 1, 8, 8);
	}
	else if (attacker->attackAnimTimer < 74) {
		Drawer_DrawSprite(SPR_spark_flower, target->x, target->y - 24, 2, 8, 8);
	}
	else if (attacker->attackAnimTimer < 76) {
		Drawer_DrawSprite(SPR_spark_flower, target->x, target->y - 24, 3, 8, 8);
	}
	else if (attacker->attackAnimTimer < 78) {
		Drawer_DrawSprite(SPR_spark_flower, target->x, target->y - 24, 4, 8, 8);
	}
}

void Action_AnimDraw__18(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 4, 2, 2);
	}
}

void Action_AnimDraw__19(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 4, 2, 2);
	}
}

void Action_AnimUpdate__20(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_boost);
	}
}
void Action_AnimDraw__20(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 31, 31);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__21(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_boost);
	}
}
void Action_AnimDraw__21(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(31, 31, 255);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__22(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_freeze);
	}
}
void Action_AnimDraw__22(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(0, 191, 255);
	if (attacker->attackAnimTimer < 50) {
		Drawer_DrawSprite(SPR_spark_snow, target->x + 18 - 36 * (attacker->attackAnimTimer % 16 < 8), target->y - 6 - 36 * (attacker->attackAnimTimer % 16 < 4 || attacker->attackAnimTimer % 16 >= 12), 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 54) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 58) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 62) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 2, 4, 4);
	}
	else if (attacker->attackAnimTimer < 66) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 3, 4, 4);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__23(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 2) {
		Audio_PlaySound(SND_thunder);
	}
}
void Action_AnimDraw__23(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 255, 31);
	if (attacker->attackAnimTimer < 8) {
		int x = target->x;
		for (int y = target->y; y > 128; y -= 2) {
			Drawer_SetDrawColor(255, 255, 31);
			Drawer_FillRect(x - 3, y - 1, 6, 2);
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_FillRect(x - 1, y - 1, 2, 2);
			x += Random_IRange(-1, 1) * 2;
		}
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_SetDrawAlpha(63);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawAlpha(255);
	}
	else if (attacker->attackAnimTimer < 14) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 22) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 26) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__24(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 8) {
		Audio_PlaySound(SND_slap);
	}
}
void Action_AnimDraw__24(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_punch, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_punch, target->x, target->y - 24, 1, 2, 2);
	}
}

void Action_AnimUpdate__25(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1 || attacker->attackAnimTimer == 6) {
		Audio_PlaySound(SND_minigun);
		attacker->state = FIGHTER_STATE_SPECIAL2;
	}
	else if (attacker->attackAnimTimer == 4 || attacker->attackAnimTimer == 9) {
		attacker->state = FIGHTER_STATE_SPECIAL1;
	}
}
void Action_AnimDraw__25(Fighter* attacker, Fighter* target) {
	
}

void Action_AnimUpdate__26(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer % 5 == 0 && attacker->attackAnimTimer >= 5 && attacker->attackAnimTimer <= 15) {
		float angle = PI * (1.0 - attacker->attackAnimTimer / 7.5) / 6.0;
		Battle_CreateSpark(6, target->x + 40 * target->facing + cos(angle) * 40 * attacker->facing, target->y - 24 - sin(angle) * 40, 0);
		Battle_ShakeScreen(12);
		Audio_PlaySound(SND_explode);
	}
}
void Action_AnimDraw__26(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(127, 127, 127);
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 2, 4, 4);
	}
	else if (attacker->attackAnimTimer < 11) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 3, 4, 4);
	}
	else if (attacker->attackAnimTimer < 14) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 4, 4, 4);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__27(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		attacker->y -= 512;
	}
	else if (attacker->attackAnimTimer == 106) {
		attacker->x = target->x - 32 * attacker->facing;
		attacker->y = target->y - 512;
		Audio_PlaySound(SND_swing);
	}
	else if (attacker->attackAnimTimer == 110) {
		attacker->y += 512;
	}
	else if (attacker->attackAnimTimer == 112) {
		Audio_PlaySound(SND_thunder);
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(40);
	}
	else if (attacker->attackAnimTimer == 136) {
		Fighter_MoveToStart(attacker);
	}
}
void Action_AnimDraw__27(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 255, 31);
	if (attacker->attackAnimTimer < 4) {
		for (int x = attacker->x - 7; x <= attacker->x + 6; x += 4) {
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_FillRect(x, 128, 2, attacker->y + 512 - 128);
		}
	}
	else if (attacker->attackAnimTimer < 106) {
		
	}
	else if (attacker->attackAnimTimer < 110) {
		for (int x = attacker->x - 7; x <= attacker->x + 6; x += 4) {
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_FillRect(x, 128, 2, attacker->y + 512 - 128);
		}
	}
	else if (attacker->attackAnimTimer < 114) {
		int x = target->x;
		for (int y = target->y; y > 128; y -= 2) {
			Drawer_SetDrawColor(255, 255, 31);
			Drawer_FillRect(x - 3, y - 1, 6, 2);
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_FillRect(x - 1, y - 1, 2, 2);
			x += Random_IRange(-1, 1) * 2;
		}
	}
	else if (attacker->attackAnimTimer < 116) {
		Drawer_SetDrawAlpha(63);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawAlpha(255);
	}
	else if (attacker->attackAnimTimer < 120) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 124) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 128) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 132) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__28(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 10) {
		Audio_ApplySoundFilter(1);
		
		int r = Random_IRange(0, 2);
		if (r == 0)
			Audio_PlaySound(SND_unknown1);
		else if (r == 1)
			Audio_PlaySound(SND_unknown2);
		else
			Audio_PlaySound(SND_unknown3);
	}
	else if (attacker->attackAnimTimer == 40) {
		Audio_RemoveSoundFilter();
	}
}
void Action_AnimDraw__28(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 10) {
		for (int y = target->y; y > target->y - 40; y -= 2) {
			Drawer_SetDrawColor(255, 0, 0);
			for (int i = 0; i < 2; i++) {
				Drawer_FillRect(target->x + Random_IRange(-32, 32), y - 1, Random_IRange(1, 2) * 2, 2);
			}
			Drawer_SetDrawColor(255, 127, 0);
			for (int i = 0; i < 2; i++) {
				Drawer_FillRect(target->x + Random_IRange(-32, 32), y - 1, Random_IRange(1, 2) * 2, 2);
			}
		}
		Drawer_SetDrawColor(255, 255, 255);
	}
}

void Action_AnimDraw__29(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(0, 127, 255);
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_spark_slash, target->x, target->y - 24, 4, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__30(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_saw);
	}
}
void Action_AnimDraw__30(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 0, 255);
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 5, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__31(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_saw);
	}
	if (attacker->attackAnimTimer == 4 || attacker->attackAnimTimer == 8 || attacker->attackAnimTimer == 13) {
		Audio_PlaySound(SND_sawkill);
	}
	if (attacker->attackAnimTimer % 4 == 0 && attacker->attackAnimTimer >= 4 && attacker->attackAnimTimer <= 28) {
		Battle_CreateSpark(3, target->x, target->y - 24 - 16 + attacker->attackAnimTimer, 0);
		Battle_ShakeScreen(2);
		Audio_PlaySound(SND_poison);
	}
	if (attacker->attackAnimTimer == 32) {
		attacker->state = FIGHTER_STATE_ATTACK3;
	}
}
void Action_AnimDraw__31(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 0, 255);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 32) {
		Drawer_DrawSprite(SPR_spark_saw, target->x, target->y - 24, 5, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__32(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 3) {
		Audio_PlaySound(SND_swing);
	}
}
void Action_AnimDraw__32(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 7) {
		Drawer_DrawSprite(SPR_misc_knife2, attacker->x + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 8, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 8, 0, 2 * attacker->facing, 2);
		Drawer_DrawSprite(SPR_misc_knife2, attacker->x - attacker->facing * 6 + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 8, attacker->y - 16 + (target->y - attacker->y) * attacker->attackAnimTimer / 8, 0, 2 * attacker->facing, 2);
		Drawer_DrawSprite(SPR_misc_knife2, attacker->x - attacker->facing * 12 + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 8, attacker->y - 8 + (target->y - attacker->y) * attacker->attackAnimTimer / 8, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 25) {
		Drawer_DrawSprite(SPR_misc_knife2, target->x + target->facing * 6, target->y - 24, 0, 2 * attacker->facing, 2);
		Drawer_DrawSprite(SPR_misc_knife2, target->x + target->facing * 6 - attacker->facing * 6, target->y - 16, 0, 2 * attacker->facing, 2);
		Drawer_DrawSprite(SPR_misc_knife2, target->x + target->facing * 6 - attacker->facing * 12, target->y - 8, 0, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__33(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 2 || attacker->attackAnimTimer == 4) {
		Audio_PlaySound(SND_swing);
	}
	if (attacker->attackAnimTimer == 70 || attacker->attackAnimTimer == 72 || attacker->attackAnimTimer == 74 || attacker->attackAnimTimer == 76) {
		Audio_PlaySound(SND_slap);
	}
}
void Action_AnimDraw__33(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 16) {
		for (int i = 0; i < 6; i++) {
			Drawer_DrawSprite_Angle(SPR_misc_knife2, attacker->x + (6 - i * 6) * attacker->facing, attacker->y - 48 - attacker->attackAnimTimer * 32, 0, 2 * attacker->facing, 2, 180 + attacker->facing * 90);
		}
	}
	else if (attacker->attackAnimTimer < 24) {
		
	}
	else if (attacker->attackAnimTimer < 122) {
		for (int i = 0; i < 32; i++) {
			Drawer_DrawSprite_Angle(SPR_misc_knife2, 480 - attacker->side * 320 + cos((float)i * 1.2) * 16 - 140 + (i % 8) * 40, 192 + sin((float)i * 1.2) * 16 + (i / 8) * 58 - Max(0, (70 - attacker->attackAnimTimer - (i % 4) * 2) * 36), 0, 2 * attacker->facing, 2, 180 - attacker->facing * 90);
		}
	}
}

void Action_AnimDraw__34(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimUpdate__35(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_charge);
	}
}
void Action_AnimDraw__35(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 255, 0);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__36(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		attacker->state = FIGHTER_STATE_SPECIAL2;
	}
	else if (attacker->attackAnimTimer == 3) {
		Audio_PlaySound(SND_gunfire2);
	}
	else if (attacker->attackAnimTimer == 7) {
		Battle_ShakeScreen(6);
	}
	else if (attacker->attackAnimTimer == 9) {
		attacker->state = FIGHTER_STATE_SPECIAL1;
	}
}
void Action_AnimDraw__36(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(223, 223, 223);
	if (attacker->attackAnimTimer < 4) {
		
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite_Angle(SPR_spark_saw, attacker->x + (target->x - attacker->x) * (attacker->attackAnimTimer - 4) / 3, attacker->y - 26 + (target->y - attacker->y) * (attacker->attackAnimTimer - 4) / 3, 3, 2 * attacker->facing, 2, 180 + 90 * attacker->facing);
		if (attacker->attackAnimTimer >= 5) Drawer_DrawSprite_Angle(SPR_spark_boost, attacker->x + (target->x - attacker->x) * (attacker->attackAnimTimer - 5) / 3, attacker->y - 26 + (target->y - attacker->y) * (attacker->attackAnimTimer - 5) / 3, 0, 2 * attacker->facing, 2, 180 + 90 * attacker->facing);
		if (attacker->attackAnimTimer >= 6) Drawer_DrawSprite_Angle(SPR_spark_boost, attacker->x + (target->x - attacker->x) * (attacker->attackAnimTimer - 6) / 3, attacker->y - 26 + (target->y - attacker->y) * (attacker->attackAnimTimer - 6) / 3, 0, 2 * attacker->facing, 2, 180 + 90 * attacker->facing);
	}
	
	if (attacker->attackAnimTimer < 7) {
		
	}
	else if (attacker->attackAnimTimer < 11) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 19) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 23) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimUpdate__37(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer <= 0) return;
	if (attacker->attackAnimTimer == 1) {
		attacker->state = FIGHTER_STATE_RUN;
	}
	
	if (attacker->attackAnimTimer <= 58) {
		attacker->x += (target->x - attacker->xStart - attacker->facing * 8) / 58;
		attacker->y += (target->y - attacker->yStart - 40) / 58 + ((float)attacker->attackAnimTimer / 29 - 1) * 5;
	}
	else if (attacker->attackAnimTimer == 59) {
		Battle_ShakeScreen(6);
		attacker->state = FIGHTER_STATE_IDLE;
	}
	else if (attacker->attackAnimTimer < 64) {
		
	}
	else if (attacker->attackAnimTimer == 64) {
		attacker->state = FIGHTER_STATE_RUN;
	}
	else if (attacker->attackAnimTimer < 93) {
		attacker->x += (attacker->xStart - target->x + attacker->facing * 8) / 29;
		attacker->y += (attacker->yStart - target->y + 40) / 29 + ((float)(attacker->attackAnimTimer - 64) / 14 - 1) * 10;
	}
	else if (attacker->attackAnimTimer == 93) {
		attacker->x = attacker->xStart;
		attacker->y = attacker->yStart;
	}
}

void Action_AnimUpdate__38(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer >= 1 && attacker->attackAnimTimer <= 46 && attacker->attackAnimTimer % 7 == 1) {
		Audio_PlaySound(SND_boost);
	}
	if (attacker->attackAnimTimer >= 72 && attacker->attackAnimTimer <= 212 && attacker->attackAnimTimer % 4 == 0) {
		Audio_PlaySound(SND_sawkill);
		Battle_CreateSpark(8, 320 + Random_IRange(-280, 280), 240 + Random_IRange(-200, 200), 0);
	}
	if (attacker->attackAnimTimer >= 72 && attacker->attackAnimTimer <= 196) {
		Battle_CreateSpark(9, 320 + Random_IRange(-312, 312), 480, 0);
	}
	/*if (attacker->attackAnimTimer >= 112 && attacker->attackAnimTimer <= 180 && attacker->attackAnimTimer % 8 == 0) {
		Audio_PlaySound(SND_sawkill);
	}*/
}
void Action_AnimDraw__38(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 15) {
		
	}
	else if (attacker->attackAnimTimer < 72) {
		for (int i = 0; i <= 640; i += 32) {
			Drawer_DrawSprite(SPR_spark_tsunami, i, 554 - attacker->attackAnimTimer * 3, (attacker->attackAnimTimer / 4) % 2, 2, 2);
		}
		Drawer_SetDrawColor(0, 0, 33);
		Drawer_FillRect(-16, 554 - attacker->attackAnimTimer * 3, 672, 160);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 212) {
		for (int i = 0; i <= 640; i += 32) {
			Drawer_DrawSprite(SPR_spark_tsunami, i, 338 - (attacker->attackAnimTimer - 72) * 12, (attacker->attackAnimTimer / 4) % 2, 2, 2);
		}
		Drawer_SetDrawColor(0, 0, 33);
		if (attacker->attackAnimTimer < 100) {
			Drawer_FillRect(-16, 338 - (attacker->attackAnimTimer - 72) * 12, 672, 560);
		}
		else {
			Drawer_FillRect(-16, -16, 672, 512);
		}
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 236) {
		for (int i = 0; i <= 640; i += 32) {
			Drawer_DrawSprite(SPR_spark_tsunami, i, (attacker->attackAnimTimer - 212) * 24, (attacker->attackAnimTimer / 4) % 2, 2, 2);
		}
		Drawer_SetDrawColor(0, 0, 33);
		Drawer_FillRect(-16, (attacker->attackAnimTimer - 212) * 24, 672, 512);
		Drawer_SetDrawColor(255, 255, 255);
		
		/*float x = 640 - (attacker->attackAnimTimer - 106) * 48;
		if (attacker->attackAnimTimer >= 170)
			x = -32 - (attacker->attackAnimTimer - 170) * 48;
		else if (attacker->attackAnimTimer >= 120)
			x = -32;
		Drawer_SetDrawColor(0, 0, 95);
		Drawer_FillRect(x, 128, 672, 246);
		Drawer_SetDrawColor(63, 255, 255);
		Drawer_FillRect(x + 2, 128, 2, 246);
		for (int i = 128; i < 368; i += 2) {
			Drawer_SetDrawColor(0, 0, 191);
			Drawer_FillRect(x + 4 + Random_IRange(0, 1) * 2, i, 2, 2);
			Drawer_FillRect(x + 4 + Random_IRange(0, 4) * 2, i, 2 * Random_IRange(1, 2), 2);
			if (Random(1) < 0.5) Drawer_FillRect(x + 6 + Random_IRange(0, 350) * 2, i, 2 * Random_IRange(1, 8), 2);
		}*/
	}
}

void Action_AnimUpdate__39(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_aztecslice);
	}
}
void Action_AnimDraw__39(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		if (attacker->attackAnimTimer >= 2) Drawer_SetDrawColor(0, 0, 0);
		Drawer_DrawSprite(SPR_spark_slashhyper, target->x, target->y - 24, attacker->actionAttacks % 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, 2);
	}
}

void Action_AnimUpdate__40(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_boost);
		Audio_PlaySound(SND_weird1);
	}
}
void Action_AnimDraw__40(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(252, 155, 242);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 42) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 43) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 47) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__41(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(6);
	}
}
void Action_AnimDraw__41(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 191, 0);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__42(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_luxuryswing);
	}
}
void Action_AnimDraw__42(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_slashcamilla, target->x, target->y - 24, attacker->attackAnimTimer / 3, 2, 2);
	}
}

void Action_AnimUpdate__43(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer >= 1 && attacker->attackAnimTimer <= 40 && attacker->attackAnimTimer % 8 == 0) {
		Audio_PlaySound(SND_chess_check);
	}
	if (attacker->attackAnimTimer == 72) {
		Audio_PlaySound(SND_boost);
	}
}
void Action_AnimDraw__43(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 255, 0);
	if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y + 4, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y + 4, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 6, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y + 4, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 6, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 16, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 32) {
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y + 4, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 6, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 16, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 26, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 40) {
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y + 4, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 6, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 16, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 26, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 36, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 72) {
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y + 4, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 6, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 16, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 26, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 36, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_brickwall, target->x, target->y - 46, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 76) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 80) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 84) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 88) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimDraw__44(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 5) {
		Drawer_SetDrawColor(255, 0, 127);
		Drawer_DrawSprite(SPR_misc_ampbeam, attacker->x + attacker->facing * 52, attacker->y - 24, attacker->attackAnimTimer, attacker->facing * 640, 2);
		Drawer_DrawSprite(SPR_misc_ampbeamstart, attacker->x + attacker->facing * 52, attacker->y - 24, attacker->attackAnimTimer, attacker->facing * 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
}

void Action_AnimUpdate__45(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_nerf);
	}
}
void Action_AnimDraw__45(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 31, 31);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__46(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_nerf);
	}
}
void Action_AnimDraw__46(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(31, 31, 255);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__47(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 5 || attacker->attackAnimTimer == 40 || attacker->attackAnimTimer == 55) {
		Audio_PlaySound(SND_electric);
	}
	else if (attacker->attackAnimTimer == 61) {
		Audio_PlaySound(SND_sawkill);
		Battle_ShakeScreen(12);
	}
	else if (attacker->attackAnimTimer == 70) {
		Audio_PlaySound(SND_firemassattack);
		Battle_ShakeScreen(16);
	}
	else if (attacker->attackAnimTimer == 74) {
		attacker->state = FIGHTER_STATE_SPECIAL1;
	}
}
void Action_AnimDraw__47(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(0, 255, 255);
	if (attacker->attackAnimTimer < 60) {
		
	}
	else if (attacker->attackAnimTimer < 70) {
		Drawer_DrawSprite(SPR_misc_ampbeam, attacker->x + attacker->facing * 76, attacker->y - 24, (attacker->attackAnimTimer - 60) / 2, attacker->facing * 640, 2);
		Drawer_DrawSprite(SPR_misc_ampbeamstart, attacker->x + attacker->facing * 76, attacker->y - 24, (attacker->attackAnimTimer - 60) / 2, attacker->facing * 2, 2);
	}
	
	if (attacker->attackAnimTimer < 70) {
		
	}
	else if (attacker->attackAnimTimer < 74) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 78) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 82) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 4, 4);
	}
	else if (attacker->attackAnimTimer < 86) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 4, 4);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__48(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_shards);
	}
}
void Action_AnimDraw__48(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_slashicely, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashicely, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_slashicely, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_slashicely, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_slashicely, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_DrawSprite(SPR_spark_slashicely, target->x, target->y - 24, 5, 2, 2);
	}
}

void Action_AnimUpdate__49(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_beamsword);
	}
}
void Action_AnimDraw__49(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_spark_slashamp, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_slashamp, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashamp, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_slashamp, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_spark_slashamp, target->x, target->y - 24, 4, 2, 2);
	}
}

void Action_AnimUpdate__50(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 3) {
		attacker->y = 168;
		attacker->facing = -attacker->facing;
		attacker->state = FIGHTER_STATE_RUN;
	}
	else if (attacker->attackAnimTimer == 8) {
		Fighter_MoveTo(attacker, target->x + 6 * target->facing, target->y - 16, PointDistance(attacker->x, attacker->y, target->x + 6 * target->facing, target->y - 16) / 6, 0);
	}
	else if (attacker->attackAnimTimer == 15) {
		attacker->x = target->x - 4 * target->facing;
		attacker->y = target->y;
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(6);
		attacker->state = FIGHTER_STATE_ATTACK1;
	}
	else if (attacker->attackAnimTimer >= 16 && attacker->attackAnimTimer <= 19) {
		attacker->x -= 12 * target->facing;
	}
	else if (attacker->attackAnimTimer == 31) {
		Fighter_MoveTo(attacker, attacker->xStart, attacker->yStart, 64, 0);
		attacker->facing = -attacker->facing;
		attacker->state = FIGHTER_STATE_RUN;
	}
}
void Action_AnimDraw__50(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 0, 0);
	if (attacker->attackAnimTimer < 15) {
		
	}
	else if (attacker->attackAnimTimer < 19) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 23) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 27) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 31) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__51(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer >= 42 && attacker->attackAnimTimer <= 120 && attacker->attackAnimTimer % 5 == 0) {
		Battle_CreateSpark(7, 160 + (1 - attacker->side) * 320 + Random_IRange(-64, 64), 304 + Random_IRange(-64, 64), 0);
		Battle_ShakeScreen(28);
		Audio_PlaySound(SND_explode);
	}
}
void Action_AnimDraw__51(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 32) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, 255 - attacker->attackAnimTimer * 7, 255 - attacker->attackAnimTimer * 7);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (attacker->attackAnimTimer < 120) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (attacker->attackAnimTimer < 141) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, (attacker->attackAnimTimer - 120) * 12, (attacker->attackAnimTimer - 120) * 12);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
}

void Action_AnimDraw__52(Fighter* attacker, Fighter* target) {
	for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
		Fighter* fighter = &battle.fighters[i];
		if (!fighter->enabled || !fighter->alive) continue;
		
		if (attacker->attackAnimTimer < 3) {
			Drawer_DrawSprite(SPR_spark_vinespike, fighter->x, fighter->y, 0, 2, 2);
		}
		else if (attacker->attackAnimTimer < 6) {
			Drawer_DrawSprite(SPR_spark_vinespike, fighter->x, fighter->y, 1, 2, 2);
		}
		else if (attacker->attackAnimTimer < 9) {
			Drawer_DrawSprite(SPR_spark_vinespike, fighter->x, fighter->y, 2, 2, 2);
		}
		else if (attacker->attackAnimTimer < 13) {
			Drawer_DrawSprite(SPR_spark_vinespike, fighter->x, fighter->y, 3, 2, 2);
		}
		else if (attacker->attackAnimTimer < 15) {
			Drawer_DrawSprite(SPR_spark_vinespike, fighter->x, fighter->y, 2, 2, 2);
		}
		else if (attacker->attackAnimTimer < 17) {
			Drawer_DrawSprite(SPR_spark_vinespike, fighter->x, fighter->y, 1, 2, 2);
		}
		else if (attacker->attackAnimTimer < 19) {
			Drawer_DrawSprite(SPR_spark_vinespike, fighter->x, fighter->y, 0, 2, 2);
		}
	}
}

void Action_AnimUpdate__53(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 5) {
		Audio_PlaySound(SND_elevator);
	}
	
	if (attacker->attackAnimTimer >= 4 && attacker->attackAnimTimer <= 54) {
		Battle_ShakeScreen(7 + (attacker->attackAnimTimer - 4) / 3);
	}
	if (attacker->attackAnimTimer == 50) {
		Audio_PlaySound(SND_thunder);
	}
	if (attacker->attackAnimTimer == 55) {
		Audio_PlaySound(SND_thunder);
		Battle_ShakeScreen(70);
	}
}

void Action_AnimUpdate__54(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 4 || attacker->attackAnimTimer == 12 || attacker->attackAnimTimer == 20) {
		Audio_PlaySound(SND_nerf);
	}
	if (attacker->attackAnimTimer == 40) {
		Audio_PlaySound(SND_sawkill);
		Battle_ShakeScreen(8);
	}
}
void Action_AnimDraw__54(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(127, 0, 63);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x - 24, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_spark, target->x + 24, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 48, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 32) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 36) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 4, 4);
	}
	else if (attacker->attackAnimTimer < 40) {
		Drawer_DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 4, 4);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__55(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_nerf);
		Audio_PlaySound(SND_electric);
	}
}
void Action_AnimDraw__55(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 255, 0);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__56(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_freeze);
		Audio_PlaySound(SND_absorb);
	}
	if (attacker->attackAnimTimer >= 4 && attacker->attackAnimTimer <= 58) {
		Battle_ShakeScreen(8);
	}
	if (attacker->attackAnimTimer == 84) {
		Battle_ShakeScreen(16);
		Audio_PlaySound(SND_shards);
	}
}
void Action_AnimDraw__56(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 54) {
		
	}
	else if (attacker->attackAnimTimer < 84) {
		Drawer_DrawSprite(SPR_spark_superfreeze, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 88) {
		Drawer_DrawSprite(SPR_spark_superfreeze, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 92) {
		Drawer_DrawSprite(SPR_spark_superfreeze, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 96) {
		Drawer_DrawSprite(SPR_spark_superfreeze, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 100) {
		Drawer_DrawSprite(SPR_spark_superfreeze, target->x, target->y - 24, 4, 2, 2);
	}
	
	Drawer_SetDrawColor(0, 191, 255);
	if (attacker->attackAnimTimer < 50) {
		Drawer_DrawSprite(SPR_spark_snow, target->x + 18 - 36 * (attacker->attackAnimTimer % 16 < 8), target->y - 6 - 36 * (attacker->attackAnimTimer % 16 < 4 || attacker->attackAnimTimer % 16 >= 12), 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_snow, target->x + 18 - 36 * ((attacker->attackAnimTimer + 8) % 16 < 8), target->y - 6 - 36 * ((attacker->attackAnimTimer + 8) % 16 < 4 || (attacker->attackAnimTimer + 8) % 16 >= 12), 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 54) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 58) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 62) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 2, 4, 4);
	}
	else if (attacker->attackAnimTimer < 66) {
		Drawer_DrawSprite(SPR_spark_snow, target->x, target->y - 24, 3, 4, 4);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__57(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_absorb);
	}
	if (attacker->attackAnimTimer >= 2 && attacker->attackAnimTimer <= 54) {
		Battle_ShakeScreen(2);
	}
	if (attacker->attackAnimTimer == 56) {
		Audio_PlaySound(SND_crusherhit2);
		Audio_PlaySound(SND_shards);
	}
}
void Action_AnimDraw__57(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 55) {
		
	}
	else if (attacker->attackAnimTimer < 57) {
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 100) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			Drawer_DrawSprite(SPR_misc_hellspike, fighter->x, fighter->y, 0, 2, 2);
		}
	}
}

void Action_AnimUpdate__58(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_gunfire2);
		Audio_PlaySound(SND_gunfire2);
		Audio_PlaySound(SND_thunder);
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(70);
		for (int i = 0; i < 4; i++) {
			Battle_CreateSpark(1, 320 + Random_IRange(-288, 288), 240 + Random_IRange(-128, 128), 0);
		}
	}
	else if (attacker->attackAnimTimer == 3) {
		attacker->tempVars[0].f = attacker->x;
		attacker->tempVars[1].f + attacker->y;
		if (attacker->actionAttacks == 19) {
			attacker->x = attacker->xStart;
			attacker->y = attacker->yStart;
		}
		else {
			switch (attacker->actionAttacks % 3) {
				case 0:
					attacker->x = 128 + Random_IRange(-64, 64);
					attacker->y = 240 + Random_IRange(-128, 128);
					break;
				case 1:
					attacker->x = 512 + Random_IRange(-64, 64);
					attacker->y = 240 + Random_IRange(-128, 128);
					break;
				case 2:
					attacker->x = 320 + Random_IRange(-64, 64);
					attacker->y = 240 + Random_IRange(-160, 160);
					break;
			}
		}
	}
}
void Action_AnimDraw__58(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 1) {
		
	}
	else if (attacker->attackAnimTimer < 3) {
		Drawer_FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	else if (attacker->attackAnimTimer < 5) {
		float distance = PointDistance(attacker->tempVars[0].f, attacker->tempVars[1].f, attacker->x, attacker->y);
		float direction = PointDirection(attacker->tempVars[0].f, attacker->tempVars[1].f, attacker->x, attacker->y);
		
		float x = attacker->tempVars[0].f;
		float y = attacker->tempVars[1].f;
		for (float i = 0.f; i < distance; i += 1.f) {
			Drawer_SetDrawColor(127 + (int)(cosf(i / 6.f) * 127), 127 + (int)(cosf(i / 6.f + PI / 1.5f) * 127), 127 + (int)(cosf(i / 6.f + 2.f * PI / 1.5f) * 127));
			Drawer_FillRect(x - 1, y - 1, 3, 3);
			Drawer_FillRect(x - 1 + cosf(direction + PI / 2) * 18, y - 1 + sinf(direction + PI / 2) * 18, 3, 3);
			Drawer_FillRect(x - 1 + cosf(direction - PI / 2) * 18, y - 1 + sinf(direction - PI / 2) * 18, 3, 3);
			
			x += cosf(direction) * 1.f;
			y += sinf(direction) * 1.f;
		}
		Drawer_SetDrawColor(255, 255, 255);
		
		x = attacker->tempVars[0].f;
		y = attacker->tempVars[1].f;
		for (float i = 0.f; i < distance; i += 1.f) {
			Drawer_FillRect(x, y, 1, 1);
			Drawer_FillRect(x + cosf(direction + PI / 2) * 18, y + sinf(direction + PI / 2) * 18, 1, 1);
			Drawer_FillRect(x + cosf(direction - PI / 2) * 18, y + sinf(direction - PI / 2) * 18, 1, 1);
			
			x += cosf(direction) * 1.f;
			y += sinf(direction) * 1.f;
		}
	}
}

void Action_AnimUpdate__59(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 12) {
		Battle_CreateSpark(7, target->x, target->y + 8, 0);
		Battle_ShakeScreen(28);
		Audio_PlaySound(SND_explode);
		Audio_PlaySound(SND_gunfire2);
	}
}
void Action_AnimDraw__59(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 127, 0);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 2, 4, 4);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__60(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_shadyboost);
	}
}
void Action_AnimDraw__60(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(127, 31, 127);
	if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 22) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 34) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 44) {
		Drawer_SetDrawColor(255, 31, 255);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 48) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 67) {
		Drawer_DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__61(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 9) {
		Audio_PlaySound(SND_slap);
	}
	if (attacker->attackAnimTimer == 10) {
		Audio_PlaySound(SND_goner);
	}
}
void Action_AnimDraw__61(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_misc_pandadart, attacker->x + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 10, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 10, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_misc_pandadart, target->x + target->facing * 6, target->y - 24, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 14) {
		Drawer_SetDrawColor(0, 0, 255);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_SetDrawColor(0, 0, 255);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 22) {
		Drawer_SetDrawColor(0, 0, 255);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 26) {
		Drawer_SetDrawColor(0, 0, 255);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 30) {
		Drawer_SetDrawColor(0, 0, 255);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 34) {
		Drawer_SetDrawColor(0, 0, 255);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
}

void Action_AnimUpdate__62(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_beamsword);
	}
}
void Action_AnimDraw__62(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(0, 255, 0);
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 4, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__63(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_beamsword);
	}
}
void Action_AnimDraw__63(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(0, 0, 255);
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_spark_slashbeam, target->x, target->y - 24, 4, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__64(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_birchswing1);
	}
}
void Action_AnimDraw__64(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_spark_slashmaline, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_slashmaline, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashmaline, target->x, target->y - 24, 2, 2, 2);
	}
}

void Action_AnimUpdate__65(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_birchswing2);
	}
	if (attacker->attackAnimTimer == 6 || attacker->attackAnimTimer == 9 || attacker->attackAnimTimer == 12) {
		Audio_PlaySound(SND_birchhit2);
		Battle_ShakeScreen(6);
	}
}
void Action_AnimDraw__65(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_DrawSprite(SPR_spark_slashcory, target->x, target->y - 24, 5, 2, 2);
	}
}

void Action_AnimUpdate__66(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 2) {
		Audio_PlaySound(SND_thunder);
		Audio_PlaySound(SND_beamsword);
	}
	if (attacker->attackAnimTimer == 14) {
		Battle_ShakeScreen(18);
		Audio_PlaySound(SND_crusherhit2);
	}
}
void Action_AnimDraw__66(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 0, 0);
	if (attacker->attackAnimTimer < 4) {
		int x = target->x;
		for (int y = target->y; y > 128; y -= 2) {
			Drawer_SetDrawColor(159, 0, 0);
			Drawer_FillRect(x - 9, y - 1, 18, 2);
			Drawer_SetDrawColor(255, 0, 0);
			Drawer_FillRect(x - 5, y - 1, 10, 2);
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_FillRect(x - 1, y - 1, 2, 2);
			x += Random_IRange(-1, 1) * 2;
		}
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_SetDrawAlpha(63);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawAlpha(255);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 14) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__67(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 2) {
		Audio_PlaySound(SND_beamsword);
		Audio_PlaySound(SND_shards);
		Audio_PlaySound(SND_charge);
	}
	if (attacker->attackAnimTimer == 6) {
		Battle_ShakeScreen(18);
		Audio_PlaySound(SND_gunfire2);
	}
}
void Action_AnimDraw__67(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(63, 63, 63);
	if (attacker->attackAnimTimer < 2) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, -2, 2);
	}
	else if (attacker->attackAnimTimer < 14) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, -2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, -2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__68(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 4) {
		Audio_PlaySound(SND_beamsword);
	}
	if (attacker->attackAnimTimer == 10) {
		Audio_PlaySound(SND_deflect);
		Audio_PlaySound(SND_crusherhit2);
		Audio_PlaySound(SND_shards);
		Battle_ShakeScreen(58);
	}
}
void Action_AnimDraw__68(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 8) {
		
	}
	else if (attacker->attackAnimTimer < 10) {
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackAnimTimer < 80) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled) continue;
			
			Drawer_SetDrawColor(255, 0, 0);
			if (attacker->attackAnimTimer < 14) {
				Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, 2, 2);
			}
			else if (attacker->attackAnimTimer < 18) {
				Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, 2, 2);
			}
			else if (attacker->attackAnimTimer < 22) {
				Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, 2);
			}
			Drawer_SetDrawColor(255, 255, 255);
			
			Drawer_DrawSprite(SPR_misc_hellspike, fighter->x, fighter->y + 16, 0, 2, 2);
			Drawer_DrawSprite(SPR_misc_hellspike, fighter->x - 48, fighter->y - 16, 0, 2, 2);
			Drawer_DrawSprite(SPR_misc_hellspike, fighter->x + 48, fighter->y - 16, 0, 2, 2);
		}
	}
}

void Action_AnimUpdate__69(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_beamsword);
	}
	if (attacker->attackAnimTimer == 4) {
		Battle_ShakeScreen(12);
		Audio_PlaySound(SND_electric);
		Audio_PlaySound(SND_thunder);
	}
}
void Action_AnimDraw__69(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(255, 0, 255);
	if (attacker->attackAnimTimer < 4) {
		Drawer_SetDrawColor(0, 0, 0);
		Drawer_SetDrawAlpha(63);
		Drawer_FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Drawer_SetDrawAlpha(255);
		Drawer_SetDrawColor(255, 0, 255);
		Drawer_DrawSprite(SPR_spark_slashhyper, target->x, target->y - 24, attacker->actionAttacks % 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_slashultra, target->x, target->y - 24, 2, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__70(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer >= 42 && attacker->attackAnimTimer <= 140 && attacker->attackAnimTimer % 3 == 0) {
		Battle_CreateSpark(17, 480 - (1 - attacker->side) * 320 + Random_IRange(-128, 128), Random_IRange(-96, -64), 0);
		int sparkId = battle.sparkCounter - 1;
		if (sparkId < 0) sparkId += OBJECT_COUNT_MAX;
		
		battle.sparks[sparkId].xVel = Random_Range(22, 26) * attacker->facing;
		battle.sparks[sparkId].yVel = 32;
		Audio_PlaySound(SND_gunfire);
	}
}
void Action_AnimDraw__70(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 32) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, 255 - attacker->attackAnimTimer * 7, 255);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (attacker->attackAnimTimer < 180) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, 0, 255);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
	else if (attacker->attackAnimTimer < 201) {
		Drawer_SetDrawBlend(BLENDMODE_MUL);
		Drawer_SetDrawColor(255, (attacker->attackAnimTimer - 180) * 12, 255);
		Drawer_FillRect(-40, -40, SCREEN_WIDTH + 80, SCREEN_HEIGHT + 80);
		Drawer_SetDrawColor(255, 255, 255);
		Drawer_SetDrawBlend(BLENDMODE_BLEND);
	}
}

void Action_AnimUpdate__71(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Battle_CreateSpark(19, 192 + (1 - attacker->side) * 256 + Random_IRange(-184, 184), 320, 0);
		Audio_PlaySound(SND_minigun);
		Audio_PlaySound(SND_electric);
		Audio_PlaySound(SND_thunder);
		Battle_ShakeScreen(12);
	}
}

void Action_AnimUpdate__72(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_explode);
		Battle_ShakeScreen(28);
	}
}
void Action_AnimDraw__72(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		Drawer_DrawSprite(SPR_spark_ultlulubeam, attacker->x + attacker->facing * 28, attacker->y - 24, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		Drawer_DrawSprite(SPR_spark_ultlulubeam, attacker->x + attacker->facing * 28, attacker->y - 24, 1, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		Drawer_DrawSprite(SPR_spark_ultlulubeam, attacker->x + attacker->facing * 28, attacker->y - 24, 2, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__73(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1 || attacker->attackAnimTimer == 7 || attacker->attackAnimTimer == 13 || attacker->attackAnimTimer == 19) {
		Audio_PlaySound(SND_boost);
	}
}
void Action_AnimDraw__73(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(31, 31, 31);
	for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
		Fighter* fighter = &battle.fighters[i];
		if (!fighter->enabled || !fighter->alive) continue;
		
		if (attacker->attackAnimTimer < 4) {
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 0, 2, 2);
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 0, 2, 2);
		}
		else if (attacker->attackAnimTimer < 8) {
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 1, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 0, 2, 2);
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 1, 2, 2);
		}
		else if (attacker->attackAnimTimer < 12) {
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 2, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 1, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 0, 2, 2);
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
		else if (attacker->attackAnimTimer < 16) {
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 3, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 2, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 1, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 0, 2, 2);
			Drawer_DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
		else if (attacker->attackAnimTimer < 20) {
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 3, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 2, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 1, 2, 2);
		}
		else if (attacker->attackAnimTimer < 24) {
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 3, 2, 2);
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 2, 2, 2);
		}
		else if (attacker->attackAnimTimer < 28) {
			Drawer_DrawSprite(SPR_spark_boost, fighter->x, fighter->y, 3, 2, 2);
		}
	}
	Drawer_SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__74(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		Audio_PlaySound(SND_nerf);
		Audio_PlaySound(SND_electric);
	}
}
void Action_AnimDraw__74(Fighter* attacker, Fighter* target) {
	Drawer_SetDrawColor(31, 255, 31);
	if (attacker->attackAnimTimer < 4) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		Drawer_DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		Drawer_DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	Drawer_SetDrawColor(255, 255, 255);
}
