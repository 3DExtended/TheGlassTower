#pragma once
#include "Engine/Core/AGame.h"

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
};

