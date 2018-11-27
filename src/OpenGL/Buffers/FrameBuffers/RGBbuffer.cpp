
#include "RGBbuffer.h"

RGBBuffer::RGBBuffer() : RenderBuffer(){
  glGenTextures(1, &m_buffer);
}

void RGBBuffer::init(int w, int h) {
  initRGBBuffer(w,h);
}

void RGBBuffer::resize(int w, int h) {
  initRGBBuffer(w,h);
}

void RGBBuffer::initRGBBuffer(int w, int h){
  initRenderBuffer(w,h);
  bind();
  glBindTexture(GL_TEXTURE_2D, m_buffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_buffer, 0);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
      std::cerr << "Framebuffer is not complete !";
    }
  unbind();
}
