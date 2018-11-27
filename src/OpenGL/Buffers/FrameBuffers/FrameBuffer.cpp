#include "framebuffer.h"

FrameBuffer::FrameBuffer(){
    glGenFramebuffers(1, &m_id);
}

void FrameBuffer::init(int w, int h) {
    m_width = w;
    m_height = h;
}

void FrameBuffer::initFrameBuffer(int w, int h) {
  m_width = w;
  m_height = h;
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &m_id);
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::unbindOther(unsigned int id){
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBuffer::resize(int w, int h) {
    initFrameBuffer(w,h);
}
