/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:32:34 by capi              #+#    #+#             */
/*   Updated: 2026/02/05 17:18:09 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TextureManager.hpp"

unsigned int	TextureManager::texturesId = 1;
GL_Wrapper::Texture2DArray*	TextureManager::textures = nullptr;
std::unordered_map<unsigned int, std::array<TextureId, 6> >	TextureManager::blocksTexturesMap = std::unordered_map<unsigned int, std::array<TextureId, 6> >();

void	TextureManager::initialize()
{
	if (textures == nullptr)
		textures = new GL_Wrapper::Texture2DArray(TEXTURE_WIDTH, TEXTURE_HEIGHT, 3, GL_RGBA);
}

unsigned int	TextureManager::instanciateTexture(const char* filename)
{
	TextureManager::textures->addTexture(filename, GL_RGBA, true);
	return (TextureManager::texturesId++);
}

void	TextureManager::instanciateTextureBlock(unsigned int blokcId, const std::array<TextureId, 6>& texturesIds)
{
	TextureManager::blocksTexturesMap.insert(std::pair<unsigned int, std::array<TextureId, 6> >(blokcId, texturesIds));
}

const std::array<TextureId, 6>&	TextureManager::getBlockTextures(unsigned int blockId)
{
	return (TextureManager::blocksTexturesMap.at(blockId));
}