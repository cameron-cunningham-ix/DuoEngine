#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glad/glad.h>

#include "Vertex.hpp"
#include "Shader.hpp"

/// @brief Holds mesh data for rendering objects in OpenGL
class Mesh {
public:

    // Default constructor
    Mesh();
    Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices);
    // Move constructor
    Mesh(Mesh&& other);
    // Deconstructor
    ~Mesh();

    // Move assignment
    Mesh& operator=(Mesh&& other);

    // Tells OpenGL to draw this mesh
    void drawMesh(Shader& shader);

private:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int indicesSize;

    // Render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();

};

#endif