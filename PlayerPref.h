#ifndef _PLAYERPREF_H_
#define _PLAYERPREF_H_

#include <Box2D\Common\b2Settings.h>

class EntityManager;
class Input;

class PlayerPref
{
public:
	PlayerPref(EntityManager* manager, float32 x, float32 y, Input* input);

};

#endif