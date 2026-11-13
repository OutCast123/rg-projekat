#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    : vertexPath(vertexPath), fragmentPath(fragmentPath) {
    ID = build(vertexPath, fragmentPath);
}

Shader::~Shader() {
    if (ID != 0) {
        glDeleteProgram(ID);
    }
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setVec4(const std::string &name, const glm::vec3 &v, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v.x, v.y, v.z, w);
}

std::string Shader::readFile(const std::string &path, bool &ok) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "ERROR::SHADER::FILE_NOT_FOUND: " << path << std::endl;
        ok = false;
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    ok = true;
    return ss.str();
}

unsigned int Shader::compile(GLenum type, const std::string &source, const std::string &name) {
    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED (" << name << ")\n"
                  << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

unsigned int Shader::build(const std::string &vsPath, const std::string &fsPath) {
    bool okVs = false, okFs = false;
    std::string vsSource = readFile(vsPath, okVs);
    std::string fsSource = readFile(fsPath, okFs);
    if (!okVs || !okFs) {
        return 0;
    }

    unsigned int vs = compile(GL_VERTEX_SHADER, vsSource, vsPath);
    unsigned int fs = compile(GL_FRAGMENT_SHADER, fsSource, fsPath);
    if (vs == 0 || fs == 0) {
        if (vs) glDeleteShader(vs);
        if (fs) glDeleteShader(fs);
        return 0;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}