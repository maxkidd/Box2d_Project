#include "PlayerComponent.h"

#include "EntityManager.h"
#include "B2Component.h"
#include "Input.h"

#include <cmath>
#include <iostream>
#include <SFML\Window\Keyboard.hpp>

PlayerComponent::PlayerComponent()
{

}
PlayerComponent::~PlayerComponent(){}


void PlayerComponent::SetInput(Input* input)
{
	this->input = input;
}

void PlayerComponent::Update()
{
	B2Component* b2Comp = dynamic_cast<B2Component*>(entityManager->GetComponent(entityID, typeid(B2Component)));

	// Get rotation of body
	float angle = b2Comp->body->GetAngle();
	while (angle > PI)
	{
		angle -= 2*PI;
	}
	while (angle < -PI)
	{
		angle += 2*PI;
	}

	// Find where to apply force
	b2Vec2 leftPoint = b2Vec2((-copterHalfLength * cos(angle) - sin(angle) + b2Comp->body->GetWorldCenter().x), sin(angle) * -copterHalfLength + cos(angle) + b2Comp->body->GetWorldCenter().y);
	b2Vec2 rightPoint = b2Vec2((copterHalfLength * cos(angle) - sin(angle) + b2Comp->body->GetWorldCenter().x), sin(angle) * copterHalfLength + cos(angle) + b2Comp->body->GetWorldCenter().y);
	
	// Initiale force if unstable
	float32 angleVel = b2Comp->body->GetAngularVelocity();
	
	// Find positive variables 
	float32 absAngle = abs(angle);
	float32 absAngleVel = abs(angleVel);


	if (angle < 0.0f)
	{
		if (angle * 2 + angleVel < 0.0f)
			forceRight += absAngle*forceConstant1;

		if (angle * 2 + angleVel > 0.0f)
			forceLeft += absAngleVel*forceConstant2;
	}
	else if (angle > 0.0f)
	{
		if (angle * 2 + angleVel > -0.0f)
			forceLeft += absAngle*forceConstant1;

		if (angle * 2 + angleVel < 0.2f)
			forceRight += absAngleVel*forceConstant2;
	}
	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		forceRight += ((maxForce - forceRight) * fadeOutSpeed);
	}
	else
	{
		if (forceRight > 0.0f)
			forceRight -= 0.00001 + (forceRight - minForce) * fadeOutSpeed;
		else
			forceRight = 0.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		forceLeft += ((maxForce - forceLeft) * fadeOutSpeed);
	}
	else
	{
		if (forceLeft > 0.0f)
			forceLeft -= 0.00001 + ((forceLeft - minForce) * fadeOutSpeed);
		else
			forceLeft = 0.0f;
	}


	// Apply forces
	b2Comp->body->ApplyForce(b2Vec2(cos(angle) * 0.0 - sin(angle) * forceRight, sin(angle) * 0.0 + cos(angle) * forceRight), rightPoint, true);
	b2Comp->body->ApplyForce(b2Vec2(cos(angle) * 0.0 - sin(angle) * forceLeft, sin(angle) * 0.0 + cos(angle) * forceLeft), leftPoint, true);
}