/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Noise.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 23:11:43 by capi              #+#    #+#             */
/*   Updated: 2026/01/28 17:47:18 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_HPP
# define NOISE_HPP

# include "glm/glm.hpp"

typedef struct NoiseParam
{
	uint8_t	octave;
	float	lacunarity;
	float	persistence;
	float	zoom;

	NoiseParam(uint8_t octave, float lacunarity, float persistence, float zoom): octave(octave), lacunarity(lacunarity), persistence(persistence), zoom(zoom) {};
}	NoiseParam;

class Noise
{
	public:
		static float	fractalNoise2D(float x, float y, uint8_t octave, float lacunarity, float persistence);
		static float	noise2D(float x, float y);

	private:
		static float	dot_grad(int hash, float x, float y);

		static float	fade(float t);
		static float	lerp(float a, float b, float t);
	private:
		static const int	_permutationTable[512];
};

#endif