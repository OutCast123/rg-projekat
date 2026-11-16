#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Kvadrant.hpp"
#include "Shader.hpp"
#include "Teksture.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void crtaj(const Shader &shader, const std::vector<Texture> &teksture);

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
        Shader shader( "./app/shaders/vertex.vs" , "./app/shaders/fragment.fs");
        if (!shader.isValid()) {
            glfwTerminate();
            return -1;
        }

        std::vector<Texture> teksture;
        teksture.reserve(4);
        teksture.emplace_back("resources/teksture/tekstura1.jpg");
        teksture.emplace_back("resources/teksture/tekstura2.jpg");
        teksture.emplace_back("resources/teksture/tekstura3.jpg");
        teksture.emplace_back("resources/teksture/tekstura4.jpg");

        shader.use();
        shader.setInt("tekstura", 0);

        float vertices[] = {
        // prvi
         0.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 0
         1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // 1
         0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 2
         1.0f, 1.0f, 0.0f,  1.0f, 1.0f, // 3
        // drugi
        -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 4
         0.0f, 0.0f, 0.0f,  1.0f, 0.0f, // 5
        -1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 6
         0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // 7
        // treci
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // 8
         0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // 9
        -1.0f,  0.0f, 0.0f,  0.0f, 1.0f, // 10
         0.0f,  0.0f, 0.0f,  1.0f, 1.0f, // 11
        // cetvrti
         0.0f, -1.0f, 0.0f,  0.0f, 0.0f, // 12
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // 13
         0.0f,  0.0f, 0.0f,  0.0f, 1.0f, // 14
         1.0f,  0.0f, 0.0f,  1.0f, 1.0f, // 15
};

unsigned indices[] = {
        0, 1, 3,   0, 2, 3,     // prvi
        4, 5, 7,   4, 6, 7,     // drugi
        8, 9, 11,  8, 10, 11,   // treci
        12, 13, 15, 12, 14, 15  // cetvrti
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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float))); 
        glEnableVertexAttribArray(1);    

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            processInput(window);

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(VAO);
            crtaj(shader,teksture);

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

    static bool tWasPressed = false;
    bool tPressed = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
    bool tJustPressed = tPressed && !tWasPressed;
    tWasPressed = tPressed;

    if (!shift) return;

    static int selected = -1;

    for (int k = 0; k < 4; k++) {
        if (glfwGetKey(window, GLFW_KEY_1 + k) == GLFW_PRESS) {
            selected = k;
        }
    }

    if (selected < 0) return;

    if (tJustPressed) {
        float f = g_kvadranti[selected].getTextureFactor();
        g_kvadranti[selected].setTextureFactor(f == 1.0f ? 0.65f : 1.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        g_kvadranti[selected].setColor({1.0f, 0.0f, 0.0f});
        g_kvadranti[selected].setTextureFactor(std::max(g_kvadranti[selected].getTextureFactor(), 0.65f));
    } else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        g_kvadranti[selected].setColor({0.0f, 1.0f, 0.0f});
        g_kvadranti[selected].setTextureFactor(std::max(g_kvadranti[selected].getTextureFactor(), 0.65f));
    } else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        g_kvadranti[selected].setColor({0.0f, 0.0f, 1.0f});
        g_kvadranti[selected].setTextureFactor(std::max(g_kvadranti[selected].getTextureFactor(), 0.65f));
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void crtaj(const Shader &shader, const std::vector<Texture> &teksture) {
    shader.setVec4("ourColor", g_kvadranti[0].getColor(), 1.0f);
    shader.setFloat("useTexture", g_kvadranti[0].getTextureFactor());
    teksture[0].bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    shader.setVec4("ourColor", g_kvadranti[1].getColor(), 1.0f);
    shader.setFloat("useTexture", g_kvadranti[1].getTextureFactor());
    teksture[1].bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

    shader.setVec4("ourColor", g_kvadranti[2].getColor(), 1.0f);
    shader.setFloat("useTexture", g_kvadranti[2].getTextureFactor());
    teksture[2].bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));
    
    shader.setVec4("ourColor", g_kvadranti[3].getColor(), 1.0f);
    shader.setFloat("useTexture", g_kvadranti[3].getTextureFactor());
    teksture[3].bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));
}