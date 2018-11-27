#ifndef GBUFFER_H
#define GBUFFER_H
#include "Renderbuffer.h"

class GBuffer : public RenderBuffer
{
public:
    GBuffer();
    virtual ~GBuffer();
    virtual void init(int w, int h);
    virtual void resize(int w, int h);
    inline unsigned int position() const {return m_position;}
    inline unsigned int normal() const {return m_normal;}
    inline unsigned int albedo() const {return m_albedo;}
protected:
    unsigned int m_position;
    unsigned int m_normal;
    unsigned int m_albedo;
    void initGBuffer(int w, int h);

};

typedef GBuffer G3x3Buffer;

#endif // GBUFFER_H
