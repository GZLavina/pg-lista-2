#include <iostream>
#include <string>
#include <glad/glad.h>
#include "shader.h"
#include <GLFW/glfw3.h>
#include <numbers>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void error_callback(int error, const char *msg);

GLuint basicTriangle();

void drawBasicTriangle(Shader *shader);

GLuint ex8();

void drawEx8();

const unsigned int SCREEN_WIDTH = 600;
const unsigned int SCREEN_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("../shaders/HelloTriangle.vert", "../shaders/HelloTriangle.frag");
//    //Shader para triagulo colorido
//    Shader shader("../shaders/HelloTriangle.vert", "../shaders/ColoredTriangle.frag");

    // dois triangulos com borda e vertice
    GLuint VAO = basicTriangle();

//    // Triangulo colorido
//    GLuint VAO = ex8();

    shader.use();

    // Tamanho padrao (utilizar para exercicios 4 e 5)
    glm::mat4 projection = glm::ortho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
//    // Exercicio 1
//    glm::mat4 projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,-1.0f,1.0f);
//    // Exercicio 2
//    glm::mat4 projection = glm::ortho(0.0f,800.0f,0.0f,600.0f,-1.0f,1.0f);
    shader.setMat4("projection", glm::value_ptr(projection));
    // render loop
    while(!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
//        // Exercicios 1, 2 e 3
//        glViewport(0, 0, width, height);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        // Exercicios 4 e 5
        glViewport(0, 0, width/2, height/2);
        drawBasicTriangle(&shader);
        glViewport(0, height/2, width/2, height/2);
        drawBasicTriangle(&shader);
        glViewport(width/2, 0, width/2, height/2);
        drawBasicTriangle(&shader);
        glViewport(width/2, height/2, width/2, height/2);
        drawBasicTriangle(&shader);

        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void error_callback(int error, const char *msg) {
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

GLuint basicTriangle() {
    GLfloat vertices[] = {
            // Triangle 1
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.0f,  0.0f, 0.0f,
            // Triangle 2
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.0f, 0.0f, 0.0f
    };

    GLuint VBO, VAO;
    //Geração do identificador do VBO
    glGenBuffers(1, &VBO);
    //Faz a conexão (vincula) do buffer como um buffer de array
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Envia os dados do array de floats para o buffer da OpenGl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Geração do identificador do VAO (Vertex Array Object)
    glGenVertexArrays(1, &VAO);
    // Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
    // e os ponteiros para os atributos
    glBindVertexArray(VAO);
    // Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando:
    // Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
    // Numero de valores que o atributo tem (por ex, 3 coordenadas xyz)
    // Tipo do dado
    // Se está normalizado (entre zero e um)
    // Tamanho em bytes
    // Deslocamento a partir do byte zero
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    // Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice
    // atualmente vinculado - para que depois possamos desvincular com segurança
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
    glBindVertexArray(0);

    return VAO;
}

void drawBasicTriangle(Shader *shader) {
    glLineWidth(10);
    glPointSize(20);

    // Triangulos preenchidos
    shader->setVec4("inputColor", 0.0f, 0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 3, 3);

    // Contornos
    shader->setVec4("inputColor", 0.0f, 1.0f, 0.0f, 1.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glDrawArrays(GL_LINE_LOOP, 3, 3);

    // Pontos
    shader->setVec4("inputColor", 1.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_POINTS, 0, 6);
}

GLuint ex8() {
    GLfloat vertices[] = {
            // positions        // colors
            0.6f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.6f, 0.0f,  1.0f, 0.0f, 0.0f   // top
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    return VAO;
}

void drawEx8() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
