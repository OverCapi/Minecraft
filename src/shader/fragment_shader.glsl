#version 330 core

out vec4 FragColor;

in vec2	texCoord;
in vec2	BlockId;

uniform sampler2DArray blockTexture;

void	main()
{
	// FragColor = vec4(texCoord, 0, 1);
	FragColor = texture(blockTexture, vec3(texCoord, BlockId));
}