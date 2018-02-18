#pragma once
#include "ShaderVFSource.h"

namespace engine
{
	class ShaderVF
	{
	public:
		ShaderVF();
		~ShaderVF();

		void create(ShaderVFSource * source);
		void destroy();

		void bind();
		void unbind();

		int getLocation(std::string uniform);

		void pushMatrix(int loc, glm::mat4 matrix);
		void pushMatrix(std::string loc, glm::mat4 matrix);

		void pushInt(int loc, int value);
		void pushInt(std::string loc, int value);

	private:
		int programID = 0;
	};
}