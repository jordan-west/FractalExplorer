#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &m_vao_id);

    Upload(vertices, indices);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao_id);
    glDeleteBuffers(1, &m_vbo_id);
    glDeleteBuffers(1, &m_ebo_id);

    m_vao_id = 0;
    m_vbo_id = 0;
    m_ebo_id = 0;
    m_indices_size = 0;
}

void Mesh::Render() const
{
    glBindVertexArray(m_vao_id);

    glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::Upload(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    glGenBuffers(1, &m_vbo_id);
    glGenBuffers(1, &m_ebo_id);

    glBindVertexArray(m_vao_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    m_indices_size = indices.size();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, ux));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
