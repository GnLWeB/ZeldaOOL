/*
 * =====================================================================================
 *
 *       Filename:  VertexBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/12/2014 13:57:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &m_id);
}

VertexBuffer::VertexBuffer(VertexBuffer &&vertexBuffer) {
	m_id = vertexBuffer.m_id;
	vertexBuffer.m_id = 0;
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::setData(GLsizeiptr size, const GLvoid *data, GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::updateData(GLintptr offset, GLsizeiptr size, const GLvoid *data) {
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::bind(const VertexBuffer *vertexBuffer) {
	if(vertexBuffer) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->m_id);
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

