#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  
#include "floatingWords.h" 

FWords* FWords_create(int x, int y, int index)
{
    FWords* fw = malloc(sizeof(FWords));
    fw->wordTexture = NULL;
	fw->posX = x; 
	fw->posY = y;
	fw->wordWidth = 0;
	fw->wordHeight = 0;
	fw->maxSwingRight = x + 5;
    fw->maxSwingLeft = x - 5;  
	fw->currentWordIndex = index;
	fw->swingRight = true;
	fw->correctGuessed = false;
	return fw;
}

void FWords_reset(FWords* fw)
{
    if( fw->wordTexture != NULL )
	{
		SDL_DestroyTexture( fw->wordTexture );
		fw->wordTexture = NULL;
		fw->wordWidth = 0;
		fw->wordHeight = 0;
	}
}

void FWords_destroy(FWords* fw)
{
    FWords_reset(fw);
    free(fw);
}
bool FWords_loadFromRenderedWord( FWords *fw, SDL_Renderer* renderer, char textureText[], TTF_Font* font, SDL_Color textColor ){
    //Get rid of preexisting texture
	FWords_reset(fw);

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText, textColor );
	if(textSurface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        fw->wordTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if( fw->wordTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			fw->wordWidth = textSurface->w;
			fw->wordHeight = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}

	return fw->wordTexture != NULL;
}
void FWords_render(FWords* fw, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip){
	SDL_Rect renderQuad = { x, y, fw->wordWidth, fw->wordHeight };

	if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

	//SDL_RenderCopyEx(renderer, fw->wordTexture, clip, &renderQuad, NULL, 0, NULL, 0); 
	SDL_RenderCopy(renderer, fw->wordTexture, clip, &renderQuad);
} 

void WordTick(FWords* fw){
	fw->posY++; 
	if (fw->swingRight)
    {
        fw->posX++;    
    }else{
        fw->posX--;
    } 
	if(fw->posX == fw->maxSwingRight){
        fw->swingRight = false; 
    } 
    if (fw->posX == fw->maxSwingLeft)
    {
        fw->swingRight = true;
    }
} 
int getPosY(FWords fw){
	return fw.posY;
} 
int getPosX(FWords fw){
	return fw.posX;
} 