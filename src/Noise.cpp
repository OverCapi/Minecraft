/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Noise.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 23:13:19 by capi              #+#    #+#             */
/*   Updated: 2026/01/18 23:42:06 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Noise.hpp"

float	Noise::perlin_noise_2D(
	glm::vec2 p, size_t seed,
	float scale, size_t octave = 1, float lacunarity = 2.0f, float persistence = 0.5f
)
{	
	p += seed;

	float result = 0;

	float frequency = 1.0f;
	float amplitude = 1.0f;
	for (size_t i = 0; i < octave; i++)
	{
		p *= frequency;
		p /= scale;

		// * get the coordonate of the grid
		int grid_x0 = p.x;
		int grid_y0 = p.y;
		int grid_x1 = p.x + 1;
		int grid_y1 = p.y + 1;

		// * get weight for x and y
		glm::vec2 weight = glm::vec2(p.x - grid_x0, p.y - grid_y0);

		glm::vec2 gradient = Noise::getRandomGradient(grid_x0, grid_y0);

		glm::vec2 grid_p = p - glm::vec2(grid_x0, grid_y0);

		float dot_n0 = glm::dot(gradient, p - glm::vec2(grid_x0, grid_y0));
		float dot_n1 = glm::dot(gradient, p - glm::vec2(grid_x1, grid_y0));
		float a = Noise::cubic_interpolate(dot_n0, dot_n1, weight.x);

		dot_n0 = glm::dot(gradient, p - glm::vec2(grid_x0, grid_y1));
		dot_n1 = glm::dot(gradient, p - glm::vec2(grid_x1, grid_y1));
		float b = Noise::cubic_interpolate(dot_n0, dot_n1, weight.x);

		result += Noise::cubic_interpolate(a, b, weight.y) * amplitude;

		frequency *= lacunarity;
		amplitude *= persistence;
	}
	return (result);
}

float	Noise::cubic_interpolate(float a, float b, float t)
{
	return ((b - a) * (3.0 - t * 2.0) * t * t + a);
}

glm::vec2	Noise::getRandomGradient(int grid_x, int grid_y)
{
	// * No precomputed gradients mean this works for any number of grid coordinates
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2; 
	
	unsigned a = grid_x;
	unsigned b = grid_y;
	a *= 3284157443;

	b ^= a << s | a >> w - s;
	b *= 1911520717;

	a ^= b << s | b >> w - s;
	a *= 2048419325;
	float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
	
	// * Create the vector from the angle
	glm::vec2 v;
	v.x = sin(random);
	v.y = cos(random);

	return (v);
}