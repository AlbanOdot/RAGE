#ifndef GBUFFER_H
#define GBUFFER_H
#include "RenderBuffer.h"

class GBuffer : public RenderBuffer
{
public:
    GBuffer();

    void init(int w, int h);
    void resize(int w, int h);
    GLuint positions() const {return position;}
    GLuint normals() const {return normal;}
    GLuint albedos() const {return albedo;}
private:
    unsigned int position;
    unsigned int normal;
    unsigned int albedo;

protected:
     void initGBuffer(int w, int h);

};

#endif // GBUFFER_H
