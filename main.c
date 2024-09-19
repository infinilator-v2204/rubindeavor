#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "generic.h"
#include "sprites.h"
#include "audio.h"
#include "console.h"
#include "exception.h"

const char* globalGameName = "Rubindeavor";

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int mainGameWindowWidth = 640;
int mainGameWindowHeight = 480;
double mainGameRendererSize = 1;
double mainGameRendererX = 0;
double mainGameRendererY = 0;

SDL_Window* mainGameWindow = NULL;
SDL_Renderer* globalRenderer = NULL;

int globalForceGameQuit = 0;

#if defined(_WIN32)
int WinMain(int argc, char* argv[]) {
#else
int main(int argc, char* argv[]) {
#endif
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		return 1;
	}
	
	mainGameWindow = SDL_CreateWindow("Rubindeavor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mainGameWindow == NULL) {
		printf("Window could not be created! Error: %s\n", SDL_GetError());
		return 1;
	}
	
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! Error: %s\n", IMG_GetError());
		return 1;
	}
	
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! Error: %s\n", Mix_GetError());
		return 1;
	}
	Mix_AllocateChannels(64);
	
	globalRenderer = SDL_CreateRenderer(mainGameWindow, -1, SDL_RENDERER_ACCELERATED);
	if (globalRenderer == NULL) {
		printf("Renderer could not be created! Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_SetRenderDrawColor(globalRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_SetRenderDrawBlendMode(globalRenderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetLogicalSize(globalRenderer, 640, 480);
	
	
	
	
	srand(time(NULL));
	
	Uint32 gTicksUntilUpdate, gTicks1, gTicks2;
	
	gTicksUntilUpdate = 0;
	gTicks1 = SDL_GetTicks();
	
	SetDrawBlend(SDL_BLENDMODE_BLEND);
	Init();
	
	RubindeavorExceptionHandler_Enable();
	
	SDL_Event e;
	int quit = 0;
	game.settings.fullscreen = false;
	while (!quit && !globalForceGameQuit) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_WINDOWEVENT:
					switch (e.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							{
								mainGameWindowWidth = e.window.data1;
								mainGameWindowHeight = e.window.data2;
								double ratio = (double)mainGameWindowHeight / (double)mainGameWindowWidth;
								if (ratio <= 0) break;
								if (ratio < 0.75) {
									mainGameRendererSize = (double)mainGameWindowHeight / 480;
									mainGameRendererX = (mainGameWindowWidth - mainGameWindowHeight / 0.75) / 2;
									mainGameRendererY = 0;
								}
								else if (ratio > 0.75) {
									mainGameRendererSize = (double)mainGameWindowWidth / 640;
									mainGameRendererX = 0;
									mainGameRendererY = (mainGameWindowHeight - mainGameWindowWidth * 0.75) / 2;
								}
								else {
									mainGameRendererSize = (double)mainGameWindowWidth / 640;
									mainGameRendererX = 0;
									mainGameRendererY = 0;
								}
							}
							break;
					}
					break;
				
				case SDL_QUIT:
					quit = 1;
					break;
				
				case SDL_MOUSEWHEEL:
					if (e.wheel.y > 0)
						game.mouseScrollY = 2;
					else if (e.wheel.y < 0)
						game.mouseScrollY = -2;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (e.button.button == SDL_BUTTON_LEFT)
						game.mouseHeld[MOUSE_LEFT] = 1;
					else if (e.button.button == SDL_BUTTON_MIDDLE)
						game.mouseHeld[MOUSE_MIDDLE] = 1;
					else if (e.button.button == SDL_BUTTON_RIGHT)
						game.mouseHeld[MOUSE_RIGHT] = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					if (e.button.button == SDL_BUTTON_LEFT)
						game.mouseHeld[MOUSE_LEFT] = 0;
					else if (e.button.button == SDL_BUTTON_MIDDLE)
						game.mouseHeld[MOUSE_MIDDLE] = 0;
					else if (e.button.button == SDL_BUTTON_RIGHT)
						game.mouseHeld[MOUSE_RIGHT] = 0;
					break;
				
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_F4) {
						game.settings.fullscreen = !game.settings.fullscreen;
						
						if (game.settings.fullscreen)
							SDL_SetWindowFullscreen(mainGameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
						else
							SDL_SetWindowFullscreen(mainGameWindow, 0);
					}
					
					if (e.key.keysym.sym == SDLK_BACKQUOTE) {
						devConsole.enabled = !devConsole.enabled;
						
						if (devConsole.enabled) {
							SDL_StartTextInput();
						}
						else {
							SDL_StopTextInput();
						}
					}
					else if (devConsole.enabled) {
						if (e.key.keysym.sym == SDLK_BACKSPACE && devConsole.stringLength > 0 && devConsole.stringCursor > 0) {
							devConsole.stringLength--;
							devConsole.stringCursor--;
							for (int i = devConsole.stringCursor; i <= devConsole.stringLength; i++) {
								devConsole.string[i] = devConsole.string[i + 1];
							}
						}
						else if (e.key.keysym.sym == SDLK_LEFT && devConsole.stringCursor > 0) {
							devConsole.stringCursor--;
						}
						else if (e.key.keysym.sym == SDLK_RIGHT && devConsole.stringCursor < devConsole.stringLength) {
							devConsole.stringCursor++;
						}
						else if (e.key.keysym.sym == SDLK_UP && devConsole.stringLogCursor < devConsole.stringLogCount - 1) {
							devConsole.stringLogCursor++;
							
							SetString(devConsole.string, devConsole.stringLog[devConsole.stringLogCursor]);
							devConsole.stringLength = StringLength(devConsole.string);
							devConsole.stringCursor = devConsole.stringLength;
						}
						else if (e.key.keysym.sym == SDLK_DOWN && devConsole.stringLogCursor > -1) {
							devConsole.stringLogCursor--;
							
							if (devConsole.stringLogCursor < 0) {
								SetString(devConsole.string, "");
								devConsole.stringLength = 0;
								devConsole.stringCursor = 0;
							}
							else {
								SetString(devConsole.string, devConsole.stringLog[devConsole.stringLogCursor]);
								devConsole.stringLength = StringLength(devConsole.string);
								devConsole.stringCursor = devConsole.stringLength;
							}
						}
						else if (e.key.keysym.sym == SDLK_RETURN && devConsole.stringLength > 0) {
							DevConsole_ExecuteCommand();
							
							if (devConsole.stringLogCount < 16) devConsole.stringLogCount++;
							devConsole.stringLogCursor = -1;
							for (int i = 15; i > 0; i--) {
								SetString(devConsole.stringLog[i], devConsole.stringLog[i - 1]);
							}
							SetString(devConsole.stringLog[0], devConsole.string);
							
							devConsole.stringLength = 0;
							devConsole.stringCursor = 0;
							devConsole.string[devConsole.stringLength] = 0;
						}
					}
					break;
				case SDL_TEXTINPUT:
					if (e.text.text[0] == '`') break;
					
					if (devConsole.enabled && devConsole.stringLength < 78) {
						for (int i = devConsole.stringLength + 1; i > devConsole.stringCursor; i--) {
							devConsole.string[i] = devConsole.string[i - 1];
						}
						
						devConsole.string[devConsole.stringCursor++] = e.text.text[0];
						devConsole.stringLength++;
					}
					break;
			}
		}
		
		gTicks2 = SDL_GetTicks();
		gTicksUntilUpdate += gTicks2 - gTicks1;
		gTicks1 = SDL_GetTicks();
		if (gTicksUntilUpdate >= 1000 / 60) {
			gTicksUntilUpdate = 0;
			
			Update();
			
			if (game.frameskipCounter < game.frameskip)
				game.frameskipCounter++;
			else {
				SDL_SetRenderDrawColor(globalRenderer, 0x00, 0x00, 0x00, 0xff);
				SDL_RenderClear(globalRenderer);
				Draw();
				SDL_RenderPresent(globalRenderer);
				game.frameskipCounter = 0;
			}
		}
		SDL_Delay(3);
	}
	
	FreeSprites();
	FreeAudio();
	
	SDL_DestroyRenderer(globalRenderer);
	SDL_DestroyWindow(mainGameWindow);
	
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}