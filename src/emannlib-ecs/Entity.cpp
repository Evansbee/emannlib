/*
  Copyright (c) 2013 Evan Ackmann

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

Creator(s)    : Evan Ackmann
File Name     : Entity.cpp
Purpose       :
*/

#include "Entity.hpp"
#include "../emannlib-common/Autoprofile.hpp"

namespace emannlib
{

    uint32_t BaseComponent::ms_TypeIDCounter = 0;

    void Entity::Destroy()
    {
		AUTO_PROFILE("Entity::Destroy");
        if (IsValid())
        {
            m_EntityManager.lock()->Destroy(m_ID);
            SetInvalid();
        }
    }
    bool Entity::IsValid() const
    {
		AUTO_PROFILE("Entity::IsValid");
		return !m_EntityManager.expired() &&  m_EntityManager.lock()->IsValid(m_ID);
    }

    void Entity::SetInvalid()
    {
		AUTO_PROFILE("Entity::SetInvalid");
        m_ID = INVALID;
        m_EntityManager.reset();
    }


	bool Entity::HasTag(const std::string& tag)
	{
		AUTO_PROFILE("Entity::HasTag");
		return m_EntityManager.lock()->HasTag(m_ID, tag);
	}
	void Entity::AddTags(const std::string& tag)
	{
		AUTO_PROFILE("Entity::AddTags");
		m_EntityManager.lock()->AddTags(m_ID, tag);
	}
	void Entity::RemoveTags(const std::string& tag)
	{
		AUTO_PROFILE("Entity::RemoveTags");
		m_EntityManager.lock()->RemoveTags(m_ID, tag);
	}


    Entity EntityManager::Create()
    {
		AUTO_PROFILE("EntityManager::Create");
        uint32_t index;
        uint32_t version;

        if (m_FreeSlots.empty())
        {
            index = m_TopIndex++;
            AllocateSpaceForEntity(index);
            m_EntityVersionNumbers[index] = 1;
        }
        else
        {
            index = m_FreeSlots.front();
            m_FreeSlots.pop_front();
        }


        version = m_EntityVersionNumbers[index];
        m_EntityComponentMask[index] = 0;
		m_EntityTags[index].clear();

        Entity newEntity(shared_from_this(), Entity::ID(index, version));
        m_EventManager->Emit<EntityCreatedEvent>(newEntity);
        return newEntity;
    }

    void EntityManager::Destroy(Entity::ID id)
    {
		AUTO_PROFILE("EntityManager::Destroy");
        uint32_t index = id.GetIndex();
        uint32_t version = id.GetVersion();

        if (id.GetIndex() < m_EntityVersionNumbers.size() && id.GetVersion() == m_EntityVersionNumbers[id.GetIndex()])
        {
            m_EntityVersionNumbers[id.GetIndex()]++;
            m_EntityComponentMask[id.GetIndex()] = 0;
			m_EntityTags[id.GetIndex()].clear();
            m_FreeSlots.push_back(id.GetIndex());

            Entity newEntity(shared_from_this(), Entity::ID(index, version));
            m_EventManager->Emit<EntityDestroyedEvent>(newEntity);
        }
    }




    bool EntityManager::IsValid(Entity::ID id)
    {
		AUTO_PROFILE("EntityManager::IsValid");
        return (id.GetVersion() > 0 && id.GetIndex() < m_EntityVersionNumbers.size() && id.GetVersion() == m_EntityVersionNumbers[id.GetIndex()]);
    }

//Currently doesn't have test coverage
    Entity EntityManager::GetEntity(Entity::ID id)
    {
		AUTO_PROFILE("EntityManager::GetEntity");
        if (IsValid(id))
        {
            return Entity(shared_from_this(), id);
        }
        else
        {
            //No great way to issue an invalid entity
            return Entity(shared_from_this(), INVALID);
        }
    }


    uint32_t EntityManager::GetEntityCount() const
    {
		AUTO_PROFILE("EntityManager::GetEntityCount");
        return m_EntityComponentMask.size() - m_FreeSlots.size();
    }


    uint32_t EntityManager::GetEntityCapacity() const
    {
		AUTO_PROFILE("EntityManager::GetEntityCapacity");
        return m_EntityComponentMask.size();
    }

//This returns a valid Entity, something else will fail later
//if a bad index was fed in.
    Entity EntityManager::CreateEntityFromIndex(uint32_t idx)
    {
		AUTO_PROFILE("EntityManager::CreateEntityFromIndex");
        if (idx < m_EntityVersionNumbers.size())
        {
            return Entity(shared_from_this(), Entity::ID(idx, m_EntityVersionNumbers[idx]));
        }
        else
        {
            return Entity(shared_from_this(), INVALID);
        }
    }


    void EntityManager::AllocateSpaceForEntity(uint32_t index)
    {
		AUTO_PROFILE("EntityManager::AllocateSpaceForEntity");
        if (m_EntityVersionNumbers.size() <= index)
        {
            m_EntityVersionNumbers.resize(index + 1);
            m_EntityComponentMask.resize(index + 1);
	    m_EntityTags.resize(index + 1);
            
            for (auto &component : m_EntityComponents)
            {
                component.resize(index + 1);
            }
        }
    }
    void EntityManager::AllocateSpaceForComponent(uint32_t index)
    {
		AUTO_PROFILE("EntityManager::AllocateSpaceForComponent");
        if (m_EntityComponents.size() <= index)
        {
            m_EntityComponents.resize(index + 1);
            m_EntityComponents[index].resize(m_TopIndex);
        }
    }


	bool EntityManager::HasTag(Entity::ID id, const std::string& tag)
	{
		AUTO_PROFILE("EntityManager::HasTag");
		if (IsValid(id))
		{
			return (std::find(m_EntityTags[id.GetIndex()].begin(), m_EntityTags[id.GetIndex()].end(), tag) != m_EntityTags[id.GetIndex()].end()) ? (true) : (false);
		}
		return false;

		
	}
	void EntityManager::AddTags(Entity::ID id, const std::string& tag)
	{
		AUTO_PROFILE("EntityManager::AddTags");
		if (IsValid(id))
		{
			m_EntityTags[id.GetIndex()].insert(tag);
		}
		
	}
	void EntityManager::RemoveTags(Entity::ID id, const std::string& tag)
	{
		AUTO_PROFILE("EntityManager::RemoveTag");
		if (IsValid(id))
		{
			auto element = m_EntityTags[id.GetIndex()].find(tag);
			if (element != m_EntityTags[id.GetIndex()].end())
			{
				m_EntityTags[id.GetIndex()].erase(element);
			}
		}
	}
}
