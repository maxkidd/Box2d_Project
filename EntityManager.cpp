#include "EntityManager.h"
#include "IComponent.h"

EntityManager::EntityManager(){}
EntityManager::~EntityManager(){}

void EntityManager::Update()
{
	int count = 0;
	// Loop through entity map
	for (std::map<unsigned int, Entity>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		it->second.Update();
	}
}

IComponent* EntityManager::GetComponent(const unsigned int &entity, std::type_index type)
{
	return entities[entity].GetComponent(type);
}


std::vector<IComponent*> EntityManager::GetAllComponentsOfType(std::type_index type)
{
	std::vector<IComponent*> components;
	
	// Loop through entity map
	for (std::map<unsigned int, Entity>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		// If component exists in entity, push it into the returning vector
		if (entities[it->first].ComponentExists(type))
		{
			components.push_back(it->second.GetComponent(type));
		}
	}
	// Return components
	return components;
}

std::vector<unsigned int> EntityManager::GetAllEntitiesPossessingComponents(std::initializer_list<std::type_index> types)
{
	std::vector<unsigned int> entity_IDs;

	// Loop through entity map
	for (std::map<unsigned int, Entity>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		entity_IDs.push_back(it->first);
		for (std::type_index type : types)
		{
			if (!entities[it->first].ComponentExists(type))
			{
				entity_IDs.pop_back();
				break;
			}
		}
	}
	return entity_IDs;
}

void EntityManager::AddComponent(const unsigned int entityID, IComponent* component, std::type_index type, const bool replace)
{
	entities[entityID].AddComponent(component, type, replace);
}

void EntityManager::RemoveComponent(const unsigned int entityID, std::type_index type)
{
	entities[entityID].RemoveComponent(type);
}

unsigned int EntityManager::CreateEntity()
{
	entities[lastID] = Entity{ lastID };

	return lastID++;
}

void EntityManager::DestroyEntity(unsigned int entityID)
{
	
	entities.erase(entityID);
}

