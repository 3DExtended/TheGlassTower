#include "Texture2D.h"

namespace engine
{
	Texture2D::Texture2D()
	{
	}

	Texture2D::~Texture2D()
	{
		if (textureID != 0)
			destroy();
	}

	void Texture2D::create(Texture2DSource * source)
	{
		// Generate Texture
		glGenTextures(1, &textureID);

		// Bind
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Border
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Load Texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, source->getWidth(), source->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &source->getBuffer().front());

		// Reset
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::destroy()
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}

	void Texture2D::bind(uint32_t num)
	{
		glActiveTexture(GL_TEXTURE0 + num);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Texture2D::unbind(uint32_t num)
	{
		glActiveTexture(GL_TEXTURE0 + num);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}