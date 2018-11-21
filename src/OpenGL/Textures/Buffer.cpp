#include "Buffer.h"
#include <gl3.h>
#include <gl3ext.h>
#include <iostream>

Buffer::Buffer(){
    glGenBuffers(1, &m_id);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &m_id);
}
Buffer::Buffer(int w, int h){
    glGenBuffers(1, &m_id);
    m_width = w;
    m_height = h;
}


void Buffer::init(int w, int h) {
    m_width = w;
    m_height = h;
}
void Buffer::initBuffer(int w, int h){
    m_width = w;
    m_height = h;
}

void Buffer::resize(int w, int h) {
    initBuffer(w,h);
}


void Buffer::bind() {
    glBindBuffer(GL_FRAMEBUFFER, m_id);
}

void Buffer::unbind() {
    glBindBuffer(GL_FRAMEBUFFER, 0);
}

void Buffer::unbindOther(unsigned int id){
    glBindBuffer(GL_FRAMEBUFFER, id);
}


void Buffer::clear(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
