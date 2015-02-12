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
// File Name: SipBoardResourceStates.cpp
//
// Description: Implementation of the SipBoardResource state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "SipBoardResourceStates.h"
#include "ASipBoardResource.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResourceState::Open(ASipBoardResource &a_sipBoardResource)
//
// Description: Open command is invalid in this state
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResourceState::Open( ASipBoardResource& a_sipBoardResource) 
{ 
   LogInvalidStateForCommand( a_sipBoardResource, "Open");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResourceState::OnOpened(ASipBoardResource &a_sipBoardResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnOpened event is invalid in this state
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResourceState::OnOpened( ASipBoardResource& a_sipBoardResource, const CMetaEventSptr& a_metaEvent) 
{ 
   LogInvalidStateForCommand( a_sipBoardResource, "OnOpened");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResourceState::Close(ASipBoardResource &a_sipBoardResource)
//
// Description: Close command is invalid in this state
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResourceState::Close( ASipBoardResource& a_sipBoardResource) 
{ 
   LogInvalidStateForCommand( a_sipBoardResource, "Close");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResourceState::OnClosed(ASipBoardResource &a_sipBoardResource)
//
// Description: OnCloseed event is invalid in this state
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResourceState::OnClosed( ASipBoardResource& a_sipBoardResource) 
{ 
   LogInvalidStateForEvent( a_sipBoardResource, "OnClosed");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResourceState::LogInvalidStateForCommand(ASipBoardResource &a_sipBoardResource, const char *a_command)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//             const char *a_command
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResourceState::LogInvalidStateForCommand( ASipBoardResource& a_sipBoardResource, const char* a_command) 
{ 
   a_sipBoardResource.LogError( a_command, "Invalid state for command");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResourceState::LogInvalidStateForEvent(ASipBoardResource &a_sipBoardResource, const char *a_event)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//             const char *a_event
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResourceState::LogInvalidStateForEvent( ASipBoardResource& a_sipBoardResource, const char* a_event) 
{ 
   a_sipBoardResource.LogError( a_event, "Invalid state for event");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipBoardResourceClosedState::Open(ASipBoardResource &a_sipBoardResource)
//
// Description: Open the SIP Board Resource
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipBoardResourceClosedState::Open( ASipBoardResource& a_sipBoardResource) 
{ 
   if (a_sipBoardResource.PrimOpen() == 0) 
   {
      a_sipBoardResource.SetStateToOpening();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipBoardResourceOpeningState::OnOpened(ASipBoardResource &a_sipBoardResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle the SIP Board Resource opened completion event
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipBoardResourceOpeningState::OnOpened( ASipBoardResource& a_sipBoardResource, const CMetaEventSptr& a_metaEvent) 
{ 
   if (a_sipBoardResource.PrimOnOpened( a_metaEvent) == 0)   
   {
      a_sipBoardResource.SetStateToOpened();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipBoardResourceOpenedState::Close(ASipBoardResource &a_sipBoardResource)
//
// Description: Close the SIP Board Resource
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipBoardResourceOpenedState::Close( ASipBoardResource& a_sipBoardResource) 
{ 
   if ( a_sipBoardResource.PrimClose() == 0) 
   {
      a_sipBoardResource.SetStateToClosing();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipBoardResourceClosingState::OnClosed(ASipBoardResource &a_sipBoardResource)
//
// Description: Handle the SIP Resource closed completion event
//
// Return: void
//
// Parameters: ASipBoardResource &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipBoardResourceClosingState::OnClosed( ASipBoardResource& a_sipBoardResource) 
{ 
   if ( a_sipBoardResource.PrimOnClosed() == 0) 
   {
      a_sipBoardResource.SetStateToClosed();
   }
}
