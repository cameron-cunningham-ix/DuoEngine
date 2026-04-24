#include <glad/glad.h>

#include "include/renderer/Mesh.hpp"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    EBO = 0;
}

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices) :
    vertices(std::move(vertices)), indices(std::move(indices)) {
        indicesSize = this->indices.size();
        setupMesh();
}

Mesh::Mesh(Mesh&& other) {
    this->VAO = other.VAO;
    this->VBO = other.VBO;
    this->EBO = other.EBO;
    this->indicesSize = other.indicesSize;
    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
}

Mesh& Mesh::operator=(Mesh&& other) {
    if (this == &other) return *this;
    this->VAO = other.VAO;
    this->VBO = other.VBO;
    this->EBO = other.EBO;
    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
    return *this;
}

Mesh::~Mesh() {
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
    if (EBO != 0)
        glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh() {
    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    // Binding the VBO buffer means any buffer calls made on the GL_ARRAY_BUFFER target will configure VBO.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // We copy the vertices data into the buffer's memory. 
    // 1st param: buffer type we want to copy data into; this is why we just bound VBO.
    // 2nd param: size of data in bytes. 
    // 3rd param: Actual data
    // 4th param: How we want the GPU to manage the given data.
    // GL_STATIC_DRAW suggests the data is set once and used many times.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBindVertexArray(0);

    // Clear vectors
    std::vector<Vertex>().swap(vertices);
    std::vector<unsigned int>().swap(indices);
};

// Tells OpenGL to draw this mesh
void Mesh::drawMesh(Shader& shader) {
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}