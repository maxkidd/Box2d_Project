#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include <SFML\Graphics\RenderWindow.hpp>

class EntityManager;
class b2World;

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	void Initialize();
	void SetRenderWindow(sf::RenderWindow* window);
	void SetEntityManager(EntityManager* manager);
	void SetWorld(b2World* world);

	void Render(b2World* world);

	sf::RenderWindow* renderWindow;
	EntityManager* entityManager;
	b2World* world;
	
};

#endif