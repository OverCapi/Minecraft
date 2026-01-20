/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Noise.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 23:11:43 by capi              #+#    #+#             */
/*   Updated: 2026/01/20 01:51:25 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_HPP
# define NOISE_HPP

# include "glm/glm.hpp"

class Noise
{
	public:
		static float	perlin_noise_2D(glm::vec2 p,
										size_t octave = 1, float lacunarity = 2.0f, float persistence = 0.5f);
		static float	perlin_noise_3D(glm::vec3 p, size_t seed,
										float scale, size_t octave = 1, float lacunarity = 2.0f, float persistence = 0.5f);

		static float	cubic_interpolate(float a, float b, float t);

	private:
			static glm::vec2	getRandomGradient(int grid_x, int grid_y);
};

#endif