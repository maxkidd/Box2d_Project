#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <map>
#include <typeindex>

#include "IComponent.h"


class IComponent;

class Entity
{
public:
	Entity();
	Entity(unsigned int ID);
	~Entity();

	void Update();

	void AddComponent(IComponent* component, std::type_index type, bool replace = false);
	void RemoveComponent(std::type_index type);
	bool ComponentExists(std::type_index type);
	IComponent* GetComponent(std::type_index type);


	void SetID(unsigned int id);
	unsigned int getID();

	void SetName(std::string name);
	std::string getName();

	void SetTag(std::string tag);
	std::string getTag();

private:
	std::map<std::type_index, IComponent*> components;
	unsigned int entityID;
	std::string entityName;
	std::string entityTag;
};

#endif