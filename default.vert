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

// Imports the camera matrix from the main function
uniform mat4 camMatrix;

void main()
{
   // Outputs the positions/coordinates of all vertices
   gl_Position = camMatrix * vec4(aPos, 1.0);
   // Assigns the color from the vertex data to "color"
   color = aColor;
   // Assigns the texture coordinates from the vertex data
   texCoord = aTex;
}