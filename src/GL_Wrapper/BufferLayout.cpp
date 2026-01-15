/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BufferLayout.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:27:07 by capi              #+#    #+#             */
/*   Updated: 2026/01/15 22:05:45 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GL_Wrapper/BufferLayout.hpp"

using namespace GL_Wrapper;

BufferLayout::BufferLayout(void): _stride(0) {}

BufferLayout::~BufferLayout(void) {}

void	BufferLayout::addLayout(const Layout& layout)
{
	this->_layouts.push_back(layout);
	this->_stride += GetTypeSize(layout.type) * layout.count;
}

const std::vector<Layout>&	BufferLayout::getLayout(void) const
{
	return (this->_layouts);
}

size_t	BufferLayout::getStride(void) const
{
	return (this->_stride);
}