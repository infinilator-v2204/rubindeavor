#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "generic.h"
#include "overworld.h"
#include "profile.h"
#include "sprites.h"
#include "audio.h"
#include "console.h"
#include "exception.h"

const char* globalGameName = "Rubindeavor";

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
	struct {
		bool useSoftwareRenderer;
		int frameskip;
		int loadSaveFileNumber;
	} cmdParams = {false, 0, -1};
	
	for (int i = 1; i < argc; i++) {
		if (StringsEqual(argv[i], "--software") || StringsEqual(argv[i], "-s")) {
			cmdParams.useSoftwareRenderer = true;
			continue;
		}
		if (StringsEqual(argv[i], "--frameskip") || StringsEqual(argv[i], "-f")) {
			if (i + 1 < argc) {
				char* temp = argv[++i];
				if (!((temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '-' && temp[1] >= '0' && temp[1] <= '9'))) {
					printf("Frameskip not specified\n");
					return 1;
				}
				int tempValue = strtol(temp, NULL, 10);
				if (tempValue < 0 || tempValue > 999) {
					printf("Frameskip must be between 0 and 999\n");
					return 1;
				}
				cmdParams.frameskip = tempValue;
				continue;
			}
			printf("Frameskip not specified\n");
			return 1;
		}
		if (StringsEqual(argv[i], "--load") || StringsEqual(argv[i], "-l")) {
			if (i + 1 < argc) {
				char* temp = argv[++i];
				if (!((temp[0] >= '0' && temp[0] <= '9') || (temp[0] == '-' && temp[1] >= '0' && temp[1] <= '9'))) {
					printf("Save file not specified\n");
					return 1;
				}
				int tempValue = strtol(temp, NULL, 10);
				cmdParams.loadSaveFileNumber = tempValue;
				continue;
			}
			printf("Save file not specified\n");
			return 1;
		}
		if (StringsEqual(argv[i], "--help") || StringsEqual(argv[i], "-h")) {
			printf(
				"Usage: rubindeavor [options]\n"
				"\n"
				"  -h, --help                Print this message and exit.\n"
				"  -s, --software            Use software renderer (no hardware acceleration).\n"
				"                            This lets you play the game without requiring a\n"
				"                            modern graphics adapter at a performance cost.\n"
				"                            You may want to use this with --frameskip option.\n"
				"  -f, --frameskip VALUE     Skip VALUE frames each render. Default is 0. This\n"
				"                            can significantly improve performance at the cost\n"
				"                            of the game rendering less smoothly.\n"
				"  -l, --load SAVEFILE       Immediately loads the specified save file with ID\n"
				"                            number SAVEFILE. Save file ID starts at 0 (first\n"
				"                            is 0, second is 1 etc). Default is -1, which does\n"
				"                            nothing.\n"
			);
			return 0;
		}
		printf("Invalid parameter or usage\nUse option '-h' to print help information\n");
		return 1;
	}
	
	game.settings.softwareRendering = cmdParams.useSoftwareRenderer;
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		snprintf(game.textBuffer, 256, "SDL could not be initialized! Error: %s\n", SDL_GetError());
		puts(game.textBuffer);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", game.textBuffer, NULL);
		return 1;
	}
	
	game.internal.window = SDL_CreateWindow("Rubindeavor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (game.internal.window == NULL) {
		snprintf(game.textBuffer, 256, "Window could not be created! Error: %s\n", SDL_GetError());
		puts(game.textBuffer);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", game.textBuffer, NULL);
		return 1;
	}
	
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		snprintf(game.textBuffer, 256, "SDL_image could not be initialized! Error: %s\n", IMG_GetError());
		puts(game.textBuffer);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", game.textBuffer, NULL);
		return 1;
	}
	
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
		snprintf(game.textBuffer, 256, "SDL_mixer could not be initialized! Error: %s\n", Mix_GetError());
		puts(game.textBuffer);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", game.textBuffer, NULL);
		return 1;
	}
	Mix_AllocateChannels(64);
	
	game.internal.renderer = SDL_CreateRenderer(game.internal.window, -1, cmdParams.useSoftwareRenderer ? SDL_RENDERER_SOFTWARE : SDL_RENDERER_ACCELERATED);
	if (game.internal.renderer == NULL) {
		game.internal.renderer = SDL_CreateRenderer(game.internal.window, -1, SDL_RENDERER_SOFTWARE);
		if (game.internal.renderer == NULL) {
			snprintf(game.textBuffer, 256, "Renderer could not be created! Error: %s\n", SDL_GetError());
			puts(game.textBuffer);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", game.textBuffer, NULL);
			return 1;
		}
		snprintf(game.textBuffer, 256, "Hardware acceleration not supported, using software fallback\n");
		puts(game.textBuffer);
		game.settings.softwareRendering = true;
	}
	else if (!cmdParams.useSoftwareRenderer) {
		SDL_SetWindowResizable(game.internal.window, SDL_TRUE);
	}
	SDL_SetRenderDrawColor(game.internal.renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_SetRenderDrawBlendMode(game.internal.renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetLogicalSize(game.internal.renderer, 640, 480);
	
	
	
	
	srand(time(NULL));
	
	Uint32 gTicksUntilUpdate, gTicks1, gTicks2, fps_ticksUntilUpdate, fps_ticks1, fps_ticks2, fps;
	
	gTicksUntilUpdate = 0;
	gTicks1 = SDL_GetTicks();
	
	fps_ticksUntilUpdate = 0;
	fps_ticks1 = gTicks1;
	fps = 0;
	
	Init();
	
	RubindeavorExceptionHandler_Enable();
	
	if (cmdParams.loadSaveFileNumber >= 0) {
		int ret = Profile_LoadGameSlot(cmdParams.loadSaveFileNumber);
		if (ret == 1) {
			Audio_StopMusic();
			game.saveFileNumber = cmdParams.loadSaveFileNumber;
			overworld.fadeAlpha = 1;
			overworld.transition.id = 1;
			overworld.transition.timer = 24;
			overworld.state = OVERWORLD_STATE_IDLE;
			ChangeScene(SCENE_OVERWORLD);
			Overworld_ChangeArea(overworld.areaId);
		}
		else {
			Audio_PlaySound(SND_no);
			if (ret == -2) {
				CreatePopup("File is not a Rubindeavor save.");
			}
			else if (ret == -3)
				CreatePopup("This file is from an older version\nof Rubindeavor and cannot be loaded.");
			else
				CreatePopup("Failed to load the file.");
		}
	}
	
	SDL_Event e;
	while (!game.forceGameQuit) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_WINDOWEVENT:
					switch (e.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							{
								game.windowWidth = e.window.data1;
								game.windowHeight = e.window.data2;
								double ratio = (double)game.windowHeight / (double)game.windowWidth;
								if (ratio <= 0) break;
								if (ratio < 0.75) {
									game.rendererSize = (double)game.windowHeight / 480;
									game.rendererX = (game.windowWidth - game.windowHeight / 0.75) / 2;
									game.rendererY = 0;
								}
								else if (ratio > 0.75) {
									game.rendererSize = (double)game.windowWidth / 640;
									game.rendererX = 0;
									game.rendererY = (game.windowHeight - game.windowWidth * 0.75) / 2;
								}
								else {
									game.rendererSize = (double)game.windowWidth / 640;
									game.rendererX = 0;
									game.rendererY = 0;
								}
							}
							break;
					}
					break;
				
				case SDL_QUIT:
					game.forceGameQuit = true;
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
						UpdateFullscreenMode();
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
			fps++;
			fps_ticks2 = SDL_GetTicks();
			fps_ticksUntilUpdate += fps_ticks2 - fps_ticks1;
			fps_ticks1 = SDL_GetTicks();
			if (fps_ticksUntilUpdate >= 1000) {
				fps_ticksUntilUpdate -= 1000;
				if (game.debug) {
					snprintf(game.textBuffer, 64, "Rubindeavor | FPS: %d", fps);
					SDL_SetWindowTitle(game.internal.window, game.textBuffer);
				}
				fps = 0;
			}
			
			if (game.frameskipCounter < game.frameskip + cmdParams.frameskip)
				game.frameskipCounter++;
			else {
				SDL_SetRenderDrawColor(game.internal.renderer, 0x00, 0x00, 0x00, 0xff);
				SDL_RenderClear(game.internal.renderer);
				Draw();
				SDL_RenderPresent(game.internal.renderer);
				game.frameskipCounter = 0;
			}
		}
		SDL_Delay(2);
	}
	
	RubindeavorExceptionHandler_Disable();
	
	FreeSprites();
	FreeAudio();
	
	SDL_DestroyRenderer(game.internal.renderer);
	SDL_DestroyWindow(game.internal.window);
	
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}