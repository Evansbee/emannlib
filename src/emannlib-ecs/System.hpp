#ifndef __system_h__
#define __system_h__

#include "Entity.hpp"
#include "Event.hpp"
#include "../emannlib-utility/RunTime.hpp"
#include "../emannlib-utility/Task.hpp"
#include "Components.hpp"
#include "../emannlib-utility/OpenGLStateMachine.hpp"




#define GLEW_STATIC
#define GLFW_INCLUDE_GLU
#include "GL\glew.h"
#include "GLFW\glfw3.h"

namespace goldenduck
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


	class MovementSystem : public System
	{
	public:
		MovementSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr);
		bool Start();
		void OnSuspend();
		void Update(double deltaTime);
		void OnResume();
		void Stop();
	};

	class RenderSystem : public System
	{
	public:
		RenderSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr);
		bool Start();
		void OnSuspend();
		void Update(double deltaTime);
		void OnResume();
		void Stop();
	};



	class PlayerMovementSystem : public System
	{

	public:
		PlayerMovementSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr);

		bool Start();


		void OnSuspend();
		void Update(double deltaTime);
		void OnResume();
		void Stop();

		void KeyDownCallback(std::shared_ptr<BaseEvent> e);

		void KeyUpCallback(std::shared_ptr<BaseEvent> e);
	};

	class CursorSystem : public System
	{

	public:
		CursorSystem(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr);

		bool Start();
		void Update(double deltaTime);

		void OnSuspend();
		void OnResume();
		void Stop();

		void CursorPositionCallback(std::shared_ptr<BaseEvent> e);
	};

}

#endif