#include "GameScene1.h"

#include "Input.h"
#include "EntityManager.h"
#include "GraphicsManager.h"

#include "B2Component.h"
#include "PlayerComponent.h"
#include "PolygonComponent.h"
#include "TransformComponent.h"

#include "PlayerPref.h"

#include <SFML\Window.hpp>

GameScene1::GameScene1()
{
}

void GameScene1::OnEnter()
{
	B2Component::SetWorld(&world);
	graphicsManager.SetEntityManager(&entityManager);
	graphicsManager.SetRenderWindow(GetWindowManager());
	graphicsManager.SetWorld(&world);

	IComponent testComp{};
	testComp.SetEntityManager(&entityManager);

	// Entity 1 PLAYER
	PlayerPref player = PlayerPref(&entityManager, 5.0f, -1.0f, GetInput());

	// Entity 2
	int entity2 = entityManager.CreateEntity();

	b2BodyDef staticBodyDef1;
	b2PolygonShape groundBox1;
	b2FixtureDef groundFixtureDef1;

	staticBodyDef1.position.Set(2.0f, -10.0f);
	groundBox1.SetAsBox(1.0f, 2.0f);

	groundFixtureDef1.shape = &groundBox1;
	groundFixtureDef1.density = 1.0f;
	groundFixtureDef1.friction = 0.3f;
	groundFixtureDef1.restitution = 0.0;

	B2Component* staticBox = new B2Component();
	b2Body* bodyTest2 = staticBox->DefineBody(staticBodyDef1);
	b2Fixture* fixTest2 = staticBox->SetFixture(groundFixtureDef1);

	entityManager.AddComponent(entity2, staticBox, typeid(B2Component));

	// Entity 3
	int entity5 = entityManager.CreateEntity();

	b2BodyDef staticBodyDef2;
	b2PolygonShape groundBox2;
	b2FixtureDef groundFixtureDef2;

	staticBodyDef2.position.Set(5.0f, -12.0f);
	groundBox2.SetAsBox(2.0f, 2.0f);

	groundFixtureDef2.shape = &groundBox2;
	groundFixtureDef2.density = 1.0f;
	groundFixtureDef2.friction = 0.3f;

	B2Component* staticBox2 = new B2Component();
	b2Body* bodyTest3 = staticBox2->DefineBody(staticBodyDef2);
	bodyTest3->SetTransform(bodyTest3->GetPosition(), 5.0f);
	b2Fixture* fixTest3 = staticBox2->SetFixture(groundFixtureDef2);
	entityManager.AddComponent(entity5, staticBox2, typeid(B2Component));

	// Entity 4 GROUND
	int entity6 = entityManager.CreateEntity();

	b2BodyDef staticBodyDef3;
	b2PolygonShape groundBox3;
	b2FixtureDef groundFixtureDef3;

	staticBodyDef3.position.Set(0.0f, -28.0f);
	groundBox3.SetAsBox(40.0f, 2.0f);

	groundFixtureDef3.shape = &groundBox3;
	groundFixtureDef3.density = 1.0f;
	groundFixtureDef3.friction = 0.3f;

	B2Component* staticBox3 = new B2Component();
	b2Body* bodyTest4 = staticBox3->DefineBody(staticBodyDef3);
	bodyTest3->SetTransform(bodyTest3->GetPosition(), 5.0f);
	b2Fixture* fixTest4 = staticBox3->SetFixture(groundFixtureDef3);

	entityManager.AddComponent(entity6, staticBox3, typeid(B2Component));

	entityManager.GetComponent(entity6, typeid(TransformComponent));

	clock = sf::Clock{};
	lastTime = clock.getElapsedTime();
	delta = 0;
}

void GameScene1::OnExit()
{

}

void GameScene1::Frame()
{
	sf::Time now = clock.getElapsedTime();
	delta += (now - lastTime).asSeconds() / frame;
	lastTime = now;
	while (delta >= 1)
	{
		world.Step(timeStep, velocityIterations, positionIterations);
		entityManager.Update();
		delta--;
	}

	graphicsManager.Render(&world);
}