/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:47:28 by capi              #+#    #+#             */
/*   Updated: 2026/01/21 22:56:21 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Noise.hpp"
#include <iostream>
#include <glm/glm.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 1000
#define HEIGHT 1000

int main(void)
{
	unsigned char data[WIDTH * HEIGHT] = {0};

	for (size_t z = 0; z < HEIGHT; z++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			float v = Noise::perlin_noise_2D(glm::vec2(-(float)x / 16.0f * 5, -(float)z / 16.0f * 5), 6, 1.25f, 0.3f);
			v = (v + 1.0) / 2.0;
			data[z * WIDTH + x] = (unsigned char)(v * 255);
		}
	}
	
	stbi_write_bmp("noise.bmp", WIDTH, HEIGHT, 1, data);

	return (0);
}