#include "mesh.h"
#include <GL/glew.h>

namespace btoleda {
	void mesh::_setup_mesh()
	{
		glGenVertexArrays(1, &_m_VAO);
		glGenBuffers(1, &_m_VBO);
		glGenBuffers(1, &_m_EBO);

		glBindVertexArray(_m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _m_VBO);

		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), &m_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tex_coords));

		glBindVertexArray(0);
	}

	void mesh::draw(shader_program &sp)
	{
		sp.use();
		unsigned int diffuse_nr = 1;
		unsigned int specular_nr = 1;

		for (unsigned int i = 0; i < m_textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string number;
			std::string name = "";
			if (m_textures[i].type == texture_type::DIFFUSE)
			{
				number = std::to_string(diffuse_nr++);
				name = "texture_diffuse" + number;
			}
			else if (m_textures[i].type == texture_type::SPECULAR)
			{
				number = std::to_string(specular_nr++);
				name = "texture_specular" + number;
			}

			glUniform1i(glGetUniformLocation(sp.program_id(), name.c_str()), i);
			glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(_m_VAO);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
} // namepsace btoleda