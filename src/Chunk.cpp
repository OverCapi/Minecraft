/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/17 18:03:45 by capi             ###   ########.fr       */
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
	for (size_t depth = 0; depth < CHUNK_SIZE; depth++)
	{
		for (size_t row = 0; row < CHUNK_SIZE; row++)
		{
			for (size_t col = 0; col < CHUNK_SIZE; col++)
			{
				this->_blocks[depth][row][col]->draw(shader);
			}
		}
	}
}