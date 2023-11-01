#pragma once

#include "vec.h"

typedef struct Mesh
{
    int numVertices;
    int sizeVertices;
    Vec3* vertices;

    int numNormals;
    int sizeNormals;
    Vec3* normals;

    int numIndices;
    int sizeIndices;
    int* indices;
} Mesh;

void initMesh(Mesh* mesh);
void addVertice(Mesh* mesh, Vec3 vertice);
void addNormal(Mesh* mesh, Vec3 normal);
void addIndex(Mesh* mesh, int index);
