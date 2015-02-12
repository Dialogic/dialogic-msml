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
// File Name: AObserverSubject.h
//
// Description: AObserverSubject class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AObserverSubject_h
#define AObserverSubject_h

#include "TypeDefs.h"
#include "CTask.h"

#include <map>

#include <boost/thread/mutex.hpp>

const int ALL_NOTIFICATIONS   = 0xFFFFFFFF;

class ATaskHandler;

typedef std::map< ATaskHandler*, ATaskSptr> ATaskHandlerList;
typedef std::map< int, ATaskHandlerList *> ATaskHandlerListByNotificationMap;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AObserverSubject
//
// Description: The abstract Observer Subject class is responsible for 
// maintaining a registry of observers and dispatching function tasks to the 
// observers when notifications are issued.
//
///////////////////////////////////////////////////////////////////////////////
class AObserverSubject
{
public:
   AObserverSubject();
   virtual ~AObserverSubject();

   void RegisterForNotification( ATaskHandler* a_observer, ATaskSptr a_task, int a_notificationID);
   void Unregister( ATaskHandler* a_observer, int a_notificationID = ALL_NOTIFICATIONS);
   int EnumerateNotifications( int a_notifications[], int a_max);
   int EnumerateObservers( ATaskHandler** a_observers, int a_notificationID, int a_max);

protected:  
   template< typename T> 
   void NotifyObservers( int a_notificationID, T& a_data);

   void NotifyObservers( int a_notificationID);

private:
   ATaskHandlerListByNotificationMap m_registrations;
   void RemoveObserver( ATaskHandler* a_observer, ATaskHandlerList* a_observerList);
   boost::mutex m_mapMutex;
};

#include "AObserverSubject_imp.h"
#endif
