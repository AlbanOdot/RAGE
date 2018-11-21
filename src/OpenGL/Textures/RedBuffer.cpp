#include "RedBuffer.h"

RedBuffer::RedBuffer() : RenderBuffer(){
    glGenTextures(1, &buf);
}

void RedBuffer::init(int w, int h) {
    initRed(w,h);
}

void RedBuffer::initRed(int w, int h){
    bind();

    glBindTexture(GL_TEXTURE_2D, buf);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buf, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "Redbuffer is not complete !";
    }
    unbind();
    initRender(w,h);
}

void RedBuffer::resize(int w, int h) {
    initRed(w,h);
}

