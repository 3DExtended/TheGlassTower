#pragma once
#include <string>
#include <vector>
#include "GL\glew.h"

namespace engine
{
	class Texture2DSource
	{
	public:
		Texture2DSource(std::string texturePath);
		~Texture2DSource();

		std::vector<uint8_t>& getBuffer();
		uint32_t getWidth();
		uint32_t getHeight();
	private:
		std::vector<uint8_t> buffer;
		uint32_t width, height;
	};
}