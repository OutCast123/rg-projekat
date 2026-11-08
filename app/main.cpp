#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <cmath>
#include <cstdlib>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool g_mouseWasPressed = false;

int main() {
    glfwInit();
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
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
void ChangeWindow(GLFWwindow *window, int xOff, int yOff) {
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetWindowSize(window, width + xOff, height + yOff);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    bool isCtrlPressed = (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
                          glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);
    bool isShiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                           glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);


    bool isLeftMouseButtonPressed = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT));
    bool isLeftArrowPressed = (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    bool isRightArrowPressed = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
    bool isUpArrowPressed = (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
    bool isDownArrowPressed = (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);

    if (isCtrlPressed && isLeftArrowPressed) {
        ChangeWindow(window, -1, 0);
    } else if (isCtrlPressed && isRightArrowPressed) {
        ChangeWindow(window, 1, 0);
    } else if (isCtrlPressed && isDownArrowPressed) {
        ChangeWindow(window, 0, 1);
    } else if (isCtrlPressed && isUpArrowPressed) {
        ChangeWindow(window, 0, -1);
    }

    if (isLeftMouseButtonPressed) {
        if (isShiftPressed) {
            double xpos;
            double ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (!g_mouseWasPressed) {
                int width;
                int height;
                glfwGetWindowSize(window, &width, &height);
                glClearColor(xpos / width, (height - ypos) / height, 0, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
            }
        } else if (!g_mouseWasPressed) {
            float red;
            float green;
            float blue;
            red = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            green = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            blue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            glClearColor(red, green, blue, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        g_mouseWasPressed = true;
    } else {
        g_mouseWasPressed = false;
    }

    bool isSpacePressed = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);

    if (isSpacePressed && !g_mouseWasPressed) { // Možeš preimenovati promenljivu u g_buttonWasPressed
        float red = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float green = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float blue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        g_mouseWasPressed = true; 
    }
   

        
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}