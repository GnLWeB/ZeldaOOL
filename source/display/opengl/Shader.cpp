/*
 * =====================================================================================
 *
 *       Filename:  Shader.cpp
 *
 *    Description:
 *
 *        Created:  20/09/2014 14:42:45
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

#include "Exception.hpp"
#include "Shader.hpp"

Shader *Shader::currentShader = nullptr;

Shader::Shader(Shader &&shader) {
	m_vertexShader = shader.m_vertexShader;
	m_fragmentShader = shader.m_fragmentShader;
	m_program = shader.m_program;

	shader.m_vertexShader = 0;
	shader.m_fragmentShader = 0;
	shader.m_program = 0;
}

Shader::Shader(const std::string &vertexFilename, const std::string &fragmentFilename) {
	loadFromFile(vertexFilename, fragmentFilename);
}

Shader::~Shader() {
	if(m_vertexShader) glDeleteShader(m_vertexShader);
	if(m_fragmentShader) glDeleteShader(m_fragmentShader);
	if(m_program) glDeleteProgram(m_program);
}

void Shader::loadFromFile(const std::string &vertexFilename, const std::string &fragmentFilename) {
	compileShader(GL_VERTEX_SHADER, m_vertexShader, vertexFilename);
	compileShader(GL_FRAGMENT_SHADER, m_fragmentShader, fragmentFilename);

	m_program = glCreateProgram();

	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);

	glLinkProgram(m_program);

	GLint linkOK = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkOK);
	if(!linkOK){
		GLint errorSize = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &errorSize);

		char *errorMsg = new char[errorSize + 1];

		glGetProgramInfoLog(m_program, errorSize, &errorSize, errorMsg);
		errorMsg[errorSize] = '\0';

		std::string error = std::string(errorMsg);

		delete[] errorMsg;
		glDeleteProgram(m_program);

		throw EXCEPTION("Program", m_program, "link failed:", error);
	}
}

void Shader::compileShader(GLenum type, GLuint &shader, const std::string &filename) {
	shader = glCreateShader(type);

	std::ifstream file(filename);
	if(!file) {
		glDeleteShader(type);

		throw EXCEPTION("Failed to open", filename);
	}

	std::string line;
	std::string sourceCode;

	while(getline(file, line)) sourceCode += line + '\n';
	file.close();

	const GLchar *sourceCodeString = sourceCode.c_str();

	glShaderSource(shader, 1, &sourceCodeString, nullptr);

	glCompileShader(shader);

	GLint compileOK = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOK);
	if(!compileOK) {
		GLint errorSize = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);

		char *errorMsg = new char[errorSize + 1];

		glGetShaderInfoLog(shader, errorSize, &errorSize, errorMsg);
		errorMsg[errorSize] = '\0';

		std::string error = std::string(errorMsg);

		delete[] errorMsg;
		glDeleteShader(shader);

		throw EXCEPTION("Shader", filename, "compilation failed:", error);
	}
}

GLint Shader::attrib(const std::string &name) {
	GLint attrib = glGetAttribLocation(m_program, name.c_str());
	if(attrib == -1) DEBUG("Could not bind attribute:", name);

	return attrib;
}

GLint Shader::uniform(const std::string &name) {
	GLint uniform = glGetUniformLocation(m_program, name.c_str());
	if(uniform == -1) DEBUG("Could not bind uniform:", name);

	return uniform;
}

void Shader::enableVertexAttribArray(const std::string &name) {
	glEnableVertexAttribArray(attrib(name));
}

void Shader::disableVertexAttribArray(const std::string &name) {
	glDisableVertexAttribArray(attrib(name));
}

void Shader::setUniform(const std::string &name, int n) {
	glUniform1i(uniform(name), n);
}

void Shader::setUniform(const std::string &name, float d, float e) {
	glUniform2f(uniform(name), d, e);
}

void Shader::setUniform(const std::string &name, const glm::mat4 &matrix) {
	glUniformMatrix4fv(uniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::bind(const Shader *shader) {
	currentShader = (Shader*)shader;
	glUseProgram((shader) ? shader->m_program : 0);
}

