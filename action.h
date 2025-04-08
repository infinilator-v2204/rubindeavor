#pragma once

#include "battlesystem.h"

typedef struct {
	char name[32];
	int descriptionDialogId;
	int cost;
	int armorOnlyId;
	bool ranged;
	int priority;
	int codeId;
	int animationId;
	int targetType;
	int condition;
	union {
		int i;
		float f;
	} conditionVars[4];
	int category;
	int power[4];
	int powerRepeat;
	float attackMultiplier;
	union {
		int i;
		float f;
	} vars[4];
} Action;

enum {
	TARGETTYPE_NONE,
	TARGETTYPE_ENEMY,
	TARGETTYPE_ALLY,
	TARGETTYPE_ENEMYPARTY,
	TARGETTYPE_ALLYPARTY,
	TARGETTYPE_ANY,
	TARGETTYPE_DOWNALLY,
};

enum {
	ACTIONCONDITION_NONE,
	ACTIONCONDITION_EXHAUST,
	ACTIONCONDITION_HPHALF,
	ACTIONCONDITION_STATUSCOST,
	ACTIONCONDITION_AZTEC_1,
	ACTIONCONDITION_EXHAUST_HPHALF,
};

enum {
	ACTIONCATEGORY_MISC,
	ACTIONCATEGORY_ATTACK,
	ACTIONCATEGORY_DEFENSIVE,
};

typedef struct {
	int time;
} ActionAnim;

typedef int (*ActionUpdateFunction)(Fighter* attacker, Fighter* target);
typedef void (*ActionDrawFunction)(Fighter* attacker, Fighter* target);
typedef void (*ActionAnimFunction)(Fighter* attacker, Fighter* target);

extern Action actionData[OBJECT_COUNT_MAX];
extern ActionAnim actionAnimData[OBJECT_COUNT_MAX];
extern ActionUpdateFunction actionUpdateCode[OBJECT_COUNT_MAX];
extern ActionDrawFunction actionDrawCode[OBJECT_COUNT_MAX];
extern ActionAnimFunction actionAnimUpdateCode[OBJECT_COUNT_MAX];
extern ActionAnimFunction actionAnimDrawCode[OBJECT_COUNT_MAX];



void LoadActionData();

int Action_AttackUpdate(Fighter* attacker, Fighter* target);
void Action_BlockUpdate(Fighter* attacker, Fighter* target);
int Action_CalculateAttackPower(Fighter* attacker, Fighter* target, int damage);
int Action_GetDamagePower(Fighter* attacker, Fighter* target);

int Action_Update__0(Fighter* attacker, Fighter* target);
void Action_Draw__0(Fighter* attacker, Fighter* target);

int Action_Update__1(Fighter* attacker, Fighter* target);
void Action_Draw__1(Fighter* attacker, Fighter* target);

int Action_Update__2(Fighter* attacker, Fighter* target);

int Action_Update__3(Fighter* attacker, Fighter* target);

int Action_Update__4(Fighter* attacker, Fighter* target);

int Action_Update__5(Fighter* attacker, Fighter* target);

int Action_Update__6(Fighter* attacker, Fighter* target);

int Action_Update__7(Fighter* attacker, Fighter* target);

int Action_Update__8(Fighter* attacker, Fighter* target);

int Action_Update__9(Fighter* attacker, Fighter* target);

int Action_Update__10(Fighter* attacker, Fighter* target);

int Action_Update__11(Fighter* attacker, Fighter* target);

int Action_Update__12(Fighter* attacker, Fighter* target);

int Action_Update__13(Fighter* attacker, Fighter* target);

int Action_Update__14(Fighter* attacker, Fighter* target);
void Action_Draw__14(Fighter* attacker, Fighter* target);

int Action_Update__15(Fighter* attacker, Fighter* target);

int Action_Update__16(Fighter* attacker, Fighter* target);

int Action_Update__17(Fighter* attacker, Fighter* target);

int Action_Update__18(Fighter* attacker, Fighter* target);

int Action_Update__19(Fighter* attacker, Fighter* target);

int Action_Update__20(Fighter* attacker, Fighter* target);
void Action_Draw__20(Fighter* attacker, Fighter* target);

int Action_Update__21(Fighter* attacker, Fighter* target);

int Action_Update__22(Fighter* attacker, Fighter* target);

int Action_Update__23(Fighter* attacker, Fighter* target);
void Action_Draw__23(Fighter* attacker, Fighter* target);

int Action_Update__24(Fighter* attacker, Fighter* target);

int Action_Update__25(Fighter* attacker, Fighter* target);

int Action_Update__26(Fighter* attacker, Fighter* target);
void Action_Draw__26(Fighter* attacker, Fighter* target);

int Action_Update__27(Fighter* attacker, Fighter* target);
void Action_Draw__27(Fighter* attacker, Fighter* target);

int Action_Update__28(Fighter* attacker, Fighter* target);

int Action_Update__29(Fighter* attacker, Fighter* target);
void Action_Draw__29(Fighter* attacker, Fighter* target);

int Action_Update__30(Fighter* attacker, Fighter* target);

int Action_Update__31(Fighter* attacker, Fighter* target);

int Action_Update__32(Fighter* attacker, Fighter* target);
void Action_Draw__32(Fighter* attacker, Fighter* target);

int Action_Update__33(Fighter* attacker, Fighter* target);

int Action_Update__34(Fighter* attacker, Fighter* target);

int Action_Update__35(Fighter* attacker, Fighter* target);

int Action_Update__36(Fighter* attacker, Fighter* target);
void Action_Draw__36(Fighter* attacker, Fighter* target);

int Action_Update__37(Fighter* attacker, Fighter* target);

int Action_Update__38(Fighter* attacker, Fighter* target);

int Action_Update__39(Fighter* attacker, Fighter* target);

int Action_Update__40(Fighter* attacker, Fighter* target);
void Action_Draw__40(Fighter* attacker, Fighter* target);

int Action_Update__41(Fighter* attacker, Fighter* target);
void Action_Draw__41(Fighter* attacker, Fighter* target);

int Action_Update__42(Fighter* attacker, Fighter* target);
void Action_Draw__42(Fighter* attacker, Fighter* target);

int Action_Update__43(Fighter* attacker, Fighter* target);

int Action_Update__44(Fighter* attacker, Fighter* target);

int Action_Update__45(Fighter* attacker, Fighter* target);

int Action_Update__46(Fighter* attacker, Fighter* target);

int Action_Update__47(Fighter* attacker, Fighter* target);
void Action_Draw__47(Fighter* attacker, Fighter* target);

int Action_Update__48(Fighter* attacker, Fighter* target);

int Action_Update__49(Fighter* attacker, Fighter* target);
void Action_Draw__49(Fighter* attacker, Fighter* target);

int Action_Update__50(Fighter* attacker, Fighter* target);

int Action_Update__51(Fighter* attacker, Fighter* target);

int Action_Update__52(Fighter* attacker, Fighter* target);

int Action_Update__53(Fighter* attacker, Fighter* target);

int Action_Update__54(Fighter* attacker, Fighter* target);

int Action_Update__55(Fighter* attacker, Fighter* target);

int Action_Update__56(Fighter* attacker, Fighter* target);

int Action_Update__57(Fighter* attacker, Fighter* target);
void Action_Draw__57(Fighter* attacker, Fighter* target);

int Action_Update__58(Fighter* attacker, Fighter* target);
void Action_Draw__58(Fighter* attacker, Fighter* target);

int Action_Update__59(Fighter* attacker, Fighter* target);

int Action_Update__60(Fighter* attacker, Fighter* target);

int Action_Update__61(Fighter* attacker, Fighter* target);

int Action_Update__62(Fighter* attacker, Fighter* target);

int Action_Update__63(Fighter* attacker, Fighter* target);

int Action_Update__64(Fighter* attacker, Fighter* target);

int Action_Update__65(Fighter* attacker, Fighter* target);

int Action_Update__66(Fighter* attacker, Fighter* target);

int Action_Update__67(Fighter* attacker, Fighter* target);
void Action_Draw__67(Fighter* attacker, Fighter* target);

int Action_Update__68(Fighter* attacker, Fighter* target);
void Action_Draw__68(Fighter* attacker, Fighter* target);

int Action_Update__69(Fighter* attacker, Fighter* target);

int Action_Update__70(Fighter* attacker, Fighter* target);
void Action_Draw__70(Fighter* attacker, Fighter* target);

int Action_Update__71(Fighter* attacker, Fighter* target);

int Action_Update__72(Fighter* attacker, Fighter* target);

int Action_Update__73(Fighter* attacker, Fighter* target);

int Action_Update__74(Fighter* attacker, Fighter* target);

int Action_Update__75(Fighter* attacker, Fighter* target);

int Action_Update__76(Fighter* attacker, Fighter* target);

int Action_Update__77(Fighter* attacker, Fighter* target);

int Action_Update__78(Fighter* attacker, Fighter* target);

int Action_Update__79(Fighter* attacker, Fighter* target);

int Action_Update__80(Fighter* attacker, Fighter* target);

int Action_Update__81(Fighter* attacker, Fighter* target);

int Action_Update__82(Fighter* attacker, Fighter* target);
void Action_Draw__82(Fighter* attacker, Fighter* target);

int Action_Update__83(Fighter* attacker, Fighter* target);
void Action_Draw__83(Fighter* attacker, Fighter* target);

int Action_Update__84(Fighter* attacker, Fighter* target);

int Action_Update__85(Fighter* attacker, Fighter* target);
void Action_Draw__85(Fighter* attacker, Fighter* target);

int Action_Update__86(Fighter* attacker, Fighter* target);

int Action_Update__87(Fighter* attacker, Fighter* target);

int Action_Update__88(Fighter* attacker, Fighter* target);

int Action_Update__89(Fighter* attacker, Fighter* target);

int Action_Update__90(Fighter* attacker, Fighter* target);
void Action_Draw__90(Fighter* attacker, Fighter* target);

int Action_Update__91(Fighter* attacker, Fighter* target);

int Action_Update__92(Fighter* attacker, Fighter* target);

int Action_Update__93(Fighter* attacker, Fighter* target);
void Action_Draw__93(Fighter* attacker, Fighter* target);

int Action_Update__94(Fighter* attacker, Fighter* target);

int Action_Update__95(Fighter* attacker, Fighter* target);

int Action_Update__96(Fighter* attacker, Fighter* target);

int Action_Update__97(Fighter* attacker, Fighter* target);


int Action_Update__191(Fighter* attacker, Fighter* target);
void Action_Draw__191(Fighter* attacker, Fighter* target);


int Action_Update__192(Fighter* attacker, Fighter* target);
void Action_Draw__192(Fighter* attacker, Fighter* target);



void Action_AnimUpdate__0(Fighter* attacker, Fighter* target);
void Action_AnimDraw__0(Fighter* attacker, Fighter* target);

void Action_AnimDraw__1(Fighter* attacker, Fighter* target);

void Action_AnimDraw__2(Fighter* attacker, Fighter* target);

void Action_AnimDraw__3(Fighter* attacker, Fighter* target);

void Action_AnimDraw__4(Fighter* attacker, Fighter* target);

void Action_AnimDraw__5(Fighter* attacker, Fighter* target);

void Action_AnimDraw__6(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__7(Fighter* attacker, Fighter* target);
void Action_AnimDraw__7(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__8(Fighter* attacker, Fighter* target);
void Action_AnimDraw__8(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__9(Fighter* attacker, Fighter* target);
void Action_AnimDraw__9(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__10(Fighter* attacker, Fighter* target);
void Action_AnimDraw__10(Fighter* attacker, Fighter* target);

void Action_AnimDraw__11(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__12(Fighter* attacker, Fighter* target);
void Action_AnimDraw__12(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__13(Fighter* attacker, Fighter* target);
void Action_AnimDraw__13(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__14(Fighter* attacker, Fighter* target);
void Action_AnimDraw__14(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__15(Fighter* attacker, Fighter* target);
void Action_AnimDraw__15(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__16(Fighter* attacker, Fighter* target);
void Action_AnimDraw__16(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__17(Fighter* attacker, Fighter* target);
void Action_AnimDraw__17(Fighter* attacker, Fighter* target);

void Action_AnimDraw__18(Fighter* attacker, Fighter* target);

void Action_AnimDraw__19(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__20(Fighter* attacker, Fighter* target);
void Action_AnimDraw__20(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__21(Fighter* attacker, Fighter* target);
void Action_AnimDraw__21(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__22(Fighter* attacker, Fighter* target);
void Action_AnimDraw__22(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__23(Fighter* attacker, Fighter* target);
void Action_AnimDraw__23(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__24(Fighter* attacker, Fighter* target);
void Action_AnimDraw__24(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__25(Fighter* attacker, Fighter* target);
void Action_AnimDraw__25(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__26(Fighter* attacker, Fighter* target);
void Action_AnimDraw__26(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__27(Fighter* attacker, Fighter* target);
void Action_AnimDraw__27(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__28(Fighter* attacker, Fighter* target);
void Action_AnimDraw__28(Fighter* attacker, Fighter* target);

void Action_AnimDraw__29(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__30(Fighter* attacker, Fighter* target);
void Action_AnimDraw__30(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__31(Fighter* attacker, Fighter* target);
void Action_AnimDraw__31(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__32(Fighter* attacker, Fighter* target);
void Action_AnimDraw__32(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__33(Fighter* attacker, Fighter* target);
void Action_AnimDraw__33(Fighter* attacker, Fighter* target);

void Action_AnimDraw__34(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__35(Fighter* attacker, Fighter* target);
void Action_AnimDraw__35(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__36(Fighter* attacker, Fighter* target);
void Action_AnimDraw__36(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__37(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__38(Fighter* attacker, Fighter* target);
void Action_AnimDraw__38(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__39(Fighter* attacker, Fighter* target);
void Action_AnimDraw__39(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__40(Fighter* attacker, Fighter* target);
void Action_AnimDraw__40(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__41(Fighter* attacker, Fighter* target);
void Action_AnimDraw__41(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__42(Fighter* attacker, Fighter* target);
void Action_AnimDraw__42(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__43(Fighter* attacker, Fighter* target);
void Action_AnimDraw__43(Fighter* attacker, Fighter* target);

void Action_AnimDraw__44(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__45(Fighter* attacker, Fighter* target);
void Action_AnimDraw__45(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__46(Fighter* attacker, Fighter* target);
void Action_AnimDraw__46(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__47(Fighter* attacker, Fighter* target);
void Action_AnimDraw__47(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__48(Fighter* attacker, Fighter* target);
void Action_AnimDraw__48(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__49(Fighter* attacker, Fighter* target);
void Action_AnimDraw__49(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__50(Fighter* attacker, Fighter* target);
void Action_AnimDraw__50(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__51(Fighter* attacker, Fighter* target);
void Action_AnimDraw__51(Fighter* attacker, Fighter* target);

void Action_AnimDraw__52(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__53(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__54(Fighter* attacker, Fighter* target);
void Action_AnimDraw__54(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__55(Fighter* attacker, Fighter* target);
void Action_AnimDraw__55(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__56(Fighter* attacker, Fighter* target);
void Action_AnimDraw__56(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__57(Fighter* attacker, Fighter* target);
void Action_AnimDraw__57(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__58(Fighter* attacker, Fighter* target);
void Action_AnimDraw__58(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__59(Fighter* attacker, Fighter* target);
void Action_AnimDraw__59(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__60(Fighter* attacker, Fighter* target);
void Action_AnimDraw__60(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__61(Fighter* attacker, Fighter* target);
void Action_AnimDraw__61(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__62(Fighter* attacker, Fighter* target);
void Action_AnimDraw__62(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__63(Fighter* attacker, Fighter* target);
void Action_AnimDraw__63(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__64(Fighter* attacker, Fighter* target);
void Action_AnimDraw__64(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__65(Fighter* attacker, Fighter* target);
void Action_AnimDraw__65(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__66(Fighter* attacker, Fighter* target);
void Action_AnimDraw__66(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__67(Fighter* attacker, Fighter* target);
void Action_AnimDraw__67(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__68(Fighter* attacker, Fighter* target);
void Action_AnimDraw__68(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__69(Fighter* attacker, Fighter* target);
void Action_AnimDraw__69(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__70(Fighter* attacker, Fighter* target);
void Action_AnimDraw__70(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__71(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__72(Fighter* attacker, Fighter* target);
void Action_AnimDraw__72(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__73(Fighter* attacker, Fighter* target);
void Action_AnimDraw__73(Fighter* attacker, Fighter* target);

void Action_AnimUpdate__74(Fighter* attacker, Fighter* target);
void Action_AnimDraw__74(Fighter* attacker, Fighter* target);
