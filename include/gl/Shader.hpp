/*
 * =====================================================================================
 *
 *       Filename:  Shader.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/09/2014 14:42:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>

#include <glm/glm.hpp>

#include "OpenGL.hpp"

class Shader {
	public:
		Shader();
		Shader(const char *vertexFilename, const char *fragementFilename);
		~Shader();
		
		void loadFromFile(const char *vertexFilename, const char *fragementFilename);
		
		void compileShader(GLenum type, GLuint &shader, const char *filename);
		
		GLint attrib(std::string name);
		GLint uniform(std::string name);
		
		void enableVertexAttribArray(std::string name);
		void disableVertexAttribArray(std::string name);
		
		void setUniform(std::string name, int n);
		void setUniform(std::string name, float d, float e);
		void setUniform(std::string name, const glm::mat4 &matrix);
		
		static void bind(const Shader *shader);
		static Shader *currentShader;
		
		GLint program() const { return m_program; }
		
	private:
		GLuint m_vertexShader;
		GLuint m_fragmentShader;
		GLuint m_program;
};

#endif // SHADER_HPP_
