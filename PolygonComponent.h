#ifndef _POLYGONCOMPONENT_H_
#define _POLYGONCOMPONENT_H_

#include "IComponent.h"
#include <SFML\Graphics\ConvexShape.hpp>

class PolygonComponent : public IComponent
{
public:
	PolygonComponent();
	PolygonComponent(sf::ConvexShape);
	~PolygonComponent();
	
	sf::ConvexShape shape;
};

#endif