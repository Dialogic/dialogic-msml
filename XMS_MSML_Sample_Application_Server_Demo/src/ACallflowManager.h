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
// File Name: ACallflowManager.h
//
// Description: ACallflowManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ACallflowManager_h
#define ACallflowManager_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "CallflowManagerStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumCallflowManagerNotifications
//
// Description: Observer notifications supported by the CallflowManager
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   CALLFLOW_MANAGER_STARTED,
   CALLFLOW_MANAGER_STOPPED,
   CALLFLOW_MANAGER_CALLFLOW_AVAILABLE,
   CALLFLOW_MANAGER_CALLFLOW_RESET
} EnumCallflowManagerNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowManager
//
// Description: Tyhe abstract Callflow Manager class implements the public 
// interface and state machine for the Callflow Manager.  The Callflow Manager
// is responsible for managing instances of Callflow objects
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowManager : public ATaskHandler, public AObserverSubject
{
   friend class ACallflowManagerState;
   friend class CCallflowManagerStoppedState;
   friend class CCallflowManagerStartingState;
   friend class CCallflowManagerStartedState;
   friend class CCallflowManagerStoppingState;

public:
   ACallflowManager( CTaskProcessorSptr& a_taskProcessor);
   virtual ~ACallflowManager();

   void Start();
   void OnStarted( int a_result);
   void GetCallflow( AResourceGroupSptr a_resourceGroup);
   void ResetCallflow( ACallflowSptr a_callflow);
   void Stop();
   void OnStopped( int a_result);

   bool IsStopped();
   bool IsStarted();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   virtual ACallflowSptr FindCallflow( AResourceGroupSptr a_resourceGroup) = 0;

protected:
   virtual int PrimStart() = 0;
   virtual int PrimOnStarted( int a_result) = 0;
   virtual int PrimGetCallflow( AResourceGroupSptr a_resourceGroup) = 0;
   virtual int PrimResetCallflow( ACallflowSptr a_callflow) = 0;
   virtual int PrimStop() = 0;
   virtual int PrimOnStopped( int a_result) = 0;

private:
   ACallflowManager();

   void BasicStart();
   void BasicOnStarted( int a_result);
   void BasicGetCallflow( AResourceGroupSptr a_resourceGroup);
   void BasicResetCallflow( ACallflowSptr a_callflow);
   void BasicStop();
   void BasicOnStopped( int a_result);

   void SetStateToStopped();
   void SetStateToStarting();
   void SetStateToStarted();
   void SetStateToStopping();

   ACallflowManagerState* m_state; 
   static CCallflowManagerStoppedState m_stoppedState; 
   static CCallflowManagerStartingState m_startingState; 
   static CCallflowManagerStartedState m_startedState; 
   static CCallflowManagerStoppingState m_stoppingState; 
};

#endif
