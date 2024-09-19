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
	SetString(action->name, "Ruthless Swinging");
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
	action->armorOnlyId = 15;
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
	action->cost = 11;
	action->armorOnlyId = 15;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 5;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 8;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 8;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_BIND;
	action->vars[3].i = 8;
	
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
	action->power[0] = 9;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 9;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_FEEBLE;
	action->vars[3].i = 10;
	
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
	action->vars[3].i = 7;
	
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
	action->power[0] = 6;
	action->powerRepeat = 6;
	action->attackMultiplier = 1;
	action->vars[0].i = 6;
	
	action = &actionData[18];
	SetString(action->name, "Fire Chop");
	action->descriptionDialogId = 5018;
	action->cost = 7;
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
	action->cost = 15;
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
	action->cost = 18;
	action->priority = 1;
	action->codeId = 9;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 16;
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
	
	action = &actionData[28];
	SetString(action->name, "Blaze Oblivion");
	action->descriptionDialogId = 5028;
	action->cost = 30;
	action->priority = 1;
	action->codeId = 14;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMYPARTY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
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
	action->cost = 6;
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
	action->vars[3].i = 8;
	
	action = &actionData[31];
	SetString(action->name, "Just Dancing");
	action->descriptionDialogId = 5031;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 16;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3; action->power[1] = 1;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 3;
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
	action->vars[3].i = 2;
	
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
	action->vars[3].i = 3;
	
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
	action->vars[3].i = 8;
	
	action = &actionData[35];
	SetString(action->name, "Shuriken Throw");
	action->descriptionDialogId = 5035;
	action->cost = 4;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 6;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 3;
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
	action->cost = 12;
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
	action->cost = 10;
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
	
	action = &actionData[45];
	SetString(action->name, "Blink Speed");
	action->descriptionDialogId = 5045;
	action->cost = 20;
	action->priority = 2;
	action->codeId = 21;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 7;
	action->attackMultiplier = 1;
	action->vars[0].i = 5;
	action->vars[1].i = 0;
	
	action = &actionData[46];
	SetString(action->name, "Stun Shot");
	action->descriptionDialogId = 5046;
	action->cost = 18;
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
	
	action = &actionData[49];
	SetString(action->name, "Heavy Strike");
	action->descriptionDialogId = 5049;
	action->cost = 9;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 7;
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
	action->cost = 17;
	action->armorOnlyId = 39;
	action->priority = 2;
	action->codeId = 5;
	action->animationId = 14;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 14;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 14;
	action->vars[1].i = 2;
	action->vars[2].i = FIGHTER_STATUS_PARALYSIS;
	action->vars[3].i = 2;
	
	action = &actionData[54];
	SetString(action->name, "Breaking Beam");
	action->descriptionDialogId = 5054;
	action->cost = 99;
	action->armorOnlyId = 39;
	action->priority = 2;
	action->codeId = 26;
	action->animationId = 15;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 15;
	action->powerRepeat = 8;
	action->attackMultiplier = 1;
	action->vars[0].i = 15;
	
	action = &actionData[55];
	SetString(action->name, "Amp Charge");
	action->descriptionDialogId = 5055;
	action->cost = 0;
	action->priority = 1;
	action->codeId = 3;
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
	action->power[0] = 3;
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
	action->power[0] = 2;
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
	action->power[0] = 9;
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
	action->power[0] = 6; action->power[1] = 7; action->power[2] = 8; action->power[3] = 11;
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
	action->vars[1].i = 15;
	
	action = &actionData[69];
	SetString(action->name, "Setup Jab");
	action->descriptionDialogId = 5069;
	action->cost = 12;
	action->priority = 1;
	action->codeId = 15;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 4;
	action->vars[1].i = 1;
	action->vars[2].i = FIGHTER_STATUS_HASTE;
	action->vars[3].i = 20;
	
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
	action->vars[3].i = 8;
	
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
	action->power[0] = 8; action->power[1] = 8;
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
	action->power[0] = 11;
	action->attackMultiplier = 0.5;
	action->vars[0].i = 10;
	action->vars[1].i = FIGHTER_STATUS_BURN;
	action->vars[2].i = FIGHTER_STATUS_TIMEDBOMB;
	
	action = &actionData[80];
	SetString(action->name, "Air Smite");
	action->descriptionDialogId = 5080;
	action->cost = 38;
	action->priority = 1;
	action->codeId = 5;
	action->animationId = 27;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 4;
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
	action->cost = 3;
	action->priority = 3;
	action->codeId = 12;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ALLY;
	action->category = ACTIONCATEGORY_DEFENSIVE;
	action->attackMultiplier = 0;
	action->vars[0].i = FIGHTER_STATUS_GUARD;
	action->vars[1].i = 3;
	
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
	action->power[0] = 72;
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
	action->cost = 20;
	action->priority = 1;
	action->codeId = 43;
	action->animationId = -1;
	action->targetType = TARGETTYPE_ENEMY;
	action->category = ACTIONCATEGORY_ATTACK;
	action->power[0] = 14;
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
	action->vars[1].i = 15;
	
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
	action->attackMultiplier = 0;
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
	action->attackMultiplier = 0;
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
	action->attackMultiplier = 0;
	action->vars[0].i = 0;
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
	actionAnim->time = 7;
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
	actionAnim->time = 7;
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
	actionAnim->time = 7;
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
	if (!target->alive) return;
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
	
	damage -= target->defense;
	
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
	return power + attacker->actionAttackMultiplier * (attacker->attack + attacker->status[FIGHTER_STATUS_STRENGTH] - attacker->status[FIGHTER_STATUS_FEEBLE] - attacker->status[FIGHTER_STATUS_PARALYSIS]) / powerCount / attacker->actionPowerRepeat;
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
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__1(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
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
			
			PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__3(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_HealMP(attacker, attacker->actionVars[0].i);
			Fighter_HealHP(attacker, attacker->actionVars[1].i);
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
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
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
			
			if (attacker->actionAttacks % 2 == 0)
				attacker->state = FIGHTER_STATE_ATTACK3;
			else
				attacker->state = FIGHTER_STATE_ATTACK1;
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__11(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			Fighter_GainStatus(attacker, attacker->actionVars[0].i, attacker->actionVars[1].i, false);
			
			if (attacker->actionVars[0].i == FIGHTER_STATUS_GUARD) {
				attacker->state = FIGHTER_STATE_BLOCK;
			}
			else if (attacker->actionVars[0].i == FIGHTER_STATUS_COUNTER) {
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
			target->bodyguardId = attacker->id;
			Fighter_MoveTo(attacker, target->x + attacker->facing * 32, target->y, 8, 0);
			attacker->state = FIGHTER_STATE_RUN;
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
		}
	}
	
	return 0;
}



int Action_Update__14(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) {
		Action_BlockUpdate(attacker, target);
	}
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64) return 1;
		
		if (attacker->attackTimer == 4) {
			PlaySound(SND_firemassattack);
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
				Fighter_DealDamage(attacker, fighter, damageLocal, DAMAGE_FLAG_BLOCKABLE);
			}
		}
		
		if (attacker->attackTimer >= 52) {
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
			
			if (attacker->attackTimer == 63) {
				attacker->x = attacker->xStart;
				attacker->y = attacker->yStart;
			}
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
				
				PlaySound(SND_swing);
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
		SetDrawColor(255, 127, 0);
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer < 4) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 8) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
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
			
			PlaySound(SND_swing);
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
				
				Fighter_GainStatus(fighter, FIGHTER_STATUS_STRENGTH, 3, false);
				Fighter_GainStatus(fighter, FIGHTER_STATUS_HASTE, 3, false);
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
			
			PlaySound(SND_swing);
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
			PlaySound(SND_hit3);
		}
		if (attacker->attackTimer == 67 || attacker->attackTimer == 77) {
			target->x -= 2 * target->facing;
			PlaySound(SND_hit3);
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
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
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
				
				PlaySound(SND_swing);
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
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer < 8) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
}



int Action_Update__21(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer <= 4) Action_BlockUpdate(attacker, target);
	
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 44) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
			attacker->attackAnimTimer += 2;
		}
		if (attacker->attackTimer == 4) {
			int damage = attacker->speedRoll * attacker->actionAttackMultiplier;
			
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
			
			PlaySound(SND_swing);
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
			PlaySound(SND_firemassattack);
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
		SetDrawColor(255, 127, 0);
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		SetDrawColor(255, 255, 255);
	}
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 4) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
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
			
			PlaySound(SND_swing);
		}
	}
	
	return 0;
}



int Action_Update__26(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64) return 1;
		
		if (attacker->attackTimer == 2) {
			if (attacker->actionAttacks % 2 == 0) {
				int damage = Action_GetDamagePower(attacker, target);
				
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				Fighter_DealDamage(attacker, target, damage, 0);
			}
			
			attacker->actionAttacks++;
			
			PlaySound(SND_explode);
		}
		if (attacker->attackTimer == 6 && attacker->actionAttacks <= 15) {
			attacker->attackTimer = 1;
			attacker->readyTimer = -1;
			attacker->attackAnimTimer = 2;
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
			
			PlaySound(SND_gunfire);
			PlaySound(SND_firemassattack);
		}
		
		if (attacker->readyTimer == 1) {
			Fighter_MoveTo(attacker, attacker->x, target->y, 48, 0);
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
				PlaySound(SND_burn);
			}
		}
		else if (attacker->readyTimer == 120) {
			PlaySound(SND_mana);
		}
	}
	
	return 0;
}
void Action_Draw__26(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 0 && attacker->readyTimer < 120) {
		DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 40, attacker->y - 22, (300 - attacker->readyTimer / 8) % 3, 4, 4);
	}
	if (attacker->readyTimer >= 120 && attacker->readyTimer <= 122) {
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
			PlaySound(SND_firemassattack);
			
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
			
			PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__27(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	actionAnimDrawCode[attacker->actionTempAnimId](attacker, target);
	
	if (attacker->attackTimer >= 2 && attacker->attackTimer < 124) {
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	if (attacker->attackTimer >= 124 && attacker->attackTimer < 126) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer >= 126 && attacker->attackTimer < 130) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
}



int Action_Update__28(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 64) return 1;
		
		if (attacker->attackTimer == 1 && attacker->attackAnimTimer < attacker->attackAnimTime) {
			attacker->attackTimer--;
		}
		if (attacker->attackTimer == 4) {
			int damage = Action_GetDamagePower(attacker, target);
			
			if (target->status[FIGHTER_STATUS_FLOWER]) {
				damage += 80;
				PlaySound(SND_flower);
			}
			
			damage = Action_CalculateAttackPower(attacker, target, damage);
			
			Fighter_DealDamage(attacker, target, damage, 0);
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL1;
		
		if (Action_AttackUpdate(attacker, target) || attacker->readyTimer >= ACTION_DELAYTIME_MAX) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			PlaySound(SND_burn);
		}
	}
	
	return 0;
}



int Action_Update__29(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 67) return 1;
		
		if (attacker->attackTimer == 4) {
			PlaySound(SND_flower3);
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
				
				if (fighter->status[FIGHTER_STATUS_FLOWER]) {
					damageLocal += 6;
					PlaySoundInterrupt(SND_flower);
				}
				
				Fighter_DealDamage(attacker, fighter, damageLocal, 0);
			}
		}
		
		if (attacker->attackTimer == 27) {
			attacker->actionAttacks++;
			
			if (attacker->actionAttacks <= 7) {
				attacker->attackTimer = -1;
				attacker->readyTimer = 0;
			}
		}
	}
	else if (attacker->readyTimer >= 0) {
		if (attacker->actionAttacks == 0) attacker->state = FIGHTER_STATE_SPECIAL1;
		
		if (attacker->readyTimer >= 65) {
			Fighter_OnAttackSwing(attacker);
			attacker->readyTimer = -1;
			attacker->attackTimer = 0;
			attacker->attackAnimTimer = 0;
			attacker->attackAnimTime = actionAnimData[attacker->actionTempAnimId].time;
			
			attacker->state = FIGHTER_STATE_SPECIAL2;
			
			PlaySound(SND_swing);
		}
	}
	
	return 0;
}
void Action_Draw__29(Fighter* attacker, Fighter* target) {
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
		SetDrawColor(255, 255, 255);
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer < 4) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
			DrawSprite(SPR_spark_star, fighter->x, fighter->y - 24, 0, 8, 8);
		}
	}
	else if (attacker->attackTimer < 8) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
			DrawSprite(SPR_spark_star, fighter->x, fighter->y - 24, 1, 8, 8);
		}
	}
	else if (attacker->attackTimer < 12) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_star, fighter->x, fighter->y - 24, 2, 8, 8);
		}
	}
	else if (attacker->attackTimer < 16) {
		for (int i = iMin; i <= iMax; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_star, fighter->x, fighter->y - 24, 3, 8, 8);
		}
	}
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
			
			PlaySound(SND_swing);
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



int Action_Update__32(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 204) return 1;
		
		if (attacker->attackTimer == 1) {
			target->actionVars[0].i = audioSystem.soundFilterId;
			ApplySoundFilter(2);
		}
		if (attacker->attackTimer >= 1 && attacker->attackTimer < 64 && attacker->attackTimer % 4 == 1) {
			PlaySound(SND_burn);
		}
		if (attacker->attackTimer == 96) {
			ApplySoundFilter(target->actionVars[0].i);
		}
		
		if (attacker->attackTimer == 144) {
			PlaySound(SND_firemassattack);
			
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
					PlaySoundInterrupt(SND_flower);
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
			FillRect(0, Random_IRange(128, SCREEN_HEIGHT), SCREEN_WIDTH, 2);
			FillRect(0, Random_IRange(128, SCREEN_HEIGHT), SCREEN_WIDTH, 2);
			FillRect(0, Random_IRange(128, SCREEN_HEIGHT), SCREEN_WIDTH, 4);
		}
	}
	else if (attacker->attackTimer >= 142 && attacker->attackTimer < 144) {
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
			
			PlaySound(SND_swing);
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
			PlaySound(SND_minigunambience);
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
			Fighter_MoveTo(attacker, target->x + attacker->facing * 8, target->y, 24, 0);
			attacker->state = FIGHTER_STATE_ATTACK3;
		}
		if (attacker->attackTimer == 2) {
			if (attacker->moveTarget.enabled) attacker->attackTimer--;
			if ((attacker->facing > 0 && attacker->x >= target->x) || (attacker->facing < 0 && attacker->x <= target->x)) {
				int damage = Action_GetDamagePower(attacker, target);
				
				damage = Action_CalculateAttackPower(attacker, target, damage);
				
				Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[1].i, attacker->actionVars[0].i, false);
				Fighter_InflictStatusDodgable(attacker, target, attacker->actionVars[2].i, attacker->actionVars[0].i, false);
				Fighter_DealDamage(attacker, target, damage, DAMAGE_FLAG_BLOCKABLE | DAMAGE_FLAG_DODGABLE);
				
				Battle_CreateSpark(6, target->x, target->y - 24, 0);
				Battle_ShakeScreen(28);
				PlaySound(SND_explode);
				
				attacker->state = FIGHTER_STATE_SPECIAL2;
				attacker->attackTimer++;
				Fighter_MoveTo(attacker, target->x + attacker->facing * 48, target->y, 1, 0);
			}
		}
		if (attacker->attackTimer == 3 && attacker->moveTarget.enabled) {
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
			Battle_CreateSpark(6, 160 + Random_IRange(-64, 64), 304 + Random_IRange(-64, 64), 0);
			Battle_CreateSpark(6, 160 + 130 * cos((double)attacker->attackTimer / 2.5) + Random_IRange(-24, 24), 304 + 80 * cos((double)attacker->attackTimer / 3.5) + Random_IRange(-24, 24), 0);
			Battle_ShakeScreen(28);
			PlaySound(SND_explode);
		}
		
		if (attacker->attackTimer == 234) {
			attacker->y += 512;
			PlaySound(SND_firemassattack);
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
			
			PlaySound(SND_swing);
			attacker->y -= 512;
		}
	}
	
	return 0;
}
void Action_Draw__36(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer < 0) return;
	
	if (attacker->attackTimer < 4) {
		for (int x = attacker->x - 7; x <= attacker->x + 6; x += 4) {
			SetDrawColor(255, 255, 255);
			FillRect(x, 128, 2, attacker->y + 512 - 128);
		}
	}
	else if (attacker->attackTimer < 232) {
		
	}
	else if (attacker->attackTimer < 234) {
		SetDrawColor(255, 127, 0);
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer < 236) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 240) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
		}
	}
	
	if (attacker->attackAnimTimer < 234) {
		
	}
	else if (attacker->attackAnimTimer < 238) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, 160 + attacker->side * 320, 304, 0, 16, 16);
	}
	else if (attacker->attackAnimTimer < 242) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, 160 + attacker->side * 320, 304, 1, 16, 16);
	}
	else if (attacker->attackAnimTimer < 246) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, 160 + attacker->side * 320, 304, 2, 16, 16);
	}
	else if (attacker->attackAnimTimer < 250) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, 160 + attacker->side * 320, 304, 3, 16, 16);
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
		
		PlaySound(SND_neutralize);
	}
	
	return 0;
}



int Action_Update__38(Fighter* attacker, Fighter* target) {
	if (attacker->readyTimer >= 40) return 1;
	
	if (attacker->readyTimer >= 0) {
		if (attacker->readyTimer == 1) {
			attacker->state = FIGHTER_STATE_ATTACK3;
			if (!target->alive) {
				PlaySound(SND_reset);
				target->alive = true;
				target->state = FIGHTER_STATE_ATTACK1;
				Fighter_HealHP(target, attacker->actionVars[0].i);
				Fighter_HealMP(target, attacker->actionVars[1].i);
			}
			else {
				PlaySound(SND_dodge);
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
			
			PlaySound(SND_swing);
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
			
			PlaySound(SND_swing);
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
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 3, 2, 2);
		}
	}
	else if (attacker->attackTimer < 8) {
		for (int i = target->side * 8; i < target->side * 8 + 8; i++) {
			Fighter* fighter = &battle.fighters[i];
			if (!fighter->enabled || !fighter->alive) continue;
			
			DrawSprite(SPR_spark_spark, fighter->x, fighter->y - 24, 4, 2, 2);
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
		DrawSprite(SPR_spark_spark, attacker->x, attacker->y - 24, 3, 2, 2);
	}
	else if (attacker->attackTimer >= 4 && attacker->attackTimer < 8) {
		DrawSprite(SPR_spark_spark, attacker->x, attacker->y - 24, 4, 2, 2);
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
				PlaySound(SND_chess_move);
			}
		}
		if (attacker->attackTimer == 2) {
			PlaySound(SND_explode);
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
			PlaySound(SND_chess_move);
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
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackTimer < 8) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackTimer < 12) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackTimer < 16) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
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
			
			PlaySound(SND_swing);
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
		PlaySound(SND_neutralize);
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
		PlaySound(SND_flower2);
	}
	
	return 0;
}






int Action_Update__191(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 1660) return 1;
		
		if (attacker->attackTimer >= 15 && attacker->attackTimer <= 70) {
			if (attacker->attackTimer % 2 == 0) PlaySound(SND_crusherhit);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, SCREEN_WIDTH / 2 + 280 * cos((double)attacker->attackTimer / 1.38), SCREEN_HEIGHT / 2 + 150 * cos((double)attacker->attackTimer / 3.8879), 0);
		}
		if (attacker->attackTimer >= 100 && attacker->attackTimer <= 350) {
			if (attacker->attackTimer % 2 == 0) PlaySound(SND_crusherhit);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			Battle_CreateSpark(9900, SCREEN_WIDTH / 2 + 280 * cos((double)attacker->attackTimer / 3.38), SCREEN_HEIGHT / 2 + 200 * cos((double)attacker->attackTimer / 1.1879), 0);
		}
		if (attacker->attackTimer >= 400 && attacker->attackTimer <= 430) {
			Battle_ShakeScreen(10);
			if (attacker->attackTimer % 2 == 0) PlaySound(SND_crusherhit2);
			for (int i = 0; i < 8; i++) {
				Battle_CreateSpark(9901, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			}
		}
		if (attacker->attackTimer == 451) {
			PlaySound(SND_firemassattack);
			PlaySound(SND_crusherhit2);
			Battle_ShakeScreen(100);
		}
		if (attacker->attackTimer >= 510 && attacker->attackTimer <= 690 && attacker->attackTimer % 2 == 0) {
			attacker->state = FIGHTER_STATE_BLOCK;
			attacker->spriteId = SPR_misc_lulu_omega_rage;
			attacker->spriteFrame = 1;
			Battle_ShakeScreen(27);
			PlaySound(SND_gunshot);
			Battle_CreateSpark(9900, Random_Range(32, 288), Random_Range(128, SCREEN_HEIGHT - 128), 0);
		}
		if (attacker->attackTimer == 710) {
			PlaySound(SND_firemassattack);
		}
		if (attacker->attackTimer >= 710 && attacker->attackTimer <= 840 && attacker->attackTimer % 2 == 0) {
			Battle_ShakeScreen(12);
			PlaySound(SND_explode);
		}
		if (attacker->attackTimer >= 930 && attacker->attackTimer <= 1380) {
			Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
			battle.shakeTimer -= 20;
			if (attacker->attackTimer % 5 == 0) {
				Battle_ShakeScreen(40);
				PlaySound(SND_crusherhit);
				Battle_CreateSpark(9902, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
				Battle_CreateSpark(9903, 320, 240, 0);
				PlaySound(SND_crusherhit);
				Battle_CreateSpark(9903, 320, 240, 0);
			}
			Battle_CreateSpark(9904, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
		}
		
		if (attacker->attackTimer == 1440) {
			PlaySound(SND_firemassattack);
			PlaySound(SND_crusherhit2);
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
			PlayMusic(MUS_lastresort2);
			
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
	SetDrawColor(255, 255, 255);
	if (attacker->readyTimer >= 0 && attacker->readyTimer < 60) {
		SetDrawColor(0, 0, 0);
		SetDrawAlpha(attacker->readyTimer * 255 / 60);
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		SetDrawColor(255, 255, 255);
		SetDrawAlpha(255);
	}
	else if (attacker->attackTimer >= 0 && attacker->attackTimer < 451) {
		SetDrawColor(0, 0, 0);
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		SetDrawColor(255, 255, 255);
	}
	else if (attacker->attackTimer >= 510 && attacker->attackTimer <= 690) {
		for (int i = 0; i < 9; i++) {
			float angle = ((float)attacker->attackTimer * 18 + 40 * i) / 180 * PI;
			DrawSprite_Angle(SPR_misc_omegalulugun, attacker->x, attacker->y - 24, 0, 2, 2, angle / PI * 180);
		}
		DrawSprite_Angle(SPR_misc_omegalulugunfire, attacker->x + Random_Range(-8, 8), attacker->y - 24 + Random_Range(-8, 8), 0, 4, 4, Random_Range(-30, 30));
	}
	else if (attacker->attackTimer >= 691 && attacker->attackTimer <= 840) {
		DrawSprite(SPR_misc_omegalulucannon, attacker->x - 8, attacker->y - 64, 0, -2, 2);
		
		if (attacker->attackTimer >= 710) {
			DrawSprite(SPR_misc_ampbeam, attacker->x + attacker->facing * 118, attacker->y - 64, (1 + attacker->attackTimer / 2) % 3, attacker->facing * 640, 16);
			DrawSprite(SPR_misc_ampbeamstart, attacker->x + attacker->facing * 118, attacker->y - 64, (1 + attacker->attackTimer / 2) % 3, attacker->facing * 16, 16);
		}
	}
	else if (attacker->attackTimer >= 841 && attacker->attackTimer < 930) {
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	else if (attacker->attackTimer >= 930 && attacker->attackTimer <= 1380) {
		SetDrawColor(0, 0, 0);
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		SetDrawColor(255, 255, 255);
		
		float x = 0;
		float y = 0;
		float scale = 2;
		if ((battle.globalTimer % 12) / 4 == 2)
			scale = 8;
		else if ((battle.globalTimer % 12) / 4 == 1)
			scale = 4;
		
		SetDrawColor(0, 15, 31);
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		
		SetDrawBlend(SDL_BLENDMODE_ADD);
		SetDrawColor(0, 23, 79);
		for (int j = -9; j < 16; j++)
		for (int i = -9; i < 14; i++) {
			DrawSprite(SPR_misc_bossbattlebg_0, x + 64*i*scale - (battle.globalTimer % 64) / 4, y + 64*j*scale - (battle.globalTimer % 64) / 4, 0, scale, scale);
		}
		
		SetDrawColor(0, 23, 79);
		for (int j = -9; j < 20; j++)
		for (int i = -9; i < 17; i++) {
			DrawSprite(SPR_misc_bossbattlebg_1, -x + 64*i*scale + (battle.globalTimer % 64) / 2, y + 64*j*scale - (battle.globalTimer % 64) / 2, 0, scale, scale);
		}
		SetDrawBlend(SDL_BLENDMODE_BLEND);
		SetDrawColor(255, 255, 255);
		
		DrawFighterChar(1, 1, FIGHTER_STATE_HURT, 320, 280, 2, 2, FACING_RIGHT);
		
	}
	else if (attacker->attackTimer > 1380 && attacker->attackTimer < 1440) {
		SetDrawColor(0, 0, 0);
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
}






int Action_Update__192(Fighter* attacker, Fighter* target) {
	if (attacker->attackTimer >= 0) {
		if (attacker->attackTimer >= 2870) return 1;
		
		if (attacker->attackTimer >= 2 && attacker->attackTimer <= 20) {
			PlaySound(SND_crusherhit);
			for (int i = 0; i < 6; i++) {
				Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
				Battle_CreateSpark(9900, Random_Range(64, SCREEN_WIDTH - 64), Random_Range(96, SCREEN_HEIGHT - 96), 0);
				Battle_CreateSpark(9900, SCREEN_WIDTH / 2 + 280 * cos((double)attacker->attackTimer / 1.38), SCREEN_HEIGHT / 2 + 150 * cos((double)attacker->attackTimer / 3.8879), 0);
			}
		}
		if (attacker->attackTimer == 24 || attacker->attackTimer == 28) {
			PlaySound(SND_crusherhit2);
			PlaySound(SND_crusherhit2);
			PlaySound(SND_crusherhit2);
			PlaySound(SND_subspace_transform);
			for (int i = 0; i < 10; i++) {
				Battle_CreateSpark(9909, 5 + i * 70, 480, 0);
			}
		}
		if ((attacker->attackTimer >= 98 && attacker->attackTimer <= 160) || (attacker->attackTimer >= 179 && attacker->attackTimer <= 220)) {
			if (attacker->attackTimer % 2 == 0) PlaySound(SND_crusherhit);
			if (attacker->attackTimer % 2 == 1) PlaySound(SND_crusherhit3);
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
			PlaySound(SND_crusherhit2);
			for (int i = 0; i < 16; i++) {
				Battle_CreateSpark(9901, Random_Range(32, SCREEN_WIDTH - 32), Random_Range(32, SCREEN_HEIGHT - 32), 0);
				Battle_CreateSpark(9909, Random_Range(4, SCREEN_WIDTH - 4), 480, 0);
			}
		}
		if (attacker->attackTimer == 225) {
			attacker->spriteId = SPR_misc_lulu_subspace_rage;
			attacker->spriteFrame = 1;
			PlaySound(SND_firemassattack);
			PlaySound(SND_crusherhit2);
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
				PlaySound(SND_crusherhit3);
				Battle_ShakeScreen(12);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
				PlaySound(SND_crusherhit3);
			}
		}
		if (attacker->attackTimer == 320) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, target->x + attacker->facing * 24, target->y, 24, 0);
		}
		if (attacker->attackTimer == 323) {
			Battle_ShakeScreen(8);
			PlaySound(SND_crusherhit);
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
				PlaySound(SND_explode);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
			Battle_ShakeScreen(16);
			PlaySound(SND_crusherhit4);
			PlaySound(SND_explode);
			Battle_CreateSpark(6, battle.fighters[0].x + Random_IRange(-4, 4), battle.fighters[0].y - 24 + Random_IRange(-4, 4), 0);
		}
		if (attacker->attackTimer == 441) {
			Battle_ShakeScreen(8);
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_crusherhit);
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
				PlaySound(SND_explode);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
			Battle_ShakeScreen(16);
			PlaySound(SND_crusherhit4);
			PlaySound(SND_explode);
			Battle_CreateSpark(6, battle.fighters[0].x + Random_IRange(-4, 4), battle.fighters[0].y - 24 + Random_IRange(-4, 4), 0);
		}
		if (attacker->attackTimer == 568) {
			attacker->state = FIGHTER_STATE_RUN;
			Fighter_MoveTo(attacker, target->x + attacker->facing * 24, target->y, 24, 0);
		}
		if (attacker->attackTimer == 571) {
			Battle_ShakeScreen(8);
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_crusherhit);
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
			PlaySound(SND_firemassattack);
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
				PlaySound(SND_explode);
				PlaySound(SND_crusherhit4);
			}
			else {
				attacker->state = FIGHTER_STATE_ATTACK1;
			}
			Battle_ShakeScreen(16);
			PlaySound(SND_crusherhit3);
			Battle_CreateSpark(6, battle.fighters[0].x + Random_IRange(-4, 4), battle.fighters[0].y - 24 + Random_IRange(-4, 4), 0);
		}
		
		if (attacker->attackTimer >= 770 && attacker->attackTimer < 860) {
			int timer = (attacker->attackTimer - 770) % 30;
			if (timer == 0) {
				PlaySound(SND_crusherhit);
				Fighter_MoveTo(target, 640 - 96, battle.fighters[0].yStart, 30, 0);
			}
			if (timer % 2 == 0) {
				Battle_CreateSpark(9907, battle.fighters[0].x, 480, 0);
				Battle_CreateSpark(9907, battle.fighters[0].x + 24, 480, 0);
				Battle_CreateSpark(9907, battle.fighters[0].x - 24, 480, 0);
				PlaySound(SND_thunder);
				Battle_ShakeScreen(3);
			}
			if (timer == 15) {
				PlaySound(SND_crusherhit);
				Fighter_MoveTo(target, 96, battle.fighters[0].yStart, 30, 0);
			}
			Battle_Camera_MoveTo(battle.fighters[0].x, battle.fighters[0].y - 20, 3, 29);
		}
		
		if (attacker->attackTimer == 860) {
			PlaySound(SND_firemassattack);
			PlaySound(SND_firemassattack);
			PlaySound(SND_firemassattack);
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
			PlayMusic(MUS_lastresort2_pitchdown);
			attacker->spriteFrame = 0;
		}
		if (attacker->attackTimer > 960 && attacker->attackTimer < 1880) {
			if (attacker->attackTimer % 48 == 0) {
				Battle_CreateSpark(9910, attacker->x, attacker->y - 24, 0);
				PlaySound(SND_charge);
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
			PlaySound(SND_subspace_transform2);
		}
		if (attacker->attackTimer == 1930) {
			attacker->spriteFrame = 1;
		}
		if (attacker->attackTimer >= 1930 && attacker->attackTimer < 2650) {
			if (attacker->attackTimer % 32 == 0) {
				PlaySound(SND_subspace_transform);
				for (int i = 0; i < 5; i++) {
					Battle_CreateSpark(9908, battle.fighters[0].x - 80 + i * 40, 480, 0);
				}
			}
			if (attacker->attackTimer >= 2050 && attacker->attackTimer % 14 == 0) {
				PlaySound(SND_explode);
				for (int i = 0; i < 6; i++) {
					Battle_CreateSpark(9908, i * 128, 480, 0);
				}
			}
			if (attacker->attackTimer >= 2300 && attacker->attackTimer % 6 == 0) {
				PlaySound(SND_crusherhit2);
				for (int i = 0; i < 5; i++) {
					Battle_CreateSpark(9908, 20 + i * 150, 400, 0);
					Battle_CreateSpark(9908, 20 + i * 150, 280, 0);
				}
				for (int i = 0; i < 5; i++) {
					Battle_CreateSpark(9909, 40 + i * 140, 360, 0);
				}
			}
			if (attacker->attackTimer >= 2500 && attacker->attackTimer % 2 == 0) {
				PlaySound(SND_crusherhit);
				PlaySound(SND_crusherhit3);
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
				PlaySound(SND_subspace_transform);
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
		SetDrawColor(0, 0, 0);
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
		SetDrawColor(255, 255, 255);
	}
	if (attacker->attackTimer >= 859 && attacker->attackTimer < 861) {
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	if (attacker->attackTimer >= 1930 && attacker->attackTimer < 1932) {
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
	if (attacker->attackTimer >= 2660 && attacker->attackTimer < 2720) {
		FillRect(-128, -128, SCREEN_WIDTH + 256, SCREEN_HEIGHT + 256);
	}
}






void Action_AnimUpdate__0(Fighter* attacker, Fighter* target) {
	
}
void Action_AnimDraw__0(Fighter* attacker, Fighter* target) {
	
}

void Action_AnimDraw__1(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_punch, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite(SPR_spark_punch, target->x, target->y - 24, 1, 2, 2);
	}
}

void Action_AnimDraw__2(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 4, 2, 2);
	}
}

void Action_AnimDraw__3(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimDraw__4(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		DrawSprite(SPR_spark_vinespike, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_spark_vinespike, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		DrawSprite(SPR_spark_vinespike, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 13) {
		DrawSprite(SPR_spark_vinespike, target->x, target->y, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_spark_vinespike, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 17) {
		DrawSprite(SPR_spark_vinespike, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 19) {
		DrawSprite(SPR_spark_vinespike, target->x, target->y, 0, 2, 2);
	}
}

void Action_AnimDraw__5(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_vinetrap, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_vinetrap, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_vinetrap, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_vinetrap, target->x, target->y, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 22) {
		DrawSprite(SPR_spark_vinetrap, target->x, target->y, 4, 2, 2);
	}
}

void Action_AnimDraw__6(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 7) {
		DrawSprite(SPR_misc_shuriken, attacker->x + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 6, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 6, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 25) {
		DrawSprite(SPR_misc_shuriken, target->x + target->facing * 6, target->y - 24, 0, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__7(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_gunfire);
		attacker->state = FIGHTER_STATE_SPECIAL2;
	}
	else if (attacker->attackAnimTimer == 5) {
		attacker->state = FIGHTER_STATE_SPECIAL1;
	}
}
void Action_AnimDraw__7(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
}

void Action_AnimUpdate__8(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 20) {
		PlaySound(SND_explode);
		Battle_ShakeScreen(8);
		attacker->state = FIGHTER_STATE_ATTACK3;
	}
}
void Action_AnimDraw__8(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 4, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x - 16, target->y - 34, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x + 16, target->y - 34, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_star, target->x, target->y - 4, 0, 2, 2);
		DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 0, 2, 2);
		DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_star, target->x, target->y - 4, 1, 2, 2);
		DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 1, 2, 2);
		DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_star, target->x, target->y - 4, 2, 2, 2);
		DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 2, 2, 2);
		DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite(SPR_spark_star, target->x, target->y - 4, 3, 2, 2);
		DrawSprite(SPR_spark_star, target->x - 16, target->y - 34, 3, 2, 2);
		DrawSprite(SPR_spark_star, target->x + 16, target->y - 34, 3, 2, 2);
	}
}

void Action_AnimUpdate__9(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_gunfire);
		attacker->state = FIGHTER_STATE_SPECIAL4;
	}
	else if (attacker->attackAnimTimer == 5) {
		attacker->state = FIGHTER_STATE_SPECIAL3;
	}
}
void Action_AnimDraw__9(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 7) {
		DrawSprite(SPR_misc_rocket, attacker->x + attacker->facing * 16 + (target->x + target->facing * 6 - (attacker->x + attacker->facing * 16)) * attacker->attackAnimTimer / 6, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 6, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 8, 8);
	}
	else if (attacker->attackAnimTimer < 13) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 8, 8);
	}
	else if (attacker->attackAnimTimer < 16) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 8, 8);
	}
	else if (attacker->attackAnimTimer < 19) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 8, 8);
	}
}

void Action_AnimUpdate__10(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 15) {
		PlaySound(SND_explode);
		Battle_ShakeScreen(6);
	}
}
void Action_AnimDraw__10(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_misc_bomb, attacker->x + attacker->facing * 8 + (target->x + target->facing * 6 - attacker->x + attacker->facing * 8) * attacker->attackAnimTimer / 15, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 15 + (attacker->attackAnimTimer - 7) * (attacker->attackAnimTimer - 7) - 48, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 17) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 19) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 21) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 23) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimDraw__11(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 7) {
		DrawSprite(SPR_misc_kunai, attacker->x + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 6, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 6, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 25) {
		DrawSprite(SPR_misc_kunai, target->x + target->facing * 6, target->y - 24, 0, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__12(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_burn);
	}
	else if (attacker->attackAnimTimer == 22) {
		PlaySound(SND_explode);
		Battle_ShakeScreen(6);
	}
}
void Action_AnimDraw__12(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		SetDrawColor(255, 255, 255);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		SetDrawColor(255, 159, 0);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		SetDrawColor(255, 159, 0);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		SetDrawColor(255, 0, 0);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	SetDrawColor(255, 255, 255);
	if (attacker->attackAnimTimer < 22) {
		DrawSprite(SPR_misc_flameorb, attacker->x + attacker->facing * 72 + (target->x + target->facing * 12 - (attacker->x + attacker->facing * 72)) * attacker->attackAnimTimer / 21, attacker->y - 22 + (target->y - attacker->y) * attacker->attackAnimTimer / 21, (attacker->attackAnimTimer / 3) % 3, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 26) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 30) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimUpdate__13(Fighter* attacker, Fighter* target) {
	
}
void Action_AnimDraw__13(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		SetDrawColor(255, 255, 255);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		SetDrawColor(0, 165, 255);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		SetDrawColor(0, 165, 255);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		SetDrawColor(0, 43, 255);
		DrawSprite(SPR_misc_diamondcast, attacker->x + attacker->facing * 56, attacker->y - 20, 2, 2, 2);
	}
	SetDrawColor(255, 255, 255);
	if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_misc_waterbullet, attacker->x + attacker->facing * 64 + (target->x + target->facing * 6 - (attacker->x + attacker->facing * 64)) * attacker->attackAnimTimer / 13, attacker->y - 22 + (target->y - attacker->y) * attacker->attackAnimTimer / 13, (attacker->attackAnimTimer / 3) % 2, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__14(Fighter* attacker, Fighter* target) {
	
}
void Action_AnimDraw__14(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 2) {
		DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 56, attacker->y - 26, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 56, attacker->y - 26, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 56, attacker->y - 26, 2, 2, 2);
	}
	
	if (attacker->attackAnimTimer >= 2) {
		if (attacker->attackAnimTimer < 4) {
			DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 72, attacker->y - 26, 0, 2, 2);
		}
		else if (attacker->attackAnimTimer < 6) {
			DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 72, attacker->y - 26, 1, 2, 2);
		}
		else if (attacker->attackAnimTimer < 8) {
			DrawSprite(SPR_misc_amppulse, attacker->x + attacker->facing * 72, attacker->y - 26, 2, 2, 2);
		}
	}
	
	if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_misc_ampbullet, attacker->x + attacker->facing * 64 + (target->x + target->facing * 6 - (attacker->x + attacker->facing * 64)) * attacker->attackAnimTimer / 13, attacker->y - 26 + (target->y - attacker->y) * attacker->attackAnimTimer / 13, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 14) {
		SetDrawColor(0, 255, 255);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		SetDrawColor(0, 255, 255);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		SetDrawColor(0, 255, 255);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		SetDrawColor(0, 255, 255);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimUpdate__15(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer % 2 == 0 && attacker->attackAnimTimer < 8) {
		Battle_ShakeScreen(40);
	}
}
void Action_AnimDraw__15(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 10) {
		DrawSprite(SPR_misc_ampbeam, attacker->x + attacker->facing * 38, attacker->y - 22, attacker->attackAnimTimer / 2, attacker->facing * 640, 4);
		DrawSprite(SPR_misc_ampbeamstart, attacker->x + attacker->facing * 38, attacker->y - 22, attacker->attackAnimTimer / 2, attacker->facing * 4, 4);
	}
}

void Action_AnimUpdate__16(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 15) {
		PlaySound(SND_firemassattack);
	}
	if (attacker->attackAnimTimer >= 15 && attacker->attackAnimTimer <= 135 && attacker->attackAnimTimer % 7 == 0) {
		PlaySound(SND_explode);
		Battle_ShakeScreen(76);
	}
}
void Action_AnimDraw__16(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_misc_bomb, attacker->x + attacker->facing * 8 + (target->x + target->facing * 6 - attacker->x + attacker->facing * 8) * attacker->attackAnimTimer / 15, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 15 + (attacker->attackAnimTimer - 7) * (attacker->attackAnimTimer - 7) - 48, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 142) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 16, 16);
	}
	else if (attacker->attackAnimTimer < 145) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 16, 16);
	}
	else if (attacker->attackAnimTimer < 148) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 16, 16);
	}
	else if (attacker->attackAnimTimer < 151) {
		SetDrawColor(255, 191, 0);
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 16, 16);
	}
}

void Action_AnimUpdate__17(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		attacker->state = FIGHTER_STATE_SPECIAL2;
	}
	else if (attacker->attackAnimTimer == 66) {
		PlaySound(SND_explode);
		Battle_ShakeScreen(64);
	}
}
void Action_AnimDraw__17(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 66) {
		
	}
	else if (attacker->attackAnimTimer < 68) {
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	else if (attacker->attackAnimTimer < 70) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 8, 8);
	}
	else if (attacker->attackAnimTimer < 72) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 8, 8);
	}
	else if (attacker->attackAnimTimer < 74) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 8, 8);
	}
	else if (attacker->attackAnimTimer < 76) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 8, 8);
	}
}

void Action_AnimDraw__18(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_spark_slashmagic, target->x, target->y - 24, 4, 2, 2);
	}
}

void Action_AnimDraw__19(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 3) {
		DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_spark_slashfirelu, target->x, target->y - 24, 4, 2, 2);
	}
}

void Action_AnimUpdate__20(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_boost);
	}
}
void Action_AnimDraw__20(Fighter* attacker, Fighter* target) {
	SetDrawColor(255, 31, 31);
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__21(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_boost);
	}
}
void Action_AnimDraw__21(Fighter* attacker, Fighter* target) {
	SetDrawColor(31, 31, 255);
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__22(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_freeze);
	}
}
void Action_AnimDraw__22(Fighter* attacker, Fighter* target) {
	SetDrawColor(0, 191, 255);
	if (attacker->attackAnimTimer < 50) {
		DrawSprite(SPR_spark_snow, target->x + 18 - 36 * (attacker->attackAnimTimer % 16 < 8), target->y - 6 - 36 * (attacker->attackAnimTimer % 16 < 4 || attacker->attackAnimTimer % 16 >= 12), 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 54) {
		DrawSprite(SPR_spark_snow, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 58) {
		DrawSprite(SPR_spark_snow, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 62) {
		DrawSprite(SPR_spark_snow, target->x, target->y - 24, 2, 4, 4);
	}
	else if (attacker->attackAnimTimer < 66) {
		DrawSprite(SPR_spark_snow, target->x, target->y - 24, 3, 4, 4);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__23(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 2) {
		PlaySound(SND_thunder);
	}
}
void Action_AnimDraw__23(Fighter* attacker, Fighter* target) {
	SetDrawColor(255, 255, 31);
	if (attacker->attackAnimTimer < 8) {
		int x = target->x;
		for (int y = target->y; y > 128; y -= 2) {
			SetDrawColor(255, 255, 31);
			FillRect(x - 3, y - 1, 6, 2);
			SetDrawColor(255, 255, 255);
			FillRect(x - 1, y - 1, 2, 2);
			x += Random_IRange(-1, 1) * 2;
		}
	}
	else if (attacker->attackAnimTimer < 10) {
		SetDrawAlpha(63);
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		SetDrawAlpha(255);
	}
	else if (attacker->attackAnimTimer < 14) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 22) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 26) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__24(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 8) {
		PlaySound(SND_slap);
	}
}
void Action_AnimDraw__24(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_spark, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_punch, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_punch, target->x, target->y - 24, 1, 2, 2);
	}
}

void Action_AnimUpdate__25(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1 || attacker->attackAnimTimer == 6) {
		PlaySound(SND_minigun);
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
		PlaySound(SND_explode);
	}
}
void Action_AnimDraw__26(Fighter* attacker, Fighter* target) {
	SetDrawColor(127, 127, 127);
	if (attacker->attackAnimTimer < 3) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 0, 4, 4);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 1, 4, 4);
	}
	else if (attacker->attackAnimTimer < 9) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 2, 4, 4);
	}
	else if (attacker->attackAnimTimer < 11) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 3, 4, 4);
	}
	else if (attacker->attackAnimTimer < 14) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 4, 4, 4);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__27(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		attacker->y -= 512;
	}
	else if (attacker->attackAnimTimer == 106) {
		attacker->x = target->x - 32 * attacker->facing;
		attacker->y = target->y - 512;
		PlaySound(SND_swing);
	}
	else if (attacker->attackAnimTimer == 110) {
		attacker->y += 512;
	}
	else if (attacker->attackAnimTimer == 112) {
		PlaySound(SND_thunder);
		PlaySound(SND_explode);
		Battle_ShakeScreen(40);
	}
	else if (attacker->attackAnimTimer == 136) {
		Fighter_MoveToStart(attacker);
	}
}
void Action_AnimDraw__27(Fighter* attacker, Fighter* target) {
	SetDrawColor(255, 255, 31);
	if (attacker->attackAnimTimer < 4) {
		for (int x = attacker->x - 7; x <= attacker->x + 6; x += 4) {
			SetDrawColor(255, 255, 255);
			FillRect(x, 128, 2, attacker->y + 512 - 128);
		}
	}
	else if (attacker->attackAnimTimer < 106) {
		
	}
	else if (attacker->attackAnimTimer < 110) {
		for (int x = attacker->x - 7; x <= attacker->x + 6; x += 4) {
			SetDrawColor(255, 255, 255);
			FillRect(x, 128, 2, attacker->y + 512 - 128);
		}
	}
	else if (attacker->attackAnimTimer < 114) {
		int x = target->x;
		for (int y = target->y; y > 128; y -= 2) {
			SetDrawColor(255, 255, 31);
			FillRect(x - 3, y - 1, 6, 2);
			SetDrawColor(255, 255, 255);
			FillRect(x - 1, y - 1, 2, 2);
			x += Random_IRange(-1, 1) * 2;
		}
	}
	else if (attacker->attackAnimTimer < 116) {
		SetDrawAlpha(63);
		FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		SetDrawAlpha(255);
	}
	else if (attacker->attackAnimTimer < 120) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 124) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 128) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 132) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__28(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 10) {
		ApplySoundFilter(1);
		
		int r = Random_IRange(0, 2);
		if (r == 0)
			PlaySound(SND_unknown1);
		else if (r == 1)
			PlaySound(SND_unknown2);
		else
			PlaySound(SND_unknown3);
	}
	else if (attacker->attackAnimTimer == 40) {
		RemoveSoundFilter();
	}
}
void Action_AnimDraw__28(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 10) {
		for (int y = target->y; y > target->y - 40; y -= 2) {
			SetDrawColor(255, 0, 0);
			for (int i = 0; i < 2; i++) {
				FillRect(target->x + Random_IRange(-32, 32), y - 1, Random_IRange(1, 2) * 2, 2);
			}
			SetDrawColor(255, 127, 0);
			for (int i = 0; i < 2; i++) {
				FillRect(target->x + Random_IRange(-32, 32), y - 1, Random_IRange(1, 2) * 2, 2);
			}
		}
		SetDrawColor(255, 255, 255);
	}
}

void Action_AnimDraw__29(Fighter* attacker, Fighter* target) {
	SetDrawColor(0, 127, 255);
	if (attacker->attackAnimTimer < 2) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 10) {
		DrawSprite(SPR_spark_slash, target->x, target->y - 24, 4, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__30(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_saw);
	}
}
void Action_AnimDraw__30(Fighter* attacker, Fighter* target) {
	SetDrawColor(255, 0, 255);
	if (attacker->attackAnimTimer < 3) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 6) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 9) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 18) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 5, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__31(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_saw);
	}
	if (attacker->attackAnimTimer == 4 || attacker->attackAnimTimer == 8 || attacker->attackAnimTimer == 13) {
		PlaySound(SND_sawkill);
	}
	if (attacker->attackAnimTimer % 4 == 0 && attacker->attackAnimTimer >= 4 && attacker->attackAnimTimer <= 28) {
		Battle_CreateSpark(3, target->x, target->y - 24 - 16 + attacker->attackAnimTimer, 0);
		Battle_ShakeScreen(2);
		PlaySound(SND_poison);
	}
	if (attacker->attackAnimTimer == 32) {
		attacker->state = FIGHTER_STATE_ATTACK3;
	}
}
void Action_AnimDraw__31(Fighter* attacker, Fighter* target) {
	SetDrawColor(255, 0, 255);
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 3, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 4, 2, 2);
	}
	else if (attacker->attackAnimTimer < 32) {
		DrawSprite(SPR_spark_saw, target->x, target->y - 24, 5, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__32(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 3) {
		PlaySound(SND_swing);
	}
}
void Action_AnimDraw__32(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 7) {
		DrawSprite(SPR_misc_knife2, attacker->x + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 6, attacker->y - 24 + (target->y - attacker->y) * attacker->attackAnimTimer / 6, 0, 2 * attacker->facing, 2);
		DrawSprite(SPR_misc_knife2, attacker->x - attacker->facing * 6 + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 6, attacker->y - 16 + (target->y - attacker->y) * attacker->attackAnimTimer / 6, 0, 2 * attacker->facing, 2);
		DrawSprite(SPR_misc_knife2, attacker->x - attacker->facing * 12 + (target->x + target->facing * 6 - attacker->x) * attacker->attackAnimTimer / 6, attacker->y - 8 + (target->y - attacker->y) * attacker->attackAnimTimer / 6, 0, 2 * attacker->facing, 2);
	}
	else if (attacker->attackAnimTimer < 25) {
		DrawSprite(SPR_misc_knife2, target->x + target->facing * 6, target->y - 24, 0, 2 * attacker->facing, 2);
		DrawSprite(SPR_misc_knife2, target->x + target->facing * 6 - attacker->facing * 6, target->y - 16, 0, 2 * attacker->facing, 2);
		DrawSprite(SPR_misc_knife2, target->x + target->facing * 6 - attacker->facing * 12, target->y - 8, 0, 2 * attacker->facing, 2);
	}
}

void Action_AnimUpdate__33(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 2 || attacker->attackAnimTimer == 4) {
		PlaySound(SND_swing);
	}
	if (attacker->attackAnimTimer == 70 || attacker->attackAnimTimer == 72 || attacker->attackAnimTimer == 74 || attacker->attackAnimTimer == 76) {
		PlaySound(SND_slap);
	}
}
void Action_AnimDraw__33(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 16) {
		for (int i = 0; i < 6; i++) {
			DrawSprite_Angle(SPR_misc_knife2, attacker->x + (6 - i * 6) * attacker->facing, attacker->y - 48 - attacker->attackAnimTimer * 32, 0, 2 * attacker->facing, 2, 180 + attacker->facing * 90);
		}
	}
	else if (attacker->attackAnimTimer < 24) {
		
	}
	else if (attacker->attackAnimTimer < 122) {
		for (int i = 0; i < 32; i++) {
			DrawSprite_Angle(SPR_misc_knife2, 480 - attacker->side * 320 + cos((float)i * 1.2) * 16 - 140 + (i % 8) * 40, 192 + sin((float)i * 1.2) * 16 + (i / 8) * 58 - Max(0, (70 - attacker->attackAnimTimer - (i % 4) * 2) * 36), 0, 2 * attacker->facing, 2, 180 - attacker->facing * 90);
		}
	}
}

void Action_AnimDraw__34(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 0, 2, 2);
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 1, 2, 2);
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 24) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_boost, target->x, target->y, 2, 2, 2);
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 28) {
		DrawSprite(SPR_spark_boost, target->x, target->y, 3, 2, 2);
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
	}
}

void Action_AnimUpdate__35(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		PlaySound(SND_charge);
	}
}
void Action_AnimDraw__35(Fighter* attacker, Fighter* target) {
	SetDrawColor(255, 255, 0);
	if (attacker->attackAnimTimer < 4) {
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 8) {
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 12) {
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 16) {
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite(SPR_spark_ring, target->x, target->y - 24, 3, 2, 2);
	}
	SetDrawColor(255, 255, 255);
}

void Action_AnimUpdate__36(Fighter* attacker, Fighter* target) {
	if (attacker->attackAnimTimer == 1) {
		attacker->state = FIGHTER_STATE_SPECIAL2;
	}
	else if (attacker->attackAnimTimer == 3) {
		PlaySound(SND_gunfire2);
	}
	else if (attacker->attackAnimTimer == 7) {
		Battle_ShakeScreen(6);
	}
	else if (attacker->attackAnimTimer == 9) {
		attacker->state = FIGHTER_STATE_SPECIAL1;
	}
}
void Action_AnimDraw__36(Fighter* attacker, Fighter* target) {
	SetDrawColor(223, 223, 223);
	if (attacker->attackAnimTimer < 4) {
		
	}
	else if (attacker->attackAnimTimer < 20) {
		DrawSprite_Angle(SPR_spark_saw, attacker->x + (target->x - attacker->x) * (attacker->attackAnimTimer - 4) / 3, attacker->y - 26 + (target->y - attacker->y) * (attacker->attackAnimTimer - 4) / 3, 3, 2 * attacker->facing, 2, 180 + 90 * attacker->facing);
		if (attacker->attackAnimTimer >= 5) DrawSprite_Angle(SPR_spark_boost, attacker->x + (target->x - attacker->x) * (attacker->attackAnimTimer - 5) / 3, attacker->y - 26 + (target->y - attacker->y) * (attacker->attackAnimTimer - 5) / 3, 0, 2 * attacker->facing, 2, 180 + 90 * attacker->facing);
		if (attacker->attackAnimTimer >= 6) DrawSprite_Angle(SPR_spark_boost, attacker->x + (target->x - attacker->x) * (attacker->attackAnimTimer - 6) / 3, attacker->y - 26 + (target->y - attacker->y) * (attacker->attackAnimTimer - 6) / 3, 0, 2 * attacker->facing, 2, 180 + 90 * attacker->facing);
	}
	
	if (attacker->attackAnimTimer < 7) {
		
	}
	else if (attacker->attackAnimTimer < 11) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 0, 2, 2);
	}
	else if (attacker->attackAnimTimer < 15) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 1, 2, 2);
	}
	else if (attacker->attackAnimTimer < 19) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 2, 2, 2);
	}
	else if (attacker->attackAnimTimer < 23) {
		DrawSprite(SPR_spark_star, target->x, target->y - 24, 3, 2, 2);
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
