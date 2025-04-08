#include "generic.h"
#include "menu.h"
#include "sprites.h"
#include "audio.h"
#include "dialog.h"

void Menu_New(Menu* menu, int id, int pageColumns, int pageRows, int cursorId) {
	Menu_ClearOptions(menu);
	menu->id = id;
	menu->pageColumns = pageColumns;
	menu->pageRows = pageRows;
	menu->cursorId = cursorId;
	menu->page = menu->cursors[menu->cursorId] / (pageColumns * pageRows);
	menu->holdTimer = 0;
	menu->canNavigate = true;
}

void Menu_ResetCursor(Menu* menu) {
	menu->cursors[menu->cursorId] = 0;
	menu->page = 0;
}

void Menu_SetCursor(Menu* menu, int optionId) {
	menu->cursors[menu->cursorId] = optionId;
	menu->page = optionId / (menu->pageColumns * menu->pageRows);
}

void Menu_ClearOptions(Menu* menu) {
	menu->optionCount = 0;
	menu->optionPressed = -1;
	menu->optionPressedValue = 0;
	menu->page = 0;
	menu->pageCount = 1;
}

void Menu_AddOption(Menu* menu, bool enabled, int value, const char* name) {
	MenuOption* option = &menu->options[menu->optionCount++];
	
	option->enabled = enabled;
	option->value = value;
	option->type = MENUOPTION_TYPE_BUTTON;
	SetString(option->name, name);
	
	if (menu->optionCount > menu->pageColumns * menu->pageRows * menu->pageCount) {
		menu->pageCount++;
	}
}

void Menu_AddOption_Number(Menu* menu, bool enabled, int value, const char* name, int valueMin, int valueMax) {
	Menu_AddOption(menu, enabled, value, name);
	MenuOption* option = &menu->options[menu->optionCount - 1];
	
	option->type = MENUOPTION_TYPE_NUMBER;
	option->valueMin = valueMin;
	option->valueMax = valueMax;
}

void Menu_AddOption_Boolean(Menu* menu, bool enabled, int value, const char* name) {
	Menu_AddOption(menu, enabled, value, name);
	MenuOption* option = &menu->options[menu->optionCount - 1];
	
	option->type = MENUOPTION_TYPE_BOOLEAN;
}



void Menu_Update(Menu* menu) {
	int cursor = menu->cursors[menu->cursorId];
	MenuOption* option = &menu->options[cursor];
	
	bool hold = false;
	
	if (menu->canNavigate) {
		if (PlayerButtonHeld(PLAYER_BUTTON_LEFT)) {
			hold = true;
			
			if (menu->holdTimer == 0 || (menu->holdTimer >= 16 && menu->holdTimer % 4 == 0)) {
				if (option->type == MENUOPTION_TYPE_NUMBER) {
					if (option->value - 1 >= option->valueMin) {
						option->value--;
						Audio_PlaySoundInterrupt(SND_menu4);
					}
				}
				else if (cursor - 1 >= 0) {
					if (cursor % menu->pageColumns == 0) {
						if (menu->page > 0) {
							cursor -= menu->pageColumns * menu->pageRows;
							menu->page--;
							Audio_PlaySoundInterrupt(SND_menu5);
						}
					}
					else {
						cursor--;
						Audio_PlaySoundInterrupt(SND_menu5);
					}
				}
			}
		}
		if (PlayerButtonHeld(PLAYER_BUTTON_RIGHT)) {
			hold = true;
			
			if (menu->holdTimer == 0 || (menu->holdTimer >= 16 && menu->holdTimer % 4 == 0)) {
				if (option->type == MENUOPTION_TYPE_NUMBER) {
					if (option->value + 1 <= option->valueMax) {
						option->value++;
						Audio_PlaySoundInterrupt(SND_menu4);
					}
				}
				else if (cursor + 1 < menu->optionCount) {
					if (cursor % menu->pageColumns == menu->pageColumns - 1) {
						if (menu->page < menu->pageCount - 1) {
							cursor += menu->pageColumns * menu->pageRows;
							menu->page++;
							if (cursor >= menu->optionCount) cursor = menu->optionCount - 1;
							Audio_PlaySoundInterrupt(SND_menu5);
						}
					}
					else {
						cursor++;
						Audio_PlaySoundInterrupt(SND_menu5);
					}
				}
			}
		}
		if (PlayerButtonHeld(PLAYER_BUTTON_UP)) {
			hold = true;
			
			if (menu->holdTimer == 0 || (menu->holdTimer >= 16 && menu->holdTimer % 4 == 0)) {
				if ((cursor % (menu->pageColumns * menu->pageRows)) - menu->pageColumns >= 0) {
					cursor -= menu->pageColumns;
					Audio_PlaySoundInterrupt(SND_menu4);
				}
			}
		}
		if (PlayerButtonHeld(PLAYER_BUTTON_DOWN)) {
			hold = true;
			
			if (menu->holdTimer == 0 || (menu->holdTimer >= 16 && menu->holdTimer % 4 == 0)) {
				if ((cursor % (menu->pageColumns * menu->pageRows)) + menu->pageColumns < menu->pageColumns * menu->pageRows && cursor + menu->pageColumns < menu->optionCount) {
					cursor += menu->pageColumns;
					Audio_PlaySoundInterrupt(SND_menu4);
				}
			}
		}
	}
	
	if (hold)
		menu->holdTimer++;
	else
		menu->holdTimer = 0;
	
	if (PlayerButtonPressed(PLAYER_BUTTON_Z) && menu->options[cursor].enabled) {
		if (menu->options[cursor].type == MENUOPTION_TYPE_BUTTON) {
			Audio_PlaySoundInterrupt(SND_menu6);
		}
		else if (menu->options[cursor].type == MENUOPTION_TYPE_BOOLEAN) {
			Audio_PlaySoundInterrupt(SND_menu6);
			menu->options[cursor].value = !menu->options[cursor].value;
		}
		menu->optionPressed = cursor;
		menu->optionPressedValue = menu->options[cursor].value;
	}
	else if (PlayerButtonPressed(PLAYER_BUTTON_X)) {
		Audio_PlaySoundInterrupt(SND_menu3);
		menu->optionPressed = MENUOPTION_BACK;
	}
	else {
		menu->optionPressed = MENUOPTION_NONE;
	}
	
	menu->cursors[menu->cursorId] = cursor;
}

void Menu_DrawOptions(Menu* menu, int x, int y, int w) {
	Drawer_SetDrawColor(255, 255, 255);
	Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
	
	if (menu->page + 1 < menu->pageCount)
		Drawer_DrawSprite(SPR_gui_valuearrow, x + w - 4, y + 4 + (menu->pageRows - 1) * 28 + 16, 0, 2, 2);
	if (menu->page - 1 >= 0)
		Drawer_DrawSprite(SPR_gui_valuearrow, x + w - 32, y + 4 + (menu->pageRows - 1) * 28 + 16, 0, -2, 2);
	
	int c = 0;
	for (int i = menu->pageColumns * menu->pageRows * menu->page; i < menu->pageColumns * menu->pageRows * (menu->page + 1) && i < menu->optionCount; i++) {
		MenuOption* option = &menu->options[i];
		
		if (!option->enabled)
			Drawer_SetDrawColor(127, 127, 127);
		else
			Drawer_SetDrawColor(255, 255, 255);
		
		if (option->type == MENUOPTION_TYPE_BOOLEAN) {
			Drawer_DrawSprite(SPR_gui_checkmark, x + 54 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28 + 16, option->value, 2, 2);
			
			Drawer_DrawText(option->name, 32, x + 60 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28, 2, 2);
			Drawer_SetDrawColor(255, 255, 255);
			
			if (i == menu->cursors[menu->cursorId]) {
				Drawer_DrawSprite(SPR_gui_markergem, x + 28 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28 + 16, 0, 2, 2);
			}
		}
		else if (option->type == MENUOPTION_TYPE_NUMBER) {
			Drawer_DrawSprite(SPR_gui_valuearrow, x + 108 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28 + 16, i == menu->cursors[menu->cursorId], 2, 2);
			Drawer_DrawSprite(SPR_gui_valuearrow, x + 28 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28 + 16, i == menu->cursors[menu->cursorId], -2, 2);
			
			Drawer_SetDrawColor(255, 255, 255);
			Drawer_SetFontAlignment(FONT_ALIGN_RIGHT | FONT_ALIGN_TOP);
			snprintf(game.textBuffer, 32, "%d", option->value);
			Drawer_DrawText(game.textBuffer, 20, x + 92 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28, 2, 2);
			Drawer_SetFontAlignment(FONT_ALIGN_LEFT | FONT_ALIGN_TOP);
			
			Drawer_DrawText(option->name, 32, x + 124 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28, 2, 2);
			Drawer_SetDrawColor(255, 255, 255);
		}
		else {
			Drawer_DrawText(option->name, 32, x + 28 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28, 2, 2);
			Drawer_SetDrawColor(255, 255, 255);
			
			if (i == menu->cursors[menu->cursorId]) {
				Drawer_DrawSprite(SPR_gui_markergem, x + 28 + (c % menu->pageColumns) * w / 2, y + 4 + (c / menu->pageColumns) * 28 + 16, 0, 2, 2);
			}
		}
		
		c++;
	}
}
