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
//	File Name:		ADispatcher_imp.h
//
//	Description:	ADispatcher class template implementations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ADispatcher_imp_h
#define ADispatcher_imp_h

#include "ATaskHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void ADispatcher::DispatchEvent(long a_event, ATaskHandler *a_eventHandler, T &a_data)
//
// Description: Create a task object for the event and queue the task to the target
//
// Return: void 
//
// Parameters: long a_event 
//             ATaskHandler *a_eventHandler 
//             T &a_data 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T> 
void ADispatcher::DispatchEvent( long a_event, ATaskHandler* a_eventHandler, T& a_data)
{
   boost::mutex::scoped_lock lock( m_mapMutex);
   ATaskHandlerListByEventMap::iterator l_eventHandlerList;
   l_eventHandlerList = m_eventRegistrations.find( a_event);
   if ( l_eventHandlerList != m_eventRegistrations.end())
   {
      ATaskHandlerList::iterator l_eventHandler;
      l_eventHandler = (l_eventHandlerList->second)->find( a_eventHandler);
      if ( l_eventHandler != (l_eventHandlerList->second)->end())
      {
         CTask1< T>* l_task = dynamic_cast < CTask1< T>* > ( ( l_eventHandler->second).get());
         assert( l_task);
         ATaskSptr l_newTask( new CTask1< T>( l_task->TaskFunc(), a_data)); 
         (l_eventHandler->first)->QueueTask( l_newTask);
      }
   }
}

#endif


