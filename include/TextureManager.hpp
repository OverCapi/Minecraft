/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:13:21 by capi              #+#    #+#             */
/*   Updated: 2026/01/24 14:39:25 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTUREMANAGER_HPP
# define TEXTUREMANAGER_HPP

# include "GL_Wrapper/Texture2DArray.hpp"

class TextureManager
{
	public:
		static GL_Wrapper::Texture2DArray	_textures;

		void	instanciateTexture(unsigned int);
};

#endif