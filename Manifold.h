#ifndef MANIFOLD_H
#define MANIFOLD_H

#include <SFML\System\Vector2.hpp>

struct PolygonComponent;

// http://gamedev.tutsplus.com/tutorials/implementation/create-custom-2d-physics-engine-aabb-circle-impulse-resolution/
struct Manifold
{
	Manifold(PolygonComponent *a, PolygonComponent *b)
	: A(a)
	, B(b)
	{
	}

	void Solve(void);                 // Generate contact information
	void Initialize(void);            // Precalculations for impulse solving
	void ApplyImpulse(void);          // Solve impulse and apply
	void PositionalCorrection(void);  // Naive correction of positional penetration
	void InfiniteMassCorrection(void);

	PolygonComponent *A;
	PolygonComponent *B;

	float penetration;     // Depth of penetration from collision
	sf::Vector2f normal;          // From A to B
	sf::Vector2f contacts[2];     // Points of contact during collision
	unsigned int contact_count; // Number of contacts that occured during collision
	float e;               // Mixed restitution
	float df;              // Mixed dynamic friction
	float sf;              // Mixed static friction
};

#endif // MANIFOLD_H