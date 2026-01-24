/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:42:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:04:28 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCKTYPE_HPP
# define BLOCKTYPE_HPP

# include <glm/glm.hpp>

# include <array>

# include "GL_Wrapper/Shader.hpp"
# include "GL_Wrapper/VertexBuffer.hpp"
# include "GL_Wrapper/ElementBuffer.hpp"
# include "GL_Wrapper/VertexArray.hpp"

typedef enum BlockId
{
	AIR = 0,
	DIRT,
	GRASS_BLOCK,
}	BlockId;

// TODO store texturesIds in unordered_map<id, textureArray> in the texture manager
class BlockType
{	
	public:
		// This class should only be instantiated directly if the block has no function.
		// otherwise WIP
		BlockType(const std::string& name, unsigned int blockId);
		~BlockType(void);

		const std::string&						getName(void) const { return (this->_name); };
		unsigned int							getBlockId(void) const { return (this->_blockId); };
	private:
		const std::string	_name;
		const unsigned int	_blockId;
};


#endif