/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TerrainGenerator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:14:35 by capi              #+#    #+#             */
/*   Updated: 2026/01/27 02:27:52 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAINGENERATOR_HPP
# define TERRAINGENERATOR_HPP

# include "Utils.hpp"
# include "Noise.hpp"

# include <vector>

typedef struct s_spline
{
	std::vector<float>	points;
	std::vector<float>	value;

	void	addPoint(float point, float value);
	float	getPointAt(float t) const;
}	Spline;

class TerrainGenerator
{
	public:
		TerrainGenerator(void);
		~TerrainGenerator(void);

		float	getTerrainHeight(float x, float z) const;
		float	getTerrainHeightVariation(float x, float z) const;
	private:
		Spline	_baseHeightSpline;	
		Spline	_variationHeightSpline;
		
};

#endif