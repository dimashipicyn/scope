#include "graphics.h"
#include "loop.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    GfxContext gfxContext;
    if (gfxInit(&gfxContext, "Scope", 800, 600))
    {
        // Error
        return 1;
    }

    loop(&gfxContext);

    gfxDestroy(&gfxContext);
    return 0;
}
