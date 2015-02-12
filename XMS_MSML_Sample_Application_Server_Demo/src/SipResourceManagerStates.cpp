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
// File Name: SipResourceManagerStates.cpp
//
// Description: Implementation of the SipResourceManager state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "ASipResourceManager.h"
#include "ASipBoardResource.h"
#include "ASipResource.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::Start(ASipResourceManager &a_manager)
//
// Description: Start command is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::Start( ASipResourceManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Start", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnSrlEventManagerStarted(ASipResourceManager &a_manager, int a_result)
//
// Description: OnSrlEventManagerStarted event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnSrlEventManagerStarted( ASipResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSrlEventManagerStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnSipBoardResourceOpened(ASipResourceManager &a_manager, const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: OnSipBoardResourceOpened event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnSipBoardResourceOpened( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSipBoardResourceOpened", a_sipBoardResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnSipResourceOpened(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: OnSipResourceOpened event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnSipResourceOpened( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSipResourceOpened", a_sipResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnStarted(ASipResourceManager &a_manager, int a_result)
//
// Description: OnStarted event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnStarted( ASipResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStarted", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::EnableInboundCalls(ASipResourceManager &a_manager)
//
// Description: EnableInboundCalls command is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::EnableInboundCalls( ASipResourceManager& a_manager) 
{ 
   LogInvalidStateForEvent( a_manager, "EnableInboundCalls", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnCallOffered(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: OnCallOffered event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnCallOffered( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnCallOffered", a_sipResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnCallDisconnected(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: OnCallDisconnected event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnCallDisconnected( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnCallDisconnected", a_sipResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::Stop(ASipResourceManager &a_manager)
//
// Description: Stop command is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::Stop( ASipResourceManager& a_manager) 
{ 
   LogInvalidStateForCommand( a_manager, "Stop", "");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnSipResourceClosed(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: OnSipResourceClosed event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnSipResourceClosed( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSipResourceClosed", a_sipResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnSipBoardResourceClosed(ASipResourceManager &a_manager, const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: OnSipBoardResourceClosed event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnSipBoardResourceClosed( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSipBoardResourceClosed", a_sipBoardResource->Name());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnSrlEventManagerStopped(ASipResourceManager &a_manager, int a_result)
//
// Description: OnSrlEventManagerStopped event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnSrlEventManagerStopped( ASipResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnSrlEventManagerStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::OnStopped(ASipResourceManager &a_manager, int a_result)
//
// Description: OnStopped event is invalid in this state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::OnStopped( ASipResourceManager& a_manager, int a_result) 
{ 
   LogInvalidStateForEvent( a_manager, "OnStopped", "a_result: " + AsString(a_result));
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::LogInvalidStateForCommand(ASipResourceManager &a_manager, const char *a_command, const std::string &a_msg)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const char *a_command
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::LogInvalidStateForCommand( ASipResourceManager& a_manager, const char* a_command, const std::string& a_msg) 
{ 
   a_manager.LogError( a_command, "Invalid state for command. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManagerState::LogInvalidStateForEvent(ASipResourceManager &a_manager, const char *a_event, const std::string &a_msg)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const char *a_event
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManagerState::LogInvalidStateForEvent( ASipResourceManager& a_manager, const char* a_event, const std::string& a_msg) 
{ 
   a_manager.LogError( a_event, "Invalid state for event. " + a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStoppedState::Start(ASipResourceManager &a_manager)
//
// Description: Start the SIP Resource Manager
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStoppedState::Start( ASipResourceManager& a_manager) 
{ 
   if (a_manager.PrimStartSrlEventManager() == 0) 
   {
      a_manager.SetStateToStartingSrlEventManager();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStartingSrlEventManagerState::OnSrlEventManagerStarted(ASipResourceManager &a_manager, int a_result)
//
// Description: Handle the SRL Event Manager started completion event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStartingSrlEventManagerState::OnSrlEventManagerStarted( ASipResourceManager& a_manager, int a_result) 
{ 
   if (a_manager.PrimOnSrlEventManagerStarted( a_result) == 0) 
   {
      if ( a_manager.PrimOpenSipBoardResource() == 0)
      {
         a_manager.SetStateToOpeningSipBoardResource();
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStartingSrlEventManagerState::Stop(ASipResourceManager &a_manager)
//
// Description: Stop the SIP Resource Manager
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStartingSrlEventManagerState::Stop( ASipResourceManager& a_manager) 
{ 
   if (a_manager.PrimStopSrlEventManager() == 0)
   {
      a_manager.SetStateToStoppingSrlEventManager();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerOpeningSipBoardResourceState::OnSipBoardResourceOpened(ASipResourceManager &a_manager, const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Handle the SIP Board Resource opened completion event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerOpeningSipBoardResourceState::OnSipBoardResourceOpened( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource) 
{ 
   if (a_manager.PrimOnSipBoardResourceOpened( a_sipBoardResource) == 0)
   {
      if ( a_manager.PrimOpenSipResources() == 0)
      {
         a_manager.SetStateToOpeningSipResources();
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerOpeningSipResourcesState::OnSipResourceOpened(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP Resource opened completion event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerOpeningSipResourcesState::OnSipResourceOpened( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   a_manager.PrimOnSipResourceOpened( a_sipResource);
   if ( ! a_manager.SipResourcesPending() )
   {
      a_manager.OnStarted( 0);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerOpeningSipResourcesState::OnStarted(ASipResourceManager &a_manager, int a_result)
//
// Description: Handle the SIP Resource Manager started completion event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerOpeningSipResourcesState::OnStarted( ASipResourceManager& a_manager, int a_result) 
{ 
   if (a_manager.PrimOnStarted( a_result) == 0) 
   {
      a_manager.SetStateToStarted();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStartedState::EnableInboundCalls(ASipResourceManager &a_manager)
//
// Description: EnableInbounfCalls on the SIP Resources
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStartedState::EnableInboundCalls( ASipResourceManager& a_manager) 
{ 
   a_manager.PrimEnableInboundCalls();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStartedState::OnCallOffered(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP Resource call offered event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStartedState::OnCallOffered( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   a_manager.PrimOnCallOffered( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStartedState::OnCallDisconnected(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP Resource call disconnected event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStartedState::OnCallDisconnected( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   a_manager.PrimOnCallDisconnected( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerOpeningSipBoardResourceState::Stop(ASipResourceManager &a_manager)
//
// Description: Stop the SIP Resource Manager
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerOpeningSipBoardResourceState::Stop( ASipResourceManager& a_manager) 
{ 
   if (a_manager.PrimCloseSipBoardResource() == 0)  
   {
      a_manager.SetStateToClosingSipBoardResource();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerOpeningSipResourcesState::Stop(ASipResourceManager &a_manager)
//
// Description: Stop the SIP Resource Manager
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerOpeningSipResourcesState::Stop( ASipResourceManager& a_manager) 
{ 
   if (a_manager.PrimCloseSipResources() == 0)  
   {
      a_manager.SetStateToClosingSipResources();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStartedState::Stop(ASipResourceManager &a_manager)
//
// Description: Stop the SIP Resource Manager
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStartedState::Stop( ASipResourceManager& a_manager) 
{ 
   if (a_manager.PrimCloseSipResources() == 0) 
   {
      a_manager.SetStateToClosingSipResources();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerClosingSipResourcesState::OnSipResourceClosed(ASipResourceManager &a_manager, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP Resource closed completion event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerClosingSipResourcesState::OnSipResourceClosed( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource) 
{ 
   a_manager.PrimOnSipResourceClosed( a_sipResource);
   if ( ! a_manager.SipResourcesPending() )
   {
      if ( a_manager.PrimCloseSipBoardResource() == 0)
      {
         a_manager.SetStateToClosingSipBoardResource();
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerClosingSipBoardResourceState::OnSipBoardResourceClosed(ASipResourceManager &a_manager, const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Handle the SIP Board Resource closed completion event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerClosingSipBoardResourceState::OnSipBoardResourceClosed( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource) 
{ 
   if ( a_manager.PrimOnSipBoardResourceClosed( a_sipBoardResource) == 0)
   {
      if ( a_manager.PrimStopSrlEventManager() == 0)
      {
         a_manager.SetStateToStoppingSrlEventManager();
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStoppingSrlEventManagerState::OnSrlEventManagerStopped(ASipResourceManager &a_manager, int a_result)
//
// Description: Handle the SRL Event Manager stopped completion event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStoppingSrlEventManagerState::OnSrlEventManagerStopped( ASipResourceManager& a_manager, int a_result) 
{ 
   if ( a_manager.PrimOnSrlEventManagerStopped( a_result) == 0)
   {
      a_manager.OnStopped( 0);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceManagerStoppingSrlEventManagerState::OnStopped(ASipResourceManager &a_manager, int a_result)
//
// Description: Handle the SIP Resource Manager stopped completione event
//
// Return: void
//
// Parameters: ASipResourceManager &a_manager
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceManagerStoppingSrlEventManagerState::OnStopped( ASipResourceManager& a_manager, int a_result) 
{ 
   if ( a_manager.PrimOnStopped( a_result) == 0) 
   {
      a_manager.SetStateToStopped();
   }
}

