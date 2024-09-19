#pragma once

#include "menu.h"

#define COUNTER_DEFAULT_ACTION 1

typedef struct {
	bool enabled;
	bool alive;
	bool fatalInjury;
	bool trulyDead;
	int side;
	int id;
	
	char name[32];
	int exp;
	int cash;
	int rewardCount;
	struct {
		int type;
		int id;
		int rarity;
	} rewards[16];
	
	int headId;
	int bodyId;
	int charId;
	int collapseSpriteId;
	int spriteId;
	int spriteFrame;
	int actionAnimId;
	int ai;
	
	float x;
	float y;
	float xStart;
	float yStart;
	float xStore;
	float yStore;
	struct {
		bool enabled;
		float x;
		float y;
		float speed;
		int facing;
	} moveTarget;
	int facing;
	int state;
	int flinchTicks;
	
	int hp;
	int hpMax;
	int mp;
	int mpMax;
	
	bool canAct;
	int speedRoll;
	int speedRollMin;
	int speedRollMax;
	int priority;
	int status[32];
	int statusNext[32];
	int passiveCount;
	int passives[32];
	int manaCostReduction;
	union {
		int i;
		float f;
	} passiveVars[OBJECT_COUNT_MAX];
	
	int attack;
	int defense;
	int speed;
	
	int movesetCount;
	int moveset[16];
	bool movesetDisabled[16];
	
	int bodyguardId;
	int counterTargetId;
	int targetId;
	int actionId;
	int usedItemId;
	int usedItemSlot;
	int storeHealedHP;
	int storeHealedMP;
	union {
		int i;
		float f;
	} actionVars[4];
	union {
		int i;
		float f;
	} tempVars[8];
	int battleEventVars[4];
	int actionPower[4];
	int actionPowerRepeat;
	float actionAttackMultiplier;
	
	int blockTime;
	int dodgeTime;
	int criticalTime;
	int blockTimer;
	int blockCooldownTimer;
	int attackTimer;
	int attackAnimTimer;
	int attackAnimTime;
	int readyTimer;
	int totalAttackTimer;
	int actionAttacks;
	int actionTempAnimId;
} Fighter;

enum {
	FIGHTER_STATE_IDLE,
	FIGHTER_STATE_RUN,
	FIGHTER_STATE_BLOCK,
	FIGHTER_STATE_HURT,
	FIGHTER_STATE_DOWN,
	FIGHTER_STATE_ATTACK1,
	FIGHTER_STATE_ATTACK2,
	FIGHTER_STATE_ATTACK3,
	FIGHTER_STATE_SPECIAL1,
	FIGHTER_STATE_SPECIAL2,
	FIGHTER_STATE_SPECIAL3,
	FIGHTER_STATE_SPECIAL4,
	FIGHTER_STATE_SPECIAL5,
	FIGHTER_STATE_SPECIAL6,
};

enum {
	TARGET_ALLYPARTY = 64,
	TARGET_ENEMYPARTY = 128,
};

void Fighter_TakeDamage(Fighter* fighter, Fighter* attacker, int damage, unsigned int flags);
void Fighter_DealDamage(Fighter* fighter, Fighter* target, int damage, unsigned int flags);
void Fighter_InflictStatus(Fighter* fighter, Fighter* target, int statusId, int count, bool instant);
void Fighter_InflictStatusDodgable(Fighter* fighter, Fighter* target, int statusId, int count, bool instant);

void Fighter_OnAttackSwing(Fighter* fighter);
void Fighter_PrepareToBlock(Fighter* fighter);
void Fighter_UpdateBlock(Fighter* fighter);
void Fighter_MoveTo(Fighter* fighter, float x, float y, float speed, int facing);
void Fighter_MoveToStart(Fighter* fighter);

void Fighter_HealHP(Fighter* fighter, int amount);
void Fighter_HealMP(Fighter* fighter, int amount);
void Fighter_GainStatus(Fighter* fighter, int statusId, int count, bool instant);
void Fighter_ClearAllStatus(Fighter* fighter);
void Fighter_EnableAction(Fighter* fighter, int actionId);
void Fighter_DisableAction(Fighter* fighter, int actionId);

enum {
	DAMAGE_FLAG_BLOCKABLE = 1 << 0,
	DAMAGE_FLAG_DODGABLE = 1 << 1,
	DAMAGE_FLAG_LETHAL = 1 << 2,
	DAMAGE_FLAG_CRITICAL = 1 << 3,
};

typedef struct {
	char name[32];
	char desc[64];
	int type;
	bool visible;
	bool instantByDefault;
} StatusEffect;

enum {
	STATUS_TYPE_NEUTRAL,
	STATUS_TYPE_POSITIVE,
	STATUS_TYPE_NEGATIVE,
};

extern StatusEffect statusEffectData[32];

void LoadStatusEffectData();

enum {
	FIGHTER_STATUS_STRENGTH,
	FIGHTER_STATUS_FEEBLE,
	FIGHTER_STATUS_ENDURANCE,
	FIGHTER_STATUS_DISARM,
	FIGHTER_STATUS_HASTE,
	FIGHTER_STATUS_BIND,
	FIGHTER_STATUS_BURN,
	FIGHTER_STATUS_BLEED,
	FIGHTER_STATUS_GUARD,
	FIGHTER_STATUS_COUNTER,
	FIGHTER_STATUS_PARALYSIS,
	FIGHTER_STATUS_POISON,
	FIGHTER_STATUS_TIMEDBOMB,
	FIGHTER_STATUS_ANTIGUARD,
	FIGHTER_STATUS_IMMOBILE,
	FIGHTER_STATUS_CHILL,
	FIGHTER_STATUS_FLOWER,
	FIGHTER_STATUS_CHARGE,
	FIGHTER_STATUS_SERIOUS,
	FIGHTER_STATUS_HYPERENERGIZER,
	FIGHTER_STATUS_WEAPONSEARCH,
};

typedef struct {
	unsigned short fighterIds[8];
	unsigned char musicId;
	unsigned char backgroundId;
} BattleEncounter;

extern BattleEncounter battleEncounterData[256];



typedef struct {
	int encounter;
	union {
		int i;
		float f;
	} encounterVars[4];
	bool gameover;
	bool turnStartFatalInjury;
	bool retry;
	bool loadLastSave;
	bool canFlee;
	bool fleeing;
	int state;
	int turnCount;
	int timer;
	int globalTimer;
	int shakeTimer;
	int backgroundId;
	int musicId;
	int battleEventId;
	int battleEventType;
	int battleEventVars[4];
	bool battleEventDialogWait;
	Fighter* battleEventFighter;
	bool gameOverDisabled;
	
	struct {
		float x;
		float y;
		float zoom;
		struct {
			bool enabled;
			float x;
			float y;
			float zoom;
			float zoomSpeed;
			float speed;
		} moveTarget;
	} camera;
	
	Menu menu;
	
	int expEarned;
	int cashEarned;
	int rewardCount;
	struct {
		int type;
		int id;
		int count;
	} rewards[16];
	
	struct {
		int partyId;
		int hpGain;
		int mpGain;
		int attackGain;
		int defenseGain;
		int speedGain;
		int actionId;
	} levelUp;
	
	int turnOrder[16];
	
	Fighter fighters[16];
	
	int turn;
	int priority;
	Fighter* attacker;
	Fighter* target;
	
	int labelCounter;
	struct {
		int color;
		char string[16];
		float x;
		float y;
		int timer;
	} label[16];
	
	int sparkCounter;
	struct {
		int id;
		float x;
		float y;
		float xVel;
		float yVel;
		int depth;
		int timer;
	} sparks[OBJECT_COUNT_MAX];
} Battle;

enum {
	BATTLE_STATE_START,
	BATTLE_STATE_IDLE,
	BATTLE_STATE_ACTION,
	BATTLE_STATE_END,
	BATTLE_STATE_FLEE,
	BATTLE_STATE_EVENT,
};

enum {
	BATTLE_EVENT_TYPE_TURNSTART,
	BATTLE_EVENT_TYPE_TURNEND,
};

extern Battle battle;



void Battle_Init();

void Battle_Update();
void Battle_Update_Start();
void Battle_Update_Idle();
void Battle_Update_Action();
void Battle_Update_End();
void Battle_Update_Event();
void Battle_Draw_Event();

void Battle_CreateFighter(int fighterId, int side);
void Battle_CreateLabel(int color, const char* string, float x, float y);
void Battle_CreateSpark(int id, float x, float y, int depth);
void Battle_ShakeScreen(int timer);
void Battle_TriggerBattleEvent(int battleEventId, Fighter* fighter);

void Battle_Camera_MoveTo(float x, float y, float zoom, float speed);
void Battle_Camera_MoveToStart(float speed);

void Battle_Draw();
void Battle_DrawFighterPortrait(Fighter* fighter, int x, int y);
void Battle_DrawFighterProfile(Fighter* fighter);
void Battle_DrawFighterProfileAction(Fighter* fighter);

void Battle_ChangeMenu(int id);

void DrawFighterChar(int headId, int bodyId, int state, float x, float y, float xScale, float yScale, int facing);
