#include "graphics.h"

#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

int gfxInit(GfxContext* gfxContext, const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

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

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_DestroyWindow(window);
        SDL_GL_DeleteContext(ctx);
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
    SDL_GL_DeleteContext(gfxContext->glCtx);
    SDL_memset(gfxContext, 0, sizeof(GfxContext));
    SDL_Quit();
}
