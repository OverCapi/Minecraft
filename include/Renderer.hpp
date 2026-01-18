/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:02:45 by capi              #+#    #+#             */
/*   Updated: 2026/01/18 17:34:30 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_HPP
# define RENDERER_HPP

# include "GL_Wrapper/Shader.hpp"
# include "GL_Wrapper/Texture2DArray.hpp"

# include "World.hpp"


class Renderer
{
	public:
		Renderer(void);
		~Renderer(void);

		void	render(World& world);
	private:
		void	send_info_gpu(Camera& camera);

	private:
		GL_Wrapper::Shader			_shader;
		GL_Wrapper::Texture2DArray	_texture;
};

#endif