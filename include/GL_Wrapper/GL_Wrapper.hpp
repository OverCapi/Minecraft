/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GL_Wrapper.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:39:41 by capi              #+#    #+#             */
/*   Updated: 2026/01/16 22:19:07 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_WRAPPER_HPP
# define GL_WRAPPER_HPP

# include <glad/glad.h>
# include <glm/glm.hpp>
# include <glm/gtc/type_ptr.hpp>

# include <iostream>
# include <stdexcept>

#  define STB_IMAGE_IMPLEMENTATION

# include "GL_Wrapper/Macro.hpp"
# include "GL_Wrapper/VertexBuffer.hpp"
# include "GL_Wrapper/ElementBuffer.hpp"
# include "GL_Wrapper/BufferLayout.hpp"
# include "GL_Wrapper/VertexArray.hpp"
# include "GL_Wrapper/Shader.hpp"
# include "GL_Wrapper/Texture2D.hpp"
# include "GL_Wrapper/Texture2DArray.hpp"

#endif