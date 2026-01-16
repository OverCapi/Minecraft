/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture2DArray.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:03:25 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 22:16:15 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE2DARRAY_HPP
# define TEXTURE2DARRAY_HPP

# include "stbi_image.hpp"

# include "GL_Wrapper/Macro.hpp"

namespace GL_Wrapper
{
	class Texture2DArray
	{
		public:
			Texture2DArray(unsigned int tile_width, unsigned int tile_height, unsigned int image_count, GLenum format);
			~Texture2DArray(void);

			void	addTexture(const char *filename, GLenum format, bool flip_on_load);

			void	bind(void) const;
			void	unbind(void) const;
			void	use(unsigned int index) const;
		private:
			unsigned int	_id;
			unsigned int	_tileWidth;
			unsigned int	_tileHeight;
			unsigned int 	_maxImageCount;
			unsigned int 	_imageCount;
	};
};

#endif