

#define BTOLEDA_WIDTH 800
#define BTOLEDA_HEIGHT 600

#define GLEW_STATIC 1
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <shader_program.h>
#include <mesh.h>

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

    std::vector<vertex> vertices {
        { glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ -0.5f, -0.5f } },
		{ glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.5f, -0.5f }  },
        { glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec2{ 0.0f, -0.5f }  }
    };

    std::vector<unsigned int> indices {
        0, 1, 2
    };

    mesh m{ vertices, indices, std::vector<texture>{0} };
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m.draw(program);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}