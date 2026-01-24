/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:49:41 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 21:52:41 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCKMANAGER_HPP
# define BLOCKMANAGER_HPP

# include <unordered_map>

# include "BlockType.hpp"

class BlockManager
{
	public:
		static unsigned int instanciateBlock(const char* blockName);

		static unsigned int									blockId;
		static std::unordered_map<unsigned int, BlockType>	blockTypeMap;
};

#endif