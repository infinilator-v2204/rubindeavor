# Introduction

A hastily made repository for the source code of Rubindeavor, a turn-based RPG with a dark twist or something. Currently supports Windows (x64).

The codebase was made with only myself as a developer in mind, so it might take a while for an average programmer to get used to it.

# Getting started

You need a Windows operating system first of all. It's possible to compile the game on Linux, but you may need to modify the makefile.

To verify that you can compile the game, follow the step-to-step guide below (unless you know what you're doing).

1. Download and install MSYS2 from the [official website](https://www.msys2.org/), follow the installation guide in the website.

2. Open "MSYS2 UCRT64" application which you just installed. You've already opened it when following through the guide in MSYS2's website, but you now know the right application to open. A command prompt-like window ("terminal") should appear.

3. Install the required libraries and binaries using the following command:

```
pacman -S make mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-SDL2_image mingw-w64-ucrt-x86_64-SDL2_mixer
```

4. Go to the repository's directory in the terminal (use `cd` command to navigate).

5. Run `make` to build the application. This creates "rubindeavor.exe" that is the game itself.

6. Launch "rubindeavor.exe". Now you should be able to play the game!

# Making changes

## Programming

All files ending in .c and .h are the game's source code written in C. You must have basic knowledge of the C programming language, there are plenty of tutorials for that.

Header (.h) files are mostly for declaring functions and such. Source (.c) files are the bulk of program logic.

Files zip.c, zip.h, miniz.h are not written by me.

## Graphics and audio

Add .png and .ogg files in gfx and sfx folders respectively, then modify audio.c, audio.h, sprites.c, sprites.h to include new filenames.

## In-game console

You can open the console in the game itself. Just press the \` or ~ key at any point in the game. All commands are written in "console.c".

## Map editing

Open in-game console, type `mapeditor` and press ENTER. This should bring you to the map editor.

The interface and controls are not exactly user-friendly, because once again, this was made with only myself as a developer in mind.

### Controls

WASD or arrows to move.

Use mouse wheel to change the zoom.

Press T to open the tileset (you can move around with WASD or arrows).

Hold and release C to copy-paste highlighted tiles.

Press SPACE to switch between tile or decoration placing mode. Decorations are multiple tiles combined to create solid objects.

Press = or - to increase/decrease the tile height of decorations. Hold SHIFT to affect width instead.

Hold CTRL and press S to save changes. Check the modification date of "level/_temp.bin" to ensure you've saved the map.

## GFXCRYPT (optional)

GFXCRYPT "encrypts" the assets.dat file (it's just a zip file containing gfx folder). Go to gfxcrypt folder and simply run `make`. Put assets.dat in the folder, run "gfxcrypt.exe" and the assets.dat can now be read by the game (if you modify `RXS_LOAD_SPRITES_FROM_FOLDER` from generic.h).

## Standalone release

Standalone release only includes the following: gfx, sfx, level and save folders, SDL2.dll, SDL2\_image.dll, SDL2\_mixer.dll, rubindeavor.exe. Folder gfx is replaced with assets.dat if gfxcrypt is used.
