/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ElementBuffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:58:10 by capi              #+#    #+#             */
/*   Updated: 2026/01/12 17:52:04 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTBUFFER_HPP
# define ELEMENTBUFFER_HPP

# include "GL_Wrapper/Macro.hpp"

namespace GL_Wrapper
{
	class ElementBuffer
	{
		public:
			ElementBuffer(const unsigned int *data, size_t count);
			~ElementBuffer(void);

			void	bind(void) const;
			void	unbind(void) const;
		private:
			unsigned int	_id;
	};
} // namespace GL_Wrapper


#endif