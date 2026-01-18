/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:22:19 by capi              #+#    #+#             */
/*   Updated: 2026/01/18 17:31:37 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# define GLFW_INCLUDE_NONE
# include <GLFW/glfw3.h>

extern float g_ImGui_speed;

class Camera
{
	public:
		Camera(void) {};
		Camera(glm::vec3 pos, float yaw, float pitch);
		~Camera(void);

		void		process_input(GLFWwindow *window, float delta_time);

		void		update_vector(void);
		void		update_pos(glm::vec3 newPos);

		glm::vec3&	getPos(void) { return (this->_pos); };
		glm::vec3&	getDir(void) { return (this->_dir); };
		glm::vec3&	getRight(void) { return (this->_right); };
		glm::vec3&	getUp(void) { return (this->_up); };
		float&		getYaw(void) { return (this->_yaw); };
		float&		getPitch(void) { return (this->_pitch); };

		glm::mat4&	getView(void) { return (this->_view); };
		glm::mat4&	getProjection(void) { return (this->_projection); };
	private:
		glm::vec3	_pos;
		
		glm::vec3	_dir;
		glm::vec3	_right;
		glm::vec3	_up;
		
		float		_yaw;
		float		_pitch;

		glm::mat4	_view;
		glm::mat4	_projection;
};

#endif