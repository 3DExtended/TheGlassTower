#include "GameTest.h"

GameTest::GameTest()
{
}
GameTest::~GameTest()
{
}
void GameTest::create()
{
	// Model
	engine::Mesh * mesh = new engine::Mesh();
	mesh->loadOBJ("res/Model/sphere.obj");
	modelSphere = new engine::ModelStatic(mesh);
	delete mesh;

	mesh = new engine::Mesh();
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
	matSphere = glm::mat4(1.0f);
}
void GameTest::destroy()
{
	// Texture
	texture->destroy();
	delete texture;

	// Shader
	shader->destroy();
	delete shader;

	// Model
	delete modelSphere;
}	
void GameTest::update()
{
	angleSphere += getInput()->getDelta();
}
void GameTest::render()
{
	// Shader
	shader->bind();
	shader->pushInt("baseTex", 0);
	texture->bind(0);

	// Sphere
	matSphere = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f+2.0f*(2.25f - glm::pow(glm::mod(angleSphere, 3.0f)-1.5f,2.0f)), 0.0f)) , angleSphere, glm::vec3(0.0f, 1.0f, 0.0f));
	shader->pushMatrix("matTrans", proj * view * matSphere);
	modelSphere->render();

	// Plane
	shader->pushMatrix("matTrans", proj * view);
	modelPlane->render();

	// Shader
	texture->unbind(0);
	shader->unbind();
}