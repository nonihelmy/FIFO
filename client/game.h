#pragma once

#ifndef game_h
#define game_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include "filehandler.h"
#include "floatingWords.h"
#include "LTexture.h"



typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    TTF_Font *inputFont;
} GameRenderer;

int init();
void startRound(SDL_Renderer *renderer, SDL_Color White);
void setNextWord(FWords *fw, SDL_Rect background);  
int play(GameRenderer *game);

#endif 