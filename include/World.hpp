/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:40 by capi              #+#    #+#             */
/*   Updated: 2026/02/03 16:01:49 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_HPP
# define WORLD_HPP

# include <map>
# include <iostream>

# include <glm/glm.hpp>

# include "Utils.hpp"
# include "Camera.hpp"
# include "Chunk.hpp"

# include "TerrainGenerator.hpp"

class Chunk;

class World
{
	public:
		World(void);
		~World(void);

		Camera&	getCamera(void) { return (this->_camera); };

		int		getRenderDistance(void) { return (this->_renderDirstance); };
		void	setRenderDistance(int renderDistance) { if (renderDistance > 0) { this->_renderDirstance = renderDistance;} };
		
		std::unordered_map<int, std::unordered_map<int, Chunk*> >&	getChunkMap(void) { return (this->_chunkMap); };
		
		void	update(float delta_time);

		const TerrainGenerator&	getTerrainGenerator(void) const { return (this->_terrainGenerator); };

	private:
		Camera	_camera;

		int	_renderDirstance;
		std::unordered_map<int, std::unordered_map<int, Chunk*> > _chunkMap;

		TerrainGenerator	_terrainGenerator;		
};

#endif