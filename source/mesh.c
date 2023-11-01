#include "mesh.h"
#include "util.h"

#include <string.h>

void initMesh(Mesh* mesh)
{
    memset(mesh, 0, sizeof(Mesh));
}

void addVertice(Mesh* mesh, Vec3 vertice)
{
    REALLOC(Vec3, mesh->vertices, mesh->numVertices, mesh->sizeVertices);
    mesh->vertices[mesh->numVertices++] = vertice;
}

void addNormal(Mesh* mesh, Vec3 normal)
{
    REALLOC(Vec3, mesh->normals, mesh->numNormals, mesh->sizeNormals);
    mesh->normals[mesh->numNormals++] = normal;
}

void addIndex(Mesh* mesh, int index)
{
    REALLOC(int, mesh->indices, mesh->numIndices, mesh->sizeIndices);
    mesh->indices[mesh->numIndices++] = index;
}
