#version 330 core
layout (location = 0) in vec3 aPos;
// Normals
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


out vec3 crntPos;
// outputs normals for frag shader
out vec3 Normal;
// outputs the color
out vec3 color;
// output the texture coords to fragment shader
out vec2 texCoord;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));
	Normal = aNormal;
   // Assigns the color from the vertex data to "color"
   color = aColor;
   // Assigns the texture coordinates from the vertex data
   texCoord = aTex;
   // Outputs the positions/coordinates of all vertices
   gl_Position = camMatrix * vec4(crntPos, 1.0);
}