#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 worldPos;

out vec4 vertexColor;

uniform mat4 mode;
uniform mat4 view;
uniform mat4 projection;

//*
//*	V clip = Mprojection·Mview·Mmodel·V local
//*

void	main()
{
	mat4 model = mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		worldPos.x, worldPos.y, worldPos.z, 1
	);
	gl_Position = projection * view * model * vec4(vertexPos, 1.0);
	vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
}