#ifndef _ICOMPONENT_H_
#define _ICOMPONENT_H_

class EntityManager;

class IComponent
{
public:
	virtual ~IComponent(){}

	void SetEntityManager(EntityManager* manager)
	{
		entityManager = manager;
	}

	virtual void Start(){};
	virtual void Update(){};

	int entityID;
	
protected:
	static EntityManager* entityManager;
};
#endif