/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:56:01 by capi              #+#    #+#             */
/*   Updated: 2026/02/04 16:30:24 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Game.hpp"

Game::Game(size_t seed)
: _seed(seed), _world()
{
	(void)this->_seed;
}

Game::~Game(void) {}

void	Game::init(void)
{
	// * Initialize TextureManager
	TextureManager::initialize();
	
	// * Instanciate all blocks
	BlockManager::instanciateBlock("dirt");			// 1
	BlockManager::instanciateBlock("grass_block");	// 2
	
	// * Instanciate all textures
	TextureManager::instanciateTexture("./assets/texture/block/dirt.png");			// 1
	TextureManager::instanciateTexture("./assets/texture/block/grass_side.png");	// 2
	TextureManager::instanciateTexture("./assets/texture/block/grass_top.png");		// 3

	//* Texture order : FRONT, BACK, RIGHT, LEFT, TOP, BOTTOM
	TextureManager::instanciateTextureBlock(DIRT, {TEX_DIRT, TEX_DIRT, TEX_DIRT, TEX_DIRT, TEX_DIRT, TEX_DIRT} );
	TextureManager::instanciateTextureBlock(GRASS_BLOCK, {TEX_GRASS_SIDE, TEX_GRASS_SIDE, TEX_GRASS_SIDE, TEX_GRASS_SIDE, TEX_GRASS_TOP, TEX_DIRT} );
}

void	Game::update(float deltaTime)
{
	this->_world.update(deltaTime);
}