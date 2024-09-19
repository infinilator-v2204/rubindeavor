#pragma once

typedef struct {
	char levelFileName[64];
	
	int zoomId;
	int tileId;
	int tilesetVisible;
	int mode;
	int decorationWidth;
	int decorationHeight;
	int selectX;
	int selectY;
	int selectW;
	int selectH;
	short selectTiles[32][32];
	
	struct {
		float x;
		float y;
	} tilesetCamera;
	
	int hoverAreaId;
	bool moving;
} MapEditor;

enum {
	MAPEDITOR_PLACEMODE_TILE,
	MAPEDITOR_PLACEMODE_DECORATION
};

extern MapEditor mapEditor;

void MapEditor_Init();
void MapEditor_Update();
void MapEditor_Draw();
int MapEditor_LoadMap();
int MapEditor_SaveMap();
