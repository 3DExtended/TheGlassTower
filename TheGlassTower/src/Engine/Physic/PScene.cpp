#include "PScene.h"
#include "Engine/Core/Engine.h"

namespace engine
{
	PScene::PScene()
	{
	}
	PScene::~PScene()
	{
	}
	void PScene::create()
	{
		physx::PxSceneDesc sceneDesc(m_engine->getPhysics()->getTolerancesScale());
		physx::PxCpuDispatcher * cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
		if (!cpuDispatcher)
		{
			printf("CPU Dispatcher Creation failed!\n");
			exit(0);
		}
		sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
		sceneDesc.cpuDispatcher = cpuDispatcher;
		sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
		m_pxScene = m_engine->getPhysics()->createScene(sceneDesc);
	}
	void PScene::destroy()
	{
		m_pxScene->release();
	}
	void PScene::step(const float & delta)
	{
		m_pxScene->simulate(delta);
	}
	void PScene::fetch()
	{
		m_pxScene->fetchResults(true);
	}
}