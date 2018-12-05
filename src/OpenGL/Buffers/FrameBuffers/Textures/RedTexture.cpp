#include "RedTexture.h"

RedTexture::RedTexture() : FrameBuffer(){
  glGenTextures(1, &m_buffer);
}

void RedTexture::init(int w, int h, float* data) {
  initRedTexture(w,h,data);
}
void RedTexture::init(int w, int h){
  initRedTexture(w,h,nullptr);
}
void RedTexture::resize(int w, int h, float *data) {
  initRedTexture(w,h,data);
}

void RedTexture::resize(int w, int h) {
  initRedTexture(w,h,nullptr);
}

void RedTexture::initRedTexture(int w, int h, float* data){
  initFrameBuffer(w,h);
  bind();
  glBindTexture(GL_TEXTURE_2D, m_buffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_FLOAT, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_buffer, 0);
  unbind();
}
