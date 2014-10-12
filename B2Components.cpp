#include "B2Component.h"

B2Component::B2Component()
{
	this->world = world;
}

B2Component::B2Component(b2BodyDef bodyDefine)
{
	this->world = world;
	DefineBody(bodyDefine);
}

B2Component::B2Component(b2BodyDef bodyDefine, b2FixtureDef fixtureDefine)
{
	this->world = world;
	DefineBody(bodyDefine);
	SetFixture(fixtureDefine);
}

B2Component::~B2Component()
{
	if (body != nullptr)
		world->DestroyBody(body);
	body = nullptr;
}

b2Body* B2Component::DefineBody(b2BodyDef bodyDefine)
{
	body = world->CreateBody(&bodyDefine);
	return body;
}

b2Fixture* B2Component::SetFixture(b2FixtureDef fixtureDefine)
{
	return body->CreateFixture(&fixtureDefine);
}

void B2Component::SetWorld(b2World* world)
{
	B2Component::world = world;
}

void B2Component::Update()
{

}


b2World* B2Component::world;