#pragma once
#include "AModel.h"
#include "Mesh.h"

namespace engine
{
	class ModelDynamic : public AModel
	{
	public:
		ModelDynamic();
		~ModelDynamic();

		void create(Mesh *);

		void render();
	private:
		GLuint vaoID, vertexID, normalID, textureID, indexID;
		uint32_t size;
	};
}