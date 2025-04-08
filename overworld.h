#pragma once

#include "menu.h"

#define DECORATION_COUNT_MAX 1024
#define MOVETARGET_QUEUE_MAX 16

typedef struct {
	bool enabled;
	float x;
	float y;
	float speed;
	int direction;
	int jumpTime;
	float jumpHeight;
} MoveTarget;

typedef struct {
	int type;
	int id;
	int spriteId;
	int spriteFrame;
	int spriteType;
	float spriteFrameFraction;
	float spriteFrameSpeed;
	uint8_t color[3];
	int state;
	int timer;
	float x;
	float y;
	float z;
	float w;
	float h;
	float collisionOffsetX;
	float collisionOffsetY;
	float depth;
	int direction;
	float xPrev;
	float yPrev;
	int headId;
	int bodyId;
	int fighterState;
	bool walkAnimationEnabled;
	bool ghost;
	int climbSpriteId;
	MoveTarget moveTarget;
	MoveTarget moveTargetQueue[MOVETARGET_QUEUE_MAX];
	union {
		int i;
		float f;
	} vars[8];
} OverworldObject;

enum {
	OBJECT_STATE_IDLE,
	OBJECT_STATE_WALK,
	OBJECT_STATE_JUMP,
	OBJECT_STATE_CLIMB,
	OBJECT_STATE_FREE,
};

enum {
	ENEMY_STATE_IDLE,
	ENEMY_STATE_CHASE,
	ENEMY_STATE_FIGHT,
	ENEMY_STATE_KNOCKED,
};

enum  {
	OBJECT_DIRECTION_LEFT,
	OBJECT_DIRECTION_RIGHT,
	OBJECT_DIRECTION_UP,
	OBJECT_DIRECTION_DOWN,
};

void OverworldObject_Destroy(int objectId);
void OverworldObject_SetCollisionSize(int objectId, int w, int h);
void OverworldObject_SetPositionZ(int objectId, float z);
void OverworldObject_ChangeDirection(int objectId, int direction);
void OverworldObject_ChangeSpriteId(int objectId, int spriteId);
void OverworldObject_ChangeSpriteFrame(int objectId, int spriteFrame);
void OverworldObject_ChangeSpriteFrameSpeed(int objectId, float spriteFrameSpeed);
void OverworldObject_WalkTo(int objectId, float x, float y, float speed, int direction);
void OverworldObject_QueueWalkTo(int objectId, float x, float y, float speed, int direction);
void OverworldObject_JumpTo(int objectId, float x, float y, int direction, float jumpHeight, int jumpTime);
void OverworldObject_TryMove(int objectId, float xMove, float yMove);
void OverworldObject_EnableFighterSprite(int objectId, int headId, int bodyId, int fighterState);
void OverworldObject_DisableFighterSprite(int objectId);
void OverworldObject_ToggleWalkAnimation(int objectId, bool value);
void OverworldObject_SetColor(int objectId, uint8_t r, uint8_t g, uint8_t b);
void OverworldObject_ToggleGhost(int objectId, bool value);



typedef struct {
	int state;
	int areaId;
	
	float fadeAlpha;
	uint8_t fadeColor[3];
	int overlayId;
	int backgroundId;
	bool cameraClamping;
	bool areaWrap;
	int lastMusicId;
	int shakeTimer;
	bool lockSaving;
	
	Menu menu;
	Menu menuBuffer[5];
	
	struct {
		int id;
		struct {
			int id;
			int cost;
		} items[16];
	} shop;
	
	struct {
		int state;
		int timer;
		float x;
		float y;
		int direction;
		float xPrev;
		float yPrev;
		int invincibleFrames;
		int dashChargeTimer;
		bool dashing;
		bool dashEnabled;
		int blushTimer;
	} player;
	
	struct {
		float x;
		float y;
		int direction;
	} caterpillar[128];
	
	struct {
		float x;
		float y;
		float zoom;
	} camera;
	
	struct {
		int id;
		int timer;
		float vars[8];
	} transition;
	
	struct {
		int tilesetSpriteId;
		short tileMap[2048][2048];
		int w;
		int h;
		struct {
			int x1;
			int y1;
			int x2;
			int y2;
		} areas[OBJECT_COUNT_MAX];
		struct {
			bool enabled;
			int x1;
			int y1;
			int area1;
			int x2;
			int y2;
			int area2;
			int direction1;
			int direction2;
			int w1;
			int h1;
			int w2;
			int h2;
		} doors[OBJECT_COUNT_MAX];
		struct {
			int eventId;
			float x1;
			float y1;
			float x2;
			float y2;
		} triggers[OBJECT_COUNT_MAX];
		
		int decorationCount;
		OverworldObject decorations[DECORATION_COUNT_MAX];
		
		unsigned char tileData[8192];
	} map;
	
	OverworldObject objects[OBJECT_COUNT_MAX];
	
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
} Overworld;

enum {
	OVERWORLD_STATE_IDLE,
	OVERWORLD_STATE_PAUSED,
	OVERWORLD_STATE_EVENT,
	OVERWORLD_STATE_TRANSITION,
};

enum {
	PLAYER_STATE_IDLE,
	PLAYER_STATE_WALK,
	PLAYER_STATE_FREE,
	PLAYER_STATE_FLINCH,
};

extern Overworld overworld;



void Overworld_Init();
void Overworld_Update();
void Overworld_Draw();
void Overworld_DrawMap();
void Overworld_DrawCharBox(int partyId, int x, int y, bool selected);
void Overworld_UpdateMenu();
void Overworld_DrawMenu();
void Overworld_ChangeMenu(int id);
void Overworld_OpenShopMenu(int id);
void Overworld_OpenSaveMenu();
void Overworld_FadeIn(int time, uint8_t r, uint8_t g, uint8_t b);
void Overworld_FadeOut(int time, uint8_t r, uint8_t g, uint8_t b);
void Overworld_ShakeScreen(int timer);

void Overworld_CreateObject(int objectId, int type, int id, float x, float y, int direction);
void Overworld_CreateNPC(int objectId, int id, float x, float y, int direction);
void Overworld_CreateNPC_Wandering(int objectId, int id, float x, float y, int direction);
void Overworld_CreateEnemy(int objectId, int id, float x, float y);
void Overworld_CreateWall(int objectId, float x, float y, float w, float h);
void Overworld_CreateArea(int id, int x1, int y1, int x2, int y2);
void Overworld_CreateDoor(int id, int x1, int y1, int area1, int x2, int y2, int area2, int direction1, int direction2);
void Overworld_CreateDoor_Advanced(int id, int x1, int y1, int area1, int x2, int y2, int area2, int direction1, int direction2, int w1, int h1, int w2, int h2);
void Overworld_CreateTrigger(int id, float x1, float y1, float x2, float y2, int eventId);
void Overworld_CreateDecoration(float x, float y, int tileId, int width, int height);
void Overworld_DeleteDecoration(int id);
void Overworld_CreateSpark(int id, float x, float y, int depth);

void Overworld_ChangeArea(int id);

int Overworld_LoadMap(const char* path);

void Player_UpdateObject();
void Player_TeleportTo(int x, int y);
void Player_TeleportToTile(int tileX, int tileY);
void Player_TakeDamage(int damage);
void Player_TryMove(float xMove, float yMove);
void Player_StopDashing();
