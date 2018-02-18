#pragma once
#include "Texture2DSource.h"

namespace engine
{
	class Texture2D
	{
	public:
		Texture2D();
		~Texture2D();

		void create(Texture2DSource * source);
		void destroy();

		void bind(uint32_t = 0);
		void unbind(uint32_t = 0);

	private:
		GLuint textureID = 0;
	};
}