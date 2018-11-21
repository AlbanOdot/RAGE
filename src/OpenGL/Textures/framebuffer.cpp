#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() : RenderBuffer(){
    glGenTextures(1, &buf);
}

void FrameBuffer::init(int w, int h){
    initFrame(w,h);
}

void FrameBuffer::initFrame(int w, int h){

    bind();
    glBindTexture(GL_TEXTURE_2D, buf);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buf, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "Framebuffer is not complete !";
    }
    unbind();
    initRender(w,h);
}

void FrameBuffer::resize(int w, int h) {
    initFrame(w,h);
}
