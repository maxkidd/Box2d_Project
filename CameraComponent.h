#ifndef _CAMERACOMPONENT_H_
#define _CAMERACOMPONENT_H_

#include "IComponent.h"

class B2Component;

class CameraComponent : public IComponent
{
public:
	CameraComponent();
	~CameraComponent();

	void Update();

private:
	B2Component* playerB2Component{nullptr};
};

#endif