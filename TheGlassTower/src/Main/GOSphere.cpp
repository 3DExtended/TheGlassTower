#include "GOSphere.h"

GOSphere::GOSphere()
{
}

GOSphere::~GOSphere()
{
}

void GOSphere::create()
{
	// Model
	engine::Mesh * mesh = new engine::Mesh();
	mesh->loadOBJ("res/Model/sphere.obj");
	modelSphere = new engine::ModelStatic(mesh);
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

	// PhysX
	gMaterial = getScene()->getGame()->getEngine()->getPhysics()->createMaterial(0.5f, 0.5f, 0.6f);
	pxSphere = physx::PxCreateDynamic(*getScene()->getGame()->getEngine()->getPhysics(), physx::PxTransform(physx::PxVec3(0, 10, 0)), physx::PxSphereGeometry(1.0f), *gMaterial, 10.0f);
	getScene()->getPScene()->m_pxScene->addActor(*pxSphere);
}

void GOSphere::destroy()
{
	// PhysX
	getScene()->getPScene()->m_pxScene->removeActor(*pxSphere);
	pxSphere->release();
	gMaterial->release();

	// Texture
	texture->destroy();
	delete texture;

	// Shader
	shader->destroy();
	delete shader;

	// Model
	delete modelSphere;
}

void GOSphere::postUpdate()
{
	physx::PxTransform t = pxSphere->getGlobalPose();
	pos.x = t.p.x;
	pos.y = t.p.y;
	pos.z = t.p.z;
	rot.x = t.q.x;
	rot.y = t.q.y;
	rot.z = t.q.z;
	rot.w = t.q.w;
}

void GOSphere::render()
{
	// Shader
	shader->bind();
	shader->pushInt("baseTex", 0);
	texture->bind(0);

	// Sphere
	matSphere = glm::translate(glm::mat4(1.0f), pos) * glm::mat4_cast(rot);
	shader->pushMatrix("matTrans", proj * view * matSphere);
	modelSphere->render();

	// Shader
	texture->unbind(0);
	shader->unbind();
}
