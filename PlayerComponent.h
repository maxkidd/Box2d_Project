#ifndef _PLAYERCOMPONENT_H_
#define _PLAYERCOMPONENT_H_

#include "IComponent.h"
#include <Box2D\Common\b2Settings.h>

#define PI 3.14159265358979323846

class Input;

class PlayerComponent : public IComponent
{
public:
	PlayerComponent();
	~PlayerComponent();

	void SetInput(Input* input);

	void Update();


private:
	Input* input;

	float r{ 0 };
	float r2{ 0 };
	int count{ 0 };
	const float copterHalfLength{ 1.0f };

	float maxForce{ 1.2f };
	float minForce{ 0.0f };

	float forceLeft{ 0.0f };
	float forceRight{ 0.0f };

	float fadeOutSpeed{ 0.1f };

	float32 forceConstant1{ 0.1f };
	float32 forceConstant2{ 0.02f };
};

#endif