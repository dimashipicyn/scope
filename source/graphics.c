#include "graphics.h"

#include <stdio.h>
#include <SDL2/SDL.h>

int gfxInit(GfxContext* gfxContext, const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialize: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (ctx == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL gl context failed to initialize: %s\n", SDL_GetError());
        return 1;
    }

    gfxContext->window = window;
    gfxContext->glCtx = ctx;
    gfxContext->width = width;
    gfxContext->height = height;

    return 0;
}

void gfxDestroy(GfxContext* gfxContext)
{
    SDL_DestroyWindow(gfxContext->window);
    SDL_memset(gfxContext, 0, sizeof(GfxContext));
    SDL_Quit();
}
