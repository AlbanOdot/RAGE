#include "framebuffer.h"
#include <gl3.h>
#include <gl3ext.h>
#include <iostream>
FrameBuffer::FrameBuffer(){
    glGenFramebuffers(1, &m_id);
    glGenTextures(1, &textureColor);
    glGenRenderbuffers(1, &rbo);
}

void FrameBuffer::init(int w, int h) {
    m_width = w;
    m_height = h;
    bind();

    glBindTexture(GL_TEXTURE_2D, textureColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColor, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "Framebuffer is not complete !";
    }
    unbind();
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
    init(w,h);
}
