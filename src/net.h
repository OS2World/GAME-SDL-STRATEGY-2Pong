#ifndef __NET_H__
#define __NET_H__
#include "defs.h"
#include "draw.h"
#include <SDL/SDL_net.h>

#ifndef htons
#define htons(A)  ((((Uint16)(A) & 0xff00) >> 8) | \
                   (((Uint16)(A) & 0x00ff) << 8))
#endif
#ifndef htonl
#define htonl(A)  ((((Uint32)(A) & 0xff000000) >> 24) | \
                   (((Uint32)(A) & 0x00ff0000) >> 8)  | \
                   (((Uint32)(A) & 0x0000ff00) << 8)  | \
                   (((Uint32)(A) & 0x000000ff) << 24))
#endif
#ifndef ntohs
#define ntohs     htons
#endif
#ifndef ntohl
#define ntohl     htohl
#endif

void ParseNetData(Game *game,Ball * balls, Paddle * paddles, Uint8 * data);
void UpdateClient(Game * game, Ball * balls, Paddle * paddles, UDPsocket sock, int channel);
int StartServer(UDPsocket *sock, IPaddress *address, int *channel, int port);
int StartClient(UDPsocket *sock, IPaddress address, int *channel, int myport);
IPaddress GetAddress(SDL_Surface * screen, SDLFont * font);
int GetPort(SDL_Surface * screen, SDLFont * font, int server);

#endif
