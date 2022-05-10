#ifndef FLOATINGWORDS_H
#define FLOATINGWORDS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define n 10

struct fwords
{
    SDL_Texture* wordTexture;
    int posX; 
    int posY;
    int wordWidth;
    int wordHeight;
    int maxSwingRight;
    int maxSwingLeft;
    int currentWordIndex;
    bool swingRight; 
    bool correctGuessed;
}; typedef struct fwords FWords; 

FWords* FWords_create(int x, int y, int index); 
void FWords_reset(FWords* fw);
void FWords_destroy(FWords* fw); 
bool FWords_loadFromRenderedWord(FWords *fw, SDL_Renderer* renderer, char textureText[], TTF_Font* font, SDL_Color textColor ); 
void FWords_render(FWords* fw, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip); 
void WordTick(FWords* fw); 
int getPosY(FWords fw); 
int getPosX(FWords fw);

#endif