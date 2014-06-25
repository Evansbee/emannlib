//
//  RunTime.cpp
//  goldenduckLib
//
//  Created by Evan Ackmann on 5/7/14.
//
//

#include <memory>
#include <list>
#include <chrono>
#include <thread>

#include "goldenduck/RunTime.hpp"
#include "goldenduck/Task.hpp"
#include "goldenduck/AutoProfile.hpp"
#include "goldenduck/Time.hpp"

namespace goldenduck {
   
        RunTime::RunTime(){}
        RunTime::~RunTime(){}
        
        int RunTime::Execute(){

            //AUTO_PROFILE("Runtime::Execute");
		
			double currentTime = Time::GetCurrentTime();
			double lastTime = currentTime;

			while(m_RunningTaskList.size())
            {
				AUTO_PROFILE("Runtime::RunLoop");
				currentTime = Time::GetCurrentTime();

				double dt = currentTime - lastTime;
                for(auto it = m_RunningTaskList.begin(); it != m_RunningTaskList.end();)
                {
                    std::shared_ptr<goldenduck::Task> task = (*it);
                    it++;
                    if(!task->CanKill())
                    {
						task->Update(dt);
                    }
                }
                
                //nuke running stuff
                for(auto it = m_RunningTaskList.begin(); it != m_RunningTaskList.end();)
                {
                    std::shared_ptr<goldenduck::Task> task = (*it);
                    it++;
                    if(task->CanKill())
                    {
                        task->Stop();
                        m_RunningTaskList.remove(task);
                        task = nullptr;
                    }
                }

				//std::this_thread::sleep_until(currentTime + std::chrono::duration<double>(1.0 / 60.0));
				lastTime = currentTime;
            }
            return 0;
        }
        
        bool RunTime::AddTask(std::shared_ptr<goldenduck::Task> newTask)
        {
            AUTO_PROFILE("Runtime::AddTask");
            if(!newTask->Start())
            {
                return false;
            }
            auto it = m_RunningTaskList.begin();
            for(; it != m_RunningTaskList.end();++it)
            {
                std::shared_ptr<goldenduck::Task> task = (*it);
                if(task->GetPriority() > newTask->GetPriority())
                {
                    break;
                }
            }
            m_RunningTaskList.insert(it,newTask);
            return true;
        }
        void RunTime::SuspendTask(std::shared_ptr<goldenduck::Task> newTask)
        {
            AUTO_PROFILE("Runtime::SuspendTask");
            if(std::find(m_RunningTaskList.begin(),m_RunningTaskList.end(),newTask) != m_RunningTaskList.end())
            {
                newTask->OnSuspend();
                m_RunningTaskList.remove(newTask);
                //m_P
            }
        }
        void RunTime::ResumeTask(std::shared_ptr<goldenduck::Task> newTask)
        {
            AUTO_PROFILE("Runtime::ResumeTask");
			if (std::find(m_RunningTaskList.begin(), m_RunningTaskList.end(), newTask) != m_RunningTaskList.end())
			{
				newTask->OnResume();
				m_RunningTaskList.remove(newTask);
				//m_P
			}
        }
        void RunTime::KillTask(std::shared_ptr<goldenduck::Task> newTask)
        {
             AUTO_PROFILE("Runtime::KillTask");
			 if (std::find(m_RunningTaskList.begin(), m_RunningTaskList.end(), newTask) != m_RunningTaskList.end())
			 {
				 newTask->Kill();
			 }
        }
        
        void RunTime::KillAllTasks()
		{
			AUTO_PROFILE("Runtime::KillAllTasks");
			//nuke running stuff
			for (auto it = m_RunningTaskList.begin(); it != m_RunningTaskList.end();)
			{
				std::shared_ptr<goldenduck::Task> task = (*it);
				
				it++;
				

				task->Kill();
			}
             
        }
    
}