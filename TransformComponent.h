#ifndef _TRANSFORMCOMPONENT_H_
#define _TRANSFORMCOMPONENT_H_

#include "IComponent.h"
#include <SFML/System/Vector2.hpp>

class TransformComponent : public IComponent
{
public:
	TransformComponent();
	~TransformComponent();

	void Update();

	sf::Vector2f position, rotation, scale;
};

#endif