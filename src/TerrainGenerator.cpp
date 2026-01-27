/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerrainGenerator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:16:59 by capi              #+#    #+#             */
/*   Updated: 2026/01/27 02:40:24 by capi             ###   ########.fr       */
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
{
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

float	TerrainGenerator::getTerrainHeight(float x, float z) const
{
	const float continentalness_scale = 16.0f * 30.0f;
	float continentalness = Noise::fractalNoise2D(x / continentalness_scale, z / continentalness_scale, 1, 2.0f, 0.5f);

	continentalness = ((continentalness + 1.0f) / 2.0f) * this->_baseHeightSpline.points.size();
	return (this->_baseHeightSpline.getPointAt(continentalness));
}

float	TerrainGenerator::getTerrainHeightVariation(float x, float z) const
{
	const float variation_scale = 16.0f * 10.0f;
	float variation = Noise::fractalNoise2D(x / variation_scale, z / variation_scale, 1, 2.0f, 0.5f);

	variation = ((variation + 1.0f) / 2.0f) * this->_variationHeightSpline.points.size();
	return (this->_variationHeightSpline.getPointAt(variation));
}