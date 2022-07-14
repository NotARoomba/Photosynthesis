#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture;
uniform bool textureOn;
uniform vec3 color;

void main()
{
if(textureOn)
	{
		FragColor = texture2D(texture, TexCoord);
	}
	else
	{
		FragColor = vec4(color, 1.0);
	}

}