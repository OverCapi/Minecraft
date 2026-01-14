/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 22:57:54 by capi              #+#    #+#             */
/*   Updated: 2026/01/14 23:20:27 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <stdexcept>

# include <GLFW/glfw3.h>

class Window
{
	public:
		Window(const char *title, int width, int height);
		~Window(void);

		GLFWwindow*	getGLFWWindow(void) const;
	private:
		GLFWwindow*	_glfwWindow;
};

#endif