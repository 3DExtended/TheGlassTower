#include "GOCapsule.h"



GOCapsule::GOCapsule()
{
}


GOCapsule::~GOCapsule()
{
}

void GOCapsule::create()
{
	// Model
	engine::Mesh * mesh = new engine::Mesh();
	mesh->loadOBJ("res/Model/capsule.obj");
	modelCapsule = new engine::ModelStatic(mesh);
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
	matCapsule = glm::mat4(1.0f);

	// PhysX
	gMaterial = getScene()->getGame()->getEngine()->getPhysics()->createMaterial(0.5f, 0.5f, 0.6f);
	pxCapsule = getScene()->getGame()->getEngine()->getPhysics()->createRigidDynamic(physx::PxTransform(physx::PxVec3(0,1,0)));
	physx::PxTransform relativePose(physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	physx::PxShape* aCapsuleShape = physx::PxRigidActorExt::createExclusiveShape(*pxCapsule, physx::PxCapsuleGeometry(0.5f,0.5f), *gMaterial);
	aCapsuleShape->setLocalPose(relativePose);
	physx::PxRigidBodyExt::updateMassAndInertia(*pxCapsule, 1.0f);
	getScene()->getPScene()->m_pxScene->addActor(*pxCapsule);
}

void GOCapsule::destroy()
{
	// PhysX
	getScene()->getPScene()->m_pxScene->removeActor(*pxCapsule);
	pxCapsule->release();
	gMaterial->release();

	// Texture
	texture->destroy();
	delete texture;

	// Shader
	shader->destroy();
	delete shader;

	// Model
	delete modelCapsule;
}

void GOCapsule::postUpdate()
{
	physx::PxTransform t = pxCapsule->getGlobalPose();
	pos.x = t.p.x;
	pos.y = t.p.y;
	pos.z = t.p.z;
	rot.x = t.q.x;
	rot.y = t.q.y;
	rot.z = t.q.z;
	rot.w = t.q.w;
}

void GOCapsule::render()
{
	// Shader
	shader->bind();
	shader->pushInt("baseTex", 0);
	texture->bind(0);

	// Sphere
	matCapsule = glm::translate(glm::mat4(1.0f), pos) * glm::mat4_cast(rot);
	shader->pushMatrix("matTrans", proj * view * matCapsule);
	modelCapsule->render();

	// Shader
	texture->unbind(0);
	shader->unbind();
}
