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
#include "game.h"
#include "timer.h"

#define COLOUR_BLACK 0xFF, 0xFF, 0xFF, 0xFF
#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (720)

int init();
void startRound(SDL_Renderer *renderer, SDL_Color White);
void LoadTimerBySeconds(Timer *t, TTF_Font *font, SDL_Renderer *renderer, SDL_Color White);
void setNextWord(FWords *fw, SDL_Rect background);
void quit();

int play(GameRenderer *game)
{
    init();
    (*game).renderer = SDL_CreateRenderer((*game).window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_SOFTWARE);
    if (!(*game).window)
    {
        printf("Failed to create window\n");
        return -1;
    }

    int buffSize = 45;
    char input[buffSize];
    Timer *timer;
    Names words[100];
    fileReader(words);
    LTexture *gInputTextTexture;
    FWords *fwt1;
    FWords *fwt2;
    FWords *fwt3;

    (*game).font = TTF_OpenFont("../resource/font.ttf", 24);
    (*game).inputFont = TTF_OpenFont("../resource/font.ttf", 36);
    SDL_Color White = {255, 255, 255};

    SDL_Rect background;
    background.x = 160;
    background.y = 0;
    background.w = 960;
    background.h = 540;

    SDL_Rect textInput;
    textInput.x = 160;
    textInput.y = 560;
    textInput.w = 960;
    textInput.h = 140;

    SDL_Rect text;
    text.x = textInput.x + ((textInput.w) / 2);
    text.y = textInput.y + ((textInput.h) / 2);

    // Load input from user
    snprintf(input, buffSize, "");
    gInputTextTexture = LTexture_create();
    LTexture_loadFromRenderedText(gInputTextTexture, (*game).renderer, input, (*game).inputFont, White);

    // Initiates the words and respective x,y coordinates.
    fwt1 = FWords_create(background.x + 10, background.y, 0);
    fwt2 = FWords_create(background.x + 156, background.y - 300, 1);
    fwt3 = FWords_create(background.x + 500, background.y - 70, 2);

    // Background for input from user
    SDL_Surface *bTextSurface = SDL_CreateRGBSurface(0, 960, 200, 32, 0, 0, 0, 0);
    SDL_FillRect(bTextSurface, NULL, SDL_MapRGB(bTextSurface->format, 140, 16, 16));
    SDL_Texture *TextInput = SDL_CreateTextureFromSurface((*game).renderer, bTextSurface);
    SDL_FreeSurface(bTextSurface);

    // Background for the main game
    SDL_Surface *bSurface = SDL_LoadBMP("../resource/elena.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface((*game).renderer, bSurface);
    SDL_FreeSurface(bSurface);

    int points = 0;
    bool keep_window_open = true;
    // bool correct = false;
    srand(time(NULL));
    SDL_Event e;
    SDL_StartTextInput();
    startRound((*game).renderer, White);

    timer = TimerInit(60);
    Timer_load(timer, (*game).renderer, "60", (*game).font, White);
    while (keep_window_open)
    {
        UpdateTimer(timer);
        FWords_loadFromRenderedWord(fwt1, (*game).renderer, words[fwt1->currentWordIndex].name, (*game).font, White);
        FWords_loadFromRenderedWord(fwt2, (*game).renderer, words[fwt2->currentWordIndex].name, (*game).font, White);
        FWords_loadFromRenderedWord(fwt3, (*game).renderer, words[fwt3->currentWordIndex].name, (*game).font, White);

        SDL_RenderCopy((*game).renderer, TextInput, NULL, &textInput);
        LTexture_render(gInputTextTexture, (*game).renderer, text.x, text.y, NULL, 0, NULL, 0);
        SDL_RenderCopy((*game).renderer, texture, NULL, &background);
        FWords_render(fwt1, (*game).renderer, fwt1->posX, fwt1->posY, NULL);
        FWords_render(fwt2, (*game).renderer, fwt2->posX, fwt2->posY, NULL);
        FWords_render(fwt3, (*game).renderer, fwt3->posX, fwt3->posY, NULL);

        Timer_render(timer, (*game).renderer, WINDOW_WIDTH, WINDOW_HEIGHT, NULL);

        SDL_RenderPresent((*game).renderer);
        WordTick(fwt1);
        WordTick(fwt2);
        WordTick(fwt3);
        SDL_Delay(15);

        if (fwt1->posY >= background.h - fwt1->wordHeight)
        {
            setNextWord(fwt1, background);
        }
        else if (fwt1->correctGuessed == true)
        {
            setNextWord(fwt1, background);
            snprintf(input, buffSize, "");
            LTexture_loadFromRenderedText(gInputTextTexture, (*game).renderer, input, (*game).inputFont, White);
        }

        if (fwt2->posY >= background.h - fwt2->wordHeight)
        {
            setNextWord(fwt2, background);
        }
        else if (fwt2->correctGuessed == true)
        {
            setNextWord(fwt2, background);
            snprintf(input, buffSize, "");
            LTexture_loadFromRenderedText(gInputTextTexture, (*game).renderer, input, (*game).inputFont, White);
        }

        if (fwt3->posY >= background.h - fwt3->wordHeight)
        {
            setNextWord(fwt3, background);
        }
        else if (fwt3->correctGuessed == true)
        {
            setNextWord(fwt3, background);
            snprintf(input, buffSize, "");
            LTexture_loadFromRenderedText(gInputTextTexture, (*game).renderer, input, (*game).inputFont, White);
        }

        if (timer->elapsedTicks % 1000 == 0)
        {
            Timer_load(timer, (*game).renderer, " ", (*game).font, White);
        }
        else
        {
            LoadTimerBySeconds(timer, (*game).font, (*game).renderer, White);
        }
        SDL_Event e;
        SDL_StartTextInput();
        bool renderText = false;
        if (e.type == SDL_QUIT)
        {
            keep_window_open = false;
            break;
        }
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                keep_window_open = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                // Handle backspace
                if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 0)
                {
                    // lop off character
                    int length = strlen(input);
                    strcpy(&input[length - 1], "\0");
                    renderText = true;
                }
            }
            else if (e.type == SDL_TEXTINPUT)
            {
                if (strlen(input) < buffSize)
                {
                    strcat(input, e.text.text);
                    renderText = true;
                }
                else
                {
                    printf("string buff full\n");
                }
                if (strcmp(input, words[fwt1->currentWordIndex].name) == 0)
                {
                    fwt1->correctGuessed = true;
                }
                if (strcmp(input, words[fwt2->currentWordIndex].name) == 0)
                {
                    fwt2->correctGuessed = true;
                }
                if (strcmp(input, words[fwt3->currentWordIndex].name) == 0)
                {
                    fwt3->correctGuessed = true;
                }
            }
        }

        if (renderText)
        {
            // Text is not empty
            if (strncmp(input, "", buffSize))
            {
                // Render new text
                LTexture_loadFromRenderedText(gInputTextTexture, (*game).renderer, input, (*game).inputFont, White);
            }
            // Text is empty
            else
            {
                // Render space texture
                LTexture_loadFromRenderedText(gInputTextTexture, (*game).renderer, " ", (*game).inputFont, White);
            }
        }
    }
    TTF_CloseFont((*game).font);
    LTexture_destroy(gInputTextTexture);
    FWords_destroy(fwt1);
    FWords_destroy(fwt2);
    FWords_destroy(fwt3);
    DestroyTimer(timer);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(TextInput);
    SDL_DestroyRenderer((*game).renderer);
    SDL_DestroyWindow((*game).window);
    TTF_Quit();
    SDL_Quit();
}

void startRound(SDL_Renderer *renderer, SDL_Color White)
{
    TTF_Font *timerFont = TTF_OpenFont("../resource/font.ttf", 128);
    SDL_Rect timerRect;

    char tUnit[1];
    SDL_Texture *tTexture;
    for (int i = 5; i >= 0; i--)
    {
        // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(renderer);
        // sprintf(tUnit, "%d", i);
        SDL_Surface *tSurface = TTF_RenderText_Solid(timerFont, tUnit, White);
        tTexture = SDL_CreateTextureFromSurface(renderer, tSurface);
        // timerRect.w = tSurface->w;
        // timerRect.h = tSurface->h;
        timerRect.x = (WINDOW_WIDTH - timerRect.w) / 2;
        timerRect.y = (WINDOW_HEIGHT - timerRect.h) / 2;
        SDL_FreeSurface(tSurface);
        SDL_RenderCopy(renderer, tTexture, NULL, &timerRect);
        SDL_Delay(1000 / 60);
        SDL_RenderPresent(renderer);
    }
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(tTexture);
}
void LoadTimerBySeconds(Timer *t, TTF_Font *font, SDL_Renderer *renderer, SDL_Color White)
{
    int tRemainingBySeconds = (t->timerDuration - t->elapsedTicks) / 1000;
    char timer[10];
    sprintf(timer, "%d", tRemainingBySeconds);
    Timer_load(t, renderer, timer, font, White);
}

void setNextWord(FWords *fw, SDL_Rect background)
{
    fw->posY = background.y - fw->wordHeight;
    fw->currentWordIndex += 3;
    fw->posX = (rand() % ((background.w - fw->wordWidth - 5) - (background.x + 10 + 5) + 1)) + (background.x + 10 + 5);
    fw->maxSwingRight = fw->posX + 5;
    fw->maxSwingLeft = fw->posX - 5;
    fw->correctGuessed = false;
}

int init()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize the SDL2 library\n");
        return -1;
    }

    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        return -1;
    }
    /*
    if (SDL_INIT_TIMER < 0)
    {
        printf("SDL_INIT_TIMER: %s\n", SDL_GetError());
        return -1;
    }
    */
}
