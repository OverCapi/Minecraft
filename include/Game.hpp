/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:56:10 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:52:07 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <ctype.h>

# include "TextureManager.hpp"
# include "Blocks/BlockManager.hpp"

# include "World.hpp"

class Game
{
	public:
		Game(size_t seed);
		~Game(void);

		void	init(void);
		void	update(float deltaTime);

		World&	getWorld(void) { return (this->_world); };
	private:
		size_t	_seed;

		World	_world;
};

#endif