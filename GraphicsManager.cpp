#include "GraphicsManager.h"

#include "EntityManager.h"
#include "IComponent.h"

#include "TransformComponent.h"
#include "PolygonComponent.h"

#include <Box2D\Dynamics\b2World.h>
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Dynamics\b2Fixture.h>
#include <Box2D\Collision\Shapes\b2CircleShape.h>
#include <Box2D\Collision\Shapes\b2PolygonShape.h>

GraphicsManager::GraphicsManager(){}
GraphicsManager::~GraphicsManager(){}

void GraphicsManager::Initialize()
{

}


void GraphicsManager::SetRenderWindow(sf::RenderWindow* window)
{
	renderWindow = window;
}
void GraphicsManager::SetEntityManager(EntityManager* manager)
{
	entityManager = manager;
}

void GraphicsManager::SetWorld(b2World* world)
{
	this->world = world;
}



void GraphicsManager::Render(b2World* world)
{

	renderWindow->clear();
	

	for (b2Body* body = world->GetBodyList(); body;body = body->GetNext())
	{
		for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{

			const b2Transform& xf = body->GetTransform();

			b2Shape::Type shapeType = fixture->GetType();
			if (shapeType == b2Shape::e_circle)
			{
				b2CircleShape* circleShape = (b2CircleShape*)fixture->GetShape();
			}
			else if (shapeType == b2Shape::e_polygon)
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)fixture->GetShape();
				b2Vec2 vertices[b2_maxPolygonVertices];

				sf::ConvexShape sfmlPoly(polygonShape->GetVertexCount());
				sfmlPoly.setOutlineColor(sf::Color::Red);
				sfmlPoly.setOutlineThickness(1);
				for (int i = 0; i < polygonShape->GetVertexCount(); i++)
				{
					vertices[i] = b2Mul(xf, polygonShape->GetVertex(i));
					sfmlPoly.setPoint(i, sf::Vector2f(vertices[i].x*20, -vertices[i].y*20));
				}
				renderWindow->draw(sfmlPoly);
			}
		}
	}

	renderWindow->display();
}