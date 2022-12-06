#version 330 core
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;

// outputs the color
out vec3 color;
// output the texture coords to fragment shader
out vec2 texCoord;
// Controls the scale of the vertices
uniform float scale;

void main()
{
   // Outputs the positions/coordinates of all vertices
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   // Assigns the color from the vertex data to "color"
   color = aColor;
   // Assigns the texture coordinates from the vertex data
   texCoord = aTex;
}