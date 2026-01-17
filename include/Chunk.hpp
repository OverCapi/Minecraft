/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:47:06 by capi              #+#    #+#             */
/*   Updated: 2026/01/17 22:30:43 by capi             ###   ########.fr       */
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
		void	draw(GL_Wrapper::Shader& shader);
	private:
		glm::vec3																		_worldPos;
		std::array<std::array<std::array<Block *, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE>	_blocks;

		
};

#endif