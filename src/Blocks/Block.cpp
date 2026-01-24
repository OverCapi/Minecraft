/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:41:57 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 14:54:00 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Block.hpp"

Block::Block(const std::string& name, unsigned int id, const std::array<unsigned int, 6>& texturesIds)
: _name(name), _id(id), _texturesIds(texturesIds)
{}

Block::~Block(void) {}