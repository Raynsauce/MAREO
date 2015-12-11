#include "stdafx.h"

inline int vlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLine(renderer, x, y1, x, y2);
	return result;
}
inline int hlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8& r, Uint8& g, Uint8& b, Uint8& a)
{
	int result = 0;
	result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);
	result |= SDL_RenderDrawLine(renderer, x, y1, x, y2);
	return result;
//Returns 0 on success
}
//Returns 0 on success
inline int fillEllipse(SDL_Renderer * renderer,Sint16 x,Sint16 y,Sint16 rx,Sint16 ry,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	int result = 0;
	int ix = 0; int iy = 0;
	int h = 0; int i = 1; int j = 0; int k = 0; /* i INTENTIONALLY INIT TO 1 */
	//initialized later:
	int oh,oi,oj,ok;
	int xmh,xph;	int xmi,xpi;
	int xmj,xpj;	int xmk,xpk;
	int yc00,yc01;

	/* Sanity check radii */
	if((rx < 0) || (ry < 0)) { return (-1); }
	/* Special case for rx=0 -- draw a vline */
	if(rx == 0) { return (vlineRGBA(renderer,x,y - ry,y + ry,r,g,b,a)); }
	/* Special case for ry=0 -- draw a hline */
	if(ry == 0) { return (hlineRGBA(renderer,x - rx,x + rx,y,r,g,b,a)); }

	/* Set color */
	result |= SDL_SetRenderDrawBlendMode(renderer,(a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer,r,g,b,a);

	/* Init vars */
	oh = oi = oj = ok = 0xFFFF;

	/* Draw */
	if(rx > ry) {
		ix = 0;
		iy = rx * 64;
		for(;i > h;) {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if((ok != k) && (oj != k)) {
				xph = x + h;
				xmh = x - h;
				if(k > 0) {
					yc00 = y + k;	//Refrain from computing these twice
					result |= SDL_RenderDrawLine(renderer,xmh,yc00,xph,yc00);
					yc01 = y - k;
					result |= SDL_RenderDrawLine(renderer,xmh,yc01,xph,yc01);
				} else {
					result |= SDL_RenderDrawLine(renderer,xmh,y,xph,y);
				}
				ok = k;
			}
			if((oj != j) && (ok != j) && (k != j)) {
				xmi = x - i;
				xpi = x + i;
				if(j > 0) {
					yc00 = y + j;
					result |= SDL_RenderDrawLine(renderer,xmi,yc00,xpi,yc00);
					yc01 = y - j;
					result |= SDL_RenderDrawLine(renderer,xmi,yc01,xpi,yc01);
				} else {
					result |= SDL_RenderDrawLine(renderer,xmi,y,xpi,y);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;
		}/*while(i > h);*/
	} else {	//if(rx <= ry)
		ix = 0;
		iy = ry * 64;

		for(;i > h;) {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if((oi != i) && (oh != i)) {
				xmj = x - j;
				xpj = x + j;
				if(i > 0) {
					yc00 = y + i;
					result |= SDL_RenderDrawLine(renderer,xmj,yc00,xpj,yc00);
					yc01 = y - i;
					result |= SDL_RenderDrawLine(renderer,xmj,yc01,xpj,yc01);
				} else {
					result |= SDL_RenderDrawLine(renderer,xmj,y,xpj,y);
				}
				oi = i;
			}
			if((oh != h) && (oi != h) && (i != h)) {
				xmk = x - k;
				xpk = x + k;
				if(h > 0) {
					yc00 = y + h;
					result |= SDL_RenderDrawLine(renderer,xmk,yc00,xpk,yc00);
					yc01 = y - h;
					result |= SDL_RenderDrawLine(renderer,xmk,yc01,xpk,yc01);
				} else {
					result |= SDL_RenderDrawLine(renderer,xmk,y,xpk,y);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;
		}/*while(i > h);*/
	}

	return (result);
}
//Draws circle with current render colour
inline int fillEllipse(SDL_Renderer * renderer,Sint16 x,Sint16 y,Sint16 rx,Sint16 ry)
{
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
	return fillEllipse(renderer,x,y,rx,ry, r,g,b,a);
}