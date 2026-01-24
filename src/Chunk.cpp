/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:37:35 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunk.hpp"

Chunk::Chunk(World* associateWorld, const glm::vec3& worldPos)
: _associateWorld(associateWorld), _worldPos(worldPos)
{}

Chunk::~Chunk(void)
{
	delete this->_vb;
	delete this->_eb;
	delete this->_va;
}

void	Chunk::generate(void)
{
	if (!this->_needToGenerate)
		return ;
	this->_needToGenerate = false;
	float scale = CHUNK_SIZE * 10.0f;
	// * GENERATE MAP HEIGHT
	for (size_t z = 0; z < CHUNK_SIZE; z++)
	{
		for (size_t x = 0; x < CHUNK_SIZE; x++)
		{
			float h = Noise::perlin_noise_2D(
				glm::vec2(((float)x + this->_worldPos.x) / scale, ((float)z + this->_worldPos.z) / scale),
				6,
				0.9f,
				0.01f
			);
			h = (h + 1.0f) / 2.0f;

			h = Utils::lerp(60.0f, CHUNK_HEIGHT, h);

			for (size_t y = 0; y < CHUNK_HEIGHT; y++)
			{
				if ((float)y < roundf(h))
					this->_blocks[z][y][x] = GRASS_BLOCK;
				else
					this->_blocks[z][y][x] = AIR;
			}
		}
	}
}

void	Chunk::render(void)
{
	// * GET CHUNK ARROUND
	Chunk *forward = nullptr, *backward = nullptr, *right = nullptr, *left = nullptr;
	
	std::map<int, std::map<int, Chunk *> >& chunk_map = this->_associateWorld->getChunkMap();

	// * FORWARD chunk
	if (chunk_map.find(this->_worldPos.z + CHUNK_SIZE) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z + CHUNK_SIZE).find(this->_worldPos.x) != chunk_map.at(this->_worldPos.z + CHUNK_SIZE).end())
		forward = chunk_map.at(this->_worldPos.z + CHUNK_SIZE).at(this->_worldPos.x);
	// * BACKWARD chunk
	if (chunk_map.find(this->_worldPos.z - CHUNK_SIZE) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z - CHUNK_SIZE).find(this->_worldPos.x) != chunk_map.at(this->_worldPos.z - CHUNK_SIZE).end())
		backward = chunk_map.at(this->_worldPos.z - CHUNK_SIZE).at(this->_worldPos.x);
	// * RIGHT chunk
	if (chunk_map.find(this->_worldPos.z) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z).find(this->_worldPos.x + CHUNK_SIZE) != chunk_map.at(this->_worldPos.z).end())
		right = chunk_map.at(this->_worldPos.z).at(this->_worldPos.x + CHUNK_SIZE);
	// * LEFT chunk
	if (chunk_map.find(this->_worldPos.z) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z).find(this->_worldPos.x - CHUNK_SIZE) != chunk_map.at(this->_worldPos.z).end())
		left = chunk_map.at(this->_worldPos.z).at(this->_worldPos.x - CHUNK_SIZE);

	// * CREATE BLOCK VERTICES
	std::vector<BlockVertex> blocks_vertices;
	std::vector<unsigned int> vertices_indices;
	size_t block_count = 0;

	for (size_t z = 0; z < CHUNK_SIZE; z++)
	{
		for (size_t y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (size_t x = 0; x < CHUNK_SIZE; x++)
			{
				// * CHECK IF WE NEED TO RENDER BLOCK
				if (this->_blocks[z][y][x] != AIR &&
					(z == 0 || z == CHUNK_SIZE - 1 || y == 0 || y == CHUNK_HEIGHT - 1 || x == 0 || x == CHUNK_SIZE - 1
					|| this->_blocks[z - 1][y][x] == AIR || this->_blocks[z + 1][y][x] == AIR
					|| this->_blocks[z][y - 1][x] == AIR || this->_blocks[z][y + 1][x] == AIR
					|| this->_blocks[z][y][x - 1] == AIR || this->_blocks[z][y][x + 1] == AIR))
				{
					std::array<TextureId, 6>& textures = TextureManager::getBlockTextures(this->_blocks[z][y][x]);
					for (size_t i = 0; i < 24; i++)
					{
						BlockVertex vertex = BlockVertex {
							.vPos = { vertices[i * 5 + 0], vertices[i * 5 + 1], vertices[i * 5 + 2]},
							.texCoord = { vertices[i * 5 + 3], vertices[i * 5 + 4] },
							.world_pos = { this->_worldPos.x + x, this->_worldPos.y + y, this->_worldPos.z + z },
							.TextureId = textures.at((i * 5) / 20)
						};
						blocks_vertices.push_back(vertex);
					}

					for (size_t i = 0; i < 36; i++)
					{
						// * CHECK IF WE NEED TO RENDER FACE
						size_t face_id = i / 6;
						switch (face_id)
						{
							// * FRONT
							case 0:
								if ((forward && z == CHUNK_SIZE - 1 && forward->getBlock(x, y, 0) != AIR) || (z != CHUNK_SIZE - 1 && this->_blocks[z + 1][y][x] != AIR))
									i += 5;
								else
									vertices_indices.push_back(indices[i] + (24 * block_count));
								break;
							// * BACK
							case 1:
								if ((backward && z == 0 && backward->getBlock(x, y, CHUNK_SIZE - 1) != AIR) || (z != 0 && this->_blocks[z - 1][y][x] != AIR))
									i += 5;
								else
									vertices_indices.push_back(indices[i] + (24 * block_count));
								break;
							// * RIGHT
							case 2:
								if ((right && x == CHUNK_SIZE - 1 && right->getBlock(0, y, z) != AIR) || (x != CHUNK_SIZE - 1 && this->_blocks[z][y][x + 1] != AIR))
									i += 5;
								else
									vertices_indices.push_back(indices[i] + (24 * block_count));
								break;
							// * LEFT
							case 3:
								if ((left && x == 0 && left->getBlock(CHUNK_SIZE - 1, y, z) != AIR) || (x != 0 && this->_blocks[z][y][x - 1] != AIR))
									i += 5;
								else
									vertices_indices.push_back(indices[i] + (24 * block_count));
								break;
							// * TOP
							case 4:
								if (y != CHUNK_HEIGHT - 1 && this->_blocks[z][y + 1][x] != AIR)
									i += 5;
								else
									vertices_indices.push_back(indices[i] + (24 * block_count));
								break;
							// * BOTTOM
							case 5:
								if (y != 0 && this->_blocks[z][y - 1][x] != AIR)
									i += 5;
								else
									vertices_indices.push_back(indices[i] + (24 * block_count));
								break;
						}
					}
					block_count++;
				}
			}
		}
	}
	this->_verticesToRender = vertices_indices.size();
	this->_vb = new GL_Wrapper::VertexBuffer(blocks_vertices.data(), sizeof(BlockVertex) * blocks_vertices.size());
	this->_eb = new GL_Wrapper::ElementBuffer(vertices_indices.data(), this->_verticesToRender);
	this->_va = new GL_Wrapper::VertexArray();

	GL_Wrapper::Layout layout_vpos = {GL_FLOAT, 3, GL_FALSE};
	GL_Wrapper::Layout layout_texture_coord = {GL_FLOAT, 2, GL_FALSE};
	GL_Wrapper::Layout layout_wpos = {GL_FLOAT, 3, GL_FALSE};
	GL_Wrapper::Layout layout_texture_id = {GL_UNSIGNED_INT, 1, GL_FALSE};
	GL_Wrapper::BufferLayout buffer_layout; 
	buffer_layout.addLayout(layout_vpos);
	buffer_layout.addLayout(layout_texture_coord);
	buffer_layout.addLayout(layout_wpos);
	buffer_layout.addLayout(layout_texture_id);

	this->_va->AddVertexBuffer(*this->_vb, buffer_layout);
	this->_va->AddElementBuffer(*this->_eb);

	this->_needToRender = false;
}

void	Chunk::draw(GL_Wrapper::Shader& shader)
{
	if (this->_needToRender)
		this->render();
	shader.use();
	this->_va->bind();
	GLCallThrow(glDrawElements(GL_TRIANGLES, this->_verticesToRender, GL_UNSIGNED_INT, 0));
	this->_va->unbind();
}