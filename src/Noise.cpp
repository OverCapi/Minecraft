/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Noise.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 23:13:19 by capi              #+#    #+#             */
/*   Updated: 2026/01/26 23:27:17 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Noise.hpp"

#include <iostream>

const int Noise::_permutationTable[512] = { 
	151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,

	151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
};

float	Noise::fractalNoise2D(float x, float y, uint8_t octave, float lacunarity, float persistence)
{
	float result = 0.0f;
	float frequency = 1.0f;
	float amplitude = 1.0f;
	float sum_amplitude = 0.0f;
	for (uint8_t i = 0; i < octave; i++)
	{
		result += noise2D(x * frequency, y * frequency) * amplitude;
		sum_amplitude += amplitude;
		frequency *= lacunarity;
		amplitude *= persistence;
	}
	return (result / sum_amplitude);
}

float	Noise::noise2D(float x, float y)
{
    const int floor_x = (int)floorf(x);
    const int floor_y = (int)floorf(y);
    
    const int ix = (floor_x % 256 + 256) % 256;
    const int iy = (floor_y % 256 + 256) % 256;

    const float xf0 = x - floor_x;
    const float xf1 = xf0 - 1;
    const float yf0 = y - floor_y;
    const float yf1 = yf0 - 1;

	const float u = fade(xf0);
	const float v = fade(yf0);

	const int h00 = _permutationTable[_permutationTable[ix + 0] + iy + 0];
	const int h01 = _permutationTable[_permutationTable[ix + 0] + iy + 1];
	const int h10 = _permutationTable[_permutationTable[ix + 1] + iy + 0];
	const int h11 = _permutationTable[_permutationTable[ix + 1] + iy + 1];

	const float x1 = lerp(dot_grad(h00, xf0, yf0), dot_grad(h10, xf1, yf0), u);
	const float x2 = lerp(dot_grad(h01, xf0, yf1), dot_grad(h11, xf1, yf1), u);
	float noise = lerp(x1, x2, v);
	
	noise = noise > 1.0f ? 1.0f : noise;
	noise = noise < -1.0f ? -1.0f : noise;
	return (noise);
}

float	Noise::dot_grad(int hash, float x, float y)
{
	switch (hash & 0x7) {
		case 0x0: return  x + y;
		case 0x1: return  x;
		case 0x2: return  x - y;
		case 0x3: return -y;
		case 0x4: return -x - y;
		case 0x5: return -x;
		case 0x6: return -x + y;
		case 0x7: return  y;
		default:  return  0.0f;
	}
}

float	Noise::fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

float	Noise::lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}