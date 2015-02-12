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
// File Name: CTaskProcessor.h
//
// Description: CTaskProcessor class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CTaskProcessor_h
#define CTaskProcessor_h

#include "TypeDefs.h"
#include "CTask.h"
#include "LoggerDefs.h"

#include <queue>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::WorkerThreadState
//
// Description: Task processor states
//
///////////////////////////////////////////////////////////////////////////////
typedef enum 
{
   TASK_PROCESSOR_STOPPED,
   TASK_PROCESSOR_STARTING,
   TASK_PROCESSOR_RUNNING,
   TASK_PROCESSOR_STOPPING
} WorkerThreadState;

///////////////////////////////////////////////////////////////////////////////
// Class: ::CTaskProcessor
//
// Description: The Task processor is responsible for maintaining a queue of 
// tasks and executing them in a worker thread.
//
///////////////////////////////////////////////////////////////////////////////
class CTaskProcessor : boost::noncopyable
{
public:
   CTaskProcessor();
   virtual ~CTaskProcessor();

   int Start();
   int Stop();
   int QueueTask( ATaskSptr& a_task); 

   LogObjectTypeEnum LogObjectType();

   const char* ClassName();
   const std::string& Name();
   const char* StateDesc();

   bool IsRunning();

private:
   WorkerThreadState m_state;
   boost::shared_ptr<boost::thread> m_thread;
   boost::mutex m_controlMutex;
   boost::mutex m_queueMutex;
   boost::mutex m_semaphoreMutex;
   boost::condition m_semaphore;
   std::queue< ATaskSptr> m_queue;
   std::string m_idString;

   void ProcessTasks();
};

#endif
