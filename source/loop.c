#include "loop.h"

#include "graphics.h"
#include "obj_loader.h"
#include "shader_program.h"

#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cglm/cglm.h>

int handleEvent(void)
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

void update(void)
{

}

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,
    -1.0f,
    0.0f,
    1.0f,
    -1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
};

unsigned int program;
GLuint vertexbuffer;
GLuint VertexArrayID;
GLuint MatrixID;
mat4 MVP;

void render(GfxContext* gfxContext, Mesh* mesh)
{
    (void)mesh;
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(program);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        (void*)0 // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);

    SDL_GL_SwapWindow(gfxContext->window);
}

void loop(GfxContext* gfxContext)
{
    Mesh mesh;
    initMesh(&mesh);

    objLoad("../models/cube.obj", &mesh);

    program = createShaderProgram("../shaders/vert.glsl", "../shaders/frag.glsl");

    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(program, "MVP");

    mat4 Projection;
    glm_perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f, Projection);
    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    mat4 View;
    glm_lookat(
        (vec3) { 4, 3, 3 }, // Camera is at (4,3,3), in World Space
        (vec3) { 0, 0, 0 }, // and looks at the origin
        (vec3) { 0, 1, 0 }, // Head is up (set to 0,-1,0 to look upside-down)
        View
    );

    // Model matrix : an identity matrix (model will be at the origin)
    mat4 Model;
    glm_mat4_identity(Model);

    // Our ModelViewProjection : multiplication of our 3 matrices
    glm_mat4_mul(Projection, View, MVP);
    glm_mat4_mul(MVP, Model, MVP); // Remember, matrix multiplication is the other way around


    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    while (1)
    {
        if (handleEvent())
        {
            return;
        }

        update();
        render(gfxContext, &mesh);
    }
}
