#include "ssaoframebuffer.h"
#include "framebuffer.h"
#include <gl3.h>
#include <gl3ext.h>
#include <iostream>

SSAOFrameBuffer::SSAOFrameBuffer(){
    glGenFramebuffers(1, &m_id);
    glGenTextures(1, &buf);
    glGenRenderbuffers(1, &rbo);
}

void SSAOFrameBuffer::init(int w, int h) {
    m_width = w;
    m_height = h;
    bind();

    glBindTexture(GL_TEXTURE_2D, buf);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buf, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "SSAOFramebuffer is not complete !";
    }
    unbind();
}

SSAOFrameBuffer::~SSAOFrameBuffer() {
    glDeleteFramebuffers(1, &m_id);
}

void SSAOFrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void SSAOFrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAOFrameBuffer::unbindOther(unsigned int id){
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void SSAOFrameBuffer::resize(int w, int h) {
    init(w,h);
}
