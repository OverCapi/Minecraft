/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capi <capi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 22:59:27 by capi              #+#    #+#             */
/*   Updated: 2026/01/14 23:20:17 by capi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"

Window::Window(const char *title, int width, int height)
{
	this->_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!this->_glfwWindow)
		throw std::runtime_error("Failed to create GLFW window.");
}

Window::~Window(void)
{
	glfwTerminate();
}

GLFWwindow*	Window::getGLFWWindow(void) const
{
	return (this->_glfwWindow);
}