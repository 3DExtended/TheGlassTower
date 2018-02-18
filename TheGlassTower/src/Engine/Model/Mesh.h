#pragma once
#include <vector>
#include <fstream>
#include "glm\glm.hpp"
#include "GL\glew.h"

namespace engine
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		uint32_t addVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture, bool optimize = false);
		void addTriangle(uint32_t indexA, uint32_t indexB, uint32_t indexC);

		std::vector<float> * getVertex();
		std::vector<float> * getNormal();
		std::vector<float> * getTexture();
		std::vector<uint32_t> * getIndex();

		void loadOBJ(std::string path);
	private:

		// Vertex List
		std::vector<float> * vertex;
		std::vector<float> * normal;
		std::vector<float> * texture;

		// Triangle List
		std::vector<uint32_t> * index;

	};
}