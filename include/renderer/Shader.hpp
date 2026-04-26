#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "math/Mat4.hpp"

class Shader {
public:
    unsigned int ID;    // Unique ID of shader program

    // Constructor that reads and builds shader from one file
    Shader(const char* filePath);
    // Constructor that reads and builds shader from two files, vertex and fragment
    Shader(const char* vertexPath, const char* fragmentPath);
    // Deconstructor
    ~Shader();
    // Activate shader
    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMatrix4f(const std::string &name, RendMath::Mat4f matrix) const;

private:
    // Utility function for checking shader compilation/linking errors
    void checkCompileErrors(unsigned int shader, std::string type);
    void CompileShaders(const char* vertexCode, const char* fragmentCode);
};

#endif