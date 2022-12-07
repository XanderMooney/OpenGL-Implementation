#version 330 core
out vec4 FragColor;

// Imports the color from the vertex shader
in vec3 color;
// Imports the texture coordinates from vertex shader
in vec2 texCoord;

// Imports the normal from the Vertex shader
in vec3 Normal;
// Imports the current position from the Vertex shader
in vec3 crntPos;

// gets the texture unit
uniform sampler2D tex0;
// Gets the color / pos of the light from the main function
uniform vec4 lightColor;
uniform vec3 lightPos;
// gets the camera position
uniform vec3 camPos;

void main()
{
	// ambient lighting to prevent completely dark spots
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

}