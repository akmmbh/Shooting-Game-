#pragma once
#include <map>
#include "Entity.hpp"
using EntityVec = std::vector<std::shared_ptr<Entity>>;
class EntityManager
{
	EntityVec                         m_entities;
	EntityVec                         m_entitiesToAdd;
	std::map<std::string, EntityVec>   m_entityMap;
	size_t                             m_totalEntities = 0;

	void removeDeadEntities(EntityVec& vec)
	{
		//ToDO : remove all dead entites from the input vector
		//this is called by update() funciton 
	}

public:
	EntityManager() = default;
	void update()
	{
  // TODO : add entities from m_entitiesTOAdd the proper location(S)
		//-- add them to the vector of all entities 
		// -- add them to the vector inside the map with the tag as a key

		// remove dead entities from the vector of all entities 
		removeDeadEntities(m_entities);
		//remove dead entities form the each vector in the entitiy map
		// C++ 20 way of iterating through [key value ] pairs in map

		for (auto& [tag, entityVec] : m_entityMap)
		{
			removeDeadEntities(entityVec);
		}
	}
	std::shared_ptr<Entity> addEntity(const std::string& tag)
	{
		//creat the entity shared pointer
		auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

		//add  it to the vec of all entites 
		m_entitiesToAdd.push_back(entity);
		//add it to the entity map

		if (m_entityMap.find(tag) == m_entityMap.end()) { m_entityMap[tag] = EntityVec(); }
		m_entityMap[tag].push_back(entity);
		return entity;
	}
	const EntityVec& getEntities()
	{
		return m_entities;
	}
	const EntityVec& getEntities(const std::string& tag)
	{
		if (m_entityMap.find(tag) == m_entityMap.end()) {
			m_entityMap[tag] = EntityVec();
		}
		return m_entityMap[tag];
	}
	const std::map<std::string, EntityVec>& getEntityMap()
	{
		return m_entityMap;
	}
};
