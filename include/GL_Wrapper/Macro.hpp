/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Macro.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:09:50 by capi              #+#    #+#             */
/*   Updated: 2026/01/15 23:36:33 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_HPP
# define MACRO_HPP

# include <iostream>
# include <stdexcept>

# include <glad/glad.h>

// #define DEV

#ifdef DEV
# define GLCall(x)\
GLClearError();\
x;\
return (bool)GLLogCall(#x, __FILE__, __LINE__);
#else
# define GLCall(x) x;
#endif

#ifdef DEV
# define GLCallThrow(x)\
GLClearError();\
x;\
if (!GLLogCall(#x, __FILE__, __LINE__)) {\
	throw std::runtime_error("OpenGL error");\
}
#else
# define GLCallThrow(x) x;
#endif


namespace GL_Wrapper
{
	inline void	GLClearError(void)
	{
		while (glGetError() != GL_NO_ERROR);		
	};

	inline const char	*GLGetErrorMsg(GLenum error)
	{
		switch (error)
		{
			case GL_INVALID_ENUM:
				return ("GL_INVALID_ENUM : An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.");
			case GL_INVALID_VALUE:
				return ("GL_INVALID_VALUE : A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.");
			case GL_INVALID_OPERATION:
				return ("The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.");
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				return ("The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.");
			case GL_OUT_OF_MEMORY:
				return ("There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
		}
		return ("");
	}
	
	inline bool	GLLogCall(const char *function_name, const char *filename, int line)
	{
		while (GLenum error = glGetError())
		{
			std::cerr << "[OpenGL Error] (" << function_name << ") (" << filename << ":" << line << ") "<< GLGetErrorMsg(error) << std::endl;
			return false;
		}
		return true;
	};

	inline size_t	GetTypeSize(GLenum type)
	{
		// TODO ADD MORE TYPE
		switch (type)
		{
			case GL_FLOAT:
				return (sizeof(float));
		}
		throw std::runtime_error("GetTypeSize invalid Type");
		return (0);
	}
};

#endif