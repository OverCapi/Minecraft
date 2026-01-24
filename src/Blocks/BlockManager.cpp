/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:51:54 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:47:36 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Blocks/BlockManager.hpp"

unsigned int	BlockManager::blockId = 0;
std::unordered_map<unsigned int, BlockType>	BlockManager::blockTypeMap = std::unordered_map<unsigned int, BlockType>();

unsigned int BlockManager::instanciateBlock(const char* blockName)
{
	BlockManager::blockTypeMap.insert(std::pair<unsigned int, BlockType>(BlockManager::blockId, BlockType(blockName, BlockManager::blockId)));
	return (BlockManager::blockId++);
}