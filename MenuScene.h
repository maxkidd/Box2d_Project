#ifndef _MENUSCENE_H_
#define _MENUSCENE_H_

#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();

	virtual void Frame();
	virtual void OnEnter();
	virtual void OnExit();

private:
	
};

#endif