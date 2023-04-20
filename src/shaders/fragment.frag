#version 330 core
in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform bool hasTexture;


void main() {
    if (!hasTexture) FragColor = vec4(vertexColor, 1.0);
    else FragColor = texture(ourTexture, TexCoord);
    
}
