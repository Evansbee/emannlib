#include "System.hpp"
#include "Entity.hpp"
#include "Event.hpp"

#include "../emannlib-common/AutoProfile.hpp"
#include "../emannlib-common/RunTime.hpp"
#include "../emannlib-common/Task.hpp"




namespace emannlib
{

	System::System(std::shared_ptr<EntityManager> entityMgr, std::shared_ptr<EventManager> eventMgr) :
		m_EntityManager(entityMgr),
		m_EventManager(eventMgr),
		Task(100)
	{

	}



	bool System::Start(){ return true; }
	void System::OnSuspend(){}
	void System::Update(double deltaTime){}
	void System::OnResume(){}
	void System::Stop(){}

}

