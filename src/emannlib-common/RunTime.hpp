//
//  RunTime.hpp
//  emannlibLib
//
//  Created by Evan Ackmann on 5/7/14.
//
//

#ifndef emannlibLib_RunTime_hpp
#define emannlibLib_RunTime_hpp

#include <memory>
#include <list>

#include "Task.hpp"
#include "Singleton.hpp"

namespace emannlib {
    
        class RunTime : public Singleton<RunTime>
        {
        public:
            RunTime();
            virtual ~RunTime();
            
            int Execute();
            
            bool AddTask(std::shared_ptr<emannlib::Task> newTask);
            void SuspendTask(std::shared_ptr<emannlib::Task> newTask);
            void ResumeTask(std::shared_ptr<emannlib::Task> newTask);
            void KillTask(std::shared_ptr<emannlib::Task> newTask);
            void KillAllTasks();
        
        protected:
            std::list< std::shared_ptr<emannlib::Task> >m_RunningTaskList;
            //std::list< std::shared_ptr<emannlib::utility::Task> >m_DeadTaskList;
        };
    
}

#endif
