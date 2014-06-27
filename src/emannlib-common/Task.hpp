//
//  Task.hpp
//  emannlibLib
//
//  Created by Evan Ackmann on 5/7/14.
//
//

#ifndef emannlibLib_Task_hpp
#define emannlibLib_Task_hpp

struct GLFWwindow;

#include <string>
#include <inttypes.h>


namespace emannlib
{
	class Task
	{
	public:
		Task() :
			m_Priority(5000),
			m_CanKill(false)
		{
		};

		Task(uint32_t prio) :
			m_Priority(prio),
			m_CanKill(false)
		{

		}

		virtual ~Task(){};

		virtual bool Start() = 0;
		virtual void OnSuspend(){};
		virtual void Update(double deltaTime) = 0;
		virtual void OnResume(){};
		virtual void Stop() = 0;
		virtual bool CanKill() const { return m_CanKill; };
		virtual unsigned int GetPriority() const { return m_Priority; };
		virtual void Kill() { m_CanKill = true; };

	protected:
		unsigned int m_Priority;
		bool m_CanKill;
	};

}

#endif
