#include "System.hpp"
#include "Entity.hpp"
#include "Event.hpp"
#include "Components.hpp"

#include "../emannlib-utility/AutoProfile.hpp"
#include "../emannlib-utility/RunTime.hpp"
#include "../emannlib-utility/Task.hpp"




namespace goldenduck
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

