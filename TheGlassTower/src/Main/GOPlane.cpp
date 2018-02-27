#include "GOPlane.h"


GOPlane::GOPlane()
{
}

GOPlane::~GOPlane()
{
}

void GOPlane::create()
{
	// Model
	engine::Mesh * mesh = new engine::Mesh();
	mesh->loadOBJ("res/Model/plane.obj");
	modelPlane = new engine::ModelStatic(mesh);
	delete mesh;

	// Shader
	engine::ShaderVFSource * shaderSource = new engine::ShaderVFSource("res/Shader/base.vert", "res/Shader/base.frag");
	shader = new engine::ShaderVF();
	shader->create(shaderSource);
	delete shaderSource;

	// Texture
	engine::Texture2DSource * textureSource = new engine::Texture2DSource("res/Texture/default.png");
	texture = new engine::Texture2D();
	texture->create(textureSource);
	delete textureSource;

	// Matrix
	view = glm::lookAt(glm::vec3(0.0f, 4.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	proj = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	// PhysX
	gMaterial = getScene()->getGame()->getEngine()->getPhysics()->createMaterial(0.5f, 0.5f, 0.6f);
	groundPlane = physx::PxCreatePlane(*getScene()->getGame()->getEngine()->getPhysics(), physx::PxPlane(0,1,0,0), *gMaterial);
	getScene()->getPScene()->m_pxScene->addActor(*groundPlane);
}

void GOPlane::destroy()
{
	// PhysX
	getScene()->getPScene()->m_pxScene->removeActor(*groundPlane);
	groundPlane->release();
	gMaterial->release();

	// Texture
	texture->destroy();
	delete texture;

	// Shader
	shader->destroy();
	delete shader;

	// Model
	delete modelPlane;
}

void GOPlane::render()
{
	// Shader
	shader->bind();
	shader->pushInt("baseTex", 0);
	texture->bind(0);

	// Plane
	shader->pushMatrix("matTrans", proj * view);
	modelPlane->render();

	// Shader
	texture->unbind(0);
	shader->unbind();
}
