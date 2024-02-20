#pragma once
#include <string>
#include <GL/glew.h>

namespace btoleda
{
    class shader_program
    {
        public:
        /**
         * Immediately tries to compile the vertex and fragment shaders.
         * May throw a std::runtime_error if the shaders fail to compile.
        */
        shader_program(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename);
        ~shader_program() = default;
        void use() const;

        private:
        GLuint _compile(const std::string& vertex_shader, const std::string& fragment_shader) const;
        GLuint _m_program_id;
    };
} // namespace btoleda
