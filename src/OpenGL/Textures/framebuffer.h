#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void init(int w, int h);

    void bind();
    void unbind();
    void unbindOther(unsigned int id);

    void resize(int w, int h);
    unsigned int textureColor;

private:

    int m_width;
    int m_height;

    unsigned int m_id;
    unsigned int rbo;

};

#endif // FRAMEBUFFER_H
