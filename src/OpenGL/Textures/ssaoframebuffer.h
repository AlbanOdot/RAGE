#ifndef SSAOFRAMEBUFFER_H
#define SSAOFRAMEBUFFER_H


class SSAOFrameBuffer
{
public:
    SSAOFrameBuffer();
    ~SSAOFrameBuffer();

    void init(int w, int h);

    void bind();
    void unbind();
    void unbindOther(unsigned int id);

    void resize(int w, int h);
    unsigned int buf;

private:

    int m_width;
    int m_height;

    unsigned int m_id;
    unsigned int rbo;
};

#endif // SSAOFRAMEBUFFER_H
