#include "Mesh.h"
#include <sstream>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

namespace engine
{
	Mesh::Mesh()
	{
		// Create
		vertex = new std::vector<float>();
		normal = new std::vector<float>();
		texture = new std::vector<float>();
		index = new std::vector<uint32_t>();
	}

	Mesh::~Mesh()
	{
		// Delete
		delete vertex;
		delete normal;
		delete texture;
		delete index;
	}

	uint32_t Mesh::addVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texture, bool optimize)
	{
		// Scan for Vertex
		if (optimize)
		{
			// Check All
			for (uint32_t i = 0; i < this->texture->size() / 2; i++)
			{
				// Vertex
				if (this->vertex->at(i * 3) == position.x)
				{
					if (this->vertex->at(i * 3 + 1) == position.y)
					{
						if (this->vertex->at(i * 3 + 2) == position.z)
						{
							// Normal
							if (this->normal->at(i * 3) == normal.x)
							{
								if (this->normal->at(i * 3 + 1) == normal.y)
								{
									if (this->normal->at(i * 3 + 2) == normal.z)
									{
										// Texture
										if (this->texture->at(i * 2) == texture.x)
										{
											if (this->texture->at(i * 2 + 1) == texture.y)
											{
												// FOUND!
												return i;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		// Add Vertex
		this->vertex->push_back(position.x);
		this->vertex->push_back(position.y);
		this->vertex->push_back(position.z);

		this->normal->push_back(normal.x);
		this->normal->push_back(normal.y);
		this->normal->push_back(normal.z);

		this->texture->push_back(texture.x);
		this->texture->push_back(texture.y);

		// Return ID
		return this->texture->size() / 2 - 1;
	}

	void Mesh::addTriangle(uint32_t indexA, uint32_t indexB, uint32_t indexC)
	{
		// Add Triangle
		index->push_back(indexA);
		index->push_back(indexB);
		index->push_back(indexC);
	}
	std::vector<float>* Mesh::getVertex()
	{
		return vertex;
	}
	std::vector<float>* Mesh::getNormal()
	{
		return normal;
	}
	std::vector<float>* Mesh::getTexture()
	{
		return texture;
	}
	std::vector<uint32_t>* Mesh::getIndex()
	{
		return index;
	}
	void Mesh::loadOBJ(std::string path)
	{
		// Data
		std::vector<glm::vec3> objVert;
		std::vector<glm::vec3> objNorm;
		std::vector<glm::vec2> objTex;

		// Open File
		std::ifstream file;
		file.open(path.c_str());

		// Loop Lines
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == 'v')
			{
				// Vertex
				if (line[1] == ' ') {
					std::vector<std::string> part = split(line, ' ');
					objVert.push_back(glm::vec3(std::stof(part[1]), std::stof(part[2]), std::stof(part[3])));
				}
				// Normal
				if (line[1] == 'n') {
					std::vector<std::string> part = split(line, ' ');
					objNorm.push_back(glm::vec3(std::stof(part[1]), std::stof(part[2]), std::stof(part[3])));
				}
				// Texture
				if (line[1] == 't') {
					std::vector<std::string> part = split(line, ' ');
					objTex.push_back(glm::vec2(std::stof(part[1]), std::stof(part[2])));
				}
			}
			// Face
			if (line[0] == 'f')
			{
				std::vector<std::string> part = split(line, ' ');
				// Vertex 1
				std::vector<std::string> subA = split(part[1], '/');
				int a = addVertex(objVert[std::stoi(subA[0]) - 1], objNorm[std::stoi(subA[2]) - 1], objTex[std::stoi(subA[1]) - 1]);
				// Vertex 2
				std::vector<std::string> subB = split(part[2], '/');
				int b = addVertex(objVert[std::stoi(subB[0]) - 1], objNorm[std::stoi(subB[2]) - 1], objTex[std::stoi(subB[1]) - 1]);
				// Vertex 3
				std::vector<std::string> subC = split(part[3], '/');
				int c = addVertex(objVert[std::stoi(subC[0]) - 1], objNorm[std::stoi(subC[2]) - 1], objTex[std::stoi(subC[1]) - 1]);
				// Face
				addTriangle(a, b, c);
			}
		}

		// Close File
		file.close();
	}
}