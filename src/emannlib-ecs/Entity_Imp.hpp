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
File Name     : EntityImp.hpp
Purpose       :
*/

namespace goldenduck
{
	template <class T>
	uint32_t Component<T>::GetTypeID()
	{
		AUTO_PROFILE("Component<T>::GetTypeID");
		static uint32_t typeID = ms_TypeIDCounter++;
		return typeID;
	}

	template <class C>
	std::shared_ptr<C> Entity::GetComponent() const
	{
		AUTO_PROFILE("Entity::GetComponent");
		if (IsValid())
		{
			return m_EntityManager.lock()->GetComponent<C>(m_ID);
		}
		return nullptr;
	}

	template < class C >
	bool Entity::GetComponent(std::shared_ptr<C> &component) const
	{
		AUTO_PROFILE("Entity::GetComponent");
		if (IsValid())
		{
			component = m_EntityManager.lock()->GetComponent<C>(m_ID);
			return component != nullptr;
		}
		return false;
	}

	template < class A, class ... Args>
	bool Entity::GetComponents(std::shared_ptr<A> &a, std::shared_ptr<Args> &... args) const
	{
		AUTO_PROFILE("Entity::GetComponents");
		if (IsValid())
		{
			a = m_EntityManager.lock()->GetComponent<A>(m_ID);
			return a != nullptr && GetComponents(args ...);
		}
		return false;
	}

	template < class C >
	std::shared_ptr<C> Entity::RemoveComponent() const
	{
		AUTO_PROFILE("Entity::RemoveComponent");
		return m_EntityManager.lock()->RemoveComponent<C>(m_ID);
	}

	template< class C >
	std::shared_ptr<C> Entity::AddComponent(std::shared_ptr<C> component)
	{
		AUTO_PROFILE("Entity::AddComponent");
		return m_EntityManager.lock()->AddComponent<C>(m_ID, component);
	}

	template< class C, class ... Args>
	std::shared_ptr<C> Entity::AddComponent(Args && ... args)
	{
		AUTO_PROFILE("Entity::AddComponent");
		return m_EntityManager.lock()->AddComponent<C>(m_ID, args ...);
	}

	template <class ... Args>
	void Entity::AddTags(const std::string& first, const std::string& second, const Args& ... args)
	{
		AUTO_PROFILE("Entity::AddTags");
		m_EntityManager.lock()->AddTags(m_ID, first, second, args...);
	}

	template <class ... Args>
	void Entity::RemoveTags(const std::string& first, const std::string& second, const Args& ... args)
	{
		AUTO_PROFILE("Entity::RemoveTags");
		m_EntityManager.lock()->RemoveTags(m_ID, first, second, args...);
	}


	template <class C>
	std::shared_ptr<C> EntityManager::AddComponent(Entity::ID id, std::shared_ptr<C> component)
	{
		AUTO_PROFILE("EntityManager::AddComponent");
		Entity newEntity(shared_from_this(), id);
		if (C::GetTypeID() < goldenduck_MAX_COMPONENTS)
		{
			std::shared_ptr<BaseComponent> base(std::static_pointer_cast<BaseComponent>(component));
			AllocateSpaceForComponent(C::GetTypeID());
			m_EntityComponents[C::GetTypeID()][id.GetIndex()] = base;
			m_EntityComponentMask[id.GetIndex()] |= (uint64_t) (1) << C::GetTypeID();
			m_EventManager->Emit<ComponentAddedEvent<C>>(newEntity, component);
			return component;
		}
		return nullptr;
	}


	template <class C>
	std::shared_ptr<C> EntityManager::GetComponent(Entity::ID id) const
	{
		AUTO_PROFILE("EntityManager::GetComponent");
		uint32_t id1 = id.GetIndex();
		uint32_t id2 = C::GetTypeID();

		if (id.GetIndex() < m_EntityComponentMask.size() &&
			id.GetVersion() == m_EntityVersionNumbers[id.GetIndex()] &&
			C::GetTypeID() < m_EntityComponents.size() &&
			m_EntityComponentMask[id.GetIndex()].test(C::GetTypeID()))
		{
			std::shared_ptr<C> ret(std::static_pointer_cast<C>(m_EntityComponents[C::GetTypeID()][id.GetIndex()]));
			return ret;
		}
		return nullptr;
	}

	template <class C>
	std::shared_ptr<C> EntityManager::RemoveComponent(Entity::ID id)
	{
		AUTO_PROFILE("EntityManager::RemoveComponent");
		uint32_t id1 = id.GetIndex();
		uint32_t id2 = C::GetTypeID();

		if (id.GetIndex() < m_EntityComponentMask.size() &&
			id.GetVersion() == m_EntityVersionNumbers[id.GetIndex()] &&
			C::GetTypeID() < m_EntityComponents.size() &&
			m_EntityComponentMask[id.GetIndex()].test(C::GetTypeID()))
		{
			std::shared_ptr<C> ret(std::static_pointer_cast<C>(m_EntityComponents[C::GetTypeID()][id.GetIndex()]));
			m_EntityComponentMask[id.GetIndex()].reset(C::GetTypeID());

			Entity newEntity(shared_from_this(), id);
			m_EventManager->Emit<ComponentRemovedEvent<C>>(newEntity, ret);

			return ret;
		}
		return nullptr;
	}

	template <class A, class ... Args>
	EntityManager::FilteredView EntityManager::GetEntitiesWithComponents()
	{
		AUTO_PROFILE("EntityManager::GetEntitiesWithComponents");
		std::shared_ptr<EntityManager> em = shared_from_this();
		std::bitset<goldenduck_MAX_COMPONENTS> mask = CreateComponentMask<A, Args...>();
		return EntityManager::FilteredView(em, [em, mask](Entity e) { return  ((em->m_EntityComponentMask[e.m_ID.GetIndex()] & mask) == mask); });
	}


	template <class ... Args>
	EntityManager::FilteredView EntityManager::GetEntitiesWithTags(const std::string& first, const Args& ... args)
	{
		AUTO_PROFILE("EntityManager::GetEntitiesWithTags");
		std::shared_ptr<EntityManager> em = shared_from_this();
		std::vector<std::string> tagstomatch = { first, args... };
		return EntityManager::FilteredView(em, [em, tagstomatch](Entity e) -> bool {
			for (auto t : tagstomatch)
			{
				if (!e.HasTag(t))
				{
					return false;
				}
			}
			return true;
		}
		);
	}

	template <class ... Args>
	void EntityManager::AddTags(Entity::ID id, const std::string& first, const std::string& second, const Args& ... args)
	{
		AUTO_PROFILE("EntityManager::AddTags");
		AddTags(id, first);
		AddTags(id, second, args ...);
	}

	template <class ... Args>
	void EntityManager::RemoveTags(Entity::ID id, const std::string& first, const std::string& second, const Args& ... args)
	{
		AUTO_PROFILE("EntityManager::RemoveTags");
		RemoveTags(id, first);
		RemoveTags(id, second, args ...);
	}
    
}