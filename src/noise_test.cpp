/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:47:28 by capi              #+#    #+#             */
/*   Updated: 2026/01/27 02:17:42 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Noise.hpp"
#include "TerrainGenerator.hpp"
#include <iostream>
#include <glm/glm.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 1000
#define HEIGHT 1000

int main(void)
{
	unsigned char data[WIDTH * HEIGHT] = {0};

	float min = FLT_MAX;
	float max = FLT_MIN;

	TerrainGenerator gen;

	const float scale = 16.0f * 10.0f;
	for (size_t z = 0; z < HEIGHT; z++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			float fx = (float)x - (float)WIDTH / 2.0f;
			float fz = (float)z - (float)HEIGHT / 2.0f;
			float v = gen.getTerrainHeight(x / scale, z / scale);
			
			v /= 150;
			
			data[z * WIDTH + x] = (unsigned char)(v * 255);
		}
	}
	
	stbi_write_bmp("noise.bmp", WIDTH, HEIGHT, 1, data);

	return (0);
}