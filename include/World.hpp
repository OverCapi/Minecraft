/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:46:40 by capi              #+#    #+#             */
/*   Updated: 2026/01/17 21:11:43 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_HPP
# define WORLD_HPP

# include <map>
# include <iostream>

# include <glm/glm.hpp>

# include "Camera.hpp"
# include "Chunk.hpp"

class World
{
	public:
		World(Camera& camera);
		~World(void);

		Camera&	getCamera(void) { return (this->_camera); };

		int	getRenderDistance(void) { return (this->_renderDirstance); };
		std::map<int, std::map<int, Chunk*> >&	getChunkMap(void) { return (this->_chunkMap); };
		

		void	update(float delta_time);
	private:
		Camera&	_camera;

		int	_renderDirstance;
		std::map<int, std::map<int, Chunk*> > _chunkMap;
};

#endif