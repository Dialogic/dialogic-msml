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
// File Name: AResourceManager.h
//
// Description: AResourceManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AResourceManager_h
#define AResourceManager_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "ResourceManagerStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumResourceManagerNotifications
//
// Description: Observer notifications supported by Resource Manager
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   RESOURCE_MANAGER_STARTED,
   RESOURCE_MANAGER_STOPPED
} EnumResourceManagerNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AResourceManager
//
// Description: The abstract Resource Manager class implements the public 
// interface and state machine for the concrete Resource Manager.  The Resource
// Manager is responsible for starting and stopping other managers, obtaining 
// Resource Group and Callflow objects in response to an inbouind call, and 
// freeing resource at the end of a call.
//
///////////////////////////////////////////////////////////////////////////////
class AResourceManager : public ATaskHandler, public AObserverSubject
{
   friend class AResourceManagerState;
   friend class CResourceManagerStoppedState;
   friend class CResourceManagerStartingState;
   friend class CResourceManagerStartedState;
   friend class CResourceManagerStoppingState;

public:
   AResourceManager( CTaskProcessorSptr a_taskProcessor);
   virtual ~AResourceManager();

   void Start();
   void OnCallflowManagerStarted( int a_result);
   void OnResourceGroupManagerStarted( int a_result);
   void OnSipResourceManagerStarted( int a_result);
   void OnStarted( int a_result);
   void OnCallOffered( const ASipResourceSptr& a_sipResource);
   void OnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup);
   void OnResourceGroupReset( AResourceGroupSptr a_resourceGroup);
   void OnCallflowAvailable( ACallflowSptr a_callflow);
   void OnCallflowReset( ACallflowSptr a_callflow);
   void OnCallDisconnected( const ASipResourceSptr& a_sipResource);
   void Stop();
   void OnCallflowManagerStopped( int a_result);
   void OnResourceGroupManagerStopped( int a_result);
   void OnSipResourceManagerStopped( int a_result);
   void OnStopped( int a_result);

   bool IsStopped();
   bool IsStarted();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

protected:
   virtual int PrimStart() = 0;
   virtual int PrimOnCallflowManagerStarted( int a_result) = 0;
   virtual int PrimOnResourceGroupManagerStarted( int a_result) = 0;
   virtual int PrimOnSipResourceManagerStarted( int a_result) = 0;
   virtual int PrimOnStarted( int a_result) = 0;
   virtual int PrimOnCallOffered( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup) = 0;
   virtual int PrimOnResourceGroupReset( AResourceGroupSptr a_resourceGroup) = 0;
   virtual int PrimOnCallflowAvailable( ACallflowSptr a_callflow) = 0;
   virtual int PrimOnCallflowReset( ACallflowSptr a_callflow) = 0;
   virtual int PrimOnCallDisconnected( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimStop() = 0;
   virtual int PrimOnCallflowManagerStopped( int a_result) = 0;
   virtual int PrimOnResourceGroupManagerStopped( int a_result) = 0;
   virtual int PrimOnSipResourceManagerStopped( int a_result) = 0;
   virtual int PrimOnStopped( int a_result) = 0;

private:
   AResourceManager();

   void BasicStart();
   void BasicOnCallflowManagerStarted( int a_result);
   void BasicOnResourceGroupManagerStarted( int a_result);
   void BasicOnSipResourceManagerStarted( int a_result);
   void BasicOnStarted( int a_result);
   void BasicOnCallOffered( const ASipResourceSptr& a_sipResource);
   void BasicOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup);
   void BasicOnResourceGroupReset( AResourceGroupSptr a_resourceGroup);
   void BasicOnCallflowAvailable( ACallflowSptr a_callflow);
   void BasicOnCallflowReset( ACallflowSptr a_callflow);
   void BasicOnCallDisconnected( const ASipResourceSptr& a_sipResource);
   void BasicStop();
   void BasicOnCallflowManagerStopped( int a_result);
   void BasicOnResourceGroupManagerStopped( int a_result);
   void BasicOnSipResourceManagerStopped( int a_result);
   void BasicOnStopped( int a_result);

   void SetStateToStopped();
   void SetStateToStarting();
   void SetStateToStarted();
   void SetStateToStopping();

   AResourceManagerState* m_state; 
   static CResourceManagerStoppedState m_stoppedState; 
   static CResourceManagerStartingState m_startingState; 
   static CResourceManagerStartedState m_startedState; 
   static CResourceManagerStoppingState m_stoppingState; 
};

#endif
