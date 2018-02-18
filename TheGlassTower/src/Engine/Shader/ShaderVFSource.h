#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <glm\gtc\type_ptr.hpp>


namespace engine
{
	class ShaderVFSource
	{
	public:
		ShaderVFSource(std::string, std::string);
		~ShaderVFSource();

		std::string & getVertexSource();
		std::string & getFragmentSource();
	private:
		std::string vertexSource;
		std::string fragmentSource;
	};
}