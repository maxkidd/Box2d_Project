#include "PlayerPref.h"
#include <Box2D\Box2D.h>

#include "B2Component.h"
#include "PlayerComponent.h"
#include "CameraComponent.h"
#include "Input.h"
#include "EntityManager.h"

PlayerPref::PlayerPref(EntityManager* manager, float32 x, float32 y, Input* input)
{
	// Entity 1 PLAYER
	int entity1 = manager->CreateEntity();

	b2BodyDef bodyDef1;
	b2PolygonShape dynamicBox1;
	b2FixtureDef fixtureDef;

	bodyDef1.type = b2_dynamicBody;
	bodyDef1.position.Set(x, y);

	dynamicBox1.SetAsBox(1.0f, 0.2f);

	fixtureDef.shape = &dynamicBox1;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.4f;

	B2Component* b2d = new B2Component();
	b2Body* bodyTest = b2d->DefineBody(bodyDef1);
	b2Fixture* fixTest = b2d->SetFixture(fixtureDef);
	PlayerComponent* playerComp = new PlayerComponent();
	playerComp->SetInput(input);

	manager->AddComponent(entity1, b2d, typeid(B2Component));
	manager->AddComponent(entity1, new PlayerComponent(), typeid(PlayerComponent));
	manager->AddComponent(entity1, new CameraComponent(), typeid(CameraComponent));

}