#pragma once

#define EVENT_QUEUE_MAX 256

typedef struct {
	int id;
	union {
		int i;
		float f;
		char c;
		bool b;
		int* pi;
		float* pf;
		char* pc;
		bool* pb;
	} args[16];
} EventCommand;

typedef struct {
	int runningSize;
	EventCommand running[EVENT_QUEUE_MAX];
	int queueSize;
	EventCommand queue[EVENT_QUEUE_MAX];
	
	bool paused;
	int ptr;
	int triggerId;
	int callerObjectId;
	bool sync;
	bool playerPositionSync;
	bool cameraPlayerFollow;
	
	struct {
		unsigned equal : 1, greater : 1, less : 1;
	} flags;
	
	union {
		int i;
		float f;
		char c;
		bool b;
		int* pi;
		float* pf;
		char* pc;
		bool* pb;
	} vars[16];
	
	int labels[64];
} EventSystem;

extern EventSystem eventSystem;

void LoadEventData();

void Event_Trigger(int id);

void Event_Update();
void Event_UpdateCommand(EventCommand* command);

void Event_Queue_Dialog_Run(int id);
void Event_Queue_Overworld_SetState(int id);
void Event_Queue_Object_WalkToRelative(int id, float x, float y, float speed, int direction);
void Event_Queue_EngageBattle(int id, int enemyObjectId);
void Event_Queue_Camera_MoveToRelative(float x, float y, float speed);
void Event_Queue_Regroup(float cameraSpeed);
void Event_Queue_WaitFrames(int frames);
void Event_Queue_Object_WalkToPointer(int id, float x, float y, float speed, int direction, float* px, float* py);
void Event_Queue_Object_WalkTo(int id, float x, float y, float speed, int direction);
void Event_Queue_Object_ChangeDirection(int objectId, int direction);
void Event_Queue_Object_ChangeSpriteId(int objectId, int spriteId);
void Event_Queue_Object_ChangeSpriteFrame(int objectId, int spriteFrame);
void Event_Queue_Object_Destroy(int objectId);
void Event_Queue_Camera_MoveTo(float x, float y, float speed);
void Event_Queue_Player_SetPositionSync(bool value);
void Event_Queue_Object_TeleportTo(int id, float x, float y);
void Event_Queue_Object_TeleportToPointer(int id, float x, float y, float* px, float* py);
void Event_Queue_CreateObject(int objectId, int type, int id, float x, float y, int direction);
void Event_Queue_CreateNPC(int objectId, int id, float x, float y, int direction);
void Event_Queue_CreateEnemy(int objectId, int id, float x, float y);
void Event_Queue_GotoArea(int areaId, float x, float y, int tilesetSpriteId);
void Event_Queue_Object_EnableFighterSprite(int objectId, int headId, int bodyId, int fighterState);
void Event_Queue_Object_DisableFighterSprite(int objectId);
void Event_Queue_Object_ChangeSpriteFrameSpeed(int objectId, float spriteFrameSpeed);
void Event_Queue_Object_ToggleWalkAnimation(int objectId, bool value);
void Event_Queue_Object_QueueWalkTo(int id, float x, float y, float speed, int direction);
void Event_Queue_Camera_TogglePlayerFollow(bool value);
void Event_Queue_FadeOut(float speed);
void Event_Queue_FadeIn(float speed);
void Event_Queue_OpenShopMenu(int id);
void Event_Queue_OpenSaveMenu();
void Event_Queue_Camera_TeleportTo(float x, float y);
void Event_Queue_Object_ToggleGhost(int objectId, bool value);
void Event_Queue_Overworld_FadeIn(int time, uint8_t r, uint8_t g, uint8_t b);
void Event_Queue_Overworld_FadeOut(int time, uint8_t r, uint8_t g, uint8_t b);
void Event_Queue_CreateTrigger(int id, float x1, float y1, float x2, float y2, int eventId);
void Event_Queue_Overworld_ShakeScreen(int timer);
void Event_Queue_Object_JumpToPointer(int id, float x, float y, int direction, float jumpHeight, int jumpTime, float* px, float* py);
void Event_Queue_Object_JumpTo(int id, float x, float y, int direction, float jumpHeight, int jumpTime);
void Event_Queue_Object_JumpToRelative(int id, float x, float y, int direction, float jumpHeight, int jumpTime);
void Event_Queue_Object_SetColor(int objectId, uint8_t r, uint8_t g, uint8_t b);
void Event_Queue_CreateSpark(int id, float x, float y, int depth);
void Event_Queue_Object_SetCollisionSize(int objectId, int w, int h);
void Event_Queue_Object_SetPositionZ(int objectId, float z);

void Event_Queue_RemoveCurrentTrigger();
void Event_Queue_SetSync(bool value);
void Event_Queue_SetVarInt(int id, int value);
void Event_Queue_SetVarFloat(int id, float value);
void Event_Queue_SaveToVarInt(int id, int* value);
void Event_Queue_SaveToVarFloat(int id, float* value);
void Event_Queue_SetFlag(int id, int value);
void Event_Queue_Party_Join(int id);
void Event_Queue_Party_Leave(int id);
void Event_Queue_Profile_InventoryPartyOrderAdd(int id);
void Event_Queue_Profile_InventoryPartyOrderRemove(int id);
void Event_Queue_SetIntPtr(int* p, int value);
void Event_Queue_SetFloatPtr(float* p, float value);
void Event_Queue_AddCash(int value);
void Event_Queue_SetCash(int value);
void Event_Queue_Profile_ItemAdd(int id);
void Event_Queue_Profile_ItemRemove(int inventoryId);
void Event_Queue_Profile_ClearItemInventory();
void Event_Queue_Profile_KeyItemAdd(int id);
void Event_Queue_Profile_KeyItemRemove(int id);
void Event_Queue_Profile_KeyItemExists(int id);
void Event_Queue_PlayMusic(int id);
void Event_Queue_StopMusic();
void Event_Queue_PlaySound(int id);
void Event_Queue_FadeOutMusic(int ms);
void Event_Queue_SetIntPtrToPtr(int* p, int* value);
void Event_Queue_SetFloatPtrToPtr(float* p, float* value);
void Event_Queue_AddIntPtr(int* p, int value);
void Event_Queue_AddFloatPtr(float* p, float value);
void Event_Queue_CustomAction(int id);
void Event_Queue_FullyHealParty();
void Event_Queue_SetTempFlag(int id, int value);
void Event_Queue_AddFlag(int id, int value);
void Event_Queue_SetBoolPtr(bool* p, bool value);

void Event_Queue_Jump(int label);
void Event_Queue_JumpIfEqual(int label);
void Event_Queue_JumpIfTrue(int label);
void Event_Queue_JumpIfLess(int label);
void Event_Queue_JumpIfGreater(int label);
void Event_Queue_JumpIfLessEqual(int label);
void Event_Queue_JumpIfGreaterEqual(int label);
void Event_Queue_JumpIfNotEqual(int label);
void Event_Queue_JumpIfFalse(int label);

void Event_Queue_CompareIntToConst(int* a, const int b);
void Event_Queue_CompareFloatToConst(float* a, const float b);
void Event_Queue_CompareIntToVar(int* a, int* b);
void Event_Queue_CompareFloatToVar(float* a, float* b);
void Event_Queue_CompareCharToConst(char* a, const char b);
void Event_Queue_CompareCharToVar(char* a, char* b);

void Event_Queue_Exit();

void Event_Queue_Label(int id);
