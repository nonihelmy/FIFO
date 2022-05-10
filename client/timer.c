#include "timer.h" 


Timer* TimerInit(int duration){
    Timer* t = malloc(sizeof(Timer));
    t->timerTexture = NULL;
    t->startTicks = SDL_GetTicks();
    t->elapsedTicks = 0;
    t->timerDuration = duration * 1000;
    t->timerWidth = 0;
    t->timerHeight = 0;
    return t;
} 

void DestroyTimer(Timer* t){
    //ResetTimer(t); 
    ResetTimerTexture(t);
    free(t);
}

void ResetTimer(Timer* t){
    t->startTicks = SDL_GetTicks();
    t->elapsedTicks = 0;
} 

void ResetTimerTexture(Timer* t){
    if (t->timerTexture != NULL)
    {
        SDL_DestroyTexture( t->timerTexture);
        t->timerTexture = NULL;
        t->timerWidth = 0; 
        t->timerHeight = 0;
    }
    
}

void UpdateTimer(Timer* t){
    t->elapsedTicks = SDL_GetTicks() - t->startTicks;
}

bool Timer_load(Timer *t, SDL_Renderer* renderer, char time[], TTF_Font* font, SDL_Color textColor){
    //Get rid of preexisting texture
	ResetTimerTexture(t);
	//Render text surface
	SDL_Surface* timerSurface = TTF_RenderText_Solid( font, time, textColor );
    //timerSurface = TTF_RenderText_Solid( font, time, textColor );
	if(timerSurface == NULL)
	{
		printf( "Unable to render timer surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        t->timerTexture = SDL_CreateTextureFromSurface(renderer, timerSurface);
		if( t->timerTexture == NULL )
		{
			printf( "Unable to create timer texture from rendered elapsed time! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
            t->timerWidth = timerSurface->w;
            t->timerHeight = timerSurface->h;
		}

		SDL_FreeSurface( timerSurface );

	}

	return t->timerTexture != NULL;
}
void Timer_render(Timer* t, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip){
	SDL_Rect renderQuad = {(x - t->timerWidth - 10), t->timerHeight, t->timerWidth, t->timerHeight };
    
	if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_Surface* bTimerSurface = SDL_CreateRGBSurface(0, t->timerWidth, t->timerHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(bTimerSurface, NULL, SDL_MapRGB(bTimerSurface->format, 0, 0, 0)); 
    SDL_Texture* bTimerTexture = SDL_CreateTextureFromSurface(renderer, bTimerSurface); 
    SDL_FreeSurface(bTimerSurface); 
    SDL_RenderCopy(renderer, bTimerTexture, clip, &renderQuad);
	SDL_RenderCopy(renderer, t->timerTexture, clip, &renderQuad); 
    SDL_DestroyTexture(bTimerTexture);
} 
