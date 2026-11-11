#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <cmath>
#include <cstdlib>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void crtaj();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


const char* VertexShaderSource = R"S(
#version 330 core

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
} 

)S";

const char* FragmentShaderSource = R"S(
#version 330 core

out vec4 FragColor;
uniform vec4 ourColor;
void main(){
    FragColor = ourColor;
}
)S";
unsigned shaderProgram;
int curr=0;

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



    unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertexShaderSource, nullptr);
    glCompileShader(vertexShader); 

    int success = 0;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    success = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }



    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);




    float vertices[] = {
    // trougao
    -0.5f,  -0.5f,  0.0f, // 0 
     0.5f,  -0.5f,  0.0f, // 1 
     0.0f,   0.5f,  0.0f, // 2 

    // cetvorougao
    -0.5f,   0.5f,  0.0f, // 3 
     0.5f,   0.5f,  0.0f, // 4 

    // petougao
    -0.48f,  0.15f, 0.0f, // 5 
    -0.29f, -0.4f,  0.0f, // 6 
     0.29f, -0.4f,  0.0f, // 7 
     0.48f,  0.15f, 0.0f, // 8 

    // sestougao
    -0.43f,  0.25f, 0.0f, // 9 
    -0.43f, -0.25f, 0.0f, // 10 
     0.0f,  -0.5f,  0.0f, // 11 
     0.43f, -0.25f, 0.0f, // 12 
     0.43f,  0.25f, 0.0f, // 13 

    // sedmougao
    -0.39f,  0.31f, 0.0f, // 14 
    -0.49f, -0.11f, 0.0f, // 15 
    -0.22f, -0.45f, 0.0f, // 16 
     0.22f, -0.45f, 0.0f, // 17 
     0.49f, -0.11f, 0.0f, // 18 
     0.39f,  0.31f, 0.0f,  // 19 

     // osmougao
    -0.35f,  0.35f, 0.0f, // 20 
    -0.5f,   0.0f,  0.0f, // 21 
    -0.35f, -0.35f, 0.0f, // 22 
     0.35f, -0.35f, 0.0f, // 23 
     0.5f,   0.0f,  0.0f, // 24 
     0.35f,  0.35f, 0.0f, // 25 

    // devetougao
    -0.32f,  0.38f, 0.0f, // 26 
    -0.49f,  0.09f, 0.0f, // 27 
    -0.17f, -0.47f, 0.0f, // 28 
     0.17f, -0.47f, 0.0f, // 29 
     0.49f,  0.09f, 0.0f, // 30 
     0.32f,  0.38f, 0.0f  // 31 
};


    unsigned indices[] = {
    // trougao
    0, 1, 2,

    // cetvorougao
    0, 1, 3,
    1, 3, 4,

    // petougao
    2, 5, 6,
    2, 6, 7,
    2, 7, 8,

    // sestougao
    2,  9, 10,
    2, 10, 11,
    2, 11, 12,
    2, 12, 13,

    // sedmougao
    2, 14, 15,
    2, 15, 16,
    2, 16, 17,
    2, 17, 18,
    2, 18, 19,

    // osmougao
    2, 20, 21,
    2, 21, 22,
    2, 22, 11,
    2, 11, 23,
    2, 23, 24,
    2, 24, 25,




    // devetougao
    2, 26, 27,
    2, 27, 10, 
    2, 10, 28, 
    2, 28, 29,
    2, 29, 12, 
    2, 12, 30, 
    2, 30, 31
};



    unsigned int VBO; //Vertex Buffer Object
    unsigned int VAO; //Vertex Array Object 
    unsigned int EBO; //Element Buffer Object

    


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        crtaj();
        glfwSwapBuffers(window);
        
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        
        if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            curr=1;
        }
        else if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
           curr=2;
        }
        else if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            curr=3;
        }
        else if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
            curr=4;
        }
        else if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
            curr=5;
        }
        else if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
            curr=6;
        }
        else if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
            curr=7;
        }
    }
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void crtaj(){
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    if(curr == 1){
        glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }
    else if(curr == 2){
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
    }
    else if(curr == 3){
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)(9 * sizeof(unsigned int)));
    }
    else if(curr == 4){
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));
    }
    else if(curr == 5){
        glUniform4f(vertexColorLocation, 1.0f, 0.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));
    }
    else if(curr == 6){
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(45 * sizeof(unsigned int)));
    }
    else if(curr == 7){
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, (void*)(63 * sizeof(unsigned int)));
    }
}