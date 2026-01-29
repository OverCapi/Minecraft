/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerrainGenerator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:16:59 by capi              #+#    #+#             */
/*   Updated: 2026/01/29 02:25:16 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TerrainGenerator.hpp"

void	Spline::addPoint(float point, float value)
{
	this->points.push_back(point);
	this->value.push_back(value);
}

float	Spline::getPointAt(float t) const
{
	size_t start_index = (int)floorf(t);

	float dist = t - start_index;

	size_t size = this->value.size();

	return (Utils::cubic_interpolate(this->value[start_index % size], this->value[(start_index + 1) % size], dist));
}

TerrainGenerator::TerrainGenerator(void)
: _continentalness(NoiseParam(4, 2.0f, 0.5f, CHUNK_SIZE * 30.0f)),
_heightVariationScale(NoiseParam(4, 2.0f, 0.5f, CHUNK_SIZE * 10.0f)),
_heightVariation(NoiseParam(4, 2.0f, 0.5f, CHUNK_SIZE * 10.0f))
{
	this->_maxOctave = this->getMaxOctave();

	this->_baseHeightSpline.addPoint(-1, 80);
	this->_baseHeightSpline.addPoint(0.0, 80);
	this->_baseHeightSpline.addPoint(0.2, 100);
	this->_baseHeightSpline.addPoint(0.5, 125);
	this->_baseHeightSpline.addPoint(0.7, 150);
	this->_baseHeightSpline.addPoint(1.0, 150);

	this->_variationHeightSpline.addPoint(-1, 20);
	this->_variationHeightSpline.addPoint(-0.5, 20);
	this->_variationHeightSpline.addPoint(0.0, 40);
	this->_variationHeightSpline.addPoint(0.4, 60);
	this->_variationHeightSpline.addPoint(0.5, 60);
	this->_variationHeightSpline.addPoint(0.7, 30);
	this->_variationHeightSpline.addPoint(1.0, 30);
}

TerrainGenerator::~TerrainGenerator(void) {}

float	TerrainGenerator::getTerrainShape(float x, float y) const
{
	float continentalness = 0;
	const float continentalness_x = x / this->_continentalness.zoom;
	const float continentalness_y = y / this->_continentalness.zoom;
	float continentalness_frequence = 1.0f;
	float continentalness_amplitude = 1.0f;
	float continentalness_sum_amplitude = 0.0f;
	
	float heightVariationScale = 0;
	const float heightVariationScale_x = x / this->_heightVariationScale.zoom;
	const float heightVariationScale_y = y / this->_heightVariationScale.zoom;
	float heightVariationScale_frequence = 1.0f;
	float heightVariationScale_amplitude = 1.0f;
	float heightVariationScale_sum_amplitude = 0.0f;
	
	float heightVariation = 0;
	const float heightVariation_x = x / this->_heightVariation.zoom;
	const float heightVariation_y = y / this->_heightVariation.zoom;
	float heightVariation_frequence = 1.0f;
	float heightVariation_amplitude = 1.0f;
	float heightVariation_sum_amplitude = 0.0f;

	for (uint8_t i = 0; i < this->_maxOctave; i++)
	{
		if (i < this->_continentalness.octave)
		{
			continentalness += Noise::noise2D(continentalness_x * continentalness_frequence, continentalness_y * continentalness_frequence) * continentalness_amplitude;
			continentalness_sum_amplitude += continentalness_amplitude;
			continentalness_frequence *= this->_continentalness.lacunarity;
			continentalness_amplitude *= this->_continentalness.persistence;
		}
		
		if (i < this->_heightVariationScale.octave)
		{
			heightVariationScale += Noise::noise2D(heightVariationScale_x * heightVariationScale_frequence, heightVariationScale_y * heightVariationScale_frequence) * heightVariationScale_amplitude;
			heightVariationScale_sum_amplitude += heightVariationScale_amplitude;
			heightVariationScale_frequence *= this->_heightVariationScale.lacunarity;
			heightVariationScale_amplitude *= this->_heightVariationScale.persistence;
		}

		if (i < this->_heightVariation.octave)
		{
			heightVariation += Noise::noise2D(heightVariation_x * heightVariation_frequence, heightVariation_y * heightVariation_frequence) * heightVariation_amplitude;
			heightVariation_sum_amplitude += heightVariation_amplitude;
			heightVariation_frequence *= this->_heightVariation.lacunarity;
			heightVariation_amplitude *= this->_heightVariation.persistence;
		}
	}
	continentalness /= continentalness_sum_amplitude;
	heightVariationScale /= heightVariationScale_sum_amplitude;
	heightVariation /= heightVariation_sum_amplitude;
	
	continentalness = ((continentalness + 1.0f) / 2.0f) * this->_baseHeightSpline.points.size();
	heightVariationScale = ((heightVariationScale + 1.0f) / 2.0f) * this->_variationHeightSpline.points.size();

	return (this->_baseHeightSpline.getPointAt(continentalness) + heightVariation * this->_variationHeightSpline.getPointAt(heightVariationScale));
}

uint8_t	TerrainGenerator::getMaxOctave(void) const
{
	uint8_t max = this->_continentalness.octave;

	if (this->_heightVariationScale.octave > max) max = this->_heightVariationScale.octave;
	if (this->_heightVariation.octave > max) max = this->_heightVariation.octave;
	return (max);
}

float	TerrainGenerator::getTerrainHeight(float x, float z) const
{
	const float continentalness_scale = 16.0f * 30.0f;
	float continentalness = Noise::fractalNoise2D(x / continentalness_scale, z / continentalness_scale, 4, 2.0f, 0.5f);

	continentalness = ((continentalness + 1.0f) / 2.0f) * this->_baseHeightSpline.points.size();
	return (this->_baseHeightSpline.getPointAt(continentalness));
}

float	TerrainGenerator::getTerrainHeightVariation(float x, float z) const
{
	const float variation_scale = 16.0f * 10.0f;
	float variation = Noise::fractalNoise2D(x / variation_scale, z / variation_scale, 4, 2.0f, 0.5f);

	variation = ((variation + 1.0f) / 2.0f) * this->_variationHeightSpline.points.size();
	return (this->_variationHeightSpline.getPointAt(variation));
}