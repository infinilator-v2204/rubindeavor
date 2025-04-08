#include <stdint.h>

#include "generic.h"
#include "sprites.h"
#include "audio.h"
#include "mapeditor.h"
#include "overworld.h"
#include "battlesystem.h"

MapEditor mapEditor;

void MapEditor_Init() {
	Audio_StopMusic();
	overworld.camera.x = 160;
	overworld.camera.y = 120;
	overworld.camera.zoom = 2;
	
	overworld.map.tilesetSpriteId = SPR_tileset_day;
	
	overworld.map.w = 4;
	overworld.map.h = 4;
	
	for (int j = 0; j < overworld.map.h; j++)
	for (int i = 0; i < overworld.map.w; i++) {
		overworld.map.tileMap[j][i] = 0;
	}
	
	mapEditor.zoomId = 4;
	mapEditor.tileId = 0;
	mapEditor.tilesetVisible = 0;
	mapEditor.mode = MAPEDITOR_PLACEMODE_TILE;
	mapEditor.decorationWidth = 1;
	mapEditor.decorationHeight = 1;
	mapEditor.selectX = 0;
	mapEditor.selectY = 0;
	mapEditor.selectW = 0;
	mapEditor.selectH = 0;
	mapEditor.tilesetCamera.x = 320;
	mapEditor.tilesetCamera.y = 240;
	
	SetString(mapEditor.levelFileName, "_temp");
	
	mapEditor.hoverAreaId = -1;
	mapEditor.moving = false;
}

void MapEditor_Update() {
	#ifdef RXS_INCLUDE_MAP_EDITOR
	mapEditor.moving = false;
	if (game.keyStates[SDL_SCANCODE_LSHIFT]) {
		if (game.keyPressed[SDL_SCANCODE_LEFT] || game.keyPressed[SDL_SCANCODE_A]) {
			if (mapEditor.tileId > 0) mapEditor.tileId--;
			mapEditor.selectW = 0;
		}
		if (game.keyPressed[SDL_SCANCODE_RIGHT] || game.keyPressed[SDL_SCANCODE_D]) {
			if (mapEditor.tileId < 64*128 - 1) mapEditor.tileId++;
			mapEditor.selectW = 0;
		}
		if (game.keyPressed[SDL_SCANCODE_UP] || game.keyPressed[SDL_SCANCODE_W]) {
			if (mapEditor.tileId >= 64) mapEditor.tileId -= 64;
			mapEditor.selectW = 0;
		}
		if (game.keyPressed[SDL_SCANCODE_DOWN] || game.keyPressed[SDL_SCANCODE_S]) {
			if (mapEditor.tileId < 64*128 - 64) mapEditor.tileId += 64;
			mapEditor.selectW = 0;
		}
	}
	else if (mapEditor.tilesetVisible) {
		if (game.keyStates[SDL_SCANCODE_LEFT] || game.keyStates[SDL_SCANCODE_A]) {
			mapEditor.tilesetCamera.x -= 8;
			if (mapEditor.tilesetCamera.x < 320) mapEditor.tilesetCamera.x = 320;
		}
		if (game.keyStates[SDL_SCANCODE_RIGHT] || game.keyStates[SDL_SCANCODE_D]) {
			mapEditor.tilesetCamera.x += 8;
			if (mapEditor.tilesetCamera.x > 704) mapEditor.tilesetCamera.x = 704;
		}
		if (game.keyStates[SDL_SCANCODE_UP] || game.keyStates[SDL_SCANCODE_W]) {
			mapEditor.tilesetCamera.y -= 8;
			if (mapEditor.tilesetCamera.y < 240) mapEditor.tilesetCamera.y = 240;
		}
		if (game.keyStates[SDL_SCANCODE_DOWN] || game.keyStates[SDL_SCANCODE_S]) {
			mapEditor.tilesetCamera.y += 8;
			if (mapEditor.tilesetCamera.y > 1808) mapEditor.tilesetCamera.y = 1808;
		}
	}
	else {
		if (game.keyStates[SDL_SCANCODE_LEFT] || game.keyStates[SDL_SCANCODE_A]) {
			overworld.camera.x -= 16 / overworld.camera.zoom;
			mapEditor.moving = true;
		}
		if (game.keyStates[SDL_SCANCODE_RIGHT] || game.keyStates[SDL_SCANCODE_D]) {
			overworld.camera.x += 16 / overworld.camera.zoom;
			mapEditor.moving = true;
		}
		if (game.keyStates[SDL_SCANCODE_UP] || game.keyStates[SDL_SCANCODE_W]) {
			overworld.camera.y -= 16 / overworld.camera.zoom;
			mapEditor.moving = true;
		}
		if (game.keyStates[SDL_SCANCODE_DOWN] || game.keyStates[SDL_SCANCODE_S]) {
			overworld.camera.y += 16 / overworld.camera.zoom;
			mapEditor.moving = true;
		}
	}
	
	if (game.mouseScrollY < 0 && mapEditor.zoomId > 1) {
		mapEditor.zoomId--;
		switch (mapEditor.zoomId) {
			case 0: overworld.camera.zoom = 0.125; break;
			case 1: overworld.camera.zoom = 0.25; break;
			case 2: overworld.camera.zoom = 0.5; break;
			case 3: overworld.camera.zoom = 1; break;
			case 4: overworld.camera.zoom = 2; break;
		}
		mapEditor.moving = true;
	}
	if (game.mouseScrollY > 0 && mapEditor.zoomId < 4) {
		mapEditor.zoomId++;
		switch (mapEditor.zoomId) {
			case 0: overworld.camera.zoom = 0.125; break;
			case 1: overworld.camera.zoom = 0.25; break;
			case 2: overworld.camera.zoom = 0.5; break;
			case 3: overworld.camera.zoom = 1; break;
			case 4: overworld.camera.zoom = 2; break;
		}
		mapEditor.moving = true;
	}
	
	if (game.keyPressed[SDL_SCANCODE_SPACE]) {
		mapEditor.mode++;
		if (mapEditor.mode >= 2) mapEditor.mode = 0;
	}
	
	if (game.keyPressed[SDL_SCANCODE_MINUS]) {
		if (mapEditor.mode == MAPEDITOR_PLACEMODE_DECORATION) {
			if (game.keyStates[SDL_SCANCODE_LSHIFT]) {
				if (mapEditor.decorationWidth > 1) mapEditor.decorationWidth--;
			}
			else {
				if (mapEditor.decorationHeight > 1) mapEditor.decorationHeight--;
			}
		}
		else {
			overworld.map.tilesetSpriteId--;
			if (overworld.map.tilesetSpriteId < firstTilesetSpriteId) overworld.map.tilesetSpriteId = lastTilesetSpriteId;
		}
	}
	if (game.keyPressed[SDL_SCANCODE_EQUALS]) {
		if (mapEditor.mode == MAPEDITOR_PLACEMODE_DECORATION) {
			if (game.keyStates[SDL_SCANCODE_LSHIFT]) {
				if (mapEditor.decorationWidth < 8) mapEditor.decorationWidth++;
			}
			else {
				if (mapEditor.decorationHeight < 8) mapEditor.decorationHeight++;
			}
		}
		else {
			overworld.map.tilesetSpriteId++;
			if (overworld.map.tilesetSpriteId > lastTilesetSpriteId) overworld.map.tilesetSpriteId = firstTilesetSpriteId;
		}
	}
	
	if (game.keyPressed[SDL_SCANCODE_T]) {
		mapEditor.tilesetVisible = !mapEditor.tilesetVisible;
	}
	
	Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
	if (game.keyPressed[SDL_SCANCODE_C]) {
		int x = (int)(GetWorldX(game.mouseX) + 16) / 16 - 1;
		int y = (int)(GetWorldY(game.mouseY) + 16) / 16 - 1;
		mapEditor.selectX = x;
		mapEditor.selectY = y;
		mapEditor.selectW = 1;
		mapEditor.selectH = 1;
	}
	else if (game.keyStates[SDL_SCANCODE_C]) {
		int x = (int)(GetWorldX(game.mouseX) + 16) / 16 - 1;
		int y = (int)(GetWorldY(game.mouseY) + 16) / 16 - 1;
		mapEditor.selectW = x - mapEditor.selectX + 1;
		mapEditor.selectH = y - mapEditor.selectY + 1;
		if (mapEditor.selectW > 32) mapEditor.selectW = 32;
		if (mapEditor.selectH > 32) mapEditor.selectH = 32;
	}
	else if (game.keyReleased[SDL_SCANCODE_C]) {
		for (int j = 0; j < mapEditor.selectH; j++)
		for (int i = 0; i < mapEditor.selectW; i++) {
			if (i + mapEditor.selectX < 0 || i + mapEditor.selectX >= overworld.map.w || j + mapEditor.selectY < 0 || j + mapEditor.selectY >= overworld.map.h) continue;
			mapEditor.selectTiles[j][i] = overworld.map.tileMap[j + mapEditor.selectY][i + mapEditor.selectX];
		}
	}
	
	if (MouseHeld(MOUSE_LEFT) || MouseHeld(MOUSE_RIGHT)) {
		if (!game.keyStates[SDL_SCANCODE_R]) {
			if (mapEditor.tilesetVisible) {
				Drawer_SetProjection(mapEditor.tilesetCamera.x, mapEditor.tilesetCamera.y, 1);
				for (int j = 0; j < 128; j++)
				for (int i = 0; i < 64; i++) {
					if (MouseRectangleHover(i * 16, j * 16, 16, 16)) {
						mapEditor.tileId = j*64 + i;
						mapEditor.selectW = 0;
						break;
					}
				}
			}
			else {
				Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
				int x = (int)(GetWorldX(game.mouseX) + 16) / 16 - 1;
				int y = (int)(GetWorldY(game.mouseY) + 16) / 16 - 1;
				
				if (mapEditor.mode == MAPEDITOR_PLACEMODE_DECORATION) {
					for (int i = 0; i < overworld.map.decorationCount; i++) {
						OverworldObject* object = &overworld.map.decorations[i];
						
						if (object->x >= x * 16 && object->x < (x + 1) * 16 && object->y > y * 16 && object->y <= (y + 1) * 16) {
							Overworld_DeleteDecoration(i--);
						}
					}
					if (MouseHeld(MOUSE_LEFT)) Overworld_CreateDecoration(x * 16, y * 16, mapEditor.tileId, mapEditor.decorationWidth, mapEditor.decorationHeight);
				}
				else if (mapEditor.mode == MAPEDITOR_PLACEMODE_TILE && mapEditor.selectW >= 1) {
					for (int j = 0; j < mapEditor.selectH; j++)
					for (int i = 0; i < mapEditor.selectW; i++) {
						if (i + x < 0 || i + x >= overworld.map.w || j + y < 0 || j + y >= overworld.map.h) continue;
						overworld.map.tileMap[y + j][x + i] = mapEditor.selectTiles[j][i];
					}
				}
				else if (x >= 0 && x < overworld.map.w && y >= 0 && y < overworld.map.h) {
					overworld.map.tileMap[y][x] = mapEditor.tileId;
				}
			}
		}
	}
	
	if (MousePressed(MOUSE_LEFT)) {
		if (game.keyStates[SDL_SCANCODE_R]) {
			Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
			int x = (int)(GetWorldX(game.mouseX) + 16000) / 16 - 1000;
			int y = (int)(GetWorldY(game.mouseY) + 16000) / 16 - 1000;
			
			if (x < 0) {
				overworld.map.w += -x;
				overworld.camera.x -= x * 16;
				for (int j = overworld.map.h - 1; j >= 0; j--)
				for (int i = overworld.map.w - 1; i >= 0; i--) {
					if (i >= -x) {
						overworld.map.tileMap[j][i] = overworld.map.tileMap[j][i - -x];
					}
					else {
						overworld.map.tileMap[j][i] = 0;
					}
				}
			}
			else if (x < overworld.map.w / 2) {
				overworld.map.w += -x;
				overworld.camera.x -= x * 16;
				for (int j = 0; j <= overworld.map.h - 1; j++)
				for (int i = 0; i <= overworld.map.w - 1; i++) {
					if (i < overworld.map.w) {
						overworld.map.tileMap[j][i] = overworld.map.tileMap[j][i - -x];
					}
					else {
						overworld.map.tileMap[j][i] = 0;
					}
				}
			}
			else {
				overworld.map.w = x;
			}
			
			if (y < 0) {
				overworld.map.h += -y;
				overworld.camera.y -= y * 16;
				for (int j = overworld.map.h - 1; j >= 0; j--)
				for (int i = overworld.map.w - 1; i >= 0; i--) {
					if (j >= -y) {
						overworld.map.tileMap[j][i] = overworld.map.tileMap[j - -y][i];
					}
					else {
						overworld.map.tileMap[j][i] = 0;
					}
				}
			}
			else if (y < overworld.map.h / 2) {
				overworld.map.h += -y;
				overworld.camera.y -= y * 16;
				for (int j = 0; j <= overworld.map.h - 1; j++)
				for (int i = 0; i <= overworld.map.w - 1; i++) {
					if (j < overworld.map.h) {
						overworld.map.tileMap[j][i] = overworld.map.tileMap[j - -y][i];
					}
					else {
						overworld.map.tileMap[j][i] = 0;
					}
				}
			}
			else {
				overworld.map.h = y;
			}
		}
	}
	
	if (game.keyStates[SDL_SCANCODE_LCTRL]) {
		if (game.keyPressed[SDL_SCANCODE_S]) {
			MapEditor_SaveMap();
		}
		if (game.keyPressed[SDL_SCANCODE_L]) {
			MapEditor_LoadMap();
		}
	}
	#endif
}

void MapEditor_Draw() {
	#ifdef RXS_INCLUDE_MAP_EDITOR
	Drawer_SetProjection(320, 240, 1);
	
	Drawer_SetDrawColor(23, 23, 23);
	Drawer_FillRect(0, 0, 640, 480);
	Drawer_SetDrawColor(255, 255, 255);
	
	Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
	
	Overworld_DrawMap();
	
	int objectCount = 0;
	int objectOrder[OBJECT_COUNT_MAX];
	
	for (int i = 8; i < OBJECT_COUNT_MAX; i++) {
		if (overworld.objects[i].type == 0) continue;
		OverworldObject* object = &overworld.objects[i];
		if (object->x < overworld.camera.x - SCREEN_WIDTH / 2 / overworld.camera.zoom - 64 || object->x > overworld.camera.x + SCREEN_WIDTH / 2 / overworld.camera.zoom + 64 || object->y < overworld.camera.y - SCREEN_HEIGHT / 2 / overworld.camera.zoom - 64 || object->y > overworld.camera.y + SCREEN_HEIGHT / 2 / overworld.camera.zoom + 64) continue;
		objectOrder[objectCount++] = i;
	}
	
	for (int i = 0; i < overworld.map.decorationCount; i++) {
		if (objectCount >= OBJECT_COUNT_MAX) break;
		OverworldObject* object = &overworld.map.decorations[i];
		if (object->x < overworld.camera.x - SCREEN_WIDTH / 2 / overworld.camera.zoom - 64 || object->x > overworld.camera.x + SCREEN_WIDTH / 2 / overworld.camera.zoom + 64 || object->y < overworld.camera.y - SCREEN_HEIGHT / 2 / overworld.camera.zoom - 64 || object->y > overworld.camera.y + SCREEN_HEIGHT / 2 / overworld.camera.zoom + 64) continue;
		objectOrder[objectCount++] = 10000 + i;
	}
	
	for (int i = 0; i < objectCount; i++) {
		for (int j = 0; j < objectCount - 1; j++) {
			OverworldObject* object1;
			OverworldObject* object2;
			
			if (objectOrder[j] >= 10000)
				object1 = &overworld.map.decorations[objectOrder[j] - 10000];
			else
				object1 = &overworld.objects[objectOrder[j]];
			
			if (objectOrder[j+1] >= 10000)
				object2 = &overworld.map.decorations[objectOrder[j+1] - 10000];
			else
				object2 = &overworld.objects[objectOrder[j+1]];
			
			if (object1->depth < object2->depth) {
				int temp = objectOrder[j];
				objectOrder[j] = objectOrder[j+1];
				objectOrder[j+1] = temp;
			}
		}
	}
	
	for (int i = 0; i < objectCount; i++) {
		OverworldObject* object;
		
		if (objectOrder[i] >= 10000)
			object = &overworld.map.decorations[objectOrder[i] - 10000];
		else
			object = &overworld.objects[objectOrder[i]];
		
		Drawer_SetDrawColor(object->color[0], object->color[1], object->color[2]);
		
		if (object->type == 4) {
			for (int k = 0; k < object->vars[1].i; k++)
			for (int j = 0; j < object->vars[0].i; j++) {
				Drawer_DrawSprite(overworld.map.tilesetSpriteId, object->x - 8 - (object->vars[1].i - 1) * 8 + k * 16, object->y - 16 * (1 + j), object->id - 64 * j + k, 1, 1);
			}
		}
		else if (object->bodyId >= 0) {
			DrawFighterChar(object->headId, object->bodyId, object->fighterState, object->x, object->y, 1, 1, 1 - (object->direction == OBJECT_DIRECTION_LEFT) * 2);
		}
		else if (object->spriteId >= 0) {
			if (object->direction == OBJECT_DIRECTION_LEFT)
				Drawer_DrawSprite(object->spriteId, object->x, object->y, object->spriteFrame, -1, 1);
			else
				Drawer_DrawSprite(object->spriteId, object->x, object->y, object->spriteFrame, 1, 1);
		}
	}
	Drawer_SetDrawColor(255, 255, 255);
	
	for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
		if (!overworld.map.doors[i].enabled) continue;
		float x1 = overworld.map.doors[i].x1;
		float y1 = overworld.map.doors[i].y1;
		float x2 = overworld.map.doors[i].x2;
		float y2 = overworld.map.doors[i].y2;
		if (x1 >= overworld.camera.x - SCREEN_WIDTH * 2 && x1 <= overworld.camera.x + SCREEN_WIDTH * 2 && y1 >= overworld.camera.y - SCREEN_HEIGHT * 2 && y1 <= overworld.camera.y + SCREEN_HEIGHT * 2) {
			Drawer_FillRect(x1, y1, 2, 2);
			snprintf(game.textBuffer, 32, "Door\n%d", i);
			Drawer_DrawText(game.textBuffer, 32, x1, y1, 0.5, 0.5);
		}
		if (x2 >= overworld.camera.x - SCREEN_WIDTH * 2 && x2 <= overworld.camera.x + SCREEN_WIDTH * 2 && y2 >= overworld.camera.y - SCREEN_HEIGHT * 2 && y2 <= overworld.camera.y + SCREEN_HEIGHT * 2) {
			Drawer_FillRect(x2, y2, 2, 2);
			snprintf(game.textBuffer, 32, "Door\n%d", i);
			Drawer_DrawText(game.textBuffer, 32, x2, y2, 0.5, 0.5);
		}
	}
	
	int x = (int)(GetWorldX(game.mouseX) + 16000) / 16 - 1000;
	int y = (int)(GetWorldY(game.mouseY) + 16000) / 16 - 1000;
	
	if (mapEditor.mode == MAPEDITOR_PLACEMODE_TILE) {
		if (game.keyStates[SDL_SCANCODE_C]) {
			Drawer_SetDrawAlpha(127);
			Drawer_FillRect(mapEditor.selectX * 16, mapEditor.selectY * 16, mapEditor.selectW * 16, mapEditor.selectH * 16);
			Drawer_SetDrawAlpha(255);
		}
		else if (mapEditor.selectW >= 1) {
			for (int j = 0; j < mapEditor.selectH; j++)
			for (int i = 0; i < mapEditor.selectW; i++) {
				Drawer_DrawSprite(overworld.map.tilesetSpriteId, (x + i) * 16, (y + j) * 16, mapEditor.selectTiles[j][i], 1, 1);
			}
		}
		else if (x >= 0 && x < overworld.map.w && y >= 0 && y < overworld.map.h) {
			Drawer_DrawSprite(overworld.map.tilesetSpriteId, x * 16, y * 16, mapEditor.tileId, 1, 1);
		}
	}
	else if (mapEditor.mode == MAPEDITOR_PLACEMODE_DECORATION) {
		for (int j = 0; j < mapEditor.decorationWidth; j++)
		for (int i = 0; i < mapEditor.decorationHeight; i++) {
			if (x >= 0 && x < overworld.map.w && y - i >= 0 && y - i < overworld.map.h && mapEditor.tileId - 64 * i >= 0) {
				Drawer_DrawSprite(overworld.map.tilesetSpriteId, (x + j) * 16 - (mapEditor.decorationWidth - 1) * 8, (y - i) * 16, mapEditor.tileId - 64 * i + j, 1, 1);
			}
		}
	}
	
	Drawer_SetProjection(320, 240, 1);
	
	if (mapEditor.tilesetVisible) {
		Drawer_SetProjection(320, 240, 1);
		
		Drawer_SetDrawColor(32, 32, 32);
		Drawer_FillRect(0, 0, 640, 480);
		Drawer_SetDrawColor(255, 255, 255);
		
		Drawer_SetProjection(mapEditor.tilesetCamera.x, mapEditor.tilesetCamera.y, 1);
		
		for (int j = 0; j < 128; j++)
		for (int i = 0; i < 64; i++) {
			Drawer_DrawSprite(overworld.map.tilesetSpriteId, i * 16, j * 16, j*64 + i, 1, 1);
			if (mapEditor.tileId == j*64 + i) {
				Drawer_SetDrawAlpha(127);
				Drawer_FillRect(i * 16, j * 16, 16, 16);
				Drawer_SetDrawAlpha(255);
			}
		}
		
		Drawer_SetProjection(320, 240, 1);
	}
	else {
		if ((game.mouseX != game.mouseXPrev || game.mouseY != game.mouseYPrev || mapEditor.moving) && game.timer % 4 == 0) {
			mapEditor.hoverAreaId = -1;
			Drawer_SetProjection(overworld.camera.x, overworld.camera.y, overworld.camera.zoom);
			int mouseX = (int)(GetWorldX(game.mouseX) + 16000) / 16 - 1000;
			int mouseY = (int)(GetWorldY(game.mouseY) + 16000) / 16 - 1000;
			Drawer_SetProjection(320, 240, 1);
			for (int i = 0; i < OBJECT_COUNT_MAX; i++) {
				int x1 = overworld.map.areas[i].x1;
				int x2 = overworld.map.areas[i].x2;
				int y1 = overworld.map.areas[i].y1;
				int y2 = overworld.map.areas[i].y2;
				if (mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2) {
					mapEditor.hoverAreaId = i;
					break;
				}
			}
		}
		
		Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
		snprintf(game.textBuffer, 128, "x: %d (tile %d)\ny: %d (tile %d)\ntileId: %d\nareaId: %d", x * 16, x, y * 16, y, mapEditor.tileId, mapEditor.hoverAreaId);
		Drawer_DrawText(game.textBuffer, 128, 4, 4, 2, 2);
		
		if (mapEditor.mode == MAPEDITOR_PLACEMODE_DECORATION) {
			snprintf(game.textBuffer, 64, "Decoration count: %d", overworld.map.decorationCount);
			Drawer_DrawText(game.textBuffer, 64, 4, SCREEN_HEIGHT - 32, 2, 2);
		}
	}
	#endif
}

int MapEditor_LoadMap() {
	return Overworld_LoadMap("level/_temp.bin");
}

int MapEditor_SaveMap() {
	char fileName[128];
	snprintf(fileName, 128, "level/%s.bin", mapEditor.levelFileName);
	FILE* file = fopen(fileName, "wb");
	
	if (file == NULL) return 0;
	
	fputc((uint8_t)overworld.map.w, file);
	fputc((uint8_t)(overworld.map.w >> 8), file);
	fputc((uint8_t)overworld.map.h, file);
	fputc((uint8_t)(overworld.map.h >> 8), file);
	
	for (int j = 0; j < overworld.map.h; j++)
	for (int i = 0; i < overworld.map.w; i++) {
		fputc((uint8_t)overworld.map.tileMap[j][i], file);
		fputc((uint8_t)(overworld.map.tileMap[j][i] >> 8), file);
	}
	
	fputc((uint8_t)overworld.map.decorationCount, file);
	fputc((uint8_t)(overworld.map.decorationCount >> 8), file);
	
	for (int i = 0; i < overworld.map.decorationCount; i++) {
		fputc((uint8_t)(overworld.map.decorations[i].x - 8), file);
		fputc((uint8_t)((int)(overworld.map.decorations[i].x - 8) >> 8), file);
		
		fputc((uint8_t)(overworld.map.decorations[i].y - 16), file);
		fputc((uint8_t)((int)(overworld.map.decorations[i].y - 16) >> 8), file);
		
		fputc((uint8_t)overworld.map.decorations[i].id, file);
		fputc((uint8_t)(overworld.map.decorations[i].id >> 8), file);
		
		fputc((uint8_t)overworld.map.decorations[i].vars[0].i, file);
		fputc((uint8_t)(overworld.map.decorations[i].vars[0].i >> 8), file);
		
		fputc((uint8_t)overworld.map.decorations[i].vars[1].i, file);
		fputc((uint8_t)(overworld.map.decorations[i].vars[1].i >> 8), file);
	}
	
	fclose(file);
	return 1;
}
