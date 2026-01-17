/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:41:57 by capi              #+#    #+#             */
/*   Updated: 2026/01/17 22:01:59 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Block.hpp"

const float Block::vertices[] = {
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

const unsigned int	Block::indices[] = {
	// FRONT
	0, 3, 2,
	0, 1, 3,

	// BACK
	4, 7, 6,
	4, 5, 7,

	// RIGHT
	8, 11, 10,
	8,  9, 11,  

	// LEFT
	12, 15, 14,
	12, 13, 15,

	// TOP
	16, 19, 18,
	16, 17, 19,
	
	// BOTTOM
	20, 23, 22,
	20, 21, 23
};

// Texture order : FRONT, BACK, RIGHT, LEFT, TOP, BOTTOM
Block::Block(BlockId type, const glm::vec3& worldPos, const std::array<TextureId, 6>& face_texture)
: _type(type), _worldPos(worldPos), _textureIdFace(face_texture)
{
	(void)this->_type;
	BlockVertex vertices[24];
	// * GENERATE BLOCK VERTICES
	for (size_t i = 0; i < 24; i++)
	{
		vertices[i] = BlockVertex {
			.vPos = { Block::vertices[i * 5 + 0], Block::vertices[i * 5 + 1], Block::vertices[i * 5 + 2]},
			.texCoord = { Block::vertices[i * 5 + 3], Block::vertices[i * 5 + 4] },
			.world_pos = { this->_worldPos.x, this->_worldPos.y, this->_worldPos.z },
			.TextureId = this->_textureIdFace.at((i * 5 / 20))
		};
	}

	// * GENERATE ALL BUFFER

	this->_vb = new GL_Wrapper::VertexBuffer(vertices, 24 * sizeof(BlockVertex));
	this->_eb = new GL_Wrapper::ElementBuffer(Block::indices, 36);
	this->_va = new GL_Wrapper::VertexArray();

	GL_Wrapper::Layout layout_vpos = {GL_FLOAT, 3, GL_FALSE};
	GL_Wrapper::Layout layout_texture_coord = {GL_FLOAT, 2, GL_FALSE};
	GL_Wrapper::Layout layout_wpos = {GL_FLOAT, 3, GL_FALSE};
	GL_Wrapper::Layout layout_texture_id = {GL_UNSIGNED_INT, 1, GL_FALSE};
	GL_Wrapper::BufferLayout buffer_layout; 
	buffer_layout.addLayout(layout_vpos);
	buffer_layout.addLayout(layout_texture_coord);
	buffer_layout.addLayout(layout_wpos);
	buffer_layout.addLayout(layout_texture_id);

	this->_va->AddVertexBuffer(*this->_vb, buffer_layout);
	this->_va->AddElementBuffer(*this->_eb);
}

Block::~Block(void)
{
	delete this->_vb;
	delete this->_eb;
	delete this->_va;
}

void	Block::draw(GL_Wrapper::Shader& shader) const
{
	shader.use();

	this->_va->bind();
	GLCallThrow(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0));
	this->_va->unbind();
}
