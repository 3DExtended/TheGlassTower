#include "Texture2DSource.h"
#include "_ThirdParty/lodepng.h"

namespace engine
{
	Texture2DSource::Texture2DSource(std::string texturePath)
	{
		lodepng::decode(buffer, width, height, texturePath);
	}

	Texture2DSource::~Texture2DSource()
	{
	}

	std::vector<unsigned char>& Texture2DSource::getBuffer()
	{
		return buffer;
	}

	unsigned int Texture2DSource::getWidth()
	{
		return width;
	}

	unsigned int Texture2DSource::getHeight()
	{
		return height;
	}
}