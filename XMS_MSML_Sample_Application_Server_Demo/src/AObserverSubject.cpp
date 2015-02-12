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
// File Name: AObserverSubject.cpp
//
// Description: AObserverSubject class implementation
//
///////////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786) 

#include "AObserverSubject.h"
#include "ATaskHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Function: AObserverSubject::AObserverSubject()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
AObserverSubject::AObserverSubject()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: AObserverSubject::~AObserverSubject()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
AObserverSubject::~AObserverSubject()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AObserverSubject::RegisterForNotification(ATaskHandler *a_observer, ATaskSptr a_task, int a_notificationID)
//
// Description: Register an observer and task for an observer notification ID
//
// Return: void
//
// Parameters: ATaskHandler *a_observer
//             ATaskSptr a_task
//             int a_notificationID
//
///////////////////////////////////////////////////////////////////////////////
void AObserverSubject::RegisterForNotification( ATaskHandler* a_observer, ATaskSptr a_task, int a_notificationID)
{
    boost::mutex::scoped_lock lock( m_mapMutex);

    ATaskHandlerListByNotificationMap::iterator l_observerList;
    l_observerList = m_registrations.find( a_notificationID);
    if ( l_observerList == m_registrations.end())
    {
        ATaskHandlerList* l_newObserverList = new ATaskHandlerList;
        l_newObserverList->insert( std::make_pair( a_observer, a_task));
        m_registrations[a_notificationID] = l_newObserverList;
    }
    else
    {
        m_registrations[a_notificationID]->insert( std::make_pair( a_observer, a_task));
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AObserverSubject::Unregister(ATaskHandler *a_observer, int a_notificationID)
//
// Description: Unregister an observer for an observer notification.  An 
// observer is unregistered for all notifications by setting the notification 
// ID to ALL_NOTIFICATIONS
//
// Return: void
//
// Parameters: ATaskHandler *a_observer
//             int a_notificationID
//
///////////////////////////////////////////////////////////////////////////////
void AObserverSubject::Unregister( ATaskHandler* a_observer, int a_notificationID)
{
    boost::mutex::scoped_lock l_lock( m_mapMutex);

    ATaskHandlerListByNotificationMap::iterator l_observerList;
    if ( a_notificationID == ALL_NOTIFICATIONS)
    {
        for (  l_observerList = m_registrations.begin();
               l_observerList != m_registrations.end();
               ++l_observerList)
        {
         ( l_observerList->second)->erase( a_observer);
        }
    }
    else
    {
        l_observerList = m_registrations.find( a_notificationID);
        if ( l_observerList != m_registrations.end())
        {
         ( l_observerList->second)->erase( a_observer);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AObserverSubject::NotifyObservers(int a_notificationID)
//
// Description: Notify all observers registered for an observer notification ID
//
// Return: void
//
// Parameters: int a_notificationID
//
///////////////////////////////////////////////////////////////////////////////
void AObserverSubject::NotifyObservers( int a_notificationID)
{
   boost::mutex::scoped_lock l_lock( m_mapMutex);
   ATaskHandlerListByNotificationMap::iterator l_observerList;
   l_observerList = m_registrations.find( a_notificationID);
   if ( l_observerList != m_registrations.end())
   {
      ATaskHandlerList::iterator l_observer;
      for ( l_observer = ( l_observerList->second)->begin();
            l_observer != ( l_observerList->second)->end();
            ++l_observer)
      {
         CTask0* l_task = dynamic_cast < CTask0* > ( ( l_observer->second).get() );
         if ( l_task)
         {
            ATaskSptr l_newTask( new CTask0( l_task->TaskFunc())); 
            ( l_observer->first)->QueueTask( l_newTask);
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AObserverSubject::EnumerateNotifications(int a_notifications[], int a_max)
//
// Description: Fill an array with notification IDs that hacve been registered for.
//
// Return: int - the number of notification IDs that have bneen registered for
//
// Parameters: int a_notifications[]
//             int a_max
//
///////////////////////////////////////////////////////////////////////////////
int AObserverSubject::EnumerateNotifications( int a_notifications[], int a_max)
{
    ATaskHandlerListByNotificationMap::iterator l_observerList;
    int i;

    for (   i=0, l_observerList = m_registrations.begin();
            l_observerList != m_registrations.end() && i < a_max;
            ++l_observerList, i++)
    {
        a_notifications[i] = l_observerList->first;
    }
    return i;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AObserverSubject::EnumerateObservers(ATaskHandler **a_observers, int a_notificationID, int a_max)
//
// Description: Fill an array with all observers registered for an observer notification ID
//
// Return: int - the number of observers registered
//
// Parameters: ATaskHandler **a_observers
//             int a_notificationID
//             int a_max
//
///////////////////////////////////////////////////////////////////////////////
int AObserverSubject::EnumerateObservers( ATaskHandler** a_observers, int a_notificationID, int a_max)
{
    ATaskHandlerListByNotificationMap::iterator l_observerList;
    int i=0;

    l_observerList = m_registrations.find( a_notificationID);
    if ( l_observerList != m_registrations.end())
    {
        ATaskHandlerList::iterator l_observer;
        if ( ( l_observerList->second)->size() > 0 )
        {
            for ( i=0, l_observer = ( l_observerList->second)->begin();
                  l_observer != ( l_observerList->second)->end() && i < a_max;
                  ++l_observer, i++)
            {
               a_observers[i] = l_observer->first;
            }
        }
    }
    return i;
}
