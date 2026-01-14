/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexArray.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:07:23 by capi              #+#    #+#             */
/*   Updated: 2026/01/12 17:53:18 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GL_Wrapper/VertexArray.hpp"

using namespace GL_Wrapper;

VertexArray::VertexArray(void)
{
	GLCallThrow(glGenVertexArrays(1, &this->_id));
}

VertexArray::~VertexArray(void)
{
	glDeleteVertexArrays(1, &this->_id);
}

void	VertexArray::bind(void) const
{
	GLCallThrow(glBindVertexArray(this->_id));
}

void	VertexArray::unbind(void) const
{
	GLCallThrow(glBindVertexArray(0));
}

void	VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer, BufferLayout& bufferLayout)
{
	this->bind();
	vertexBuffer.bind();
	const std::vector<Layout> layouts = bufferLayout.getLayout();
	size_t offset = 0;
	for (size_t i = 0; i < layouts.size(); i++)
	{
		Layout	layout = layouts[i];
		GLCallThrow(glEnableVertexAttribArray(i));
		GLCallThrow(glVertexAttribPointer(
			i,
			layout.count,
			layout.type,
			layout.normalized,
			bufferLayout.getStride(),
			(const void *)offset
		));
		offset += GetTypeSize(layout.type) * layout.count;
	}
	this->bind();
	vertexBuffer.bind();
}

void	VertexArray::AddElementBuffer(const ElementBuffer& elementBuffer)
{
	this->bind();
	elementBuffer.bind();
	this->bind();
	elementBuffer.bind();
}
