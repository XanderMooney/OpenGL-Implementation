#version 330 core
out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 color;
// Inputs the texture coordinates from vertex shader
in vec2 texCoord;
// gets the texture unit
uniform sampler2D tex0;

in vec3 Normal;
in vec3 crntPos;

uniform vec4 lightColor;

uniform vec3 lightPos;

void main()
{
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient);
}