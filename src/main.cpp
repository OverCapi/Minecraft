# include <iostream>

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GL_Wrapper/GL_Wrapper.hpp"

#include "Window.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "World.hpp"

#define WIDTH 1920
#define HEIGHT 1080

float speed = 10.0f;

using namespace GL_Wrapper;

glm::vec2 mouse_pos = glm::vec2(WIDTH / 2, HEIGHT / 2);

void	window_resize_callback(GLFWwindow *window, int width, int heigh)
{
	(void)window;
	glViewport(0, 0, width, heigh);
}

void	mouse_move_callback(GLFWwindow *window, double xpos, double ypos)
{
	(void)window;
	mouse_pos.x = xpos;
	mouse_pos.y = ypos;
}

Window	init(void)
{
	// * Initialize GLFW Context
	if (glfwInit() != GLFW_TRUE)
		throw std::runtime_error("Error glfw_init()");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// * =========================================================

	Window window("ft_minecraft", WIDTH, HEIGHT);
	// Make the OpenGL context current
	glfwMakeContextCurrent(window.getGLFWWindow());
	glfwSwapInterval(0); // Enable vsync

	glfwSetInputMode(window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowSizeCallback(window.getGLFWWindow(), window_resize_callback);
	glfwSetCursorPosCallback(window.getGLFWWindow(), mouse_move_callback);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window.getGLFWWindow(), true);	// Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init("#version 330");

	// * Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD");

	return (window);
}

void	render_imgui(Camera& camera, float delta_time, float render_time)
{
	static size_t	fps_sum = 0;
	static size_t	nb_call = 1;

	fps_sum += (size_t)(1 / delta_time);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (fps_sum > 0xF000000000000000)
	{
		fps_sum = 0;
		nb_call = 0;
	}

	static bool	debug = false;
	ImGui::Begin("Debug", &debug, 0);

	ImGui::Text("Avg: %zu, FPS: %g", fps_sum / nb_call++, 1 / delta_time);
	ImGui::Text("Render time: %g ms", render_time * 1000);

	if (ImGui::CollapsingHeader("Camera"))
	{
		glm::vec3	cam_pos = camera.getPos();
		ImGui::Text("Position: (%g, %g, %g)", cam_pos.x, cam_pos.y, cam_pos.z);
	
		glm::vec3	cam_dir = camera.getDir();
		ImGui::Text("Direction: (%g, %g, %g)", cam_dir.x, cam_dir.y, cam_dir.z);

		glm::vec3	cam_right = camera.getRight();
		ImGui::Text("Right: (%g, %g, %g)", cam_right.x, cam_right.y, cam_right.z);

		glm::vec3	cam_up = camera.getUp();
		ImGui::Text("Up: (%g, %g, %g)", cam_up.x, cam_up.y, cam_up.z);

		ImGui::SliderFloat("Speed", &speed, 0, 10);
	}
	ImGui::End();

	// Usefull to knowing all feature of ImGui
	// ImGui::ShowDemoWindow();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

# define SPEED 2.5f

void	process_input(float dt, GLFWwindow *window, Camera& camera)
{
	float velocity = speed * dt;
	// std::cout << "velocity: " << velocity << std::endl;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.getPos() += camera.getDir() * (velocity);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.getPos() -= camera.getDir() * (velocity);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.getPos() -= glm::normalize(camera.getRight()) * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.getPos() += glm::normalize(camera.getRight()) * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.getPos() += glm::normalize(camera.getUp()) * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.getPos() -= glm::normalize(camera.getUp()) * velocity;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
	{
		static bool lock_cursor = true;
		glfwSetInputMode(window, GLFW_CURSOR, lock_cursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_CAPTURED);
		lock_cursor = !lock_cursor;
	}
}

void	update_dir(Camera& camera)
{
	static float lastX = mouse_pos.x;
	static float lastY = mouse_pos.y;

	if (mouse_pos.x == lastX && mouse_pos.y == lastY)
		return ;
	float xoffset = mouse_pos.x - lastX;
	float yoffset = lastY - mouse_pos.y;
	
	lastX = mouse_pos.x;
	lastY = mouse_pos.y;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.getYaw() += xoffset;
	camera.getPitch() += yoffset;
	if(camera.getPitch() > 89.0f)
		camera.getPitch() = 89.0f;
	if(camera.getPitch() < -89.0f)
		camera.getPitch() = -89.0f;

	camera.update_vector();
}

int	main(void)
{
	try
	{
		Window window = init();

		GLCallThrow(glEnable(GL_DEPTH_TEST));

		glViewport(0, 0, WIDTH*2, HEIGHT*2);

		Renderer renderer;

		Camera camera(glm::vec3(0, 20, 0), 90, 0);
		World world(camera);

		float delta_time = 0.0f;
		float last_frame = 0.0f;
		while (!glfwWindowShouldClose(window.getGLFWWindow()))
		{
			glfwPollEvents();

			float current_frame = glfwGetTime();
			delta_time = current_frame - last_frame;
			last_frame = current_frame;

			process_input(delta_time, window.getGLFWWindow(), world.getCamera());
			update_dir(world.getCamera());

			world.update(delta_time);

			float start_render = glfwGetTime();
			renderer.render(world);
			float end_render = glfwGetTime();

			// render(camera, shader, texture, chunk);
	
			render_imgui(camera, delta_time, end_render - start_render);
			
			glfwSwapBuffers(window.getGLFWWindow());
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		
		return (0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}