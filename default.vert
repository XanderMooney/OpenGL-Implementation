#version 330 core
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals
layout (location = 3) in vec3 aNormal;

// outputs the color
out vec3 color;
// output the texture coords to fragment shader
out vec2 texCoord;
// outputs normals for frag shader
out vec3 Normal;
out vec3 crntPos;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));

   // Outputs the positions/coordinates of all vertices
   gl_Position = camMatrix * vec4(crntPos, 1.0);
   // Assigns the color from the vertex data to "color"
   color = aColor;
   // Assigns the texture coordinates from the vertex data
   texCoord = aTex;
   Normal = aNormal;
}