/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:41:57 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 22:28:10 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Blocks/BlockType.hpp"

BlockType::BlockType(const std::string& name, unsigned int blockId)
: _name(name), _blockId(blockId) {}

BlockType::~BlockType(void) {}