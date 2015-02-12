///////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2006-2012 Dialogic Inc. All Rights Reserved.
//
// The source code contained or described herein and all documents related to
// the source code (collectively "Material") are owned by Dialogic Inc.,
// its subsidiaries, affiliates, suppliers, licensors and/or assigns 
// ("Dialogic"). Title to the Material remains with Dialogic. The Material 
// contains proprietary information and material of Dialogic. The Material is 
// protected by worldwide copyright, trade secret laws, treaty provisions 
// and/or other applicable intellectual property rights, laws and/or treaties.
// No part of the Material may be used, copied, reproduced, modified, 
// published, uploaded, posted, transmitted, distributed, or disclosed in any 
// way without Dialogic's prior express written permission.
//
// No license under any patent, copyright, trade secret or other intellectual
// property right is granted to or conferred upon you by disclosure or delivery
// of the Material, either expressly, by implication, inducement, estoppels
// or otherwise. Any license under such intellectual property rights must be
// express and approved by Dialogic in writing.
//
///////////////////////////////////////////////////////////////////////////////
// File Name: CTaskProcessor.cpp
//
// Description: CTaskProcessor class implementation
//
///////////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786)

#include "CTaskProcessor.h"
#include "CLogger.h"
#include "Utility.h"

#include <string>
#include <queue>

#include <boost/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
// Function: CTaskProcessor::CTaskProcessor()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CTaskProcessor::CTaskProcessor() 
   : m_state( TASK_PROCESSOR_STOPPED), m_idString("TaskProcessor")
{}
   
///////////////////////////////////////////////////////////////////////////////
// Function: CTaskProcessor::~CTaskProcessor()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CTaskProcessor::~CTaskProcessor()
{}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CTaskProcessor::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CTaskProcessor::ClassName()
{
   return "CTaskProcessor";
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string& CTaskProcessor::Name()
//
// Description: Acess the object name
//
// Return: const std::string& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CTaskProcessor::Name()
{
   return m_idString;
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum CTaskProcessor::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum CTaskProcessor::LogObjectType()
{
   return LogObject_System;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CTaskProcessor::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CTaskProcessor::StateDesc() 
{ 
   switch (m_state)
   {
   case TASK_PROCESSOR_STOPPED:
      return "Stopping";
   case TASK_PROCESSOR_STARTING:
      return "Starting";
   case  TASK_PROCESSOR_RUNNING:
      return "Running";
   case  TASK_PROCESSOR_STOPPING:
      return "Stopping";
   }
   return "unknown";
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CTaskProcessor::IsRunning()
//
// Description: Test if the Task Processor is running
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool CTaskProcessor::IsRunning()
{
   return m_state == TASK_PROCESSOR_RUNNING;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CTaskProcessor::Start()
//
// Description: Start the TaskProcessor by starting the worker thread
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CTaskProcessor::Start()
{
   boost::mutex::scoped_lock l_controlLock( m_controlMutex);
   if ( m_state == TASK_PROCESSOR_STOPPED )
   {
      m_state = TASK_PROCESSOR_STARTING;
      m_thread = boost::shared_ptr< boost::thread> (new boost::thread( boost::bind( &CTaskProcessor::ProcessTasks, this)));
      return 0;
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CTaskProcessor::Stop()
//
// Description: Signal the worker thread to stop, wait fot the thread to exit, 
// then flush the task queue.
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CTaskProcessor::Stop()
{
   boost::mutex::scoped_lock l_controlLock( m_controlMutex);
   if ( m_state == TASK_PROCESSOR_RUNNING )
   {
      m_state = TASK_PROCESSOR_STOPPING;
      m_semaphore.notify_one();
      m_thread->join();

      while ( ! m_queue.empty())
      {
         m_queue.pop();
      }

      m_state = TASK_PROCESSOR_STOPPED;

      CLogger::Instance()->Log( LOG_LEVEL_ALWAYS, *this, "Stop", "stopped");

      return 0;
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CTaskProcessor::QueueTask(ATaskSptr &task)
//
// Description: Add a task to the queue
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ATaskSptr &task
//
///////////////////////////////////////////////////////////////////////////////
int CTaskProcessor::QueueTask( ATaskSptr& task) 
{ 
   if ( m_state == TASK_PROCESSOR_RUNNING )
   {
      { // scope for lock
         boost::mutex::scoped_lock l_lock( m_queueMutex);
         m_queue.push( task);
      }
      m_semaphore.notify_one();
      return 0;
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CTaskProcessor::ProcessTasks()
//
// Description: Wait for tasks on the queue and execute them as they arrive
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CTaskProcessor::ProcessTasks()
{
   m_idString = "TaskProcessor-" + AsHexString( ThreadID());
   ATaskSptr l_task;
   boost::mutex::scoped_lock semaphoreLock( m_semaphoreMutex);

   { // scope for lock
      boost::mutex::scoped_lock l_controlLock( m_controlMutex);
      m_state = TASK_PROCESSOR_RUNNING;
   }

   CLogger::Instance()->Log( LOG_LEVEL_ALWAYS, *this, "ProcessTasks", "started");

   while( m_state == TASK_PROCESSOR_RUNNING )
   {
      if ( m_queue.empty())
      {
         m_semaphore.wait(semaphoreLock);
      }

      {  // scope for lock
         boost::mutex::scoped_lock l_queueLock( m_queueMutex);
         if ( !m_queue.empty ())
         {
            l_task = m_queue.front();
            m_queue.pop();
         }
         else
         {
            continue;
         }
      }

      try
      {
         (*l_task)();
      }
      catch(...)
      {
		   std::string l_debugInfo = "Caught Exception! debug info: " + AsString( l_task->DebugInfo());
         CLogger::Instance()->Log( LOG_LEVEL_ERROR, *this, "ProcessTasks", l_debugInfo);
         // TODO: add logging of any data associated with the task
      }
      l_task.reset();
   }
}

