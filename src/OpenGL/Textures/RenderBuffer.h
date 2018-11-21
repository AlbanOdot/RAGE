#ifndef RenderBuffer_H
#define RenderBuffer_H
#include "Buffer.h"

class RenderBuffer : public Buffer
{
public:
    RenderBuffer();

    void init(int w, int h);
    void resize(int w, int h);
private:
    GLuint rbo;
protected:
    void initRender(int w, int h);
};

#endif // RenderBuffer_H
