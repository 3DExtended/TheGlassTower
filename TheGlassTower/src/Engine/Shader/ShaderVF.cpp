#include "ShaderVF.h"

namespace engine
{
	ShaderVF::ShaderVF()
	{
	}

	ShaderVF::~ShaderVF()
	{
		if (programID != 0)
			destroy();
	}

	void ShaderVF::create(ShaderVFSource * source)
	{
		// Logging
		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Vertex
		GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
		char const * VertexSourcePointer = source->getVertexSource().c_str();
		glShaderSource(vertexID, 1, &VertexSourcePointer, NULL);
		glCompileShader(vertexID);
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(vertexID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}

		// Fragment
		GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		char const * FragmentSourcePointer = source->getFragmentSource().c_str();
		glShaderSource(fragmentID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(fragmentID);
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(fragmentID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}

		// Program
		programID = glCreateProgram();
		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);
		glLinkProgram(programID);
		glGetProgramiv(programID, GL_LINK_STATUS, &Result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}

		// CleanUp
		glDetachShader(programID, vertexID);
		glDetachShader(programID, fragmentID);
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}

	void ShaderVF::destroy()
	{
		unbind();
		glDeleteProgram(programID);
		programID = 0;
	}

	void ShaderVF::bind()
	{
		glUseProgram(programID);
	}

	void ShaderVF::unbind()
	{
		glUseProgram(0);
	}

	int ShaderVF::getLocation(std::string uniform)
	{
		return glGetUniformLocation(programID, uniform.c_str());
	}

	void ShaderVF::pushMatrix(int loc, glm::mat4 matrix)
	{
		glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
	}

	void ShaderVF::pushMatrix(std::string loc, glm::mat4 matrix)
	{
		pushMatrix(getLocation(loc), matrix);
	}

	void ShaderVF::pushInt(int loc, int value)
	{
		glUniform1i(loc, value);
	}

	void ShaderVF::pushInt(std::string loc, int value)
	{
		pushInt(getLocation(loc), value);
	}
}