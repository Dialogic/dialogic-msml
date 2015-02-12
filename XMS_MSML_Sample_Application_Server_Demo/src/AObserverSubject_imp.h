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
//	File Name:		AObserverSubject_imp.h
//
//	Description:	
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AObserverSubject_imp_h
#define AObserverSubject_imp_h

#include "ATaskHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void AObserverSubject::NotifyObservers(int a_notificationID, T &a_data)
//
// Description: Notify all observers registered to the notification ID
//
// Return: void 
//
// Parameters: int a_notificationID 
//             T &a_data 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T> 
   void AObserverSubject::NotifyObservers( int a_notificationID, T& a_data)
{
   boost::mutex::scoped_lock lock( m_mapMutex);
   ATaskHandlerListByNotificationMap::iterator l_observerList;
   l_observerList = m_registrations.find( a_notificationID);
   if ( l_observerList != m_registrations.end())
   {
      ATaskHandlerList::iterator l_observer;
      for ( l_observer = ( l_observerList->second)->begin();
            l_observer != ( l_observerList->second)->end();
            ++l_observer)
      {
         CTask1< T>* l_task = dynamic_cast < CTask1< T>* > ( ( l_observer->second).get());
         assert( l_task);
         ATaskSptr l_newTask( new CTask1< T>( l_task->TaskFunc(), a_data)); 
         (l_observer->first)->QueueTask( l_newTask);
      }
   }
}

#endif


