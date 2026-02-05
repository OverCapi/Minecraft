/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:47:06 by capi              #+#    #+#             */
/*   Updated: 2026/02/05 17:01:00 by capi             ###   ########.fr       */
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
	 0.0,  0.0,  1.0,	0.0, 0.0,	// 0
	 1.0,  0.0,  1.0,	1.0, 0.0,	// 1
	 0.0,  1.0,  1.0,	0.0, 1.0,	// 2
	 1.0,  1.0,  1.0,	1.0, 1.0,	// 3

	// BACK
	 0.0,  0.0,  0.0,	0.0, 0.0,	// 4
	 1.0,  0.0,  0.0,	1.0, 0.0,	// 5
	 0.0,  1.0,  0.0,	0.0, 1.0,	// 6
	 1.0,  1.0,  0.0,	1.0, 1.0,	// 7

	// RIGHT
	 1.0,  0.0,  1.0,	0.0, 0.0,	// 8
	 1.0,  0.0,  0.0,	1.0, 0.0,	// 9
	 1.0,  1.0,  1.0,	0.0, 1.0,	// 10
	 1.0,  1.0,  0.0,	1.0, 1.0,	// 11

	// LEFT
	 0.0,  0.0,  1.0,	0.0, 0.0,	// 12
	 0.0,  0.0,  0.0,	1.0, 0.0,	// 13
	 0.0,  1.0,  1.0,	0.0, 1.0,	// 14
	 0.0,  1.0,  0.0,	1.0, 1.0,	// 15

	// TOP
	 0.0,  1.0,  1.0,	0.0, 0.0,	// 16
	 1.0,  1.0,  1.0,	1.0, 0.0,	// 17
	 0.0,  1.0,  0.0,	0.0, 1.0,	// 18
	 1.0,  1.0,  0.0,	1.0, 1.0,	// 19

	// BOTTOM
	 0.0,  0.0,  1.0,	0.0, 0.0,	// 20
	 1.0,  0.0,  1.0,	1.0, 0.0,	// 21
	 0.0,  0.0,  0.0,	0.0, 1.0,	// 22
	 1.0,  0.0,  0.0,	1.0, 1.0,	// 23
};

class World;

// typedef struct BlockVertex
// {
// 	float		vPos[3];
// 	float		texCoord[2];
// 	float		world_pos[3];
// 	TextureId	TextureId;
// }	BlockVertex;

typedef struct BlockVertex
{
	float		world_pos[3];
	float		texCoord[2];
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

		void	renderGreedyMeshing(void);

		BlockId	getBlock(int x, int y, int z) const { return (this->_blocks[z][y][x]); };

	private:
		bool	isBlockVisible(int x, int y, int z) const;
		bool	isFaceVisible(int x, int y, int z, int faceId) const;
	private:
		World		*_associateWorld;
		
		Chunk		*_forward = nullptr;
		Chunk		*_backward = nullptr;
		Chunk		*_right = nullptr;
		Chunk		*_left = nullptr;

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