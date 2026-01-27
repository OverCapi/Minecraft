/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 00:40:31 by capi              #+#    #+#             */
/*   Updated: 2026/01/27 01:25:21 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <glm/glm.hpp>
# include <iostream>

#define CHUNK_SIZE 16

namespace Utils
{
	glm::vec3		getChunkPos(const glm::vec3& pos);
	float			cubic_interpolate(float a, float b, float t);
} // namespace Utils

	std::ostream&	operator<<(std::ostream& os, const glm::vec3& v);

#endif