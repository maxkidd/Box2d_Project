#ifndef _GAMESCENE1_H_
#define _GAMESCENE1_H_

#include <SFML\System\Clock.hpp>

#include "Scene.h"

#include <Box2D\Box2D.h>

#include "EntityManager.h"
#include "GraphicsManager.h"

class GameScene1 : public Scene
{
public:
	GameScene1();

	virtual void Frame();
	virtual void OnEnter();
	virtual void OnExit();

private:
	// Time variables
	double delta;
	sf::Clock clock;
	sf::Time lastTime;
	const float frame = 1.0f / 60.0f;

	// Box2d variables
	const b2Vec2 gravity{ 0.0f, -9.8f };
	b2World world{ gravity };
	const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;

	// Managers
	EntityManager entityManager;
	GraphicsManager graphicsManager;
};

#endif