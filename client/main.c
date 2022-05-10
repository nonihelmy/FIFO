#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "filehandler.h"
#include "floatingWords.h"
#include "LTexture.h"
#include "game.h"
#include "menu.h"

int main(int argc, char *args[])
{

  UDPsocket sd;
  IPaddress srvadd;
  UDPpacket *p;
  UDPpacket *p2;

  if (SDLNet_Init() < 0)
  {
    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    getchar();
    exit(EXIT_FAILURE);
  }

  if (!(sd = SDLNet_UDP_Open(0)))
  {
    fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
    getchar();
    exit(EXIT_FAILURE);
  }

  /* Resolve server name  */
  if (SDLNet_ResolveHost(&srvadd, "127.0.0.1", 2000) == -1)
  {
    fprintf(stderr, "SDLNet_ResolveHost(127.0.0.1 2000): %s\n", SDLNet_GetError());
    getchar();
    exit(EXIT_FAILURE);
  }

  if (!(p = SDLNet_AllocPacket(512)))
  {
    fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
    getchar();
    exit(EXIT_FAILURE);
  }

  // sprintf((char *)p->data, "%d %d\n", (int)text.x, (int)text.y);
  p->address.host = srvadd.host; /* Set the destination host */
  p->address.port = srvadd.port; /* And destination port */
  p->len = strlen((char *)p->data) + 1;
  SDLNet_UDP_Send(sd, -1, p);

  // INdetifiera om du är host , öppna lobby
  // om inte host vad ska hända
  // Om du är klient connect till server genom att ge ip adress

  GameRenderer game;
  menu(&game);

  // SDL_FreeSurface(surfaceMessage);
  // SDL_DestroyTexture(Message);

  return 0;
}
