#pragma once
#include "Engine/Core/AGameObject.h"
#include "Engine/Model/ModelStatic.h"
#include "Engine/Shader/ShaderVF.h"
#include "Engine/Texture/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"

class GOPlane : public engine::AGameObject
{
public:
	GOPlane();
	~GOPlane();

private:
	// Create and Destroy
	virtual void create();
	virtual void destroy();

	virtual void render(); // REMOVE ME

	// Plane
	engine::ModelStatic * modelPlane;

	// Base
	engine::Texture2D * texture;
	engine::ShaderVF * shader;
	glm::mat4 proj;
	glm::mat4 view;

	// PhysX
	physx::PxMaterial * gMaterial;
	physx::PxRigidStatic * groundPlane;
};

