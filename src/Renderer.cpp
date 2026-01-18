/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:06:07 by capi              #+#    #+#             */
/*   Updated: 2026/01/18 14:22:39 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.hpp"

Renderer::Renderer(void)
:	_shader(GL_Wrapper::Shader("src/shader/vertex_shader.glsl", "src/shader/fragment_shader.glsl")),
	_texture(GL_Wrapper::Texture2DArray(16, 16, 3, GL_RGBA))
{
	this->_shader.use();
	this->_shader.setInt("blockTexture", 0);

	this->_texture.addTexture("assets/texture/block/dirt.png", GL_RGBA, true);
	this->_texture.addTexture("assets/texture/block/grass_side.png", GL_RGBA, true);
	this->_texture.addTexture("assets/texture/block/grass_top.png", GL_RGBA, true);
}

Renderer::~Renderer(void) {}

void	Renderer::render(World& world)
{
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	this->_texture.use(0);

	Camera& camera = world.getCamera();
	camera.send_gpu(this->_shader);
	camera.update_vector();

	glm::vec3& cam_pos = camera.getPos();
	int render_distance = world.getRenderDistance();
	std::map<int, std::map<int, Chunk*> >& chunk_map = world.getChunkMap();

	glm::vec3 chunk_pos = glm::vec3(
		(int)(cam_pos.x / CHUNK_SIZE),
		(int)(cam_pos.y / CHUNK_SIZE),
		(int)(cam_pos.z / CHUNK_SIZE)
	);

	/*
		For render distance of 2:

		1 2 3
		4 0 5
		6 7 8
	*/
	for (size_t circle = 0; circle < (size_t)render_distance; circle++)
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
				chunk_map.at(render_chunk_pos.x).at(render_chunk_pos.z)->draw(this->_shader);
				if (z != 0 && z != (1 + 2 * circle - 1))
					x += (circle * 2);
				else
					x += 1;
			}
		}
	}
}