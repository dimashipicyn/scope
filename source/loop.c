#include "loop.h"

#include "graphics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

int handleEvent()
{
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
        if (Event.type == SDL_KEYDOWN)
        {
            switch (Event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return 1;
            default:
                break;
            }
        }
        else if (Event.type == SDL_QUIT)
        {
            return 1;
        }
    }
    return 0;
}

void update()
{

}

void render(GfxContext* gfxContext)
{
    glViewport(0, 0, gfxContext->width, gfxContext->height);
    glClearColor(1.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(gfxContext->window);
}

void loop(GfxContext* gfxContext)
{
    while (1)
    {
        if (handleEvent())
        {
            return;
        }

        update();
        render(gfxContext);
    }
}