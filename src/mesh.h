#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "shader_program.h"

namespace btoleda {
	struct vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coords;
	};

	enum texture_type
	{
		NONE = 0,
		DIFFUSE,
		SPECULAR,
	};

	struct texture
	{
		unsigned int id;
		texture_type type;
	};

	class mesh
	{
		public:
			std::vector<vertex> m_vertices;
			std::vector<unsigned int> m_indices;
			std::vector<texture> m_textures;

			inline mesh(std::vector<vertex> vertices,
				std::vector<unsigned int> indices,
				std::vector<texture> textures) : m_vertices(vertices), m_indices(indices), m_textures(textures)
			{
				_setup_mesh();
			}
			void draw(shader_program& shader);

		private:
			unsigned int _m_VAO, _m_VBO, _m_EBO;
			void _setup_mesh();

	};
} // namespace btoleda

