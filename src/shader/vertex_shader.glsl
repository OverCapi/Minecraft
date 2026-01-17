#version 330 core

layout (location = 0) in vec3	aVertexPos;
layout (location = 1) in vec2 	aTexCoord;
layout (location = 2) in vec3 	aWorldPos;
layout (location = 3) in uint 	aBlockId;

out vec2	texCoord;
out vec2	BlockId;

uniform mat4 mode;
uniform mat4 view;
uniform mat4 projection;

//*
//*	V clip = Mprojection·Mview·Mmodel·V local
//*

void	main()
{
	texCoord = aTexCoord;
	BlockId = vec2(aBlockId, aBlockId);

	mat4 model = mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		aWorldPos.x, aWorldPos.y, aWorldPos.z, 1
	);
	gl_Position = projection * view * model * vec4(aVertexPos, 1.0);
}