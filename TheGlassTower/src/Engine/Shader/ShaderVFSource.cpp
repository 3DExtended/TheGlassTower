#include "ShaderVFSource.h"

namespace engine
{
	ShaderVFSource::ShaderVFSource(std::string vertexPath, std::string fragmentPath)
	{
		// Vertex
		vertexSource = "";
		std::ifstream vertex_shader_stream(vertexPath, std::ios::in);
		if (vertex_shader_stream.is_open())
		{
			std::string line = "";
			while (getline(vertex_shader_stream, line))
			{
				vertexSource += line + "\n";
			}
			vertex_shader_stream.close();
		}
		else
		{
			std::cout << "Impossible to open " << vertexPath << "." << std::endl;
			return;
		}

		// Fragment
		fragmentSource = "";
		std::ifstream fragment_shader_stream(fragmentPath, std::ios::in);
		if (fragment_shader_stream.is_open())
		{
			std::string line = "";
			while (getline(fragment_shader_stream, line))
			{
				fragmentSource += line + "\n";
			}
			fragment_shader_stream.close();
		}
		else
		{
			std::cout << "Impossible to open " << fragmentSource << "." << std::endl;
			return;
		}
	}

	ShaderVFSource::~ShaderVFSource()
	{
	}

	std::string & ShaderVFSource::getVertexSource()
	{
		return vertexSource;
	}

	std::string & ShaderVFSource::getFragmentSource()
	{
		return fragmentSource;
	}
}