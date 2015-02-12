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
// File Name: HttpManagerStates.cpp
//
// Description: Implementation of the HttpManager state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "HttpManagerStates.h"
#include "AHttpManager.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManagerState::LogInvalidStateForCommand(AHttpManager &a_httpManager, const char *a_command, const std::string &a_msg)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: AHttpManager &a_httpManager
//             const char *a_command
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManagerState::LogInvalidStateForCommand( AHttpManager& a_httpManager, const char*  a_command, const std::string& a_msg) 
{ 
   a_httpManager.LogError( a_command, "Invalid state for command. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManagerState::LogInvalidStateForEvent(AHttpManager &a_httpManager, const char *a_event, const std::string &a_msg)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: AHttpManager &a_httpManager
//             const char *a_event
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManagerState::LogInvalidStateForEvent( AHttpManager& a_httpManager, const char*  a_event, const std::string& a_msg) 
{ 
   a_httpManager.LogError( a_event, "Invalid state for event. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManagerState::Start(AHttpManager &a_httpManager)
//
// Description:  Start command is invalid in this state
//
// Return: none
//
// Parameters: AHttpManager &a_httpManager
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManagerState::Start( AHttpManager& a_httpManager)
{
   LogInvalidStateForCommand( a_httpManager, "Start", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManagerState::OnStarted(AHttpManager &a_httpManager, int a_result)
//
// Description:  OnStarted event is invalid in this state
//
// Return: none
//
// Parameters: AHttpManager &a_httpManager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManagerState::OnStarted( AHttpManager& a_httpManager, int a_result)
{
   LogInvalidStateForEvent( a_httpManager, "OnStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManagerState::Stop(AHttpManager &a_httpManager)
//
// Description:  Stop command is invalid in this state
//
// Return: none
//
// Parameters: AHttpManager &a_httpManager
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManagerState::Stop( AHttpManager& a_httpManager)
{
   LogInvalidStateForCommand( a_httpManager, "Stop", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AHttpManagerState::OnStopped(AHttpManager &a_httpManager, int a_result)
//
// Description:  OnStopped event is invalid in this state
//
// Return: void
//
// Parameters: AHttpManager &a_httpManager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManagerState::OnStopped( AHttpManager& a_httpManager, int a_result)
{
   LogInvalidStateForEvent( a_httpManager, "OnStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * CHttpManagerStoppedState::StateDesc()
//
// Description: Return a description of the state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* CHttpManagerStoppedState::StateDesc()
{
   return "Stopped";
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpManagerStoppedState::Start(AHttpManager &a_httpManager)
//
// Description: Start the HTTP Manager
//
// Return: none
//
// Parameters: AHttpManager &a_httpManager
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManagerStoppedState::Start( AHttpManager& a_httpManager)
{
   if (a_httpManager.PrimStart() == 0) 
   {
      a_httpManager.SetStateToStarting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * CHttpManagerStartingState::StateDesc()
//
// Description: Return a description of the state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* CHttpManagerStartingState::StateDesc()
{
   return "Starting";
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CHttpManagerStartingState::OnStarted(AHttpManager &a_httpManager, int a_result)
//
// Description: Handle HTTP Manager started completion event
//
// Return: void
//
// Parameters: AHttpManager &a_httpManager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManagerStartingState::OnStarted( AHttpManager& a_httpManager, int a_result) 
{ 
   if ( a_httpManager.PrimOnStarted( a_result) == 0)
   {
      a_httpManager.SetStateToStarted();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpManagerStartingState::Stop(AHttpManager &a_httpManager)
//
// Description: Stop the HTTP Manager
//
// Return: none
//
// Parameters: AHttpManager &a_httpManager
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManagerStartingState::Stop( AHttpManager& a_httpManager)
{
   a_httpManager.SetStateToStopping();
   a_httpManager.PrimStop();
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * CHttpManagerStartedState::StateDesc()
//
// Description: Return a description of the state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* CHttpManagerStartedState::StateDesc()
{
   return "Started";
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpManagerStartedState::Stop(AHttpManager &a_httpManager)
//
// Description: Stop the HTTP Manager
//
// Return: none
//
// Parameters: AHttpManager &a_httpManager
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManagerStartedState::Stop( AHttpManager& a_httpManager)
{
   a_httpManager.SetStateToStopping();
   a_httpManager.PrimStop();
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * CHttpManagerStoppingState::StateDesc()
//
// Description: Return a description of the state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* CHttpManagerStoppingState::StateDesc()
{
   return "Stopping";
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CHttpManagerStoppingState::OnStopped(AHttpManager &a_httpManager, int a_result)
//
// Description: Handle HTTP Manager stopped completion event
//
// Return: void
//
// Parameters: AHttpManager &a_httpManager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManagerStoppingState::OnStopped( AHttpManager& a_httpManager, int a_result) 
{ 
   if ( a_httpManager.PrimOnStopped( a_result) == 0)
   {
      a_httpManager.SetStateToStopped();
   }
}

