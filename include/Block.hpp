/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:42:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 22:28:16 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_HPP
# define BLOCK_HPP

# define BLOCK_VERTICES 36

# include <glm/glm.hpp>

typedef enum BlockType
{
	GRASS_BLOCK = 1
}	BlockType;

typedef enum TextureId
{
	DIRT = 0,
	GRASS_BLOCK_SIDE,
	GRASS_BLOCK_TOP,
}	TextureId;

typedef struct BlockVertex
{
	float		vPos[3];
	float		texCoord[2];
	float		world_pos[3];
	TextureId	TextureId;
}	BlockVertex;

class Block
{
	public:
		static const float vertices[BLOCK_VERTICES * (3 + 2)];

	public:
		Block(BlockType	type, const glm::vec3& worldPos, const std::array<TextureId, 6>& face_texture);
		~Block(void);

		std::array<BlockVertex, 36>&	getVerticesData(void);
	private:
		BlockType					_type;
		glm::vec3					_worldPos;
		std::array<BlockVertex, 36>	_block_vertices;
		std::array<TextureId, 6>	_textureIdFace;
};

#endif