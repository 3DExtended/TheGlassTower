#pragma once
#include "Engine/Core/AGameObject.h"
#include "Engine/Core/AScene.h"
#include "Engine/Model/ModelStatic.h"
#include "Engine/Shader/ShaderVF.h"
#include "Engine/Texture/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"

class GOSphere : public engine::AGameObject
{
public:
	GOSphere();
	~GOSphere();

private:
	// Create and Destroy
	virtual void create();
	virtual void destroy();

	// Update
	virtual void postUpdate();

	virtual void render(); // REMOVE ME

	// Sphere
	engine::ModelStatic * modelSphere;
	glm::mat4 matSphere;
	glm::vec3 pos;
	glm::quat rot;

	// Base
	engine::Texture2D * texture;
	engine::ShaderVF * shader;
	glm::mat4 proj;
	glm::mat4 view;

	// PhysX
	physx::PxMaterial * gMaterial;
	physx::PxRigidDynamic * pxSphere;
};

