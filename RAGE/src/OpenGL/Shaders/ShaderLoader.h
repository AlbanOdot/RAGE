#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <gl.h>
#include <string>

class ShaderLoader {
public:
    ShaderLoader();
    ~ShaderLoader();

    ShaderLoader(const char * shaderSource, GLenum  type, const std::string& error);

    GLuint getShader() {return shader;}
    GLuint getType() { return type;}

private:
    GLuint shader;
    GLenum type;
};
#endif
