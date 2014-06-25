//
//  RunTime.hpp
//  goldenduckLib
//
//  Created by Evan Ackmann on 5/7/14.
//
//

#ifndef goldenduckLib_RunTime_hpp
#define goldenduckLib_RunTime_hpp

#include <memory>
#include <list>

#include "Task.hpp"
#include "Singleton.hpp"

namespace goldenduck {
    
        class RunTime : public Singleton<RunTime>
        {
        public:
            RunTime();
            virtual ~RunTime();
            
            int Execute();
            
            bool AddTask(std::shared_ptr<goldenduck::Task> newTask);
            void SuspendTask(std::shared_ptr<goldenduck::Task> newTask);
            void ResumeTask(std::shared_ptr<goldenduck::Task> newTask);
            void KillTask(std::shared_ptr<goldenduck::Task> newTask);
            void KillAllTasks();
        
        protected:
            std::list< std::shared_ptr<goldenduck::Task> >m_RunningTaskList;
            //std::list< std::shared_ptr<goldenduck::utility::Task> >m_DeadTaskList;
        };
    
}

#endif
