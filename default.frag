#version 330 core
out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 color;
// Inputs the texture coordinates from vertex shader
in vec2 texCoord;
// gets the texture unit
uniform sampler2D tex0;
void main()
{
   FragColor = texture(tex0, texCoord);
}