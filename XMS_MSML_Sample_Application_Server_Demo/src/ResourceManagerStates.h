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
// File Name: ResourceManagerStates.h
//
// Description: Resource Manager state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ResourceManagerStates_h
#define ResourceManagerStates_h

#include "TypeDefs.h"

#include <string>

class AResourceManager;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AResourceManagerState
//
// Description: The abstract Resource Manager State class and all concrete 
// subclasses comprise a State Pattern implementation of the Resource Manager 
// state machine.  
//
// The abstract Resource Manager state declares all functions supported by the 
// state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class AResourceManagerState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Start( AResourceManager& a_manager);
   virtual void Stop( AResourceManager& a_manager);
   virtual void OnCallflowManagerStarted( AResourceManager& a_manager, int a_result);
   virtual void OnResourceGroupManagerStarted( AResourceManager& a_manager, int a_result);
   virtual void OnSipResourceManagerStarted( AResourceManager& a_manager, int a_result);
   virtual void OnStarted( AResourceManager& a_manager, int a_result);
   virtual void OnCallOffered( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   virtual void OnResourceGroupAvailable( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup);
   virtual void OnResourceGroupReset( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup);
   virtual void OnCallflowAvailable( AResourceManager& a_manager, ACallflowSptr a_callflow);
   virtual void OnCallflowReset( AResourceManager& a_manager, ACallflowSptr a_callflow);
   virtual void OnCallDisconnected( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   virtual void OnCallflowManagerStopped( AResourceManager& a_manager, int a_result);
   virtual void OnResourceGroupManagerStopped( AResourceManager& a_manager, int a_result);
   virtual void OnSipResourceManagerStopped( AResourceManager& a_manager, int a_result);
   virtual void OnStopped( AResourceManager& a_manager, int a_result);

private:
   void LogInvalidStateForCommand( AResourceManager& a_manager, const char*  a_command, const std::string& a_msg);
   void LogInvalidStateForEvent( AResourceManager& a_manager, const char*  a_event, const std::string& a_msg);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceManagerStoppedState
//
// Description: Resource Manager stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CResourceManagerStoppedState : public AResourceManagerState
{
public:
   const char* StateDesc() { return "Stopped"; }
   void Start( AResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceManagerStartingState
//
// Description: Resource Manager stopped starting
//
///////////////////////////////////////////////////////////////////////////////
class CResourceManagerStartingState : public AResourceManagerState
{
public:
   const char* StateDesc() { return "Starting"; }
   void OnCallflowManagerStarted( AResourceManager& a_manager, int a_result);
   void OnResourceGroupManagerStarted( AResourceManager& a_manager, int a_result);
   void OnSipResourceManagerStarted( AResourceManager& a_manager, int a_result);
   void OnStarted( AResourceManager& a_manager, int a_result);
   void Stop( AResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceManagerStartedState
//
// Description: Resource Manager started state
//
///////////////////////////////////////////////////////////////////////////////
class CResourceManagerStartedState : public AResourceManagerState
{
public:
   const char* StateDesc() { return "Started"; }
   void OnCallOffered( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   void OnResourceGroupAvailable( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup);
   void OnResourceGroupReset( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup);
   void OnCallflowAvailable( AResourceManager& a_manager, ACallflowSptr a_callflow);
   void OnCallflowReset( AResourceManager& a_manager, ACallflowSptr a_callflow);
   void OnCallDisconnected( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   void Stop( AResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceManagerStoppingState
//
// Description: Resource Manager stopping state
//
///////////////////////////////////////////////////////////////////////////////
class CResourceManagerStoppingState : public AResourceManagerState
{
public:
   const char* StateDesc() { return "Stopping"; }
   void OnCallflowManagerStopped( AResourceManager& a_manager, int a_result);
   void OnResourceGroupManagerStopped( AResourceManager& a_manager, int a_result);
   void OnSipResourceManagerStopped( AResourceManager& a_manager, int a_result);
   void OnStopped( AResourceManager& a_manager, int a_result);
};

#endif
