/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:41:57 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 23:09:47 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Block.hpp"

const float Block::vertices[] = {
	// Position				// TexCoord
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
	1.0f, -1.0f, -1.0f,		1.0f, 0.0f,
	1.0f,  1.0f, -1.0f,		1.0f, 1.0f,
	1.0f,  1.0f, -1.0f,		1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f,	0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,

	-1.0f, -1.0f, 1.0f, 	0.0f, 0.0f,
	 1.0f, -1.0f, 1.0f,		1.0f, 0.0f,
	 1.0f,  1.0f, 1.0f, 	1.0f, 1.0f,
	 1.0f,  1.0f, 1.0f,		1.0f, 1.0f,
	-1.0f,  1.0f, 1.0f, 	0.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,

	-1.0f,  1.0f,  1.0f, 	1.0f, 0.0f,
	-1.0f,  1.0f, -1.0f, 	1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 	0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 	0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 	0.0f, 0.0f,
	-1.0f,  1.0f,  1.0f, 	1.0f, 0.0f,

	1.0f,  1.0f,  1.0f,		1.0f, 0.0f,
	1.0f,  1.0f, -1.0f,		1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 1.0f,
	1.0f, -1.0f, -1.0f,		0.0f, 1.0f,
	1.0f, -1.0f,  1.0f,		0.0f, 0.0f,
	1.0f,  1.0f,  1.0f,		1.0f, 0.0f,

	-1.0f, -1.0f, -1.0f,	0.0f, 1.0f,
	 1.0f, -1.0f, -1.0f,	1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,
	 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,
	-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,	0.0f, 1.0f,

	-1.0f, 1.0f, -1.0f, 	0.0f, 1.0f,
	 1.0f, 1.0f, -1.0f, 	1.0f, 1.0f,
	 1.0f, 1.0f,  1.0f,		1.0f, 0.0f,
	 1.0f, 1.0f,  1.0f, 	1.0f, 0.0f,
	-1.0f, 1.0f,  1.0f,		0.0f, 0.0f,
	-1.0f, 1.0f, -1.0f,		0.0f, 1.0f
};

Block::Block(BlockType	type, const glm::vec3& worldPos, const std::array<TextureId, 6>& face_texture)
: _type(type), _worldPos(worldPos), _textureIdFace(face_texture)
{
	(void)this->_type;
}

Block::~Block(void) {}

# include <iostream>

std::array<BlockVertex, 36>&	Block::getVerticesData(void)
{	
	for (size_t i = 0; i < this->_block_vertices.size(); i++)
	{
		this->_block_vertices.at(i) = BlockVertex {
			.vPos = { Block::vertices[i * 5 + 0], Block::vertices[i * 5 + 1], Block::vertices[i * 5 + 2]},
			.texCoord = { Block::vertices[i * 5 + 3], Block::vertices[i * 5 + 4] },
			.world_pos = { this->_worldPos.x, this->_worldPos.y, this->_worldPos.z },
			.TextureId = this->_textureIdFace.at((i * 5 / 30))
		};
	}
	return (this->_block_vertices);
}