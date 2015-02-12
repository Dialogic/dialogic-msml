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
// File Name: AResourceGroupManager.h
//
// Description: AResourceGroupManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AResourceGroupManager_h
#define AResourceGroupManager_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "ResourceGroupManagerStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumResourceGroupManagerNotifications
//
// Description: Observer notifications supported by Resource Group Manager 
// objects
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   RESOURCEGROUP_MANAGER_STARTED,
   RESOURCEGROUP_MANAGER_STOPPED,
   RESOURCEGROUP_MANAGER_GROUP_AVAILABLE,
   RESOURCEGROUP_MANAGER_GROUP_RESET
} EnumResourceGroupManagerNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AResourceGroupManager
//
// Description: The abstract Resource Group Manager class implements the public
// interface and state machine for the concrete Resource Group Manager class.
// The Resource Group Manager is responsible for managing Resource Group 
// objects.
//
///////////////////////////////////////////////////////////////////////////////
class AResourceGroupManager : public ATaskHandler, public AObserverSubject
{
   friend class AResourceGroupManagerState;
   friend class CResourceGroupManagerStoppedState;
   friend class CResourceGroupManagerStartingState;
   friend class CResourceGroupManagerStartedState;
   friend class CResourceGroupManagerStoppingState;

public:
   AResourceGroupManager( CTaskProcessorSptr a_taskProcessor);
   virtual ~AResourceGroupManager();

   void Start();
   void OnStarted( int a_result);
   void GetResourceGroup( ASipResourceSptr a_inboundSipResource);
   void OnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup);
   void ResetResourceGroup( AResourceGroupSptr a_resourceGroup);
   void OnResourceGroupReset( AResourceGroupSptr a_resourceGroup);
   void Stop();
   void OnStopped( int a_result);

   bool IsStopped();
   bool IsStarted();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   virtual AResourceGroupSptr FindResourceGroup( ASipResourceSptr a_sipResource) = 0;

protected:
   virtual int PrimStart() = 0;
   virtual int PrimOnStarted( int a_result) = 0;
   virtual int PrimGetResourceGroup( ASipResourceSptr a_inboundSipResource) = 0;
   virtual int PrimOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup) = 0;
   virtual int PrimResetResourceGroup( AResourceGroupSptr a_resourceGroup) = 0;
   virtual int PrimOnResourceGroupReset( AResourceGroupSptr a_resourceGroup) = 0;
   virtual int PrimStop() = 0;
   virtual int PrimOnStopped( int a_result) = 0;

private:
   AResourceGroupManager();

   void BasicStart();
   void BasicOnStarted( int a_result);
   void BasicGetResourceGroup( ASipResourceSptr a_inboundSipResource);
   void BasicOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup);
   void BasicResetResourceGroup( AResourceGroupSptr a_resourceGroup);
   void BasicOnResourceGroupReset( AResourceGroupSptr a_resourceGroup);
   void BasicStop();
   void BasicOnStopped( int a_result);

   void SetStateToStopped();
   void SetStateToStarting();
   void SetStateToStarted();
   void SetStateToStopping();

   AResourceGroupManagerState* m_state; 
   static CResourceGroupManagerStoppedState m_stoppedState; 
   static CResourceGroupManagerStartingState m_startingState; 
   static CResourceGroupManagerStartedState m_startedState; 
   static CResourceGroupManagerStoppingState m_stoppingState; 
};

#endif


