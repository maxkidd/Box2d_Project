#include "PolygonComponent.h"


PolygonComponent::PolygonComponent()
{
	shape = sf::ConvexShape{};

}
PolygonComponent::PolygonComponent(sf::ConvexShape shape)
{
	this->shape = shape;
}
PolygonComponent::~PolygonComponent(){}