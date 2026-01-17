/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/17 22:34:13 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunk.hpp"

Chunk::Chunk(const glm::vec3& worldPos)
: _worldPos(worldPos)
{}

Chunk::~Chunk(void) {}

void	Chunk::generate(void)
{
	for (size_t depth = 0; depth < CHUNK_SIZE; depth++)
	{
		for (size_t row = 0; row < CHUNK_SIZE; row++)
		{
			for (size_t col = 0; col < CHUNK_SIZE; col++)
			{
				this->_blocks[depth][row][col] = new Block(
					GRASS_BLOCK,
					glm::vec3(this->_worldPos.x + col, this->_worldPos.y + row, this->_worldPos.z + depth),
					{ GRASS_BLOCK_SIDE, GRASS_BLOCK_SIDE, GRASS_BLOCK_SIDE, GRASS_BLOCK_SIDE, GRASS_BLOCK_TOP, DIRT }
				);
			}
		}
	}
}

void	Chunk::draw(GL_Wrapper::Shader& shader)
{
	size_t block_draw = 0;
	for (size_t depth = 0; depth < CHUNK_SIZE; depth++)
	{
		for (size_t row = 0; row < CHUNK_SIZE; row++)
		{
			for (size_t col = 0; col < CHUNK_SIZE; col++)
			{
				if (
					depth == 0 || depth == CHUNK_SIZE - 1 || row == 0 || row == CHUNK_SIZE - 1 || col == 0 || col == CHUNK_SIZE - 1
					|| this->_blocks[depth - 1][row][col]->getBlockId() == AIR || this->_blocks[depth + 1][row][col]->getBlockId() == AIR
					|| this->_blocks[depth][row - 1][col]->getBlockId() == AIR || this->_blocks[depth][row + 1][col]->getBlockId() == AIR
					|| this->_blocks[depth][row][col - 1]->getBlockId() == AIR || this->_blocks[depth][row][col + 1]->getBlockId() == AIR
				)
				{
					this->_blocks[depth][row][col]->draw(shader);
					block_draw++;
				}
			}
		}
	}
	std::cout << "Block drawed: " << block_draw << std::endl;
}