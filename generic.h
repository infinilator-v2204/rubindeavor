#pragma once

// Game compilation settings

#define RXS_LOAD_SPRITES_FROM_FOLDER
#define RXS_INCLUDE_MAP_EDITOR
#define RXS_INCLUDE_EXCEPTION_HANDLER



#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#define PI 3.14159
#define GLOBAL_TEXT_BUFFER_SIZE 2048
#define OBJECT_COUNT_MAX 256

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

typedef struct {
	bool forceGameQuit;
	
	int debug;
	int saveFileNumber;
	int frameskip;
	int frameskipCounter;
	char textBuffer[GLOBAL_TEXT_BUFFER_SIZE];
	
	int windowWidth;
	int windowHeight;
	double rendererSize;
	double rendererX;
	double rendererY;
	
	bool keyStates[256];
	bool keyStatesPrev[256];
	bool keyPressed[256];
	bool keyReleased[256];
	bool playerKeyStates[32];
	bool playerKeyStatesPrev[32];
	bool playerKeyPressed[32];
	bool playerKeyReleased[32];
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
		int id;
		int timer;
		int stage;
		int gems[6];
		int actionCount;
		int armorCount;
		int passiveCount;
		int totalActionCount;
		int totalArmorCount;
		int totalPassiveCount;
	} ending;
	
	struct {
		bool textSkip;
		bool autoRun;
		bool fullscreen;
		bool showStatSymbolLabels;
		
		bool softwareRendering;
	} settings;
	
	struct {
		const Uint8* keyStates;
		SDL_Window* window;
		SDL_Renderer* renderer;
	} internal;
} Game;

extern Game game;

enum {
	SCENE_MENU,
	SCENE_CINEMA,
	SCENE_OVERWORLD,
	SCENE_BATTLE,
	SCENE_GAMEOVER,
	SCENE_ENDING,
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
	PLAYER_BUTTON_LEFT,
	PLAYER_BUTTON_RIGHT,
	PLAYER_BUTTON_UP,
	PLAYER_BUTTON_DOWN,
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

void UpdateFullscreenMode();

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
void ShowEnding(int id);

void DrawDialogBox(int x, int y, int w, int h);
void DrawSaveFile(int id, int x, int y, int variation, bool selected);
void DrawActionDetailBox(int actionId, int x, int y, int manaCostReduction, bool armorLocked, bool rangeLocked);

void Setup();

void Init();
void UpdateInput();
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

void Ending_Init();
void Ending_Update();
void Ending_Draw();
