/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:22:02 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:27:16 by capi             ###   ########.fr       */
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
	this->_projection = glm::perspective(glm::radians(70.0f), 1920.0f / 1080.0f, 0.1f, 192.0f);
}

Camera::~Camera(void) {}

void	Camera::process_input(GLFWwindow *window, float delta_time)
{
	float velocity = g_ImGui_speed * delta_time;

	glm::vec3 dir_xz = glm::normalize(glm::vec3(this->_dir.x, 0.0, this->_dir.z));
	glm::vec3 right_xz = glm::normalize(glm::vec3(this->_right.x, 0.0, this->_right.z));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->_pos += dir_xz * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->_pos -= dir_xz * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->_pos -= right_xz * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->_pos += right_xz * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->_pos += glm::vec3(0, 1, 0) * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		this->_pos -= glm::vec3(0, 1, 0) * velocity;
	}
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
	this->_projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 10000.0f);	
}
