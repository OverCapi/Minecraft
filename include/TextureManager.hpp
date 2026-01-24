/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:13:21 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:52:07 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTUREMANAGER_HPP
# define TEXTUREMANAGER_HPP

# include <array>
# include <unordered_map>
# include "GL_Wrapper/Texture2DArray.hpp"

# define TEXTURE_WIDTH 16
# define TEXTURE_HEIGHT 16

typedef enum TextureId
{
	TEX_DIRT = 0,
	TEX_GRASS_SIDE,
	TEX_GRASS_TOP,
}	TextureId;

class TextureManager
{
	public:
		static void			initialize();
		static unsigned int	instanciateTexture(const char* filename);
		//* Texture order : FRONT, BACK, RIGHT, LEFT, TOP, BOTTOM
		static void			instanciateTextureBlock(unsigned int blockId, const std::array<TextureId, 6>& texturesIds);
		static std::array<TextureId, 6>&	getBlockTextures(unsigned int blockId);

		static unsigned int														texturesId;
		static GL_Wrapper::Texture2DArray*											textures;

		static std::unordered_map<unsigned int, std::array<TextureId, 6> >	blocksTexturesMap;
};

#endif