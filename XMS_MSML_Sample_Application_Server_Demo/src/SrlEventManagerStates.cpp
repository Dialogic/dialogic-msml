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
// File Name: SrlEventManagerStates.cpp
//
// Description: Implementation of the SrlEventManager state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "ASrlEventManager.h"
#include "AResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManagerState::Start(ASrlEventManager &a_manager)
//
// Description: Start command is invalid in this state
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManagerState::Start( ASrlEventManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Start", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManagerState::Stop(ASrlEventManager &a_manager)
//
// Description: Stop command is invalid in this state
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManagerState::Stop( ASrlEventManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Stop", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManagerState::OnStarted(ASrlEventManager &a_manager, int a_result)
//
// Description: OnStarted event is invalid in this state
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManagerState::OnStarted( ASrlEventManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManagerState::OnStopped(ASrlEventManager &a_manager, int a_result)
//
// Description: OnStopped event is invalid in this state
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManagerState::OnStopped( ASrlEventManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManagerState::LogInvalidStateForCommand(ASrlEventManager &a_manager, const char *a_command, const std::string &a_msg)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//             const char *a_command
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManagerState::LogInvalidStateForCommand( ASrlEventManager& a_manager, const char* a_command, const std::string& a_msg) 
{ 
   a_manager.LogError( a_command, "Invalid state for command. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManagerState::LogInvalidStateForEvent(ASrlEventManager &a_manager, const char *a_event, const std::string &a_msg)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//             const char *a_event
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManagerState::LogInvalidStateForEvent( ASrlEventManager& a_manager, const char* a_event, const std::string& a_msg) 
{ 
   a_manager.LogError( a_event, "Invalid state for event. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSrlEventManagerStoppedState::Start(ASrlEventManager &a_manager)
//
// Description: Start the SRL Event Manager
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSrlEventManagerStoppedState::Start( ASrlEventManager& a_manager) 
{ 
   if (a_manager.PrimStart() == 0) 
      a_manager.SetStateToStarting();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSrlEventManagerStartingState::OnStarted(ASrlEventManager &a_manager, int a_result)
//
// Description: Handle the the SRL Event Manager started completion event
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CSrlEventManagerStartingState::OnStarted( ASrlEventManager& a_manager, int a_result) 
{ 
   if (a_manager.PrimOnStarted( a_result) == 0)  
      a_manager.SetStateToStarted();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSrlEventManagerStartingState::Stop(ASrlEventManager &a_manager)
//
// Description: Stop the SRL Event Manager
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSrlEventManagerStartingState::Stop( ASrlEventManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
      a_manager.SetStateToStopping();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSrlEventManagerStartedState::Stop(ASrlEventManager &a_manager)
//
// Description: Stop the SRL Event Manager
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSrlEventManagerStartedState::Stop( ASrlEventManager& a_manager) 
{ 
   if (a_manager.PrimStop() == 0) 
      a_manager.SetStateToStopping();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSrlEventManagerStoppingState::OnStopped(ASrlEventManager &a_manager, int a_result)
//
// Description: Handle the SRL Event Manager stopped completion event
//
// Return: void
//
// Parameters: ASrlEventManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CSrlEventManagerStoppingState::OnStopped( ASrlEventManager& a_manager, int a_result) 
{ 
   if ( a_manager.PrimOnStopped( a_result) == 0) 
      a_manager.SetStateToStopped();
}
