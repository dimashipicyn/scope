#include "obj_loader.h"

#include <stdio.h>

void skipTo(FILE* file, char c);
void processV(FILE* file, Mesh* mesh);
void processVertice(FILE* file, Mesh* mesh);
void processVn(FILE* file, Mesh* mesh);
void processF(FILE* file, Mesh* mesh);

int objLoad(const char* path, Mesh* mesh)
{
    FILE* file = NULL;
    fopen_s(&file, path, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open file '%s'\n", path);
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        switch (ch)
        {
        case 'v':
            processV(file, mesh);
            break;
        case 'f':
            processF(file, mesh);
            break;
        default:
            skipTo(file, '\n');
            break;
        }
    }

    return 0;
}

void skipTo(FILE* file, char c)
{
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == c)
        {
            break;
        }
    }
}

void processV(FILE* file, Mesh* mesh)
{
    int ch;
    if ((ch = fgetc(file)) != EOF)
    {
        switch (ch)
        {
        case ' ':
            processVertice(file, mesh);
            break;
        case 'n':
            processVn(file, mesh);
            break;
        default:
            skipTo(file, '\n');
            break;
        }
    }
}

void processVertice(FILE* file, Mesh* mesh)
{
    Vec3 vertice;
    if (fscanf_s(file, "%f %f %f", &vertice.x, &vertice.y, &vertice.z) == 3)
    {
        addVertice(mesh, vertice);
    }

    skipTo(file, '\n');
}

void processVn(FILE* file, Mesh* mesh)
{
    Vec3 normal;
    if (fscanf_s(file, "%f %f %f", &normal.x, &normal.y, &normal.z) == 3)
    {
        addNormal(mesh, normal);
    }

    skipTo(file, '\n');
}

void processF(FILE* file, Mesh* mesh)
{
    int index;
    if (fscanf_s(file, "%d", &index) == 1)
    {
        addIndex(mesh, index);
    }

    skipTo(file, '\n');
}
