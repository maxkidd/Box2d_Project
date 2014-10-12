#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(unsigned int ID)
{
	entityID = ID;
}
Entity::~Entity()
{
	for (std::map<std::type_index, IComponent*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		delete it->second;
	}
}

void Entity::Update()
{
	// Loop through entity map
	for (std::map<std::type_index, IComponent*>::iterator it = components.begin(); it != components.end(); it++)
	{
		it->second->Update();
	}
}

void Entity::AddComponent(IComponent* component, std::type_index type, bool replace)
{
	if (replace || (components.find(type) == components.end()))
	{
		components[type] = component;
		components[type]->entityID = entityID;
	}
}

void Entity::RemoveComponent(std::type_index type)
{
	components.erase(type);
}

bool Entity::ComponentExists(std::type_index type)
{
	if (components.find(type) != components.end()) 
	{
		return true;
	}
	return false;

}

IComponent* Entity::GetComponent(std::type_index type)
{
	if (components.find(type) != components.end())
		return components[type];
	return NULL;
}

void Entity::SetName(std::string name)
{
	entityName = name;
}
std::string Entity::getName()
{
	return entityName;
}

void Entity::SetID(unsigned int id)
{
	entityID = id;

	// Loop through components map
	for (std::map<std::type_index, IComponent*>::iterator it = components.begin(); it != components.end(); it++)
	{
		it->second->entityID = id;
	}
}
unsigned int Entity::getID()
{
	return entityID;
}