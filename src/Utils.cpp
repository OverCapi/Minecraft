/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 00:40:50 by capi              #+#    #+#             */
/*   Updated: 2026/01/27 01:43:14 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

glm::vec3	Utils::getChunkPos(const glm::vec3& pos)
{
	glm::vec3	chunk_pos;
	float		x, z;
	float		modx, modz;
	float		d;

	chunk_pos.y = 0.0;

	x = floorf(pos.x);
	modx = fmod(x, CHUNK_SIZE);
	if (modx < 0)
		d = CHUNK_SIZE + modx;
	else
		d = modx;
	chunk_pos.x = x - d;
	
	z = floorf(pos.z);
	modz = fmod(z, CHUNK_SIZE);
	if (modz < 0)
		d = -CHUNK_SIZE - modz;
	else
		d = -modz;
	chunk_pos.z = z + d;
	return (chunk_pos);
}

float	Utils::cubic_interpolate(float a, float b, float t)
{
	return ((b - a) * (3.0 - t * 2.0) * t * t + a);
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return (os);
}