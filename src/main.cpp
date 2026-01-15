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
#include "Block.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace GL_Wrapper;

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
	glfwSwapInterval(1); // Enable vsync

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

void	render_imgui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool	cameraOpen = false;
	ImGui::Begin("Camera", &cameraOpen, 0);
	
	ImGui::End();

	// Usefull to knowing all feature of ImGui
	// ImGui::ShowDemoWindow();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void	render(Camera& camera, VertexArray& va, Shader& shader)
{
	camera.send_gpu(shader);
	camera.update_vector();
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.use();
	va.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	va.unbind();
}

# define SPEED 2.5f

void	process_input(float dt, GLFWwindow *window, Camera& camera)
{
	const float speed = SPEED * dt;
	// std::cout << "speed: " << speed << std::endl;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.getPos() += camera.getDir() * (speed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.getPos() -= camera.getDir() * (speed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.getPos() -= glm::normalize(camera.getRight()) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.getPos() += glm::normalize(camera.getRight()) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.getPos() += glm::normalize(camera.getUp()) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.getPos() -= glm::normalize(camera.getUp()) * speed;
	}
}

int	main(void)
{
	try
	{
		Window window = init();

		glViewport(0, 0, WIDTH*2, HEIGHT*2);

		Shader shader("src/shader/vertex_shader.glsl", "src/shader/fragment_shader.glsl");

		Camera camera(glm::vec3(0, 0, 0), 90, 0);

		Block	block(GRASS_BLOCK, glm::vec3(0, 0, 10));

		std::array<BlockVertex, 36>block_data = block.getVerticesData();

		VertexBuffer vb(block_data.data(), block_data.size() * sizeof(BlockVertex));
		VertexArray va;

		Layout layout_vpos = {GL_FLOAT, 3, GL_FALSE};
		Layout layout_wpos = {GL_FLOAT, 3, GL_FALSE};
		BufferLayout buffer_layout;
		buffer_layout.addLayout(layout_vpos);
		buffer_layout.addLayout(layout_wpos);

		va.AddVertexBuffer(vb, buffer_layout);

		float delta_time = 0.0f;
		float last_frame = 0.0f;
		while (!glfwWindowShouldClose(window.getGLFWWindow()))
		{
			glfwPollEvents();

			float current_frame = glfwGetTime();
			delta_time = current_frame - last_frame;
			last_frame = current_frame;

			process_input(delta_time, window.getGLFWWindow(), camera);

			render(camera, va, shader);
	
			render_imgui();
			
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