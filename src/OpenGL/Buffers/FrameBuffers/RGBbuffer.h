#ifndef RGBBUFFER_H
#define RGBBUFFER_H
#include "Renderbuffer.h"


class RGBBuffer : public RenderBuffer
{
public:
  RGBBuffer();
  virtual ~RGBBuffer(){}
  virtual void init(int w, int h);
  virtual void resize(int w, int h);
  inline GLuint buffer() const { return m_buffer;}
protected:
  void initRGBBuffer(int w, int h);
  GLuint m_buffer;
};

typedef RGBBuffer RGBABuffer;

#endif // RGBBUFFER_H
