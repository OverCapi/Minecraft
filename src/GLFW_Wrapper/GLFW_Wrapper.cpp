#include "GLFW_Wrapper.hpp"

GLFW_Wrapper::GLFW_Wrapper(void)
{
	if (glfwInit() != GLFW_TRUE)
		throw std::runtime_error("Failed to initialze GLFW");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFW_Wrapper::~GLFW_Wrapper(void)
{
	glfwTerminate();
}

GLFWwindow*	GLFW_Wrapper::create_window(int width, int height, const char *title) const
{
	GLFWwindow*	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
		throw std::runtime_error("Failed to create GLFW window.");
	return (window);
}