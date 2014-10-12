#include "SceneManager.h"

#include "Scene.h"
#include "Input.h"

#include <cstddef>
#include <SFML\Graphics\RenderWindow.hpp>

SceneManager::SceneManager()
{
	currentScene = NULL;
	nextScene = NULL;
	destroyPreviousScene = false;
}


void SceneManager::RunFrame()
{
	if (nextScene != NULL)
	{
		if (currentScene != NULL)
		{
			currentScene->OnExit();
		}
		if (destroyPreviousScene)
		{
			delete currentScene;
		}

		currentScene = nextScene;
		nextScene = NULL;
		currentScene->OnEnter();
	}

	if (currentScene != NULL)
	{
		currentScene->Frame();
	}
}

void SceneManager::SetScene(Scene* scene, bool destroyPreviousScene)
{
	scene->sceneManager = this;
	scene->window = window;
	scene->input = input;
	nextScene = scene;
	this->destroyPreviousScene = destroyPreviousScene;
}

void SceneManager::SetWindow(sf::RenderWindow* window)
{
	this->window = window;
	if (currentScene != NULL)
		currentScene->window = window;
}

void SceneManager::SetInput(Input* input)
{
	this->input = input;
	if (currentScene != NULL)
		currentScene->input = input;
}