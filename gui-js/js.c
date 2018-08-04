#include "u.h"
#include "lib.h"
#include "dat.h"
#include "fns.h"
#include "error.h"

#include <draw.h>
#include <memdraw.h>
#include <keyboard.h>
#include <cursor.h>
#include <SDL.h>
#include "screen.h"

#define argv0 "drawterm"

SDL_Surface *window;

/* perfect approximation to NTSC = .299r+.587g+.114b when 0 ≤ r,g,b < 256 */
#define RGB2K(r,g,b)	((156763*(r)+307758*(g)+59769*(b))>>19)
#define FLIP(u)		(((u >> 24) & 0xff) | (((u >> 16) & 0xff) << 8) | (((u >> 8) & 0xff) << 16) | ((u & 0xff) << 24))

void
sdlbits(Memimage *i, Rectangle r)
{
	uchar *p;
	uchar *q;
	int bpp, j, k;

	SDL_LockSurface(window);
	bpp = window->format->BytesPerPixel;
	p = (uchar*) window->pixels + r.min.y * window->pitch + r.min.x * bpp;
	q = byteaddr(i, r.min);
	for(j = r.min.y; j < r.max.y; j++){
		for (k = 0; k < Dx(r); k++) {
			((ulong*)p)[k] = FLIP(((ulong*)q)[k]);
		}
		p += window->pitch;
		q += window->pitch;
	}
	SDL_UnlockSurface(window);
}

ulong
pixelbits(Memimage *m, Point p)
{
	SDL_Surface *s;
	ulong r;

	if(window != NULL){
		s = window;
		SDL_LockSurface(s);
		r = * ((ulong *) s->pixels + p.y * s->pitch + p.x * 4);
		r = FLIP(r);
		SDL_UnlockSurface(s);
		return r;
	}
	return pixelbits(m, p);
}

static int
xdraw(Memimage *dst, Rectangle r, Memimage *src, Point sp, Memimage *mask, Point mp, int op)
{
	return 0;
}

Memimage *gscreen;
Screeninfo screen;

void
flushmemscreen(Rectangle r)
{
	sdlbits(gscreen, r);
	SDL_UpdateRect(window, r.min.x, r.min.y, Dx(r), Dy(r));
}

Memimage *
xinitscreen(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return NULL;

	window = SDL_SetVideoMode(640, 480, 32, 0);
	if(window == NULL)
		return NULL;
	
	gscreen = allocmemimage(Rect(0, 0, 640, 480), RGBA32);
	
	return gscreen;
}

void
screeninit(void)
{
	_memmkcmap();

	gscreen = xinitscreen();

	memimageinit();
	terminit();
	qlock(&drawlock);
	flushmemscreen(gscreen->clipr);
	qunlock(&drawlock);
}

uchar*
attachscreen(Rectangle *r, ulong *chan, int *depth,
	int *width, int *softscreen)
{
	*r = gscreen->r;
	*chan = gscreen->chan;
	*depth = gscreen->depth;
	*width = gscreen->width;
	*softscreen = 1;

	return gscreen->data->bdata;
}

void
mouseset(Point xy)
{
}

void
setcursor(void)
{
}

void
cursorarrow(void)
{
}

void
getcolor(ulong i, ulong *r, ulong *g, ulong *b)
{
	ulong v;
	
	v = cmap2rgb(i);
	*r = (v>>16)&0xFF;
	*g = (v>>8)&0xFF;
	*b = v&0xFF;
}

void
setcolor(ulong i, ulong r, ulong g, ulong b)
{
	/* no-op */
}

int
atlocalconsole(void)
{
	return 0;
}

static char *snarfbuf = NULL;

char*
clipread(void)
{
	return strdup(snarfbuf? snarfbuf: ""); 
}

int
clipwrite(char *buf)
{
	if (snarfbuf)
		free(snarfbuf);
	snarfbuf = strdup(buf);
	return 0;
}

void
setterm(int raw)
{
}

void
guimain(void)
{
	cpubody();
}
