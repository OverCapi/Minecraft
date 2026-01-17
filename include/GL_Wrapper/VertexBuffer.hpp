/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuffer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:40:33 by capi              #+#    #+#             */
/*   Updated: 2026/01/17 16:53:47 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXBUFFER_HPP
# define VERTEXBUFFER_HPP

# include "GL_Wrapper/Macro.hpp"

namespace GL_Wrapper
{
	class VertexBuffer
	{
		public:
			VertexBuffer(void) {};
			VertexBuffer(const void *data, size_t size);
			~VertexBuffer(void);

			void	bind(void) const;
			void	unbind(void) const;
		private:
			unsigned int	_id;
	};
}; // namespace GL_Wrapper

#endif