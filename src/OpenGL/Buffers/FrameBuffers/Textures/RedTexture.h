#ifndef REDTEXTURE_H
#define REDTEXTURE_H
#include "../FrameBuffer.h"

class RedTexture : public FrameBuffer
{
public:
  RedTexture();
  virtual ~RedTexture() override{}
  virtual void init(int w, int h, float * data);
  virtual void init(int w, int h) override;
  virtual void resize(int w, int h, float * data);
  virtual void resize(int w, int h) override;
  inline GLuint buffer() { return m_buffer;}
protected:
  void initRedTexture(int w, int h, float * data);
  GLuint m_buffer;
};

typedef RedTexture FloatTexture;
#endif // TEXTURE_H
