#include "shader_program.h"

#include "shader.h"

#include <stdio.h>
#include <GL/glew.h>

int createShaderProgram(const char* vertShaderPath, const char* fragShaderPath)
{
    int vs = loadVertexShader(vertShaderPath);
    if (vs == -1)
    {
        return -1;
    }

    int fs = loadFragmentShader(fragShaderPath);
    if (fs == -1)
    {
        glDeleteShader(vs);
        return -1;
    }

    // create program
    int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    int success;
    char infolog[BUFSIZ];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infolog);
        fprintf(stderr, "Shader program failed! %s\n", infolog);
        return -1;
    }

    return program;
}
