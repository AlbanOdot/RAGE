#include "Renderbuffer.h"

RenderBuffer::RenderBuffer() : FrameBuffer(){
    glGenRenderbuffers(1, &m_rbo);
}

void RenderBuffer::init(int w, int h) {
  initRenderBuffer(w,h);
}

void RenderBuffer::resize(int w, int h) {
    initRenderBuffer(w,h);
}

void RenderBuffer::initRenderBuffer(int w, int h){
  initFrameBuffer(w,h);
  bind();
  glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
  unbind();
}
