#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D ourTexture;
uniform bool textureOn;

void main()
{
	if (textureOn)
	{
		FragColor = texture(ourTexture, ourTexCoord);
	}
	else
	{
		FragColor = vec4(ourColor, 1.0);
	}
}