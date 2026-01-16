/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture2DArray.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:05:16 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 22:26:33 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GL_Wrapper/Texture2DArray.hpp"

using namespace GL_Wrapper;

Texture2DArray::Texture2DArray(unsigned int tile_width, unsigned int tile_height, unsigned int image_count, GLenum format)
: _tileWidth(tile_height), _tileHeight(tile_height), _maxImageCount(image_count), _imageCount(0)
{
	this->_id = 0;
	try
	{

		GLCallThrow(glGenTextures(1, &this->_id));
		this->bind();
		// Default config for Texture
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCallThrow(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLCallThrow(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, 
			tile_width, tile_height, image_count, 0,
			format, GL_UNSIGNED_BYTE, nullptr));

		this->unbind();
	}
	catch(const std::exception& e)
	{
		if (this->_id > 0)
			glDeleteTextures(1, &this->_id);
		throw;
	}
}

Texture2DArray::~Texture2DArray(void)
{
	glDeleteTextures(1, &this->_id);
}

void	Texture2DArray::addTexture(const char *filename, GLenum format, bool flip_on_load)
{
	if (this->_imageCount >= this->_maxImageCount)
		throw std::runtime_error("You cannot add the image to the texture array, texture array is full.");
	unsigned char	*data = NULL;
	try
	{
		int width, height, nr_channel;
		stbi_set_flip_vertically_on_load(flip_on_load);
		data = stbi_load(filename, &width, &height, &nr_channel, 0);
		if (!data)
		{
			std::string error_msg = "Cannot load image : " + std::string(filename);
			throw std::runtime_error(error_msg);
		}
		stbi_set_flip_vertically_on_load(false);

		this->bind();
		
    	GLCallThrow(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
    	    0, 0, this->_imageCount,
			this->_tileWidth, this->_tileHeight, 1,
			format, GL_UNSIGNED_BYTE, data
		));

		this->_imageCount += 1;

		this->unbind();

		stbi_image_free(data);
	}
	catch(const std::exception& e)
	{
		stbi_image_free(data);
		throw;
	}
	
}

void	Texture2DArray::bind(void) const
{
	GLCallThrow(glBindTexture(GL_TEXTURE_2D_ARRAY, this->_id));
}

void	Texture2DArray::unbind(void) const
{
	GLCallThrow(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
}

void	Texture2DArray::use(unsigned int index) const
{
	GLCallThrow(glActiveTexture(GL_TEXTURE0 + index));
	this->bind();
}