#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Kvadrant.hpp"
#include "Shader.hpp"

#ifndef SHADER_DIR
#define SHADER_DIR "app/shaders/"
#endif

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void crtaj(const Shader &shader);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::vector<Kvadrant> g_kvadranti = {
        Kvadrant({0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}),
        Kvadrant({0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}),
        Kvadrant({0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}),
        Kvadrant({0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}),
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Strahinja Vasiljevic", nullptr, nullptr);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    {
        Shader shader(SHADER_DIR "vertex.vs", SHADER_DIR "fragment.fs");
        if (!shader.isValid()) {
            glfwTerminate();
            return -1;
        }

        float vertices[] = {
                -1.0f , -1.0f , 0.0f ,  //dole levo 0
                 0.0f , -1.0f , 0.0f , // dole sredina 1
                 1.0f , -1.0f , 0.0f , // dole desno 2

                -1.0f , 0.0f , 0.0f , //sredina levo 3
                 0.0f , 0.0f , 0.0f , //sredina 4
                 1.0f , 0.0f , 0.0f , //sredina desno 5

                -1.0f , 1.0f , 0.0f ,  //gore levo 6
                 0.0f , 1.0f , 0.0f , // gore sredina 7
                 1.0f , 1.0f , 0.0f , // gore desno 8 
        };

        unsigned indices[] = {
                //prvi
                4 , 5 , 8,
                4 , 7 , 8,

                //drugi
                3 , 4 , 7,
                3 , 6, 7,

                //treci
                0 , 1 , 4,
                0 , 3 , 4,

                //cetrvti
                1 , 2 , 5,
                1 , 4 , 5
        };

        unsigned int VBO, VAO, EBO;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            processInput(window);

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(VAO);
            crtaj(shader);

            glfwSwapBuffers(window);
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    bool shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                 glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
    if (!shift) return;

    static int selected = -1;

    for (int k = 0; k < 4; k++) {
        if (glfwGetKey(window, GLFW_KEY_1 + k) == GLFW_PRESS) {
            selected = k;
        }
    }

        
    if (selected < 0) return;

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        g_kvadranti[selected].setColor({1.0f, 0.0f, 0.0f});
    } else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        g_kvadranti[selected].setColor({0.0f, 1.0f, 0.0f});
    } else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        g_kvadranti[selected].setColor({0.0f, 0.0f, 1.0f});
    }
    
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void crtaj(const Shader &shader) {
    shader.setVec4("ourColor", g_kvadranti[0].getColor(), 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    shader.setVec4("ourColor", g_kvadranti[1].getColor(), 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));
    shader.setVec4("ourColor", g_kvadranti[2].getColor(), 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));
    shader.setVec4("ourColor", g_kvadranti[3].getColor(), 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));
}