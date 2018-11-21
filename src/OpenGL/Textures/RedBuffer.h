#ifndef RedBUFFER_H
#define RedBUFFER_H
#include "RenderBuffer.h"

class RedBuffer : public RenderBuffer
{
public:
    RedBuffer();

    void init(int w, int h);
    void resize(int w, int h);

    GLuint buffer() const {return buf;}
private:
    unsigned int buf;

protected:
    void initRed(int w, int h);
};

#endif // RedBUFFER_H
