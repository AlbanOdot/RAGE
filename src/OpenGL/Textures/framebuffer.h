#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "RenderBuffer.h"

class FrameBuffer : public RenderBuffer{
public:
    FrameBuffer();

    void init(int w, int h);
    void resize(int w, int h);

    GLuint buffer() const {return buf;}
private:
    unsigned int buf;

protected:
    void initFrame(int w, int h);

};

#endif // FRAMEBUFFER_H
