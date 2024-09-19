#pragma once

typedef struct {
	char name[32];
	int type;
	int actionId;
	union {
		int i;
		float f;
	} vars[4];
} Item;

extern Item itemData[OBJECT_COUNT_MAX];



void LoadItemData();

void Item_UseInOverworld(int inventoryId, int partyId);
