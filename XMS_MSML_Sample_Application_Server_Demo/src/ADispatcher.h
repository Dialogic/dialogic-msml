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
// File Name: ADispatcher.h
//
// Description: ADispatcher class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ADispatcher_h
#define ADispatcher_h

#include "TypeDefs.h"
#include "CTask.h"

#include <boost/thread/mutex.hpp>

const int ALL_EVENTS   = 0xFFFFFFFF;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ADispatcher
//
// Description: The abstract Dispatcher class is responsible for maintaining a 
// registry of task handlers and dispatching event tasks to registered handlers.
//
///////////////////////////////////////////////////////////////////////////////
class ADispatcher
{
public:
   ADispatcher();
   virtual ~ADispatcher();

   void RegisterForEventDispatch( ATaskHandler* a_eventHandler, ATaskSptr a_task, long a_event);
   void UnregisterForEventDispatch( ATaskHandler* a_eventHandler, long a_event = ALL_EVENTS);
   int EnumerateEventRegistrations( long a_events[], int a_max);
   int EnumerateEventHandlers( ATaskHandler** a_taskHandlers, long a_event, int a_max);

protected:  
   template< typename T> 
   void DispatchEvent( long a_event, ATaskHandler* a_eventHandler, T& a_data);

private:
   ATaskHandlerListByEventMap m_eventRegistrations;
   void RemoveEventHandler( ATaskHandler* a_eventHandler, ATaskHandlerList* a_eventHandlerList);
   boost::mutex m_mapMutex;
};

#include "ADispatcher_imp.h"
#endif
