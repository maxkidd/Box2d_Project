#ifndef _SCENE_H_
#define _SCENE_H_


class SceneManager;
class Input;

namespace sf
{
	class RenderWindow;
}

class Scene
{
public:
	Scene(){};
	virtual void OnEnter(){};
	virtual void OnExit(){};
	virtual void Frame(){};

protected:
	SceneManager* GetSceneManager(){ return sceneManager; };
	sf::RenderWindow* GetWindowManager(){ return window; };
	Input* GetInput(){ return input; };
	friend class SceneManager;
private:
	SceneManager* sceneManager;
	sf::RenderWindow* window;
	Input* input;
};

#endif