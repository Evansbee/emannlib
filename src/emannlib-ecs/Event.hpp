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
File Name     : Event.h
Purpose       :
*/

#pragma once

#include <inttypes.h>

#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <bitset>
#include <functional>
#include <map>
#include <unordered_map>

#include "goldenduck\AutoProfile.hpp"
namespace goldenduck
{
    class BaseEvent
    {
    public:
        virtual ~BaseEvent() {};

    protected:
        static uint32_t ms_TypeIDCounter;
    };

    typedef std::function <void(std::shared_ptr<BaseEvent>)> EventCallback;



    template< class T >
    class Event : public BaseEvent
    {
    public:
        static uint32_t GetTypeID();

    protected:
        friend class EventManager;
    };


    class EventManager 
    {
    public:
        EventManager() {}

        static std::shared_ptr<EventManager> Make()
        {
            return std::make_shared<EventManager>();
        }

        template <class E>
        void RegisterCallback(EventCallback newCallback)
        {
			AUTO_PROFILE("EventManager::RegisterCallback");
            auto it = m_EventCallbackMap.find(E::GetTypeID());
            if (m_EventCallbackMap.end() == it)
            {
                m_EventCallbackMap[E::GetTypeID()] = std::vector<EventCallback>();
                m_EventCallbackMap[E::GetTypeID()].push_back(newCallback);
            }
            else
            {
                it->second.push_back(newCallback);
            }


        }

        template <class E>
        void ClearCallbacks()
        {
			AUTO_PROFILE("EventManager::ClearCallbacks");
            auto it = m_EventCallbackMap.find(E::GetTypeID());
            if (it!=m_EventCallbackMap.end())
            {
                it->second.clear();
            }

        }

        template <class E>
        void Emit(std::shared_ptr<E> EmittedEvent)
        {
			AUTO_PROFILE("EventManager::Emit");
            for (auto fcn : m_EventCallbackMap[E::GetTypeID()])
            {
                fcn(EmittedEvent);
            }
        }

        template <class E, class ... Args>
        void Emit(Args && ... args)
        {
			AUTO_PROFILE("EventManager::Emit");
            Emit(std::make_shared<E>(args ...));
        }

    private:
        std::unordered_map<uint32_t, std::vector<EventCallback>> m_EventCallbackMap;

    };

    template <class T>
    uint32_t Event<T>::GetTypeID()
    {
        static uint32_t typeID = ms_TypeIDCounter++;
        return typeID;
    }

}