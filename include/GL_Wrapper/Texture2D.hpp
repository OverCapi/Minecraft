/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture2D.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:56:25 by capi              #+#    #+#             */
/*   Updated: 2026/01/14 19:37:05 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include "GL_Wrapper/Macro.hpp"

namespace GL_Wrapper
{
	class Texture2D
	{
		public:
			Texture2D(const char *texture_file, GLenum format, bool flip_on_load);
			~Texture2D(void);

			void	bind(void) const;
			void	unbind(void) const;
			void	use(unsigned int index) const;
		private:
			unsigned int	_id;
	};
};

#endif