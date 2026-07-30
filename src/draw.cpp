#include "draw.h"

void DrawScene(Game * game, Ball *balls, Paddle *paddles, Powerup *powerups, defines def)
{
	int i;
	SDL_Surface * screen = game->GetScreen();
	InitBackground(screen);
/*	for (i = 0; i < def.GetMaxBalls(); i++)
		if (balls[i].GetShow())
			balls[i].clearBG ();
	for (i = 0; i < def.GetMaxPaddles(); i++)
		paddles[i].clearBG();
	if (def.GetPowerups())
	for (i = 0; i < def.GetMaxPowerups(); i++)
		if (powerups[i].GetState()) powerups[i].clearBG();
	for (i = 0; i < def.GetMaxBalls(); i++)
		if (balls[i].GetShow()) balls[i].updateBG();
	for (i = 0; i < def.GetMaxPaddles(); i++)
		paddles[i].updateBG();
	if (def.GetPowerups())
	for (i = 0; i < def.GetMaxPowerups(); i++)
		if (powerups[i].GetState()) powerups[i].updateBG();
*/
	for (i = 0; i < def.GetMaxBalls(); i++)
		if (balls[i].GetShow()) {
			balls[i].draw();
		}
	for (i = 0; i < def.GetMaxPaddles(); i++)
			paddles[i].draw();
	if (def.GetPowerups())
	for (i = 0; i < def.GetMaxPowerups(); i++)
		if (powerups[i].GetState()) powerups[i].draw();

	DrawResults(game, paddles,10,10);
//For Windows
//      SDL_Flip(screen);
//For Linux
	PresentScreen(game);
}

void DrawResults(Game * game, Paddle *paddles, int i, int j)
{
	SDL_Surface * screen = game->GetScreen();
	SDLFont * font = game->GetFont();
	char str[10];
	(void) sprintf(str,"%d",paddles[0].GetPoints());
	drawString(screen,font,i,j,str);
	drawString(screen,font,i+30,j,":");
	(void) sprintf(str,"%d",paddles[1].GetPoints());
	drawString(screen,font,i+50,j,str);
	SDL_Rect rect={i,i,i+80,i+30};
	AddRectList(game,rect);
}

SDL_Surface * ImageLoad(char *file)
{
	SDL_Surface *temp1, *temp2;
	temp1 = SDL_LoadBMP(file);
	temp2 = SDL_ConvertSurfaceFormat(temp1, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(temp1);
	return temp2;
}

void DrawIMG(SDL_Surface *screen, SDL_Surface *img, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(img, NULL, screen, &dest);
}

void DrawBG(SDL_Surface *screen, SDL_Surface *back)
{
	DrawIMG(screen, back, 0, 0);
}

void ResetRectList(Game * game)
{
	game->SetRectNum(0);
}

void AddRectList(Game * game, SDL_Rect rect)
{
	game->GetRectList()[game->GetRectNum()] = FixRect(rect);
	game->SetRectNum(game->GetRectNum() + 1);
}
void InitBackground(SDL_Surface * screen)
{
	SDL_FillRect(screen,NULL,0x000000);
}

void WindowToGameCoords(Game *game, int wx, int wy, int *gx, int *gy)
{
	SDL_Surface *dst = SDL_GetWindowSurface(game->GetWindow());
	SDL_Surface *src = game->GetScreen();
	if (dst->w != src->w || dst->h != src->h) {
		float sx = (float)dst->w / src->w;
		float sy = (float)dst->h / src->h;
		float scale = (sx < sy) ? sx : sy;
		int ox = (dst->w - (int)(src->w * scale)) / 2;
		int oy = (dst->h - (int)(src->h * scale)) / 2;
		*gx = (int)((wx - ox) / scale);
		*gy = (int)((wy - oy) / scale);
	} else {
		*gx = wx;
		*gy = wy;
	}
}

void PresentScreen(Game *game)
{
	SDL_Surface *dst = SDL_GetWindowSurface(game->GetWindow());
	SDL_Surface *src = game->GetScreen();
	if (dst->w != src->w || dst->h != src->h) {
		float sx = (float)dst->w / src->w;
		float sy = (float)dst->h / src->h;
		float scale = (sx < sy) ? sx : sy;
		SDL_Rect r;
		r.w = (int)(src->w * scale);
		r.h = (int)(src->h * scale);
		r.x = (dst->w - r.w) / 2;
		r.y = (dst->h - r.h) / 2;
		SDL_FillRect(dst, NULL, 0);
		SDL_BlitScaled(src, NULL, dst, &r);
	} else {
		SDL_BlitSurface(src, NULL, dst, NULL);
	}
	SDL_UpdateWindowSurface(game->GetWindow());
}

