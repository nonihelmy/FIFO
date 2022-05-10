#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

#define COLOUR_BLACK 0xFF, 0xFF, 0xFF, 0xFF
#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (720)

void createRects();
int menu(GameRenderer *game)
{
	bool quit = false;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	(*game).window = SDL_CreateWindow("SDL2 Window",
									  SDL_WINDOWPOS_CENTERED,
									  SDL_WINDOWPOS_CENTERED,
									  WINDOW_WIDTH, WINDOW_HEIGHT,
									  0);

	(*game).renderer = SDL_CreateRenderer((*game).window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_SOFTWARE);
	(*game).font = TTF_OpenFont("../resource/font.ttf", 40);
	SDL_Texture *texture[3];
	SDL_Rect optionsRect[3];
	SDL_Color color = {255, 255, 255};
	SDL_Surface *options[3];
	options[0] = TTF_RenderText_Blended((*game).font, "PLAY", color);
	options[1] = TTF_RenderText_Blended((*game).font, "INSTRUCTIONS", color);
	options[2] = TTF_RenderText_Blended((*game).font, "QUIT", color);
	int nrOfRects = 3, mouseX, mouseY;

	for (int i = 0; i < nrOfRects; i++)
	{
		texture[i] = SDL_CreateTextureFromSurface((*game).renderer, options[i]);
	}

	SDL_Event event;

	while (!quit)
	{
		SDL_Surface *bg = SDL_LoadBMP("../resource/elena.bmp");
		SDL_Texture *bgTex = SDL_CreateTextureFromSurface((*game).renderer, bg);
		createRects(&optionsRect, options);
		SDL_RenderClear((*game).renderer);
		SDL_RenderCopy((*game).renderer, bgTex, NULL, NULL);

		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			for (int i = 0; i < nrOfRects; i++)
			{
				SDL_FreeSurface(options[i]);
				SDL_DestroyTexture(texture[i]);
			}

			quit = true;
			break;

		case SDL_MOUSEMOTION:
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			for (int i = 0; i < nrOfRects; i++)
			{
				if (mouseX >= optionsRect[i].x && mouseX <= optionsRect[i].x + optionsRect[i].w && mouseY >= optionsRect[i].y && mouseY <= optionsRect[i].y + optionsRect[i].h)
				{
					SDL_SetTextureColorMod(texture[i], 100, 255, 50);
				}
				else
				{
					SDL_SetTextureColorMod(texture[i], 255, 255, 255);
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (mouseX >= optionsRect[0].x && mouseX <= optionsRect[0].x + optionsRect[0].w && mouseY >= optionsRect[0].y && mouseY <= optionsRect[0].y + optionsRect[0].h)
			{
				for (int i = 0; i < nrOfRects; i++)
				{
					SDL_FreeSurface(options[i]);
					SDL_DestroyTexture(texture[i]);
				}
				SDL_DestroyRenderer((*game).renderer);
				TTF_Quit();
				play(game);
			}
			else if (mouseX >= optionsRect[1].x && mouseX <= optionsRect[1].x + optionsRect[1].w && mouseY >= optionsRect[1].y && mouseY <= optionsRect[1].y + optionsRect[1].h)
			{

				int backspace = 1;
				SDL_Surface *tutorial = NULL;
				tutorial = IMG_Load("../resource/rules.png");
				printf("Tutorial\n");
				SDL_Texture *tut = SDL_CreateTextureFromSurface((*game).renderer, tutorial);
				SDL_RenderClear((*game).renderer);
				SDL_RenderCopy((*game).renderer, tut, NULL, NULL);
				SDL_RenderPresent((*game).renderer);
				while (backspace)
				{
					while (SDL_PollEvent(&event))
					{
						switch (event.type)
						{
						case SDL_QUIT:
							for (int i = 0; i < nrOfRects; i++)
							{
								SDL_FreeSurface(options[i]);
								SDL_DestroyTexture(texture[i]);
							}

							return 0;

						case SDL_KEYDOWN:
							if (event.key.keysym.sym == SDLK_BACKSPACE)
							{
								printf("hej\n");
								SDL_FreeSurface(tutorial);
								SDL_DestroyTexture(tut);
								SDL_RenderClear((*game).renderer);
								SDL_RenderPresent((*game).renderer);
								backspace = 0;
							}
							break;

						default:
							break;
						}
					}
				}
			}
			else if (mouseX >= optionsRect[2].x && mouseX <= optionsRect[2].x + optionsRect[2].w && mouseY >= optionsRect[2].y && mouseY <= optionsRect[2].y + optionsRect[2].h)
			{
				printf("quit\n");
				for (int i = 0; i < nrOfRects; i++)
				{
					SDL_FreeSurface(options[i]);
					SDL_DestroyTexture(texture[i]);
				}
				SDL_FreeSurface(bg);
				SDL_DestroyTexture(bgTex);
				quit = true;
			}

			break;
		}

		for (int i = 0; i < nrOfRects; i++) // render mutliple textboxes
		{
			SDL_RenderCopy((*game).renderer, texture[i], NULL, &optionsRect[i]);
		}

		SDL_RenderPresent((*game).renderer);
	}

	TTF_CloseFont((*game).font);
	SDL_DestroyRenderer((*game).renderer);
	SDL_DestroyWindow((*game).window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

void createRects(SDL_Rect optionsRect[], SDL_Surface *options[])
{

	optionsRect[0].x = 640 - options[0]->w / 2;
	optionsRect[0].y = 260;
	optionsRect[0].w = options[0]->w;
	optionsRect[0].h = options[0]->h;

	optionsRect[1].x = 640 - options[1]->w / 2;
	optionsRect[1].y = 290 + options[0]->h;
	optionsRect[1].w = options[1]->w;
	optionsRect[1].h = options[1]->h;

	optionsRect[2].x = 640 - options[2]->w / 2;
	optionsRect[2].y = 320 + options[0]->h + options[1]->h;
	optionsRect[2].w = options[2]->w;
	optionsRect[2].h = options[2]->h;
}
