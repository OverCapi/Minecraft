/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:47:06 by capi              #+#    #+#             */
/*   Updated: 2026/01/18 15:06:40 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_HPP
# define CHUNK_HPP

# include <array>

# include <glm/glm.hpp>

# include "GL_Wrapper/Shader.hpp"

# include "GL_Wrapper/Shader.hpp"
# include "GL_Wrapper/VertexBuffer.hpp"
# include "GL_Wrapper/ElementBuffer.hpp"
# include "GL_Wrapper/VertexArray.hpp"

# include "Block.hpp"

# define CHUNK_SIZE 16

class Chunk
{
	public:
		Chunk(const glm::vec3& worldPos);
		~Chunk(void);

		void	generate(void);
		void	render(void);
		void	draw(GL_Wrapper::Shader& shader);
	private:
		glm::vec3	_worldPos;

		BlockId	_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		size_t	_verticesToRender = 0;

		bool	_needToRender = true;

		GL_Wrapper::VertexBuffer	*_vb = nullptr;
		GL_Wrapper::ElementBuffer	*_eb = nullptr;
		GL_Wrapper::VertexArray		*_va = nullptr;
};

#endif