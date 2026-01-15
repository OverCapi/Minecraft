/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:41:57 by capi              #+#    #+#             */
/*   Updated: 2026/01/15 23:29:17 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Block.hpp"

const float Block::vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,	
		 0.5f,  0.5f, 0.5f,
		 0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f,
		 0.5f, 0.5f, -0.5f,
		 0.5f, 0.5f,  0.5f,
		 0.5f, 0.5f,  0.5f,
		-0.5f, 0.5f,  0.5f,
		-0.5f, 0.5f, -0.5f
};

Block::Block(BlockType type, glm::vec3 worldPos): _type(type), _worldPos(worldPos)
{
}

Block::~Block(void) {}

std::array<BlockVertex, 36>&	Block::getVerticesData(void)
{
	(void)this->_type;
	for (size_t i = 0; i < this->_block_vertices.size(); i++)
	{
		this->_block_vertices.at(i) = BlockVertex {
			.vPos = { Block::vertices[i * 3 + 0], Block::vertices[i * 3 + 1], Block::vertices[i * 3 + 2]},
			.world_pos = { this->_worldPos.x, this->_worldPos.y, this->_worldPos.z }
		};
	}
	return (this->_block_vertices);
}