#pragma once

typedef struct {
	int enabled;
	char string[128];
	int stringLength;
	int stringCursor;
	
	char stringLog[16][128];
	int stringLogCount;
	int stringLogCursor;
	
	char log[4096];
	int logLength;
} DevConsole;

extern DevConsole devConsole;

void DevConsole_Init();
void DevConsole_Print(const char* text);
void DevConsole_ExecuteCommand();
void DevConsole_Draw();
