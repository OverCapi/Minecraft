/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:22:19 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 22:51:07 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "GL_Wrapper/Shader.hpp"

class Camera
{
	public:
		Camera(glm::vec3 pos, float yaw, float pitch);
		~Camera(void);

		void	send_gpu(GL_Wrapper::Shader& shader) const;
		void	update_vector(void);
		void	update_pos(glm::vec3 newPos);

		glm::vec3&	getPos(void) { return (this->_pos); };
		glm::vec3&	getDir(void) { return (this->_dir); };
		glm::vec3&	getRight(void) { return (this->_right); };
		glm::vec3&	getUp(void) { return (this->_up); };
		float&		getYaw(void) { return (this->_yaw); };
		float&		getPitch(void) { return (this->_pitch); };
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

std::ostream& operator << (std::ostream &out, Camera& cam);

#endif