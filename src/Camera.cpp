/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:22:02 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 22:37:42 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, float yaw, float pitch): _pos(pos), _yaw(yaw), _pitch(pitch)
{
	this->_dir = glm::vec3(
		cosf(glm::radians(this->_yaw)) * cosf(glm::radians(this->_pitch)),
		sin(glm::radians(this->_pitch)),
		sinf(glm::radians(this->_yaw)) * cosf(glm::radians(this->_pitch))
	);
	this->_dir = glm::normalize(this->_dir);

	glm::vec3 world_up = glm::vec3(0.0, 1.0, 0.0);
	this->_right = glm::normalize(glm::cross(world_up, this->_dir));

	this->_up = glm::normalize(glm::cross(this->_dir, this->_right));

	this->_view = glm::lookAt(this->_pos, this->_pos + this->_dir, this->_up);
	this->_projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

Camera::~Camera(void) {}

void	Camera::send_gpu(GL_Wrapper::Shader& shader) const
{
	shader.setMat4("view", this->_view);
	shader.setMat4("projection", this->_projection);
}

void	Camera::update_pos(glm::vec3 newPos)
{
	this->_pos = newPos;
}

void	Camera::update_vector(void)
{
	this->_dir = glm::vec3(
		cosf(glm::radians(this->_yaw)) * cosf(glm::radians(this->_pitch)),
		sin(glm::radians(this->_pitch)),
		sinf(glm::radians(this->_yaw)) * cosf(glm::radians(this->_pitch))
	);
	this->_dir = glm::normalize(this->_dir);

	glm::vec3 world_up = glm::vec3(0.0, 1.0, 0.0);
	this->_right = glm::normalize(glm::cross(world_up, this->_dir));

	this->_up = glm::normalize(glm::cross(this->_dir, this->_right));

	this->_view = glm::lookAt(this->_pos, this->_pos + this->_dir, this->_up);
	this->_projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);	
}

std::ostream& operator << (std::ostream &out, Camera& cam)
{
	glm::vec3 pos = cam.getPos();
	glm::vec3 dir = cam.getDir();
	glm::vec3 right = cam.getRight();
	
	out << "Pos: (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	out << "Dir: (" << dir.x << ", " << dir.y << ", " << dir.z << ")" << std::endl;
	out << "Right: (" << right.x << ", " << right.y << ", " << right.z << ")" << std::endl;

	return (out);
}