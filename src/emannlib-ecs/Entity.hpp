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
  File Name     : Entity.h
  Purpose       :
  */

#pragma once

#include <inttypes.h>

#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <bitset>
#include <iostream>
#include <unordered_set>

#include "Event.hpp"

#define emannlib_MAX_COMPONENTS (64)

namespace emannlib
{
    
	class EntityManager;




	class Entity
	{
	public:
		Entity() {}
		Entity(const Entity &) = default;
		//Entity(Entity &&) = default;
		Entity &operator = (const Entity &) = default;


	public:
		struct ID
		{
			ID() : m_ID(0) {};
			explicit ID(uint64_t id) : m_ID(id) {};
			explicit ID(uint32_t index, uint32_t version) : m_ID(((uint64_t) version << 32UL) | (uint64_t) index) {};

			uint32_t GetVersion() const { return m_ID >> 32UL; }

			uint32_t GetIndex() const { return m_ID & 0xFFffFFffUL; }

			uint64_t GetID() const { return m_ID; }

			bool operator == (const ID &other) const { return m_ID == other.m_ID; }
			bool operator != (const ID &other) const { return m_ID != other.m_ID; }
			bool operator < (const ID &other) const { return m_ID < other.m_ID; }

		private:
			friend class EntityManager;
			uint64_t m_ID;
		};

		ID m_ID;
		ID GetID() const { return m_ID; }

		template< class C >
		std::shared_ptr<C> AddComponent(std::shared_ptr<C> component);

		template< class C, class ... Args>
		std::shared_ptr<C> AddComponent(Args && ... args);

		template < class C >
		std::shared_ptr<C> RemoveComponent() const;

		template < class C >
		std::shared_ptr<C> GetComponent() const;

		template < class C >
		bool GetComponent(std::shared_ptr<C> &component) const;

		template < class A, class ... Args>
		bool GetComponents(std::shared_ptr<A> &a, std::shared_ptr<Args> &... args) const;

		bool GetComponents() const { return true; }

		bool HasTag(const std::string& tag);
		void AddTags(const std::string& tag);

		template <class ... Args>
		void AddTags(const std::string& first, const std::string& second, const Args& ... args);

		void RemoveTags(const std::string& tag);

		template <class ... Args>
		void RemoveTags(const std::string& first, const std::string& second, const Args& ... args);

		//validation etc
		bool IsValid() const;
		void SetInvalid();
		void Destroy();

		//operators
		operator bool() const { return IsValid(); }

		bool operator == (const Entity &other) const { return  other.m_EntityManager.lock() == m_EntityManager.lock() && other.m_ID == m_ID; }


	private:
		friend class EntityManager;
		std::weak_ptr<EntityManager> m_EntityManager;

		Entity(std::weak_ptr<EntityManager> em, ID id) :
			m_EntityManager(em),
			m_ID(id)
		{}
	};

	const Entity::ID INVALID(0x0);





	class BaseComponent
	{
	protected:
		static uint32_t ms_TypeIDCounter;
	};

	template <class T>
	class Component : public BaseComponent
	{
	public:
		static uint32_t GetTypeID();
	};














#pragma region PrecannedEvents
	class EntityCreatedEvent : public Event<EntityCreatedEvent>
	{
	public:
		EntityCreatedEvent() {}
		EntityCreatedEvent(Entity e) : m_Entity(e) {}
		Entity m_Entity;
	};




	class EntityDestroyedEvent : public Event<EntityDestroyedEvent>
	{
	public:
		EntityDestroyedEvent() {}
		EntityDestroyedEvent(Entity e) : m_Entity(e) {}
		Entity m_Entity;
	};




	template <class C>
	class ComponentAddedEvent : public Event<ComponentAddedEvent<C > >
	{
		
	public:
		ComponentAddedEvent() {}
		ComponentAddedEvent(Entity e, std::shared_ptr< C> c) : m_Entity(e), m_Component(c) {}
		Entity m_Entity;
		std::shared_ptr< C> m_Component;
	};





	template <class C>
	class ComponentRemovedEvent : public Event<ComponentRemovedEvent<C > >
	{
	public:
		ComponentRemovedEvent() {}
		ComponentRemovedEvent(Entity e, std::shared_ptr<C> c) : m_Entity(e), m_Component(c) {}
		Entity m_Entity;
		std::shared_ptr<C> m_Component;
	};

#pragma endregion







	typedef std::function<bool(Entity)> EntitySelectionPredicate;


	class EntityManager : public std::enable_shared_from_this<EntityManager>
	{
	
	private:
		friend class Entity;

	public:

		Entity Create();

		void Destroy(Entity::ID id);

		bool IsValid(Entity::ID id);
		//Currently doesn't have test coverage
		Entity GetEntity(Entity::ID id);

		uint32_t GetEntityCount() const;

		uint32_t GetEntityCapacity() const;

		//This returns a valid Entity, something else will fail later
		//if a bad index was fed in.
		Entity CreateEntityFromIndex(uint32_t idx);



	private:
		void AllocateSpaceForEntity(uint32_t index);
		void AllocateSpaceForComponent(uint32_t index);

	private:
		uint32_t m_TopIndex = 0;
		std::list<uint32_t> m_FreeSlots;
		std::vector<uint32_t> m_EntityVersionNumbers;
		std::vector<std::bitset<emannlib_MAX_COMPONENTS > > m_EntityComponentMask;
		std::vector<std::vector<std::shared_ptr<BaseComponent > > > m_EntityComponents;
		std::vector<std::unordered_set<std::string > > m_EntityTags;

	private:

		template <class C>
		std::shared_ptr<C> AddComponent(Entity::ID id, std::shared_ptr<C> component);

		template <class C, class ... Args>
		std::shared_ptr<C> AddComponent(Entity::ID id, Args && ... args) { return AddComponent(id, std::make_shared<C>(std::forward<Args>(args) ...)); }

		template <class C>
		std::shared_ptr<C> GetComponent(Entity::ID id) const;

		template <class C>
		std::shared_ptr<C> RemoveComponent(Entity::ID id);


		bool HasTag(Entity::ID id, const std::string& tag);
		void AddTags(Entity::ID id, const std::string& tag);

		template <class ... Args>
		void AddTags(Entity::ID id, const std::string& first, const std::string& second, const Args& ... args);

		void RemoveTags(Entity::ID id, const std::string& tag);

		template <class ... Args>
		void RemoveTags(Entity::ID id, const std::string& first, const std::string& second, const Args& ... args);

	private:
		std::shared_ptr<EventManager> m_EventManager;

	public:
		EntityManager(std::shared_ptr<EventManager> ev) : m_EventManager(ev) {}
		EntityManager() : m_EventManager(std::make_shared<EventManager>()) {}
		static std::shared_ptr<EntityManager> Make(std::shared_ptr<EventManager> ev) { return std::make_shared<EntityManager>(ev); }
	public:
		//entity retrieval...

		friend class FilteredView;


		class FilteredView
		{
		private:
			std::shared_ptr<EntityManager> m_ViewEntityManager;
			EntitySelectionPredicate m_SelectionPredicate;

		public:

			FilteredView(std::shared_ptr<EntityManager> em, EntitySelectionPredicate pred) : m_ViewEntityManager(em), m_SelectionPredicate(pred) {}
			

		public:
			class Iterator : public std::iterator<std::input_iterator_tag, Entity::ID>
			{
			private:
				uint32_t m_Index;
				std::shared_ptr<EntityManager> m_IteratorEntityManager;
				EntitySelectionPredicate m_SelectionPredicate;


			public:
				Iterator &operator ++()
				{
					++m_Index;
					MoveToNext();
					return *this;
				}

				bool operator == (const Iterator& rhs) const { return m_Index == rhs.m_Index; }
				bool operator != (const Iterator& rhs) const { return m_Index != rhs.m_Index; }


				Entity operator * () { return m_IteratorEntityManager->CreateEntityFromIndex(m_Index); }

				const Entity operator * () const { return m_IteratorEntityManager->CreateEntityFromIndex(m_Index); }

			private:
				void MoveToNext()
				{
					while (
						m_Index < m_IteratorEntityManager->GetEntityCapacity() &&
						(!m_SelectionPredicate(m_IteratorEntityManager->CreateEntityFromIndex(m_Index))))
					{
						++m_Index;
					}
				}

			public:
				Iterator(std::shared_ptr<EntityManager> em, EntitySelectionPredicate pred, uint32_t index) : m_IteratorEntityManager(em), m_SelectionPredicate(pred), m_Index(index)
				{
					MoveToNext();
				};
			};

			Iterator begin() { return Iterator(m_ViewEntityManager, m_SelectionPredicate, 0); }
			Iterator end() { return Iterator(m_ViewEntityManager, m_SelectionPredicate, m_ViewEntityManager->GetEntityCapacity()); }
			const Iterator begin() const { return Iterator(m_ViewEntityManager, m_SelectionPredicate, 0); }
			const Iterator end() const { return Iterator(m_ViewEntityManager, m_SelectionPredicate, m_ViewEntityManager->GetEntityCapacity()); }
		};













		friend class FilteredView::Iterator;

		template <class A, class ... Args>
		FilteredView GetEntitiesWithComponents();

		template <class ... Args>
		FilteredView GetEntitiesWithTags(const std::string& first, const Args& ... args);


	private:
		template <class C>
		std::bitset<emannlib_MAX_COMPONENTS> CreateComponentMask()
		{
			AUTO_PROFILE("EntityManager::CreateComponentMask");
			std::bitset<emannlib_MAX_COMPONENTS> m;
			m.set(C::GetTypeID());
			return m;
		}

		template <class C1, class C2, class ... Components>
		std::bitset<emannlib_MAX_COMPONENTS> CreateComponentMask() { AUTO_PROFILE("EntityManager::CreateComponentMask"); return CreateComponentMask<C1>() | CreateComponentMask<C2, Components ...>(); }

	};

    
}

#include "Entity_Imp.hpp"