#ifndef GLFW_WRAPPER_HPP
# define GLFW_WRAPPER_HPP

# include <glad/glad.h>
# include <GLFW/glfw3.h>

# include <iostream>

class GLFW_Wrapper
{
	public:
		GLFW_Wrapper(void);
		~GLFW_Wrapper(void);

		GLFWwindow* create_window(int width, int height, const char *title) const;
};

#endif