#ifndef __system_h__
#define __system_h__

#include "Entity.hpp"
#include "Event.hpp"
#include "../emannlib-common/RunTime.hpp"
#include "../emannlib-common/Task.hpp"


#define GLEW_STATIC
#define GLFW_INCLUDE_GLU
#include "GL\glew.h"
#include "GLFW\glfw3.h"

namespace emannlib
{
	class System : public Task
	{
	private:
		System();
	public:
		System(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr);
	public:
		std::shared_ptr<EntityManager> m_EntityManager;
		std::shared_ptr<EventManager> m_EventManager;

	public:
		virtual bool Start();
		virtual void OnSuspend();
		virtual void Update(double deltaTime);
		virtual void OnResume();
		virtual void Stop();
	};
}

#endif