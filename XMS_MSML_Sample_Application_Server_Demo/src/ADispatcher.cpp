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
// File Name: ADispatcher.cpp
//
// Description: ADispatcher class implementation
//
///////////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786) 

#include "ADispatcher.h"
#include "ATaskHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Function: ADispatcher::ADispatcher()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ADispatcher::ADispatcher()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ADispatcher::~ADispatcher()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ADispatcher::~ADispatcher()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ADispatcher::RegisterForEventDispatch(ATaskHandler *a_eventHandler, ATaskSptr a_task, long a_event)
//
// Description: Register a task handler and task object to be dispatched for an event
//
// Return: void
//
// Parameters: ATaskHandler *a_eventHandler
//             ATaskSptr a_task
//             long a_event
//
///////////////////////////////////////////////////////////////////////////////
void ADispatcher::RegisterForEventDispatch( ATaskHandler* a_eventHandler, ATaskSptr a_task, long a_event)
{
    boost::mutex::scoped_lock lock( m_mapMutex);

    ATaskHandlerListByEventMap::iterator l_eventHandlerList;
    l_eventHandlerList = m_eventRegistrations.find( a_event);
    if ( l_eventHandlerList == m_eventRegistrations.end())
    {
        ATaskHandlerList* l_newEventHandlerList = new ATaskHandlerList;
        l_newEventHandlerList->insert( std::make_pair( a_eventHandler, a_task));
        m_eventRegistrations[a_event] = l_newEventHandlerList;
    }
    else
    {
        m_eventRegistrations[a_event]->insert( std::make_pair( a_eventHandler, a_task));
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ADispatcher::UnregisterForEventDispatch(ATaskHandler *a_eventHandler, long a_event)
//
// Description: Unregister an event handler for an event.  To unregister a 
// task handler for all events, set the event parameter to ALL_EVENTS.
//
// Return: void
//
// Parameters: ATaskHandler *a_eventHandler
//             long a_event
//
///////////////////////////////////////////////////////////////////////////////
void ADispatcher::UnregisterForEventDispatch( ATaskHandler* a_eventHandler, long a_event)
{
    boost::mutex::scoped_lock l_lock( m_mapMutex);

    ATaskHandlerListByEventMap::iterator l_eventHandlerList;
    if ( a_event == ALL_EVENTS)
    {
        for (  l_eventHandlerList = m_eventRegistrations.begin();
               l_eventHandlerList != m_eventRegistrations.end();
               ++l_eventHandlerList)
        {
         ( l_eventHandlerList->second)->erase( a_eventHandler);
        }
    }
    else
    {
        l_eventHandlerList = m_eventRegistrations.find( a_event);
        if ( l_eventHandlerList != m_eventRegistrations.end())
        {
         ( l_eventHandlerList->second)->erase( a_eventHandler);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ADispatcher::EnumerateEventRegistrations(long a_events[], int a_max)
//
// Description: Fill an array with all events for which there are registrations
//
// Return: int - the number of events that have been registered for
//
// Parameters: long a_events[]
//             int a_max
//
///////////////////////////////////////////////////////////////////////////////
int ADispatcher::EnumerateEventRegistrations( long a_events[], int a_max)
{
    ATaskHandlerListByEventMap::iterator l_eventHandlerList;
    int i;

    for (   i=0, l_eventHandlerList = m_eventRegistrations.begin();
            l_eventHandlerList != m_eventRegistrations.end() && i < a_max;
            ++l_eventHandlerList, i++)
    {
        a_events[i] = l_eventHandlerList->first;
    }
    return i;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ADispatcher::EnumerateEventHandlers(ATaskHandler **a_taskHandlers, long a_event, int a_max)
//
// Description: Fill an array with an array with task handlers that are 
// registered for an event
//
// Return: int - the number ot task handlers that are registered
//
// Parameters: ATaskHandler **a_taskHandlers
//             long a_event
//             int a_max
//
///////////////////////////////////////////////////////////////////////////////
int ADispatcher::EnumerateEventHandlers( ATaskHandler** a_taskHandlers, long a_event, int a_max)
{
    ATaskHandlerListByEventMap::iterator l_eventHandlerList;
    int i=0;

    l_eventHandlerList = m_eventRegistrations.find( a_event);
    if ( l_eventHandlerList != m_eventRegistrations.end())
    {
        ATaskHandlerList::iterator l_eventHandler;
        if ( ( l_eventHandlerList->second)->size() > 0 )
        {
            for ( i=0, l_eventHandler = ( l_eventHandlerList->second)->begin();
                  l_eventHandler != ( l_eventHandlerList->second)->end() && i < a_max;
                  ++l_eventHandler, i++)
            {
               a_taskHandlers[i] = l_eventHandler->first;
            }
        }
    }
    return i;
}
