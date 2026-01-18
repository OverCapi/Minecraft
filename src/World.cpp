/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:29 by capi              #+#    #+#             */
/*   Updated: 2026/01/18 14:21:38 by capi             ###   ########.fr       */
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
	
	glm::vec3 chunk_pos = glm::vec3(
		(int)(cam_pos.x / CHUNK_SIZE),
		(int)(cam_pos.y / CHUNK_SIZE),
		(int)(cam_pos.z / CHUNK_SIZE)
	);
	// * RENDER CHUNK (CIRCLE RENDERING)
	/*
		For render distance of 2:

		1 2 3
		4 0 5
		6 7 8
	*/
	size_t new_chunk = 0;
	for (size_t circle = 0; circle < (size_t)this->_renderDirstance; circle++)
	{
		for (size_t z = 0; z < 1 + 2 * circle; z++)
		{
			for (size_t x = 0; x < 1 + 2 * circle; )
			{
				glm::vec3 render_chunk_pos = glm::vec3(
					chunk_pos.x - (circle * CHUNK_SIZE) + (x * CHUNK_SIZE),
					chunk_pos.y,
					chunk_pos.z - (circle * CHUNK_SIZE) + (z * CHUNK_SIZE)
				);

				if (this->_chunkMap.find(render_chunk_pos.x) == this->_chunkMap.end())
				{
					this->_chunkMap.insert(std::pair<int, std::map<int, Chunk*> >(render_chunk_pos.x, std::map<int, Chunk*>()));
					this->_chunkMap.at(render_chunk_pos.x).insert(std::pair<int, Chunk*>(render_chunk_pos.z, new Chunk(render_chunk_pos)));
					this->_chunkMap.at(render_chunk_pos.x).at(render_chunk_pos.z)->generate();
					new_chunk++;
				} 
				else if (this->_chunkMap.at(render_chunk_pos.x).find(render_chunk_pos.z) == this->_chunkMap.at(render_chunk_pos.x).end()) 
				{
					this->_chunkMap.at(render_chunk_pos.x).insert(std::pair<int, Chunk*>(render_chunk_pos.z, new Chunk(render_chunk_pos * 16.0f)));
					this->_chunkMap.at(render_chunk_pos.x).at(render_chunk_pos.z)->generate();
					new_chunk++;
				}
				if (z != 0 && z != (1 + 2 * circle - 1))
					x += (circle * 2);
				else
					x += 1;
			}
		}	
		if (new_chunk != 0)
			std::cout << "new to render: " << new_chunk << std::endl;
	}
}