#define GLEW_STATIC 1

#define BTOLEDA_WIDTH 800
#define BTOLEDA_HEIGHT 600

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <shader_program.h>

#include <iostream>
#include <memory>

#define BTOLEDA_DEBUG_GL(x)\
    x;\
    {\
        GLenum glError = glGetError();\
        if(glError != GL_NO_ERROR)\
        {\
            printf("glError: %d at line %d\n", glError, __LINE__);\
        }\
    }

#define BTOLEDA_FILE_PATH(x) FILE_ROOT x

int main(int argc, char** argv)
{
    using namespace btoleda;

    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    auto window = glfwCreateWindow(BTOLEDA_WIDTH, BTOLEDA_HEIGHT, "Depth Peeling", nullptr, nullptr);

    if (!window)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    auto resize_viewport = [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    };

    resize_viewport(window, BTOLEDA_WIDTH, BTOLEDA_HEIGHT);
    glfwSetFramebufferSizeCallback(window, resize_viewport);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    shader_program program(BTOLEDA_FILE_PATH("/assets/shaders/vertex_shader.glsl"), BTOLEDA_FILE_PATH("/assets/shaders/fragment_shader.glsl"));

    BTOLEDA_DEBUG_GL();

    GLuint VAO, VBO, EBO;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    program.use();
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}