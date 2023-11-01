#include "shader.h"

#include <stdio.h>
#include <GL/glew.h>

static int loadShader(const char* path, int shaderType)
{
    FILE* file = NULL;
    fopen_s(&file, path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File open failed! %s\n", path);
        return -1;
    }

    char buffer[BUFSIZ + 1] = {0};
    fread_s(buffer, BUFSIZ, 1, BUFSIZ, file);

    unsigned int shaderId = glCreateShader(shaderType);
    const GLchar* code = buffer;
    glShaderSource(shaderId, 1, &code, NULL);
    glCompileShader(shaderId);

    int success = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success)
    {
        return shaderId;
    }

    // error
    char infolog[512];
    glGetShaderInfoLog(shaderId, 512, NULL, infolog);
    fprintf(stderr, "Load shader %s failed! %s\n", path, infolog);
    return -1;
}

int loadVertexShader(const char* path)
{
    return loadShader(path, GL_VERTEX_SHADER);
}

int loadFragmentShader(const char* path)
{
    return loadShader(path, GL_FRAGMENT_SHADER);
}
