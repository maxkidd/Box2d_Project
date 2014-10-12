
#include "Input.h"

#include "SceneManager.h"

#include "MenuScene.h"
#include "GameScene1.h"

#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

int main()
{
	sf::RenderWindow window{};
	window.create(sf::VideoMode(600, 550), "Experimental game!");

	Input inputController{};

	SceneManager sceneManager{};
	sceneManager.SetWindow(&window);
	sceneManager.SetScene(new GameScene1(), false);

	while (window.isOpen())
	{
		inputController.Frame();

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				inputController.OnKeyDown(event.key.code);
			else if (event.type == sf::Event::KeyReleased)
				inputController.OnKeyUp(event.key.code);
		}

		sceneManager.RunFrame();
	}

	return 0;
}