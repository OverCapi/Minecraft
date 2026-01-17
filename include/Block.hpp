/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:42:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/17 17:44:42 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_HPP
# define BLOCK_HPP

# define BLOCK_VERTICES 36

# include <glm/glm.hpp>

# include "GL_Wrapper/Shader.hpp"
# include "GL_Wrapper/VertexBuffer.hpp"
# include "GL_Wrapper/ElementBuffer.hpp"
# include "GL_Wrapper/VertexArray.hpp"

typedef enum BlockId
{
	GRASS_BLOCK = 1
}	BlockId;

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
		static const float			vertices[5 * 4 * 6];
		static const unsigned int	indices[BLOCK_VERTICES];

	public:
		Block(BlockId	type, const glm::vec3& worldPos, const std::array<TextureId, 6>& face_texture);
		~Block(void);

		void	draw(GL_Wrapper::Shader& shader) const;
	private:
		BlockId						_type;
		glm::vec3					_worldPos;
		std::array<TextureId, 6>	_textureIdFace;

		GL_Wrapper::VertexBuffer	*_vb;		
		GL_Wrapper::ElementBuffer	*_eb;		
		GL_Wrapper::VertexArray		*_va;	
};

#endif