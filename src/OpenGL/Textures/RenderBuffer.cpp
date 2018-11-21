#include "RenderBuffer.h"

RenderBuffer::RenderBuffer() : Buffer(){
    glGenRenderbuffers(1, &rbo);
}

void RenderBuffer::init(int w, int h){
    initRender(w,h);
}

void RenderBuffer::initRender(int w, int h){
    bind();
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "RenderBuffer is not complete !";
    }
    unbind();
    initBuffer(w,h);
}

void RenderBuffer::resize(int w, int h) {
    initRender(w,h);
}
