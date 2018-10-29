#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include "./opengl_stuff.h"
#include <string>

class ShaderLoader {
public:
    ShaderLoader();
    ~ShaderLoader();

    ShaderLoader(const char * shaderSource, int  type, const char * error);

    GLuint getShader() {return shader;}
    GLuint getType() { return type;}

private:
    GLuint shader;
    GLenum type;
};
#endif
