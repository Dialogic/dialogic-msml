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
// File Name: ASrlEventManager.h
//
// Description: ASrlEventManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ASrlEventManager_h
#define ASrlEventManager_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "SrlEventManagerStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumSrlEventManagerNotifications
//
// Description: Observer notifications supported by the SRL Event Manager
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   SRLEVENT_MANAGER_STARTED,
   SRLEVENT_MANAGER_STOPPED,
   SRLEVENT_MANAGER_SRLEVENT_AVAILABLE,
   SRLEVENT_MANAGER_SRLEVENT_RESET
} EnumSrlEventManagerNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASrlEventManager
//
// Description: The abstract SRL Event Manager class implements the public 
// interface and state machine for the concrete SRL Event Manager class.  The
// SRL Event Manager is responsible for handling all SRL and GC events by 
// saving event data and dispatching event tasks to the target objects.
//
///////////////////////////////////////////////////////////////////////////////
class ASrlEventManager : public ATaskHandler, public AObserverSubject
{
   friend class ASrlEventManagerState;
   friend class CSrlEventManagerStoppedState;
   friend class CSrlEventManagerStartingState;
   friend class CSrlEventManagerStartedState;
   friend class CSrlEventManagerStoppingState;

public:
   void Start();
   void OnStarted( int a_result);
   void Stop();
   void OnStopped( int a_result);

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   bool IsStarted();
   bool IsStopping();
   bool IsStopped();

protected:
   ASrlEventManager();
   ASrlEventManager( CTaskProcessorSptr& a_taskProcessor);
   virtual ~ASrlEventManager();

   virtual int PrimStart() = 0;
   virtual int PrimOnStarted( int a_result) = 0;
   virtual int PrimStop() = 0;
   virtual int PrimOnStopped( int a_result) = 0;

private:
   void BasicStart();
   void BasicOnStarted( int a_result);
   void BasicStop();
   void BasicOnStopped( int a_result);

   void SetStateToStopped();
   void SetStateToStarting();
   void SetStateToStarted();
   void SetStateToStopping();

   ASrlEventManagerState* m_state; 
   static CSrlEventManagerStoppedState m_stoppedState; 
   static CSrlEventManagerStartingState m_startingState; 
   static CSrlEventManagerStartedState m_startedState; 
   static CSrlEventManagerStoppingState m_stoppingState; 
};

#endif
