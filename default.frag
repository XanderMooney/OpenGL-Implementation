#version 330 core
out vec4 FragColor;

// Imports the current position from the Vertex shader
in vec3 crntPos;
// Imports the normal from the Vertex shader
in vec3 Normal;
// Imports the color from the vertex shader
in vec3 color;
// Imports the texture coordinates from vertex shader
in vec2 texCoord;

// gets the texture unit
uniform sampler2D diffuse0;

uniform sampler2D specular0;
// Gets the color / pos of the light from the main function
uniform vec4 lightColor;
uniform vec3 lightPos;
// gets the camera position
uniform vec3 camPos;

vec4 pointLight() 
{
	vec3 lightVec = lightPos - crntPos;
	
	// intensity of the light based on distance
	float dist = length(lightVec);
	float a = 0.05;
	float b = 0.01;
	float intensity = 1.0f / (a * dist * dist + b * dist +1.0f);
	
	// ambient lighting to prevent completely dark spots
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * lightColor * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

vec4 globalLight()
{
	// ambient lighting to prevent completely dark spots
	float ambient = 0.20f;
	
	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	
	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	// controls how big the light cone is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting to prevent completely dark spots
	float ambient = 0.20f;
	
	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);
	
	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

void main()
{
	// outputs the final color
    FragColor = globalLight();
}