#include "ModelStatic.h"

namespace engine
{
	ModelStatic::ModelStatic(Mesh * mesh)
	{
		size = (uint32_t)mesh->getIndex()->size();

		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		glGenBuffers(1, &vertexID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexID);

		glGenBuffers(1, &normalID);
		glBindBuffer(GL_ARRAY_BUFFER, normalID);

		glGenBuffers(1, &textureID);
		glBindBuffer(GL_ARRAY_BUFFER, textureID);

		glGenBuffers(1, &indexID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);

		// Vertex
		glBindBuffer(GL_ARRAY_BUFFER, vertexID);
		glBufferData(GL_ARRAY_BUFFER, mesh->getVertex()->size() * sizeof(float), &mesh->getVertex()->front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Normal
		glBindBuffer(GL_ARRAY_BUFFER, normalID);
		glBufferData(GL_ARRAY_BUFFER, mesh->getNormal()->size() * sizeof(float), &mesh->getNormal()->front(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Texture
		glBindBuffer(GL_ARRAY_BUFFER, textureID);
		glBufferData(GL_ARRAY_BUFFER, mesh->getTexture()->size() * sizeof(float), &mesh->getTexture()->front(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Index
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndex()->size() * sizeof(int), &mesh->getIndex()->front(), GL_STATIC_DRAW);

		// Reset
		glBindVertexArray(0);
	}

	ModelStatic::~ModelStatic()
	{
		glDeleteBuffers(1, &indexID);
		glDeleteBuffers(1, &textureID);
		glDeleteBuffers(1, &normalID);
		glDeleteBuffers(1, &vertexID);

		glDeleteVertexArrays(1, &vaoID);
	}

	void ModelStatic::render()
	{
		if (size != 0)
		{
			glBindVertexArray(vaoID);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)0);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
			glBindVertexArray(0);
		}
	}
}