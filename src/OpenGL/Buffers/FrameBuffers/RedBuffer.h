#ifndef REDBUFFER_H
#define REDBUFFER_H
#include "Renderbuffer.h"

class RedBuffer : public RenderBuffer
{
public:
  RedBuffer();
  virtual ~RedBuffer(){}
  virtual void init(int w, int h);
  virtual void resize(int w, int h);
  inline GLuint buffer() { return m_buffer;}
protected:
  void initRedBuffer(int w, int h);
  GLuint m_buffer;
};

typedef RedBuffer FloatBuffer;

#endif // REDBUFFER_H
