#pragma once

typedef struct SDL_Window SDL_Window;
typedef void* SDL_GLContext;

typedef struct GfxContext
{
    SDL_Window* window;
    SDL_GLContext glCtx;
    int width;
    int height;
} GfxContext;

int gfxInit(GfxContext* gfxContext, const char* title, int width, int height);
void gfxDestroy(GfxContext* gfxContext);
