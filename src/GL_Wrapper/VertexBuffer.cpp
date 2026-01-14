/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuffer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:13:00 by capi              #+#    #+#             */
/*   Updated: 2026/01/12 17:53:11 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GL_Wrapper/VertexBuffer.hpp"

using namespace GL_Wrapper;

VertexBuffer::VertexBuffer(const void *data, size_t size)
{
	GLCallThrow(glGenBuffers(1, &this->_id));
	try {
		GLCallThrow(glBindBuffer(GL_ARRAY_BUFFER, this->_id));
		GLCallThrow(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	} catch (...) {
		glDeleteBuffers(1, &this->_id);
		throw;
	}
}

VertexBuffer::~VertexBuffer(void)
{
	glDeleteBuffers(1, &this->_id);
}

void	VertexBuffer::bind(void) const
{
	GLCallThrow(glBindBuffer(GL_ARRAY_BUFFER, this->_id));
}

void	VertexBuffer::unbind(void) const
{
	GLCallThrow(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
