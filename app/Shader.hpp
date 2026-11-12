#pragma once

#include <glad/glad.h>
#include <string>

class Shader {

private:
    std::string vertexPath;
    std::string fragmentPath;

    static std::string readFile(const std::string &path, bool &ok);
    static unsigned int compile(GLenum type, const std::string &source, const std::string &name);
    static unsigned int build(const std::string &vsPath, const std::string &fsPath);
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    void use() const;
    bool isValid() const { return ID != 0; }

    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    unsigned int ID = 0;
};