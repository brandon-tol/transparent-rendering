#include "shader_program.h"
#include <fstream>
#include <sstream>

namespace btoleda
{
    shader_program::shader_program(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename)
    {
        std::string vertex_shader;
        std::string fragment_shader;

        std::ifstream vertex_shader_file(vertex_shader_filename);
        std::ifstream fragment_shader_file(fragment_shader_filename);

        if (!vertex_shader_file.is_open())
        {
            printf("Failed to open vertex shader file: %s\n", vertex_shader_filename.c_str());
            return;
        }

        if (!fragment_shader_file.is_open())
        {
            printf("Failed to open fragment shader file: %s\n", fragment_shader_filename.c_str());
            return;
        }

        std::string line;
        while (std::getline(vertex_shader_file, line))
        {
            vertex_shader += line + "\n";
        }

        while (std::getline(fragment_shader_file, line))
        {
            fragment_shader += line + "\n";
        }

        _m_program_id = _compile(vertex_shader, fragment_shader);
    }
        

    GLuint shader_program::_compile(const std::string& vertex_shader, const std::string& fragment_shader) const
    {
        GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
        const char* vertex_shader_cstr = vertex_shader.c_str();
        glShaderSource(vertex_shader_id, 1, &vertex_shader_cstr, nullptr);
        glCompileShader(vertex_shader_id);

        GLint success;
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar info_log[512];
            glGetShaderInfoLog(vertex_shader_id, 512, nullptr, info_log);
            std::stringstream ss;
            ss << "Vertex shader compilation failed: " << info_log;
            throw std::runtime_error(ss.str());
        }

        GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragment_shader_cstr = fragment_shader.c_str();
        glShaderSource(fragment_shader_id, 1, &fragment_shader_cstr, nullptr);
        glCompileShader(fragment_shader_id);

        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar info_log[512];
            glGetShaderInfoLog(fragment_shader_id, 512, nullptr, info_log);
            std::stringstream ss;
            ss << "Fragment shader compilation failed: " << info_log;
            throw std::runtime_error(ss.str());
        }

        GLuint program_id = glCreateProgram();
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
        glLinkProgram(program_id);

        glGetProgramiv(program_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar info_log[512];
            glGetProgramInfoLog(program_id, 512, nullptr, info_log);
            std::stringstream ss;
            ss << "Shader program linking failed: " << info_log;
            throw std::runtime_error(ss.str());
        }

        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);

        return program_id;
    }

    void shader_program::use() const
    {
        glUseProgram(_m_program_id);
    }
} // namespace btoleda
