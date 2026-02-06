/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:06:07 by capi              #+#    #+#             */
/*   Updated: 2026/02/05 17:29:54 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.hpp"

Renderer::Renderer(void)
:	_shader(GL_Wrapper::Shader("src/shader/vertex_shader.glsl", "src/shader/fragment_shader.glsl"))
{
	this->_shader.use();
	this->_shader.setInt("blockTexture", 0);
}

Renderer::~Renderer(void) {}

void	Renderer::render(World& world)
{
	Camera& camera = world.getCamera();
	camera.update_vector();
	this->send_info_gpu(camera);

	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	TextureManager::textures->use(0);

	glm::vec3& cam_pos = camera.getPos();
	int render_distance = world.getRenderDistance();
	glm::vec3 chunk_pos = Utils::getChunkPos(cam_pos);

	std::unordered_map<int, std::unordered_map<int, Chunk*> >& chunk_map = world.getChunkMap();	
	
	// chunk_map.at(0).at(0)->draw(this->_shader);

	/*
		For render distance of 2:

		6 7 8
		4 0 5
		1 2 3
	*/
	// TODO Draw only chunks that are in front of the camera.
	// ! Cam closer to the back chunk than the forward chunk due to chunk pos who is at the corner of the chunk
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

				glm::vec3 center = render_chunk_pos + glm::vec3(CHUNK_SIZE / 2, 0, CHUNK_SIZE / 2);
				
				if (glm::dot(center - cam_pos, camera.getDir()) >= 0)
					chunk_map.at(render_chunk_pos.z).at(render_chunk_pos.x)->draw(this->_shader);

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