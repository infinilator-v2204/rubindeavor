#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#define PI 3.14159
#define GLOBAL_TEXT_BUFFER_SIZE 2048
#define OBJECT_COUNT_MAX 256

extern SDL_Renderer* globalRenderer;
extern SDL_Window* mainGameWindow;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int globalForceGameQuit;

extern int mainGameWindowWidth;
extern int mainGameWindowHeight;
extern double mainGameRendererSize;
extern double mainGameRendererX;
extern double mainGameRendererY;

typedef struct {
	int debug;
	int saveFileNumber;
	int frameskip;
	int frameskipCounter;
	char textBuffer[GLOBAL_TEXT_BUFFER_SIZE];
	
	const Uint8* sdlKeyStates;
	Uint8 keyStates[256];
	Uint8 keyStatesPrev[256];
	Uint8 keyPressed[256];
	Uint8 keyReleased[256];
	int mouseX;
	int mouseY;
	int mouseXPrev;
	int mouseYPrev;
	int mouseHeld[3];
	int mouseHeldPrev[3];
	int mousePressed[3];
	int mouseReleased[3];
	int mouseScrollY;
	
	int scene;
	int timer;
	struct {
		bool enabled;
		char message[128];
	} popup;
	
	struct {
		int id;
		int timer;
		int spriteId;
		int transitionTimer;
		int transitionSpriteId;
	} cinema;
	
	struct {
		bool textSkip;
		bool autoRun;
		bool fullscreen;
		bool showStatSymbolLabels;
	} settings;
} Game;

extern Game game;

enum {
	SCENE_MENU,
	SCENE_CINEMA,
	SCENE_OVERWORLD,
	SCENE_BATTLE,
	SCENE_GAMEOVER,
	SCENE_MAPEDITOR,
	SCENE_CHESS,
};

enum {
	PLAYER_BUTTON_Z,
	PLAYER_BUTTON_X,
	PLAYER_BUTTON_C,
	PLAYER_BUTTON_A,
	PLAYER_BUTTON_S,
	PLAYER_BUTTON_D,
};

enum {
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

enum {
	FACING_LEFT = -1,
	FACING_RIGHT = 1
};

int StringLength(const char* string);
int StringsEqual(const char* s1, const char* s2);
int StringLineCount(const char* string);
int StringMaxLineWidth(const char* string);
void SetString(char* string, const char* value);
float GetWorldX(float x);
float GetWorldY(float y);
float GetScreenX(float x);
float GetScreenY(float y);
float PointDistance(float x1, float y1, float x2, float y2);
float PointDirection(float x1, float y1, float x2, float y2);
float Random(float x);
float Random_Range(float x1, float x2);
int Random_IRange(int x1, int x2);
int Max(int x1, int x2);
int Min(int x1, int x2);

int PlayerButtonPressed(int button);
int PlayerButtonHeld(int button);

int MouseRectangleHover(float x, float y, float w, float h);
int MouseCircleHover(float x, float y, float r);
int MouseRectangleHoverFirst(float x, float y, float w, float h);
int MousePressed(int button);
int MouseHeld(int button);
int MouseReleased(int button);

void EngageBattle(int id, int enemyObjectId);
void CreatePopup(const char* message);
void ShowCinemaCutscene(int id);

void DrawDialogBox(int x, int y, int w, int h);
void DrawSaveFile(int id, int x, int y, int variation, bool selected);
void DrawActionDetailBox(int actionId, int x, int y, int manaCostReduction, bool armorLocked, bool rangeLocked);

void Setup();

void Init();
void Update();
void Draw();
void ChangeScene(int scene);

void MainMenu_Init();
void MainMenu_Update();
void MainMenu_Draw();
void MainMenu_ChangeMenu(int id);

void Cinema_Init();
void Cinema_Update();
void Cinema_Draw();
void Cinema_SlideImage(int spriteId);

void GameOver_Init();
void GameOver_Update();
void GameOver_Draw();
