#ifndef FRACTAL_EXPLORER_MESH_H_
#define FRACTAL_EXPLORER_MESH_H_

#include <glad/glad.h>

#include <vector>

class Mesh
{
    public:
        struct Vertex
        {
            Vertex(float x, float y, float z, float ux, float uy) : x(x), y(y), z(z), ux(ux), uy(uy) { } 

            float x, y, z;
            float ux, uy;
        };

        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void Render() const;
    private:
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void Upload(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

        GLuint m_vao_id;
        GLuint m_vbo_id;
        GLuint m_ebo_id;

        size_t m_indices_size;
};

#endif
