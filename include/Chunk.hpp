/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:47:06 by capi              #+#    #+#             */
/*   Updated: 2026/01/19 14:45:33 by capi             ###   ########.fr       */
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
#include  "World.hpp"

# define CHUNK_SIZE 16

class World;

class Chunk
{
	public:
		Chunk(World *_associateWorld, const glm::vec3& worldPos);
		~Chunk(void);

		void	generate(void);
		void	render(void);
		void	draw(GL_Wrapper::Shader& shader);

		BlockId	getBlock(int x, int y, int z) const { return (this->_blocks[z][y][x]); };
	private:
		World		*_associateWorld;

		glm::vec3	_worldPos;

		BlockId	_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		size_t	_verticesToRender = 0;

		bool	_needToRender = true;

		GL_Wrapper::VertexBuffer	*_vb = nullptr;
		GL_Wrapper::ElementBuffer	*_eb = nullptr;
		GL_Wrapper::VertexArray		*_va = nullptr;
};

#endif