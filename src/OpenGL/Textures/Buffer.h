#ifndef BUFFER_H
#define BUFFER_H
#include <gl3.h>
#include <gl3ext.h>
#include <iostream>

class Buffer
{
public:
    Buffer();
    Buffer(int w, int h);
    ~Buffer();

    virtual void init(int w, int h);

    void bind();
    void initBuffer(int w, int h);
    void unbind();
    void unbindOther(unsigned int id);

    virtual void resize(int w, int h);
    void clear();
private:
    GLuint m_id;
protected:
    int m_width;
    int m_height;
};

#endif // BUFFER_H
