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
// File Name: ResourceGroupManagerStates.h
//
// Description: Resource Group Manager state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ResourceGroupManagerStates_h
#define ResourceGroupManagerStates_h

#include "ASipResource.h"

class AResourceGroupManager;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AResourceGroupManagerState
//
// Description: The abstract Resource Group Manager State class and all 
// concrete subclasses comprise a State Pattern implementation of the Resource
// Group Manager state machine.  
//
// The abstract Resource Group Manager state declares all functions 
// supported by the state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class AResourceGroupManagerState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Start( AResourceGroupManager& a_manager);
   virtual void OnStarted( AResourceGroupManager& a_manager, int a_result);
   virtual void GetResourceGroup( AResourceGroupManager& a_manager, ASipResourceSptr a_inboundSipResource);
   virtual void OnResourceGroupAvailable( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup);
   virtual void ResetResourceGroup( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup);
   virtual void OnResourceGroupReset( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup);
   virtual void Stop( AResourceGroupManager& a_manager);
   virtual void OnStopped( AResourceGroupManager& a_manager, int a_result);

private:
   void LogInvalidStateForCommand( AResourceGroupManager& a_manager, const char* a_command, const std::string& a_msg);
   void LogInvalidStateForEvent( AResourceGroupManager& a_manager, const char* a_event, const std::string& a_msg);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupManagerStoppedState
//
// Description: Resource Group Manager stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupManagerStoppedState : public AResourceGroupManagerState
{
public:
   const char* StateDesc() { return "Stopped"; }
   void Start( AResourceGroupManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupManagerStartingState
//
// Description: Resource Group Manager starting state
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupManagerStartingState : public AResourceGroupManagerState
{
public:
   const char* StateDesc() { return "Starting"; }
   void OnStarted( AResourceGroupManager& a_manager, int a_result);
   void Stop( AResourceGroupManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupManagerStartedState
//
// Description: Resource Group Manager started state
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupManagerStartedState : public AResourceGroupManagerState
{
public:
   const char* StateDesc() { return "Started"; }
   void GetResourceGroup( AResourceGroupManager& a_manager, ASipResourceSptr a_inboundSipResource);
   void OnResourceGroupAvailable( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup);
   void ResetResourceGroup( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup);
   void OnResourceGroupReset( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup);
   void Stop( AResourceGroupManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupManagerStoppingState
//
// Description: Resource Group Manager stopping state
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupManagerStoppingState : public AResourceGroupManagerState
{
public:
   const char* StateDesc() { return "Stopping"; }
   void OnStopped( AResourceGroupManager& a_manager, int a_result);
};

#endif
