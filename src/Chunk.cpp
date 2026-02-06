/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:27 by capi              #+#    #+#             */
/*   Updated: 2026/02/06 18:38:40 by capi             ###   ########.fr       */
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

	const TerrainGenerator& generator = this->_associateWorld->getTerrainGenerator();

	// * GENERATE MAP HEIGHT
	for (size_t z = 0; z < CHUNK_SIZE; z++)
	{            
		for (size_t x = 0; x < CHUNK_SIZE; x++)
		{
			const float wx = this->_worldPos.x + x;
			const float wz = this->_worldPos.z + z;
			const float height = generator.getTerrainShape(wx, wz);

			for (size_t y = 0; y < CHUNK_HEIGHT; y++)
			{
				float density = Noise::fractalNoise3D((this->_worldPos.x + x) / (16.0f * 4.0f), (this->_worldPos.y + y) / (16.0f * 4.0f), (this->_worldPos.z + z) / (16.0f * 4.0f), 4, 2.0f, 0.5f);
				density = (density + 1.0f) / 2.0f;
				if ((float)y < height && density >= 0.5f)
				{
					this->_blocks[z][y][x] = GRASS_BLOCK;
				}
				else
					this->_blocks[z][y][x] = AIR;
			}
		}
	}
}

bool	Chunk::isBlockVisible(int x, int y, int z) const
{
	return (this->_blocks[z][y][x] != AIR &&
		(z == 0 || z == CHUNK_SIZE - 1 || y == 0 || y == CHUNK_HEIGHT - 1 || x == 0 || x == CHUNK_SIZE - 1
		|| this->_blocks[z - 1][y][x] == AIR || this->_blocks[z + 1][y][x] == AIR
		|| this->_blocks[z][y - 1][x] == AIR || this->_blocks[z][y + 1][x] == AIR
		|| this->_blocks[z][y][x - 1] == AIR || this->_blocks[z][y][x + 1] == AIR));
}

bool	Chunk::isFaceVisible(int x, int y, int z, int faceId) const
{
	switch (faceId)
	{
		//* FRONT
		case 0:
			return ((this->_forward && z == CHUNK_SIZE - 1 && this->_forward->getBlock(x, y, 0) == AIR) || (z != CHUNK_SIZE - 1 && this->_blocks[z + 1][y][x] == AIR));
		//* BACK
		case 1:
			return ((this->_backward && z == 0 && this->_backward->getBlock(x, y, CHUNK_SIZE - 1) == AIR) || (z != 0 && this->_blocks[z - 1][y][x] == AIR));
		//* RIGHT
		case 2:
			return ((this->_right && x == CHUNK_SIZE - 1 && this->_right->getBlock(0, y, z) == AIR) || (x != CHUNK_SIZE - 1 && this->_blocks[z][y][x + 1] == AIR));
		//* LEFT
		case 3:
			return ((this->_left && x == 0 && this->_left->getBlock(CHUNK_SIZE - 1, y, z) == AIR) || (x != 0 && this->_blocks[z][y][x - 1] == AIR));
		//* UP
		case 4:
			return (y == CHUNK_HEIGHT - 1 || this->_blocks[z][y + 1][x] == AIR);
		//* DOWN
		case 5:
			return (y != 0 && this->_blocks[z][y - 1][x] == AIR);
		default:
			return (false);
	}
}

void	Chunk::render(void)
{
	// * GET CHUNK ARROUND
	
	std::unordered_map<int, std::unordered_map<int, Chunk *> >& chunk_map = this->_associateWorld->getChunkMap();

	// * FORWARD chunk
	if (!this->_forward && chunk_map.find(this->_worldPos.z + CHUNK_SIZE) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z + CHUNK_SIZE).find(this->_worldPos.x) != chunk_map.at(this->_worldPos.z + CHUNK_SIZE).end())
		this->_forward = chunk_map.at(this->_worldPos.z + CHUNK_SIZE).at(this->_worldPos.x);
	// * BACKWARD chunk
	if (!this->_backward && chunk_map.find(this->_worldPos.z - CHUNK_SIZE) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z - CHUNK_SIZE).find(this->_worldPos.x) != chunk_map.at(this->_worldPos.z - CHUNK_SIZE).end())
		this->_backward = chunk_map.at(this->_worldPos.z - CHUNK_SIZE).at(this->_worldPos.x);
	// * RIGHT chunk
	if (!this->_right && chunk_map.find(this->_worldPos.z) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z).find(this->_worldPos.x + CHUNK_SIZE) != chunk_map.at(this->_worldPos.z).end())
		this->_right = chunk_map.at(this->_worldPos.z).at(this->_worldPos.x + CHUNK_SIZE);
	// * LEFT chunk
	if (!this->_left && chunk_map.find(this->_worldPos.z) != chunk_map.end() 
		&& chunk_map.at(this->_worldPos.z).find(this->_worldPos.x - CHUNK_SIZE) != chunk_map.at(this->_worldPos.z).end())
		this->_left = chunk_map.at(this->_worldPos.z).at(this->_worldPos.x - CHUNK_SIZE);

	// * CREATE BLOCK VERTICES
	std::vector<BlockVertex> blocks_vertices;
	std::vector<unsigned int> vertices_indices;
	size_t face_count = 0;

	blocks_vertices.reserve(1800);
	vertices_indices.reserve(2500);
	for (size_t z = 0; z < CHUNK_SIZE; z++)
	{
		for (size_t y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (size_t x = 0; x < CHUNK_SIZE; x++)
			{
				// * CHECK IF WE NEED TO RENDER BLOCK
				if (this->isBlockVisible(x, y, z))
				{
					//* Texture order : FRONT, BACK, RIGHT, LEFT, TOP, BOTTOM
					const std::array<TextureId, 6>& textures = TextureManager::getBlockTextures(this->_blocks[z][y][x]);
				
					//* FRONT
					if (this->isFaceVisible(x, y, z, 0))
					{
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[0 * 5 + 0], this->_worldPos.y + y + vertices[0 * 5 + 1], this->_worldPos.z + z + vertices[0 * 5 + 2]},
							.texCoord = { vertices[0 * 5 + 3], vertices[0 * 5 + 4] },
							.TextureId = textures.at(0)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[1 * 5 + 0], this->_worldPos.y + y + vertices[1 * 5 + 1], this->_worldPos.z + z + vertices[1 * 5 + 2]},
							.texCoord = { vertices[1 * 5 + 3], vertices[1 * 5 + 4] },
							.TextureId = textures.at(0)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[2 * 5 + 0], this->_worldPos.y + y + vertices[2 * 5 + 1], this->_worldPos.z + z + vertices[2 * 5 + 2]},
							.texCoord = { vertices[2 * 5 + 3], vertices[2 * 5 + 4] },
							.TextureId = textures.at(0)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[3 * 5 + 0], this->_worldPos.y + y + vertices[3 * 5 + 1], this->_worldPos.z + z + vertices[3 * 5 + 2]},
							.texCoord = { vertices[3 * 5 + 3], vertices[3 * 5 + 4] },
							.TextureId = textures.at(0)
						});
						vertices_indices.push_back(0 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(3 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						face_count++;
					}
					//* BACK
					if (this->isFaceVisible(x, y, z, 1))
					{
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[4 * 5 + 0], this->_worldPos.y + y + vertices[4 * 5 + 1], this->_worldPos.z + z + vertices[4 * 5 + 2]},
							.texCoord = { vertices[4 * 5 + 3], vertices[4 * 5 + 4] },
							.TextureId = textures.at(1)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[5 * 5 + 0], this->_worldPos.y + y + vertices[5 * 5 + 1], this->_worldPos.z + z + vertices[5 * 5 + 2]},
							.texCoord = { vertices[5 * 5 + 3], vertices[5 * 5 + 4] },
							.TextureId = textures.at(1)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[6 * 5 + 0], this->_worldPos.y + y + vertices[6 * 5 + 1], this->_worldPos.z + z + vertices[6 * 5 + 2]},
							.texCoord = { vertices[6 * 5 + 3], vertices[6 * 5 + 4] },
							.TextureId = textures.at(1)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[7 * 5 + 0], this->_worldPos.y + y + vertices[7 * 5 + 1], this->_worldPos.z + z + vertices[7 * 5 + 2]},
							.texCoord = { vertices[7 * 5 + 3], vertices[7 * 5 + 4] },
							.TextureId = textures.at(1)
						});
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(0 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(3 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						face_count++;
					}
					//* RIGHT
					if (this->isFaceVisible(x, y, z, 2))
					{
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[8 * 5 + 0], this->_worldPos.y + y + vertices[8 * 5 + 1], this->_worldPos.z + z + vertices[8 * 5 + 2]},
							.texCoord = { vertices[8 * 5 + 3], vertices[8 * 5 + 4] },
							.TextureId = textures.at(2)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[9 * 5 + 0], this->_worldPos.y + y + vertices[9 * 5 + 1], this->_worldPos.z + z + vertices[9 * 5 + 2]},
							.texCoord = { vertices[9 * 5 + 3], vertices[9 * 5 + 4] },
							.TextureId = textures.at(2)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[10 * 5 + 0], this->_worldPos.y + y + vertices[10 * 5 + 1], this->_worldPos.z + z + vertices[10 * 5 + 2]},
							.texCoord = { vertices[10 * 5 + 3], vertices[10 * 5 + 4] },
							.TextureId = textures.at(2)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[11 * 5 + 0], this->_worldPos.y + y + vertices[11 * 5 + 1], this->_worldPos.z + z + vertices[11 * 5 + 2]},
							.texCoord = { vertices[11 * 5 + 3], vertices[11 * 5 + 4] },
							.TextureId = textures.at(2)
						});
						vertices_indices.push_back(0 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(3 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						face_count++;
					}
					//* LEFT
					if (this->isFaceVisible(x, y, z, 3))
					{
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[12 * 5 + 0], this->_worldPos.y + y + vertices[12 * 5 + 1], this->_worldPos.z + z + vertices[12 * 5 + 2] },
							.texCoord = { vertices[12 * 5 + 3], vertices[12 * 5 + 4] },
							.TextureId = textures.at(3)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[13 * 5 + 0], this->_worldPos.y + y + vertices[13 * 5 + 1], this->_worldPos.z + z + vertices[13 * 5 + 2] },
							.texCoord = { vertices[13 * 5 + 3], vertices[13 * 5 + 4] },
							.TextureId = textures.at(3)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[14 * 5 + 0], this->_worldPos.y + y + vertices[14 * 5 + 1], this->_worldPos.z + z + vertices[14 * 5 + 2] },
							.texCoord = { vertices[14 * 5 + 3], vertices[14 * 5 + 4] },
							.TextureId = textures.at(3)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[15 * 5 + 0], this->_worldPos.y + y + vertices[15 * 5 + 1], this->_worldPos.z + z + vertices[15 * 5 + 2] },
							.texCoord = { vertices[15 * 5 + 3], vertices[15 * 5 + 4] },
							.TextureId = textures.at(3)
						});
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(0 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(3 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						face_count++;
					}
					//* UP
					if (this->isFaceVisible(x, y, z, 4))
					{	
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[16 * 5 + 0], this->_worldPos.y + y + vertices[16 * 5 + 1], this->_worldPos.z + z + vertices[16 * 5 + 2] },
							.texCoord = { vertices[16 * 5 + 3], vertices[16 * 5 + 4] },
							.TextureId = textures.at(4)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[17 * 5 + 0], this->_worldPos.y + y + vertices[17 * 5 + 1], this->_worldPos.z + z + vertices[17 * 5 + 2] },
							.texCoord = { vertices[17 * 5 + 3], vertices[17 * 5 + 4] },
							.TextureId = textures.at(4)
						}); 
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[18 * 5 + 0], this->_worldPos.y + y + vertices[18 * 5 + 1], this->_worldPos.z + z + vertices[18 * 5 + 2] },
							.texCoord = { vertices[18 * 5 + 3], vertices[18 * 5 + 4] },
							.TextureId = textures.at(4)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[19 * 5 + 0], this->_worldPos.y + y + vertices[19 * 5 + 1], this->_worldPos.z + z + vertices[19 * 5 + 2] },
							.texCoord = { vertices[19 * 5 + 3], vertices[19 * 5 + 4] },
							.TextureId = textures.at(4)
						});
						vertices_indices.push_back(0 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(3 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						face_count++;
					}
					//* DOWN
					if (this->isFaceVisible(x, y, z, 5))
					{
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[20 * 5 + 0], this->_worldPos.y + y + vertices[20 * 5 + 1], this->_worldPos.z + z + vertices[20 * 5 + 2] },
							.texCoord = { vertices[20 * 5 + 3], vertices[20 * 5 + 4] },
							.TextureId = textures.at(5)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[21 * 5 + 0], this->_worldPos.y + y + vertices[21 * 5 + 1], this->_worldPos.z + z + vertices[21 * 5 + 2] },
							.texCoord = { vertices[21 * 5 + 3], vertices[21 * 5 + 4] },
							.TextureId = textures.at(5)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[22 * 5 + 0], this->_worldPos.y + y + vertices[22 * 5 + 1], this->_worldPos.z + z + vertices[22 * 5 + 2] },
							.texCoord = { vertices[22 * 5 + 3], vertices[22 * 5 + 4] },
							.TextureId = textures.at(5)
						});
						blocks_vertices.emplace_back(BlockVertex {
							.world_pos = { this->_worldPos.x + x + vertices[23 * 5 + 0], this->_worldPos.y + y + vertices[23 * 5 + 1], this->_worldPos.z + z + vertices[23 * 5 + 2] },
							.texCoord = { vertices[23 * 5 + 3], vertices[23 * 5 + 4] },
							.TextureId = textures.at(5)
						});
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						vertices_indices.push_back(0 + face_count * 4);
						vertices_indices.push_back(2 + face_count * 4);
						vertices_indices.push_back(3 + face_count * 4);
						vertices_indices.push_back(1 + face_count * 4);
						face_count++;
					}
				}
			}
		}
	}

	
	this->_verticesToRender = vertices_indices.size();
	this->_vb = new GL_Wrapper::VertexBuffer(blocks_vertices.data(), sizeof(BlockVertex) * blocks_vertices.size());
	this->_eb = new GL_Wrapper::ElementBuffer(vertices_indices.data(), this->_verticesToRender);
	this->_va = new GL_Wrapper::VertexArray();
	
	// g_indices += this->_verticesToRender;
	// g_vertex += blocks_vertices.size();
	// g_call += 1;
	
	// std::cout << "vertex (avg) : " << g_vertex / g_call << std::endl;
	// std::cout << "vertices indices (avg) : " << g_indices / g_call << std::endl;
	
	// GL_Wrapper::Layout layout_vpos = {GL_FLOAT, 3, GL_FALSE};
	GL_Wrapper::Layout layout_wpos = {GL_FLOAT, 3, GL_FALSE};
	GL_Wrapper::Layout layout_texture_coord = {GL_FLOAT, 2, GL_FALSE};
	GL_Wrapper::Layout layout_texture_id = {GL_UNSIGNED_INT, 1, GL_FALSE};
	GL_Wrapper::BufferLayout buffer_layout; 
	// buffer_layout.addLayout(layout_vpos);
	buffer_layout.addLayout(layout_wpos);
	buffer_layout.addLayout(layout_texture_coord);
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