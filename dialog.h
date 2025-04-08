#pragma once

#include "menu.h"

#define DIALOG_TEXT_SIZE 256
#define DIALOG_BUFFER_SIZE 512

typedef struct {
	int state;
	int ptr;
	int timer;
	int time;
	int voiceSoundId;
	int voiceCooldown;
	int voiceTickDelay;
	int voiceDelayTimer;
	
	int textLength;
	unsigned char text[DIALOG_TEXT_SIZE];
	
	char name[32];
	
	int bufferPtr;
	int bufferLength;
	unsigned char buffer[DIALOG_BUFFER_SIZE];
	
	Menu menu;
	int optionSelected;
} DialogSystem;

enum {
	DIALOG_STATE_IDLE,
	DIALOG_STATE_RUN,
	DIALOG_STATE_WAIT,
	DIALOG_STATE_INPUTWAIT,
};

extern DialogSystem dialogSystem;

extern unsigned char dialogData[0x40000];
extern int dialogPointerData[6000];

void LoadDialogData();
void SetDialogString(int id, const char* value);
char* GetDialogString(int id);

void Dialog_Run(int id);
void Dialog_RunVoiced(int id, int voiceId);
void Dialog_Jump(int id);
void Dialog_Continue();
void Dialog_AppendString(const char* string);
bool Dialog_IsFinished();
bool Dialog_IsWaiting();
unsigned char Dialog_GetChar();
void Dialog_Update();
