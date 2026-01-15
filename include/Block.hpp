/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:42:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/15 23:08:32 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_HPP
# define BLOCK_HPP

# define BLOCK_VERTICES 36

# include <glm/glm.hpp>

typedef enum BlockType
{
	GRASS_BLOCK
}	BlockType;

typedef struct BlockVertex
{
	float		vPos[3];
	float		world_pos[3];
}	BlockVertex;

class Block
{
	public:
		static const float vertices[BLOCK_VERTICES * 3];

	public:
		Block(BlockType	type, glm::vec3 worldPos);
		~Block(void);

		std::array<BlockVertex, 36>&	getVerticesData(void);
	private:
		BlockType					_type;
		glm::vec3					_worldPos;
		std::array<BlockVertex, 36>	_block_vertices;
};

#endif