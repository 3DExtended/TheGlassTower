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
	// Create and Destroy
	void create();
	void destroy();
};

