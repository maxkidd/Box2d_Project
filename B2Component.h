#ifndef _B2COMPONENT_H_
#define _B2COMPONENT_H_

#include "IComponent.h"
#include <Box2D\Box2D.h>


class B2Component : public IComponent
{
public:
	B2Component();
	B2Component(b2BodyDef bodyDefine);
	B2Component(b2BodyDef bodyDefine, b2FixtureDef fixtureDefine);
	~B2Component();

	void Update();

	b2Body* DefineBody(b2BodyDef bodyDefine);
	b2Fixture* SetFixture(b2FixtureDef fixtureDefine);

	static void SetWorld(b2World* world);

	b2Body* body;
private:
	static b2World* world;
};

#endif