#ifndef TIMER_H
#define TIMER_H  
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

typedef struct Timer
{
    SDL_Texture* timerTexture;
    unsigned int startTicks; 
    unsigned int elapsedTicks;
    int timerDuration;
    int timerWidth;
    int timerHeight;
} Timer;

Timer* TimerInit(int duration); 
void DestroyTimer(Timer* t);
void ResetTimer(Timer* t); 
void ResetTimerTexture(Timer* t);
void UpdateTimer(Timer* t);
bool Timer_load(Timer *t, SDL_Renderer* renderer, char time[], TTF_Font* font, SDL_Color textColor); 
void Timer_render(Timer* t, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip); 

#endif