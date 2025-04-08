#pragma once

typedef struct {
	int spriteId;
	int backSpriteId;
} BattleHead;

typedef struct {
	int spriteId;
	int headFrame[20];
	int headOffsetX[20];
	int headOffsetY[20];
} BattleBody;

enum {
	BATTLEBODY_HEAD_MIRROR = 1 << 16,
	BATTLEBODY_HEAD_FLIP = 1 << 17,
};

extern BattleHead battleHeadData[OBJECT_COUNT_MAX];
extern BattleBody battleBodyData[OBJECT_COUNT_MAX];

void LoadBattleBodyData();
void BattleBody_SetStateData(BattleBody* battleBody, int state, int headFrame, int headOffsetX, int headOffsetY);
