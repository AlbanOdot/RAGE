#ifndef GBUFFER_H
#define GBUFFER_H


class GBuffer
{
public:
    GBuffer();
    ~GBuffer();
    void init(int w, int h);

    void bind();
    void unbind();
    void unbindOther(unsigned int id);

    void resize(int w, int h);
    unsigned int position;
    unsigned int normal;
    unsigned int albedo;

private:

    int m_width;
    int m_height;

    unsigned int m_id;
    unsigned int rbo;

};

#endif // GBUFFER_H
