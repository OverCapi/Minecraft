/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:47:06 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:25:37 by capi             ###   ########.fr       */
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

# include "Noise.hpp"
# include "Blocks/BlockType.hpp"
# include "TextureManager.hpp"
# include "World.hpp"

# define CHUNK_SIZE	  16
# define CHUNK_HEIGHT 256
# define BLOCK_VERTICES 36

const float vertices[] = {
	// POSITION			// TEX COORD
	// FRONT
	-0.5, -0.5,  0.5,	0.0, 0.0,	// 0
	 0.5, -0.5,  0.5,	1.0, 0.0,	// 1
	-0.5,  0.5,  0.5,	0.0, 1.0,	// 2
	 0.5,  0.5,  0.5,	1.0, 1.0,	// 3

	// BACK
	-0.5, -0.5, -0.5,	0.0, 0.0,	// 4
	 0.5, -0.5, -0.5,	1.0, 0.0,	// 5
	-0.5,  0.5, -0.5,	0.0, 1.0,	// 6
	 0.5,  0.5, -0.5,	1.0, 1.0,	// 7

	// RIGHT
	 0.5, -0.5,  0.5,	0.0, 0.0,	// 8
	 0.5, -0.5, -0.5,	1.0, 0.0,	// 9
	 0.5,  0.5,  0.5,	0.0, 1.0,	// 10
	 0.5,  0.5, -0.5,	1.0, 1.0,	// 11

	// LEFT
	-0.5, -0.5,  0.5,	0.0, 0.0,	// 12
	-0.5, -0.5, -0.5,	1.0, 0.0,	// 13
	-0.5,  0.5,  0.5,	0.0, 1.0,	// 14
	-0.5,  0.5, -0.5,	1.0, 1.0,	// 15

	// TOP
	-0.5,  0.5,  0.5,	0.0, 0.0,	// 16
	 0.5,  0.5,  0.5,	1.0, 0.0,	// 17
	-0.5,  0.5, -0.5,	0.0, 1.0,	// 18
	 0.5,  0.5, -0.5,	1.0, 1.0,	// 19

	// BOTTOM
	-0.5, -0.5,  0.5,	0.0, 0.0,	// 20
	 0.5, -0.5,  0.5,	1.0, 0.0,	// 21
	-0.5, -0.5, -0.5,	0.0, 1.0,	// 22
	 0.5, -0.5, -0.5,	1.0, 1.0,	// 23
};

const unsigned int	indices[] = {
	// FRONT
	0, 3, 2,
	0, 1, 3,

	// BACK
	6, 7, 4,
	7, 5, 4,

	// RIGHT
	8, 11, 10,
	8,  9, 11,  

	// LEFT
	14, 15, 12,
	15, 13, 12,

	// TOP
	16, 19, 18,
	16, 17, 19,
	
	// BOTTOM
	22, 23, 20,
	23, 21, 20
};

class World;

typedef struct BlockVertex
{
	float		vPos[3];
	float		texCoord[2];
	float		world_pos[3];
	TextureId	TextureId;
}	BlockVertex;

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

		BlockId	_blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
		size_t	_verticesToRender = 0;

		bool	_needToGenerate = true;
		bool	_needToRender = true;

		GL_Wrapper::VertexBuffer	*_vb = nullptr;
		GL_Wrapper::ElementBuffer	*_eb = nullptr;
		GL_Wrapper::VertexArray		*_va = nullptr;
};

#endif