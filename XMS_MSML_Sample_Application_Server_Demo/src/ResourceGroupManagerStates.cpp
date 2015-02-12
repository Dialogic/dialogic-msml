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
// File Name: ResourceGroupManagerStates.cpp
//
// Description: Implementation of the ResourceGroupManager state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "ResourceGroupManagerStates.h"
#include "AResourceGroupManager.h"
#include "AResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::Start(AResourceGroupManager &a_manager)
//
// Description: Start command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::Start( AResourceGroupManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Start", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::OnStarted(AResourceGroupManager &a_manager, int a_result)
//
// Description: OnStarted event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::OnStarted( AResourceGroupManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStarted", "a_result: " + AsString( a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::GetResourceGroup(AResourceGroupManager &a_manager, ASipResourceSptr a_inboundSipResource)
//
// Description: GetResourceGroup command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             ASipResourceSptr a_inboundSipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::GetResourceGroup( AResourceGroupManager& a_manager, ASipResourceSptr a_inboundSipResource) 
{ 
   LogInvalidStateForCommand( a_manager, "GetResourceGroup", a_inboundSipResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::OnResourceGroupAvailable(AResourceGroupManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: OnResourceGroupAvailable event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::OnResourceGroupAvailable( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup)
{
   LogInvalidStateForEvent( a_manager, "OnResourceGroupAvailable", a_resourceGroup->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::ResetResourceGroup(AResourceGroupManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: ResetResourceGroup command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::ResetResourceGroup( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup) 
{ 
   LogInvalidStateForCommand( a_manager, "ResetResourceGroup", a_resourceGroup->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::OnResourceGroupReset(AResourceGroupManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: OnResourceGroupReset event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::OnResourceGroupReset( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup)
{
   LogInvalidStateForEvent( a_manager, "OnResourceGroupReset", a_resourceGroup->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::Stop(AResourceGroupManager &a_manager)
//
// Description: Stop command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::Stop( AResourceGroupManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Stop", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::OnStopped(AResourceGroupManager &a_manager, int a_result)
//
// Description: OnStopped event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::OnStopped( AResourceGroupManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStopped", "a_result: " + AsString( a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::LogInvalidStateForCommand(AResourceGroupManager &a_manager, const char *a_command, const std::string &a_msg)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             const char *a_command
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::LogInvalidStateForCommand( AResourceGroupManager& a_manager, const char* a_command, const std::string& a_msg) 
{ 
   a_manager.LogError( a_command, "Invalid state for command." + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManagerState::LogInvalidStateForEvent(AResourceGroupManager &a_manager, const char *a_event, const std::string &a_msg)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             const char *a_event
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManagerState::LogInvalidStateForEvent( AResourceGroupManager& a_manager, const char* a_event, const std::string& a_msg) 
{ 
   a_manager.LogError( a_event, "Invalid state for event. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStoppedState::Start(AResourceGroupManager &a_manager)
//
// Description: Start the Resource Group Manager
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStoppedState::Start( AResourceGroupManager& a_manager) 
{ 
   if (a_manager.PrimStart() == 0) 
   {
      a_manager.SetStateToStarting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStartingState::OnStarted(AResourceGroupManager &a_manager, int a_result)
//
// Description: Handle the Resource Group Manager started completion event
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStartingState::OnStarted( AResourceGroupManager& a_manager, int a_result) 
{ 
   if (a_manager.PrimOnStarted( a_result) == 0)  
   {
      a_manager.SetStateToStarted();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStartingState::Stop(AResourceGroupManager &a_manager)
//
// Description: Stop the Resource Group Manager
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStartingState::Stop( AResourceGroupManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
   {
      a_manager.SetStateToStopping();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStartedState::GetResourceGroup(AResourceGroupManager &a_manager, ASipResourceSptr a_inboundSipResource)
//
// Description: Get a Resource Group from the Resource Group Manager
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             ASipResourceSptr a_inboundSipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStartedState::GetResourceGroup( AResourceGroupManager& a_manager, ASipResourceSptr a_inboundSipResource) 
{ 
   a_manager.PrimGetResourceGroup( a_inboundSipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStartedState::OnResourceGroupAvailable(AResourceGroupManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: Handle the Resource Group available completion event
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStartedState::OnResourceGroupAvailable( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup)
{
   a_manager.PrimOnResourceGroupAvailable( a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStartedState::ResetResourceGroup(AResourceGroupManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: Reset a Resource Group
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStartedState::ResetResourceGroup( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup) 
{ 
   a_manager.PrimResetResourceGroup( a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStartedState::OnResourceGroupReset(AResourceGroupManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: Handle the Resource Group reset completion event
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStartedState::OnResourceGroupReset( AResourceGroupManager& a_manager, AResourceGroupSptr a_resourceGroup)
{
   a_manager.PrimOnResourceGroupReset( a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStartedState::Stop(AResourceGroupManager &a_manager)
//
// Description: Stop the Resource Group Manager
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStartedState::Stop( AResourceGroupManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
   {
      a_manager.SetStateToStopping();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupManagerStoppingState::OnStopped(AResourceGroupManager &a_manager, int a_result)
//
// Description: Handle the Resource Group Manager stopped completion event
//
// Return: void
//
// Parameters: AResourceGroupManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupManagerStoppingState::OnStopped( AResourceGroupManager& a_manager, int a_result) 
{ 
   if ( a_manager.PrimOnStopped( a_result) == 0) 
   {
      a_manager.SetStateToStopped();
   }
}
