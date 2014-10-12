#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include<vector>


class Scene;
class Input;

namespace sf
{
	class RenderWindow;
}
class SceneManager
{
public:
	SceneManager();
	void RunFrame();
	void SetScene(Scene* scene, bool DestroyPreviousScene);
	void SetWindow(sf::RenderWindow* window);
	void SetInput(Input* input);
private:
	Scene* currentScene;
	Scene* nextScene;
	bool destroyPreviousScene;
	std::vector<Scene*> scenes;

	sf::RenderWindow* window;
	Input* input;
};

#endif