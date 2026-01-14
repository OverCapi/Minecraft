/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexArray.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:03:36 by capi              #+#    #+#             */
/*   Updated: 2026/01/12 17:52:01 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXARRAY_HPP
# define VERTEXARRAY_HPP

# include "GL_Wrapper/Macro.hpp"
# include "GL_Wrapper/BufferLayout.hpp"
# include "GL_Wrapper/VertexBuffer.hpp"
# include "GL_Wrapper/ElementBuffer.hpp"

namespace GL_Wrapper
{
	class VertexArray
	{
		public:
			VertexArray(void);
			~VertexArray(void);

			void	bind(void) const;
			void	unbind(void) const;
			
			void	AddVertexBuffer(const VertexBuffer& vertexBuffer, BufferLayout& bufferLayout);
			void	AddElementBuffer(const ElementBuffer& elementBuffer);
		private:
			unsigned int	_id;
	};
}

#endif