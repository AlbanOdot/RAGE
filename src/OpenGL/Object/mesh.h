#ifndef MESH_H
#define MESH_H
#include <vector>

using namespace std;
class Mesh {
    public:
        /*  Mesh Data  */
        vector<float> m_vertices;
        vector<float> m_normals;
        vector<float> m_uv;
        vector<float> m_colors;
        vector<unsigned int> m_indices;
        /*  Functions  */
        Mesh(vector<float> vertices, vector<float> normals, vector<float> UV, vector<float> colors, vector<unsigned int> indices);
        void draw() const;
    private:
        /*  Render data  */
        unsigned int m_VAO, m_VBO, m_NBO, m_UVBO, m_CRBO, m_EBO;
        /*  Functions    */
        void setupMesh();
};
#endif // MESH_H
