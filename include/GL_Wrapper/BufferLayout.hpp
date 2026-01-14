/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BufferLayout.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:21:44 by capi              #+#    #+#             */
/*   Updated: 2026/01/12 17:12:56 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERLAYOUT_HPP
# define BUFFERLAYOUT_HPP

# include <vector>

# include "GL_Wrapper/Macro.hpp"

namespace GL_Wrapper
{
	struct Layout
	{
		GLenum		type;
		size_t		count;
		GLboolean	normalized;
	};

	class BufferLayout
	{
		public:
			BufferLayout(void);	
			~BufferLayout(void);

			void						addLayout(const Layout& layout);
			const std::vector<Layout>&	getLayout(void) const;
			size_t						getStride(void) const;
		private:
			std::vector<Layout>	_layouts;
			size_t				_stride;
	};
} // namespace GL_Wrapper


#endif