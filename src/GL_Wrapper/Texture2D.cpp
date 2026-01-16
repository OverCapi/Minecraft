/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture2D.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:03:02 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 15:24:39 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GL_Wrapper/Texture2D.hpp"

using namespace GL_Wrapper;

Texture2D::Texture2D(const char *texture_file, GLenum format, bool flip_on_load)
{
	this->_id = 0;
	unsigned char	*data = NULL;
	try
	{
		int width, height, nr_channel;
		stbi_set_flip_vertically_on_load(flip_on_load);
		data = stbi_load(texture_file, &width, &height, &nr_channel, 0);
		if (!data)
		{
			std::string error_msg = "Cannot load image : " + std::string(texture_file);
			throw std::runtime_error(error_msg);
		}
		stbi_set_flip_vertically_on_load(false);

		GLCallThrow(glGenTextures(1, &this->_id));
		this->bind();
		// Default config for Texture
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		
		GLCallThrow(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data));
		GLCallThrow(glGenerateMipmap(GL_TEXTURE_2D));
		this->unbind();
		stbi_image_free(data);
	}
	catch(const std::exception& e)
	{
		stbi_image_free(data);
		if (this->_id > 0)
			glDeleteTextures(1, &this->_id);
		throw;
	}
}

Texture2D::~Texture2D(void)
{
	glDeleteTextures(1, &this->_id);
}

void	Texture2D::bind(void) const
{
	GLCallThrow(glBindTexture(GL_TEXTURE_2D, this->_id));
}

void	Texture2D::unbind(void) const
{
	GLCallThrow(glBindTexture(GL_TEXTURE_2D, 0));
}

void	Texture2D::use(unsigned int index) const
{
	GLCallThrow(glActiveTexture(GL_TEXTURE0 + index));
	this->bind();
}