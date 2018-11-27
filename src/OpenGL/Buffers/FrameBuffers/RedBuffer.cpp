#include "RedBuffer.h"

RedBuffer::RedBuffer() : RenderBuffer(){
  glGenTextures(1, &m_buffer);
}

void RedBuffer::init(int w, int h) {
  initRedBuffer(w,h);
}

void RedBuffer::resize(int w, int h) {
  initRedBuffer(w,h);
}

void RedBuffer::initRedBuffer(int w, int h){
  initRenderBuffer(w,h);
  bind();
  glBindTexture(GL_TEXTURE_2D, m_buffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_buffer, 0);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
      std::cerr << "Framebuffer is not complete !";
    }
  unbind();
}
