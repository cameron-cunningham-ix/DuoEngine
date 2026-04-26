#include "include/renderer/Shader.hpp"

Shader::Shader(const char* filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    // Read lines from file
    while (getline(stream, line)) {
        // Determine if next section is a new shader
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                // Set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                // Set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    std::string vertexCode = ss[(int)ShaderType::VERTEX].str();
    std::string fragmentCode = ss[(int)ShaderType::FRAGMENT].str();

    CompileShaders(vertexCode.c_str(), fragmentCode.c_str());
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Get vertex / fragment source code from file paths
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Ensure ifstreams can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    CompileShaders(vShaderCode, fShaderCode);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::CompileShaders(const char* vertexCode, const char* fragmentCode) {
    // Compile shaders
    unsigned int vertex, fragment;
    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // Shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMatrix4f(const std::string& name, RendMath::Mat4f matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix(0,0));
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char info_log[1024];
    if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, info_log);
            std::cout << "Error::PROGRAM::COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n" << std::endl;
        }
    }
    else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, info_log);
            std::cout << "Error::SHADER::COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n" << std::endl;
        }

    }
}