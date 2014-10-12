#include "Manifold.h"
#include <cmath>
#include <algorithm>
#include "PolygonComponent.h"

void Manifold::Solve(void)
{
	Dispatch[A->shape->GetType()][B->shape->GetType()](this, A, B);
}

void Manifold::Initialize(void)
{
	// Calculate average restitution
	e = std::min(A->restitution, B->restitution);

	// Calculate static and dynamic friction
	sf = std::sqrt(A->staticFriction * B->staticFriction);
	df = std::sqrt(A->dynamicFriction * B->dynamicFriction);

	for (unsigned int i = 0; i < contact_count; ++i)
	{
		// Calculate radii from COM to contact
		sf::Vector2f ra = contacts[i] - A->position;
		sf::Vector2f rb = contacts[i] - B->position;

		sf::Vector2f rv = B->velocity + Cross(B->angularVelocity, rb) -
			A->velocity - Cross(A->angularVelocity, ra);


		// Determine if we should perform a resting collision or not
		// The idea is if the only thing moving this object is gravity,
		// then the collision should be performed without any restitution
		if (LenSqr(rv) < LenSqr(dt * gravity) + EPSILON)
			e = 0.0f;
	}
}

void Manifold::ApplyImpulse(void)
{
	// Early out and positional correct if both objects have infinite mass
	if (Equal(A->im + B->im, 0))
	{
		InfiniteMassCorrection();
		return;
	}

	for (unsigned int i = 0; i < contact_count; ++i)
	{
		// Calculate radii from COM to contact
		sf::Vector2f ra = contacts[i] - A->position;
		sf::Vector2f rb = contacts[i] - B->position;

		// Relative velocity
		sf::Vector2f rv = B->velocity + Cross(B->angularVelocity, rb) -
			A->velocity - Cross(A->angularVelocity, ra);

		// Relative velocity along the normal
		float contactVel = Dot(rv, normal);

		// Do not resolve if velocities are separating
		if (contactVel > 0)
			return;

		float raCrossN = Cross(ra, normal);
		float rbCrossN = Cross(rb, normal);
		float invMassSum = A->im + B->im + Sqr(raCrossN) * A->iI + Sqr(rbCrossN) * B->iI;

		// Calculate impulse scalar
		float j = -(1.0f + e) * contactVel;
		j /= invMassSum;
		j /= (float)contact_count;

		// Apply impulse
		sf::Vector2f impulse = normal * j;
		A->ApplyImpulse(-impulse, ra);
		B->ApplyImpulse(impulse, rb);

		// Friction impulse
		rv = B->velocity + Cross(B->angularVelocity, rb) -
			A->velocity - Cross(A->angularVelocity, ra);

		sf::Vector2f t = rv - (normal * Dot(rv, normal));
		Normalize(&t);

		// j tangent magnitude
		float jt = -Dot(rv, t);
		jt /= invMassSum;
		jt /= (float)contact_count;

		// Don't apply tiny friction impulses
		if (Equal(jt, 0.0f))
			return;

		// Coulumb's law
		sf::Vector2f tangentImpulse;
		if (std::abs(jt) < j * sf)
			tangentImpulse = t * jt;
		else
			tangentImpulse = t * -j * df;

		// Apply friction impulse
		A->ApplyImpulse(-tangentImpulse, ra);
		B->ApplyImpulse(tangentImpulse, rb);
	}
}

void Manifold::PositionalCorrection(void)
{
	const float k_slop = 0.05f; // Penetration allowance
	const float percent = 0.4f; // Penetration percentage to correct
	sf::Vector2f correction = (std::max(penetration - k_slop, 0.0f) / (A->im + B->im)) * normal * percent;
	A->position -= correction * A->im;
	B->position += correction * B->im;
}

void Manifold::InfiniteMassCorrection(void)
{
	A->velocity.Set(0, 0);
	B->velocity.Set(0, 0);
}