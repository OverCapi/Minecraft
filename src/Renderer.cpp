/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:06:07 by capi              #+#    #+#             */
/*   Updated: 2026/01/19 15:33:35 by capi             ###   ########.fr       */
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
	Camera& camera = world.getCamera();
	camera.update_vector();
	this->send_info_gpu(camera);

	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	this->_texture.use(0);

	glm::vec3& cam_pos = camera.getPos();
	int render_distance = world.getRenderDistance();
	std::map<int, std::map<int, Chunk*> >& chunk_map = world.getChunkMap();

	glm::vec3 chunk_pos = glm::vec3(
		(int)(cam_pos.x / CHUNK_SIZE) * CHUNK_SIZE,
		0,
		(int)(cam_pos.z / CHUNK_SIZE) * CHUNK_SIZE
	);


	
	// chunk_map.at(0).at(0)->draw(this->_shader);

	/*
		For render distance of 2:

		6 7 8
		4 0 5
		1 2 3
	*/
	// TODO Draw only chunks that are in front of the camera.
	for (size_t circle = 0; circle < (size_t)render_distance; circle++)
	{
		for (size_t z = 0; z < 1 + 2 * circle; z++)
		{
			for (size_t x = 0; x < 1 + 2 * circle; )
			{
				glm::vec3 render_chunk_pos = glm::vec3(
					chunk_pos.x - (circle * CHUNK_SIZE) + (x * CHUNK_SIZE),
					0.0,
					chunk_pos.z - (circle * CHUNK_SIZE) + (z * CHUNK_SIZE)
				);
				glm::vec3 render_chunk_pos_center = glm::vec3(
					chunk_pos.x - (circle * CHUNK_SIZE) + (x * CHUNK_SIZE) + CHUNK_SIZE / 2,
					0.0,
					chunk_pos.z - (circle * CHUNK_SIZE) + (z * CHUNK_SIZE) + CHUNK_SIZE / 2
				);
				if (chunk_pos == render_chunk_pos || glm::dot(camera.getDir(), glm::normalize(render_chunk_pos_center - camera.getPos())) > 0.0)
				{
					std::cout << "chunk : " << chunk_pos.x - (circle * CHUNK_SIZE) + (x * CHUNK_SIZE) << " " << chunk_pos.z - (circle * CHUNK_SIZE) + (z * CHUNK_SIZE) << std::endl;
					chunk_map.at(render_chunk_pos.x).at(render_chunk_pos.z)->draw(this->_shader);
				}
				if (z != 0 && z != (1 + 2 * circle - 1))
					x += (circle * 2);
				else
					x += 1;
			}
		}
	}
}

void	Renderer::send_info_gpu(Camera& camera)
{
	this->_shader.setMat4("view", camera.getView());
	this->_shader.setMat4("projection", camera.getProjection());
}