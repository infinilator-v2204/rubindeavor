#pragma once

typedef struct {
	bool enabled;
	int value;
	int type;
	int valueMin;
	int valueMax;
	char name[32];
} MenuOption;

typedef struct {
	int id;
	int cursorId;
	int cursors[8];
	int optionCount;
	MenuOption options[256];
	int page;
	int pageCount;
	int pageColumns;
	int pageRows;
	bool canNavigate;
	
	int optionPressed;
	int optionPressedValue;
	int holdTimer;
} Menu;

enum {
	MENUOPTION_NONE = -1,
	MENUOPTION_BACK = -2,
};

enum {
	MENUOPTION_TYPE_BUTTON,
	MENUOPTION_TYPE_NUMBER,
	MENUOPTION_TYPE_BOOLEAN,
};

void Menu_New(Menu* menu, int id, int pageColumns, int pageRows, int cursorId);
void Menu_ResetCursor(Menu* menu);
void Menu_SetCursor(Menu* menu, int optionId);
void Menu_ClearOptions(Menu* menu);
void Menu_AddOption(Menu* menu, bool enabled, int value, const char* name);
void Menu_AddOption_Number(Menu* menu, bool enabled, int value, const char* name, int valueMin, int valueMax);
void Menu_AddOption_Boolean(Menu* menu, bool enabled, int value, const char* name);

void Menu_Update(Menu* menu);
void Menu_DrawOptions(Menu* menu, int x, int y, int w);
