#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture
{
	public:
		GLuint ID;
		const char* type;
		GLuint unit;
		Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

		// Assigns texture unit to texture
		void texUnit(Shader shader, const char* uniform, GLuint unit);
		// Binds texture
		void Bind();
		// Unbinds texture
		void Unbind();
		// Deletes texture
		void Delete();
};

#endif