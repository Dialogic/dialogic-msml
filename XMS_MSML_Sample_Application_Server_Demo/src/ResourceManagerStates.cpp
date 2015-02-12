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
// File Name: ResourceManagerStates.cpp
//
// Description: Implementation of the ResourceManager state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "TypeDefs.h"
#include "ResourceManagerStates.h"
#include "AResourceManager.h"
#include "ASipResource.h"
#include "AResourceGroup.h"
#include "ACallflow.h"
#include "Utility.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::Start(AResourceManager &a_manager)
//
// Description: Start command is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::Start( AResourceManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Start", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnCallflowManagerStarted(AResourceManager &a_manager, int a_result)
//
// Description: OnCallflowManagerStarted event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnCallflowManagerStarted( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnCallflowManagerStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnResourceGroupManagerStarted(AResourceManager &a_manager, int a_result)
//
// Description: OnResourceGroupManagerStarted event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnResourceGroupManagerStarted( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnResourceGroupManagerStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnSipResourceManagerStarted(AResourceManager &a_manager, int a_result)
//
// Description: OnSipResourceManagerStarted event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnSipResourceManagerStarted( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSipResourceManagerStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnStarted(AResourceManager &a_manager, int a_result)
//
// Description: OnStarted event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnStarted( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnCallOffered(AResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: OnCallOffered event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnCallOffered( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnCallOffered", a_sipResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnResourceGroupAvailable(AResourceManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: OnResourceGroupAvailable event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnResourceGroupAvailable( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup)
{ 
   LogInvalidStateForEvent( a_manager, "OnResourceGroupAvailable", a_resourceGroup->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnResourceGroupReset(AResourceManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: OnResourceGroupReset event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnResourceGroupReset( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup)
{ 
   LogInvalidStateForEvent( a_manager, "OnResourceGroupReset", a_resourceGroup->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnCallflowAvailable(AResourceManager &a_manager, ACallflowSptr a_callflow)
//
// Description: OnCallflowAvailable event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnCallflowAvailable( AResourceManager& a_manager, ACallflowSptr a_callflow)
{ 
   LogInvalidStateForEvent( a_manager, "OnCallflowAvailable", a_callflow->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnCallflowReset(AResourceManager &a_manager, ACallflowSptr a_callflow)
//
// Description: OnCallflowReset event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnCallflowReset( AResourceManager& a_manager, ACallflowSptr a_callflow)
{ 
   LogInvalidStateForEvent( a_manager, "OnCallflowReset", a_callflow->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnCallDisconnected(AResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: OnCallDisconnected event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnCallDisconnected( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnCallDisconnected", a_sipResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::Stop(AResourceManager &a_manager)
//
// Description: Stop command is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::Stop( AResourceManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Stop", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnCallflowManagerStopped(AResourceManager &a_manager, int a_result)
//
// Description: OnCallflowManagerStopped event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnCallflowManagerStopped( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnCallflowManagerStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnResourceGroupManagerStopped(AResourceManager &a_manager, int a_result)
//
// Description: OnResourceGroupManagerStopped event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnResourceGroupManagerStopped( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnResourceGroupManagerStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnSipResourceManagerStopped(AResourceManager &a_manager, int a_result)
//
// Description: OnSipResourceManagerStopped event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnSipResourceManagerStopped( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSipResourceManagerStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::OnStopped(AResourceManager &a_manager, int a_result)
//
// Description: OnStopped event is invalid in this state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::OnStopped( AResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::LogInvalidStateForCommand(AResourceManager &a_manager, const char *a_command, const std::string &a_msg)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             const char *a_command
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::LogInvalidStateForCommand( AResourceManager& a_manager, const char*  a_command, const std::string& a_msg) 
{ 
   a_manager.LogError( a_command, "Invalid state for command. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManagerState::LogInvalidStateForEvent(AResourceManager &a_manager, const char *a_event, const std::string &a_msg)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             const char *a_event
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManagerState::LogInvalidStateForEvent( AResourceManager& a_manager, const char*  a_event, const std::string& a_msg) 
{ 
   a_manager.LogError( a_event, "Invalid state for event. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStoppedState::Start(AResourceManager &a_manager)
//
// Description: Start the Resource Manager
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStoppedState::Start( AResourceManager& a_manager) 
{ 
   if (a_manager.PrimStart() == 0) 
   {
      a_manager.SetStateToStarting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartingState::OnCallflowManagerStarted(AResourceManager &a_manager, int a_result)
//
// Description: Handle Callflow Manager started completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartingState::OnCallflowManagerStarted( AResourceManager& a_manager, int a_result) 
{ 
   a_manager.PrimOnCallflowManagerStarted( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartingState::OnResourceGroupManagerStarted(AResourceManager &a_manager, int a_result)
//
// Description: Handle Resource Group Manager started completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartingState::OnResourceGroupManagerStarted( AResourceManager& a_manager, int a_result) 
{ 
   a_manager.PrimOnResourceGroupManagerStarted( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartingState::OnSipResourceManagerStarted(AResourceManager &a_manager, int a_result)
//
// Description: Handle SIP Resource Manager started completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartingState::OnSipResourceManagerStarted( AResourceManager& a_manager, int a_result) 
{ 
   a_manager.PrimOnSipResourceManagerStarted( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartingState::OnStarted(AResourceManager &a_manager, int a_result)
//
// Description: Handle Resource Manager started completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartingState::OnStarted( AResourceManager& a_manager, int a_result) 
{ 
   if (a_manager.PrimOnStarted( a_result) == 0)  
   {
      a_manager.SetStateToStarted();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartingState::Stop(AResourceManager &a_manager)
//
// Description: Stop the Resource Manager
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartingState::Stop( AResourceManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
   {
      a_manager.SetStateToStopping();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartedState::OnCallOffered(AResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP Resource call offered event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartedState::OnCallOffered( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   a_manager.PrimOnCallOffered( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartedState::OnResourceGroupAvailable(AResourceManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: Handle Resource Group available completion  event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartedState::OnResourceGroupAvailable( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup)
{ 
   a_manager.PrimOnResourceGroupAvailable( a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartedState::OnResourceGroupReset(AResourceManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: Handle Resource Group reset completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartedState::OnResourceGroupReset( AResourceManager& a_manager, AResourceGroupSptr a_resourceGroup)
{ 
   a_manager.PrimOnResourceGroupReset( a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartedState::OnCallflowAvailable(AResourceManager &a_manager, ACallflowSptr a_callflow)
//
// Description: Handle Callflow Manager callflow available completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartedState::OnCallflowAvailable( AResourceManager& a_manager, ACallflowSptr a_callflow)
{ 
   a_manager.PrimOnCallflowAvailable( a_callflow);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartedState::OnCallflowReset(AResourceManager &a_manager, ACallflowSptr a_callflow)
//
// Description: Handle Callflow reset completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartedState::OnCallflowReset( AResourceManager& a_manager, ACallflowSptr a_callflow)
{ 
   a_manager.PrimOnCallflowReset( a_callflow);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartedState::OnCallDisconnected(AResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP Resource call disconnected event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartedState::OnCallDisconnected( AResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   a_manager.PrimOnCallDisconnected( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStartedState::Stop(AResourceManager &a_manager)
//
// Description: Stop the Resource Manager
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStartedState::Stop( AResourceManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
   {
      a_manager.SetStateToStopping();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStoppingState::OnCallflowManagerStopped(AResourceManager &a_manager, int a_result)
//
// Description: Handle Callflow Manager stopped completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStoppingState::OnCallflowManagerStopped( AResourceManager& a_manager, int a_result) 
{ 
   a_manager.PrimOnCallflowManagerStopped( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStoppingState::OnResourceGroupManagerStopped(AResourceManager &a_manager, int a_result)
//
// Description: Handle Resource Group Manager stopped completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStoppingState::OnResourceGroupManagerStopped( AResourceManager& a_manager, int a_result) 
{ 
   a_manager.PrimOnResourceGroupManagerStopped( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStoppingState::OnSipResourceManagerStopped(AResourceManager &a_manager, int a_result)
//
// Description: Handle SIP Resource Manager stopped completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStoppingState::OnSipResourceManagerStopped( AResourceManager& a_manager, int a_result) 
{ 
   a_manager.PrimOnSipResourceManagerStopped( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManagerStoppingState::OnStopped(AResourceManager &a_manager, int a_result)
//
// Description: Handle Resource Manager stopped completion event
//
// Return: void
//
// Parameters: AResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManagerStoppingState::OnStopped( AResourceManager& a_manager, int a_result) 
{ 
   if ( a_manager.PrimOnStopped( a_result) == 0) 
   {
      a_manager.SetStateToStopped();
   }
}
