#pragma once
#include "AModel.h"
#include "Mesh.h"

namespace engine
{
	class ModelStatic : public AModel
	{
	public:
		ModelStatic(Mesh *);
		~ModelStatic();

		void render();
	private:
		GLuint vaoID, vertexID, normalID, textureID, indexID;
		uint32_t size;
	};
}