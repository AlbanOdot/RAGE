#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H
#include "FrameBuffer.h"


class RenderBuffer : public FrameBuffer{
public:
  virtual ~RenderBuffer(){}
  virtual void init(int w, int h);
  virtual void resize(int w, int h);
protected:
  RenderBuffer();
  void initRenderBuffer(int w, int h);
  GLuint m_rbo;
};

#endif // RENDERBUFFER_H
