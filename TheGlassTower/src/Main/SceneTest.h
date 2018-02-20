#pragma once
#include "Engine/Core/AScene.h"
#include "Engine/Model/ModelStatic.h"
#include "Engine/Shader/ShaderVF.h"
#include "Engine/Texture/Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"

class SceneTest : public engine::AScene
{
public:
	// Constructor
	SceneTest();
	~SceneTest();

private:

	// Loop
	void update();
	void render();

	// Create and Destroy
	void create();
	void destroy();

	// Sphere
	engine::ModelStatic * modelSphere;
	glm::mat4 matSphere;
	float angleSphere = 0.0f;

	// Plane
	engine::ModelStatic * modelPlane;
	glm::mat4 matPlane;

	// Base
	engine::Texture2D * texture;
	engine::ShaderVF * shader;
	glm::mat4 proj;
	glm::mat4 view;
};

