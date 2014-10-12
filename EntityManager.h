#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <map>
#include <vector>
#include "ComponentType.h"
#include "Entity.h"
#include "IComponent.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();


	IComponent* GetComponent(const unsigned int &entity, std::type_index type);

	// Returns vector of pointers to IComponents of all components
	std::vector<IComponent*> GetAllComponentsOfType(std::type_index type);

	// Grabs all entities with components
	std::vector<unsigned int> GetAllEntitiesPossessingComponents(std::initializer_list<std::type_index> types);

	// Adds component to given entity
	void AddComponent(const unsigned int entityID, IComponent* component, std::type_index type, const bool replace = false);
	
	// Removes component from given entity
	void RemoveComponent(const unsigned int entityID, std::type_index type);

	// Creates and returns pointer to entity
	unsigned int CreateEntity();

	// Destroys entity
	void DestroyEntity(unsigned int entityID);

	//TODO: Finds and returns entity by name
	//Entity* FindWithName(std::string name);

	//TODO: Finds and returns a vector of entities with tag, returns null if none are found
	//std::vector<Entity*> FindEntitiesWithTag(std::string tag);

	void Update();

private:

	std::map<unsigned int, Entity> entities;
	unsigned int lastID{ 1 };

	std::map <std::initializer_list<IComponent>, unsigned int> component;
};


#endif