#pragma once
#include "Engine/Core/AGame.h"
#include "Engine\Model\ModelStatic.h"
#include "Engine\Shader\ShaderVF.h"
#include "Engine\Texture\Texture2D.h"
#include "glm\gtc\matrix_transform.hpp"

class GameTest : public engine::AGame
{
public:
	// Constructor
	GameTest();
	~GameTest();

	// Some Init
	virtual void create() override;
	virtual void destroy() override;
	virtual void update() override;
	virtual void render() override;

private:
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

