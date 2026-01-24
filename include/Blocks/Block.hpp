/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:42:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 15:07:27 by capi             ###   ########.fr       */
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

// # define GRASS_BLOCK() Block("grass_block", 1, );

// TODO store texturesIds in unordered_map<id, textureArray> in the texture manager
class Block
{	
	public:
		// This class should only be instantiated directly if the block has no function.
		// otherwise WIP
		Block(const std::string& name, unsigned int id, const std::array<unsigned int, 6>& texturesIds);
		~Block(void);

		const std::string&						getName(void) const { return (this->_name); };
		unsigned int							getId(void) const { return (this->_id); };
		const std::array<unsigned int, 6>&		getTexturesIds(void) const { return (this->_texturesIds); };
	private:
		const std::string					_name;
		const unsigned int					_id;
		const std::array<unsigned int, 6>	_texturesIds;
};


#endif