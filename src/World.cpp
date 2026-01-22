/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:29 by capi              #+#    #+#             */
/*   Updated: 2026/01/22 18:22:18 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "World.hpp"

World::World(Camera& camera)
: _camera(camera), _renderDirstance(2) {}

World::~World(void)
{
	for (auto it = this->_chunkMap.begin(); it != this->_chunkMap.end(); it++)
	{
		for (auto chunk = it->second.begin(); chunk != it->second.end(); chunk++)
		{
			delete chunk->second;
		}
	}
}

void	World::update(float delta_time)
{
	(void)delta_time;
	this->_camera.update_vector();

	glm::vec3& cam_pos = this->_camera.getPos();
	
	glm::vec3 chunk_pos = Utils::getChunkPos(cam_pos);

	// * RENDER CHUNK (CIRCLE RENDERING)
	/*
		For render distance of 2:
		6 7 8
		4 0 5
		1 2 3
	*/
	for (size_t circle = 0; circle <= (size_t)this->_renderDirstance; circle++)
	{
		for (size_t z = 0; z < 1 + 2 * circle; z++)
		{
			for (size_t x = 0; x < 1 + 2 * circle; )
			{
				glm::vec3 generate_chunk_pos = glm::vec3(
					chunk_pos.x - (circle * CHUNK_SIZE) + (x * CHUNK_SIZE),
					0.0,
					chunk_pos.z - (circle * CHUNK_SIZE) + (z * CHUNK_SIZE)
				);

				if (this->_chunkMap.find(generate_chunk_pos.z) == this->_chunkMap.end())
				{
					this->_chunkMap.insert(std::pair<int, std::map<int, Chunk*> >(generate_chunk_pos.z, std::map<int, Chunk*>()));
					this->_chunkMap.at(generate_chunk_pos.z).insert(std::pair<int, Chunk*>(generate_chunk_pos.x, new Chunk(this, generate_chunk_pos)));
					this->_chunkMap.at(generate_chunk_pos.z).at(generate_chunk_pos.x)->generate();
				}
				else if (this->_chunkMap.at(generate_chunk_pos.z).find(generate_chunk_pos.x) == this->_chunkMap.at(generate_chunk_pos.z).end()) 
				{
					this->_chunkMap.at(generate_chunk_pos.z).insert(std::pair<int, Chunk*>(generate_chunk_pos.x, new Chunk(this, generate_chunk_pos)));
					this->_chunkMap.at(generate_chunk_pos.z).at(generate_chunk_pos.x)->generate();
				}
				if (z != 0 && z != (1 + 2 * circle - 1))
					x += (circle * 2);
				else
					x += 1;
			}
		}
	}
}