#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <gl3.h>
#include <gl3ext.h>
#include <iostream>

class FrameBuffer {
public:
    void initFrameBuffer(int w, int h);
    void bind();
    void unbind();
    void unbindOther(unsigned int id);

    virtual ~FrameBuffer();
    virtual void init(int w, int h);
    virtual void resize(int w, int h);

protected:
    FrameBuffer();
    int m_width;
    int m_height;
    unsigned int m_id;

};

#endif
