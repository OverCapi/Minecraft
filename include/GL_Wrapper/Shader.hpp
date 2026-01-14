/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:17:42 by capi              #+#    #+#             */
/*   Updated: 2026/01/12 17:45:21 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP

# include <fstream>
# include <glm/glm.hpp>
# include <glm/gtc/type_ptr.hpp>

# include "GL_Wrapper/Macro.hpp"

namespace GL_Wrapper
{
	class Shader
	{
		public:
			Shader(const char *vs_file_name, const char *fs_file_name);
			~Shader(void);

			void	use(void) const;

			void	setBool(const std::string &name, bool value) const;
			void	setInt(const std::string &name, int value) const;
			void	setFloat(const std::string &name, float value) const;
			void	setMat4(const std::string &name, glm::mat4 mat) const;
		private:
			unsigned int	createShader(const char *file_name, GLenum shader_type);
		private:
			unsigned int	_id;
	};
};

#endif