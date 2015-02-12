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
// File Name: CallflowManagerStates.cpp
//
// Description: Implementation of the Callflow Manager state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "ACallflowManager.h"
#include "AResourceGroup.h"
#include "ACallflow.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::Start(ACallflowManager &a_manager)
//
// Description: Start command is invalid in this state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::Start( ACallflowManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Start", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::Stop(ACallflowManager &a_manager)
//
// Description: Stop command is invalid in this state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::Stop( ACallflowManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Stop", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::OnStarted(ACallflowManager &a_manager, int a_result)
//
// Description: OnStarted event is invalid in this state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::OnStarted( ACallflowManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::GetCallflow(ACallflowManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: GetCallflow command is invalid in this state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::GetCallflow( ACallflowManager& a_manager, AResourceGroupSptr a_resourceGroup)
{ 
   LogInvalidStateForCommand( a_manager, "GetCallflow", a_resourceGroup->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::ResetCallflow(ACallflowManager &a_manager, ACallflowSptr a_callflow)
//
// Description: ResetCallflow command is invalid in this state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::ResetCallflow( ACallflowManager& a_manager, ACallflowSptr a_callflow)
{ 
   LogInvalidStateForCommand( a_manager, "ResetCallflow", a_callflow->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::OnStopped(ACallflowManager &a_manager, int a_result)
//
// Description: OnStopped event is invalid in this state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::OnStopped( ACallflowManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::LogInvalidStateForCommand(ACallflowManager &a_manager, const char *a_command, const std::string &a_msg)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             const char *a_command
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::LogInvalidStateForCommand( ACallflowManager& a_manager, const char* a_command, const std::string& a_msg) 
{ 
   a_manager.LogError( a_command, "Invalid state for command. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManagerState::LogInvalidStateForEvent(ACallflowManager &a_manager, const char *a_event, const std::string &a_msg)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             const char *a_event
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManagerState::LogInvalidStateForEvent( ACallflowManager& a_manager, const char* a_event, const std::string& a_msg) 
{ 
   a_manager.LogError( a_event, "Invalid state for event. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowManagerStoppedState::Start(ACallflowManager &a_manager)
//
// Description: Start the Callflow Manager
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowManagerStoppedState::Start( ACallflowManager& a_manager) 
{ 
   if (a_manager.PrimStart() == 0) 
      a_manager.SetStateToStarting();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowManagerStartingState::OnStarted(ACallflowManager &a_manager, int a_result)
//
// Description: Handle the Callflow Manager started completion event
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowManagerStartingState::OnStarted( ACallflowManager& a_manager, int a_result) 
{ 
   if (a_manager.PrimOnStarted( a_result) == 0)  
      a_manager.SetStateToStarted();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowManagerStartingState::Stop(ACallflowManager &a_manager)
//
// Description: Stop the Callflow Manager
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowManagerStartingState::Stop( ACallflowManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
      a_manager.SetStateToStopping();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowManagerStartedState::GetCallflow(ACallflowManager &a_manager, AResourceGroupSptr a_resourceGroup)
//
// Description: Get a Callflow object from the Callflow Manager
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowManagerStartedState::GetCallflow( ACallflowManager& a_manager, AResourceGroupSptr a_resourceGroup)
{
   a_manager.PrimGetCallflow( a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowManagerStartedState::ResetCallflow(ACallflowManager &a_manager, ACallflowSptr a_callflow)
//
// Description: Reset a Callflow object
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowManagerStartedState::ResetCallflow( ACallflowManager& a_manager, ACallflowSptr a_callflow)
{
   a_manager.PrimResetCallflow( a_callflow);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowManagerStartedState::Stop(ACallflowManager &a_manager)
//
// Description: Stop the Callflow Manager
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowManagerStartedState::Stop( ACallflowManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
      a_manager.SetStateToStopping();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowManagerStoppingState::OnStopped(ACallflowManager &a_manager, int a_result)
//
// Description: Handle the Callflow Manager stopped completion event
//
// Return: void
//
// Parameters: ACallflowManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowManagerStoppingState::OnStopped( ACallflowManager& a_manager, int a_result) 
{ 
   if ( a_manager.PrimOnStopped( a_result) == 0) 
      a_manager.SetStateToStopped();
}
