#include "CameraComponent.h"
#include "B2Component.h"
#include "EntityManager.h"

CameraComponent::CameraComponent()
{

}
CameraComponent::~CameraComponent()
{

}

void CameraComponent::Update()
{
	if (!playerB2Component)
	{
		playerB2Component = dynamic_cast<B2Component*>(entityManager->GetComponent(entityID, typeid(B2Component)));
	}
	else
	{

	}
}